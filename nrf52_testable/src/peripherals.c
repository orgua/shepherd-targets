#include <stdbool.h>
#include <stdint.h>

#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"
#include "nrf_uart.h"
#include "printf.h"

#include "peripherals.h"
#include "pt.h"

byte_queue_t        q_cmds      = pt_queue_init();
byte_queue_t        q_pin_edges = pt_queue_init();

static unsigned int n_gpio_pins;

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

int uart_init(uint32_t pseltxd, uint32_t pselrxd)
{
    nrf_uart_configure(NRF_UART0, NRF_UART_PARITY_EXCLUDED, NRF_UART_HWFC_DISABLED);
    NRF_UART0->ENABLE   = 4UL;
    NRF_UART0->PSEL.TXD = pseltxd;
    NRF_UART0->PSEL.RXD = pselrxd;
    nrf_uart_baudrate_set(NRF_UART0, NRF_UART_BAUDRATE_115200);

    NRF_UART0->INTENSET = UARTE_INTENSET_RXDRDY_Msk;
    NVIC_EnableIRQ(UARTE0_UART0_IRQn);
    NRF_UART0->TASKS_STARTRX = 1;
    return 0;
}

void UARTE0_UART0_IRQHandler(void)
{
    if (NRF_UART0->EVENTS_RXDRDY == 1)
    {
        NRF_UART0->EVENTS_RXDRDY = 0;
        pt_queue_push(&q_cmds, NRF_UART0->RXD);
    }
}

void _putchar(char character)
{
    NRF_UART0->TXD           = character;
    NRF_UART0->EVENTS_TXDRDY = 0;
    NRF_UART0->TASKS_STARTTX = 1UL;
    while (NRF_UART0->EVENTS_TXDRDY == 0) {};
    NRF_UART0->EVENTS_TXDRDY = 0;
    NRF_UART0->TASKS_STOPTX  = 1UL;
}

int gpiote_init(const uint32_t pins[], uint8_t n_pins)
{
    n_gpio_pins = n_pins;
    for (uint8_t i = 0; i < n_pins; i++)
    {
        nrf_gpio_cfg_input(pins[i], NRF_GPIO_PIN_NOPULL);
        nrf_gpiote_event_configure(i, pins[i], NRF_GPIOTE_POLARITY_LOTOHI);
        nrf_gpiote_event_enable(i);
        nrf_gpiote_event_clear(i);
    }
    NRF_GPIOTE->INTENSET = 0xFF;

    NVIC_EnableIRQ(GPIOTE_IRQn);
    return 0;
}

void GPIOTE_IRQHandler(void)
{
    uint8_t i;
    for (i = 0; i < n_gpio_pins; i++)
    {
        if (NRF_GPIOTE->EVENTS_IN[i] == 1)
        {
            NRF_GPIOTE->EVENTS_IN[i] = 0;
            pt_queue_push(&q_pin_edges, i);
        }
    }
}
