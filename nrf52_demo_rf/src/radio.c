#include "nrf52840.h"
#include "nrf52840_bitfields.h"

#include "nrf_ppi.h"
#include "nrf_radio.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "peripherals.h"
#include "pt.h"
#include "radio.h"

/* Bluetooth Core Spec 5.2 Section 2.1.2 */
#define ADV_CHANNEL_AA 0x8E89BED6

static pt_event_t radio_evt;

static __inline int8_t ch2freq(uint8_t ch) {
  switch (ch) {
  case 37:
    return 2;
  case 38:
    return 26;
  case 39:
    return 80;
  default:
    if (ch > 39)
      return -1;
    else if (ch < 11)
      return 4 + (2 * ch);
    else
      return 6 + (2 * ch);
  }
}

int radio_prepare_adv(adv_pck_t *pkt, ble_ll_addr_t *adv_addr,
                      unsigned int len) {
  pkt->header.pdu_type = ADV_NONCONN_IND;
  pkt->header.txadd = 1;
  pkt->header.len = len;
  memcpy((char *)&pkt->adv_addr.addr_bytes, (char *)adv_addr->addr_bytes, 6);
  return 0;
}

__RAMFUNC pt_event_t *radio_send(adv_pck_t *pkt, uint8_t ch) {
  NRF_RADIO->FREQUENCY = ch2freq(ch);
  /* Whitening initialization see Bluetooth Core Spec 5.2 Section 3.2 */
  NRF_RADIO->DATAWHITEIV = ch & 0x3F;

  NRF_RADIO->PACKETPTR = (uint32_t)pkt;
  NRF_CLOCK->TASKS_HFCLKSTART = 1;
  pt_event_clear(&radio_evt);
  return &radio_evt;
}

__RAMFUNC void RADIO_IRQHandler(void) {
  if (NRF_RADIO->EVENTS_DISABLED == 1) {
    NRF_RADIO->EVENTS_DISABLED = 0;
    pt_event_set(&radio_evt);
  }
}
int radio_init() {
  /* 0dBm TX power */
  NRF_RADIO->TXPOWER =
      (RADIO_TXPOWER_TXPOWER_Pos4dBm << RADIO_TXPOWER_TXPOWER_Pos);

  /* BLE 2MBit */
  NRF_RADIO->MODE = (RADIO_MODE_MODE_Ble_1Mbit << RADIO_MODE_MODE_Pos);
  /* Fast radio rampup */
  NRF_RADIO->MODECNF0 = (RADIO_MODECNF0_RU_Fast << RADIO_MODECNF0_RU_Pos);

  /* Bluetooth Core Spec 5.2 Section 2.1.2 */
  NRF_RADIO->BASE0 = (ADV_CHANNEL_AA << 8) & 0xFFFFFF00;
  NRF_RADIO->PREFIX0 = (ADV_CHANNEL_AA >> 24) & RADIO_PREFIX0_AP0_Msk;

  /* Logical address 0 -> BASE0 + PREFIX.AP0 */
  NRF_RADIO->TXADDRESS = 0x00;

  /* Stores BLE header */
  NRF_RADIO->PCNF0 = (0UL << RADIO_PCNF0_S1LEN_Pos) |
                     (1UL << RADIO_PCNF0_S0LEN_Pos) |
                     (8UL << RADIO_PCNF0_LFLEN_Pos) |
                     (RADIO_PCNF0_PLEN_8bit << RADIO_PCNF0_PLEN_Pos);

  /* Data whitening, little endian, 3B base address */
  NRF_RADIO->PCNF1 = (RADIO_PCNF1_WHITEEN_Enabled << RADIO_PCNF1_WHITEEN_Pos) |
                     (RADIO_PCNF1_ENDIAN_Little << RADIO_PCNF1_ENDIAN_Pos) |
                     (3 << RADIO_PCNF1_BALEN_Pos) |
                     (0 << RADIO_PCNF1_STATLEN_Pos) |
                     (255 << RADIO_PCNF1_MAXLEN_Pos);

  /* For CRC settings see Bluetooth Core Spec 5.2 Section 3.1.1 */
  /* Three byte CRC, skip address */
  NRF_RADIO->CRCCNF = (RADIO_CRCCNF_LEN_Three << RADIO_CRCCNF_LEN_Pos) |
                      (RADIO_CRCCNF_SKIPADDR_Skip << RADIO_CRCCNF_SKIPADDR_Pos);

  /* Initial value */
  NRF_RADIO->CRCINIT = 0x555555;
  /* CRC poly: x^24 + x^10 + x^9 + x^6 + x^4 + x^3 + x + 1 */
  NRF_RADIO->CRCPOLY = 0x100065B;

  /* Set default shorts */
  NRF_RADIO->SHORTS =
      NRF_RADIO_SHORT_TXREADY_START_MASK | NRF_RADIO_SHORT_END_DISABLE_MASK;

  NRF_RADIO->INTENSET = RADIO_INTENSET_DISABLED_Msk;
  NVIC_EnableIRQ(RADIO_IRQn);

  NRF_PPI->CH[4].EEP = (uint32_t)&NRF_CLOCK->EVENTS_HFCLKSTARTED;
  NRF_PPI->CH[4].TEP = (uint32_t)&NRF_RADIO->TASKS_TXEN;

  NRF_PPI->CH[5].EEP = (uint32_t)&NRF_RADIO->EVENTS_DISABLED;
  NRF_PPI->CH[5].TEP = (uint32_t)&NRF_CLOCK->TASKS_HFCLKSTOP;

  NRF_PPI->CHENSET = PPI_CHEN_CH4_Msk | PPI_CHEN_CH5_Msk;

  return 0;
}
