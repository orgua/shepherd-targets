#include "uart.h"
#include "printf.h"

#include <msp430.h>
#include <msp430fr5962.h>

int uart_init() {
  // Configure UART TX pin
  P2SEL1 |= BIT5;
  P2SEL0 &= ~BIT5;
  /* Hold in reset state */
  UCA1CTLW0 = UCSWRST;

  /* Configure for standard UART operation */
  UCA1CTLW0 = 0;

  /* 16MHz clock */
  UCA1CTLW0 |= UCSSEL__SMCLK;

  /* This should generate 115200 baudrate */
  UCA1BRW = 8;
  UCA1MCTLW = UCOS16_1 | (10 << 4) | (0xF7 << 8);

  /* Release */
  UCA1CTLW0 &= ~UCSWRST;
  return 0;
}

void _putchar(char c) {
  while (!(UCA1IFG & UCTXIFG)) {
  };
  UCA1TXBUF = c;
}

int uart_puts(char *buf) {
  char *ptr = buf;
  while (*ptr != '\0') {
    _putchar(*ptr);
    ptr++;
  }
  return 0;
}
