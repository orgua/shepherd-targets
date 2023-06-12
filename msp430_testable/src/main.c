#include <msp430.h>
#include <msp430fr5962.h>
#include <stdbool.h>
#include <stdint.h>

static inline void delay_cycles(const uint32_t cycles)
{
    for (uint32_t i = 0; i < cycles; i++) __no_operation();
}

static inline void delay_ms(const uint32_t time)
{
    const uint32_t cycles = time * 16000;
    delay_cycles(cycles);
}

static void gpio_init(void)
{
    /* To save energy, all non-shared GPIOs are put to a defined state */

    /* Exclude [THRCTRL.H0], C2C.CS, C2C. CLK */
    P1OUT  = 0x0;
    P1DIR  = ~(BIT4 | BIT5);
    P1SEL0 = 0u;
    P1SEL1 = 0u;

    /* Exclude C2C.MOSI, C2C.MISO, D2, D3, D1, D0 */
    P2OUT  = 0;
    P2DIR  = ~(BIT0 | BIT1 | BIT3 | BIT4 | BIT5 | BIT6);
    P2SEL0 = 0u;
    P2SEL1 = 0u;

    /* Exclude [THRCTRL.H1], D5 */
    P3OUT  = 0u;
    P3DIR  = ~(BIT6);
    P3SEL0 = 0u;
    P3SEL1 = 0u;

    /* Exclude D4 */
    P4OUT  = 0;
    P4DIR  = ~(BIT6);
    P4SEL0 = 0x0;
    P4SEL1 = 0x0;

    /* Exclude D10, D9, D8, D7, [PWRGD_L], PWRGD_H  */
    P5OUT  = 0;
    P5DIR  = ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT5);
    P5SEL0 = 0x0;
    P5SEL1 = 0x0;

    /* Exclude [THRCTRL.L0], SYS.SDA, SYS.SCL */
    P6OUT  = 0;
    P6DIR  = ~(BIT4 | BIT5);
    P6SEL0 = 0x0;
    P6SEL1 = 0x0;

    /* Exclude [THRCTRL.L1], RTC_INT, [VCAP_SENSE] */
    P7OUT  = 0;
    P7DIR  = ~(BIT3);
    P7SEL0 = 0u;
    P7SEL1 = 0u;

    P8OUT  = 0;
    P8DIR  = 0xFF;
    P8SEL0 = 0x0;
    P8SEL1 = 0x0;

    PJOUT  = 0;
    /* Exclude LED_CTRL, [MAX_INT],  D6, Take control of C2C.GPIO */
    PJDIR  = ~(BIT0 | BIT6);
    PJSEL0 = 0x0;
    PJSEL1 = 0x0;
}

static void gpio_ext_out(const bool enable)
{
    if (enable)
    {
        P2DIR &= ~(BIT3 | BIT4 | BIT5 | BIT6);
        P3DIR &= ~(BIT6);
        P4DIR &= ~(BIT6);
        P5DIR &= ~(BIT2 | BIT3);
        PJDIR &= ~(BIT6);
    }
    else
    {
        P2DIR |= (BIT3 | BIT4 | BIT5 | BIT6);
        P3DIR |= (BIT6);
        P4DIR |= (BIT6);
        P5DIR |= (BIT2 | BIT3);
        PJDIR |= (BIT6);
    }
}

static void gpio_ext_ctrl(const uint32_t mask)
{
    if (mask & BIT0) P2OUT |= BIT6;
    else P2OUT &= ~BIT6;

    if (mask & BIT1) P2OUT |= BIT5;
    else P2OUT &= ~BIT5;

    if (mask & BIT2) P2OUT |= BIT3;
    else P2OUT &= ~BIT3;

    if (mask & BIT3) P2OUT |= BIT4;
    else P2OUT &= ~BIT4;

    if (mask & BIT4) P4OUT |= BIT6;
    else P4OUT &= ~BIT6;

    if (mask & BIT5) P3OUT |= BIT6;
    else P3OUT &= ~BIT6;

    if (mask & BIT6) PJOUT |= BIT6;
    else PJOUT &= ~BIT6;

    if (mask & BIT7) P5OUT |= BIT3;
    else P5OUT &= ~BIT3;

    if (mask & BIT8) P5OUT |= BIT2;
    else P5OUT &= ~BIT2;

    //if (mask & BIT9) P5OUT |= BIT5;
    //else P5OUT &= ~BIT5;
}

static void gpio_led_out(const bool enable)
{
    if (enable)
    {
        P5DIR &= ~(BIT0 | BIT1);
        PJDIR &= ~(BIT0);
    }
    else
    {
        P5DIR |= (BIT0 | BIT1);
        PJDIR |= (BIT0);
    }
}

static void gpio_led_ctrl(const uint32_t mask)
{
    if (mask & BIT0) P5OUT |= BIT1;
    else P5OUT &= ~BIT1;

    if (mask & BIT1) P5OUT |= BIT0;
    else P5OUT &= ~BIT0;

    if (mask & BIT2) PJOUT |= BIT0;
    else PJOUT &= ~BIT0;
}


int main(void)
{
    /* Stop watchdog */
    WDTCTL = WDTPW | WDTHOLD | WDTCNTCL;

    /* Apply the GPIO configuration */
    PM5CTL0 &= ~LOCKLPM5;

    gpio_init();

    gpio_led_out(true);
    for (uint8_t reps = 0; reps < 16; reps++)
    {
        for (uint8_t led_mask = BIT1; led_mask < BIT4; led_mask <<= 1u)
        {
            gpio_led_ctrl(led_mask);
            delay_ms(100);
        }
        gpio_led_ctrl(0);
    }
    gpio_led_out(false);

    gpio_ext_out(true);
    for (uint8_t reps = 0; reps < 4; reps++)
    {
        for (uint8_t ext_mask = BIT1; ext_mask < BITA; ext_mask <<= 1u)
        {
            gpio_ext_ctrl(ext_mask);
            delay_ms(100);
        }
        gpio_ext_ctrl(0);
    }
    gpio_ext_out(false);

    // TODO: enable and use UART

    /* Disable SVS */
    PMMCTL0_H = PMMPW_H; // PMM Password
    PMMCTL0_L &= ~SVSHE;

    /* turn off the PMM to allow for LPM4.5 */
    PMMCTL0_L |= PMMREGOFF; // set Flag to enter LPM4.5 with LPM4 request


    /* Wait in LPM4 until CS is high */
    __bis_SR_register(GIE + LPM4_bits);
}
