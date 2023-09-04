#ifndef __PERIPHERALS_H__
#define __PERIPHERALS_H__

#include "nrf_power.h"
#include <stdint.h>

#define __RAMFUNC __attribute__((long_call, section(".ramfunctions")))

void                 enter_low_power(void);

int                 timer_init(void);
int                 timer_reset(void);
unsigned int        timer_now_us(void);

#endif /* __PERIPHERALS_H__ */
