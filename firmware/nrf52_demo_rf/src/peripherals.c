#include <stdbool.h>
#include <stdint.h>

#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_power.h"
#include "nrf_saadc.h"
#include "nrf_uart.h"
#include "printf.h"

#include "app.h"
#include "peripherals.h"
#include "pt.h"

#define V_REF    0.6
#define G_ADC    (1.0 / 6)
#define ADC_BITS 10

static int16_t             adc_result;

static volatile pt_event_t rtc_evt = pt_event_init();

static unsigned int        gpiote_trigger_pin;

__RAMFUNC void             enter_low_power(void)
{
    __WFE();
    __SEV();
    __WFE();
}

int uart_init(uint32_t pseltxd)
{
    nrf_uart_configure(NRF_UART0, NRF_UART_PARITY_EXCLUDED, NRF_UART_HWFC_DISABLED);
    NRF_UART0->ENABLE   = 4UL;
    /* Setup TX pin only */
    NRF_UART0->PSEL.TXD = pseltxd;
    /* Disconnect RX pin */
    NRF_UART0->PSEL.RXD |= (1UL << 31);
    nrf_uart_baudrate_set(NRF_UART0, NRF_UART_BAUDRATE_115200);
    return 0;
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

__RAMFUNC int pofwarn_init(nrf_power_pof_thr_t pofwarn_thr)
{

    NRF_POWER->POFCON = (pofwarn_thr << 1);
    NVIC_ClearPendingIRQ(POWER_CLOCK_IRQn);
    NRF_POWER->INTENSET = POWER_INTENSET_POFWARN_Msk;
    NVIC_EnableIRQ(POWER_CLOCK_IRQn);
    return 0;
}

int pofwarn_arm(void)
{
    NRF_POWER->EVENTS_POFWARN = 0;
    NRF_POWER->POFCON |= (1 << 0);
    return 0;
}

void POWER_CLOCK_IRQHandler(void)
{
    if (NRF_POWER->EVENTS_POFWARN == 1)
    {
        NRF_POWER->EVENTS_POFWARN = 0;
        pt_event_set(&evt_off);

        NRF_POWER->POFCON &= ~(1 << 0);
    }
}

int gpiote_init(unsigned int trigger_pin)
{

    gpiote_trigger_pin = trigger_pin;
    nrf_gpio_cfg_sense_input(gpiote_trigger_pin, NRF_GPIO_PIN_PULLDOWN, GPIO_PIN_CNF_SENSE_High);
    NRF_GPIOTE->EVENTS_PORT = 0;
    NRF_GPIOTE->INTENSET    = GPIOTE_INTENSET_PORT_Msk;
    NVIC_EnableIRQ(GPIOTE_IRQn);
    return 0;
}

__RAMFUNC void GPIOTE_IRQHandler(void)
{

    if (NRF_GPIOTE->EVENTS_PORT == 1)
    {
        if ((NRF_P0->PIN_CNF[gpiote_trigger_pin] >> GPIO_PIN_CNF_SENSE_Pos) ==
            GPIO_PIN_CNF_SENSE_High)
        {
            pt_event_set(&evt_on);
            NRF_P0->PIN_CNF[gpiote_trigger_pin] |=
                    (GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos);
        }
        else
        {
            pt_event_set(&evt_off);
            NRF_P0->PIN_CNF[gpiote_trigger_pin] &= ~GPIO_PIN_CNF_SENSE_Msk;
            NRF_P0->PIN_CNF[gpiote_trigger_pin] |=
                    (GPIO_PIN_CNF_SENSE_High << GPIO_PIN_CNF_SENSE_Pos);
        }
        NRF_GPIOTE->EVENTS_PORT = 0;
    }
}
int rtc_init(void)
{

    NRF_RTC0->TASKS_CLEAR = 1;
    /* 32768/327 ~ 100 Hz frequency */
    NRF_RTC0->CC[0]       = 327;
    NRF_RTC0->TASKS_START = 1;

    NRF_RTC0->EVTENSET    = RTC_EVTENSET_COMPARE0_Msk;
    NRF_PPI->CH[0].EEP    = (uint32_t) &NRF_RTC0->EVENTS_COMPARE[0];
    NRF_PPI->CH[0].TEP    = (uint32_t) &NRF_RTC0->TASKS_CLEAR;
    NRF_PPI->CHENSET      = PPI_CHENSET_CH0_Msk;

    return 0;
}

int rtc_wait(unsigned int ticks)
{
    unsigned int wkup = rtc_now() + ticks;
    if (wkup > NRF_RTC0->CC[0]) rtc_request_evt(wkup - NRF_RTC0->CC[0]);
    else rtc_request_evt(wkup);

    while (!pt_event_get(&rtc_evt)) { enter_low_power(); };
    pt_event_clear(&rtc_evt);
    return 0;
}

unsigned int         rtc_now() { return NRF_RTC0->COUNTER; }

volatile pt_event_t *rtc_request_evt(unsigned int rtc_time)
{
    NRF_RTC0->CC[1]    = rtc_time;
    NRF_RTC0->EVTENSET = RTC_EVTENSET_COMPARE1_Msk;
    NRF_RTC0->INTENSET = RTC_INTENSET_COMPARE1_Msk;
    NVIC_EnableIRQ(RTC0_IRQn);
    pt_event_clear(&rtc_evt);
    return &rtc_evt;
}

__RAMFUNC void RTC0_IRQHandler(void)
{
    if (NRF_RTC0->EVENTS_COMPARE[1] == 1)
    {
        NRF_RTC0->EVENTS_COMPARE[1] = 0;
        NRF_RTC0->EVTENCLR          = RTC_EVTENCLR_COMPARE1_Msk;
        NRF_RTC0->INTENCLR          = RTC_INTENCLR_COMPARE1_Msk;
        NVIC_DisableIRQ(RTC0_IRQn);
        pt_event_set(&rtc_evt);
    }
}

int adc_init(float v_thr)
{
    NRF_SAADC->CH[0].CONFIG = (SAADC_CH_CONFIG_RESN_Bypass << SAADC_CH_CONFIG_RESN_Pos) |
                              (SAADC_CH_CONFIG_RESP_Bypass << SAADC_CH_CONFIG_RESP_Pos) |
                              (SAADC_CH_CONFIG_GAIN_Gain1_6 << SAADC_CH_CONFIG_GAIN_Pos) |
                              (SAADC_CH_CONFIG_REFSEL_Internal << SAADC_CH_CONFIG_REFSEL_Pos) |
                              (SAADC_CH_CONFIG_TACQ_3us << SAADC_CH_CONFIG_TACQ_Pos) |
                              (SAADC_CH_CONFIG_MODE_SE << SAADC_CH_CONFIG_MODE_Pos) |
                              (SAADC_CH_CONFIG_BURST_Enabled << SAADC_CH_CONFIG_BURST_Pos);

    NRF_SAADC->CH[0].PSELP   = SAADC_CH_PSELP_PSELP_VDD;

    NRF_SAADC->RESOLUTION    = SAADC_RESOLUTION_VAL_10bit;
    NRF_SAADC->OVERSAMPLE    = SAADC_OVERSAMPLE_OVERSAMPLE_Bypass;

    NRF_SAADC->RESULT.PTR    = (uint32_t) &adc_result;
    NRF_SAADC->RESULT.MAXCNT = 1;

    NRF_SAADC->ENABLE        = SAADC_ENABLE_ENABLE_Enabled;

    /* Trigger ADC start on RTC wraparound */
    NRF_PPI->CH[1].EEP       = (uint32_t) &NRF_RTC0->EVENTS_COMPARE[0];
    NRF_PPI->CH[1].TEP       = (uint32_t) &NRF_SAADC->TASKS_START;
    NRF_PPI->CHENSET         = PPI_CHENSET_CH1_Msk;

    /* Take sample right after starting ADC */
    NRF_PPI->CH[2].EEP       = (uint32_t) &NRF_SAADC->EVENTS_STARTED;
    NRF_PPI->CH[2].TEP       = (uint32_t) &NRF_SAADC->TASKS_SAMPLE;
    NRF_PPI->CHENSET         = PPI_CHENSET_CH2_Msk;

    /* Immediately stop ADC after conversion is done */
    NRF_PPI->CH[3].EEP       = (uint32_t) &NRF_SAADC->EVENTS_END;
    NRF_PPI->CH[3].TEP       = (uint32_t) &NRF_SAADC->TASKS_STOP;
    NRF_PPI->CHENSET         = PPI_CHENSET_CH3_Msk;

    NRF_SAADC->CH[0].LIMIT   = ((int16_t) (v_thr * G_ADC / V_REF * (float) (1 << ADC_BITS)))
                             << SAADC_CH_LIMIT_HIGH_Pos;

    NRF_SAADC->INTENSET = SAADC_INTENSET_CH0LIMITH_Msk;
    NVIC_EnableIRQ(SAADC_IRQn);

    rtc_init();
    return 0;
}

__RAMFUNC void SAADC_IRQHandler(void)
{
    if (NRF_SAADC->EVENTS_CH[0].LIMITH == 1)
    {
        NRF_SAADC->EVENTS_CH[0].LIMITH = 0;
        pt_event_set(&evt_on);
    }
}
