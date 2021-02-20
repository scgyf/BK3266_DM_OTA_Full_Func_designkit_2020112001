/* Modifications by Jungo Ltd. Copyright (c) 2012 Jungo Ltd. All Rights reserved */

/*-
 * Copyright (c) 2006 Itronix Inc.
 * All rights reserved.
 *
 * Written by Iain Hibbert for Itronix Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of Itronix Inc. may not be used to endorse
 *    or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ITRONIX INC. ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL ITRONIX INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <jos.h>
#include <bluetooth.h>
#include <bt_sdp.h>
#include <bt_rfcomm.h>
#include <bluetooth/service/sdp_provider.h>
#include <bluetooth/service/sdp_profile.h>
#include <bluetooth/service/sdp_server.h>

#ifdef CONFIG_BLUETOOTH_SPP
static int32_t spp_profile_create_service_class_id_list(uint8_t *buf,
    uint8_t const * const eob, uint8_t const *data, uint32_t datalen)
{
    static uuid_t service_classes[] = {
        #ifdef SUPPORT_128BITS_UUID
            {{0x51, 0xDB, 0xA1, 0x09, 0x5B, 0xA9, 0x49, 0x81, 0x96, 0xB7, 0x6A, 0xFE, 0x13, 0x20, 0x93, 0xDE} , sizeof(uw_u128_t)}
        #else
            UUID_INIT16(SDP_SERVICE_CLASS_SERIAL_PORT)
        #endif
    };
    return common_profile_create_service_class_id_list(buf, eob,
        (uint8_t const *)service_classes, sizeof(service_classes));
}

static int32_t spp_profile_create_protocol_descriptor_list(uint8_t *buf,
    uint8_t const * const eob, uint8_t const *data, uint32_t datalen)
{
    provider_t const *provider = (provider_t const *)(void *)data;
    sdp_sp_profile_t *spp = (sdp_sp_profile_t *)provider->data;

    return rfcomm_profile_create_protocol_descriptor_list(buf, eob,
        (uint8_t const *)&spp->server_channel, 1);
}

static int32_t spp_profile_create_bluetooth_profile_descriptor_list(
    uint8_t *buf, uint8_t const * const eob, uint8_t const *data,
    uint32_t datalen)
{
    static profile_descriptor_t profile_descriptor_list[] = {
        {
            UUID_INIT16(SDP_SERVICE_CLASS_SERIAL_PORT),
            0x0100 /* v1.0 Serial Port Profile */
        }
    };

    return common_profile_create_bluetooth_profile_descriptor_list(buf, eob,
        (uint8_t const *)profile_descriptor_list,
        sizeof(profile_descriptor_list));
}

/*static int32_t spp_profile_create_supported_features(uint8_t *buf,
    uint8_t const * const eob, uint8_t const *data, uint32_t datalen)
{
    provider_t const *provider = (provider_t const *)(void *)data;
    sdp_sp_profile_t *spp = (sdp_sp_profile_t *)provider->data;

    return common_profile_create_uint16(buf, eob,
        (uint8_t const *)&spp->u.hf_supported_features, 2);
}*/

static int32_t spp_profile_create_service_name(uint8_t *buf,
    uint8_t const * const eob, uint8_t const *data, uint32_t datalen)
{
    provider_t const *provider = (provider_t const *)(void *)data;
    sdp_sp_profile_t *spp = (sdp_sp_profile_t *)provider->data;

    return common_profile_create_string8(buf, eob,
        (uint8_t const *)spp->service_name, j_strlen(spp->service_name));
}

static bool_t spp_profile_data_valid(uint8_t const *data, uint32_t datalen)
{
    sdp_sp_profile_t const *spp = (sdp_sp_profile_t const *)data;
    DECLARE_FNAME("spp_profile_data_valid");

    if (spp->svc_type != BT_SVC_TYPE_SERIAL_PORT)
    {
        return FALSE;
    }

    if(spp->server_channel < RFCOMM_CHANNEL_MIN ||
        spp->server_channel > RFCOMM_CHANNEL_MAX)
    {
        DBG_E(DBT_SDP_SRV, ("%s: bad channel %d\n", FNAME, spp->server_channel));
        return FALSE;
    }

    return TRUE;
}

static attr_t spp_profile_attrs[] = {
    { SDP_ATTR_SERVICE_RECORD_HANDLE,
        common_profile_create_service_record_handle },
    { SDP_ATTR_SERVICE_CLASS_ID_LIST,
        spp_profile_create_service_class_id_list },
    { SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST,
        spp_profile_create_protocol_descriptor_list },
    { SDP_ATTR_BLUETOOTH_PROFILE_DESCRIPTOR_LIST,
        spp_profile_create_bluetooth_profile_descriptor_list },

    { SDP_ATTR_PRIMARY_LANGUAGE_BASE_ID + SDP_ATTR_SERVICE_NAME_OFFSET,
        spp_profile_create_service_name },
    { 0, NULL } /* end entry */
};

static uuid_t spp_profile_uuids[] = {
#ifdef SUPPORT_128BITS_UUID
    {{0x51, 0xDB, 0xA1, 0x09, 0x5B, 0xA9, 0x49, 0x81, 0x96, 0xB7, 0x6A, 0xFE, 0x13, 0x20, 0x93, 0xDE} , sizeof(uw_u128_t)},
#endif
    UUID_INIT16(SDP_SERVICE_CLASS_SERIAL_PORT),
    UUID_INIT16(SDP_UUID_PROTOCOL_RFCOMM),
    UUID_INIT16(SDP_UUID_PROTOCOL_L2CAP)
};

profile_t sp_profile_descriptor = {
#ifdef J_DEBUG
    "SERIALPORT",
#endif
    BT_SVC_TYPE_SERIAL_PORT,
    spp_profile_uuids,
    sizeof(spp_profile_uuids),
    sizeof(sdp_sp_profile_t),
    spp_profile_data_valid,
    (attr_t const *)&spp_profile_attrs
};
#endif

