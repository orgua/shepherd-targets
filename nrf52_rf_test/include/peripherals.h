#ifndef __PERIPHERALS_H__
#define __PERIPHERALS_H__

#include "nrf_power.h"
#include <stdint.h>

int                 timer_init(void);
int                 timer_reset(void);
unsigned int        timer_now_us(void);

#endif /* __PERIPHERALS_H__ */
