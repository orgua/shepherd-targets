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
    GPIO7       GPIO.1      P0.08       P2.5    UART TX (this MCU as Point of view)
    GPIO8       GPIO.0      P0.21       P2.6    UART RX (this MCU as Point of view)
    BATOK       GPIO.9      P0.07       P5.5

                LED.0       P0.16       P5.1
                LED.1       P0.12       P5.0
                LED.2P      P0.03       PJ.0

                I2C.SCL     P1.08       P6.5
                I2C.SDA     P0.06       P6.4
                RTC.INT     P0.30       P7.3

                C2C.CLK     P0.18       P1.5
                C2C.CoPi    P0.17       P2.0
                C2C.CiPo    P0.14       P2.1
                C2C.PSel    P0.22       P1.4
                C2C.GPIO    P0.15       PJ.2
 */

#define PIN_UART_TX 8  // P0.08
#define PIN_UART_RX 21 // P0.21
#define PIN_LED0    16 // P0.16 -> powered externally
#define PIN_LED1    12 // P0.12 -> powered externally
#define PIN_LED2    3  // P0.03 -> burns energy-budget

// with reference to names of shepherds target-port
unsigned int pins[]      = {11, 13, 4, 5, 41, 26, 35, 21, 7}; // without uart-TX
unsigned int gpios[] = {11, 13, 4, 5, 41, 26, 35, 8, 21, 7};

unsigned int leds[]      = {PIN_LED0, PIN_LED1, PIN_LED2};
unsigned int i2c[] = {40, 6, 30};
unsigned int c2c[] = {18, 17, 14, 22, 15};

unsigned int all[] = {
        11, 13, 4, 5, 41, 26, 35, 21, 7,
        PIN_LED0, PIN_LED1, PIN_LED2,
        40, 6, 30,
        18, 17, 14, 22, 15,
        };

#define N_PINS  sizeof(pins) / sizeof(unsigned int)
#define N_GPIOS sizeof(gpios) / sizeof(unsigned int)
#define N_LEDS  sizeof(leds) / sizeof(unsigned int)
#define N_I2C  sizeof(i2c) / sizeof(unsigned int)
#define N_C2C  sizeof(c2c) / sizeof(unsigned int)
#define N_ALL  sizeof(all) / sizeof(unsigned int)

/* Processes rising GPIO edges */
void gpio_consumer(struct pt *pt)
{
    pt_begin(pt);

    char *slot_num;

    gpiote_init(all, N_ALL);

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

/* PLATFORM SPECIFIC CODE */

static inline void delay_ms(const uint32_t duration)
{
    timer_reset();
    uint32_t duration_us = duration * 1000;
    while (timer_now_us() < duration_us)
        ;
}

static void set_gpio_out(const uint32_t p0_num, const bool enable)
{
    if (enable)
    {
        nrf_gpio_cfg_output(p0_num);
        nrf_gpio_pin_set(p0_num);
        NRF_P0->OUTCLR = (1u << p0_num);
    }
    else
    {
        nrf_gpio_pin_clear(p0_num);
        nrf_gpio_cfg_input(p0_num, NRF_GPIO_PIN_NOPULL);
    }
}

static void set_gpio_state(const uint32_t pin_num, const bool state)
{
    if (state) NRF_P0->OUTSET = (1u << pin_num);
    else NRF_P0->OUTCLR = (1u << pin_num);
}

/* GENERALIZED GPIO FUNCTIONS */

static void toggle_gpio_one_high(unsigned int array[], unsigned int array_size)
{
    /* set array to output */
    for (uint8_t count = 0; count < array_size; count++) { set_gpio_out(array[count], true); }
    /* switch each pin on in array */
    for (uint8_t count = 0; count < array_size; count++)
    {
        set_gpio_state(array[count], true);
        delay_ms(100);
        set_gpio_state(array[count], false);
    }
    /* set pins to INPUT */
    for (uint8_t count = 0; count < array_size; count++) { set_gpio_out(array[count], false); }
}

/* PRIMARY ROUTINE */

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

    /* TODO: test
     *  - RTC &
     *  - FRAM
     */

    /* TEST-Code Mode:
     *  - Mode 0: the other MCU toggles, this one supervises & reports
     *  - Mode 1: this MCU toggles, the other supervises & reports
     *  - Mode X: start reacting to gpio-signals or uart-messages
     */
    uint8_t mode = 0;

    if (mode == 0)
    {
        /* this MCU supervises & reports */
        while (1)
        {
            gpio_consumer(&pt_gpio_consumer);
        };
    }
    else if (mode == 1)
    {
        /* Switch on used GPIO for 100ms in a row */
        toggle_gpio_one_high(leds, N_LEDS);

        toggle_gpio_one_high(pins, N_LEDS);
        toggle_gpio_one_high(i2c, N_LEDS);
        toggle_gpio_one_high(c2c, N_LEDS);

        /* Switch on LEDs for 100ms in a row (>=8 Reps, depending on node-id) */
        uint32_t rep_sum = SHEPHERD_NODE_ID ? SHEPHERD_NODE_ID >= 8 : 8;
        for (uint32_t reps = 0; reps < rep_sum; reps++)
        {
            toggle_gpio_one_high(leds, N_LEDS);
        }
    }
    else
    {
        /* start reacting to gpio-signals or uart-messages */
        while (1)
        {
            gpio_consumer(&pt_gpio_consumer);
            cmd_consumer(&pt_cmd_consumer);
        };
    }
}
