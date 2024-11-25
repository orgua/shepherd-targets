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

// Adapted pinout for Target V1.2 (Riotee)
#define PIN_UART_TX (8)  // P0.08
#define PIN_UART_RX (21) // P0.21

#define GPIO0       PIN_UART_RX
#define GPIO1       PIN_UART_TX
#define GPIO2       (4)
#define GPIO3       (5)
#define GPIO4       (32 + 9) // P1.09
#define GPIO5       (26)
#define GPIO6       (32 + 3) // P1.03
#define GPIO7       (11)
#define GPIO8       (13)
#define GPIO9       (16)
#define GPIO10      (12)
#define GPIO11      (10)
#define GPIO12      (19)
#define GPIO13      (20)
#define GPIO14      (24)
#define GPIO15      (27)
#define PWRGDL      (23)
#define PWRGDH      (7)

#define PIN_LED0    (32 + 13) // P1.13 -> powered externally
//#define PIN_LED1    12 // P0.12 -> powered externally
#define PIN_LED2    (3) // P0.03 -> burns energy-budget

#define I2C_SCL     (32 + 8) // P1.08
#define I2C_SDA     (6)
#define RTC_INT     (30) // output of RTC, not controllable
#define MAX_INT     (25)

#define C2C_CLK     (18)
#define C2C_CoPi    (17)
#define C2C_CiPo    (14)
#define C2C_PSel    (22)
#define C2C_GPIO    (15)

#define THRCTRL_H0  (9)
#define THRCTRL_H1  (32 + 2)
#define THRCTRL_L0  (32 + 7)
#define THRCTRL_L1  (32 + 4)

// index with reference to names of shepherds target-port
const uint32_t gpios[] = {GPIO0, GPIO1,  GPIO2,  GPIO3,  GPIO4,  GPIO5,  GPIO6,  GPIO7,  GPIO8,
                          GPIO9, GPIO10, GPIO11, GPIO12, GPIO13, GPIO14, GPIO15, PWRGDL, PWRGDH};
const uint32_t pins[]  = {GPIO0, /*GPIO1,*/ GPIO2, GPIO3,  GPIO4,  GPIO5,  GPIO6,  GPIO7,  GPIO8,
                          GPIO9, GPIO10,           GPIO11, GPIO12, GPIO13, GPIO14, GPIO15, PWRGDL,
                          PWRGDH}; // without uart-tx

const uint32_t leds[]  = {PIN_LED0, PIN_LED2};
const uint32_t i2c[]   = {I2C_SCL, I2C_SDA, /*RTC_INT,*/ MAX_INT};
const uint32_t c2c[]   = {C2C_CLK, C2C_CoPi, C2C_CiPo, C2C_PSel, C2C_GPIO};
const uint32_t thr[]   = {THRCTRL_H0, THRCTRL_H1, THRCTRL_L0, THRCTRL_L1};

const uint32_t all[]   = {
        GPIO0,      /*GPIO1,*/ GPIO2,
        GPIO3,      GPIO4,
        GPIO5,      GPIO6,
        GPIO7,      GPIO8,
        GPIO9,      GPIO10,
        GPIO11,     GPIO12,
        GPIO13,     GPIO14,
        GPIO15,     PWRGDL,
        PWRGDH,     PIN_LED0,
        PIN_LED2,   I2C_SCL,
        I2C_SDA,    /*RTC_INT,*/ MAX_INT,
        C2C_CLK,    C2C_CoPi,
        C2C_CiPo,   C2C_PSel,
        C2C_GPIO,   THRCTRL_H0,
        THRCTRL_H1, THRCTRL_L0,
        THRCTRL_L1,
};

#define N_PINS  sizeof(pins) / sizeof(uint32_t)
#define N_GPIOS sizeof(gpios) / sizeof(uint32_t)
#define N_LEDS  sizeof(leds) / sizeof(uint32_t)
#define N_I2C   sizeof(i2c) / sizeof(uint32_t)
#define N_C2C   sizeof(c2c) / sizeof(uint32_t)
#define N_THR   sizeof(thr) / sizeof(uint32_t)
#define N_ALL   sizeof(all) / sizeof(uint32_t)

/* Processes rising GPIO edges */
void gpio_consumer(struct pt *pt)
{
    /* works for up to 8 pins */
    pt_begin(pt);

    const char *slot_num;

    gpiote_init(pins, N_PINS);

    while (1)
    {
        pt_wait(pt, !pt_queue_empty(&q_pin_edges));
        slot_num = pt_queue_pop(&q_pin_edges);
        printf("%c triggered\r\n", *slot_num);
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
        const char *cmd = pt_queue_pop(&q_cmds);

        /* Convert ascii number to pin number */
        pin_idx         = *cmd - 0x30;
        if (pin_idx >= N_PINS)
            printf("%c is outside of range of supported pins (%zu)\r\n", *cmd, N_PINS);

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
    const uint32_t duration_us = duration * 1000;
    while (timer_now_us() < duration_us);
}

static void set_gpio_out(const uint8_t pin_num, const bool enable)
{
    const bool    is_p0 = pin_num < 32;
    const uint8_t pin   = pin_num & 0b11111;

    if (enable)
    {
        nrf_gpio_cfg_output(pin_num);
        nrf_gpio_pin_set(pin_num);
        if (is_p0) NRF_P0->OUTCLR = (1u << pin);
        else NRF_P1->OUTCLR = (1u << pin);
    }
    else
    {
        nrf_gpio_pin_clear(pin_num);
        nrf_gpio_cfg_input(pin_num, NRF_GPIO_PIN_NOPULL);
    }
}

static void set_gpio_state(const uint8_t pin_num, const bool state)
{
    if (state) NRF_P0->OUTSET = (1u << pin_num);
    else NRF_P0->OUTCLR = (1u << pin_num);
}

static bool get_gpio(const uint8_t pin_num)
{
    const bool    is_p0 = pin_num < 32;
    const uint8_t pin   = pin_num & 0b11111;
    uint32_t      value;
    if (is_p0) value = NRF_P0->IN;
    else value = NRF_P1->IN;
    return (value & (1u << pin)) > 0;
}

/* GENERALIZED GPIO FUNCTIONS */

static void toggle_gpio_one_high(const uint32_t array[], const uint8_t array_size)
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

static uint8_t gpio_watcher(const uint32_t array[], const uint8_t array_size)
{
    for (uint8_t count = 0; count < array_size; count++)
    {
        if (get_gpio(array[count])) return count;
    }
    return 0xFF;
}

/* PRIMARY ROUTINE */

int main(void)
{

    /* Optimize latency over power */
    NRF_POWER->TASKS_CONSTLAT   = 1;
    /* Start HF crystal oscillator */
    NRF_CLOCK->TASKS_HFCLKSTART = 1;

    uart_init(PIN_UART_TX, PIN_UART_RX);
    timer_init();

    /* TODO: test
     *  - RTC &
     *  - FRAM
     */

    /* TEST-Code Mode:
     *  - Mode 0: the other MCU toggles, this one supervises & reports
     *  - Mode 1: this MCU toggles, the other supervises & reports
     *  - Mode X: start reacting to gpio-signals or uart-messages
     */
    uint8_t mode = 5;

    if (mode == 5)
    {
        /* this MCU supervises & reports */
        for (uint8_t count = 0; count < N_ALL; count++) { set_gpio_out(all[count], false); }
        uint32_t map_new          = 0x00;
        uint32_t map_old          = 0xFF;
        uint8_t  triggered[N_ALL] = {0};
        printf("\r\nGPIO WATCHER (%zu pins)\r\n", N_ALL);
        if (N_ALL > 32) printf("Error: Implementation can only handle 32 pins");
        while (1)
        {
            map_new = 0;
            for (uint8_t count = 0; count < N_ALL; count++)
            {
                if (get_gpio(all[count]))
                {
                    triggered[count] = 1;
                    map_new |= 1 << count;
                }
            }
            if (map_new != map_old)
            {
                for (uint8_t count = 0; count < N_ALL; count++)
                {
                    if (map_new & (1 << count)) printf("%d", count % 10);
                    else printf(" ");
                }
                printf("\r\n");
                map_old     = map_new;
                uint8_t sum = 0;
                for (uint8_t pos = 0; pos < N_ALL; pos++) sum += triggered[pos];
                if (sum >= N_ALL) { printf("Received all %u shared pins!!\r\n", sum); }
            }
        };
    }
    else if (mode == 0)
    {
        /* this MCU supervises & reports */
        for (uint8_t count = 0; count < N_ALL; count++) { set_gpio_out(all[count], false); }
        uint8_t num_new          = 0x00;
        uint8_t num_old          = 0xFF;
        uint8_t triggered[N_ALL] = {0};
        printf("\r\nGPIO WATCHER\r\n");
        while (1)
        {
            num_new = gpio_watcher(all, N_ALL);
            if ((num_new < N_ALL) && (num_new != num_old))
            {
                printf("%u triggered\r\n", num_new);
                num_old            = num_new;
                triggered[num_new] = 1;
                uint8_t sum        = 0;
                for (uint8_t pos = 0; pos < N_ALL; pos++) sum += triggered[pos];
                if (sum >= N_ALL) { printf("Received all %u shared pins!!\r\n", sum); }
            }
        };
    }
    else if (mode == 1)
    {
        /* Switch on used GPIO for 100ms in a row */
        toggle_gpio_one_high(leds, N_LEDS);

        toggle_gpio_one_high(pins, N_PINS); // GPIO without UART
        toggle_gpio_one_high(i2c, N_I2C);
        toggle_gpio_one_high(c2c, N_C2C);

        /* Switch on LEDs for 100ms in a row (>=8 Reps, depending on node-id) */
        uint32_t rep_sum = SHEPHERD_NODE_ID ? SHEPHERD_NODE_ID >= 8 : 8;
        for (uint32_t reps = 0; reps < rep_sum; reps++) { toggle_gpio_one_high(leds, N_LEDS); }
    }
    else
    {
        /* start reacting to gpio-signals or uart-messages */
        struct pt pt_gpio_consumer = pt_init();
        struct pt pt_cmd_consumer  = pt_init();

        while (1)
        {
            gpio_consumer(&pt_gpio_consumer);
            cmd_consumer(&pt_cmd_consumer);
        };
    }
}
