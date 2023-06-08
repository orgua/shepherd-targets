#ifndef __PERIPHERALS_H__
#define __PERIPHERALS_H__

#include "pt.h"
#include <stdint.h>

typedef pt_queue(char, 128) byte_queue_t;

/* Buffers the commands received on UART */
extern byte_queue_t q_cmds;
/* Buffers the rising edges observed on  */
extern byte_queue_t q_pin_edges;

void                _putchar(char character);
void                enter_low_power(void);
int                 uart_init(uint32_t pseltxd, uint32_t pselrxd);

int                 gpiote_init(unsigned int pins[], unsigned int n_pins);

int                 timer_init(void);
int                 timer_reset(void);
unsigned int        timer_now_us(void);


#endif /* __PERIPHERALS_H__ */
