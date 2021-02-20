#include "driver_beken_includes.h"
#include "app_beken_includes.h"
#include "data_message.h"

#ifdef CONFIG_DRIVER_I2S

#define GPIO_2F_I2S_SYNC_PIN          18
#define GPIO_2F_I2S_CLK_PIN           19
#define GPIO_2F_I2S_DIN_PIN           20
#define GPIO_2F_I2S_DOUT_PIN          21

#define GPIO_2F_I2S_SYNC_CONFIG       BK3000_GPIO_18_CONFIG
#define GPIO_2F_I2S_CLK_CONFIG        BK3000_GPIO_19_CONFIG
#define GPIO_2F_I2S_DIN_CONFIG        BK3000_GPIO_20_CONFIG
#define GPIO_2F_I2S_DOUT_CONFIG       BK3000_GPIO_21_CONFIG

#define BK3000_GPIO_FUNCTION_MODE_1   BK3000_GPIO_GPIOCON
#define BK3000_GPIO_FUNCTION_MODE_2   BK3000_AB_CONFIG
#define BK3000_GPIO_FUNCTION_MODE_3   BK3000_GPIO_DPLL_UNLOCK
#define BK3000_GPIO_FUNCTION_MODE_4   BK3000_GPIO_ANABUCKFERQ

#define NUMBER_ROUND_UP(a,b)        ((a) / (b) + (((a) % (b)) ? 1 : 0))

volatile i2s_message i2s_msg;

void GPIO_I2S_function_enable(unsigned char ucChannel)
{
    GPIO_2F_I2S_CLK_CONFIG  = 0x48;
    GPIO_2F_I2S_SYNC_CONFIG = 0x48;
    GPIO_2F_I2S_DIN_CONFIG  = 0x48;
    GPIO_2F_I2S_DOUT_CONFIG = 0x48;
    
    BK3000_GPIO_FUNCTION_MODE_1 &= (~((1<<GPIO_2F_I2S_SYNC_PIN)
                          | (1<<GPIO_2F_I2S_CLK_PIN)
                          | (1<<GPIO_2F_I2S_DIN_PIN)
                          | (1<<GPIO_2F_I2S_DOUT_PIN)));
    BK3000_GPIO_FUNCTION_MODE_2 |= ((1<<GPIO_2F_I2S_SYNC_PIN)
                          | (1<<GPIO_2F_I2S_CLK_PIN)
                          | (1<<GPIO_2F_I2S_DIN_PIN)
                          | (1<<GPIO_2F_I2S_DOUT_PIN));
    BK3000_GPIO_FUNCTION_MODE_3 &= (~((1<<GPIO_2F_I2S_SYNC_PIN)
                          | (1<<GPIO_2F_I2S_CLK_PIN)
                          | (1<<GPIO_2F_I2S_DIN_PIN)
                          | (1<<GPIO_2F_I2S_DOUT_PIN)));
    BK3000_GPIO_FUNCTION_MODE_4 &= (~((1<<GPIO_2F_I2S_SYNC_PIN)
                          | (1<<GPIO_2F_I2S_CLK_PIN)
                          | (1<<GPIO_2F_I2S_DIN_PIN)
                          | (1<<GPIO_2F_I2S_DOUT_PIN)));
}

void audio_pll_set(unsigned long ulfreq)
{
    uint32 tmp;
    if (ulfreq == 48000000)            // 48MHz
    {
    	tmp =  0x3B13B13B;
    }
    else if (ulfreq == 48128000)       // 48.128MHz
    {
    	tmp = 0x3B3C05AC;
    }
    else if (ulfreq == 48384000)       // 48.384MHz
    {
    	tmp = 0x3B8CAE8E;
    }
    else if (ulfreq == 49152000)       // 49.152MHz
    {
    	tmp = 0x3C7EA932;
    }
    else if (ulfreq == 49392000)       // 49.392MHz
    {
    	tmp = 0x3CCA4785;
    }
    else if (ulfreq == 50688000)       // 50.688MHz
    {
    	tmp = 0x3E629E7C;
    }
    else if (ulfreq == 50803200)       // 50.8032MHz
    {
    	tmp = 0x3E86EA7A;
    }
    else
    {
    	tmp = 0x3B13B13B;
    }
    //DPLL enable 
    BK3000_A0_CONFIG &= ~(1<<0);
    
    BK3000_XVR_REG_0x0F = XVR_analog_reg_save[15] = tmp;

	BK3000_XVR_REG_0x0E = XVR_analog_reg_save[14] =  0xA0800008;
	/* spi triggle as DPLL triggle*/
	BK3000_XVR_REG_0x0E = XVR_analog_reg_save[14] = XVR_analog_reg_save[14] & (~(1<<18));
	Delay(50);
	BK3000_XVR_REG_0x0E = XVR_analog_reg_save[14] = XVR_analog_reg_save[14] | ( (1<<18));
	Delay(50);
	BK3000_XVR_REG_0x0E = XVR_analog_reg_save[14] = XVR_analog_reg_save[14] & (~(1<<18));
	Delay(50);
}

void i2s_init(unsigned long smp_ratio, unsigned char role, unsigned char data_width, unsigned char mode_sel)
{
	unsigned long bitclk_div;
	unsigned long sys_clk;
	unsigned long lrck_div;

    if (smp_ratio != 8000 && smp_ratio != 16000 && smp_ratio != 44100 && smp_ratio != 48000)
    {
        return;
    }

    BK3000_PMU_PERI_PWDS &= ~bit_PMU_I2S_PWD;
    
    GPIO_I2S_function_enable(0);

    if (data_width == 8)
    {
        lrck_div = 7;
    }
    else if (data_width == 16)
    {
        lrck_div = 15;
    }
    else if (data_width == 24)
    {
        lrck_div = 23;
    }
    else
    {
        lrck_div = 31;
    }

    if(smp_ratio == 8000)
	{
		if(data_width == 24)
			sys_clk = 48384000;
		else
			sys_clk = 48128000;
	}
	else if (smp_ratio == 16000)
	{
		if((data_width == 16) || (data_width == 8))
			sys_clk = 48128000;
		else
			sys_clk = 49152000;
	}
    else if (smp_ratio == 44100)
	{
		sys_clk = 50803200;
	}
    else
	{
		if(data_width == 24)
			sys_clk = 50688000;
		else
			sys_clk = 49152000;
	}

    // set i2s dpll clock
    audio_pll_set(sys_clk);

    // bitclk_div <= 4 的时候接收数据会出错，所以这个值低于5是不能用的
    bitclk_div = NUMBER_ROUND_UP((sys_clk / 2 ), (smp_ratio * 2 * (lrck_div + 1))) - 1;

    REG_I2S_CONFIG2 = (0x02UL << I2S_CONFIG2_TX_FIFO_MODE_POSI);
    REG_I2S_CONTRL = ((bitclk_div & 0x00FF) 	<< 0)
                   | ( lrck_div             	<< 8)
                   | ((data_width-1)            << 16)
                   | ((role & 0x01)         	<< 30)
                   | ((mode_sel & 0x07)     	<< 27);
	REG_I2S_CONFIG = 0x00000533;   // 10-13bit : 0000;
	REG_I2S_STATUS = REG_I2S_STATUS_MASK;

    os_printf("I2S:CONTRL = 0x%lx, CONFIG = 0x%lx, STATUS = 0x%lx, bitclk_div = 0x%lx\r\n", REG_I2S_CONTRL, REG_I2S_CONFIG, REG_I2S_STATUS, bitclk_div);

	i2s_msg.rxfifo_level = 2;
	i2s_msg.txfifo0_level = 2;
	i2s_msg.trans_done = 0;
}

void i2s_enable(void)
{
	REG_I2S_CONTRL |= I2S_CONTRL_I2S_PCM_ENABLE_MASK;
    BK3000_PMU_PERI_PWDS &= ~bit_PMU_I2S_PWD;
	SYSirq_interrupt_enable(VIC_I2S_ISR_INDEX);
}

void i2s_disable(void)
{
	REG_I2S_CONTRL &= (~I2S_CONTRL_I2S_PCM_ENABLE_MASK);
    BK3000_PMU_PERI_PWDS |= bit_PMU_I2S_PWD;
	SYSirq_interrupt_enable(VIC_I2S_ISR_INDEX);
}

void i2s_clrfifo(unsigned char fifo_idx)
{
	//[0]:rxfifo, [1]:txfifo0, [2]:txfifo1, [3]:txfifo2
 	REG_I2S_CONFIG |= fifo_idx << 16;
}

void i2s_isr(void)
{
	unsigned long		i2s_stat;
	unsigned char		rxint, txint0;
	unsigned int		i;
	volatile unsigned int data_num;

	i2s_stat = REG_I2S_STATUS;
	rxint  = i2s_stat & 0x01;
	txint0 = i2s_stat & 0x02;
	//txint1 = i2s_stat & 0x04;
	//txint2 = i2s_stat & 0x08;

    //os_printf("REG_I2S_STATUS = 0x%x\r\n", i2s_stat);
	if (txint0)
	{
		switch (i2s_msg.txfifo0_level)
		{
		    case 0	: 	data_num = 1;    break;
		    case 1	: 	data_num = 8;    break;
		    case 2	: 	data_num = 16;   break;
		    case 3	: 	data_num = 24;   break;
		    default	:  	data_num = 32;   break;
		}

		for (i = 0; i < data_num; i++)
		{
			REG_I2S_DATA0 = 0xFF;
		}
		i2s_stat |= 0x2;
	}

	if (rxint)
	{
		switch (i2s_msg.rxfifo_level)
		{
		    case 0	: 	data_num = 1;    break;
		    case 1	: 	data_num = 8;    break;
		    case 2	: 	data_num = 16;   break;
		    case 3	: 	data_num = 24;   break;
		    default	:  	data_num = 32;   break;
		}
        
		for (i = 0; i < data_num; i++)
		{
		    uint32 rx_data;
			rx_data = REG_I2S_DATA0;
			rx_data = rx_data;
		}
        i2s_stat |= 0x1;
	}
    
    if (i2s_stat & 0x10)
    {
        i2s_clrfifo(3);
        os_printf("i2s_clrfifo!\r\n");
    }

    REG_I2S_STATUS = i2s_stat;
}
#endif
