#ifndef __RADIO_H__
#define __RADIO_H__

#include <stdint.h>

typedef enum
{
    ADV_IND         = 0,
    ADV_DIRECT_IND  = 1,
    ADV_NONCONN_IND = 2,
    SCAN_REQ        = 3,
    SCAN_RSP        = 4,
    CONNECT_REQ     = 5,
    ADV_SCAN_IND    = 6,
} adv_pdu_type_t;

typedef struct
{
    uint8_t addr_bytes[6];
} __attribute__((__packed__)) ble_ll_addr_t;

typedef struct
{
    adv_pdu_type_t pdu_type : 4;
    unsigned int   rfu : 1;
    unsigned int   chsel : 1;
    unsigned int   txadd : 1;
    unsigned int   rxadd : 1;
    uint8_t        len;
} __attribute__((__packed__)) ble_ll_header_t;

// This format is common to a number of ADV PDU types
typedef struct
{
    ble_ll_header_t header;
    ble_ll_addr_t   adv_addr;
    uint8_t         payload[31];
} __attribute__((__packed__)) adv_pck_t;

int               radio_prepare_adv(adv_pck_t *const pkt, const ble_ll_addr_t *const adv_addr,
                                    const unsigned int len);
pt_event_t *const radio_send(adv_pck_t *const pkt, const uint8_t ch);
int               radio_init();

#endif /* __RADIO_H__ */
