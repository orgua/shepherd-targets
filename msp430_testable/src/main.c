#include <msp430.h>
#include <msp430fr5994.h>
#include <stdbool.h>
#include <stdint.h>

// see shepherd_node_id.c for details
extern const uint16_t SHEPHERD_NODE_ID;

/*
    MSP430 Pin-Name to int-Conversion:
    - Port J = 0, Port 1-8 stay same
    - Num = 8 * Port + Port.Pin
    - example: P5.5 becomes 8 * 5 + 5 = 45
 */

// Adapted pinout for Target V1.2 (Riotee)
#define PIN_UART_TX (8 * 2 + 5) // P2.5
#define PIN_UART_RX (8 * 2 + 6) // P2.6

#define GPIO0       PIN_UART_RX
#define GPIO1       PIN_UART_TX
#define GPIO2       (8 * 2 + 3) // P2.3
#define GPIO3       (8 * 2 + 4) //   .4
#define GPIO4       (8 * 4 + 6) // P4.6
#define GPIO5       (8 * 3 + 6) // P3.6
#define GPIO6       (8 * 0 + 6) // PJ.6
#define GPIO7       (8 * 5 + 3) // P5.3
#define GPIO8       (8 * 5 + 2) //   .2
#define GPIO9       (8 * 5 + 1) //   .1
#define GPIO10      (8 * 5 + 0) //   .0
#define GPIO11      (8 * 6 + 0) // P6.0
#define GPIO12      (8 * 6 + 1) //   .1
#define GPIO13      (8 * 6 + 3) //   .3
#define GPIO14      (8 * 6 + 6) //   .6
#define GPIO15      (8 * 6 + 7) //   .7
#define PWRGDL      (8 * 5 + 4) // P5.4
#define PWRGDH      (8 * 5 + 5) //   .5

#define PIN_LED0    (8 * 5 + 7) // P5.7 -> powered externally
//#define PIN_LED1    (40) // P5.0 -> powered externally
#define PIN_LED2    (8 * 0 + 0) // PJ.0 -> burns energy-budget

#define I2C_SCL     (8 * 6 + 5) // P6.05
#define I2C_SDA     (8 * 6 + 4)
//#define RTC_INT     (8 * 7 + 3) // output of RTC, not controllable
#define MAX_INT     (8 * 1 + 5) // output of MAX-IC

#define C2C_CLK     (8 * 1 + 5)
#define C2C_CoPi    (8 * 2 + 0)
#define C2C_CiPo    (8 * 2 + 1)
#define C2C_PSel    (8 * 1 + 4)
#define C2C_GPIO    (8 * 0 + 2)

#define THRCTRL_H0  (8 * 1 + 3)
#define THRCTRL_H1  (8 * 3 + 3)
#define THRCTRL_L0  (8 * 6 + 2)
#define THRCTRL_L1  (8 * 7 + 0)

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
}; // except uart-tx

#define N_PINS  sizeof(pins) / sizeof(uint32_t)
#define N_GPIOS sizeof(gpios) / sizeof(uint32_t)
#define N_LEDS  sizeof(leds) / sizeof(uint32_t)
#define N_I2C   sizeof(i2c) / sizeof(uint32_t)
#define N_C2C   sizeof(c2c) / sizeof(uint32_t)
#define N_THR   sizeof(thr) / sizeof(uint32_t)
#define N_ALL   sizeof(all) / sizeof(uint32_t)

/* PLATFORM SPECIFIC CODE */

static inline void delay_cycles(const uint32_t cycles)
{
    for (uint32_t i = 0; i < cycles; i++) __no_operation();
}

static inline void delay_ms(const uint32_t time)
{
    /* assumptions:
       - boot with 5MHz / 128 = 39 kHz
       - above loop takes 2 clock-cycles
    */
    const uint32_t cycles = time * 33; // 16000; -> very slow without changes
    delay_cycles(cycles);
}

static void set_gpio_state(const uint32_t pin_num, const bool state)
{
    uint8_t bank = (pin_num >> 3u);
    uint8_t pin  = (pin_num & 0b111);
    if (bank > 8) return;

    if (state)
    {
        if (bank == 0) PJOUT |= 1u << pin;
        if (bank == 1) P1OUT |= 1u << pin;
        if (bank == 2) P2OUT |= 1u << pin;
        if (bank == 3) P3OUT |= 1u << pin;
        if (bank == 4) P4OUT |= 1u << pin;
        if (bank == 5) P5OUT |= 1u << pin;
        if (bank == 6) P6OUT |= 1u << pin;
        if (bank == 7) P7OUT |= 1u << pin;
        if (bank == 8) P8OUT |= 1u << pin;
    }
    else
    {
        if (bank == 0) PJOUT &= ~(1u << pin);
        if (bank == 1) P1OUT &= ~(1u << pin);
        if (bank == 2) P2OUT &= ~(1u << pin);
        if (bank == 3) P3OUT &= ~(1u << pin);
        if (bank == 4) P4OUT &= ~(1u << pin);
        if (bank == 5) P5OUT &= ~(1u << pin);
        if (bank == 6) P6OUT &= ~(1u << pin);
        if (bank == 7) P7OUT &= ~(1u << pin);
        if (bank == 8) P8OUT &= ~(1u << pin);
    }
}

static void set_gpio_dir(const uint32_t pin_num, const bool input)
{
    uint8_t bank = (pin_num >> 3u);
    uint8_t pin  = (pin_num & 0b111);
    if (bank > 8) return;

    if (input)
    {
        if (bank == 0) PJDIR &= ~(1u << pin);
        if (bank == 1) P1DIR &= ~(1u << pin);
        if (bank == 2) P2DIR &= ~(1u << pin);
        if (bank == 3) P3DIR &= ~(1u << pin);
        if (bank == 4) P4DIR &= ~(1u << pin);
        if (bank == 5) P5DIR &= ~(1u << pin);
        if (bank == 6) P6DIR &= ~(1u << pin);
        if (bank == 7) P7DIR &= ~(1u << pin);
        if (bank == 8) P8DIR &= ~(1u << pin);
    }
    else
    {
        if (bank == 0) PJDIR |= 1u << pin;
        if (bank == 1) P1DIR |= 1u << pin;
        if (bank == 2) P2DIR |= 1u << pin;
        if (bank == 3) P3DIR |= 1u << pin;
        if (bank == 4) P4DIR |= 1u << pin;
        if (bank == 5) P5DIR |= 1u << pin;
        if (bank == 6) P6DIR |= 1u << pin;
        if (bank == 7) P7DIR |= 1u << pin;
        if (bank == 8) P8DIR |= 1u << pin;
    }
}

static void set_gpio_out(const uint32_t pin_num, const bool enable)
{
    /* similar to nrf52-code */
    set_gpio_state(pin_num, 0);
    set_gpio_dir(pin_num, !enable);
}

static void gpio_init(void)
{
    /* set all to neutral state: input */
    PJOUT  = 0u;
    PJDIR  = 0x00;
    PJSEL0 = 0u;
    PJSEL1 = 0u;

    P1OUT  = 0u;
    P1DIR  = 0x00;
    P1SEL0 = 0u;
    P1SEL1 = 0u;

    P2OUT  = 0u;
    P2DIR  = 0x00;
    P2SEL0 = 0u;
    P2SEL1 = 0u;

    P3OUT  = 0u;
    P3DIR  = 0x00;
    P3SEL0 = 0u;
    P3SEL1 = 0u;

    P4OUT  = 0u;
    P4DIR  = 0x00;
    P4SEL0 = 0u;
    P4SEL1 = 0u;

    P5OUT  = 0u;
    P5DIR  = 0x00;
    P5SEL0 = 0u;
    P5SEL1 = 0u;

    P6OUT  = 0u;
    P6DIR  = 0x00;
    P6SEL0 = 0u;
    P6SEL1 = 0u;

    P7OUT  = 0u;
    P7DIR  = 0x00;
    P7SEL0 = 0u;
    P7SEL1 = 0u;

    P8OUT  = 0u;
    P8DIR  = 0x00;
    P8SEL0 = 0u;
    P8SEL1 = 0u;
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
    /* Stop watchdog */
    WDTCTL = WDTPW | WDTHOLD | WDTCNTCL;

    /* Apply the GPIO configuration */
    PM5CTL0 &= ~LOCKLPM5;

    /* TEST-CODE, mode: this MCU toggles, the other supervises & reports */
    gpio_init();
    delay_ms(2000);

    /* Switch on GPIO for 100ms in a row */
    toggle_gpio_one_high(leds, N_LEDS);

    /* run through all GPIO - to present them to the supervisor */
    toggle_gpio_one_high(all, N_ALL);

    /* Switch on LEDs for 100ms in a row (>=8 Reps, depending on node-id) */
    uint32_t rep_sum = SHEPHERD_NODE_ID ? SHEPHERD_NODE_ID >= 8 : 8;
    for (uint32_t reps = 0; reps < rep_sum; reps++) { toggle_gpio_one_high(leds, N_LEDS); }

    /* END OF TEST-CODE */

    /* Disable SVS */
    PMMCTL0_H = PMMPW_H; // PMM Password
    PMMCTL0_L &= ~SVSHE;

    /* turn off the PMM to allow for LPM4.5 */
    PMMCTL0_L |= PMMREGOFF; // set Flag to enter LPM4.5 with LPM4 request

    /* Wait in LPM4 until CS is high */
    __bis_SR_register(GIE + LPM4_bits);
}
