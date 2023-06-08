#ifndef __PERIPHERALS_H__
#define __PERIPHERALS_H__

#include "nrf_power.h"
#include "pt.h"
#include <stdint.h>

#define __RAMFUNC __attribute__((long_call, section(".ramfunctions")))

void                 _putchar(char character);
void                 enter_low_power(void);
int                  uart_init(uint32_t pseltxd);
int                  rtc_init(void);
int                  rtc_wait(unsigned int ticks);
unsigned int         rtc_now();
volatile pt_event_t *rtc_request_evt(unsigned int rtc_time);
int                  adc_init(float v_thr);
int                  gpiote_init(unsigned int trigger_pin);
int                  pofwarn_init(nrf_power_pof_thr_t pofwarn_thr);
int                  pofwarn_arm(void);

#endif /* __PERIPHERALS_H__ */
