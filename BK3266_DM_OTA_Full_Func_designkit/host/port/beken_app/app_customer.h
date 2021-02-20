#ifndef _APP_CUSTOMER_H_
#define _APP_CUSTOMER_H_

//-----------------------------------
#define CONFIG_CUSTOMER_ADVOID_POP_AUX_MODE 0 //DC filter for advoid pop in AUX mode,
void app_customer_ADC_DC_filter(void);

//----------------------------------------
#define CONFIG_CUSTOMER_EDGE_KEY		0//���ذ���(�ر仯ʱ���������¼�)
#if (CONFIG_CUSTOMER_EDGE_KEY == 1)
#define PIN_EDGE_KEY	21
void app_edge_key(void);
#endif

//------------------------------------------------------------------
#define CONFIG_CUSTOMER_2PHONES_HUNG_ACCETP	0              // ������TWC_HUNG&ACCETP�¼�
#if (CONFIG_CUSTOMER_2PHONES_HUNG_ACCETP == 1)
void app_set_2phones_hung_accetp(uint8 flag);
uint8 app_get_2phones_hung_accetp(void);
#endif

//--------------------------------------------------------------------
#define CONFIG_CUSTOMER_MOTOR_CONTROL	0//�������
#if (CONFIG_CUSTOMER_MOTOR_CONTROL == 1)
#define PIN_M_EN	18//php_pin 11
#define M_EN		do{gpio_config(PIN_M_EN,1);gpio_output(PIN_M_EN,1);}while(0)
#define M_OFF		do{gpio_config(PIN_M_EN,1);gpio_output(PIN_M_EN,0);}while(0)
void app_M_cnt_set(uint16 cnt);
void app_M_control(void);
#endif

//---------------------------------------------------------------------
#define CONFIG_CUSTOMER_SET_SUPERVISION_TIME 0 //set supervision timeout
//--------------------------------------------------

#define CONFIG_CUSTOMER_ENV_SAVE_VOLUME    	0   // 0Ϊ�رգ�1Ϊ������������

#define	CONFIG_CUSTOMER_BUTTON_HID_MODE    	0   // 0Ϊ�رգ�1Ϊ����ʹ��HID����ģʽ�򿪣�
#if (CONFIG_CUSTOMER_BUTTON_HID_MODE == 1)
void app_customer_hid_disconnect(void);
void app_customer_hid_switch_mode(void);
void app_customer_hid_set_cnt(uint8 file_id);
#endif

#define	CONFIG_CUSTOMER_1V2_CON_MODE    	0   // 0Ϊ�رգ�1Ϊ1TO2ģʽֻ���������ֻ���������,���Ӻ󲻱������ֻ����֣�
#if (CONFIG_CUSTOMER_1V2_CON_MODE == 1)
void app_customer_1v2_con_close(void);
void app_customer_1v2_con_set_cnt(uint8 file_id);
uint8 app_customer_1v2_con_reject(const btaddr_t *raddr);
#endif

typedef struct _app_customer_s
{
#if (CONFIG_CUSTOMER_2PHONES_HUNG_ACCETP == 1)
    uint8 phones_hung_accetp;
#endif
#if (CONFIG_CUSTOMER_BUTTON_HID_MODE == 1)
	uint8 hid_cnt;
#endif
#if (CONFIG_CUSTOMER_1V2_CON_MODE == 1)
	uint8 con_1v2_cnt;
#endif
#if (CONFIG_CUSTOMER_MOTOR_CONTROL == 1)
    uint16 motor_cnt;
#endif
	uint16 reserved;
}app_customer_t;

#endif

