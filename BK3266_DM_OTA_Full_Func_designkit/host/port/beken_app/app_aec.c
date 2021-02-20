#include <string.h>
#include "aec.h"
#include "app_beken_includes.h"
#include "driver_beken_includes.h"

#define AEC_MULTIPLEX_SBC_MEM   (0)
#define ECHO_RX_BUFFER_SIZE     (360 * 2)
#define ECHO_TX_BUFFER_SIZE     (256 * 2)
int sample_rate_flag=0;
static uint8_t  aec_init_flag = 0;
static uint8_t* aec_rx_buf    = NULL;
static uint8_t* aec_tx_buf    = NULL;

static driver_ringbuff_t aec_rx_rb;
static driver_ringbuff_t aec_tx_rb;

static AECContext* aec = NULL;

CONST unsigned short HFP_VOLUME_Q15[17] =
{
    0,
    184,
    260,
    368,
    519,
    734,
    1036,
    1464,
    2068,
    2920,
    4125,
    5827,
    8231,
    11627,
    16423,
    23198,
    32767
};

#if (AEC_MULTIPLEX_SBC_MEM == 1)
static uint8 *get_aec_ram_buff(void)
{
    extern uint32 _sbcmem_begin;
    return (uint8 *)((uint32)&_sbcmem_begin + 4096);
}
#endif
typedef struct _app_aec_agc_s
{
	uint16 status;
	uint16 max;
	uint16 cnt;
	uint16 decay;
	uint16 para;
}app_aec_agc_t;
app_aec_agc_t app_aec_dac_agc;
enum AEC_AGC_STATUS
{
    AEC_AGC_INIT = 0,
    AEC_AGC_GETTING_MAX,
	AEC_AGC_DECAY,
	AEC_AGC_KEEP,
};

CONST uint8_t para[8]={0x08,0x0c,0x0a,0x0a,0x04,0xff,0xff,0xff};
void app_aec_init(int sample_rate)
{
    if(aec_init_flag == 0)
    {
        uint8_t  decay_time;
        int32_t  ec_depth;
        uint32_t aec_mem_size  = 0;
    sample_rate_flag = sample_rate;
        app_env_handle_t env_h = app_env_get_handle();

        INFO_PRT("AEC.init:%d\r\n", sample_rate);

        #if (AEC_MULTIPLEX_SBC_MEM == 1)
        aec_rx_buf    = get_aec_ram_buff();
        aec_mem_size += ECHO_RX_BUFFER_SIZE;
        aec_tx_buf    = get_aec_ram_buff() + aec_mem_size;
        aec_mem_size += ECHO_TX_BUFFER_SIZE;
        #else
        aec_rx_buf    = (uint8_t*)jmalloc(ECHO_RX_BUFFER_SIZE, M_ZERO);
        aec_tx_buf    = (uint8_t*)jmalloc(ECHO_TX_BUFFER_SIZE, M_ZERO);
        aec_mem_size += ECHO_RX_BUFFER_SIZE;
        aec_mem_size += ECHO_TX_BUFFER_SIZE;
        #endif

        rb_init(&aec_rx_rb, (uint8 *)aec_rx_buf, 0, ECHO_RX_BUFFER_SIZE);
        rb_init(&aec_tx_rb, (uint8 *)aec_tx_buf, 0, ECHO_TX_BUFFER_SIZE);

        #if (AEC_MULTIPLEX_SBC_MEM == 1)
        aec = (AECContext*)(get_aec_ram_buff() + aec_mem_size);
        aec_mem_size += aec_size(AEC_MAX_MIC_DELAY);
        #else
        aec = (AECContext*)jmalloc(aec_size(AEC_MAX_MIC_DELAY), M_ZERO);
        aec_mem_size += aec_size(AEC_MAX_MIC_DELAY);
        #endif

		extern AUDIO_CTRL_BLK  audio_ctrl_blk;
os_printf("aud_buf:%d,aec_buf:%d\r\n",(int32_t)rb_get_used_size(&audio_ctrl_blk.aud_rb) / 4,aec_mem_size);
        aec_init(aec);
	aec_ctrl(aec, AEC_CTRL_CMD_SET_PARAMS, (uint32)para);

    ec_depth = env_h->env_cfg.env_aec_cfg.aec_fft_shift;
//    ec_depth = ec_depth < 0 ? (6 + ec_depth) : (ec_depth << 3);
    ec_depth = 6 + ec_depth;
        aec_ctrl(aec, AEC_CTRL_CMD_SET_EC_DEPTH, ec_depth);
    aec_ctrl(aec, AEC_CTRL_CMD_SET_MIC_GAIN, env_h->env_cfg.env_aec_cfg.aec_mic_gain);
		aec_ctrl(aec, AEC_CTRL_CMD_SET_FLAGS, 0x0c);
		aec_ctrl(aec, AEC_CTRL_CMD_SET_DECAY_TIME, 110);

        decay_time = env_h->env_cfg.env_aec_cfg.aec_decay_time;
        if(decay_time > 4 && decay_time != 0xFF)
        {
            aec_ctrl(aec, AEC_CTRL_CMD_SET_DECAY_TIME, decay_time);
        }
	app_aec_dac_agc.status = AEC_AGC_INIT;
        aec_init_flag = 1;
    }
}

void app_aec_uninit(void)
{
    if(aec_init_flag == 1)
    {
        if(NULL != aec_rx_buf)
        {
            #if (AEC_MULTIPLEX_SBC_MEM == 0)
            jfree(aec_rx_buf);
            #endif
            aec_rx_buf = NULL;
        }

        if(NULL != aec_tx_buf)
        {
            #if (AEC_MULTIPLEX_SBC_MEM == 0)
            jfree(aec_tx_buf);
            #endif
            aec_tx_buf = NULL;
        }

        if(NULL != aec)
        {
            #if (AEC_MULTIPLEX_SBC_MEM == 0)
            jfree(aec);
            #endif
            aec = NULL;
        }

        aec_init_flag = 0;
    }
}

int app_aec_get_rx_size(void)
{
    return ECHO_RX_BUFFER_SIZE - rb_get_buffer_size(&aec_rx_rb);
}

int app_aec_get_tx_size(void)
{
    return ECHO_TX_BUFFER_SIZE - rb_get_buffer_size(&aec_tx_rb);
}
#define  MAX_PCM_VALUE	 24000
CONST int16_t dac2mic_coef[48]={
		 167	,	 -243	 ,	  1241	  ,    -324    ,   -3492	 ,	 -486	 ,	  2444	  ,    3629 	,	 356,
		-2505	,	 -3241	 ,	   -391    ,	2821   ,	 2338	 ,	   167	  ,   -2363   ,    -2100	,	   98,
		1970	,	 1843	,	   -15	  ,   -1562   ,    -1464	,	 -148	  ,   1071	  ,    1051 	,	  97,
		-695	,	 -630	 ,		26	   ,	561   , 	 442	,	 -210	  ,   -562	  ,    -346 	,	 154,
		 524   ,	  423	 ,	   -79	  ,    -399   , 	-325	,	  -64	  ,    185	  , 	222 	,	  46,
		-79, -121,-32
};

void DRAM_CODE app_aec_fill_rxbuff(uint8 *buff, uint8 fid, uint32 len)
{
	int32_t  i;
	int16_t* pcm = (int16_t*)buff;
	int16_t t;
    if(app_wave_playing()) return;
	switch(app_aec_dac_agc.status)
	{
		case AEC_AGC_INIT:
			app_aec_dac_agc.cnt = 0;
			app_aec_dac_agc.para = 4096;
			app_aec_dac_agc.max = 0;
			app_aec_dac_agc.status = AEC_AGC_GETTING_MAX;
			break;
		case AEC_AGC_GETTING_MAX:
			for(i = 0; i < len / 2; i++)
			{
				t=ABS(*pcm);
				if(t>app_aec_dac_agc.max)
					app_aec_dac_agc.max = t;
				if(t>app_aec_dac_agc.para)
					app_aec_dac_agc.cnt++;
				pcm++;
			}
			if(app_aec_dac_agc.cnt>1024)
			{
				if(app_aec_dac_agc.max>(32767*3/4))
					app_aec_dac_agc.decay = 32767*3/10; // 0.3
				else if(app_aec_dac_agc.max>(32767*2/4))
					app_aec_dac_agc.decay = 32767*2/4; // 0.5
				else if(app_aec_dac_agc.max>(32767*1/4))
					app_aec_dac_agc.decay = 32767*3/4; // 0.75
				else
					app_aec_dac_agc.decay = 32767; // 1
				os_printf("max:%d,decay:%d,para:%d\r\n",app_aec_dac_agc.max,app_aec_dac_agc.decay,app_aec_dac_agc.para);
				app_aec_dac_agc.status = AEC_AGC_DECAY;

			}
			break;
		case AEC_AGC_DECAY:
			for(i = 0; i < len / 2; i++)
			{
				if((app_aec_dac_agc.para*9/8)<app_aec_dac_agc.decay)
				{
					app_aec_dac_agc.para = app_aec_dac_agc.para*9/8;
					//os_printf("para:%d\r\n",app_aec_dac_agc.para);
				}
				else
				{
					app_aec_dac_agc.status = AEC_AGC_KEEP;
				}
				t=*pcm;
				*pcm++ = t*app_aec_dac_agc.para/32768;
			}
			break;
		case AEC_AGC_KEEP:
			default:
				for(i = 0; i < len / 2; i++)
				{
					t=*pcm;
					//if(t > MAX_PCM_VALUE)
					//{
					//	t = MAX_PCM_VALUE;
					//}
					//else if(t < -MAX_PCM_VALUE)
					//{
					//	t = -MAX_PCM_VALUE;
					//}
					*pcm++ = t*app_aec_dac_agc.para/32768;
				}
			break;
	}

    //Output limitation
    #if 0
    {
        #define  MAX_PCM_VALUE   24000
        int32_t  i;
        int16_t* pcm = (int16_t*)buff;
        for(i = 0; i < len / 2; i++)
        {
            int16_t t = *pcm;
            if(t > MAX_PCM_VALUE)
            {
                t = MAX_PCM_VALUE;
            }
            else if(t < -MAX_PCM_VALUE)
            {
                t = -MAX_PCM_VALUE;
            }
            *pcm++ = t;
        }
    }
    #endif
#if 0
    {
    	 	 	int32_t  i;
    	        int16_t* pcm = (int16_t*)buff;
    	        for(i = 0; i < len / 2; i++)
    	        {
    	        	 int16_t t = *pcm;
    	             *pcm++ = t/2;
    	        }
    }
#endif
//////////////  this code is used for train pulse resp
#if 0
    {
    	static int cnt = 0;

    	memset(buff, 0, len);

    	if(++cnt==32)
    	{
    		cnt = 0;
    		buff[0] = 0xFF;
    		buff[1] = 0x7F;
    	}
    }
#endif
    cvsd_fill_buffer((uint8 *)buff,fid,len);
#if 1
    {
	    	static int16_t delays[36] = {0};
			uint8 index_step;
			uint8 orders;
	    	if(sample_rate_flag==8000)
	    	{
				index_step = 2;
				orders = 24;
	    	}
	    	else
	    	{
		    	index_step = 1;
				orders = 36;
	    	}

			{
				int32_t  i;
				int16_t* pcm = (int16_t*)buff;
				for(i = 0; i < len / 2; i++)
				{
					int16_t t = *pcm;
					int32_t j=0;
					int32_t s = 0;
					for(j = 0; j < orders; j++)
					{
						s += dac2mic_coef[orders-1-j]*delays[j];
					}
					for(j = 1; j < orders; j++)
					{
						delays[j-1]=delays[j];
					}
					delays[j-1]=t;

					*pcm =((s>>14));
					pcm += index_step;
				}
			}


    	}
#endif
#if 0
    {
    	static int32_t coef[32]=
    	{0,-106, 209,-321, 238,-293, 293,-349,
    	258,-234, 173,-257,-8763,17510,3784,-16229,
    	5338, 863,-2091,-193,-595,-515, -86,-236,
    	-132, 330, -45,  54,  37, 18,67,  38};

    	static int16_t delays[32]={0};
    	int32_t  i;
		int16_t* pcm = (int16_t*)buff;
    	for(i = 0; i < len / 2; i++)
    	{
    		int16_t t = *pcm;
    		int32_t j=0;
    		int32_t s = 0;
    		for(j = 0; j < 32; j++)
    		{
    			s += coef[31-j]*delays[j];
    		}
    		for(j = 1; j < 32; j++)
    		{
    			delays[j-1]=delays[j];
    		}
    		delays[j-1]=t;

    		*pcm++ = (s>>15);
    	}
    }
#endif
    if(aec_init_flag) rb_fill_buffer(&aec_rx_rb, buff, len, AEC_RX_FILL);

    //Output limitation
    #if 0
    {
        #define  MAX_PCM_VALUE   4096
        int32_t  i;
        int16_t* pcm = (int16_t*)buff;
        for(i = 0; i < len / 2; i++)
        {
            int16_t t = *pcm;
            if(t > MAX_PCM_VALUE)
            {
                t = MAX_PCM_VALUE;
            }
            else if(t < -MAX_PCM_VALUE)
            {
                t = -MAX_PCM_VALUE;
            }
            *pcm++ = t;
        }
    }
    #endif

    #if(CONFIG_AUDIO_TRANSFER_DMA == 1)
  //  cvsd_fill_buffer((uint8 *)buff,fid,len);
    #else
    aud_fill_buffer((uint8 *)buff, len);
    #if 0
    if(aud_get_buffer_size() < AUDIO_BUFF_LEN - 256)
    {
        aud_open();
        aud_PAmute_oper(0);
    }
    #endif
    #endif
}

void DRAM_CODE app_aec_fill_txbuff(uint8 *buff, uint32 len)
{
    if(aec_init_flag) rb_fill_buffer(&aec_tx_rb, buff, len, AEC_TX_FILL);
}

void RAM_CODE app_aec_swi()
{
    if(aec_init_flag)
    {
        #if (CONFIG_CPU_CLK_OPTIMIZATION == 1)
        BK3000_set_clock(CPU_CLK_SEL, CPU_CLK_DIV);
        #endif

        int rx_size = app_aec_get_rx_size() / 2;
        int tx_size = app_aec_get_tx_size() / 2;

        if((rx_size >= AEC_FRAME_SAMPLES) && (tx_size >= AEC_FRAME_SAMPLES))
        {
            int16_t* rin;
            int16_t* sin;
            int16_t* out;
            uint32_t flags;

            extern AUDIO_CTRL_BLK  audio_ctrl_blk;

            aec_ctrl(aec, AEC_CTRL_CMD_GET_TEMP_BUF, (uint32_t)&rin);
            aec_ctrl(aec, AEC_CTRL_CMD_GET_FLAGS,    (uint32_t)&flags);

            sin = rin + AEC_FRAME_SAMPLES;
            out = sin + AEC_FRAME_SAMPLES;

            rb_get_buffer_with_length(&aec_rx_rb,(uint8*)rin, AEC_FRAME_SAMPLES * 2);
            rb_get_buffer_with_length(&aec_tx_rb,(uint8*)sin, AEC_FRAME_SAMPLES * 2);

            if(flags & 0x80)
            {
                int i;
                char* prin = (char*)rin;
                char* psin = (char*)sin;

                for(i = 0; i < AEC_FRAME_SAMPLES; i++)
                {
                    while(!UART_TX_WRITE_READY);
                    UART_WRITE_BYTE(*prin++);
                    while(!UART_TX_WRITE_READY);
                    UART_WRITE_BYTE(*prin++);
                    while(!UART_TX_WRITE_READY);
                    UART_WRITE_BYTE(*psin++);
                    while(!UART_TX_WRITE_READY);
                    UART_WRITE_BYTE(*psin++);
                }

                memcpy(out, sin, AEC_FRAME_SAMPLES * 2);
            }
            else
            {
            	int32_t mic_delay =0;
            	//if(sample_rate_flag==8000)
            	{
            	//	mic_delay = (int32_t)rb_get_used_size(&audio_ctrl_blk.aud_rb) / 4 - (int32_t)rb_get_used_size(&aec_rx_rb) / 2 + (int32_t)rb_get_used_size(&aec_tx_rb) / 2-20;
            	}
            	//else
            	{
            	mic_delay = (int32_t)rb_get_used_size(&audio_ctrl_blk.aud_rb) / 4 - (int32_t)rb_get_used_size(&aec_rx_rb) / 2 + (int32_t)rb_get_used_size(&aec_tx_rb) / 2 -28 ;
            	}
                if(mic_delay < 0)
                {
                    mic_delay = 0;
                }
                else if(mic_delay > AEC_MAX_MIC_DELAY)
                {
                    mic_delay = AEC_MAX_MIC_DELAY;
                }
                aec_ctrl(aec, AEC_CTRL_CMD_SET_MIC_DELAY, mic_delay);
                aec_proc(aec, rin, sin, out);
            }

            pcm_fill_buffer((uint8*)out, AEC_FRAME_SAMPLES * 2);
        }
    }
}

#if CONFIG_APP_DATA_CAPTURE
void  app_aec_set_data_capture_enable(uint8 enable) {}
uint8 app_aec_get_data_capture_mode(void) { return 0; }
#endif

#if ADJUST_AEC_DELAY
void aec_set_sync_adjused_flag(int a) {}
#endif

void app_set_aec_para(uint8 *para)
{
    INFO_PRT("set aec para(%08X, %d, %02X, %d, %d, %d, %d)\r\n", aec, (int8_t)para[0], para[1], para[2], para[3], para[4], para[5]);

    if(aec) aec_ctrl(aec, AEC_CTRL_CMD_SET_PARAMS, (uint32_t)para);
}
