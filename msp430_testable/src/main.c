#include <msp430.h>
#include <msp430fr5962.h>
#include <stdbool.h>
#include <stdint.h>

// see shepherd_node_id.c for details
extern const uint16_t SHEPHERD_NODE_ID;

/*
    MSP430 Pin-Name to int-Conversion:
    - Port J = 0, Port 1-8 stay same
    - Num = Port * 8 + Port.Pin
    - example: P5.5 becomes 5*8+5 = 45
 */

#define PIN_UART_TX 21 // P2.5
#define PIN_UART_RX 22 // P2.6
#define PIN_LED0    41 // P5.1 -> powered externally
#define PIN_LED1    40 // P5.0 -> powered externally
#define PIN_LED2    0  // PJ.0 -> burns energy-budget

// with reference to names of shepherd target-port
unsigned int pins[]  = {43, 42, 19, 20, 38, 30, 6, 22, 45}; // without uart-tx
unsigned int gpios[] = {43, 42, 19, 20, 38, 30, 6, 21, 22, 45};

unsigned int leds[]  = {PIN_LED0, PIN_LED1, PIN_LED2};
unsigned int i2c[]   = {53, 52, 59};
unsigned int c2c[]   = {13, 16, 17, 12, 2};

#define N_PINS  sizeof(pins) / sizeof(unsigned int)
#define N_GPIOS sizeof(gpios) / sizeof(unsigned int)
#define N_LEDS  sizeof(leds) / sizeof(unsigned int)
#define N_I2C   sizeof(i2c) / sizeof(unsigned int)
#define N_C2C   sizeof(c2c) / sizeof(unsigned int)

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
    const uint32_t cycles = time * 18; // 16000; -> very slow without changes
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
    PJOUT  = 0u;
    PJDIR  = 0xFF;
    PJSEL0 = 0u;
    PJSEL1 = 0u;

    P1OUT  = 0u;
    P1DIR  = 0xFF;
    P1SEL0 = 0u;
    P1SEL1 = 0u;

    P2OUT  = 0u;
    P2DIR  = 0xFF;
    P2SEL0 = 0u;
    P2SEL1 = 0u;

    P3OUT  = 0u;
    P3DIR  = 0xFF;
    P3SEL0 = 0u;
    P3SEL1 = 0u;

    P4OUT  = 0u;
    P4DIR  = 0xFF;
    P4SEL0 = 0u;
    P4SEL1 = 0u;

    P5OUT  = 0u;
    P5DIR  = 0xFF;
    P5SEL0 = 0u;
    P5SEL1 = 0u;

    P6OUT  = 0u;
    P6DIR  = 0xFF;
    P6SEL0 = 0u;
    P6SEL1 = 0u;

    P7OUT  = 0u;
    P7DIR  = 0xFF;
    P7SEL0 = 0u;
    P7SEL1 = 0u;

    P8OUT  = 0u;
    P8DIR  = 0xFF;
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
    delay_ms(1000);

    /* Switch on GPIO for 100ms in a row */
    toggle_gpio_one_high(leds, N_LEDS);

    toggle_gpio_one_high(pins, N_PINS);
    toggle_gpio_one_high(i2c, N_I2C);
    toggle_gpio_one_high(c2c, N_C2C);

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
