#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include <string.h>

#include "nrf_delay.h"
#include "nrf_gpio.h"

#include "peripherals.h"
#include "radio.h"

#define GPIO_LED (32 + 13) // P1.13

// see shepherd_node_id.c for details
extern const uint16_t SHEPHERD_NODE_ID;

adv_pck_t             pkt;
ble_ll_addr_t         adv_address = {.addr_bytes = {0x05, 0x04, 0x03, 0x02, 0x01, 0x00}};

uint8_t               some_data[] = {0x02, // length of this data
                                     0x01, (1UL << 2) | (1UL << 1),
                                     0x09, /* Length of name field */
                                     0x09, /* Type of name field */
                                     'S',  'H',
                                     'E',  'P',
                                     'H',  'E',
                                     'R',  'D',
                                     0x07,       /* Length of mnf-specific data field */
                                     0xFF,       /* Type of mnf-specific data field */
                                     0x59, 0x00, /* Nordic semiconductors */
                                     0x00, 0x00, /* Custom 4B data */
                                     0x00, 0x00};

static inline void    delay_ms(const uint32_t duration)
{
    timer_reset();
    uint32_t duration_us = duration * 1000;
    while (timer_now_us() < duration_us);
}

int main(void)
{
    static unsigned int counter;

    /* put shepherd-node-id into packets user-data*/
    some_data[19] = (SHEPHERD_NODE_ID >> 8) & 0xFF;
    some_data[20] = (SHEPHERD_NODE_ID >> 0) & 0xFF;

    timer_init();
    radio_init();

    memcpy(&pkt.payload, some_data, sizeof(some_data));
    radio_prepare_adv(&pkt, &adv_address, sizeof(some_data) + sizeof(ble_ll_addr_t));

    nrf_gpio_cfg_output(GPIO_LED);
    nrf_gpio_pin_set(GPIO_LED);

    while (1)
    {
        /* Switch on LED */
        NRF_P0->OUTSET = (1u << GPIO_LED);


        /* Place the counter value within packets payload */
        memcpy(&pkt.payload[17], &counter, 4);
        radio_send(&pkt, 38);
        counter++;
        delay_ms(30);

        /* Switch off LED */
        NRF_P0->OUTCLR = (1u << GPIO_LED);

        delay_ms(1000);
    }
}
