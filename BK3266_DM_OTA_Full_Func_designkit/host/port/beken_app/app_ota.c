#include "config.h"
#include "app_ota.h"
#include "app_beken_includes.h"
#include "lmp_utils.h"
#include "le_connection.h"
#if(PRH_BS_CFG_SYS_LE_GATT_INCLUDED==1)
#include "le_att.h"
#include "le_gatt_server.h"
#endif
#if(PRH_BS_CFG_SYS_LE_GAP_INCLUDED==1)
#include "le_gap.h"
#include "le_gap_const.h"
#endif
#include "le_config.h"
#if(BEKEN_OTA_1ST_HALF_ONLY==1)
#include "bootloader.h"
#endif

#ifdef BEKEN_OTA
#define HI_UINT16(a)             (((a) >> 8) & 0xFF)
#define LO_UINT16(a)             ((a) & 0xFF)

#define OTA_VID                  0x1000
#define OTA_PID                  0x2000
#if(BEKEN_OTA_1ST_HALF_ONLY==1)
#define OTA_VID_PICTURE          0x1000
#define OTA_PID_PICTURE          0x3000
#endif

#define OTA_BUFFER_SIZE          1000
#define OTA_PKT_ADDR_LEN         4
#define OTA_ADDR_OFFSET          0x20

typedef enum
{
    INQUIRY_INFO_REQ_CMD       = 0x01,
    INQUIRY_INFO_RESP_CMD      = 0x02,
    START_REQ_CMD              = 0x03,
    START_RESP_CMD             = 0x04,
    DATA_SEND_CMD              = 0x05,
    DATA_ERROR_CMD             = 0x06,
    END_REQ_CMD                = 0x07,
    END_RESP_CMD               = 0x08,
    UPDATE_SIZE_REQ_CMD        = 0x09,
    UPDATE_SIZE_RESP_CMD       = 0x0A,
    REBOOT_CMD                 = 0x0B
}__PACKED_POST__ app_ota_cmd_s;

typedef enum
{
    OTA_SUCCESS                = 0x00,
    OTA_FAIL                   = 0x01
}__PACKED_POST__ app_ota_result_s;

typedef enum
{
    OTA_LOCATION_A             = 0x01,
    OTA_LOCATION_B             = 0x02
}__PACKED_POST__ app_ota_location_s;

typedef struct
{
    uint32 len1;
    uint32 len2;
    uint16 crc1;
    uint16 crc2;
    uint16 vid;
    uint16 pid;
    uint16 ver;
    uint8 reserved[14];
}__PACKED_POST__ app_ota_head_s;

typedef struct
{
    uint8 cmd;
    uint8 frame_seq;
    uint16 length;
    uint8 data[0];
}__PACKED_POST__ app_ota_pkt_s;

typedef struct
{
    uint8 update_flag;
    uint8 flash_protect_flag;
    uint8 tx_arqn_nak_flag;
    uint16 crc;
    uint32 flash_addr;
    uint32 flash_offset; 
    uint32 data_addr;
    uint8 data[OTA_BUFFER_SIZE];
    uint16 data_len;
    uint8 frame_seq;
}__PACKED_POST__ app_ota_param_s;

#ifdef BEKEN_OTA_BLE
/* OTA attribute handle */
#define OTA_BLE_RX_HANDLE	              0x1002
#define OTA_BLE_TX_HANDLE	              0x1004

/* OTA 16bit UUID */
#define OTA_SERVICE_UUID                  0xFFC0
#define OTA_RX_UUID                       0xFFC1
#define OTA_TX_UUID                       0xFFC2

/* OTA 128bit UUID, TI Base 128-bit UUID format: F000XXXX-0451-4000-B000-000000000000 */
#define TI_BASE_UUID_128( uuid )  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB0,0x00,0x40,0x51,0x04,LO_UINT16(uuid),HI_UINT16(uuid),0x00,0xF0}
static uint8 ota_service_uuid[16] = TI_BASE_UUID_128(OTA_SERVICE_UUID);
static uint8 ota_rx_uuid[16]      = TI_BASE_UUID_128(OTA_RX_UUID);
static uint8 ota_tx_uuid[16]      = TI_BASE_UUID_128(OTA_TX_UUID);

/* OTA Characteristic Value */
static uint8 ota_rx_value[530];
static uint8 ota_tx_value[50];

/* OTA Characteristic Config */
static uint8 ota_tx_config[2] = {0x00, 0x00};
#endif

#ifdef BEKEN_OTA_SPP
static uint8 ota_spp_buff[OTA_BUFFER_SIZE] = {0};
static uint16 ota_spp_buff_cnt = 0;
#endif

static app_ota_param_s app_ota_param;

extern unsigned char spp_is_connected(void);
extern result_t spp_send( char *buff, uint8_t len );
extern u_int16 get_software_version(void);
extern u_int16 get_software_mark(u_int16 mark);
extern void set_flash_protect(uint8 all);

uint8 app_ota_is_ongoing(void)
{
    return app_ota_param.update_flag; 
}

uint8 app_ota_tx_arqn_nak_flag_get(void)
{
    return app_ota_param.tx_arqn_nak_flag;
}

void app_ota_tx_arqn_nak_flag_set(uint8 value)
{
    app_ota_param.tx_arqn_nak_flag = value;
}

uint16 gen_crc16(uint16 crc, uint8* data, uint32 len) 
{        
    uint32 i;
    for (i = 0; i < len; i++) 
    {        
         crc = ((crc >> 8) | (crc << 8)) & 0xFFFF;   
         crc ^= (data[i] & 0xFF);// byte to int, trunc sign    
         crc ^= ((crc & 0xFF) >> 4);      
         crc ^= (crc << 12) & 0xFFFF;   
         crc ^= ((crc & 0xFF) << 5) & 0xFFFF;   
    }       
    return (crc & 0xFFFF);
}

uint16 app_ota_calc_crc(void)
{
    uint8 data[500];
    uint16 crc = 0xFFFF;
    uint16 len = 0;
    uint32 read_addr = app_ota_param.flash_addr;
    uint32 end_addr = app_ota_param.flash_addr + app_ota_param.flash_offset;

    while(read_addr < end_addr)
    {
        if((read_addr + sizeof(data)/sizeof(data[0])) <= end_addr)
            len = sizeof(data)/sizeof(data[0]);
        else
            len = end_addr - read_addr;
        
        flash_read_data(data, read_addr, len);
        crc = gen_crc16(crc, data, len);
        read_addr += len; 
    }
    return crc;
}

#if(BEKEN_OTA_1ST_HALF_ONLY==0)
void app_ota_erase_flash(void)
{
    uint32 start_addr = 0;
    uint32 end_addr = 0;
    uint32 addr = 0;

    os_printf("| Device version: 0x%x |\r\n", get_software_version());
    if((OTA_A_MARK == get_software_mark(OTA_A_MARK)) && (0xFFFF  != get_software_mark(OTA_B_MARK)))
    {
        start_addr = OTA_B_ADDR;
        end_addr   = OTA_END_ADDR - 0x1000;  /*4K calibration data*/
    }
    else if((OTA_B_MARK == get_software_mark(OTA_B_MARK)) && (0xFFFF != get_software_mark(OTA_A_MARK)))
    {
        start_addr = OTA_A_ADDR;
        end_addr   = OTA_B_ADDR;
    }    

    if(end_addr > start_addr)
    {
        os_printf("---OTA erase flash addr:0x%x, Please Waiting...\r\n\r\n", start_addr); 
        for(addr = start_addr; addr < end_addr; )
        {
            if(((addr % 0x10000) == 0) && ((addr + 0x10000) < end_addr))
            {
                flash_erase_block_64K(addr);
                addr += 0x10000;
            }
            else if(((addr % 0x8000) == 0) && ((addr + 0x8000) < end_addr))
            {
                flash_erase_block_32K(addr);
                addr += 0x8000;
            }
            else
            {
                flash_erase_sector(addr);
                addr += 0x1000;
            }
            CLEAR_WDT;
        }
    }
}
#endif
void app_ota_write_flash(void)
{
#ifdef BEKEN_OTA_BLE
    extern u_int8 le_mode;
    if(LEconnection_LE_Connected() && le_mode)
        return;
#endif

    if(app_ota_param.flash_protect_flag == 0x01)         //flash write unprotect
    {
        set_flash_protect(0);
        app_ota_param.flash_protect_flag = 0;
    }
    else if(app_ota_param.flash_protect_flag == 0x02)    //flash write protect
    {
        set_flash_protect(1);
        app_ota_param.flash_protect_flag = 0;
    }

    if(app_ota_is_ongoing() && app_ota_param.data_len)
    {
        flash_write_data(app_ota_param.data, app_ota_param.flash_addr + app_ota_param.flash_offset, app_ota_param.data_len);
        app_ota_param.flash_offset += app_ota_param.data_len;
        app_ota_param.data_len = 0;
    }
}

void app_ota_pdu_send(uint8 *pValue, uint16 length)
{
#ifdef BEKEN_OTA_SPP
    if(spp_is_connected())
    {
        spp_send((char*)pValue, length);
    }
    else
#endif
#ifdef BEKEN_OTA_BLE
    if(LEconnection_LE_Connected())
    {
        GATTserver_Characteristic_Write_Local_Value(OTA_BLE_TX_HANDLE, length, pValue);
    }
    else
#endif
    {
        os_printf("app_ota_pdu_send error!!!\r\n");
    }
}

void app_ota_pkt_encode(uint8 cmd, uint8 frame_seq, uint8 *pValue, uint16 length)
{
    uint8 data[30];
    app_ota_pkt_s* app_ota_pkt = (app_ota_pkt_s*)data;

    if((length + sizeof(app_ota_pkt_s)) > sizeof(data)/sizeof(data[0]))
    {
        os_printf("app_ota_pkt_encode error!!!:%x, %x\r\n", length + sizeof(app_ota_pkt_s), sizeof(data)/sizeof(data[0]));
        return;
    }
    
    app_ota_pkt->cmd = cmd;
    app_ota_pkt->frame_seq = frame_seq;
    app_ota_pkt->length = length;
    memcpy(&app_ota_pkt->data, pValue, length);
    
    app_ota_pdu_send(data, length + sizeof(app_ota_pkt_s));
}

void app_ota_inquiry_req_handler(uint8 *pValue, uint16 length)
{
    app_ota_pkt_s* app_ota_pkt = (app_ota_pkt_s*)pValue;
    uint8 data[7];
    uint8 location;
    uint16 version = get_software_version();

    os_printf("app_ota_inquiry_req_handler\r\n");

    memset((uint8*)&app_ota_param, 0, sizeof(app_ota_param_s));
	
    #if(BEKEN_OTA_1ST_HALF_ONLY==1)
	location = OTA_LOCATION_A;
    app_ota_param.flash_addr = OTA_B_ADDR;
	#else
    if(OTA_A_MARK == get_software_mark(OTA_A_MARK))
    {
        location = OTA_LOCATION_A;
        app_ota_param.flash_addr = OTA_B_ADDR;
    }
    else
    {
        location = OTA_LOCATION_B;
        app_ota_param.flash_addr = OTA_A_ADDR;
    }
	#endif
	
    data[0] = LO_UINT16(OTA_VID);
    data[1] = HI_UINT16(OTA_VID);
    data[2] = LO_UINT16(OTA_PID);
    data[3] = HI_UINT16(OTA_PID);
    data[4] = LO_UINT16(version);
    data[5] = HI_UINT16(version);
    data[6] = location;

    app_ota_pkt_encode(INQUIRY_INFO_RESP_CMD, app_ota_pkt->frame_seq, data, sizeof(data)/sizeof(data[0]));
}

#if(BEKEN_OTA_1ST_HALF_ONLY==1)
static uint8 picture_flag=0;
#endif
void app_ota_start_req_handler(uint8 *pValue, uint16 length)
{
    app_ota_pkt_s* app_ota_pkt = (app_ota_pkt_s*)pValue;
    app_ota_head_s* head_info = (app_ota_head_s*)app_ota_pkt->data;
    uint16 local_ver = get_software_version();
    uint16 data_size = sizeof(app_ota_param.data)/sizeof(app_ota_param.data[0]) - sizeof(app_ota_pkt_s) - OTA_PKT_ADDR_LEN;
    uint8 data[11];
    
    os_printf("app_ota_start_req_handler\r\n");
    os_printf("len1:0x%x, len2:0x%x, crc1:0x%x, crc2:0x%x\r\n", head_info->len1, head_info->len2, head_info->crc1, head_info->crc2);
    os_printf("[VID:PID:version]: local[0x%x:0x%x:0x%x], update[0x%x:0x%x:0x%x]\r\n", OTA_VID, OTA_PID, local_ver, head_info->vid, head_info->pid, head_info->ver);

    memset(data, 0, sizeof(data)/sizeof(data[0]));
	#if(BEKEN_OTA_1ST_HALF_ONLY==1)
    if(((OTA_VID == head_info->vid) && (OTA_PID == head_info->pid))
		||((OTA_VID_PICTURE == head_info->vid) && (OTA_PID_PICTURE == head_info->pid)))
	#else
	if((OTA_VID == head_info->vid) && (OTA_PID == head_info->pid) /*&& (head_info->ver > local_ver)*/)
	#endif
    {
        uint32 addr = 0;
        uint32 len = 0;
        
#ifdef BEKEN_OTA_BLE
        if(LEconnection_LE_Connected())
        {
            data_size = Gatt_Get_MTU_Size() - sizeof(app_ota_pkt_s) - OTA_PKT_ADDR_LEN - 3;   /* 3 = opcode(1 Byte) + Attribute handle(2 Byte) */       
            if(bt_flag1_is_set(APP_FLAG_MUSIC_PLAY) && (data_size > 300))
                data_size = 300;                                                              /* reduce OTA speed while BT music playing in BLE mode, size 300 is safe */                                                      
        }
#endif
		#if(BEKEN_OTA_1ST_HALF_ONLY==1)
		addr = OTA_ADDR_OFFSET + head_info->len1;
        len = head_info->len2;
        app_ota_param.crc = head_info->crc2;
		app_erase_picture();
		if((OTA_VID_PICTURE == head_info->vid) && (OTA_PID_PICTURE == head_info->pid))
		{
			picture_flag=1;
			os_printf("device running on A, update picture to B...\r\n");
		}
		else
		{
			picture_flag=0;
			os_printf("device running on A, update to B...\r\n");
		}
		#else
        if(OTA_B_ADDR == app_ota_param.flash_addr)
        {
            addr = OTA_ADDR_OFFSET + head_info->len1;
            len = head_info->len2;
            app_ota_param.crc = head_info->crc2;
            os_printf("device running on A, update to B...\r\n");
        }
        else
        {
            addr = OTA_ADDR_OFFSET;
            len = head_info->len1;
            app_ota_param.crc = head_info->crc1;
            os_printf("device running on B, update to A...\r\n");
        }
        #endif
		
        app_ota_param.data_addr = addr;
        app_ota_param.frame_seq = app_ota_pkt->frame_seq;
        app_ota_param.update_flag = 1;
        app_ota_param.flash_protect_flag = 0x01;         //flash write unprotect

        data[0] = OTA_SUCCESS;
        memcpy(&data[1], (uint8*)&addr, 4);
        memcpy(&data[5], (uint8*)&len, 4);
        memcpy(&data[9], (uint8*)&data_size, 2);
        
        app_bt_write_sniff_link_policy(bt_sniff_get_handle_from_idx(0), 0);  //exit bt sniff mode
    }
    else
    {
        data[0] = OTA_FAIL;
        os_printf("app_ota_start_FAIL!!!\r\n");
    }
    app_ota_pkt_encode(START_RESP_CMD, app_ota_pkt->frame_seq, data, sizeof(data)/sizeof(data[0]));
}

void app_ota_data_send_handler(uint8 *pValue, uint16 length)
{
    app_ota_pkt_s* app_ota_pkt = (app_ota_pkt_s*)pValue;
    uint32 addr = LMutils_Get_Uint32(app_ota_pkt->data);
    uint8* data_ptr = app_ota_pkt->data + sizeof(app_ota_pkt_s);
    uint16 data_len = app_ota_pkt->length - OTA_PKT_ADDR_LEN;
        
    if(((uint8)(app_ota_param.frame_seq + 1) == app_ota_pkt->frame_seq) && (app_ota_param.data_addr == addr))
    {
        if((app_ota_param.data_len + data_len) > (sizeof(app_ota_param.data)/sizeof(app_ota_param.data[0])))
        {
            while(app_ota_param.data_len)
            {
                app_ota_write_flash();
                os_printf("app_ota_data overflow!!!\r\n");
            }
        }
        memcpy(app_ota_param.data + app_ota_param.data_len, data_ptr, data_len);
        app_ota_param.data_len += data_len;
        app_ota_param.frame_seq++;
        app_ota_param.data_addr += data_len;
    }
    else
    {
        app_ota_pkt_encode(DATA_ERROR_CMD, app_ota_param.frame_seq, (uint8*)&app_ota_param.data_addr, sizeof(app_ota_param.data_addr));
        os_printf("app_ota_data_error:%x,%x\r\n", app_ota_param.frame_seq, app_ota_param.data_addr);
    }
}

void app_ota_end_req_handler(uint8 *pValue, uint16 length)
{
    app_ota_pkt_s* app_ota_pkt = (app_ota_pkt_s*)pValue;
    uint8 data[1];
    uint16 crc;
    uint16 section_A = 0xFFFF;
    uint16 section_B = 0xFFFF;

    os_printf("app_ota_end_req_handler\r\n");
	#if(BEKEN_OTA_1ST_HALF_ONLY==1)
	ota_info_s ota_info_write;   
	#endif
	
    while(app_ota_param.data_len)
    {
        app_ota_write_flash();         //ensure last data write to flash
    }
    
    crc = app_ota_calc_crc();
    
    os_printf("crc: 0x%x, 0x%x\r\n", crc, app_ota_param.crc);
    if(crc == app_ota_param.crc)
    {
    	#if(BEKEN_OTA_1ST_HALF_ONLY==1)
		if(picture_flag)
		{
			section_A = 0xFFFF;
        	section_B = OTA_B_PICTURE_MARK;
			os_printf("OTA_PICTURN_WRIET_OK!!!\r\n");
		}
		else
		{
			section_A = 0x0;
        	section_B = OTA_B_MARK;
			os_printf("OTA_BIN_SUCCESS!!!\r\n");
		}
		data[0] = OTA_SUCCESS;
		#else
        if(OTA_B_ADDR == app_ota_param.flash_addr)
        {
            section_A = 0x0;
            section_B = OTA_B_MARK;     
        }
        else
        {
            section_A = OTA_A_MARK;
            section_B = 0x0;
        }
		data[0] = OTA_SUCCESS;
        os_printf("OTA_SUCCESS!!!\r\n");
		#endif
    }
    else
    {
    	#if(BEKEN_OTA_1ST_HALF_ONLY==1)
		section_B = 0xFF00;
		#else
        if(OTA_B_ADDR == app_ota_param.flash_addr)
        {
            section_B = 0xFF00;     
        }
        else
        {
            section_A = 0xFF00;
        }
		#endif
        data[0] = OTA_FAIL;
        os_printf("OTA_FAIL!!!\r\n");
    }
    flash_write_data((uint8*)&section_A, OTA_A_ADDR + OTA_MARK_OFFSET, sizeof(section_A));     
    flash_write_data((uint8*)&section_B, OTA_B_ADDR + OTA_MARK_OFFSET, sizeof(section_B));

	#if(BEKEN_OTA_1ST_HALF_ONLY==1)
	if((app_ota_param.flash_offset<(OTA_END_ADDR-0x1000-0x10))&&(data[0] == OTA_SUCCESS)&&(picture_flag==0))
	{
		ota_info_write.flag = 0x5555;
		ota_info_write.len=  app_ota_param.flash_offset;
		ota_info_write.crc= app_ota_calc_crc();
    	flash_write_data((uint8*)&ota_info_write, OTA_END_ADDR-0x1000-0x10, sizeof(ota_info_s)); 
		//os_printf("WRITE OTA INFO(flag=0x%04x,len=0x%08x,crc=0x%04x)\r\n",ota_info_write.flag,ota_info_write.len,ota_info_write.crc);
		os_printf("**********************************************\r\n");
		os_printf("Please wait for a while!!!\r\n");
		os_printf("Do not cut off the power!!!\r\n");
		os_printf("**********************************************\r\n");
	} 
	#endif
    app_ota_param.flash_protect_flag = 0x02;        //flash write protcet
    app_ota_pkt_encode(END_RESP_CMD, app_ota_pkt->frame_seq, data, sizeof(data)/sizeof(data[0]));
}

void app_ota_update_size_req(uint16 size)
{
    uint16 max_size = sizeof(app_ota_param.data)/sizeof(app_ota_param.data[0]) - sizeof(app_ota_pkt_s) - OTA_PKT_ADDR_LEN;

    os_printf("app_ota_update_size_req:%x\r\n",size);
    
    if(size < max_size)
        app_ota_pkt_encode(UPDATE_SIZE_REQ_CMD, 0xFF, (uint8*)&size, sizeof(uint16));
    else
        os_printf("app_ota_update_size error:%x,%x\r\n", size, max_size);
}

void app_ota_update_size_resp_handler(uint8 *pValue, uint16 length)
{
    app_ota_pkt_s* app_ota_pkt = (app_ota_pkt_s*)pValue;
    
    if(app_ota_pkt->frame_seq == 0xFF)
        os_printf("app_ota_update_size_resp_handler\r\n");
}

void app_ota_reboot_handler(uint8 *pValue, uint16 length)
{
    os_printf("app_ota_reboot_handler\r\n\r\n");
    memset((uint8*)&app_ota_param, 0, sizeof(app_ota_param_s));
    BK3000_wdt_reset();
}

void app_ota_pkt_decode(uint8 *pValue, uint16 length)
{
    switch(pValue[0])
    {
        case INQUIRY_INFO_REQ_CMD:
            app_ota_inquiry_req_handler(pValue, length);
            break;
            
        case START_REQ_CMD:
            app_ota_start_req_handler(pValue, length);
            break; 
            
        case DATA_SEND_CMD:
            app_ota_data_send_handler(pValue, length);
            break;
            
        case END_REQ_CMD:
            app_ota_end_req_handler(pValue, length);
            break;
            
        case UPDATE_SIZE_RESP_CMD:
            app_ota_update_size_resp_handler(pValue, length);
            break;
            
        case REBOOT_CMD:
            app_ota_reboot_handler(pValue, length);
            break;

        default:
            os_printf("app_ota_pkt_decode error!!!\r\n");
            break;
    }
}

#ifdef BEKEN_OTA_BLE
u_int16 App_Setup_OAD_GATT_DB(void)
{
    u_int16 handle = 0x1000;

    // OTA Service
    _GATTserver_Add_Service(PRIMARY_SERVICE_128BIT, handle, ota_service_uuid, OTA_SERVICE_UUID);
    handle++;

    // OTA RX Characteristic Declaration
    _GATTserver_Add_16ByteUUID_Characteristic_Declaration(handle, ota_rx_uuid, GATT_PROPERTIES_WRITE_WITHOUT_RESPONSE);
    handle++;

    // OTA RX Characteristic Value
    _GATTserver_Add_16ByteUUID_Characteristic_Value(handle, ota_rx_uuid, USE_LOCAL_NOTIFY, GATT_PERMISSION_WRITE, sizeof(ota_rx_value)/sizeof(ota_rx_value[0]), ota_rx_value);
    handle++;

    // OTA TX Characteristic Declaration
    _GATTserver_Add_16ByteUUID_Characteristic_Declaration(handle, ota_tx_uuid, GATT_PROPERTIES_NOTIFY);
    handle++;

    // OTA TX Characteristic Value
    _GATTserver_Add_16ByteUUID_Characteristic_Value(handle, ota_tx_uuid, USE_LOCAL_NOTIFY, GATT_PERMISSION_WRITE, sizeof(ota_tx_value)/sizeof(ota_tx_value[0]), ota_tx_value);
    handle++;

    // OTA TX Characteristic Configuration
    _GATTserver_Add_Char_Descriptor(handle, CLIENT_CHARACTERISTIC_CONFIGURATION, GATT_PERMISSION_READ|GATT_PERMISSION_WRITE, sizeof(ota_tx_config)/sizeof(ota_tx_config[0]), ota_tx_config);
    handle++;

    return 0;
}

void app_ota_ble_pkt_decode(uint16 handle, uint8 *pValue, uint16_t length)
{
    if(handle == OTA_BLE_RX_HANDLE)
    {
        app_ota_pkt_decode(pValue, length);
    }
}
#endif

#ifdef BEKEN_OTA_SPP
void app_ota_spp_pkt_reframe(uint8 *pValue, uint16 length)
{
    uint16 copy_len = 0;
    uint16 pkt_len = 0;
    
    do
    {
        if((ota_spp_buff_cnt + length) <= sizeof(ota_spp_buff)/sizeof(ota_spp_buff[0]))
            copy_len = length;
        else
            copy_len = sizeof(ota_spp_buff)/sizeof(ota_spp_buff[0]) - ota_spp_buff_cnt;
        
        memcpy(&ota_spp_buff[ota_spp_buff_cnt], pValue, copy_len);
        ota_spp_buff_cnt += copy_len;
        pValue += copy_len;
        length -= copy_len;

        while(ota_spp_buff_cnt >= sizeof(app_ota_pkt_s))
        {
            memcpy((uint8*)&pkt_len, &ota_spp_buff[2], 2);
            pkt_len += sizeof(app_ota_pkt_s);
            if(pkt_len <= ota_spp_buff_cnt)
            {
                app_ota_pkt_decode(ota_spp_buff, pkt_len);
                memcpy(ota_spp_buff, &ota_spp_buff[pkt_len], ota_spp_buff_cnt - pkt_len);
                ota_spp_buff_cnt -= pkt_len;
            }
            else
            {
                break;
            }
        }
    }while(length);
}
#endif

#else
uint8 app_ota_is_ongoing(void)
{
    return 0; 
}

uint8 app_ota_tx_arqn_nak_flag_get(void)
{
    return 0;
}

void app_ota_tx_arqn_nak_flag_set(uint8 value)
{
}

#endif
