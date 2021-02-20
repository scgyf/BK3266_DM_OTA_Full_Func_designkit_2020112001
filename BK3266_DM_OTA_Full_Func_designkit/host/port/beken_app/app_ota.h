#ifndef _APP_OTA_H_
#define _APP_OTA_H_

#include "config.h"
#include "types.h"

#ifdef BEKEN_OTA
/*ota flash operation addr*/
#define OTA_A_ADDR               0x1000 
#define OTA_B_ADDR               0x100000
#define OTA_END_ADDR             0x200000

/*ota location mark*/
#define OTA_A_MARK               0x5AA5
#define OTA_B_MARK               0xA55A
#if(BEKEN_OTA_1ST_HALF_ONLY==1)
#define OTA_B_PICTURE_MARK       0xAAAA
#endif

/*ota mark&version offset*/
#define OTA_VER_OFFSET           0x100E
#define OTA_MARK_OFFSET          0x1010  

#if(BEKEN_OTA_1ST_HALF_ONLY==0)
void app_ota_erase_flash(void);
#endif
void app_ota_write_flash(void);
uint8 app_ota_is_ongoing(void);
#ifdef BEKEN_OTA_BLE
u_int16 App_Setup_OAD_GATT_DB(void);
void app_ota_ble_pkt_decode(uint16 handle, uint8 *pValue, uint16_t length);
#endif
#ifdef BEKEN_OTA_SPP
void app_ota_spp_pkt_reframe(uint8 *pValue, uint16_t length);
#endif
void app_ota_update_size_req(uint16 size);
#endif
uint8 app_ota_is_ongoing(void);
uint8 app_ota_tx_arqn_nak_flag_get(void);
void app_ota_tx_arqn_nak_flag_set(uint8 value);

#endif
