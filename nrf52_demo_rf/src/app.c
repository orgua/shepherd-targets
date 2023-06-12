
#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include <string.h>

#include "nrf_delay.h"
#include "nrf_gpio.h"

#include "peripherals.h"
#include "pt.h"
#include "radio.h"

#define GPIO_SIG_BAT_OK 7 // P0.07
#define GPIO_LED        3 // P0.03 -> burns energy

#define V_THR_ON        3.0

// see shepherd_node_id.c for details
extern const uint16_t SHEPHERD_NODE_ID;

pt_event_t            evt_on  = pt_event_init();
pt_event_t            evt_off = pt_event_init();

adv_pck_t             pkt;
ble_ll_addr_t         adv_address = {.addr_bytes = {0x05, 0x04, 0x03, 0x02, 0x01, 0x00}};

uint8_t               some_data[] = {0x02, // lengthof thisdata
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

__RAMFUNC void        application(struct pt *pt)
{
    pt_begin(pt);

    static volatile pt_event_t *radio_event;
    static unsigned int         counter;

    /* put shepherd-node-id into packets user-data*/
    some_data[19] = (SHEPHERD_NODE_ID >> 8) & 0xFF;
    some_data[20] = (SHEPHERD_NODE_ID >> 0) & 0xFF;

    /* Enable trigger supply voltage (reaching 3.3V -> evt_on) */
    adc_init(V_THR_ON);

    /* Prepare powerfail comparator (falling below 2.6V -> evt_off) */
    pofwarn_init(POWER_POFCON_THRESHOLD_V26);

    /* Enable trigger on pin edges (rising -> evt_on, falling -> evt_off) */
    gpiote_init(GPIO_SIG_BAT_OK);

    radio_init();
    memcpy(&pkt.payload, some_data, sizeof(some_data));
    radio_prepare_adv(&pkt, &adv_address, sizeof(some_data) + sizeof(ble_ll_addr_t));

    nrf_gpio_cfg_output(GPIO_LED);
    nrf_gpio_pin_set(GPIO_LED);

    while (1)
    {

        pt_event_clear(&evt_on);
        pt_event_wait(pt, &evt_on);
        /* Switch on LED */
        NRF_P0->OUTCLR = (1 << GPIO_LED);

        /* Place the counter value within packets payload */
        memcpy(&pkt.payload[17], &counter, 4);
        radio_event = radio_send(&pkt, 38);
        pt_event_wait(pt, radio_event);
        counter++;

        /* Clear any pending off events */
        pt_event_clear(&evt_off);
        /* Arm the powerfail comparator to switch off on low energy */
        pofwarn_arm();
        do {
            /* Important: Stay awake to keep POF comparator active */
            __NOP();
        }
        while (!pt_event_get(&evt_off));

        /* Switch off LED */
        NRF_P0->OUTSET = (1 << GPIO_LED);
    }

    pt_end(pt);
}
