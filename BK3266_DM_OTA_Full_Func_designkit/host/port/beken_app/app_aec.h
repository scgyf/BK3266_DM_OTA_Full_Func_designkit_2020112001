#ifndef _APP_AEC_H
#define _APP_AEC_H

#include "types.h"

void app_aec_init(int sample_rate);
void app_aec_uninit(void);
void app_aec_fill_rxbuff(uint8_t* buf, uint8_t fid, uint32_t len);
void app_aec_fill_txbuff(uint8_t* buf, uint32_t len);
void app_aec_swi(void);

typedef struct __app_aec_cfg_s
{
   uint16  aec_mic_delay;
   int8    aec_fft_shift;
   uint8   aec_decay_time;
   int8    aec_ear_gain;
   int8    aec_mic_gain;
   int16   hfp_eq_gain;
   uint8   hfp_eq_flag0;
   app_eq_para_t hfp_eq_para[2];
} __PACKED_POST__ app_aec_cfg_t;

#if CONFIG_APP_DATA_CAPTURE
void app_aec_set_data_capture_enable(uint8 enable);
uint8 app_aec_get_data_capture_mode(void);
#endif

#if ADJUST_AEC_DELAY
void aec_set_sync_adjused_flag(int a);
#endif

void app_set_aec_para(uint8 *para);
void app_aec_set_mic_delay(int8 decay_ime);
void app_aec_call_established(uint8_t flag);
void app_aec_sco_connected(uint8_t flag);
void app_aec_aec_delay_cancel_proc(void);
void app_aec_rin_sin_ring_buffer_clear(void);

#endif
