/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "esp_secure_cert_config.h"
#include "esp_secure_cert_tlv_config.h"

#ifdef CONFIG_ESP_SECURE_CERT_DS_PERIPHERAL
#include "rsa_sign_alt.h"
#endif
/*
 *  Get the flash address of a structure
 *
 * Note: This API also validates the crc of the respective tlv before returning the offset
 * @input
 *                          for calculating current crc for esp_secure_cert
 *
 * tlv_address              Void pointer to store tlv address
 *
 * Note: If tlv type = ESP_SECURE_CERT_TLV_END then the address returned shall be the end address of current tlv formatted data.
 * @return
 *      - ESP_OK    On success
 *      - ESP_FAIL/other relevant esp error code
 *                  On failure
 */
esp_err_t esp_secure_cert_tlv_get_addr(esp_secure_cert_tlv_type_t type, char **buffer, uint32_t *len);

/*
 * Identify if esp_secure_cert partition of type TLV is present.
 * @return
 *       - 1 on if the partition is identified as TLV
 *       - 0 on failure
 */
bool esp_secure_cert_is_tlv_partition(void);

#ifdef CONFIG_ESP_SECURE_CERT_DS_PERIPHERAL
/* @info
 *       This function returns the flash esp_ds_context which can then be
 *       directly provided to an esp-tls connection through its config structure.
 *       The memory for the context is dynamically allocated.
 *       The internal structures are however directly accessed from flash.
 *       e.g. esp_ds_data
 *
 * @params
 *      - ds_ctx    The pointer to the DS context
 * @return
 *      - ESP_OK    On success
 *      - ESP_FAIL/other relevant esp error code
 *                  On failure
 */
esp_ds_data_ctx_t *esp_secure_cert_tlv_get_ds_ctx(void);

/*
 *@info
 *      Free the ds context
 */
void esp_secure_cert_tlv_free_ds_ctx(esp_ds_data_ctx_t *ds_ctx);
#endif
