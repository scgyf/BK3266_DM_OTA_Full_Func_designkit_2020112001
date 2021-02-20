/**
 **************************************************************************************
 * @file    aec.h
 * @brief   An implementation of acoustic echo cancellation with noise suppression
 *
 * @author  Aixing.Li
 *
 * (c) 2018 ~ 2019 BEKEN Corporation, Ltd. All Rights Reserved
 **************************************************************************************
 */

#ifndef __AEC_H__
#define __AEC_H__

#include "types.h"

#ifdef  __cplusplus
extern "C" {
#endif//__cplusplus

#define AEC_FRAME_SAMPLES       (64)
#define AEC_FFT_NBIT            (8)
#define AEC_FFT_SIZE            (1 << AEC_FFT_NBIT)
#define AEC_MAX_MIC_DELAY       (AEC_FFT_SIZE * 10)

enum AEC_CTRL_CMD
{
    AEC_CTRL_CMD_NULL = 0,
    AEC_CTRL_CMD_GET_MIC_DELAY,
    AEC_CTRL_CMD_SET_MIC_DELAY,
    AEC_CTRL_CMD_GET_EC_DEPTH,
    AEC_CTRL_CMD_SET_EC_DEPTH,
    AEC_CTRL_CMD_GET_FLAGS,
    AEC_CTRL_CMD_SET_FLAGS,
    AEC_CTRL_CMD_SET_PARAMS,
    AEC_CTRL_CMD_GET_RX_BUF,
    AEC_CTRL_CMD_GET_TX_BUF,
    AEC_CTRL_CMD_GET_OUT_BUF,
    AEC_CTRL_CMD_GET_TEMP_BUF,
    AEC_CTRL_CMD_GET_NS_DEPTH,
    AEC_CTRL_CMD_SET_NS_DEPTH,
    AEC_CTRL_CMD_GET_DECAY_TIME,
    AEC_CTRL_CMD_SET_DECAY_TIME,
	AEC_CTRL_CMD_GET_MIC_GAIN,
    AEC_CTRL_CMD_SET_MIC_GAIN,
};

typedef struct _AECContext  AECContext;

uint32_t aec_size(uint32_t delay/*unit in samples*/);
uint32_t aec_version(void);
uint8_t* aec_verstr(void);

void aec_init(AECContext* aec);
void aec_ctrl(AECContext* aec, uint32_t cmd, uint32_t arg);
void aec_proc(AECContext* aec, int16_t rin[AEC_FRAME_SAMPLES], int16_t sin[AEC_FRAME_SAMPLES], int16_t out[AEC_FRAME_SAMPLES]);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//__AEC_H__
