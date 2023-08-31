#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"

#include "peripherals.h"
#include "printf.h"

#include "pt.h"

// see shepherd_node_id.c for details
extern const uint16_t SHEPHERD_NODE_ID;

#define PIN_UART_TX 8  // P0.08
#define PIN_UART_RX 21 // P0.21
#define PIN_LED0    16 // P0.16 -> powered externally
#define PIN_LED1    12 // P0.12 -> powered externally
#define PIN_LED2    3  // P0.03 -> burns energy-budget

// with reference to names of target-port (gpio 0:6 = 7, 8, 2, 3, 4, 5, 6)
unsigned int pins[]      = {11, 13, 4, 5, 41, 26, 35};
unsigned int gpios_all[] = {11, 13, 4, 5, 41, 26, 35, 8, 21, 7};
unsigned int leds[]      = {PIN_LED0, PIN_LED1, PIN_LED2};

#define N_PINS  sizeof(pins) / sizeof(unsigned int)
#define N_GPIOS sizeof(gpios_all) / sizeof(unsigned int)
#define N_LEDS  sizeof(leds) / sizeof(unsigned int)

/*
    Pins P3:12 on Target-Header of V1.0 are:

    SHP-HDR     Riotee      nRF52       msp430
    GPIO0       GPIO.7      P0.11       P5.3
    GPIO1       GPIO.8      P0.13       P5.2
    GPIO2       GPIO.2      P0.04       P2.3
    GPIO3       GPIO.3      P0.05       P2.4
    GPIO4       GPIO.4      P1.09       P4.6
    GPIO5       GPIO.5      P0.26       P3.6
    GPIO6       GPIO.6      P1.03       PJ.6
    GPIO7       GPIO.1      P0.08       P2.5
    GPIO8       GPIO.0      P0.21       P2.6
    BATOK       GPIO.9      P0.07       P5.5
                LED.0       P0.16       P5.1
                LED.1       P0.12       P5.0
                LED.2P      P0.03       PJ.0
 */


/* Processes rising GPIO edges */
void gpio_consumer(struct pt *pt)
{
    pt_begin(pt);

    char *slot_num;

    gpiote_init(pins, N_PINS);

    while (1)
    {

        pt_wait(pt, !pt_queue_empty(&q_pin_edges));
        slot_num = pt_queue_pop(&q_pin_edges);
        printf("%u triggered\r\n", *slot_num);
    }

    pt_end(pt);
}

/* Processes commands from UART */
void cmd_consumer(struct pt *pt)
{
    pt_begin(pt);

    static unsigned int pin_idx;

    while (1)
    {

        pt_wait(pt, !pt_queue_empty(&q_cmds));
        char *cmd = pt_queue_pop(&q_cmds);

        /* Convert ascii number to pin number */
        pin_idx   = *cmd - 0x30;
        if (pin_idx >= N_PINS)
            printf("%c is outside of range of supported pins (%u)\r\n", *cmd, N_PINS);

        /* Switch on pin for 100us */
        timer_reset();
        nrf_gpiote_event_disable(pin_idx);
        nrf_gpio_cfg_output(pins[pin_idx]);
        nrf_gpio_pin_set(pins[pin_idx]);
        while (timer_now_us() < 100) { pt_yield(pt); }
        nrf_gpio_pin_clear(pins[pin_idx]);
        nrf_gpio_cfg_input(pins[pin_idx], NRF_GPIO_PIN_NOPULL);
        nrf_gpiote_event_enable(pin_idx);
    }

    pt_end(pt);
}


static void set_gpio_out(const uint32_t p0_num, const bool enable)
{
    if (enable)
    {
        nrf_gpio_cfg_output(p0_num);
        nrf_gpio_pin_set(p0_num);
    }
    else
    {
        nrf_gpio_pin_clear(p0_num);
        nrf_gpio_cfg_input(p0_num, NRF_GPIO_PIN_NOPULL);
    }
}


static void set_gpio_state(const uint32_t p0_num, const bool state)
{
    if (state) NRF_P0->OUTSET = (1u << p0_num);
    else NRF_P0->OUTCLR = (1u << p0_num);
}


int main(void)
{

    /* Optimize latency over power */
    NRF_POWER->TASKS_CONSTLAT   = 1;
    /* Start HF crystal oscillator */
    NRF_CLOCK->TASKS_HFCLKSTART = 1;

    uart_init(6, 8);
    timer_init();

    struct pt pt_gpio_consumer = pt_init();
    struct pt pt_cmd_consumer  = pt_init();

    /* TODO: test RTC & FRAM */

    /* Switch on LEDs for 100ms in a row (>=8 Reps) */
    for (uint8_t count = 0; count < N_LEDS; count++)
    {
        set_gpio_out(leds[count], true);
        set_gpio_state(leds[count], false);
    }
    uint32_t rep_sum = SHEPHERD_NODE_ID ? SHEPHERD_NODE_ID >= 8 : 8;
    for (uint32_t reps = 0; reps < rep_sum; reps++)
    {
        for (uint8_t count = 0; count < N_LEDS; count++)
        {
            timer_reset();
            set_gpio_state(leds[count], true);
            while (timer_now_us() < 100000)
                ;
            set_gpio_state(leds[count], true);
        }
    }
    for (uint8_t count = 0; count < N_LEDS; count++) { set_gpio_out(leds[count], false); }

    /* switch all Header-GPIO on for 10 ms in a row (1 rep) */
    for (uint8_t count = 0; count < N_HDR; count++)
    {
        set_gpio_out(gpios_all[count], true);
        set_gpio_state(gpios_all[count], false);
    }
    for (uint8_t reps = 0; reps < 4; reps++)
    {
        for (uint8_t count = 0; count < N_HDR; count++)
        {
            timer_reset();
            set_gpio_state(gpios_all[count], true);
            while (timer_now_us() < 100000)
                ;
            set_gpio_state(gpios_all[count], false);
        }
    }
    for (uint8_t count = 0; count < N_HDR; count++) { set_gpio_out(gpios_all[count], false); }

    /* start reacting to gpio-signals or uart-messages */
    while (1)
    {
        gpio_consumer(&pt_gpio_consumer);
        cmd_consumer(&pt_cmd_consumer);
    };
}
