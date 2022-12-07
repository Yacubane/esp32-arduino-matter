/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <stdint.h>
#include "sdkconfig.h"
#ifdef CONFIG_ESP_SECURE_CERT_DS_PERIPHERAL
#include "esp_ds.h"
#endif

#define ESP_SECURE_CERT_TLV_PARTITION_TYPE      0x3F                        /* Custom partition type */
#define ESP_SECURE_CERT_TLV_PARTITION_NAME      "esp_secure_cert"           /* Name of the custom esp_secure_cert partition */
#define ESP_SECURE_CERT_TLV_MAGIC                0xBA5EBA11

/* secure cert partition of cust_flash type in this case is of 8 KB size,
 * out of which 3-3.1 KB size is utilized.
 */

/*
 * Plase note that no two TLV structures of the same type
 * can be stored in the esp_secure_cert partition at one time.
 */
typedef enum esp_secure_cert_tlv_type {
    ESP_SECURE_CERT_CA_CERT_TLV = 0,
    ESP_SECURE_CERT_DEV_CERT_TLV,
    ESP_SECURE_CERT_PRIV_KEY_TLV,
    ESP_SECURE_CERT_DS_DATA_TLV,
    ESP_SECURE_CERT_DS_CONTEXT_TLV,
    // Any new tlv types should be added above this
    ESP_SECURE_CERT_TLV_END = 50,
    //Custom data types
    //that can be defined by the user
    ESP_SECURE_CERT_USER_DATA_1 = 51,
    ESP_SECURE_CERT_USER_DATA_2 = 52,
    ESP_SECURE_CERT_USER_DATA_3 = 53,
    ESP_SECURE_CERT_USER_DATA_4 = 54,
    ESP_SECURE_CERT_USER_DATA_5 = 54,
} esp_secure_cert_tlv_type_t;

/*
 * Header for each tlv
 */
typedef struct esp_secure_cert_tlv_header {
    uint32_t magic;
    uint8_t reserved[4];                /* Reserved bytes for future use, the value currently should be 0xFF */
    uint16_t type;                      /* Type of tlv structure, this shall be typecasted
                                           to esp_secure_cert_tlv_type_t for further use */
    uint16_t length;                    /* Length of the data */
    uint8_t value[0];                   /* Actual data in form of byte array */
} __attribute__((packed)) esp_secure_cert_tlv_header_t;

/*
 * Footer for each tlv
 */
typedef struct esp_secure_cert_tlv_footer {
    uint32_t crc;                       /* crc of the data */
} esp_secure_cert_tlv_footer_t;

_Static_assert(sizeof(esp_secure_cert_tlv_header_t) == 12, "TLV header size should be 12 bytes");

_Static_assert(sizeof(esp_secure_cert_tlv_footer_t) == 4, "TLV footer size should be 4 bytes");

/*
 * Note:
 *
 * The data stored in a cust flash partition should be as follows:
 *
 * tlv_header1 -> data_1 -> tlv_footer1 -> tlv_header2...
 *
 */
