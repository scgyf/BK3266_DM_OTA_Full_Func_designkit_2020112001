#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_

#if(BEKEN_OTA_1ST_HALF_ONLY==1)
typedef struct
{
    uint16 flag;
    uint32 len;
    uint16 crc;
}__PACKED_POST__ ota_info_s;

BOOT_CODE void Boot_loader(void);
BOOT_CODE void Boot_erase_code(uint32 start_addr, uint32 end_addr);
void app_erase_flash(uint32 start_addr,uint32 end_addr);
void app_erase_2st_half_flash(void);
void app_erase_picture(void);
#if 0
BOOT_CODE int32 Boot_printf(const char *fmt, ...);
BOOT_CODE void Boot_uart_init(u_int32 baud_rate);
#endif
#endif
#endif

