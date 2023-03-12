/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_bit_defs.h"
#include "sdkconfig.h"
#include "soc/soc_caps.h"
#ifdef CONFIG_ESP_SECURE_CERT_DS_PERIPHERAL
#include "esp_ds.h"
#endif

#define ESP_SECURE_CERT_TLV_PARTITION_TYPE      0x3F                        /* Custom partition type */
#define ESP_SECURE_CERT_TLV_PARTITION_NAME      "esp_secure_cert"           /* Name of the custom esp_secure_cert partition */
#define ESP_SECURE_CERT_TLV_MAGIC                0xBA5EBA11

#define ESP_SECURE_CERT_HMAC_KEY_ID              (0)                         /* The hmac_key_id value that shall be used for HMAC based ecdsa key generation */
#define ESP_SECURE_CERT_DERIVED_ECDSA_KEY_SIZE   (32)                       /* The key size in bytes of the derived ecdsa key */
#define ESP_SECURE_CERT_KEY_DERIVATION_ITERATION_COUNT  (2048)              /* The iteration count for ecdsa key derivation */

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
    ESP_SECURE_CERT_HMAC_ECDSA_KEY_SALT,
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

/**
 * Flags    8 bits
 * Used bits:
 *      bit7(MSB) & bit6 - hmac_based_encryption
 *          If the value of the bits is 0b10 (i.e. 2 in decimal) then the data in the block needs to be
 *          decrypted first using the HMAC based encryption scheme
 *          before sending out
 *          If the value of the bits is 0b01 (i.e. 1 in decimal) then the hmac based ecdsa
 *          private key generation is enabled. Generate the private key internally using the hardware HMAC peripheral.
 * Ununsed bits:
 *      .
 *      .
 *      bit0 (LSB)
 */
#define ESP_SECURE_CERT_TLV_FLAG_HMAC_ENCRYPTION            (2 << 6)
#define ESP_SECURE_CERT_TLV_FLAG_HMAC_ECDSA_KEY_DERIVATION  (1 << 6)

#define ESP_SECURE_CERT_IS_TLV_ENCRYPTED(flags) \
    ((flags & (BIT7 | BIT6)) == ESP_SECURE_CERT_TLV_FLAG_HMAC_ENCRYPTION)

#define ESP_SECURE_CERT_HMAC_ECDSA_KEY_DERIVATION(flags) \
    ((flags & (BIT7 | BIT6)) == ESP_SECURE_CERT_TLV_FLAG_HMAC_ECDSA_KEY_DERIVATION)

/*
 * Header for each tlv
 */
typedef struct esp_secure_cert_tlv_header {
    uint32_t magic;
    uint8_t flags;                      /* flags byte that identifies different characteristics for the TLV */
    uint8_t reserved[3];                /* Reserved bytes for future use, the value currently should be 0x0 */
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
