


#include "config.h"
#include "sys_types.h"

#include "hw_lc.h"
#include "hw_le_lc.h"
#include "le_connection.h"
#include "le_att.h"
#include "bt_timer.h"
#include "le_config.h"
#include "le_gatt_service_ancs.h"
#include "le_cts_app.h"
#include "LE_gatt_server.h"


u_int16 ancs_handle_cache[HDL_CACHE_LEN];
u_int16 ancs_connHandle=0x10;
u_int8 ancs_state=0;
extern t_App_Control LEapp_Config;

static u_int8 Ancs_CCCDConfig(u_int16 attrHdl, u_int8 isEnable)
{
    u_int8 status = 1;
    u_int8 val[2] = {0x01, 0x00};
    val[0] = isEnable;

    GATT_Characteristic_Value_Write(ancs_connHandle, 0x00, 0, attrHdl, 2, val, 0);
    
    return status;
}

u_int8 Ancs_subsNotifSrc(u_int16 handle)
{
  u_int8 status = 1;
  os_printf("handle=%x\n",handle);     
  status = Ancs_CCCDConfig(handle, 1);    
  
  return status;
}


void get_ancs_characteristic(t_gatt_event_params *p_gatt_event_params)
{
    u_int8 i;

   // u_int32 current_clk;// = HW_Get_Native_Clk_Avoid_Race();
    u_int8 num_entries = p_gatt_event_params->payload_length/p_gatt_event_params->att_len;
    u_int8* p_pdu = p_gatt_event_params->payload;
    u_int32 current_clk = HW_Get_Native_Clk_Avoid_Race();  
    for(i=0;i<num_entries;i++)
    {
        u_int16 attrib_uuid = p_pdu[5] + (p_pdu[6]<<8);
        u_int16 attrib_value_handle = p_pdu[3] + (p_pdu[4]<<8);
        
        os_printf("attrib_uuid=%x\n",attrib_uuid);
        switch(attrib_uuid)
        {
            case ANCS_NOTIF_SRC_CHAR_UUID:
                ancs_handle_cache[HDL_ANCS_NTF_NOTIF_START] = attrib_value_handle;
                ancs_handle_cache[HDL_ANCS_NTF_CCCD] = attrib_value_handle+1;
                if( (current_clk+ANCS_CONFIG_NOTIFY_START)>BT_CLOCK_MAX_TICKS )
                {
                    LEapp_Config.ancs_config_notify_timer=(current_clk+ANCS_CONFIG_NOTIFY_START)-BT_CLOCK_MAX_TICKS;
                }
                else
                {
                    LEapp_Config.ancs_config_notify_timer = current_clk+ANCS_CONFIG_NOTIFY_START;
                }
                
                break;
            case ANCS_CTRL_PT_CHAR_UUID:
                ancs_handle_cache[HDL_ANCS_CTRL_PT_START] = attrib_value_handle;
                break;
            case ANCS_DATA_SRC_CHAR_UUID:
                ancs_handle_cache[HDL_ANCS_DATA_SRC_START] = attrib_value_handle;
                ancs_handle_cache[HDL_ANCS_DATA_SRC_CCCD] = attrib_value_handle+1;
                
                //Ancs_subsNotifSrc();  
               /* 
                if( (current_clk+ANCS_CONFIG_DATA_START)>BT_CLOCK_MAX_TICKS )
                {
                    LEapp_Config.ancs_config_data_timer=(current_clk+ANCS_CONFIG_DATA_START)-BT_CLOCK_MAX_TICKS;
                }
                else
                {
                    LEapp_Config.ancs_config_data_timer = current_clk+ANCS_CONFIG_DATA_START;
                }
                */
                break;
            default:
            break;
        }
        p_pdu+=p_gatt_event_params->att_len;
    }
}

void get_ancs_notification(u_int8 *p_notification_params,u_int8 len)
{

    u_int16 attrib_value_handle = p_notification_params[0] + (p_notification_params[1]<<8);
    u_int8 i;
    
    os_printf("p_notification_params, len = %d\n",len);
    
    for( i=0;i<len;i++ )
    {
        os_printf("%x ",p_notification_params[i]);
    }    
    
    if(attrib_value_handle==ancs_handle_cache[HDL_ANCS_NTF_NOTIF_START])
    {
        //在此增加代码处理获取的信息  
        os_printf("HDL_ANCS_NTF_NOTIF_START\n");

    }
    else if(attrib_value_handle==ancs_handle_cache[HDL_ANCS_DATA_SRC_START])
    {
        os_printf("HDL_ANCS_DATA_SRC_START\n");
    }
    
}

void ancs_state_set(u_int8 value)
{
    ancs_state=value;    
}

u_int8 ancs_state_get(void)
{
    return ancs_state;    
}

