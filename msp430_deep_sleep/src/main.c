#include <msp430.h>
#include <msp430fr5962.h>
#include <stdbool.h>
#include <stdint.h>

/*

LPM4: 600nA (SVS), 400nA (no SVS), wakeup time <10us
LPM4.5: 250nA (SVS), 45 nA (no SVS), wakeup time 250us (SVS), 400us (no SVS)

Steps to enter LPMx.5 -> described in slau367p chapter 1.4.3.1

*/

static void gpio_init(void)
{
    /* aim for lowest power consumption: gpio w/o function (Sel), unused=output, clear interrupt flag */
    P1OUT  = 0u;
    P1DIR  = ~(BIT4 | BIT5);
    P1SEL0 = 0u;
    P1SEL1 = 0u;
    P1IE   = 0u;
    P1IFG  = 0u;

    P2OUT  = 0u;
    P2DIR  = ~(BIT0 | BIT1 | BIT3 | BIT4 | BIT5 | BIT6);
    P2SEL0 = 0u;
    P2SEL1 = 0u;
    P2IE   = 0u;
    P2IFG  = 0u;

    P3OUT  = 0u;
    P3DIR  = ~(BIT6);
    P3SEL0 = 0u;
    P3SEL1 = 0u;
    P3IE   = 0u;
    P3IFG  = 0u;

    P4OUT  = 0u;
    P4DIR  = ~(BIT6);
    P4SEL0 = 0u;
    P4SEL1 = 0u;
    P4IE   = 0u;
    P4IFG  = 0u;

    P5OUT  = 0u;
    P5DIR  = ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT5);
    P5SEL0 = 0u;
    P5SEL1 = 0u;
    P5IE   = 0u;
    P5IFG  = 0u;

    P6OUT  = 0u;
    P6DIR  = ~(BIT4 | BIT5);
    P6SEL0 = 0u;
    P6SEL1 = 0u;
    P6IE   = 0u;
    P6IFG  = 0u;

    P7OUT  = 0u;
    P7DIR  = ~(BIT3);
    P7SEL0 = 0u;
    P7SEL1 = 0u;
    P7IE   = 0u;
    P7IFG  = 0u;

    P8OUT  = 0u;
    P8DIR  = 0xFF;
    P8SEL0 = 0u;
    P8SEL1 = 0u;
    P8IE   = 0u;
    P8IFG  = 0u;

    PJOUT  = 0u;
    PJDIR  = ~(BIT0 | BIT6);
    PJSEL0 = 0u;
    PJSEL1 = 0u;
    // PJIE = 0u;
    // PJIFG = 0u;
}


int main(void)
{
    /* Stop watchdog */
    WDTCTL = WDTPW | WDTHOLD | WDTCNTCL;

    /* Apply the GPIO configuration */
    PM5CTL0 &= ~LOCKLPM5;

    gpio_init();

    /* Disable SVS */
    PMMCTL0_H = PMMPW_H;
    PMMCTL0_L &= ~SVSHE;

    /* turn off the PMM to allow for LPM4.5 */
    PMMCTL0_L |= PMMREGOFF;

    /* Wait in LPM4 until CS is high */
    __bis_SR_register(GIE + LPM4_bits);
}
