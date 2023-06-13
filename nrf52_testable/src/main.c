#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"

#include "peripherals.h"
#include "printf.h"

#include "pt.h"

#define N_PINS      sizeof(pins) / sizeof(unsigned int)

#define PIN_UART_TX 8  // P0.08
#define PIN_UART_RX 21 // P0.21
#define PIN_LED0    16 // P0.16 -> powered externally
#define PIN_LED1    12 // P0.12 -> powered externally
#define PIN_LED2    3  // P0.03 -> burns energy-budget

// with reference to names of target-port (gpio 0:6 = 7, 8, 2, 3, 4, 5, 6)
unsigned int pins[] = {11, 13, 4, 5, 41, 26, 35};

/* Processes rising GPIO edges */
void         gpio_consumer(struct pt *pt)
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

    /* Switch on pin for 100us */
    nrf_gpio_cfg_output(PIN_LED0);
    nrf_gpio_cfg_output(PIN_LED1);
    nrf_gpio_pin_set(PIN_LED0);
    nrf_gpio_pin_set(PIN_LED1);

    for (uint8_t count = 0; count < 10; count++)
    {
        timer_reset();
        NRF_P0->OUTCLR = (1 << PIN_LED0);
        NRF_P0->OUTSET = (1 << PIN_LED1);
        while (timer_now_us() < 50000)
            ;
        NRF_P0->OUTSET = (1 << PIN_LED0);
        NRF_P0->OUTCLR = (1 << PIN_LED1);
        while (timer_now_us() < 150000)
            ;
    }

    while (1)
    {
        gpio_consumer(&pt_gpio_consumer);
        cmd_consumer(&pt_cmd_consumer);
    };
}
