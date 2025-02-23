#include <msp430.h>
#include <msp430fr5994.h>
#include <stdbool.h>
#include <stdint.h>

/*

LPM4: 600nA (SVS), 400nA (no SVS), wakeup time <10us
LPM4.5: 250nA (SVS), 45 nA (no SVS), wakeup time 250us (SVS), 400us (no SVS)

Steps to enter LPMx.5 -> described in slau367p chapter 1.4.3.1

*/

static void gpio_init(void)
{
    /* aim for lowest power consumption:
     * - gpio w/o function (Sel),
     * - unused=output, PxDIR 1b=Output
     * - clear interrupt flag
     * - FIX: P6.BIT5 as input (i2c.sda) drains 500uA (without PD-Resistor)
     * - improvement: support unconnected targets (without gpio-lines)
     *      - all inputs have now a pulldown-resistor activated,
     *      - sleep current rises from 19 to 21 nA (@3V) for the FRAM-Target
     * */
    /* THRCTRL.H0, C2C.CS, C2C.CLK */
    P1OUT  = 0u;
    P1DIR  = ~(BIT3 | BIT4 | BIT5);
    P1SEL0 = BIT3; /* analog input to disable input buffer */
    P1SEL1 = BIT3; /* analog input to disable input buffer */
    P1IE   = 0u;
    P1IFG  = 0u;
    P1REN  = BIT3 | BIT4 | BIT5;

    /* C2C.MOSI, C2C.MISO, D2, D3, D1, D0 */
    P2OUT  = 0u;
    P2DIR  = ~(BIT0 | BIT1 | BIT3 | BIT4 | BIT5 | BIT6);
    P2SEL0 = 0u;
    P2SEL1 = 0u;
    P2IE   = 0u;
    P2IFG  = 0u;
    P2REN  = BIT0 | BIT1 | BIT3 | BIT4 | BIT5 | BIT6;

    /* THRCTRL.H1, D5 */
    P3OUT  = 0u;
    P3DIR  = ~(BIT3 | BIT6);
    P3SEL0 = BIT3; /* analog input to disable input buffer */
    P3SEL1 = BIT3; /* analog input to disable input buffer */
    P3IE   = 0u;
    P3IFG  = 0u;
    P3REN  = BIT3 | BIT6;

    /* D4 */
    P4OUT  = 0u;
    P4DIR  = ~(BIT6);
    P4SEL0 = 0u;
    P4SEL1 = 0u;
    P4IE   = 0u;
    P4IFG  = 0u;
    P4REN  = BIT6;

    /* D10, D9, D8, D7, PWRGD_L, PWRGD_H, LED.0 */
    P5OUT  = 0u;
    P5DIR  = ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT7);
    P5SEL0 = 0u;
    P5SEL1 = 0u;
    P5IE   = 0u;
    P5IFG  = 0u;
    P5REN  = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT7;

    /* D11, D12, THRCTRL.L0, D13, SYS.SDA, SYS.SCL, D14, D15 */
    P6OUT  = 0u;
    P6DIR  = ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);
    P6SEL0 = 0u;
    P6SEL1 = 0u;
    P6IE   = 0u;
    P6IFG  = 0u;
    P6REN  = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;

    /* THRCTRL.L1, RTC.INT, VCAP_SENSE (without Resistor) */
    P7OUT  = 0u;
    P7DIR  = ~(BIT0 | BIT3 | BIT5);
    P7SEL0 = BIT5; /* analog input to disable input buffer */
    P7SEL1 = BIT5; /* analog input to disable input buffer */
    P7IE   = 0u;
    P7IFG  = 0u;
    P7REN  = BIT0 | BIT3;

    /* not routed to pins */
    P8OUT  = 0u;
    P8DIR  = 0xFF;
    P8SEL0 = 0u;
    P8SEL1 = 0u;
    P8IE   = 0u;
    P8IFG  = 0u;
    P8REN  = 0u;

    /* LED.2P, MAX.INT, C2C.GPIO, D6 */
    PJOUT  = 0u;
    PJDIR  = ~(BIT0 | BIT1 | BIT2 | BIT6);
    PJSEL0 = 0u;
    PJSEL1 = 0u;
    // PJIE = 0u;
    // PJIFG = 0u;
    PJREN  = BIT0 | BIT1 | BIT2 | BIT6;
}


int main(void)
{
    /* Stop watchdog */
    WDTCTL = WDTPW | WDTHOLD | WDTCNTCL;

    /* Apply the GPIO configuration */
    gpio_init();

    /* Disable SVS */
    PMMCTL0_H = PMMPW_H;
    PMMCTL0_L &= ~SVSHE;
    /* turn off the PMM to allow for LPM4.5 */
    PMMCTL0_L |= PMMREGOFF;

    /* clear & disable GIE */
    __bic_SR_register(GIE);

    /* ONLY PRECAUTION - reduce clock-speed */
    CSCTL0 = 0xA5 << 8;            // unlock clock system registers
    CSCTL1 = ~DCORSEL & DCOFSEL_0; // 1 MHz

    /* Sleep in LPM4.5 - LOOP is just a precaution */
    while (1)
    {
        PMMCTL0_H = PMMPW_H;
        PM5CTL0 &= ~LOCKLPM5;
        __bis_SR_register(LPM4_bits);
    }
}
