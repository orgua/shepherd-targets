#include <stdbool.h>
#include <stdint.h>

#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_power.h"

#include "peripherals.h"

int                 timer_init(void)
{
    NRF_TIMER0->MODE        = TIMER_MODE_MODE_Timer;
    /* prescaler 2^4 -> 1MHz */
    NRF_TIMER0->PRESCALER   = 4;
    NRF_TIMER0->BITMODE     = TIMER_BITMODE_BITMODE_32Bit;

    NRF_TIMER0->TASKS_CLEAR = 1;
    NRF_TIMER0->TASKS_START = 1;

    return 0;
}

int timer_reset(void)
{
    NRF_TIMER0->TASKS_CLEAR = 1;
    return 0;
}

unsigned int timer_now_us(void)
{
    NRF_TIMER0->TASKS_CAPTURE[0] = 1;
    return NRF_TIMER0->CC[0];
}

__RAMFUNC void             enter_low_power(void)
{
    __WFE();
    __SEV();
    __WFE();
}
