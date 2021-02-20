#ifndef _DRIVER_BEKEN_INCLUDES_H_
#define _DRIVER_BEKEN_INCLUDES_H_

#include "types.h"
#include <config/config.h>
#include "excutil.h"
#include "board.h"
#include "spr_defs.h"
#include "bautil.h"

#include "msg_pub.h"
#include "msg.h"

#include "types.h"
#include "BK3000_reg.h"
#include "BK3000_mcu.h"
#include "driver_ringbuff.h"
#include "driver_icu.h"
#include "driver_serio.h"
#include "driver_audio.h"
#include "driver_gpio.h"
#include "driver_i2c.h"
#include "driver_spi.h"
#include "driver_sdadc.h"
#include "driver_dtmf.h"
#include "driver_saradc.h"
#include "driver_flash.h"
#include "driver_i2s.h"
#include "driver_codec.h"
#include "driver_dma_fft.h"
#include "driver_usb.h"

#ifdef CONFIG_APP_SDCARD
#include "driver_sdcard.h"
#endif

#include "driver_IrDA.h"

#include "target.h"

#include "timer.h"
#include "sys_irq.h"

/****software interrupt flag**********/
extern volatile uint32 sleep_tick;
extern volatile uint32 pwdown_tick;
extern volatile uint16 sniffmode_wakeup_dly;
extern volatile uint8 flag_sbc_buffer_play;
extern volatile uint8 usb_tf_aux_in_out_flag;//防止在关机过程中拔掉U盘、TF卡及line-in产生的问题
extern volatile uint8 player_vol_bt;
extern volatile uint8 player_vol_hfp;
extern volatile uint8 flag_power_charge;
extern volatile uint16 adcmute_cnt;

extern volatile uint32 FLASH_ENVDATA2_DEF_ADDR;
extern volatile uint32 FLASH_ENVDATA_DEF_ADDR;
extern volatile uint32 FLASH_CHANGED_BT_ADDR;
extern volatile uint32 FLASH_ENVCFG_DEF_ADDR;

#define CLEAR_SLEEP_TICK     do{sleep_tick = 0;}while(0)
#define INC_SLEEP_TICK       do{sleep_tick++;}while(0)
#define SLEEP_TICK_CHECK     1000
#define CLEAR_PWDOWN_TICK    do{pwdown_tick = 0;}while(0)
#define INC_PWDOWN_TICK(step)do{pwdown_tick += step;}while(0)
#define POWER_DOWN_CHECK     -1


#endif
