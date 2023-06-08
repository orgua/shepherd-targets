/*

Copyright (c) 2010 - 2021, Nordic Semiconductor ASA

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form, except as embedded into a Nordic
   Semiconductor ASA integrated circuit in a product or a software update for
   such product, must reproduce the above copyright notice, this list of
   conditions and the following disclaimer in the documentation and/or other
   materials provided with the distribution.

3. Neither the name of Nordic Semiconductor ASA nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

4. This software, with or without modification, must only be used with a
   Nordic Semiconductor ASA integrated circuit.

5. Any software provided in binary form under this license must not be reverse
   engineered, decompiled, modified and/or disassembled.

THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef __NRF52820_BITS_H
#define __NRF52820_BITS_H

/*lint ++flb "Enter library region" */

/* Peripheral: AAR */
/* Description: Accelerated Address Resolver */

/* Register: AAR_TASKS_START */
/* Description: Start resolving addresses based on IRKs specified in the IRK data structure */

/* Bit 0 : Start resolving addresses based on IRKs specified in the IRK data structure */
#define AAR_TASKS_START_TASKS_START_Pos (0UL) /*!< Position of TASKS_START field. */
#define AAR_TASKS_START_TASKS_START_Msk                                                            \
  (0x1UL << AAR_TASKS_START_TASKS_START_Pos)      /*!< Bit mask of TASKS_START field. */
#define AAR_TASKS_START_TASKS_START_Trigger (1UL) /*!< Trigger task */

/* Register: AAR_TASKS_STOP */
/* Description: Stop resolving addresses */

/* Bit 0 : Stop resolving addresses */
#define AAR_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define AAR_TASKS_STOP_TASKS_STOP_Msk                                                              \
  (0x1UL << AAR_TASKS_STOP_TASKS_STOP_Pos)      /*!< Bit mask of TASKS_STOP field. */
#define AAR_TASKS_STOP_TASKS_STOP_Trigger (1UL) /*!< Trigger task */

/* Register: AAR_EVENTS_END */
/* Description: Address resolution procedure complete */

/* Bit 0 : Address resolution procedure complete */
#define AAR_EVENTS_END_EVENTS_END_Pos     (0UL) /*!< Position of EVENTS_END field. */
#define AAR_EVENTS_END_EVENTS_END_Msk                                                              \
  (0x1UL << AAR_EVENTS_END_EVENTS_END_Pos)            /*!< Bit mask of EVENTS_END field. */
#define AAR_EVENTS_END_EVENTS_END_NotGenerated  (0UL) /*!< Event not generated */
#define AAR_EVENTS_END_EVENTS_END_Generated     (1UL) /*!< Event generated */

/* Register: AAR_EVENTS_RESOLVED */
/* Description: Address resolved */

/* Bit 0 : Address resolved */
#define AAR_EVENTS_RESOLVED_EVENTS_RESOLVED_Pos (0UL) /*!< Position of EVENTS_RESOLVED field. */
#define AAR_EVENTS_RESOLVED_EVENTS_RESOLVED_Msk                                                    \
  (0x1UL << AAR_EVENTS_RESOLVED_EVENTS_RESOLVED_Pos) /*!< Bit mask of EVENTS_RESOLVED field. */
#define AAR_EVENTS_RESOLVED_EVENTS_RESOLVED_NotGenerated (0UL) /*!< Event not generated */
#define AAR_EVENTS_RESOLVED_EVENTS_RESOLVED_Generated    (1UL) /*!< Event generated */

/* Register: AAR_EVENTS_NOTRESOLVED */
/* Description: Address not resolved */

/* Bit 0 : Address not resolved */
#define AAR_EVENTS_NOTRESOLVED_EVENTS_NOTRESOLVED_Pos                                              \
  (0UL) /*!< Position of EVENTS_NOTRESOLVED field. */
#define AAR_EVENTS_NOTRESOLVED_EVENTS_NOTRESOLVED_Msk                                              \
  (0x1UL                                                                                           \
   << AAR_EVENTS_NOTRESOLVED_EVENTS_NOTRESOLVED_Pos) /*!< Bit mask of EVENTS_NOTRESOLVED field. */
#define AAR_EVENTS_NOTRESOLVED_EVENTS_NOTRESOLVED_NotGenerated (0UL) /*!< Event not generated */
#define AAR_EVENTS_NOTRESOLVED_EVENTS_NOTRESOLVED_Generated    (1UL) /*!< Event generated */

/* Register: AAR_INTENSET */
/* Description: Enable interrupt */

/* Bit 2 : Write '1' to enable interrupt for event NOTRESOLVED */
#define AAR_INTENSET_NOTRESOLVED_Pos                           (2UL) /*!< Position of NOTRESOLVED field. */
#define AAR_INTENSET_NOTRESOLVED_Msk                                                               \
  (0x1UL << AAR_INTENSET_NOTRESOLVED_Pos)       /*!< Bit mask of NOTRESOLVED field. */
#define AAR_INTENSET_NOTRESOLVED_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENSET_NOTRESOLVED_Enabled  (1UL) /*!< Read: Enabled */
#define AAR_INTENSET_NOTRESOLVED_Set      (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event RESOLVED */
#define AAR_INTENSET_RESOLVED_Pos         (1UL) /*!< Position of RESOLVED field. */
#define AAR_INTENSET_RESOLVED_Msk                                                                  \
  (0x1UL << AAR_INTENSET_RESOLVED_Pos)       /*!< Bit mask of RESOLVED field. */
#define AAR_INTENSET_RESOLVED_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENSET_RESOLVED_Enabled  (1UL) /*!< Read: Enabled */
#define AAR_INTENSET_RESOLVED_Set      (1UL) /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event END */
#define AAR_INTENSET_END_Pos           (0UL) /*!< Position of END field. */
#define AAR_INTENSET_END_Msk           (0x1UL << AAR_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define AAR_INTENSET_END_Disabled      (0UL)                           /*!< Read: Disabled */
#define AAR_INTENSET_END_Enabled       (1UL)                           /*!< Read: Enabled */
#define AAR_INTENSET_END_Set           (1UL)                           /*!< Enable */

/* Register: AAR_INTENCLR */
/* Description: Disable interrupt */

/* Bit 2 : Write '1' to disable interrupt for event NOTRESOLVED */
#define AAR_INTENCLR_NOTRESOLVED_Pos   (2UL) /*!< Position of NOTRESOLVED field. */
#define AAR_INTENCLR_NOTRESOLVED_Msk                                                               \
  (0x1UL << AAR_INTENCLR_NOTRESOLVED_Pos)       /*!< Bit mask of NOTRESOLVED field. */
#define AAR_INTENCLR_NOTRESOLVED_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENCLR_NOTRESOLVED_Enabled  (1UL) /*!< Read: Enabled */
#define AAR_INTENCLR_NOTRESOLVED_Clear    (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event RESOLVED */
#define AAR_INTENCLR_RESOLVED_Pos         (1UL) /*!< Position of RESOLVED field. */
#define AAR_INTENCLR_RESOLVED_Msk                                                                  \
  (0x1UL << AAR_INTENCLR_RESOLVED_Pos)       /*!< Bit mask of RESOLVED field. */
#define AAR_INTENCLR_RESOLVED_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENCLR_RESOLVED_Enabled  (1UL) /*!< Read: Enabled */
#define AAR_INTENCLR_RESOLVED_Clear    (1UL) /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event END */
#define AAR_INTENCLR_END_Pos           (0UL) /*!< Position of END field. */
#define AAR_INTENCLR_END_Msk           (0x1UL << AAR_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define AAR_INTENCLR_END_Disabled      (0UL)                           /*!< Read: Disabled */
#define AAR_INTENCLR_END_Enabled       (1UL)                           /*!< Read: Enabled */
#define AAR_INTENCLR_END_Clear         (1UL)                           /*!< Disable */

/* Register: AAR_STATUS */
/* Description: Resolution status */

/* Bits 3..0 : The IRK that was used last time an address was resolved */
#define AAR_STATUS_STATUS_Pos          (0UL) /*!< Position of STATUS field. */
#define AAR_STATUS_STATUS_Msk          (0xFUL << AAR_STATUS_STATUS_Pos) /*!< Bit mask of STATUS field. */

/* Register: AAR_ENABLE */
/* Description: Enable AAR */

/* Bits 1..0 : Enable or disable AAR */
#define AAR_ENABLE_ENABLE_Pos          (0UL) /*!< Position of ENABLE field. */
#define AAR_ENABLE_ENABLE_Msk          (0x3UL << AAR_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define AAR_ENABLE_ENABLE_Disabled     (0UL)                            /*!< Disable */
#define AAR_ENABLE_ENABLE_Enabled      (3UL)                            /*!< Enable */

/* Register: AAR_NIRK */
/* Description: Number of IRKs */

/* Bits 4..0 : Number of Identity root keys available in the IRK data structure */
#define AAR_NIRK_NIRK_Pos              (0UL)                         /*!< Position of NIRK field. */
#define AAR_NIRK_NIRK_Msk              (0x1FUL << AAR_NIRK_NIRK_Pos) /*!< Bit mask of NIRK field. */

/* Register: AAR_IRKPTR */
/* Description: Pointer to IRK data structure */

/* Bits 31..0 : Pointer to the IRK data structure */
#define AAR_IRKPTR_IRKPTR_Pos          (0UL) /*!< Position of IRKPTR field. */
#define AAR_IRKPTR_IRKPTR_Msk                                                                      \
  (0xFFFFFFFFUL << AAR_IRKPTR_IRKPTR_Pos) /*!< Bit mask of IRKPTR field. */

/* Register: AAR_ADDRPTR */
/* Description: Pointer to the resolvable address */

/* Bits 31..0 : Pointer to the resolvable address (6-bytes) */
#define AAR_ADDRPTR_ADDRPTR_Pos (0UL) /*!< Position of ADDRPTR field. */
#define AAR_ADDRPTR_ADDRPTR_Msk                                                                    \
  (0xFFFFFFFFUL << AAR_ADDRPTR_ADDRPTR_Pos) /*!< Bit mask of ADDRPTR field. */

/* Register: AAR_SCRATCHPTR */
/* Description: Pointer to data area used for temporary storage */

/* Bits 31..0 : Pointer to a scratch data area used for temporary storage during resolution. A space of minimum 3 bytes must be reserved. */
#define AAR_SCRATCHPTR_SCRATCHPTR_Pos (0UL) /*!< Position of SCRATCHPTR field. */
#define AAR_SCRATCHPTR_SCRATCHPTR_Msk                                                              \
  (0xFFFFFFFFUL << AAR_SCRATCHPTR_SCRATCHPTR_Pos) /*!< Bit mask of SCRATCHPTR field. */


/* Peripheral: ACL */
/* Description: Access control lists */

/* Register: ACL_ACL_ADDR */
/* Description: Description cluster: Start address of region to protect. The start address must be word-aligned. */

/* Bits 31..0 : Start address of flash region n. The start address must point to a flash page boundary. */
#define ACL_ACL_ADDR_ADDR_Pos (0UL) /*!< Position of ADDR field. */
#define ACL_ACL_ADDR_ADDR_Msk                                                                      \
  (0xFFFFFFFFUL << ACL_ACL_ADDR_ADDR_Pos) /*!< Bit mask of ADDR field. */

/* Register: ACL_ACL_SIZE */
/* Description: Description cluster: Size of region to protect counting from address ACL[n].ADDR. Write '0' as no effect. */

/* Bits 31..0 : Size of flash region n in bytes. Must be a multiple of the flash page size. */
#define ACL_ACL_SIZE_SIZE_Pos (0UL) /*!< Position of SIZE field. */
#define ACL_ACL_SIZE_SIZE_Msk                                                                      \
  (0xFFFFFFFFUL << ACL_ACL_SIZE_SIZE_Pos) /*!< Bit mask of SIZE field. */

/* Register: ACL_ACL_PERM */
/* Description: Description cluster: Access permissions for region n as defined by start address ACL[n].ADDR and size ACL[n].SIZE */

/* Bit 2 : Configure read permissions for region n. Write '0' has no effect. */
#define ACL_ACL_PERM_READ_Pos           (2UL) /*!< Position of READ field. */
#define ACL_ACL_PERM_READ_Msk           (0x1UL << ACL_ACL_PERM_READ_Pos) /*!< Bit mask of READ field. */
#define ACL_ACL_PERM_READ_Enable        (0UL) /*!< Allow read instructions to region n */
#define ACL_ACL_PERM_READ_Disable       (1UL) /*!< Block read instructions to region n */

/* Bit 1 : Configure write and erase permissions for region n. Write '0' has no effect. */
#define ACL_ACL_PERM_WRITE_Pos          (1UL) /*!< Position of WRITE field. */
#define ACL_ACL_PERM_WRITE_Msk          (0x1UL << ACL_ACL_PERM_WRITE_Pos) /*!< Bit mask of WRITE field. */
#define ACL_ACL_PERM_WRITE_Enable       (0UL) /*!< Allow write and erase instructions to region n */
#define ACL_ACL_PERM_WRITE_Disable      (1UL) /*!< Block write and erase instructions to region n */


/* Peripheral: CCM */
/* Description: AES CCM Mode Encryption */

/* Register: CCM_TASKS_KSGEN */
/* Description: Start generation of key-stream. This operation will stop by itself when completed. */

/* Bit 0 : Start generation of key-stream. This operation will stop by itself when completed. */
#define CCM_TASKS_KSGEN_TASKS_KSGEN_Pos (0UL) /*!< Position of TASKS_KSGEN field. */
#define CCM_TASKS_KSGEN_TASKS_KSGEN_Msk                                                            \
  (0x1UL << CCM_TASKS_KSGEN_TASKS_KSGEN_Pos)      /*!< Bit mask of TASKS_KSGEN field. */
#define CCM_TASKS_KSGEN_TASKS_KSGEN_Trigger (1UL) /*!< Trigger task */

/* Register: CCM_TASKS_CRYPT */
/* Description: Start encryption/decryption. This operation will stop by itself when completed. */

/* Bit 0 : Start encryption/decryption. This operation will stop by itself when completed. */
#define CCM_TASKS_CRYPT_TASKS_CRYPT_Pos     (0UL) /*!< Position of TASKS_CRYPT field. */
#define CCM_TASKS_CRYPT_TASKS_CRYPT_Msk                                                            \
  (0x1UL << CCM_TASKS_CRYPT_TASKS_CRYPT_Pos)      /*!< Bit mask of TASKS_CRYPT field. */
#define CCM_TASKS_CRYPT_TASKS_CRYPT_Trigger (1UL) /*!< Trigger task */

/* Register: CCM_TASKS_STOP */
/* Description: Stop encryption/decryption */

/* Bit 0 : Stop encryption/decryption */
#define CCM_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define CCM_TASKS_STOP_TASKS_STOP_Msk                                                              \
  (0x1UL << CCM_TASKS_STOP_TASKS_STOP_Pos)      /*!< Bit mask of TASKS_STOP field. */
#define CCM_TASKS_STOP_TASKS_STOP_Trigger (1UL) /*!< Trigger task */

/* Register: CCM_TASKS_RATEOVERRIDE */
/* Description: Override DATARATE setting in MODE register with the contents of the RATEOVERRIDE register for any ongoing encryption/decryption */

/* Bit 0 : Override DATARATE setting in MODE register with the contents of the RATEOVERRIDE register for any ongoing encryption/decryption */
#define CCM_TASKS_RATEOVERRIDE_TASKS_RATEOVERRIDE_Pos                                              \
  (0UL) /*!< Position of TASKS_RATEOVERRIDE field. */
#define CCM_TASKS_RATEOVERRIDE_TASKS_RATEOVERRIDE_Msk                                              \
  (0x1UL                                                                                           \
   << CCM_TASKS_RATEOVERRIDE_TASKS_RATEOVERRIDE_Pos) /*!< Bit mask of TASKS_RATEOVERRIDE field. */
#define CCM_TASKS_RATEOVERRIDE_TASKS_RATEOVERRIDE_Trigger (1UL) /*!< Trigger task */

/* Register: CCM_EVENTS_ENDKSGEN */
/* Description: Key-stream generation complete */

/* Bit 0 : Key-stream generation complete */
#define CCM_EVENTS_ENDKSGEN_EVENTS_ENDKSGEN_Pos           (0UL) /*!< Position of EVENTS_ENDKSGEN field. */
#define CCM_EVENTS_ENDKSGEN_EVENTS_ENDKSGEN_Msk                                                    \
  (0x1UL << CCM_EVENTS_ENDKSGEN_EVENTS_ENDKSGEN_Pos) /*!< Bit mask of EVENTS_ENDKSGEN field. */
#define CCM_EVENTS_ENDKSGEN_EVENTS_ENDKSGEN_NotGenerated (0UL) /*!< Event not generated */
#define CCM_EVENTS_ENDKSGEN_EVENTS_ENDKSGEN_Generated    (1UL) /*!< Event generated */

/* Register: CCM_EVENTS_ENDCRYPT */
/* Description: Encrypt/decrypt complete */

/* Bit 0 : Encrypt/decrypt complete */
#define CCM_EVENTS_ENDCRYPT_EVENTS_ENDCRYPT_Pos          (0UL) /*!< Position of EVENTS_ENDCRYPT field. */
#define CCM_EVENTS_ENDCRYPT_EVENTS_ENDCRYPT_Msk                                                    \
  (0x1UL << CCM_EVENTS_ENDCRYPT_EVENTS_ENDCRYPT_Pos) /*!< Bit mask of EVENTS_ENDCRYPT field. */
#define CCM_EVENTS_ENDCRYPT_EVENTS_ENDCRYPT_NotGenerated (0UL) /*!< Event not generated */
#define CCM_EVENTS_ENDCRYPT_EVENTS_ENDCRYPT_Generated    (1UL) /*!< Event generated */

/* Register: CCM_EVENTS_ERROR */
/* Description: Deprecated register - CCM error event */

/* Bit 0 : Deprecated field -  CCM error event */
#define CCM_EVENTS_ERROR_EVENTS_ERROR_Pos                (0UL) /*!< Position of EVENTS_ERROR field. */
#define CCM_EVENTS_ERROR_EVENTS_ERROR_Msk                                                          \
  (0x1UL << CCM_EVENTS_ERROR_EVENTS_ERROR_Pos)           /*!< Bit mask of EVENTS_ERROR field. */
#define CCM_EVENTS_ERROR_EVENTS_ERROR_NotGenerated (0UL) /*!< Event not generated */
#define CCM_EVENTS_ERROR_EVENTS_ERROR_Generated    (1UL) /*!< Event generated */

/* Register: CCM_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 0 : Shortcut between event ENDKSGEN and task CRYPT */
#define CCM_SHORTS_ENDKSGEN_CRYPT_Pos              (0UL) /*!< Position of ENDKSGEN_CRYPT field. */
#define CCM_SHORTS_ENDKSGEN_CRYPT_Msk                                                              \
  (0x1UL << CCM_SHORTS_ENDKSGEN_CRYPT_Pos)       /*!< Bit mask of ENDKSGEN_CRYPT field. */
#define CCM_SHORTS_ENDKSGEN_CRYPT_Disabled (0UL) /*!< Disable shortcut */
#define CCM_SHORTS_ENDKSGEN_CRYPT_Enabled  (1UL) /*!< Enable shortcut */

/* Register: CCM_INTENSET */
/* Description: Enable interrupt */

/* Bit 2 : Deprecated intsetfield -  Write '1' to enable interrupt for event ERROR */
#define CCM_INTENSET_ERROR_Pos             (2UL) /*!< Position of ERROR field. */
#define CCM_INTENSET_ERROR_Msk             (0x1UL << CCM_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define CCM_INTENSET_ERROR_Disabled        (0UL)                             /*!< Read: Disabled */
#define CCM_INTENSET_ERROR_Enabled         (1UL)                             /*!< Read: Enabled */
#define CCM_INTENSET_ERROR_Set             (1UL)                             /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event ENDCRYPT */
#define CCM_INTENSET_ENDCRYPT_Pos          (1UL) /*!< Position of ENDCRYPT field. */
#define CCM_INTENSET_ENDCRYPT_Msk                                                                  \
  (0x1UL << CCM_INTENSET_ENDCRYPT_Pos)       /*!< Bit mask of ENDCRYPT field. */
#define CCM_INTENSET_ENDCRYPT_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENSET_ENDCRYPT_Enabled  (1UL) /*!< Read: Enabled */
#define CCM_INTENSET_ENDCRYPT_Set      (1UL) /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event ENDKSGEN */
#define CCM_INTENSET_ENDKSGEN_Pos      (0UL) /*!< Position of ENDKSGEN field. */
#define CCM_INTENSET_ENDKSGEN_Msk                                                                  \
  (0x1UL << CCM_INTENSET_ENDKSGEN_Pos)       /*!< Bit mask of ENDKSGEN field. */
#define CCM_INTENSET_ENDKSGEN_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENSET_ENDKSGEN_Enabled  (1UL) /*!< Read: Enabled */
#define CCM_INTENSET_ENDKSGEN_Set      (1UL) /*!< Enable */

/* Register: CCM_INTENCLR */
/* Description: Disable interrupt */

/* Bit 2 : Deprecated intclrfield -  Write '1' to disable interrupt for event ERROR */
#define CCM_INTENCLR_ERROR_Pos         (2UL) /*!< Position of ERROR field. */
#define CCM_INTENCLR_ERROR_Msk         (0x1UL << CCM_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define CCM_INTENCLR_ERROR_Disabled    (0UL)                             /*!< Read: Disabled */
#define CCM_INTENCLR_ERROR_Enabled     (1UL)                             /*!< Read: Enabled */
#define CCM_INTENCLR_ERROR_Clear       (1UL)                             /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event ENDCRYPT */
#define CCM_INTENCLR_ENDCRYPT_Pos      (1UL) /*!< Position of ENDCRYPT field. */
#define CCM_INTENCLR_ENDCRYPT_Msk                                                                  \
  (0x1UL << CCM_INTENCLR_ENDCRYPT_Pos)       /*!< Bit mask of ENDCRYPT field. */
#define CCM_INTENCLR_ENDCRYPT_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENCLR_ENDCRYPT_Enabled  (1UL) /*!< Read: Enabled */
#define CCM_INTENCLR_ENDCRYPT_Clear    (1UL) /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event ENDKSGEN */
#define CCM_INTENCLR_ENDKSGEN_Pos      (0UL) /*!< Position of ENDKSGEN field. */
#define CCM_INTENCLR_ENDKSGEN_Msk                                                                  \
  (0x1UL << CCM_INTENCLR_ENDKSGEN_Pos)       /*!< Bit mask of ENDKSGEN field. */
#define CCM_INTENCLR_ENDKSGEN_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENCLR_ENDKSGEN_Enabled  (1UL) /*!< Read: Enabled */
#define CCM_INTENCLR_ENDKSGEN_Clear    (1UL) /*!< Disable */

/* Register: CCM_MICSTATUS */
/* Description: MIC check result */

/* Bit 0 : The result of the MIC check performed during the previous decryption operation */
#define CCM_MICSTATUS_MICSTATUS_Pos    (0UL) /*!< Position of MICSTATUS field. */
#define CCM_MICSTATUS_MICSTATUS_Msk                                                                \
  (0x1UL << CCM_MICSTATUS_MICSTATUS_Pos)          /*!< Bit mask of MICSTATUS field. */
#define CCM_MICSTATUS_MICSTATUS_CheckFailed (0UL) /*!< MIC check failed */
#define CCM_MICSTATUS_MICSTATUS_CheckPassed (1UL) /*!< MIC check passed */

/* Register: CCM_ENABLE */
/* Description: Enable */

/* Bits 1..0 : Enable or disable CCM */
#define CCM_ENABLE_ENABLE_Pos               (0UL) /*!< Position of ENABLE field. */
#define CCM_ENABLE_ENABLE_Msk               (0x3UL << CCM_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define CCM_ENABLE_ENABLE_Disabled          (0UL)                            /*!< Disable */
#define CCM_ENABLE_ENABLE_Enabled           (2UL)                            /*!< Enable */

/* Register: CCM_MODE */
/* Description: Operation mode */

/* Bit 24 : Packet length configuration */
#define CCM_MODE_LENGTH_Pos                 (24UL) /*!< Position of LENGTH field. */
#define CCM_MODE_LENGTH_Msk                 (0x1UL << CCM_MODE_LENGTH_Pos) /*!< Bit mask of LENGTH field. */
#define CCM_MODE_LENGTH_Default                                                                    \
  (0UL) /*!< Default length. Effective length of LENGTH field in encrypted/decrypted packet is 5 bits. A key-stream for packet payloads up to 27 bytes will be generated. */
#define CCM_MODE_LENGTH_Extended                                                                   \
  (1UL) /*!< Extended length. Effective length of LENGTH field in encrypted/decrypted packet is 8 bits. A key-stream for packet payloads up to MAXPACKETSIZE bytes will be generated. */

/* Bits 17..16 : Radio data rate that the CCM shall run synchronous with */
#define CCM_MODE_DATARATE_Pos     (16UL) /*!< Position of DATARATE field. */
#define CCM_MODE_DATARATE_Msk     (0x3UL << CCM_MODE_DATARATE_Pos) /*!< Bit mask of DATARATE field. */
#define CCM_MODE_DATARATE_1Mbit   (0UL)                            /*!< 1 Mbps */
#define CCM_MODE_DATARATE_2Mbit   (1UL)                            /*!< 2 Mbps */
#define CCM_MODE_DATARATE_125Kbps (2UL)                            /*!< 125 Kbps */
#define CCM_MODE_DATARATE_500Kbps (3UL)                            /*!< 500 Kbps */

/* Bit 0 : The mode of operation to be used. The settings in this register apply whenever either the KSGEN or CRYPT tasks are triggered. */
#define CCM_MODE_MODE_Pos         (0UL)                        /*!< Position of MODE field. */
#define CCM_MODE_MODE_Msk         (0x1UL << CCM_MODE_MODE_Pos) /*!< Bit mask of MODE field. */
#define CCM_MODE_MODE_Encryption  (0UL) /*!< AES CCM packet encryption mode */
#define CCM_MODE_MODE_Decryption  (1UL) /*!< AES CCM packet decryption mode */

/* Register: CCM_CNFPTR */
/* Description: Pointer to data structure holding AES key and NONCE vector */

/* Bits 31..0 : Pointer to the data structure holding the AES key and the CCM NONCE vector (see Table 1 CCM data structure overview) */
#define CCM_CNFPTR_CNFPTR_Pos     (0UL) /*!< Position of CNFPTR field. */
#define CCM_CNFPTR_CNFPTR_Msk                                                                      \
  (0xFFFFFFFFUL << CCM_CNFPTR_CNFPTR_Pos) /*!< Bit mask of CNFPTR field. */

/* Register: CCM_INPTR */
/* Description: Input pointer */

/* Bits 31..0 : Input pointer */
#define CCM_INPTR_INPTR_Pos   (0UL)                                 /*!< Position of INPTR field. */
#define CCM_INPTR_INPTR_Msk   (0xFFFFFFFFUL << CCM_INPTR_INPTR_Pos) /*!< Bit mask of INPTR field. */

/* Register: CCM_OUTPTR */
/* Description: Output pointer */

/* Bits 31..0 : Output pointer */
#define CCM_OUTPTR_OUTPTR_Pos (0UL) /*!< Position of OUTPTR field. */
#define CCM_OUTPTR_OUTPTR_Msk                                                                      \
  (0xFFFFFFFFUL << CCM_OUTPTR_OUTPTR_Pos) /*!< Bit mask of OUTPTR field. */

/* Register: CCM_SCRATCHPTR */
/* Description: Pointer to data area used for temporary storage */

/* Bits 31..0 : Pointer to a scratch data area used for temporary storage during key-stream generation,
        MIC generation and encryption/decryption. */
#define CCM_SCRATCHPTR_SCRATCHPTR_Pos (0UL) /*!< Position of SCRATCHPTR field. */
#define CCM_SCRATCHPTR_SCRATCHPTR_Msk                                                              \
  (0xFFFFFFFFUL << CCM_SCRATCHPTR_SCRATCHPTR_Pos) /*!< Bit mask of SCRATCHPTR field. */

/* Register: CCM_MAXPACKETSIZE */
/* Description: Length of key-stream generated when MODE.LENGTH = Extended. */

/* Bits 7..0 : Length of key-stream generated when MODE.LENGTH = Extended. This value must be greater or equal to the subsequent packet payload to be encrypted/decrypted. */
#define CCM_MAXPACKETSIZE_MAXPACKETSIZE_Pos (0UL) /*!< Position of MAXPACKETSIZE field. */
#define CCM_MAXPACKETSIZE_MAXPACKETSIZE_Msk                                                        \
  (0xFFUL << CCM_MAXPACKETSIZE_MAXPACKETSIZE_Pos) /*!< Bit mask of MAXPACKETSIZE field. */

/* Register: CCM_RATEOVERRIDE */
/* Description: Data rate override setting. */

/* Bits 1..0 : Data rate override setting. */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_Pos (0UL) /*!< Position of RATEOVERRIDE field. */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_Msk                                                          \
  (0x3UL << CCM_RATEOVERRIDE_RATEOVERRIDE_Pos)      /*!< Bit mask of RATEOVERRIDE field. */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_1Mbit   (0UL) /*!< 1 Mbps */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_2Mbit   (1UL) /*!< 2 Mbps */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_125Kbps (2UL) /*!< 125 Kbps */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_500Kbps (3UL) /*!< 500 Kbps */


/* Peripheral: CLOCK */
/* Description: Clock control */

/* Register: CLOCK_TASKS_HFCLKSTART */
/* Description: Start HFXO crystal oscillator */

/* Bit 0 : Start HFXO crystal oscillator */
#define CLOCK_TASKS_HFCLKSTART_TASKS_HFCLKSTART_Pos                                                \
  (0UL) /*!< Position of TASKS_HFCLKSTART field. */
#define CLOCK_TASKS_HFCLKSTART_TASKS_HFCLKSTART_Msk                                                \
  (0x1UL << CLOCK_TASKS_HFCLKSTART_TASKS_HFCLKSTART_Pos) /*!< Bit mask of TASKS_HFCLKSTART field. */
#define CLOCK_TASKS_HFCLKSTART_TASKS_HFCLKSTART_Trigger (1UL) /*!< Trigger task */

/* Register: CLOCK_TASKS_HFCLKSTOP */
/* Description: Stop HFXO crystal oscillator */

/* Bit 0 : Stop HFXO crystal oscillator */
#define CLOCK_TASKS_HFCLKSTOP_TASKS_HFCLKSTOP_Pos       (0UL) /*!< Position of TASKS_HFCLKSTOP field. */
#define CLOCK_TASKS_HFCLKSTOP_TASKS_HFCLKSTOP_Msk                                                  \
  (0x1UL << CLOCK_TASKS_HFCLKSTOP_TASKS_HFCLKSTOP_Pos) /*!< Bit mask of TASKS_HFCLKSTOP field. */
#define CLOCK_TASKS_HFCLKSTOP_TASKS_HFCLKSTOP_Trigger (1UL) /*!< Trigger task */

/* Register: CLOCK_TASKS_LFCLKSTART */
/* Description: Start LFCLK */

/* Bit 0 : Start LFCLK */
#define CLOCK_TASKS_LFCLKSTART_TASKS_LFCLKSTART_Pos                                                \
  (0UL) /*!< Position of TASKS_LFCLKSTART field. */
#define CLOCK_TASKS_LFCLKSTART_TASKS_LFCLKSTART_Msk                                                \
  (0x1UL << CLOCK_TASKS_LFCLKSTART_TASKS_LFCLKSTART_Pos) /*!< Bit mask of TASKS_LFCLKSTART field. */
#define CLOCK_TASKS_LFCLKSTART_TASKS_LFCLKSTART_Trigger (1UL) /*!< Trigger task */

/* Register: CLOCK_TASKS_LFCLKSTOP */
/* Description: Stop LFCLK */

/* Bit 0 : Stop LFCLK */
#define CLOCK_TASKS_LFCLKSTOP_TASKS_LFCLKSTOP_Pos       (0UL) /*!< Position of TASKS_LFCLKSTOP field. */
#define CLOCK_TASKS_LFCLKSTOP_TASKS_LFCLKSTOP_Msk                                                  \
  (0x1UL << CLOCK_TASKS_LFCLKSTOP_TASKS_LFCLKSTOP_Pos) /*!< Bit mask of TASKS_LFCLKSTOP field. */
#define CLOCK_TASKS_LFCLKSTOP_TASKS_LFCLKSTOP_Trigger (1UL) /*!< Trigger task */

/* Register: CLOCK_TASKS_CAL */
/* Description: Start calibration of LFRC */

/* Bit 0 : Start calibration of LFRC */
#define CLOCK_TASKS_CAL_TASKS_CAL_Pos                 (0UL) /*!< Position of TASKS_CAL field. */
#define CLOCK_TASKS_CAL_TASKS_CAL_Msk                                                              \
  (0x1UL << CLOCK_TASKS_CAL_TASKS_CAL_Pos)          /*!< Bit mask of TASKS_CAL field. */
#define CLOCK_TASKS_CAL_TASKS_CAL_Trigger     (1UL) /*!< Trigger task */

/* Register: CLOCK_TASKS_CTSTART */
/* Description: Start calibration timer */

/* Bit 0 : Start calibration timer */
#define CLOCK_TASKS_CTSTART_TASKS_CTSTART_Pos (0UL) /*!< Position of TASKS_CTSTART field. */
#define CLOCK_TASKS_CTSTART_TASKS_CTSTART_Msk                                                      \
  (0x1UL << CLOCK_TASKS_CTSTART_TASKS_CTSTART_Pos)      /*!< Bit mask of TASKS_CTSTART field. */
#define CLOCK_TASKS_CTSTART_TASKS_CTSTART_Trigger (1UL) /*!< Trigger task */

/* Register: CLOCK_TASKS_CTSTOP */
/* Description: Stop calibration timer */

/* Bit 0 : Stop calibration timer */
#define CLOCK_TASKS_CTSTOP_TASKS_CTSTOP_Pos       (0UL) /*!< Position of TASKS_CTSTOP field. */
#define CLOCK_TASKS_CTSTOP_TASKS_CTSTOP_Msk                                                        \
  (0x1UL << CLOCK_TASKS_CTSTOP_TASKS_CTSTOP_Pos)      /*!< Bit mask of TASKS_CTSTOP field. */
#define CLOCK_TASKS_CTSTOP_TASKS_CTSTOP_Trigger (1UL) /*!< Trigger task */

/* Register: CLOCK_EVENTS_HFCLKSTARTED */
/* Description: HFXO crystal oscillator started */

/* Bit 0 : HFXO crystal oscillator started */
#define CLOCK_EVENTS_HFCLKSTARTED_EVENTS_HFCLKSTARTED_Pos                                          \
  (0UL) /*!< Position of EVENTS_HFCLKSTARTED field. */
#define CLOCK_EVENTS_HFCLKSTARTED_EVENTS_HFCLKSTARTED_Msk                                          \
  (0x1UL                                                                                           \
   << CLOCK_EVENTS_HFCLKSTARTED_EVENTS_HFCLKSTARTED_Pos) /*!< Bit mask of EVENTS_HFCLKSTARTED field. */
#define CLOCK_EVENTS_HFCLKSTARTED_EVENTS_HFCLKSTARTED_NotGenerated (0UL) /*!< Event not generated */
#define CLOCK_EVENTS_HFCLKSTARTED_EVENTS_HFCLKSTARTED_Generated    (1UL) /*!< Event generated */

/* Register: CLOCK_EVENTS_LFCLKSTARTED */
/* Description: LFCLK started */

/* Bit 0 : LFCLK started */
#define CLOCK_EVENTS_LFCLKSTARTED_EVENTS_LFCLKSTARTED_Pos                                          \
  (0UL) /*!< Position of EVENTS_LFCLKSTARTED field. */
#define CLOCK_EVENTS_LFCLKSTARTED_EVENTS_LFCLKSTARTED_Msk                                          \
  (0x1UL                                                                                           \
   << CLOCK_EVENTS_LFCLKSTARTED_EVENTS_LFCLKSTARTED_Pos) /*!< Bit mask of EVENTS_LFCLKSTARTED field. */
#define CLOCK_EVENTS_LFCLKSTARTED_EVENTS_LFCLKSTARTED_NotGenerated (0UL) /*!< Event not generated */
#define CLOCK_EVENTS_LFCLKSTARTED_EVENTS_LFCLKSTARTED_Generated    (1UL) /*!< Event generated */

/* Register: CLOCK_EVENTS_DONE */
/* Description: Calibration of LFRC completed */

/* Bit 0 : Calibration of LFRC completed */
#define CLOCK_EVENTS_DONE_EVENTS_DONE_Pos                          (0UL) /*!< Position of EVENTS_DONE field. */
#define CLOCK_EVENTS_DONE_EVENTS_DONE_Msk                                                          \
  (0x1UL << CLOCK_EVENTS_DONE_EVENTS_DONE_Pos)           /*!< Bit mask of EVENTS_DONE field. */
#define CLOCK_EVENTS_DONE_EVENTS_DONE_NotGenerated (0UL) /*!< Event not generated */
#define CLOCK_EVENTS_DONE_EVENTS_DONE_Generated    (1UL) /*!< Event generated */

/* Register: CLOCK_EVENTS_CTTO */
/* Description: Calibration timer timeout */

/* Bit 0 : Calibration timer timeout */
#define CLOCK_EVENTS_CTTO_EVENTS_CTTO_Pos          (0UL) /*!< Position of EVENTS_CTTO field. */
#define CLOCK_EVENTS_CTTO_EVENTS_CTTO_Msk                                                          \
  (0x1UL << CLOCK_EVENTS_CTTO_EVENTS_CTTO_Pos)           /*!< Bit mask of EVENTS_CTTO field. */
#define CLOCK_EVENTS_CTTO_EVENTS_CTTO_NotGenerated (0UL) /*!< Event not generated */
#define CLOCK_EVENTS_CTTO_EVENTS_CTTO_Generated    (1UL) /*!< Event generated */

/* Register: CLOCK_EVENTS_CTSTARTED */
/* Description: Calibration timer has been started and is ready to process new tasks */

/* Bit 0 : Calibration timer has been started and is ready to process new tasks */
#define CLOCK_EVENTS_CTSTARTED_EVENTS_CTSTARTED_Pos                                                \
  (0UL) /*!< Position of EVENTS_CTSTARTED field. */
#define CLOCK_EVENTS_CTSTARTED_EVENTS_CTSTARTED_Msk                                                \
  (0x1UL << CLOCK_EVENTS_CTSTARTED_EVENTS_CTSTARTED_Pos) /*!< Bit mask of EVENTS_CTSTARTED field. */
#define CLOCK_EVENTS_CTSTARTED_EVENTS_CTSTARTED_NotGenerated (0UL) /*!< Event not generated */
#define CLOCK_EVENTS_CTSTARTED_EVENTS_CTSTARTED_Generated    (1UL) /*!< Event generated */

/* Register: CLOCK_EVENTS_CTSTOPPED */
/* Description: Calibration timer has been stopped and is ready to process new tasks */

/* Bit 0 : Calibration timer has been stopped and is ready to process new tasks */
#define CLOCK_EVENTS_CTSTOPPED_EVENTS_CTSTOPPED_Pos                                                \
  (0UL) /*!< Position of EVENTS_CTSTOPPED field. */
#define CLOCK_EVENTS_CTSTOPPED_EVENTS_CTSTOPPED_Msk                                                \
  (0x1UL << CLOCK_EVENTS_CTSTOPPED_EVENTS_CTSTOPPED_Pos) /*!< Bit mask of EVENTS_CTSTOPPED field. */
#define CLOCK_EVENTS_CTSTOPPED_EVENTS_CTSTOPPED_NotGenerated (0UL) /*!< Event not generated */
#define CLOCK_EVENTS_CTSTOPPED_EVENTS_CTSTOPPED_Generated    (1UL) /*!< Event generated */

/* Register: CLOCK_INTENSET */
/* Description: Enable interrupt */

/* Bit 11 : Write '1' to enable interrupt for event CTSTOPPED */
#define CLOCK_INTENSET_CTSTOPPED_Pos                         (11UL) /*!< Position of CTSTOPPED field. */
#define CLOCK_INTENSET_CTSTOPPED_Msk                                                               \
  (0x1UL << CLOCK_INTENSET_CTSTOPPED_Pos)       /*!< Bit mask of CTSTOPPED field. */
#define CLOCK_INTENSET_CTSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENSET_CTSTOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define CLOCK_INTENSET_CTSTOPPED_Set      (1UL) /*!< Enable */

/* Bit 10 : Write '1' to enable interrupt for event CTSTARTED */
#define CLOCK_INTENSET_CTSTARTED_Pos      (10UL) /*!< Position of CTSTARTED field. */
#define CLOCK_INTENSET_CTSTARTED_Msk                                                               \
  (0x1UL << CLOCK_INTENSET_CTSTARTED_Pos)       /*!< Bit mask of CTSTARTED field. */
#define CLOCK_INTENSET_CTSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENSET_CTSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define CLOCK_INTENSET_CTSTARTED_Set      (1UL) /*!< Enable */

/* Bit 4 : Write '1' to enable interrupt for event CTTO */
#define CLOCK_INTENSET_CTTO_Pos           (4UL) /*!< Position of CTTO field. */
#define CLOCK_INTENSET_CTTO_Msk           (0x1UL << CLOCK_INTENSET_CTTO_Pos) /*!< Bit mask of CTTO field. */
#define CLOCK_INTENSET_CTTO_Disabled      (0UL)                              /*!< Read: Disabled */
#define CLOCK_INTENSET_CTTO_Enabled       (1UL)                              /*!< Read: Enabled */
#define CLOCK_INTENSET_CTTO_Set           (1UL)                              /*!< Enable */

/* Bit 3 : Write '1' to enable interrupt for event DONE */
#define CLOCK_INTENSET_DONE_Pos           (3UL) /*!< Position of DONE field. */
#define CLOCK_INTENSET_DONE_Msk           (0x1UL << CLOCK_INTENSET_DONE_Pos) /*!< Bit mask of DONE field. */
#define CLOCK_INTENSET_DONE_Disabled      (0UL)                              /*!< Read: Disabled */
#define CLOCK_INTENSET_DONE_Enabled       (1UL)                              /*!< Read: Enabled */
#define CLOCK_INTENSET_DONE_Set           (1UL)                              /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event LFCLKSTARTED */
#define CLOCK_INTENSET_LFCLKSTARTED_Pos   (1UL) /*!< Position of LFCLKSTARTED field. */
#define CLOCK_INTENSET_LFCLKSTARTED_Msk                                                            \
  (0x1UL << CLOCK_INTENSET_LFCLKSTARTED_Pos)       /*!< Bit mask of LFCLKSTARTED field. */
#define CLOCK_INTENSET_LFCLKSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENSET_LFCLKSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define CLOCK_INTENSET_LFCLKSTARTED_Set      (1UL) /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event HFCLKSTARTED */
#define CLOCK_INTENSET_HFCLKSTARTED_Pos      (0UL) /*!< Position of HFCLKSTARTED field. */
#define CLOCK_INTENSET_HFCLKSTARTED_Msk                                                            \
  (0x1UL << CLOCK_INTENSET_HFCLKSTARTED_Pos)       /*!< Bit mask of HFCLKSTARTED field. */
#define CLOCK_INTENSET_HFCLKSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENSET_HFCLKSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define CLOCK_INTENSET_HFCLKSTARTED_Set      (1UL) /*!< Enable */

/* Register: CLOCK_INTENCLR */
/* Description: Disable interrupt */

/* Bit 11 : Write '1' to disable interrupt for event CTSTOPPED */
#define CLOCK_INTENCLR_CTSTOPPED_Pos         (11UL) /*!< Position of CTSTOPPED field. */
#define CLOCK_INTENCLR_CTSTOPPED_Msk                                                               \
  (0x1UL << CLOCK_INTENCLR_CTSTOPPED_Pos)       /*!< Bit mask of CTSTOPPED field. */
#define CLOCK_INTENCLR_CTSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENCLR_CTSTOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define CLOCK_INTENCLR_CTSTOPPED_Clear    (1UL) /*!< Disable */

/* Bit 10 : Write '1' to disable interrupt for event CTSTARTED */
#define CLOCK_INTENCLR_CTSTARTED_Pos      (10UL) /*!< Position of CTSTARTED field. */
#define CLOCK_INTENCLR_CTSTARTED_Msk                                                               \
  (0x1UL << CLOCK_INTENCLR_CTSTARTED_Pos)       /*!< Bit mask of CTSTARTED field. */
#define CLOCK_INTENCLR_CTSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENCLR_CTSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define CLOCK_INTENCLR_CTSTARTED_Clear    (1UL) /*!< Disable */

/* Bit 4 : Write '1' to disable interrupt for event CTTO */
#define CLOCK_INTENCLR_CTTO_Pos           (4UL) /*!< Position of CTTO field. */
#define CLOCK_INTENCLR_CTTO_Msk           (0x1UL << CLOCK_INTENCLR_CTTO_Pos) /*!< Bit mask of CTTO field. */
#define CLOCK_INTENCLR_CTTO_Disabled      (0UL)                              /*!< Read: Disabled */
#define CLOCK_INTENCLR_CTTO_Enabled       (1UL)                              /*!< Read: Enabled */
#define CLOCK_INTENCLR_CTTO_Clear         (1UL)                              /*!< Disable */

/* Bit 3 : Write '1' to disable interrupt for event DONE */
#define CLOCK_INTENCLR_DONE_Pos           (3UL) /*!< Position of DONE field. */
#define CLOCK_INTENCLR_DONE_Msk           (0x1UL << CLOCK_INTENCLR_DONE_Pos) /*!< Bit mask of DONE field. */
#define CLOCK_INTENCLR_DONE_Disabled      (0UL)                              /*!< Read: Disabled */
#define CLOCK_INTENCLR_DONE_Enabled       (1UL)                              /*!< Read: Enabled */
#define CLOCK_INTENCLR_DONE_Clear         (1UL)                              /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event LFCLKSTARTED */
#define CLOCK_INTENCLR_LFCLKSTARTED_Pos   (1UL) /*!< Position of LFCLKSTARTED field. */
#define CLOCK_INTENCLR_LFCLKSTARTED_Msk                                                            \
  (0x1UL << CLOCK_INTENCLR_LFCLKSTARTED_Pos)       /*!< Bit mask of LFCLKSTARTED field. */
#define CLOCK_INTENCLR_LFCLKSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENCLR_LFCLKSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define CLOCK_INTENCLR_LFCLKSTARTED_Clear    (1UL) /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event HFCLKSTARTED */
#define CLOCK_INTENCLR_HFCLKSTARTED_Pos      (0UL) /*!< Position of HFCLKSTARTED field. */
#define CLOCK_INTENCLR_HFCLKSTARTED_Msk                                                            \
  (0x1UL << CLOCK_INTENCLR_HFCLKSTARTED_Pos)       /*!< Bit mask of HFCLKSTARTED field. */
#define CLOCK_INTENCLR_HFCLKSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENCLR_HFCLKSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define CLOCK_INTENCLR_HFCLKSTARTED_Clear    (1UL) /*!< Disable */

/* Register: CLOCK_HFCLKRUN */
/* Description: Status indicating that HFCLKSTART task has been triggered */

/* Bit 0 : HFCLKSTART task triggered or not */
#define CLOCK_HFCLKRUN_STATUS_Pos            (0UL) /*!< Position of STATUS field. */
#define CLOCK_HFCLKRUN_STATUS_Msk                                                                  \
  (0x1UL << CLOCK_HFCLKRUN_STATUS_Pos)           /*!< Bit mask of STATUS field. */
#define CLOCK_HFCLKRUN_STATUS_NotTriggered (0UL) /*!< Task not triggered */
#define CLOCK_HFCLKRUN_STATUS_Triggered    (1UL) /*!< Task triggered */

/* Register: CLOCK_HFCLKSTAT */
/* Description: HFCLK status */

/* Bit 16 : HFCLK state */
#define CLOCK_HFCLKSTAT_STATE_Pos          (16UL) /*!< Position of STATE field. */
#define CLOCK_HFCLKSTAT_STATE_Msk                                                                  \
  (0x1UL << CLOCK_HFCLKSTAT_STATE_Pos)         /*!< Bit mask of STATE field. */
#define CLOCK_HFCLKSTAT_STATE_NotRunning (0UL) /*!< HFCLK not running */
#define CLOCK_HFCLKSTAT_STATE_Running    (1UL) /*!< HFCLK running */

/* Bit 0 : Source of HFCLK */
#define CLOCK_HFCLKSTAT_SRC_Pos          (0UL) /*!< Position of SRC field. */
#define CLOCK_HFCLKSTAT_SRC_Msk          (0x1UL << CLOCK_HFCLKSTAT_SRC_Pos) /*!< Bit mask of SRC field. */
#define CLOCK_HFCLKSTAT_SRC_RC           (0UL) /*!< 64 MHz internal oscillator (HFINT) */
#define CLOCK_HFCLKSTAT_SRC_Xtal         (1UL) /*!< 64 MHz crystal oscillator (HFXO) */

/* Register: CLOCK_LFCLKRUN */
/* Description: Status indicating that LFCLKSTART task has been triggered */

/* Bit 0 : LFCLKSTART task triggered or not */
#define CLOCK_LFCLKRUN_STATUS_Pos        (0UL) /*!< Position of STATUS field. */
#define CLOCK_LFCLKRUN_STATUS_Msk                                                                  \
  (0x1UL << CLOCK_LFCLKRUN_STATUS_Pos)           /*!< Bit mask of STATUS field. */
#define CLOCK_LFCLKRUN_STATUS_NotTriggered (0UL) /*!< Task not triggered */
#define CLOCK_LFCLKRUN_STATUS_Triggered    (1UL) /*!< Task triggered */

/* Register: CLOCK_LFCLKSTAT */
/* Description: LFCLK status */

/* Bit 16 : LFCLK state */
#define CLOCK_LFCLKSTAT_STATE_Pos          (16UL) /*!< Position of STATE field. */
#define CLOCK_LFCLKSTAT_STATE_Msk                                                                  \
  (0x1UL << CLOCK_LFCLKSTAT_STATE_Pos)         /*!< Bit mask of STATE field. */
#define CLOCK_LFCLKSTAT_STATE_NotRunning (0UL) /*!< LFCLK not running */
#define CLOCK_LFCLKSTAT_STATE_Running    (1UL) /*!< LFCLK running */

/* Bits 1..0 : Source of LFCLK */
#define CLOCK_LFCLKSTAT_SRC_Pos          (0UL) /*!< Position of SRC field. */
#define CLOCK_LFCLKSTAT_SRC_Msk          (0x3UL << CLOCK_LFCLKSTAT_SRC_Pos) /*!< Bit mask of SRC field. */
#define CLOCK_LFCLKSTAT_SRC_RC           (0UL) /*!< 32.768 kHz RC oscillator (LFRC) */
#define CLOCK_LFCLKSTAT_SRC_Xtal         (1UL) /*!< 32.768 kHz crystal oscillator (LFXO) */
#define CLOCK_LFCLKSTAT_SRC_Synth        (2UL) /*!< 32.768 kHz synthesized from HFCLK (LFSYNT) */

/* Register: CLOCK_LFCLKSRCCOPY */
/* Description: Copy of LFCLKSRC register, set when LFCLKSTART task was triggered */

/* Bits 1..0 : Clock source */
#define CLOCK_LFCLKSRCCOPY_SRC_Pos       (0UL) /*!< Position of SRC field. */
#define CLOCK_LFCLKSRCCOPY_SRC_Msk                                                                 \
  (0x3UL << CLOCK_LFCLKSRCCOPY_SRC_Pos)    /*!< Bit mask of SRC field. */
#define CLOCK_LFCLKSRCCOPY_SRC_RC    (0UL) /*!< 32.768 kHz RC oscillator (LFRC) */
#define CLOCK_LFCLKSRCCOPY_SRC_Xtal  (1UL) /*!< 32.768 kHz crystal oscillator (LFXO) */
#define CLOCK_LFCLKSRCCOPY_SRC_Synth (2UL) /*!< 32.768 kHz synthesized from HFCLK (LFSYNT) */

/* Register: CLOCK_LFCLKSRC */
/* Description: Clock source for the LFCLK */

/* Bit 17 : Enable or disable external source for LFCLK */
#define CLOCK_LFCLKSRC_EXTERNAL_Pos  (17UL) /*!< Position of EXTERNAL field. */
#define CLOCK_LFCLKSRC_EXTERNAL_Msk                                                                \
  (0x1UL << CLOCK_LFCLKSRC_EXTERNAL_Pos)       /*!< Bit mask of EXTERNAL field. */
#define CLOCK_LFCLKSRC_EXTERNAL_Disabled (0UL) /*!< Disable external source (use with Xtal) */
#define CLOCK_LFCLKSRC_EXTERNAL_Enabled                                                            \
  (1UL) /*!< Enable use of external source instead of Xtal (SRC needs to be set to Xtal) */

/* Bit 16 : Enable or disable bypass of LFCLK crystal oscillator with external clock source */
#define CLOCK_LFCLKSRC_BYPASS_Pos (16UL) /*!< Position of BYPASS field. */
#define CLOCK_LFCLKSRC_BYPASS_Msk                                                                  \
  (0x1UL << CLOCK_LFCLKSRC_BYPASS_Pos) /*!< Bit mask of BYPASS field. */
#define CLOCK_LFCLKSRC_BYPASS_Disabled                                                             \
  (0UL) /*!< Disable (use with Xtal or low-swing external source) */
#define CLOCK_LFCLKSRC_BYPASS_Enabled       (1UL) /*!< Enable (use with rail-to-rail external source) */

/* Bits 1..0 : Clock source */
#define CLOCK_LFCLKSRC_SRC_Pos              (0UL) /*!< Position of SRC field. */
#define CLOCK_LFCLKSRC_SRC_Msk              (0x3UL << CLOCK_LFCLKSRC_SRC_Pos) /*!< Bit mask of SRC field. */
#define CLOCK_LFCLKSRC_SRC_RC               (0UL) /*!< 32.768 kHz RC oscillator (LFRC) */
#define CLOCK_LFCLKSRC_SRC_Xtal             (1UL) /*!< 32.768 kHz crystal oscillator (LFXO) */
#define CLOCK_LFCLKSRC_SRC_Synth            (2UL) /*!< 32.768 kHz synthesized from HFCLK (LFSYNT) */

/* Register: CLOCK_HFXODEBOUNCE */
/* Description: HFXO debounce time. The HFXO is started by triggering the TASKS_HFCLKSTART task. */

/* Bits 7..0 : HFXO debounce time. Debounce time = HFXODEBOUNCE * 16 us. */
#define CLOCK_HFXODEBOUNCE_HFXODEBOUNCE_Pos (0UL) /*!< Position of HFXODEBOUNCE field. */
#define CLOCK_HFXODEBOUNCE_HFXODEBOUNCE_Msk                                                        \
  (0xFFUL << CLOCK_HFXODEBOUNCE_HFXODEBOUNCE_Pos) /*!< Bit mask of HFXODEBOUNCE field. */
#define CLOCK_HFXODEBOUNCE_HFXODEBOUNCE_Db256us                                                    \
  (0x10UL) /*!< 256 us debounce time. Recommended for 1.6 mm x 2.0 mm crystals and larger. */
#define CLOCK_HFXODEBOUNCE_HFXODEBOUNCE_Db1024us                                                   \
  (0x40UL) /*!< 1024 us debounce time. Recommended for 1.6 mm x 1.2 mm crystals and smaller. */

/* Register: CLOCK_LFXODEBOUNCE */
/* Description: LFXO debounce time. The LFXO is started by triggering the TASKS_LFCLKSTART task when the LFCLKSRC register is configured for Xtal. */

/* Bit 0 : LFXO debounce time. */
#define CLOCK_LFXODEBOUNCE_LFXODEBOUNCE_Pos (0UL) /*!< Position of LFXODEBOUNCE field. */
#define CLOCK_LFXODEBOUNCE_LFXODEBOUNCE_Msk                                                        \
  (0x1UL << CLOCK_LFXODEBOUNCE_LFXODEBOUNCE_Pos) /*!< Bit mask of LFXODEBOUNCE field. */
#define CLOCK_LFXODEBOUNCE_LFXODEBOUNCE_Normal                                                     \
  (0UL) /*!< 8192 32.768 kHz periods, or 0.25 s. Recommended for normal Operating Temperature conditions. */
#define CLOCK_LFXODEBOUNCE_LFXODEBOUNCE_Extended                                                   \
  (1UL) /*!< 16384 32.768 kHz periods, or 0.5 s. Recommended for Extended Operating Temperature conditions. */

/* Register: CLOCK_CTIV */
/* Description: Calibration timer interval */

/* Bits 6..0 : Calibration timer interval in multiple of 0.25 seconds. Range: 0.25 seconds to 31.75 seconds. */
#define CLOCK_CTIV_CTIV_Pos              (0UL) /*!< Position of CTIV field. */
#define CLOCK_CTIV_CTIV_Msk              (0x7FUL << CLOCK_CTIV_CTIV_Pos) /*!< Bit mask of CTIV field. */


/* Peripheral: COMP */
/* Description: Comparator */

/* Register: COMP_TASKS_START */
/* Description: Start comparator */

/* Bit 0 : Start comparator */
#define COMP_TASKS_START_TASKS_START_Pos (0UL) /*!< Position of TASKS_START field. */
#define COMP_TASKS_START_TASKS_START_Msk                                                           \
  (0x1UL << COMP_TASKS_START_TASKS_START_Pos)      /*!< Bit mask of TASKS_START field. */
#define COMP_TASKS_START_TASKS_START_Trigger (1UL) /*!< Trigger task */

/* Register: COMP_TASKS_STOP */
/* Description: Stop comparator */

/* Bit 0 : Stop comparator */
#define COMP_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define COMP_TASKS_STOP_TASKS_STOP_Msk                                                             \
  (0x1UL << COMP_TASKS_STOP_TASKS_STOP_Pos)      /*!< Bit mask of TASKS_STOP field. */
#define COMP_TASKS_STOP_TASKS_STOP_Trigger (1UL) /*!< Trigger task */

/* Register: COMP_TASKS_SAMPLE */
/* Description: Sample comparator value */

/* Bit 0 : Sample comparator value */
#define COMP_TASKS_SAMPLE_TASKS_SAMPLE_Pos (0UL) /*!< Position of TASKS_SAMPLE field. */
#define COMP_TASKS_SAMPLE_TASKS_SAMPLE_Msk                                                         \
  (0x1UL << COMP_TASKS_SAMPLE_TASKS_SAMPLE_Pos)      /*!< Bit mask of TASKS_SAMPLE field. */
#define COMP_TASKS_SAMPLE_TASKS_SAMPLE_Trigger (1UL) /*!< Trigger task */

/* Register: COMP_EVENTS_READY */
/* Description: COMP is ready and output is valid */

/* Bit 0 : COMP is ready and output is valid */
#define COMP_EVENTS_READY_EVENTS_READY_Pos     (0UL) /*!< Position of EVENTS_READY field. */
#define COMP_EVENTS_READY_EVENTS_READY_Msk                                                         \
  (0x1UL << COMP_EVENTS_READY_EVENTS_READY_Pos)           /*!< Bit mask of EVENTS_READY field. */
#define COMP_EVENTS_READY_EVENTS_READY_NotGenerated (0UL) /*!< Event not generated */
#define COMP_EVENTS_READY_EVENTS_READY_Generated    (1UL) /*!< Event generated */

/* Register: COMP_EVENTS_DOWN */
/* Description: Downward crossing */

/* Bit 0 : Downward crossing */
#define COMP_EVENTS_DOWN_EVENTS_DOWN_Pos            (0UL) /*!< Position of EVENTS_DOWN field. */
#define COMP_EVENTS_DOWN_EVENTS_DOWN_Msk                                                           \
  (0x1UL << COMP_EVENTS_DOWN_EVENTS_DOWN_Pos)           /*!< Bit mask of EVENTS_DOWN field. */
#define COMP_EVENTS_DOWN_EVENTS_DOWN_NotGenerated (0UL) /*!< Event not generated */
#define COMP_EVENTS_DOWN_EVENTS_DOWN_Generated    (1UL) /*!< Event generated */

/* Register: COMP_EVENTS_UP */
/* Description: Upward crossing */

/* Bit 0 : Upward crossing */
#define COMP_EVENTS_UP_EVENTS_UP_Pos              (0UL) /*!< Position of EVENTS_UP field. */
#define COMP_EVENTS_UP_EVENTS_UP_Msk                                                               \
  (0x1UL << COMP_EVENTS_UP_EVENTS_UP_Pos)           /*!< Bit mask of EVENTS_UP field. */
#define COMP_EVENTS_UP_EVENTS_UP_NotGenerated (0UL) /*!< Event not generated */
#define COMP_EVENTS_UP_EVENTS_UP_Generated    (1UL) /*!< Event generated */

/* Register: COMP_EVENTS_CROSS */
/* Description: Downward or upward crossing */

/* Bit 0 : Downward or upward crossing */
#define COMP_EVENTS_CROSS_EVENTS_CROSS_Pos    (0UL) /*!< Position of EVENTS_CROSS field. */
#define COMP_EVENTS_CROSS_EVENTS_CROSS_Msk                                                         \
  (0x1UL << COMP_EVENTS_CROSS_EVENTS_CROSS_Pos)           /*!< Bit mask of EVENTS_CROSS field. */
#define COMP_EVENTS_CROSS_EVENTS_CROSS_NotGenerated (0UL) /*!< Event not generated */
#define COMP_EVENTS_CROSS_EVENTS_CROSS_Generated    (1UL) /*!< Event generated */

/* Register: COMP_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 4 : Shortcut between event CROSS and task STOP */
#define COMP_SHORTS_CROSS_STOP_Pos                  (4UL) /*!< Position of CROSS_STOP field. */
#define COMP_SHORTS_CROSS_STOP_Msk                                                                 \
  (0x1UL << COMP_SHORTS_CROSS_STOP_Pos)       /*!< Bit mask of CROSS_STOP field. */
#define COMP_SHORTS_CROSS_STOP_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_CROSS_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between event UP and task STOP */
#define COMP_SHORTS_UP_STOP_Pos         (3UL) /*!< Position of UP_STOP field. */
#define COMP_SHORTS_UP_STOP_Msk                                                                    \
  (0x1UL << COMP_SHORTS_UP_STOP_Pos)       /*!< Bit mask of UP_STOP field. */
#define COMP_SHORTS_UP_STOP_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_UP_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between event DOWN and task STOP */
#define COMP_SHORTS_DOWN_STOP_Pos    (2UL) /*!< Position of DOWN_STOP field. */
#define COMP_SHORTS_DOWN_STOP_Msk                                                                  \
  (0x1UL << COMP_SHORTS_DOWN_STOP_Pos)       /*!< Bit mask of DOWN_STOP field. */
#define COMP_SHORTS_DOWN_STOP_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_DOWN_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between event READY and task STOP */
#define COMP_SHORTS_READY_STOP_Pos     (1UL) /*!< Position of READY_STOP field. */
#define COMP_SHORTS_READY_STOP_Msk                                                                 \
  (0x1UL << COMP_SHORTS_READY_STOP_Pos)       /*!< Bit mask of READY_STOP field. */
#define COMP_SHORTS_READY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_READY_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between event READY and task SAMPLE */
#define COMP_SHORTS_READY_SAMPLE_Pos    (0UL) /*!< Position of READY_SAMPLE field. */
#define COMP_SHORTS_READY_SAMPLE_Msk                                                               \
  (0x1UL << COMP_SHORTS_READY_SAMPLE_Pos)       /*!< Bit mask of READY_SAMPLE field. */
#define COMP_SHORTS_READY_SAMPLE_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_READY_SAMPLE_Enabled  (1UL) /*!< Enable shortcut */

/* Register: COMP_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 3 : Enable or disable interrupt for event CROSS */
#define COMP_INTEN_CROSS_Pos              (3UL) /*!< Position of CROSS field. */
#define COMP_INTEN_CROSS_Msk              (0x1UL << COMP_INTEN_CROSS_Pos) /*!< Bit mask of CROSS field. */
#define COMP_INTEN_CROSS_Disabled         (0UL)                           /*!< Disable */
#define COMP_INTEN_CROSS_Enabled          (1UL)                           /*!< Enable */

/* Bit 2 : Enable or disable interrupt for event UP */
#define COMP_INTEN_UP_Pos                 (2UL)                        /*!< Position of UP field. */
#define COMP_INTEN_UP_Msk                 (0x1UL << COMP_INTEN_UP_Pos) /*!< Bit mask of UP field. */
#define COMP_INTEN_UP_Disabled            (0UL)                        /*!< Disable */
#define COMP_INTEN_UP_Enabled             (1UL)                        /*!< Enable */

/* Bit 1 : Enable or disable interrupt for event DOWN */
#define COMP_INTEN_DOWN_Pos               (1UL) /*!< Position of DOWN field. */
#define COMP_INTEN_DOWN_Msk               (0x1UL << COMP_INTEN_DOWN_Pos) /*!< Bit mask of DOWN field. */
#define COMP_INTEN_DOWN_Disabled          (0UL)                          /*!< Disable */
#define COMP_INTEN_DOWN_Enabled           (1UL)                          /*!< Enable */

/* Bit 0 : Enable or disable interrupt for event READY */
#define COMP_INTEN_READY_Pos              (0UL) /*!< Position of READY field. */
#define COMP_INTEN_READY_Msk              (0x1UL << COMP_INTEN_READY_Pos) /*!< Bit mask of READY field. */
#define COMP_INTEN_READY_Disabled         (0UL)                           /*!< Disable */
#define COMP_INTEN_READY_Enabled          (1UL)                           /*!< Enable */

/* Register: COMP_INTENSET */
/* Description: Enable interrupt */

/* Bit 3 : Write '1' to enable interrupt for event CROSS */
#define COMP_INTENSET_CROSS_Pos           (3UL) /*!< Position of CROSS field. */
#define COMP_INTENSET_CROSS_Msk           (0x1UL << COMP_INTENSET_CROSS_Pos) /*!< Bit mask of CROSS field. */
#define COMP_INTENSET_CROSS_Disabled      (0UL)                              /*!< Read: Disabled */
#define COMP_INTENSET_CROSS_Enabled       (1UL)                              /*!< Read: Enabled */
#define COMP_INTENSET_CROSS_Set           (1UL)                              /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event UP */
#define COMP_INTENSET_UP_Pos              (2UL) /*!< Position of UP field. */
#define COMP_INTENSET_UP_Msk              (0x1UL << COMP_INTENSET_UP_Pos) /*!< Bit mask of UP field. */
#define COMP_INTENSET_UP_Disabled         (0UL)                           /*!< Read: Disabled */
#define COMP_INTENSET_UP_Enabled          (1UL)                           /*!< Read: Enabled */
#define COMP_INTENSET_UP_Set              (1UL)                           /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event DOWN */
#define COMP_INTENSET_DOWN_Pos            (1UL) /*!< Position of DOWN field. */
#define COMP_INTENSET_DOWN_Msk            (0x1UL << COMP_INTENSET_DOWN_Pos) /*!< Bit mask of DOWN field. */
#define COMP_INTENSET_DOWN_Disabled       (0UL)                             /*!< Read: Disabled */
#define COMP_INTENSET_DOWN_Enabled        (1UL)                             /*!< Read: Enabled */
#define COMP_INTENSET_DOWN_Set            (1UL)                             /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event READY */
#define COMP_INTENSET_READY_Pos           (0UL) /*!< Position of READY field. */
#define COMP_INTENSET_READY_Msk           (0x1UL << COMP_INTENSET_READY_Pos) /*!< Bit mask of READY field. */
#define COMP_INTENSET_READY_Disabled      (0UL)                              /*!< Read: Disabled */
#define COMP_INTENSET_READY_Enabled       (1UL)                              /*!< Read: Enabled */
#define COMP_INTENSET_READY_Set           (1UL)                              /*!< Enable */

/* Register: COMP_INTENCLR */
/* Description: Disable interrupt */

/* Bit 3 : Write '1' to disable interrupt for event CROSS */
#define COMP_INTENCLR_CROSS_Pos           (3UL) /*!< Position of CROSS field. */
#define COMP_INTENCLR_CROSS_Msk           (0x1UL << COMP_INTENCLR_CROSS_Pos) /*!< Bit mask of CROSS field. */
#define COMP_INTENCLR_CROSS_Disabled      (0UL)                              /*!< Read: Disabled */
#define COMP_INTENCLR_CROSS_Enabled       (1UL)                              /*!< Read: Enabled */
#define COMP_INTENCLR_CROSS_Clear         (1UL)                              /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event UP */
#define COMP_INTENCLR_UP_Pos              (2UL) /*!< Position of UP field. */
#define COMP_INTENCLR_UP_Msk              (0x1UL << COMP_INTENCLR_UP_Pos) /*!< Bit mask of UP field. */
#define COMP_INTENCLR_UP_Disabled         (0UL)                           /*!< Read: Disabled */
#define COMP_INTENCLR_UP_Enabled          (1UL)                           /*!< Read: Enabled */
#define COMP_INTENCLR_UP_Clear            (1UL)                           /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event DOWN */
#define COMP_INTENCLR_DOWN_Pos            (1UL) /*!< Position of DOWN field. */
#define COMP_INTENCLR_DOWN_Msk            (0x1UL << COMP_INTENCLR_DOWN_Pos) /*!< Bit mask of DOWN field. */
#define COMP_INTENCLR_DOWN_Disabled       (0UL)                             /*!< Read: Disabled */
#define COMP_INTENCLR_DOWN_Enabled        (1UL)                             /*!< Read: Enabled */
#define COMP_INTENCLR_DOWN_Clear          (1UL)                             /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event READY */
#define COMP_INTENCLR_READY_Pos           (0UL) /*!< Position of READY field. */
#define COMP_INTENCLR_READY_Msk           (0x1UL << COMP_INTENCLR_READY_Pos) /*!< Bit mask of READY field. */
#define COMP_INTENCLR_READY_Disabled      (0UL)                              /*!< Read: Disabled */
#define COMP_INTENCLR_READY_Enabled       (1UL)                              /*!< Read: Enabled */
#define COMP_INTENCLR_READY_Clear         (1UL)                              /*!< Disable */

/* Register: COMP_RESULT */
/* Description: Compare result */

/* Bit 0 : Result of last compare. Decision point SAMPLE task. */
#define COMP_RESULT_RESULT_Pos            (0UL) /*!< Position of RESULT field. */
#define COMP_RESULT_RESULT_Msk            (0x1UL << COMP_RESULT_RESULT_Pos) /*!< Bit mask of RESULT field. */
#define COMP_RESULT_RESULT_Below          (0UL) /*!< Input voltage is below the threshold (VIN+ &lt; VIN-) */
#define COMP_RESULT_RESULT_Above          (1UL) /*!< Input voltage is above the threshold (VIN+ &gt; VIN-) */

/* Register: COMP_ENABLE */
/* Description: COMP enable */

/* Bits 1..0 : Enable or disable COMP */
#define COMP_ENABLE_ENABLE_Pos            (0UL) /*!< Position of ENABLE field. */
#define COMP_ENABLE_ENABLE_Msk            (0x3UL << COMP_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define COMP_ENABLE_ENABLE_Disabled       (0UL)                             /*!< Disable */
#define COMP_ENABLE_ENABLE_Enabled        (2UL)                             /*!< Enable */

/* Register: COMP_PSEL */
/* Description: Pin select */

/* Bits 2..0 : Analog pin select */
#define COMP_PSEL_PSEL_Pos                (0UL) /*!< Position of PSEL field. */
#define COMP_PSEL_PSEL_Msk                (0x7UL << COMP_PSEL_PSEL_Pos) /*!< Bit mask of PSEL field. */
#define COMP_PSEL_PSEL_AnalogInput0       (0UL) /*!< AIN0 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput1       (1UL) /*!< AIN1 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput2       (2UL) /*!< AIN2 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput3       (3UL) /*!< AIN3 selected as analog input */
#define COMP_PSEL_PSEL_VddhDiv5           (7UL) /*!< VDDH/5 selected as analog input */

/* Register: COMP_REFSEL */
/* Description: Reference source select for single-ended mode */

/* Bits 2..0 : Reference select */
#define COMP_REFSEL_REFSEL_Pos            (0UL) /*!< Position of REFSEL field. */
#define COMP_REFSEL_REFSEL_Msk            (0x7UL << COMP_REFSEL_REFSEL_Pos) /*!< Bit mask of REFSEL field. */
#define COMP_REFSEL_REFSEL_Int1V2         (0UL) /*!< VREF = internal 1.2 V reference (VDD &gt;= 1.7 V) */
#define COMP_REFSEL_REFSEL_Int1V8                                                                  \
  (1UL) /*!< VREF = internal 1.8 V reference (VDD &gt;= VREF + 0.2 V) */
#define COMP_REFSEL_REFSEL_Int2V4                                                                  \
  (2UL) /*!< VREF = internal 2.4 V reference (VDD &gt;= VREF + 0.2 V) */
#define COMP_REFSEL_REFSEL_VDD       (4UL) /*!< VREF = VDD */
#define COMP_REFSEL_REFSEL_ARef      (5UL) /*!< VREF = AREF */

/* Register: COMP_EXTREFSEL */
/* Description: External reference select */

/* Bits 2..0 : External analog reference select */
#define COMP_EXTREFSEL_EXTREFSEL_Pos (0UL) /*!< Position of EXTREFSEL field. */
#define COMP_EXTREFSEL_EXTREFSEL_Msk                                                               \
  (0x7UL << COMP_EXTREFSEL_EXTREFSEL_Pos) /*!< Bit mask of EXTREFSEL field. */
#define COMP_EXTREFSEL_EXTREFSEL_AnalogReference0                                                  \
  (0UL) /*!< Use AIN0 as external analog reference */
#define COMP_EXTREFSEL_EXTREFSEL_AnalogReference1                                                  \
  (1UL) /*!< Use AIN1 as external analog reference */
#define COMP_EXTREFSEL_EXTREFSEL_AnalogReference2                                                  \
  (2UL) /*!< Use AIN2 as external analog reference */
#define COMP_EXTREFSEL_EXTREFSEL_AnalogReference3                                                  \
  (3UL) /*!< Use AIN3 as external analog reference */

/* Register: COMP_TH */
/* Description: Threshold configuration for hysteresis unit */

/* Bits 13..8 : VUP = (THUP+1)/64*VREF */
#define COMP_TH_THUP_Pos                      (8UL) /*!< Position of THUP field. */
#define COMP_TH_THUP_Msk                      (0x3FUL << COMP_TH_THUP_Pos) /*!< Bit mask of THUP field. */

/* Bits 5..0 : VDOWN = (THDOWN+1)/64*VREF */
#define COMP_TH_THDOWN_Pos                    (0UL) /*!< Position of THDOWN field. */
#define COMP_TH_THDOWN_Msk                    (0x3FUL << COMP_TH_THDOWN_Pos) /*!< Bit mask of THDOWN field. */

/* Register: COMP_MODE */
/* Description: Mode configuration */

/* Bit 8 : Main operation modes */
#define COMP_MODE_MAIN_Pos                    (8UL) /*!< Position of MAIN field. */
#define COMP_MODE_MAIN_Msk                    (0x1UL << COMP_MODE_MAIN_Pos) /*!< Bit mask of MAIN field. */
#define COMP_MODE_MAIN_SE                     (0UL) /*!< Single-ended mode */
#define COMP_MODE_MAIN_Diff                   (1UL) /*!< Differential mode */

/* Bits 1..0 : Speed and power modes */
#define COMP_MODE_SP_Pos                      (0UL) /*!< Position of SP field. */
#define COMP_MODE_SP_Msk                      (0x3UL << COMP_MODE_SP_Pos) /*!< Bit mask of SP field. */
#define COMP_MODE_SP_Low                      (0UL)                       /*!< Low-power mode */
#define COMP_MODE_SP_Normal                   (1UL)                       /*!< Normal mode */
#define COMP_MODE_SP_High                     (2UL)                       /*!< High-speed mode */

/* Register: COMP_HYST */
/* Description: Comparator hysteresis enable */

/* Bit 0 : Comparator hysteresis */
#define COMP_HYST_HYST_Pos                    (0UL) /*!< Position of HYST field. */
#define COMP_HYST_HYST_Msk                    (0x1UL << COMP_HYST_HYST_Pos) /*!< Bit mask of HYST field. */
#define COMP_HYST_HYST_NoHyst                 (0UL) /*!< Comparator hysteresis disabled */
#define COMP_HYST_HYST_Hyst50mV               (1UL) /*!< Comparator hysteresis enabled */


/* Peripheral: ECB */
/* Description: AES ECB Mode Encryption */

/* Register: ECB_TASKS_STARTECB */
/* Description: Start ECB block encrypt */

/* Bit 0 : Start ECB block encrypt */
#define ECB_TASKS_STARTECB_TASKS_STARTECB_Pos (0UL) /*!< Position of TASKS_STARTECB field. */
#define ECB_TASKS_STARTECB_TASKS_STARTECB_Msk                                                      \
  (0x1UL << ECB_TASKS_STARTECB_TASKS_STARTECB_Pos)      /*!< Bit mask of TASKS_STARTECB field. */
#define ECB_TASKS_STARTECB_TASKS_STARTECB_Trigger (1UL) /*!< Trigger task */

/* Register: ECB_TASKS_STOPECB */
/* Description: Abort a possible executing ECB operation */

/* Bit 0 : Abort a possible executing ECB operation */
#define ECB_TASKS_STOPECB_TASKS_STOPECB_Pos       (0UL) /*!< Position of TASKS_STOPECB field. */
#define ECB_TASKS_STOPECB_TASKS_STOPECB_Msk                                                        \
  (0x1UL << ECB_TASKS_STOPECB_TASKS_STOPECB_Pos)      /*!< Bit mask of TASKS_STOPECB field. */
#define ECB_TASKS_STOPECB_TASKS_STOPECB_Trigger (1UL) /*!< Trigger task */

/* Register: ECB_EVENTS_ENDECB */
/* Description: ECB block encrypt complete */

/* Bit 0 : ECB block encrypt complete */
#define ECB_EVENTS_ENDECB_EVENTS_ENDECB_Pos     (0UL) /*!< Position of EVENTS_ENDECB field. */
#define ECB_EVENTS_ENDECB_EVENTS_ENDECB_Msk                                                        \
  (0x1UL << ECB_EVENTS_ENDECB_EVENTS_ENDECB_Pos)           /*!< Bit mask of EVENTS_ENDECB field. */
#define ECB_EVENTS_ENDECB_EVENTS_ENDECB_NotGenerated (0UL) /*!< Event not generated */
#define ECB_EVENTS_ENDECB_EVENTS_ENDECB_Generated    (1UL) /*!< Event generated */

/* Register: ECB_EVENTS_ERRORECB */
/* Description: ECB block encrypt aborted because of a STOPECB task or due to an error */

/* Bit 0 : ECB block encrypt aborted because of a STOPECB task or due to an error */
#define ECB_EVENTS_ERRORECB_EVENTS_ERRORECB_Pos      (0UL) /*!< Position of EVENTS_ERRORECB field. */
#define ECB_EVENTS_ERRORECB_EVENTS_ERRORECB_Msk                                                    \
  (0x1UL << ECB_EVENTS_ERRORECB_EVENTS_ERRORECB_Pos) /*!< Bit mask of EVENTS_ERRORECB field. */
#define ECB_EVENTS_ERRORECB_EVENTS_ERRORECB_NotGenerated (0UL) /*!< Event not generated */
#define ECB_EVENTS_ERRORECB_EVENTS_ERRORECB_Generated    (1UL) /*!< Event generated */

/* Register: ECB_INTENSET */
/* Description: Enable interrupt */

/* Bit 1 : Write '1' to enable interrupt for event ERRORECB */
#define ECB_INTENSET_ERRORECB_Pos                        (1UL) /*!< Position of ERRORECB field. */
#define ECB_INTENSET_ERRORECB_Msk                                                                  \
  (0x1UL << ECB_INTENSET_ERRORECB_Pos)       /*!< Bit mask of ERRORECB field. */
#define ECB_INTENSET_ERRORECB_Disabled (0UL) /*!< Read: Disabled */
#define ECB_INTENSET_ERRORECB_Enabled  (1UL) /*!< Read: Enabled */
#define ECB_INTENSET_ERRORECB_Set      (1UL) /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event ENDECB */
#define ECB_INTENSET_ENDECB_Pos        (0UL) /*!< Position of ENDECB field. */
#define ECB_INTENSET_ENDECB_Msk        (0x1UL << ECB_INTENSET_ENDECB_Pos) /*!< Bit mask of ENDECB field. */
#define ECB_INTENSET_ENDECB_Disabled   (0UL)                              /*!< Read: Disabled */
#define ECB_INTENSET_ENDECB_Enabled    (1UL)                              /*!< Read: Enabled */
#define ECB_INTENSET_ENDECB_Set        (1UL)                              /*!< Enable */

/* Register: ECB_INTENCLR */
/* Description: Disable interrupt */

/* Bit 1 : Write '1' to disable interrupt for event ERRORECB */
#define ECB_INTENCLR_ERRORECB_Pos      (1UL) /*!< Position of ERRORECB field. */
#define ECB_INTENCLR_ERRORECB_Msk                                                                  \
  (0x1UL << ECB_INTENCLR_ERRORECB_Pos)       /*!< Bit mask of ERRORECB field. */
#define ECB_INTENCLR_ERRORECB_Disabled (0UL) /*!< Read: Disabled */
#define ECB_INTENCLR_ERRORECB_Enabled  (1UL) /*!< Read: Enabled */
#define ECB_INTENCLR_ERRORECB_Clear    (1UL) /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event ENDECB */
#define ECB_INTENCLR_ENDECB_Pos        (0UL) /*!< Position of ENDECB field. */
#define ECB_INTENCLR_ENDECB_Msk        (0x1UL << ECB_INTENCLR_ENDECB_Pos) /*!< Bit mask of ENDECB field. */
#define ECB_INTENCLR_ENDECB_Disabled   (0UL)                              /*!< Read: Disabled */
#define ECB_INTENCLR_ENDECB_Enabled    (1UL)                              /*!< Read: Enabled */
#define ECB_INTENCLR_ENDECB_Clear      (1UL)                              /*!< Disable */

/* Register: ECB_ECBDATAPTR */
/* Description: ECB block encrypt memory pointers */

/* Bits 31..0 : Pointer to the ECB data structure (see Table 1 ECB data structure overview) */
#define ECB_ECBDATAPTR_ECBDATAPTR_Pos  (0UL) /*!< Position of ECBDATAPTR field. */
#define ECB_ECBDATAPTR_ECBDATAPTR_Msk                                                              \
  (0xFFFFFFFFUL << ECB_ECBDATAPTR_ECBDATAPTR_Pos) /*!< Bit mask of ECBDATAPTR field. */


/* Peripheral: EGU */
/* Description: Event generator unit 0 */

/* Register: EGU_TASKS_TRIGGER */
/* Description: Description collection: Trigger n for triggering the corresponding TRIGGERED[n] event */

/* Bit 0 : Trigger n for triggering the corresponding TRIGGERED[n] event */
#define EGU_TASKS_TRIGGER_TASKS_TRIGGER_Pos (0UL) /*!< Position of TASKS_TRIGGER field. */
#define EGU_TASKS_TRIGGER_TASKS_TRIGGER_Msk                                                        \
  (0x1UL << EGU_TASKS_TRIGGER_TASKS_TRIGGER_Pos)        /*!< Bit mask of TASKS_TRIGGER field. */
#define EGU_TASKS_TRIGGER_TASKS_TRIGGER_Trigger   (1UL) /*!< Trigger task */

/* Register: EGU_EVENTS_TRIGGERED */
/* Description: Description collection: Event number n generated by triggering the corresponding TRIGGER[n] task */

/* Bit 0 : Event number n generated by triggering the corresponding TRIGGER[n] task */
#define EGU_EVENTS_TRIGGERED_EVENTS_TRIGGERED_Pos (0UL) /*!< Position of EVENTS_TRIGGERED field. */
#define EGU_EVENTS_TRIGGERED_EVENTS_TRIGGERED_Msk                                                  \
  (0x1UL << EGU_EVENTS_TRIGGERED_EVENTS_TRIGGERED_Pos) /*!< Bit mask of EVENTS_TRIGGERED field. */
#define EGU_EVENTS_TRIGGERED_EVENTS_TRIGGERED_NotGenerated (0UL) /*!< Event not generated */
#define EGU_EVENTS_TRIGGERED_EVENTS_TRIGGERED_Generated    (1UL) /*!< Event generated */

/* Register: EGU_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 15 : Enable or disable interrupt for event TRIGGERED[15] */
#define EGU_INTEN_TRIGGERED15_Pos                          (15UL) /*!< Position of TRIGGERED15 field. */
#define EGU_INTEN_TRIGGERED15_Msk                                                                  \
  (0x1UL << EGU_INTEN_TRIGGERED15_Pos)       /*!< Bit mask of TRIGGERED15 field. */
#define EGU_INTEN_TRIGGERED15_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED15_Enabled  (1UL) /*!< Enable */

/* Bit 14 : Enable or disable interrupt for event TRIGGERED[14] */
#define EGU_INTEN_TRIGGERED14_Pos      (14UL) /*!< Position of TRIGGERED14 field. */
#define EGU_INTEN_TRIGGERED14_Msk                                                                  \
  (0x1UL << EGU_INTEN_TRIGGERED14_Pos)       /*!< Bit mask of TRIGGERED14 field. */
#define EGU_INTEN_TRIGGERED14_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED14_Enabled  (1UL) /*!< Enable */

/* Bit 13 : Enable or disable interrupt for event TRIGGERED[13] */
#define EGU_INTEN_TRIGGERED13_Pos      (13UL) /*!< Position of TRIGGERED13 field. */
#define EGU_INTEN_TRIGGERED13_Msk                                                                  \
  (0x1UL << EGU_INTEN_TRIGGERED13_Pos)       /*!< Bit mask of TRIGGERED13 field. */
#define EGU_INTEN_TRIGGERED13_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED13_Enabled  (1UL) /*!< Enable */

/* Bit 12 : Enable or disable interrupt for event TRIGGERED[12] */
#define EGU_INTEN_TRIGGERED12_Pos      (12UL) /*!< Position of TRIGGERED12 field. */
#define EGU_INTEN_TRIGGERED12_Msk                                                                  \
  (0x1UL << EGU_INTEN_TRIGGERED12_Pos)       /*!< Bit mask of TRIGGERED12 field. */
#define EGU_INTEN_TRIGGERED12_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED12_Enabled  (1UL) /*!< Enable */

/* Bit 11 : Enable or disable interrupt for event TRIGGERED[11] */
#define EGU_INTEN_TRIGGERED11_Pos      (11UL) /*!< Position of TRIGGERED11 field. */
#define EGU_INTEN_TRIGGERED11_Msk                                                                  \
  (0x1UL << EGU_INTEN_TRIGGERED11_Pos)       /*!< Bit mask of TRIGGERED11 field. */
#define EGU_INTEN_TRIGGERED11_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED11_Enabled  (1UL) /*!< Enable */

/* Bit 10 : Enable or disable interrupt for event TRIGGERED[10] */
#define EGU_INTEN_TRIGGERED10_Pos      (10UL) /*!< Position of TRIGGERED10 field. */
#define EGU_INTEN_TRIGGERED10_Msk                                                                  \
  (0x1UL << EGU_INTEN_TRIGGERED10_Pos)       /*!< Bit mask of TRIGGERED10 field. */
#define EGU_INTEN_TRIGGERED10_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED10_Enabled  (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for event TRIGGERED[9] */
#define EGU_INTEN_TRIGGERED9_Pos       (9UL) /*!< Position of TRIGGERED9 field. */
#define EGU_INTEN_TRIGGERED9_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED9_Pos)       /*!< Bit mask of TRIGGERED9 field. */
#define EGU_INTEN_TRIGGERED9_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED9_Enabled  (1UL) /*!< Enable */

/* Bit 8 : Enable or disable interrupt for event TRIGGERED[8] */
#define EGU_INTEN_TRIGGERED8_Pos      (8UL) /*!< Position of TRIGGERED8 field. */
#define EGU_INTEN_TRIGGERED8_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED8_Pos)       /*!< Bit mask of TRIGGERED8 field. */
#define EGU_INTEN_TRIGGERED8_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED8_Enabled  (1UL) /*!< Enable */

/* Bit 7 : Enable or disable interrupt for event TRIGGERED[7] */
#define EGU_INTEN_TRIGGERED7_Pos      (7UL) /*!< Position of TRIGGERED7 field. */
#define EGU_INTEN_TRIGGERED7_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED7_Pos)       /*!< Bit mask of TRIGGERED7 field. */
#define EGU_INTEN_TRIGGERED7_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED7_Enabled  (1UL) /*!< Enable */

/* Bit 6 : Enable or disable interrupt for event TRIGGERED[6] */
#define EGU_INTEN_TRIGGERED6_Pos      (6UL) /*!< Position of TRIGGERED6 field. */
#define EGU_INTEN_TRIGGERED6_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED6_Pos)       /*!< Bit mask of TRIGGERED6 field. */
#define EGU_INTEN_TRIGGERED6_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED6_Enabled  (1UL) /*!< Enable */

/* Bit 5 : Enable or disable interrupt for event TRIGGERED[5] */
#define EGU_INTEN_TRIGGERED5_Pos      (5UL) /*!< Position of TRIGGERED5 field. */
#define EGU_INTEN_TRIGGERED5_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED5_Pos)       /*!< Bit mask of TRIGGERED5 field. */
#define EGU_INTEN_TRIGGERED5_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED5_Enabled  (1UL) /*!< Enable */

/* Bit 4 : Enable or disable interrupt for event TRIGGERED[4] */
#define EGU_INTEN_TRIGGERED4_Pos      (4UL) /*!< Position of TRIGGERED4 field. */
#define EGU_INTEN_TRIGGERED4_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED4_Pos)       /*!< Bit mask of TRIGGERED4 field. */
#define EGU_INTEN_TRIGGERED4_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED4_Enabled  (1UL) /*!< Enable */

/* Bit 3 : Enable or disable interrupt for event TRIGGERED[3] */
#define EGU_INTEN_TRIGGERED3_Pos      (3UL) /*!< Position of TRIGGERED3 field. */
#define EGU_INTEN_TRIGGERED3_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED3_Pos)       /*!< Bit mask of TRIGGERED3 field. */
#define EGU_INTEN_TRIGGERED3_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED3_Enabled  (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for event TRIGGERED[2] */
#define EGU_INTEN_TRIGGERED2_Pos      (2UL) /*!< Position of TRIGGERED2 field. */
#define EGU_INTEN_TRIGGERED2_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED2_Pos)       /*!< Bit mask of TRIGGERED2 field. */
#define EGU_INTEN_TRIGGERED2_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED2_Enabled  (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for event TRIGGERED[1] */
#define EGU_INTEN_TRIGGERED1_Pos      (1UL) /*!< Position of TRIGGERED1 field. */
#define EGU_INTEN_TRIGGERED1_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED1_Pos)       /*!< Bit mask of TRIGGERED1 field. */
#define EGU_INTEN_TRIGGERED1_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED1_Enabled  (1UL) /*!< Enable */

/* Bit 0 : Enable or disable interrupt for event TRIGGERED[0] */
#define EGU_INTEN_TRIGGERED0_Pos      (0UL) /*!< Position of TRIGGERED0 field. */
#define EGU_INTEN_TRIGGERED0_Msk                                                                   \
  (0x1UL << EGU_INTEN_TRIGGERED0_Pos)       /*!< Bit mask of TRIGGERED0 field. */
#define EGU_INTEN_TRIGGERED0_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED0_Enabled  (1UL) /*!< Enable */

/* Register: EGU_INTENSET */
/* Description: Enable interrupt */

/* Bit 15 : Write '1' to enable interrupt for event TRIGGERED[15] */
#define EGU_INTENSET_TRIGGERED15_Pos  (15UL) /*!< Position of TRIGGERED15 field. */
#define EGU_INTENSET_TRIGGERED15_Msk                                                               \
  (0x1UL << EGU_INTENSET_TRIGGERED15_Pos)       /*!< Bit mask of TRIGGERED15 field. */
#define EGU_INTENSET_TRIGGERED15_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED15_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED15_Set      (1UL) /*!< Enable */

/* Bit 14 : Write '1' to enable interrupt for event TRIGGERED[14] */
#define EGU_INTENSET_TRIGGERED14_Pos      (14UL) /*!< Position of TRIGGERED14 field. */
#define EGU_INTENSET_TRIGGERED14_Msk                                                               \
  (0x1UL << EGU_INTENSET_TRIGGERED14_Pos)       /*!< Bit mask of TRIGGERED14 field. */
#define EGU_INTENSET_TRIGGERED14_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED14_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED14_Set      (1UL) /*!< Enable */

/* Bit 13 : Write '1' to enable interrupt for event TRIGGERED[13] */
#define EGU_INTENSET_TRIGGERED13_Pos      (13UL) /*!< Position of TRIGGERED13 field. */
#define EGU_INTENSET_TRIGGERED13_Msk                                                               \
  (0x1UL << EGU_INTENSET_TRIGGERED13_Pos)       /*!< Bit mask of TRIGGERED13 field. */
#define EGU_INTENSET_TRIGGERED13_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED13_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED13_Set      (1UL) /*!< Enable */

/* Bit 12 : Write '1' to enable interrupt for event TRIGGERED[12] */
#define EGU_INTENSET_TRIGGERED12_Pos      (12UL) /*!< Position of TRIGGERED12 field. */
#define EGU_INTENSET_TRIGGERED12_Msk                                                               \
  (0x1UL << EGU_INTENSET_TRIGGERED12_Pos)       /*!< Bit mask of TRIGGERED12 field. */
#define EGU_INTENSET_TRIGGERED12_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED12_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED12_Set      (1UL) /*!< Enable */

/* Bit 11 : Write '1' to enable interrupt for event TRIGGERED[11] */
#define EGU_INTENSET_TRIGGERED11_Pos      (11UL) /*!< Position of TRIGGERED11 field. */
#define EGU_INTENSET_TRIGGERED11_Msk                                                               \
  (0x1UL << EGU_INTENSET_TRIGGERED11_Pos)       /*!< Bit mask of TRIGGERED11 field. */
#define EGU_INTENSET_TRIGGERED11_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED11_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED11_Set      (1UL) /*!< Enable */

/* Bit 10 : Write '1' to enable interrupt for event TRIGGERED[10] */
#define EGU_INTENSET_TRIGGERED10_Pos      (10UL) /*!< Position of TRIGGERED10 field. */
#define EGU_INTENSET_TRIGGERED10_Msk                                                               \
  (0x1UL << EGU_INTENSET_TRIGGERED10_Pos)       /*!< Bit mask of TRIGGERED10 field. */
#define EGU_INTENSET_TRIGGERED10_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED10_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED10_Set      (1UL) /*!< Enable */

/* Bit 9 : Write '1' to enable interrupt for event TRIGGERED[9] */
#define EGU_INTENSET_TRIGGERED9_Pos       (9UL) /*!< Position of TRIGGERED9 field. */
#define EGU_INTENSET_TRIGGERED9_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED9_Pos)       /*!< Bit mask of TRIGGERED9 field. */
#define EGU_INTENSET_TRIGGERED9_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED9_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED9_Set      (1UL) /*!< Enable */

/* Bit 8 : Write '1' to enable interrupt for event TRIGGERED[8] */
#define EGU_INTENSET_TRIGGERED8_Pos      (8UL) /*!< Position of TRIGGERED8 field. */
#define EGU_INTENSET_TRIGGERED8_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED8_Pos)       /*!< Bit mask of TRIGGERED8 field. */
#define EGU_INTENSET_TRIGGERED8_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED8_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED8_Set      (1UL) /*!< Enable */

/* Bit 7 : Write '1' to enable interrupt for event TRIGGERED[7] */
#define EGU_INTENSET_TRIGGERED7_Pos      (7UL) /*!< Position of TRIGGERED7 field. */
#define EGU_INTENSET_TRIGGERED7_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED7_Pos)       /*!< Bit mask of TRIGGERED7 field. */
#define EGU_INTENSET_TRIGGERED7_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED7_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED7_Set      (1UL) /*!< Enable */

/* Bit 6 : Write '1' to enable interrupt for event TRIGGERED[6] */
#define EGU_INTENSET_TRIGGERED6_Pos      (6UL) /*!< Position of TRIGGERED6 field. */
#define EGU_INTENSET_TRIGGERED6_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED6_Pos)       /*!< Bit mask of TRIGGERED6 field. */
#define EGU_INTENSET_TRIGGERED6_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED6_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED6_Set      (1UL) /*!< Enable */

/* Bit 5 : Write '1' to enable interrupt for event TRIGGERED[5] */
#define EGU_INTENSET_TRIGGERED5_Pos      (5UL) /*!< Position of TRIGGERED5 field. */
#define EGU_INTENSET_TRIGGERED5_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED5_Pos)       /*!< Bit mask of TRIGGERED5 field. */
#define EGU_INTENSET_TRIGGERED5_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED5_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED5_Set      (1UL) /*!< Enable */

/* Bit 4 : Write '1' to enable interrupt for event TRIGGERED[4] */
#define EGU_INTENSET_TRIGGERED4_Pos      (4UL) /*!< Position of TRIGGERED4 field. */
#define EGU_INTENSET_TRIGGERED4_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED4_Pos)       /*!< Bit mask of TRIGGERED4 field. */
#define EGU_INTENSET_TRIGGERED4_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED4_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED4_Set      (1UL) /*!< Enable */

/* Bit 3 : Write '1' to enable interrupt for event TRIGGERED[3] */
#define EGU_INTENSET_TRIGGERED3_Pos      (3UL) /*!< Position of TRIGGERED3 field. */
#define EGU_INTENSET_TRIGGERED3_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED3_Pos)       /*!< Bit mask of TRIGGERED3 field. */
#define EGU_INTENSET_TRIGGERED3_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED3_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED3_Set      (1UL) /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event TRIGGERED[2] */
#define EGU_INTENSET_TRIGGERED2_Pos      (2UL) /*!< Position of TRIGGERED2 field. */
#define EGU_INTENSET_TRIGGERED2_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED2_Pos)       /*!< Bit mask of TRIGGERED2 field. */
#define EGU_INTENSET_TRIGGERED2_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED2_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED2_Set      (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event TRIGGERED[1] */
#define EGU_INTENSET_TRIGGERED1_Pos      (1UL) /*!< Position of TRIGGERED1 field. */
#define EGU_INTENSET_TRIGGERED1_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED1_Pos)       /*!< Bit mask of TRIGGERED1 field. */
#define EGU_INTENSET_TRIGGERED1_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED1_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED1_Set      (1UL) /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event TRIGGERED[0] */
#define EGU_INTENSET_TRIGGERED0_Pos      (0UL) /*!< Position of TRIGGERED0 field. */
#define EGU_INTENSET_TRIGGERED0_Msk                                                                \
  (0x1UL << EGU_INTENSET_TRIGGERED0_Pos)       /*!< Bit mask of TRIGGERED0 field. */
#define EGU_INTENSET_TRIGGERED0_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED0_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED0_Set      (1UL) /*!< Enable */

/* Register: EGU_INTENCLR */
/* Description: Disable interrupt */

/* Bit 15 : Write '1' to disable interrupt for event TRIGGERED[15] */
#define EGU_INTENCLR_TRIGGERED15_Pos     (15UL) /*!< Position of TRIGGERED15 field. */
#define EGU_INTENCLR_TRIGGERED15_Msk                                                               \
  (0x1UL << EGU_INTENCLR_TRIGGERED15_Pos)       /*!< Bit mask of TRIGGERED15 field. */
#define EGU_INTENCLR_TRIGGERED15_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED15_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED15_Clear    (1UL) /*!< Disable */

/* Bit 14 : Write '1' to disable interrupt for event TRIGGERED[14] */
#define EGU_INTENCLR_TRIGGERED14_Pos      (14UL) /*!< Position of TRIGGERED14 field. */
#define EGU_INTENCLR_TRIGGERED14_Msk                                                               \
  (0x1UL << EGU_INTENCLR_TRIGGERED14_Pos)       /*!< Bit mask of TRIGGERED14 field. */
#define EGU_INTENCLR_TRIGGERED14_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED14_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED14_Clear    (1UL) /*!< Disable */

/* Bit 13 : Write '1' to disable interrupt for event TRIGGERED[13] */
#define EGU_INTENCLR_TRIGGERED13_Pos      (13UL) /*!< Position of TRIGGERED13 field. */
#define EGU_INTENCLR_TRIGGERED13_Msk                                                               \
  (0x1UL << EGU_INTENCLR_TRIGGERED13_Pos)       /*!< Bit mask of TRIGGERED13 field. */
#define EGU_INTENCLR_TRIGGERED13_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED13_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED13_Clear    (1UL) /*!< Disable */

/* Bit 12 : Write '1' to disable interrupt for event TRIGGERED[12] */
#define EGU_INTENCLR_TRIGGERED12_Pos      (12UL) /*!< Position of TRIGGERED12 field. */
#define EGU_INTENCLR_TRIGGERED12_Msk                                                               \
  (0x1UL << EGU_INTENCLR_TRIGGERED12_Pos)       /*!< Bit mask of TRIGGERED12 field. */
#define EGU_INTENCLR_TRIGGERED12_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED12_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED12_Clear    (1UL) /*!< Disable */

/* Bit 11 : Write '1' to disable interrupt for event TRIGGERED[11] */
#define EGU_INTENCLR_TRIGGERED11_Pos      (11UL) /*!< Position of TRIGGERED11 field. */
#define EGU_INTENCLR_TRIGGERED11_Msk                                                               \
  (0x1UL << EGU_INTENCLR_TRIGGERED11_Pos)       /*!< Bit mask of TRIGGERED11 field. */
#define EGU_INTENCLR_TRIGGERED11_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED11_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED11_Clear    (1UL) /*!< Disable */

/* Bit 10 : Write '1' to disable interrupt for event TRIGGERED[10] */
#define EGU_INTENCLR_TRIGGERED10_Pos      (10UL) /*!< Position of TRIGGERED10 field. */
#define EGU_INTENCLR_TRIGGERED10_Msk                                                               \
  (0x1UL << EGU_INTENCLR_TRIGGERED10_Pos)       /*!< Bit mask of TRIGGERED10 field. */
#define EGU_INTENCLR_TRIGGERED10_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED10_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED10_Clear    (1UL) /*!< Disable */

/* Bit 9 : Write '1' to disable interrupt for event TRIGGERED[9] */
#define EGU_INTENCLR_TRIGGERED9_Pos       (9UL) /*!< Position of TRIGGERED9 field. */
#define EGU_INTENCLR_TRIGGERED9_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED9_Pos)       /*!< Bit mask of TRIGGERED9 field. */
#define EGU_INTENCLR_TRIGGERED9_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED9_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED9_Clear    (1UL) /*!< Disable */

/* Bit 8 : Write '1' to disable interrupt for event TRIGGERED[8] */
#define EGU_INTENCLR_TRIGGERED8_Pos      (8UL) /*!< Position of TRIGGERED8 field. */
#define EGU_INTENCLR_TRIGGERED8_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED8_Pos)       /*!< Bit mask of TRIGGERED8 field. */
#define EGU_INTENCLR_TRIGGERED8_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED8_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED8_Clear    (1UL) /*!< Disable */

/* Bit 7 : Write '1' to disable interrupt for event TRIGGERED[7] */
#define EGU_INTENCLR_TRIGGERED7_Pos      (7UL) /*!< Position of TRIGGERED7 field. */
#define EGU_INTENCLR_TRIGGERED7_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED7_Pos)       /*!< Bit mask of TRIGGERED7 field. */
#define EGU_INTENCLR_TRIGGERED7_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED7_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED7_Clear    (1UL) /*!< Disable */

/* Bit 6 : Write '1' to disable interrupt for event TRIGGERED[6] */
#define EGU_INTENCLR_TRIGGERED6_Pos      (6UL) /*!< Position of TRIGGERED6 field. */
#define EGU_INTENCLR_TRIGGERED6_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED6_Pos)       /*!< Bit mask of TRIGGERED6 field. */
#define EGU_INTENCLR_TRIGGERED6_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED6_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED6_Clear    (1UL) /*!< Disable */

/* Bit 5 : Write '1' to disable interrupt for event TRIGGERED[5] */
#define EGU_INTENCLR_TRIGGERED5_Pos      (5UL) /*!< Position of TRIGGERED5 field. */
#define EGU_INTENCLR_TRIGGERED5_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED5_Pos)       /*!< Bit mask of TRIGGERED5 field. */
#define EGU_INTENCLR_TRIGGERED5_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED5_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED5_Clear    (1UL) /*!< Disable */

/* Bit 4 : Write '1' to disable interrupt for event TRIGGERED[4] */
#define EGU_INTENCLR_TRIGGERED4_Pos      (4UL) /*!< Position of TRIGGERED4 field. */
#define EGU_INTENCLR_TRIGGERED4_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED4_Pos)       /*!< Bit mask of TRIGGERED4 field. */
#define EGU_INTENCLR_TRIGGERED4_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED4_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED4_Clear    (1UL) /*!< Disable */

/* Bit 3 : Write '1' to disable interrupt for event TRIGGERED[3] */
#define EGU_INTENCLR_TRIGGERED3_Pos      (3UL) /*!< Position of TRIGGERED3 field. */
#define EGU_INTENCLR_TRIGGERED3_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED3_Pos)       /*!< Bit mask of TRIGGERED3 field. */
#define EGU_INTENCLR_TRIGGERED3_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED3_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED3_Clear    (1UL) /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event TRIGGERED[2] */
#define EGU_INTENCLR_TRIGGERED2_Pos      (2UL) /*!< Position of TRIGGERED2 field. */
#define EGU_INTENCLR_TRIGGERED2_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED2_Pos)       /*!< Bit mask of TRIGGERED2 field. */
#define EGU_INTENCLR_TRIGGERED2_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED2_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED2_Clear    (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event TRIGGERED[1] */
#define EGU_INTENCLR_TRIGGERED1_Pos      (1UL) /*!< Position of TRIGGERED1 field. */
#define EGU_INTENCLR_TRIGGERED1_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED1_Pos)       /*!< Bit mask of TRIGGERED1 field. */
#define EGU_INTENCLR_TRIGGERED1_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED1_Enabled  (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED1_Clear    (1UL) /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event TRIGGERED[0] */
#define EGU_INTENCLR_TRIGGERED0_Pos      (0UL) /*!< Position of TRIGGERED0 field. */
#define EGU_INTENCLR_TRIGGERED0_Msk                                                                \
  (0x1UL << EGU_INTENCLR_TRIGGERED0_Pos)         /*!< Bit mask of TRIGGERED0 field. */
#define EGU_INTENCLR_TRIGGERED0_Disabled   (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED0_Enabled    (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED0_Clear      (1UL) /*!< Disable */


/* Peripheral: FICR */
/* Description: Factory information configuration registers */

/* Register: FICR_CODEPAGESIZE */
/* Description: Code memory page size */

/* Bits 31..0 : Code memory page size */
#define FICR_CODEPAGESIZE_CODEPAGESIZE_Pos (0UL) /*!< Position of CODEPAGESIZE field. */
#define FICR_CODEPAGESIZE_CODEPAGESIZE_Msk                                                         \
  (0xFFFFFFFFUL << FICR_CODEPAGESIZE_CODEPAGESIZE_Pos) /*!< Bit mask of CODEPAGESIZE field. */

/* Register: FICR_CODESIZE */
/* Description: Code memory size */

/* Bits 31..0 : Code memory size in number of pages */
#define FICR_CODESIZE_CODESIZE_Pos (0UL) /*!< Position of CODESIZE field. */
#define FICR_CODESIZE_CODESIZE_Msk                                                                 \
  (0xFFFFFFFFUL << FICR_CODESIZE_CODESIZE_Pos) /*!< Bit mask of CODESIZE field. */

/* Register: FICR_DEVICEID */
/* Description: Description collection: Device identifier */

/* Bits 31..0 : 64 bit unique device identifier */
#define FICR_DEVICEID_DEVICEID_Pos (0UL) /*!< Position of DEVICEID field. */
#define FICR_DEVICEID_DEVICEID_Msk                                                                 \
  (0xFFFFFFFFUL << FICR_DEVICEID_DEVICEID_Pos) /*!< Bit mask of DEVICEID field. */

/* Register: FICR_ER */
/* Description: Description collection: Encryption root, word n */

/* Bits 31..0 : Encryption root, word n */
#define FICR_ER_ER_Pos                         (0UL) /*!< Position of ER field. */
#define FICR_ER_ER_Msk                         (0xFFFFFFFFUL << FICR_ER_ER_Pos) /*!< Bit mask of ER field. */

/* Register: FICR_IR */
/* Description: Description collection: Identity Root, word n */

/* Bits 31..0 : Identity Root, word n */
#define FICR_IR_IR_Pos                         (0UL) /*!< Position of IR field. */
#define FICR_IR_IR_Msk                         (0xFFFFFFFFUL << FICR_IR_IR_Pos) /*!< Bit mask of IR field. */

/* Register: FICR_DEVICEADDRTYPE */
/* Description: Device address type */

/* Bit 0 : Device address type */
#define FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Pos (0UL) /*!< Position of DEVICEADDRTYPE field. */
#define FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Msk                                                     \
  (0x1UL << FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Pos)     /*!< Bit mask of DEVICEADDRTYPE field. */
#define FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Public (0UL) /*!< Public address */
#define FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Random (1UL) /*!< Random address */

/* Register: FICR_DEVICEADDR */
/* Description: Description collection: Device address n */

/* Bits 31..0 : 48 bit device address */
#define FICR_DEVICEADDR_DEVICEADDR_Pos            (0UL) /*!< Position of DEVICEADDR field. */
#define FICR_DEVICEADDR_DEVICEADDR_Msk                                                             \
  (0xFFFFFFFFUL << FICR_DEVICEADDR_DEVICEADDR_Pos) /*!< Bit mask of DEVICEADDR field. */

/* Register: FICR_INFO_PART */
/* Description: Part code */

/* Bits 31..0 : Part code */
#define FICR_INFO_PART_PART_Pos (0UL) /*!< Position of PART field. */
#define FICR_INFO_PART_PART_Msk                                                                    \
  (0xFFFFFFFFUL << FICR_INFO_PART_PART_Pos)            /*!< Bit mask of PART field. */
#define FICR_INFO_PART_PART_N52820      (0x52820UL)    /*!< nRF52820 */
#define FICR_INFO_PART_PART_N52833      (0x52833UL)    /*!< nRF52833 */
#define FICR_INFO_PART_PART_N52840      (0x52840UL)    /*!< nRF52840 */
#define FICR_INFO_PART_PART_Unspecified (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_INFO_VARIANT */
/* Description: Build code (hardware version and production configuration) */

/* Bits 31..0 : Build code (hardware version and production configuration). Encoded as ASCII. */
#define FICR_INFO_VARIANT_VARIANT_Pos   (0UL) /*!< Position of VARIANT field. */
#define FICR_INFO_VARIANT_VARIANT_Msk                                                              \
  (0xFFFFFFFFUL << FICR_INFO_VARIANT_VARIANT_Pos)            /*!< Bit mask of VARIANT field. */
#define FICR_INFO_VARIANT_VARIANT_AAAA        (0x41414141UL) /*!< AAAA */
#define FICR_INFO_VARIANT_VARIANT_Unspecified (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_INFO_PACKAGE */
/* Description: Package option */

/* Bits 31..0 : Package option */
#define FICR_INFO_PACKAGE_PACKAGE_Pos         (0UL) /*!< Position of PACKAGE field. */
#define FICR_INFO_PACKAGE_PACKAGE_Msk                                                              \
  (0xFFFFFFFFUL << FICR_INFO_PACKAGE_PACKAGE_Pos)            /*!< Bit mask of PACKAGE field. */
#define FICR_INFO_PACKAGE_PACKAGE_QD          (0x2007UL)     /*!< QDxx - 40-pin QFN */
#define FICR_INFO_PACKAGE_PACKAGE_Unspecified (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_INFO_RAM */
/* Description: RAM variant */

/* Bits 31..0 : RAM variant */
#define FICR_INFO_RAM_RAM_Pos                 (0UL) /*!< Position of RAM field. */
#define FICR_INFO_RAM_RAM_Msk                 (0xFFFFFFFFUL << FICR_INFO_RAM_RAM_Pos) /*!< Bit mask of RAM field. */
#define FICR_INFO_RAM_RAM_K16                 (0x10UL)       /*!< 16 kByte RAM */
#define FICR_INFO_RAM_RAM_K32                 (0x20UL)       /*!< 32 kByte RAM */
#define FICR_INFO_RAM_RAM_K64                 (0x40UL)       /*!< 64 kByte RAM */
#define FICR_INFO_RAM_RAM_K128                (0x80UL)       /*!< 128 kByte RAM */
#define FICR_INFO_RAM_RAM_K256                (0x100UL)      /*!< 256 kByte RAM */
#define FICR_INFO_RAM_RAM_Unspecified         (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_INFO_FLASH */
/* Description: Flash variant */

/* Bits 31..0 : Flash variant */
#define FICR_INFO_FLASH_FLASH_Pos             (0UL) /*!< Position of FLASH field. */
#define FICR_INFO_FLASH_FLASH_Msk                                                                  \
  (0xFFFFFFFFUL << FICR_INFO_FLASH_FLASH_Pos)            /*!< Bit mask of FLASH field. */
#define FICR_INFO_FLASH_FLASH_K128        (0x80UL)       /*!< 128 kByte FLASH */
#define FICR_INFO_FLASH_FLASH_K256        (0x100UL)      /*!< 256 kByte FLASH */
#define FICR_INFO_FLASH_FLASH_K512        (0x200UL)      /*!< 512 kByte FLASH */
#define FICR_INFO_FLASH_FLASH_K1024       (0x400UL)      /*!< 1 MByte FLASH */
#define FICR_INFO_FLASH_FLASH_K2048       (0x800UL)      /*!< 2 MByte FLASH */
#define FICR_INFO_FLASH_FLASH_Unspecified (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_PRODTEST */
/* Description: Description collection: Production test signature n */

/* Bits 31..0 : Production test signature n */
#define FICR_PRODTEST_PRODTEST_Pos        (0UL) /*!< Position of PRODTEST field. */
#define FICR_PRODTEST_PRODTEST_Msk                                                                 \
  (0xFFFFFFFFUL << FICR_PRODTEST_PRODTEST_Pos)        /*!< Bit mask of PRODTEST field. */
#define FICR_PRODTEST_PRODTEST_Done    (0xBB42319FUL) /*!< Production tests done */
#define FICR_PRODTEST_PRODTEST_NotDone (0xFFFFFFFFUL) /*!< Production tests not done */

/* Register: FICR_TEMP_A0 */
/* Description: Slope definition A0 */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A0_A_Pos             (0UL)                           /*!< Position of A field. */
#define FICR_TEMP_A0_A_Msk             (0xFFFUL << FICR_TEMP_A0_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A1 */
/* Description: Slope definition A1 */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A1_A_Pos             (0UL)                           /*!< Position of A field. */
#define FICR_TEMP_A1_A_Msk             (0xFFFUL << FICR_TEMP_A1_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A2 */
/* Description: Slope definition A2 */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A2_A_Pos             (0UL)                           /*!< Position of A field. */
#define FICR_TEMP_A2_A_Msk             (0xFFFUL << FICR_TEMP_A2_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A3 */
/* Description: Slope definition A3 */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A3_A_Pos             (0UL)                           /*!< Position of A field. */
#define FICR_TEMP_A3_A_Msk             (0xFFFUL << FICR_TEMP_A3_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A4 */
/* Description: Slope definition A4 */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A4_A_Pos             (0UL)                           /*!< Position of A field. */
#define FICR_TEMP_A4_A_Msk             (0xFFFUL << FICR_TEMP_A4_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A5 */
/* Description: Slope definition A5 */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A5_A_Pos             (0UL)                           /*!< Position of A field. */
#define FICR_TEMP_A5_A_Msk             (0xFFFUL << FICR_TEMP_A5_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_B0 */
/* Description: Y-intercept B0 */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B0_B_Pos             (0UL)                            /*!< Position of B field. */
#define FICR_TEMP_B0_B_Msk             (0x3FFFUL << FICR_TEMP_B0_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B1 */
/* Description: Y-intercept B1 */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B1_B_Pos             (0UL)                            /*!< Position of B field. */
#define FICR_TEMP_B1_B_Msk             (0x3FFFUL << FICR_TEMP_B1_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B2 */
/* Description: Y-intercept B2 */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B2_B_Pos             (0UL)                            /*!< Position of B field. */
#define FICR_TEMP_B2_B_Msk             (0x3FFFUL << FICR_TEMP_B2_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B3 */
/* Description: Y-intercept B3 */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B3_B_Pos             (0UL)                            /*!< Position of B field. */
#define FICR_TEMP_B3_B_Msk             (0x3FFFUL << FICR_TEMP_B3_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B4 */
/* Description: Y-intercept B4 */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B4_B_Pos             (0UL)                            /*!< Position of B field. */
#define FICR_TEMP_B4_B_Msk             (0x3FFFUL << FICR_TEMP_B4_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B5 */
/* Description: Y-intercept B5 */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B5_B_Pos             (0UL)                            /*!< Position of B field. */
#define FICR_TEMP_B5_B_Msk             (0x3FFFUL << FICR_TEMP_B5_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_T0 */
/* Description: Segment end T0 */

/* Bits 7..0 : T (segment end) register */
#define FICR_TEMP_T0_T_Pos             (0UL)                          /*!< Position of T field. */
#define FICR_TEMP_T0_T_Msk             (0xFFUL << FICR_TEMP_T0_T_Pos) /*!< Bit mask of T field. */

/* Register: FICR_TEMP_T1 */
/* Description: Segment end T1 */

/* Bits 7..0 : T (segment end) register */
#define FICR_TEMP_T1_T_Pos             (0UL)                          /*!< Position of T field. */
#define FICR_TEMP_T1_T_Msk             (0xFFUL << FICR_TEMP_T1_T_Pos) /*!< Bit mask of T field. */

/* Register: FICR_TEMP_T2 */
/* Description: Segment end T2 */

/* Bits 7..0 : T (segment end) register */
#define FICR_TEMP_T2_T_Pos             (0UL)                          /*!< Position of T field. */
#define FICR_TEMP_T2_T_Msk             (0xFFUL << FICR_TEMP_T2_T_Pos) /*!< Bit mask of T field. */

/* Register: FICR_TEMP_T3 */
/* Description: Segment end T3 */

/* Bits 7..0 : T (segment end) register */
#define FICR_TEMP_T3_T_Pos             (0UL)                          /*!< Position of T field. */
#define FICR_TEMP_T3_T_Msk             (0xFFUL << FICR_TEMP_T3_T_Pos) /*!< Bit mask of T field. */

/* Register: FICR_TEMP_T4 */
/* Description: Segment end T4 */

/* Bits 7..0 : T (segment end) register */
#define FICR_TEMP_T4_T_Pos             (0UL)                          /*!< Position of T field. */
#define FICR_TEMP_T4_T_Msk             (0xFFUL << FICR_TEMP_T4_T_Pos) /*!< Bit mask of T field. */


/* Peripheral: GPIOTE */
/* Description: GPIO Tasks and Events */

/* Register: GPIOTE_TASKS_OUT */
/* Description: Description collection: Task for writing to pin specified in CONFIG[n].PSEL. Action on pin is configured in CONFIG[n].POLARITY. */

/* Bit 0 : Task for writing to pin specified in CONFIG[n].PSEL. Action on pin is configured in CONFIG[n].POLARITY. */
#define GPIOTE_TASKS_OUT_TASKS_OUT_Pos (0UL) /*!< Position of TASKS_OUT field. */
#define GPIOTE_TASKS_OUT_TASKS_OUT_Msk                                                             \
  (0x1UL << GPIOTE_TASKS_OUT_TASKS_OUT_Pos)      /*!< Bit mask of TASKS_OUT field. */
#define GPIOTE_TASKS_OUT_TASKS_OUT_Trigger (1UL) /*!< Trigger task */

/* Register: GPIOTE_TASKS_SET */
/* Description: Description collection: Task for writing to pin specified in CONFIG[n].PSEL. Action on pin is to set it high. */

/* Bit 0 : Task for writing to pin specified in CONFIG[n].PSEL. Action on pin is to set it high. */
#define GPIOTE_TASKS_SET_TASKS_SET_Pos     (0UL) /*!< Position of TASKS_SET field. */
#define GPIOTE_TASKS_SET_TASKS_SET_Msk                                                             \
  (0x1UL << GPIOTE_TASKS_SET_TASKS_SET_Pos)      /*!< Bit mask of TASKS_SET field. */
#define GPIOTE_TASKS_SET_TASKS_SET_Trigger (1UL) /*!< Trigger task */

/* Register: GPIOTE_TASKS_CLR */
/* Description: Description collection: Task for writing to pin specified in CONFIG[n].PSEL. Action on pin is to set it low. */

/* Bit 0 : Task for writing to pin specified in CONFIG[n].PSEL. Action on pin is to set it low. */
#define GPIOTE_TASKS_CLR_TASKS_CLR_Pos     (0UL) /*!< Position of TASKS_CLR field. */
#define GPIOTE_TASKS_CLR_TASKS_CLR_Msk                                                             \
  (0x1UL << GPIOTE_TASKS_CLR_TASKS_CLR_Pos)      /*!< Bit mask of TASKS_CLR field. */
#define GPIOTE_TASKS_CLR_TASKS_CLR_Trigger (1UL) /*!< Trigger task */

/* Register: GPIOTE_EVENTS_IN */
/* Description: Description collection: Event generated from pin specified in CONFIG[n].PSEL */

/* Bit 0 : Event generated from pin specified in CONFIG[n].PSEL */
#define GPIOTE_EVENTS_IN_EVENTS_IN_Pos     (0UL) /*!< Position of EVENTS_IN field. */
#define GPIOTE_EVENTS_IN_EVENTS_IN_Msk                                                             \
  (0x1UL << GPIOTE_EVENTS_IN_EVENTS_IN_Pos)           /*!< Bit mask of EVENTS_IN field. */
#define GPIOTE_EVENTS_IN_EVENTS_IN_NotGenerated (0UL) /*!< Event not generated */
#define GPIOTE_EVENTS_IN_EVENTS_IN_Generated    (1UL) /*!< Event generated */

/* Register: GPIOTE_EVENTS_PORT */
/* Description: Event generated from multiple input GPIO pins with SENSE mechanism enabled */

/* Bit 0 : Event generated from multiple input GPIO pins with SENSE mechanism enabled */
#define GPIOTE_EVENTS_PORT_EVENTS_PORT_Pos      (0UL) /*!< Position of EVENTS_PORT field. */
#define GPIOTE_EVENTS_PORT_EVENTS_PORT_Msk                                                         \
  (0x1UL << GPIOTE_EVENTS_PORT_EVENTS_PORT_Pos)           /*!< Bit mask of EVENTS_PORT field. */
#define GPIOTE_EVENTS_PORT_EVENTS_PORT_NotGenerated (0UL) /*!< Event not generated */
#define GPIOTE_EVENTS_PORT_EVENTS_PORT_Generated    (1UL) /*!< Event generated */

/* Register: GPIOTE_INTENSET */
/* Description: Enable interrupt */

/* Bit 31 : Write '1' to enable interrupt for event PORT */
#define GPIOTE_INTENSET_PORT_Pos                    (31UL) /*!< Position of PORT field. */
#define GPIOTE_INTENSET_PORT_Msk                    (0x1UL << GPIOTE_INTENSET_PORT_Pos) /*!< Bit mask of PORT field. */
#define GPIOTE_INTENSET_PORT_Disabled               (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_PORT_Enabled                (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_PORT_Set                    (1UL) /*!< Enable */

/* Bit 7 : Write '1' to enable interrupt for event IN[7] */
#define GPIOTE_INTENSET_IN7_Pos                     (7UL) /*!< Position of IN7 field. */
#define GPIOTE_INTENSET_IN7_Msk                     (0x1UL << GPIOTE_INTENSET_IN7_Pos) /*!< Bit mask of IN7 field. */
#define GPIOTE_INTENSET_IN7_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN7_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN7_Set                     (1UL) /*!< Enable */

/* Bit 6 : Write '1' to enable interrupt for event IN[6] */
#define GPIOTE_INTENSET_IN6_Pos                     (6UL) /*!< Position of IN6 field. */
#define GPIOTE_INTENSET_IN6_Msk                     (0x1UL << GPIOTE_INTENSET_IN6_Pos) /*!< Bit mask of IN6 field. */
#define GPIOTE_INTENSET_IN6_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN6_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN6_Set                     (1UL) /*!< Enable */

/* Bit 5 : Write '1' to enable interrupt for event IN[5] */
#define GPIOTE_INTENSET_IN5_Pos                     (5UL) /*!< Position of IN5 field. */
#define GPIOTE_INTENSET_IN5_Msk                     (0x1UL << GPIOTE_INTENSET_IN5_Pos) /*!< Bit mask of IN5 field. */
#define GPIOTE_INTENSET_IN5_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN5_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN5_Set                     (1UL) /*!< Enable */

/* Bit 4 : Write '1' to enable interrupt for event IN[4] */
#define GPIOTE_INTENSET_IN4_Pos                     (4UL) /*!< Position of IN4 field. */
#define GPIOTE_INTENSET_IN4_Msk                     (0x1UL << GPIOTE_INTENSET_IN4_Pos) /*!< Bit mask of IN4 field. */
#define GPIOTE_INTENSET_IN4_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN4_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN4_Set                     (1UL) /*!< Enable */

/* Bit 3 : Write '1' to enable interrupt for event IN[3] */
#define GPIOTE_INTENSET_IN3_Pos                     (3UL) /*!< Position of IN3 field. */
#define GPIOTE_INTENSET_IN3_Msk                     (0x1UL << GPIOTE_INTENSET_IN3_Pos) /*!< Bit mask of IN3 field. */
#define GPIOTE_INTENSET_IN3_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN3_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN3_Set                     (1UL) /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event IN[2] */
#define GPIOTE_INTENSET_IN2_Pos                     (2UL) /*!< Position of IN2 field. */
#define GPIOTE_INTENSET_IN2_Msk                     (0x1UL << GPIOTE_INTENSET_IN2_Pos) /*!< Bit mask of IN2 field. */
#define GPIOTE_INTENSET_IN2_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN2_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN2_Set                     (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event IN[1] */
#define GPIOTE_INTENSET_IN1_Pos                     (1UL) /*!< Position of IN1 field. */
#define GPIOTE_INTENSET_IN1_Msk                     (0x1UL << GPIOTE_INTENSET_IN1_Pos) /*!< Bit mask of IN1 field. */
#define GPIOTE_INTENSET_IN1_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN1_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN1_Set                     (1UL) /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event IN[0] */
#define GPIOTE_INTENSET_IN0_Pos                     (0UL) /*!< Position of IN0 field. */
#define GPIOTE_INTENSET_IN0_Msk                     (0x1UL << GPIOTE_INTENSET_IN0_Pos) /*!< Bit mask of IN0 field. */
#define GPIOTE_INTENSET_IN0_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN0_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN0_Set                     (1UL) /*!< Enable */

/* Register: GPIOTE_INTENCLR */
/* Description: Disable interrupt */

/* Bit 31 : Write '1' to disable interrupt for event PORT */
#define GPIOTE_INTENCLR_PORT_Pos                    (31UL) /*!< Position of PORT field. */
#define GPIOTE_INTENCLR_PORT_Msk                    (0x1UL << GPIOTE_INTENCLR_PORT_Pos) /*!< Bit mask of PORT field. */
#define GPIOTE_INTENCLR_PORT_Disabled               (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_PORT_Enabled                (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_PORT_Clear                  (1UL) /*!< Disable */

/* Bit 7 : Write '1' to disable interrupt for event IN[7] */
#define GPIOTE_INTENCLR_IN7_Pos                     (7UL) /*!< Position of IN7 field. */
#define GPIOTE_INTENCLR_IN7_Msk                     (0x1UL << GPIOTE_INTENCLR_IN7_Pos) /*!< Bit mask of IN7 field. */
#define GPIOTE_INTENCLR_IN7_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN7_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN7_Clear                   (1UL) /*!< Disable */

/* Bit 6 : Write '1' to disable interrupt for event IN[6] */
#define GPIOTE_INTENCLR_IN6_Pos                     (6UL) /*!< Position of IN6 field. */
#define GPIOTE_INTENCLR_IN6_Msk                     (0x1UL << GPIOTE_INTENCLR_IN6_Pos) /*!< Bit mask of IN6 field. */
#define GPIOTE_INTENCLR_IN6_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN6_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN6_Clear                   (1UL) /*!< Disable */

/* Bit 5 : Write '1' to disable interrupt for event IN[5] */
#define GPIOTE_INTENCLR_IN5_Pos                     (5UL) /*!< Position of IN5 field. */
#define GPIOTE_INTENCLR_IN5_Msk                     (0x1UL << GPIOTE_INTENCLR_IN5_Pos) /*!< Bit mask of IN5 field. */
#define GPIOTE_INTENCLR_IN5_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN5_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN5_Clear                   (1UL) /*!< Disable */

/* Bit 4 : Write '1' to disable interrupt for event IN[4] */
#define GPIOTE_INTENCLR_IN4_Pos                     (4UL) /*!< Position of IN4 field. */
#define GPIOTE_INTENCLR_IN4_Msk                     (0x1UL << GPIOTE_INTENCLR_IN4_Pos) /*!< Bit mask of IN4 field. */
#define GPIOTE_INTENCLR_IN4_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN4_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN4_Clear                   (1UL) /*!< Disable */

/* Bit 3 : Write '1' to disable interrupt for event IN[3] */
#define GPIOTE_INTENCLR_IN3_Pos                     (3UL) /*!< Position of IN3 field. */
#define GPIOTE_INTENCLR_IN3_Msk                     (0x1UL << GPIOTE_INTENCLR_IN3_Pos) /*!< Bit mask of IN3 field. */
#define GPIOTE_INTENCLR_IN3_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN3_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN3_Clear                   (1UL) /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event IN[2] */
#define GPIOTE_INTENCLR_IN2_Pos                     (2UL) /*!< Position of IN2 field. */
#define GPIOTE_INTENCLR_IN2_Msk                     (0x1UL << GPIOTE_INTENCLR_IN2_Pos) /*!< Bit mask of IN2 field. */
#define GPIOTE_INTENCLR_IN2_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN2_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN2_Clear                   (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event IN[1] */
#define GPIOTE_INTENCLR_IN1_Pos                     (1UL) /*!< Position of IN1 field. */
#define GPIOTE_INTENCLR_IN1_Msk                     (0x1UL << GPIOTE_INTENCLR_IN1_Pos) /*!< Bit mask of IN1 field. */
#define GPIOTE_INTENCLR_IN1_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN1_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN1_Clear                   (1UL) /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event IN[0] */
#define GPIOTE_INTENCLR_IN0_Pos                     (0UL) /*!< Position of IN0 field. */
#define GPIOTE_INTENCLR_IN0_Msk                     (0x1UL << GPIOTE_INTENCLR_IN0_Pos) /*!< Bit mask of IN0 field. */
#define GPIOTE_INTENCLR_IN0_Disabled                (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN0_Enabled                 (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN0_Clear                   (1UL) /*!< Disable */

/* Register: GPIOTE_CONFIG */
/* Description: Description collection: Configuration for OUT[n], SET[n], and CLR[n] tasks and IN[n] event */

/* Bit 20 : When in task mode: Initial value of the output when the GPIOTE channel is configured. When in event mode: No effect. */
#define GPIOTE_CONFIG_OUTINIT_Pos                   (20UL) /*!< Position of OUTINIT field. */
#define GPIOTE_CONFIG_OUTINIT_Msk                                                                  \
  (0x1UL << GPIOTE_CONFIG_OUTINIT_Pos) /*!< Bit mask of OUTINIT field. */
#define GPIOTE_CONFIG_OUTINIT_Low                                                                  \
  (0UL) /*!< Task mode: Initial value of pin before task triggering is low */
#define GPIOTE_CONFIG_OUTINIT_High                                                                 \
  (1UL) /*!< Task mode: Initial value of pin before task triggering is high */

/* Bits 17..16 : When In task mode: Operation to be performed on output when OUT[n] task is triggered. When In event mode: Operation on input that shall trigger IN[n] event. */
#define GPIOTE_CONFIG_POLARITY_Pos (16UL) /*!< Position of POLARITY field. */
#define GPIOTE_CONFIG_POLARITY_Msk                                                                 \
  (0x3UL << GPIOTE_CONFIG_POLARITY_Pos) /*!< Bit mask of POLARITY field. */
#define GPIOTE_CONFIG_POLARITY_None                                                                \
  (0UL) /*!< Task mode: No effect on pin from OUT[n] task. Event mode: no IN[n] event generated on pin activity. */
#define GPIOTE_CONFIG_POLARITY_LoToHi                                                              \
  (1UL) /*!< Task mode: Set pin from OUT[n] task. Event mode: Generate IN[n] event when rising edge on pin. */
#define GPIOTE_CONFIG_POLARITY_HiToLo                                                              \
  (2UL) /*!< Task mode: Clear pin from OUT[n] task. Event mode: Generate IN[n] event when falling edge on pin. */
#define GPIOTE_CONFIG_POLARITY_Toggle                                                              \
  (3UL) /*!< Task mode: Toggle pin from OUT[n]. Event mode: Generate IN[n] when any change on pin. */

/* Bits 12..8 : GPIO number associated with SET[n], CLR[n], and OUT[n] tasks and IN[n] event */
#define GPIOTE_CONFIG_PSEL_Pos (8UL)                              /*!< Position of PSEL field. */
#define GPIOTE_CONFIG_PSEL_Msk (0x1FUL << GPIOTE_CONFIG_PSEL_Pos) /*!< Bit mask of PSEL field. */

/* Bits 1..0 : Mode */
#define GPIOTE_CONFIG_MODE_Pos (0UL)                             /*!< Position of MODE field. */
#define GPIOTE_CONFIG_MODE_Msk (0x3UL << GPIOTE_CONFIG_MODE_Pos) /*!< Bit mask of MODE field. */
#define GPIOTE_CONFIG_MODE_Disabled                                                                \
  (0UL) /*!< Disabled. Pin specified by PSEL will not be acquired by the GPIOTE module. */
#define GPIOTE_CONFIG_MODE_Event     (1UL) /*!< Event mode */
#define GPIOTE_CONFIG_MODE_Task      (3UL) /*!< Task mode */


/* Peripheral: NVMC */
/* Description: Non Volatile Memory Controller */

/* Register: NVMC_READY */
/* Description: Ready flag */

/* Bit 0 : NVMC is ready or busy */
#define NVMC_READY_READY_Pos         (0UL) /*!< Position of READY field. */
#define NVMC_READY_READY_Msk         (0x1UL << NVMC_READY_READY_Pos) /*!< Bit mask of READY field. */
#define NVMC_READY_READY_Busy        (0UL) /*!< NVMC is busy (on-going write or erase operation) */
#define NVMC_READY_READY_Ready       (1UL) /*!< NVMC is ready */

/* Register: NVMC_READYNEXT */
/* Description: Ready flag */

/* Bit 0 : NVMC can accept a new write operation */
#define NVMC_READYNEXT_READYNEXT_Pos (0UL) /*!< Position of READYNEXT field. */
#define NVMC_READYNEXT_READYNEXT_Msk                                                               \
  (0x1UL << NVMC_READYNEXT_READYNEXT_Pos)    /*!< Bit mask of READYNEXT field. */
#define NVMC_READYNEXT_READYNEXT_Busy  (0UL) /*!< NVMC cannot accept any write operation */
#define NVMC_READYNEXT_READYNEXT_Ready (1UL) /*!< NVMC is ready */

/* Register: NVMC_CONFIG */
/* Description: Configuration register */

/* Bits 1..0 : Program memory access mode. It is strongly recommended to only activate erase and write modes when they are actively used. */
#define NVMC_CONFIG_WEN_Pos            (0UL)                          /*!< Position of WEN field. */
#define NVMC_CONFIG_WEN_Msk            (0x3UL << NVMC_CONFIG_WEN_Pos) /*!< Bit mask of WEN field. */
#define NVMC_CONFIG_WEN_Ren            (0UL)                          /*!< Read only access */
#define NVMC_CONFIG_WEN_Wen            (1UL)                          /*!< Write enabled */
#define NVMC_CONFIG_WEN_Een            (2UL)                          /*!< Erase enabled */

/* Register: NVMC_ERASEPAGE */
/* Description: Register for erasing a page in code area */

/* Bits 31..0 : Register for starting erase of a page in code area */
#define NVMC_ERASEPAGE_ERASEPAGE_Pos   (0UL) /*!< Position of ERASEPAGE field. */
#define NVMC_ERASEPAGE_ERASEPAGE_Msk                                                               \
  (0xFFFFFFFFUL << NVMC_ERASEPAGE_ERASEPAGE_Pos) /*!< Bit mask of ERASEPAGE field. */

/* Register: NVMC_ERASEPCR1 */
/* Description: Deprecated register - Register for erasing a page in code area, equivalent to ERASEPAGE */

/* Bits 31..0 : Register for erasing a page in code area, equivalent to ERASEPAGE */
#define NVMC_ERASEPCR1_ERASEPCR1_Pos (0UL) /*!< Position of ERASEPCR1 field. */
#define NVMC_ERASEPCR1_ERASEPCR1_Msk                                                               \
  (0xFFFFFFFFUL << NVMC_ERASEPCR1_ERASEPCR1_Pos) /*!< Bit mask of ERASEPCR1 field. */

/* Register: NVMC_ERASEALL */
/* Description: Register for erasing all non-volatile user memory */

/* Bit 0 : Erase all non-volatile memory including UICR registers. The erase must be enabled using CONFIG.WEN before the non-volatile memory can be erased. */
#define NVMC_ERASEALL_ERASEALL_Pos (0UL) /*!< Position of ERASEALL field. */
#define NVMC_ERASEALL_ERASEALL_Msk                                                                 \
  (0x1UL << NVMC_ERASEALL_ERASEALL_Pos)          /*!< Bit mask of ERASEALL field. */
#define NVMC_ERASEALL_ERASEALL_NoOperation (0UL) /*!< No operation */
#define NVMC_ERASEALL_ERASEALL_Erase       (1UL) /*!< Start chip erase */

/* Register: NVMC_ERASEPCR0 */
/* Description: Deprecated register - Register for erasing a page in code area, equivalent to ERASEPAGE */

/* Bits 31..0 : Register for starting erase of a page in code area, equivalent to ERASEPAGE */
#define NVMC_ERASEPCR0_ERASEPCR0_Pos       (0UL) /*!< Position of ERASEPCR0 field. */
#define NVMC_ERASEPCR0_ERASEPCR0_Msk                                                               \
  (0xFFFFFFFFUL << NVMC_ERASEPCR0_ERASEPCR0_Pos) /*!< Bit mask of ERASEPCR0 field. */

/* Register: NVMC_ERASEUICR */
/* Description: Register for erasing user information configuration registers */

/* Bit 0 : Register starting erase of all user information configuration registers. The erase must be enabled using CONFIG.WEN before the UICR can be erased. */
#define NVMC_ERASEUICR_ERASEUICR_Pos (0UL) /*!< Position of ERASEUICR field. */
#define NVMC_ERASEUICR_ERASEUICR_Msk                                                               \
  (0x1UL << NVMC_ERASEUICR_ERASEUICR_Pos)                /*!< Bit mask of ERASEUICR field. */
#define NVMC_ERASEUICR_ERASEUICR_NoOperation       (0UL) /*!< No operation */
#define NVMC_ERASEUICR_ERASEUICR_Erase             (1UL) /*!< Start erase of UICR */

/* Register: NVMC_ERASEPAGEPARTIAL */
/* Description: Register for partial erase of a page in code area */

/* Bits 31..0 : Register for starting partial erase of a page in code area */
#define NVMC_ERASEPAGEPARTIAL_ERASEPAGEPARTIAL_Pos (0UL) /*!< Position of ERASEPAGEPARTIAL field. */
#define NVMC_ERASEPAGEPARTIAL_ERASEPAGEPARTIAL_Msk                                                 \
  (0xFFFFFFFFUL                                                                                    \
   << NVMC_ERASEPAGEPARTIAL_ERASEPAGEPARTIAL_Pos) /*!< Bit mask of ERASEPAGEPARTIAL field. */

/* Register: NVMC_ERASEPAGEPARTIALCFG */
/* Description: Register for partial erase configuration */

/* Bits 6..0 : Duration of the partial erase in milliseconds */
#define NVMC_ERASEPAGEPARTIALCFG_DURATION_Pos (0UL) /*!< Position of DURATION field. */
#define NVMC_ERASEPAGEPARTIALCFG_DURATION_Msk                                                      \
  (0x7FUL << NVMC_ERASEPAGEPARTIALCFG_DURATION_Pos) /*!< Bit mask of DURATION field. */


/* Peripheral: GPIO */
/* Description: GPIO Port 1 */

/* Register: GPIO_OUT */
/* Description: Write GPIO port */

/* Bit 31 : Pin 31 */
#define GPIO_OUT_PIN31_Pos     (31UL)                        /*!< Position of PIN31 field. */
#define GPIO_OUT_PIN31_Msk     (0x1UL << GPIO_OUT_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_OUT_PIN31_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN31_High    (1UL)                         /*!< Pin driver is high */

/* Bit 30 : Pin 30 */
#define GPIO_OUT_PIN30_Pos     (30UL)                        /*!< Position of PIN30 field. */
#define GPIO_OUT_PIN30_Msk     (0x1UL << GPIO_OUT_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_OUT_PIN30_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN30_High    (1UL)                         /*!< Pin driver is high */

/* Bit 29 : Pin 29 */
#define GPIO_OUT_PIN29_Pos     (29UL)                        /*!< Position of PIN29 field. */
#define GPIO_OUT_PIN29_Msk     (0x1UL << GPIO_OUT_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_OUT_PIN29_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN29_High    (1UL)                         /*!< Pin driver is high */

/* Bit 28 : Pin 28 */
#define GPIO_OUT_PIN28_Pos     (28UL)                        /*!< Position of PIN28 field. */
#define GPIO_OUT_PIN28_Msk     (0x1UL << GPIO_OUT_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_OUT_PIN28_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN28_High    (1UL)                         /*!< Pin driver is high */

/* Bit 27 : Pin 27 */
#define GPIO_OUT_PIN27_Pos     (27UL)                        /*!< Position of PIN27 field. */
#define GPIO_OUT_PIN27_Msk     (0x1UL << GPIO_OUT_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_OUT_PIN27_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN27_High    (1UL)                         /*!< Pin driver is high */

/* Bit 26 : Pin 26 */
#define GPIO_OUT_PIN26_Pos     (26UL)                        /*!< Position of PIN26 field. */
#define GPIO_OUT_PIN26_Msk     (0x1UL << GPIO_OUT_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_OUT_PIN26_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN26_High    (1UL)                         /*!< Pin driver is high */

/* Bit 25 : Pin 25 */
#define GPIO_OUT_PIN25_Pos     (25UL)                        /*!< Position of PIN25 field. */
#define GPIO_OUT_PIN25_Msk     (0x1UL << GPIO_OUT_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_OUT_PIN25_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN25_High    (1UL)                         /*!< Pin driver is high */

/* Bit 24 : Pin 24 */
#define GPIO_OUT_PIN24_Pos     (24UL)                        /*!< Position of PIN24 field. */
#define GPIO_OUT_PIN24_Msk     (0x1UL << GPIO_OUT_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_OUT_PIN24_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN24_High    (1UL)                         /*!< Pin driver is high */

/* Bit 23 : Pin 23 */
#define GPIO_OUT_PIN23_Pos     (23UL)                        /*!< Position of PIN23 field. */
#define GPIO_OUT_PIN23_Msk     (0x1UL << GPIO_OUT_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_OUT_PIN23_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN23_High    (1UL)                         /*!< Pin driver is high */

/* Bit 22 : Pin 22 */
#define GPIO_OUT_PIN22_Pos     (22UL)                        /*!< Position of PIN22 field. */
#define GPIO_OUT_PIN22_Msk     (0x1UL << GPIO_OUT_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_OUT_PIN22_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN22_High    (1UL)                         /*!< Pin driver is high */

/* Bit 21 : Pin 21 */
#define GPIO_OUT_PIN21_Pos     (21UL)                        /*!< Position of PIN21 field. */
#define GPIO_OUT_PIN21_Msk     (0x1UL << GPIO_OUT_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_OUT_PIN21_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN21_High    (1UL)                         /*!< Pin driver is high */

/* Bit 20 : Pin 20 */
#define GPIO_OUT_PIN20_Pos     (20UL)                        /*!< Position of PIN20 field. */
#define GPIO_OUT_PIN20_Msk     (0x1UL << GPIO_OUT_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_OUT_PIN20_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN20_High    (1UL)                         /*!< Pin driver is high */

/* Bit 19 : Pin 19 */
#define GPIO_OUT_PIN19_Pos     (19UL)                        /*!< Position of PIN19 field. */
#define GPIO_OUT_PIN19_Msk     (0x1UL << GPIO_OUT_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_OUT_PIN19_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN19_High    (1UL)                         /*!< Pin driver is high */

/* Bit 18 : Pin 18 */
#define GPIO_OUT_PIN18_Pos     (18UL)                        /*!< Position of PIN18 field. */
#define GPIO_OUT_PIN18_Msk     (0x1UL << GPIO_OUT_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_OUT_PIN18_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN18_High    (1UL)                         /*!< Pin driver is high */

/* Bit 17 : Pin 17 */
#define GPIO_OUT_PIN17_Pos     (17UL)                        /*!< Position of PIN17 field. */
#define GPIO_OUT_PIN17_Msk     (0x1UL << GPIO_OUT_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_OUT_PIN17_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN17_High    (1UL)                         /*!< Pin driver is high */

/* Bit 16 : Pin 16 */
#define GPIO_OUT_PIN16_Pos     (16UL)                        /*!< Position of PIN16 field. */
#define GPIO_OUT_PIN16_Msk     (0x1UL << GPIO_OUT_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_OUT_PIN16_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN16_High    (1UL)                         /*!< Pin driver is high */

/* Bit 15 : Pin 15 */
#define GPIO_OUT_PIN15_Pos     (15UL)                        /*!< Position of PIN15 field. */
#define GPIO_OUT_PIN15_Msk     (0x1UL << GPIO_OUT_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_OUT_PIN15_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN15_High    (1UL)                         /*!< Pin driver is high */

/* Bit 14 : Pin 14 */
#define GPIO_OUT_PIN14_Pos     (14UL)                        /*!< Position of PIN14 field. */
#define GPIO_OUT_PIN14_Msk     (0x1UL << GPIO_OUT_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_OUT_PIN14_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN14_High    (1UL)                         /*!< Pin driver is high */

/* Bit 13 : Pin 13 */
#define GPIO_OUT_PIN13_Pos     (13UL)                        /*!< Position of PIN13 field. */
#define GPIO_OUT_PIN13_Msk     (0x1UL << GPIO_OUT_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_OUT_PIN13_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN13_High    (1UL)                         /*!< Pin driver is high */

/* Bit 12 : Pin 12 */
#define GPIO_OUT_PIN12_Pos     (12UL)                        /*!< Position of PIN12 field. */
#define GPIO_OUT_PIN12_Msk     (0x1UL << GPIO_OUT_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_OUT_PIN12_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN12_High    (1UL)                         /*!< Pin driver is high */

/* Bit 11 : Pin 11 */
#define GPIO_OUT_PIN11_Pos     (11UL)                        /*!< Position of PIN11 field. */
#define GPIO_OUT_PIN11_Msk     (0x1UL << GPIO_OUT_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_OUT_PIN11_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN11_High    (1UL)                         /*!< Pin driver is high */

/* Bit 10 : Pin 10 */
#define GPIO_OUT_PIN10_Pos     (10UL)                        /*!< Position of PIN10 field. */
#define GPIO_OUT_PIN10_Msk     (0x1UL << GPIO_OUT_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_OUT_PIN10_Low     (0UL)                         /*!< Pin driver is low */
#define GPIO_OUT_PIN10_High    (1UL)                         /*!< Pin driver is high */

/* Bit 9 : Pin 9 */
#define GPIO_OUT_PIN9_Pos      (9UL)                        /*!< Position of PIN9 field. */
#define GPIO_OUT_PIN9_Msk      (0x1UL << GPIO_OUT_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_OUT_PIN9_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN9_High     (1UL)                        /*!< Pin driver is high */

/* Bit 8 : Pin 8 */
#define GPIO_OUT_PIN8_Pos      (8UL)                        /*!< Position of PIN8 field. */
#define GPIO_OUT_PIN8_Msk      (0x1UL << GPIO_OUT_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_OUT_PIN8_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN8_High     (1UL)                        /*!< Pin driver is high */

/* Bit 7 : Pin 7 */
#define GPIO_OUT_PIN7_Pos      (7UL)                        /*!< Position of PIN7 field. */
#define GPIO_OUT_PIN7_Msk      (0x1UL << GPIO_OUT_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_OUT_PIN7_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN7_High     (1UL)                        /*!< Pin driver is high */

/* Bit 6 : Pin 6 */
#define GPIO_OUT_PIN6_Pos      (6UL)                        /*!< Position of PIN6 field. */
#define GPIO_OUT_PIN6_Msk      (0x1UL << GPIO_OUT_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_OUT_PIN6_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN6_High     (1UL)                        /*!< Pin driver is high */

/* Bit 5 : Pin 5 */
#define GPIO_OUT_PIN5_Pos      (5UL)                        /*!< Position of PIN5 field. */
#define GPIO_OUT_PIN5_Msk      (0x1UL << GPIO_OUT_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_OUT_PIN5_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN5_High     (1UL)                        /*!< Pin driver is high */

/* Bit 4 : Pin 4 */
#define GPIO_OUT_PIN4_Pos      (4UL)                        /*!< Position of PIN4 field. */
#define GPIO_OUT_PIN4_Msk      (0x1UL << GPIO_OUT_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_OUT_PIN4_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN4_High     (1UL)                        /*!< Pin driver is high */

/* Bit 3 : Pin 3 */
#define GPIO_OUT_PIN3_Pos      (3UL)                        /*!< Position of PIN3 field. */
#define GPIO_OUT_PIN3_Msk      (0x1UL << GPIO_OUT_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_OUT_PIN3_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN3_High     (1UL)                        /*!< Pin driver is high */

/* Bit 2 : Pin 2 */
#define GPIO_OUT_PIN2_Pos      (2UL)                        /*!< Position of PIN2 field. */
#define GPIO_OUT_PIN2_Msk      (0x1UL << GPIO_OUT_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_OUT_PIN2_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN2_High     (1UL)                        /*!< Pin driver is high */

/* Bit 1 : Pin 1 */
#define GPIO_OUT_PIN1_Pos      (1UL)                        /*!< Position of PIN1 field. */
#define GPIO_OUT_PIN1_Msk      (0x1UL << GPIO_OUT_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_OUT_PIN1_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN1_High     (1UL)                        /*!< Pin driver is high */

/* Bit 0 : Pin 0 */
#define GPIO_OUT_PIN0_Pos      (0UL)                        /*!< Position of PIN0 field. */
#define GPIO_OUT_PIN0_Msk      (0x1UL << GPIO_OUT_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_OUT_PIN0_Low      (0UL)                        /*!< Pin driver is low */
#define GPIO_OUT_PIN0_High     (1UL)                        /*!< Pin driver is high */

/* Register: GPIO_OUTSET */
/* Description: Set individual bits in GPIO port */

/* Bit 31 : Pin 31 */
#define GPIO_OUTSET_PIN31_Pos  (31UL)                           /*!< Position of PIN31 field. */
#define GPIO_OUTSET_PIN31_Msk  (0x1UL << GPIO_OUTSET_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_OUTSET_PIN31_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN31_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN31_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 30 : Pin 30 */
#define GPIO_OUTSET_PIN30_Pos  (30UL)                           /*!< Position of PIN30 field. */
#define GPIO_OUTSET_PIN30_Msk  (0x1UL << GPIO_OUTSET_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_OUTSET_PIN30_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN30_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN30_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 29 : Pin 29 */
#define GPIO_OUTSET_PIN29_Pos  (29UL)                           /*!< Position of PIN29 field. */
#define GPIO_OUTSET_PIN29_Msk  (0x1UL << GPIO_OUTSET_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_OUTSET_PIN29_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN29_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN29_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 28 : Pin 28 */
#define GPIO_OUTSET_PIN28_Pos  (28UL)                           /*!< Position of PIN28 field. */
#define GPIO_OUTSET_PIN28_Msk  (0x1UL << GPIO_OUTSET_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_OUTSET_PIN28_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN28_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN28_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 27 : Pin 27 */
#define GPIO_OUTSET_PIN27_Pos  (27UL)                           /*!< Position of PIN27 field. */
#define GPIO_OUTSET_PIN27_Msk  (0x1UL << GPIO_OUTSET_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_OUTSET_PIN27_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN27_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN27_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 26 : Pin 26 */
#define GPIO_OUTSET_PIN26_Pos  (26UL)                           /*!< Position of PIN26 field. */
#define GPIO_OUTSET_PIN26_Msk  (0x1UL << GPIO_OUTSET_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_OUTSET_PIN26_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN26_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN26_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 25 : Pin 25 */
#define GPIO_OUTSET_PIN25_Pos  (25UL)                           /*!< Position of PIN25 field. */
#define GPIO_OUTSET_PIN25_Msk  (0x1UL << GPIO_OUTSET_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_OUTSET_PIN25_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN25_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN25_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 24 : Pin 24 */
#define GPIO_OUTSET_PIN24_Pos  (24UL)                           /*!< Position of PIN24 field. */
#define GPIO_OUTSET_PIN24_Msk  (0x1UL << GPIO_OUTSET_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_OUTSET_PIN24_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN24_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN24_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 23 : Pin 23 */
#define GPIO_OUTSET_PIN23_Pos  (23UL)                           /*!< Position of PIN23 field. */
#define GPIO_OUTSET_PIN23_Msk  (0x1UL << GPIO_OUTSET_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_OUTSET_PIN23_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN23_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN23_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 22 : Pin 22 */
#define GPIO_OUTSET_PIN22_Pos  (22UL)                           /*!< Position of PIN22 field. */
#define GPIO_OUTSET_PIN22_Msk  (0x1UL << GPIO_OUTSET_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_OUTSET_PIN22_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN22_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN22_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 21 : Pin 21 */
#define GPIO_OUTSET_PIN21_Pos  (21UL)                           /*!< Position of PIN21 field. */
#define GPIO_OUTSET_PIN21_Msk  (0x1UL << GPIO_OUTSET_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_OUTSET_PIN21_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN21_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN21_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 20 : Pin 20 */
#define GPIO_OUTSET_PIN20_Pos  (20UL)                           /*!< Position of PIN20 field. */
#define GPIO_OUTSET_PIN20_Msk  (0x1UL << GPIO_OUTSET_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_OUTSET_PIN20_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN20_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN20_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 19 : Pin 19 */
#define GPIO_OUTSET_PIN19_Pos  (19UL)                           /*!< Position of PIN19 field. */
#define GPIO_OUTSET_PIN19_Msk  (0x1UL << GPIO_OUTSET_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_OUTSET_PIN19_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN19_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN19_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 18 : Pin 18 */
#define GPIO_OUTSET_PIN18_Pos  (18UL)                           /*!< Position of PIN18 field. */
#define GPIO_OUTSET_PIN18_Msk  (0x1UL << GPIO_OUTSET_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_OUTSET_PIN18_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN18_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN18_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 17 : Pin 17 */
#define GPIO_OUTSET_PIN17_Pos  (17UL)                           /*!< Position of PIN17 field. */
#define GPIO_OUTSET_PIN17_Msk  (0x1UL << GPIO_OUTSET_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_OUTSET_PIN17_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN17_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN17_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 16 : Pin 16 */
#define GPIO_OUTSET_PIN16_Pos  (16UL)                           /*!< Position of PIN16 field. */
#define GPIO_OUTSET_PIN16_Msk  (0x1UL << GPIO_OUTSET_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_OUTSET_PIN16_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN16_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN16_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 15 : Pin 15 */
#define GPIO_OUTSET_PIN15_Pos  (15UL)                           /*!< Position of PIN15 field. */
#define GPIO_OUTSET_PIN15_Msk  (0x1UL << GPIO_OUTSET_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_OUTSET_PIN15_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN15_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN15_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 14 : Pin 14 */
#define GPIO_OUTSET_PIN14_Pos  (14UL)                           /*!< Position of PIN14 field. */
#define GPIO_OUTSET_PIN14_Msk  (0x1UL << GPIO_OUTSET_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_OUTSET_PIN14_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN14_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN14_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 13 : Pin 13 */
#define GPIO_OUTSET_PIN13_Pos  (13UL)                           /*!< Position of PIN13 field. */
#define GPIO_OUTSET_PIN13_Msk  (0x1UL << GPIO_OUTSET_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_OUTSET_PIN13_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN13_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN13_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 12 : Pin 12 */
#define GPIO_OUTSET_PIN12_Pos  (12UL)                           /*!< Position of PIN12 field. */
#define GPIO_OUTSET_PIN12_Msk  (0x1UL << GPIO_OUTSET_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_OUTSET_PIN12_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN12_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN12_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 11 : Pin 11 */
#define GPIO_OUTSET_PIN11_Pos  (11UL)                           /*!< Position of PIN11 field. */
#define GPIO_OUTSET_PIN11_Msk  (0x1UL << GPIO_OUTSET_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_OUTSET_PIN11_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN11_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN11_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 10 : Pin 10 */
#define GPIO_OUTSET_PIN10_Pos  (10UL)                           /*!< Position of PIN10 field. */
#define GPIO_OUTSET_PIN10_Msk  (0x1UL << GPIO_OUTSET_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_OUTSET_PIN10_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN10_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN10_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 9 : Pin 9 */
#define GPIO_OUTSET_PIN9_Pos  (9UL)                           /*!< Position of PIN9 field. */
#define GPIO_OUTSET_PIN9_Msk  (0x1UL << GPIO_OUTSET_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_OUTSET_PIN9_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN9_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN9_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 8 : Pin 8 */
#define GPIO_OUTSET_PIN8_Pos  (8UL)                           /*!< Position of PIN8 field. */
#define GPIO_OUTSET_PIN8_Msk  (0x1UL << GPIO_OUTSET_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_OUTSET_PIN8_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN8_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN8_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 7 : Pin 7 */
#define GPIO_OUTSET_PIN7_Pos  (7UL)                           /*!< Position of PIN7 field. */
#define GPIO_OUTSET_PIN7_Msk  (0x1UL << GPIO_OUTSET_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_OUTSET_PIN7_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN7_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN7_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 6 : Pin 6 */
#define GPIO_OUTSET_PIN6_Pos  (6UL)                           /*!< Position of PIN6 field. */
#define GPIO_OUTSET_PIN6_Msk  (0x1UL << GPIO_OUTSET_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_OUTSET_PIN6_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN6_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN6_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 5 : Pin 5 */
#define GPIO_OUTSET_PIN5_Pos  (5UL)                           /*!< Position of PIN5 field. */
#define GPIO_OUTSET_PIN5_Msk  (0x1UL << GPIO_OUTSET_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_OUTSET_PIN5_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN5_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN5_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 4 : Pin 4 */
#define GPIO_OUTSET_PIN4_Pos  (4UL)                           /*!< Position of PIN4 field. */
#define GPIO_OUTSET_PIN4_Msk  (0x1UL << GPIO_OUTSET_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_OUTSET_PIN4_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN4_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN4_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 3 : Pin 3 */
#define GPIO_OUTSET_PIN3_Pos  (3UL)                           /*!< Position of PIN3 field. */
#define GPIO_OUTSET_PIN3_Msk  (0x1UL << GPIO_OUTSET_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_OUTSET_PIN3_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN3_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN3_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 2 : Pin 2 */
#define GPIO_OUTSET_PIN2_Pos  (2UL)                           /*!< Position of PIN2 field. */
#define GPIO_OUTSET_PIN2_Msk  (0x1UL << GPIO_OUTSET_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_OUTSET_PIN2_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN2_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN2_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 1 : Pin 1 */
#define GPIO_OUTSET_PIN1_Pos  (1UL)                           /*!< Position of PIN1 field. */
#define GPIO_OUTSET_PIN1_Msk  (0x1UL << GPIO_OUTSET_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_OUTSET_PIN1_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN1_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN1_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 0 : Pin 0 */
#define GPIO_OUTSET_PIN0_Pos  (0UL)                           /*!< Position of PIN0 field. */
#define GPIO_OUTSET_PIN0_Msk  (0x1UL << GPIO_OUTSET_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_OUTSET_PIN0_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN0_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN0_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Register: GPIO_OUTCLR */
/* Description: Clear individual bits in GPIO port */

/* Bit 31 : Pin 31 */
#define GPIO_OUTCLR_PIN31_Pos  (31UL)                           /*!< Position of PIN31 field. */
#define GPIO_OUTCLR_PIN31_Msk  (0x1UL << GPIO_OUTCLR_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_OUTCLR_PIN31_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN31_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN31_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 30 : Pin 30 */
#define GPIO_OUTCLR_PIN30_Pos  (30UL)                           /*!< Position of PIN30 field. */
#define GPIO_OUTCLR_PIN30_Msk  (0x1UL << GPIO_OUTCLR_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_OUTCLR_PIN30_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN30_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN30_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 29 : Pin 29 */
#define GPIO_OUTCLR_PIN29_Pos  (29UL)                           /*!< Position of PIN29 field. */
#define GPIO_OUTCLR_PIN29_Msk  (0x1UL << GPIO_OUTCLR_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_OUTCLR_PIN29_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN29_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN29_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 28 : Pin 28 */
#define GPIO_OUTCLR_PIN28_Pos  (28UL)                           /*!< Position of PIN28 field. */
#define GPIO_OUTCLR_PIN28_Msk  (0x1UL << GPIO_OUTCLR_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_OUTCLR_PIN28_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN28_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN28_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 27 : Pin 27 */
#define GPIO_OUTCLR_PIN27_Pos  (27UL)                           /*!< Position of PIN27 field. */
#define GPIO_OUTCLR_PIN27_Msk  (0x1UL << GPIO_OUTCLR_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_OUTCLR_PIN27_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN27_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN27_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 26 : Pin 26 */
#define GPIO_OUTCLR_PIN26_Pos  (26UL)                           /*!< Position of PIN26 field. */
#define GPIO_OUTCLR_PIN26_Msk  (0x1UL << GPIO_OUTCLR_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_OUTCLR_PIN26_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN26_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN26_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 25 : Pin 25 */
#define GPIO_OUTCLR_PIN25_Pos  (25UL)                           /*!< Position of PIN25 field. */
#define GPIO_OUTCLR_PIN25_Msk  (0x1UL << GPIO_OUTCLR_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_OUTCLR_PIN25_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN25_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN25_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 24 : Pin 24 */
#define GPIO_OUTCLR_PIN24_Pos  (24UL)                           /*!< Position of PIN24 field. */
#define GPIO_OUTCLR_PIN24_Msk  (0x1UL << GPIO_OUTCLR_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_OUTCLR_PIN24_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN24_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN24_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 23 : Pin 23 */
#define GPIO_OUTCLR_PIN23_Pos  (23UL)                           /*!< Position of PIN23 field. */
#define GPIO_OUTCLR_PIN23_Msk  (0x1UL << GPIO_OUTCLR_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_OUTCLR_PIN23_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN23_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN23_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 22 : Pin 22 */
#define GPIO_OUTCLR_PIN22_Pos  (22UL)                           /*!< Position of PIN22 field. */
#define GPIO_OUTCLR_PIN22_Msk  (0x1UL << GPIO_OUTCLR_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_OUTCLR_PIN22_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN22_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN22_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 21 : Pin 21 */
#define GPIO_OUTCLR_PIN21_Pos  (21UL)                           /*!< Position of PIN21 field. */
#define GPIO_OUTCLR_PIN21_Msk  (0x1UL << GPIO_OUTCLR_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_OUTCLR_PIN21_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN21_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN21_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 20 : Pin 20 */
#define GPIO_OUTCLR_PIN20_Pos  (20UL)                           /*!< Position of PIN20 field. */
#define GPIO_OUTCLR_PIN20_Msk  (0x1UL << GPIO_OUTCLR_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_OUTCLR_PIN20_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN20_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN20_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 19 : Pin 19 */
#define GPIO_OUTCLR_PIN19_Pos  (19UL)                           /*!< Position of PIN19 field. */
#define GPIO_OUTCLR_PIN19_Msk  (0x1UL << GPIO_OUTCLR_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_OUTCLR_PIN19_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN19_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN19_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 18 : Pin 18 */
#define GPIO_OUTCLR_PIN18_Pos  (18UL)                           /*!< Position of PIN18 field. */
#define GPIO_OUTCLR_PIN18_Msk  (0x1UL << GPIO_OUTCLR_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_OUTCLR_PIN18_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN18_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN18_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 17 : Pin 17 */
#define GPIO_OUTCLR_PIN17_Pos  (17UL)                           /*!< Position of PIN17 field. */
#define GPIO_OUTCLR_PIN17_Msk  (0x1UL << GPIO_OUTCLR_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_OUTCLR_PIN17_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN17_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN17_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 16 : Pin 16 */
#define GPIO_OUTCLR_PIN16_Pos  (16UL)                           /*!< Position of PIN16 field. */
#define GPIO_OUTCLR_PIN16_Msk  (0x1UL << GPIO_OUTCLR_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_OUTCLR_PIN16_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN16_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN16_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 15 : Pin 15 */
#define GPIO_OUTCLR_PIN15_Pos  (15UL)                           /*!< Position of PIN15 field. */
#define GPIO_OUTCLR_PIN15_Msk  (0x1UL << GPIO_OUTCLR_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_OUTCLR_PIN15_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN15_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN15_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 14 : Pin 14 */
#define GPIO_OUTCLR_PIN14_Pos  (14UL)                           /*!< Position of PIN14 field. */
#define GPIO_OUTCLR_PIN14_Msk  (0x1UL << GPIO_OUTCLR_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_OUTCLR_PIN14_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN14_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN14_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 13 : Pin 13 */
#define GPIO_OUTCLR_PIN13_Pos  (13UL)                           /*!< Position of PIN13 field. */
#define GPIO_OUTCLR_PIN13_Msk  (0x1UL << GPIO_OUTCLR_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_OUTCLR_PIN13_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN13_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN13_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 12 : Pin 12 */
#define GPIO_OUTCLR_PIN12_Pos  (12UL)                           /*!< Position of PIN12 field. */
#define GPIO_OUTCLR_PIN12_Msk  (0x1UL << GPIO_OUTCLR_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_OUTCLR_PIN12_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN12_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN12_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 11 : Pin 11 */
#define GPIO_OUTCLR_PIN11_Pos  (11UL)                           /*!< Position of PIN11 field. */
#define GPIO_OUTCLR_PIN11_Msk  (0x1UL << GPIO_OUTCLR_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_OUTCLR_PIN11_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN11_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN11_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 10 : Pin 10 */
#define GPIO_OUTCLR_PIN10_Pos  (10UL)                           /*!< Position of PIN10 field. */
#define GPIO_OUTCLR_PIN10_Msk  (0x1UL << GPIO_OUTCLR_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_OUTCLR_PIN10_Low  (0UL)                            /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN10_High (1UL)                            /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN10_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 9 : Pin 9 */
#define GPIO_OUTCLR_PIN9_Pos  (9UL)                           /*!< Position of PIN9 field. */
#define GPIO_OUTCLR_PIN9_Msk  (0x1UL << GPIO_OUTCLR_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_OUTCLR_PIN9_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN9_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN9_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 8 : Pin 8 */
#define GPIO_OUTCLR_PIN8_Pos  (8UL)                           /*!< Position of PIN8 field. */
#define GPIO_OUTCLR_PIN8_Msk  (0x1UL << GPIO_OUTCLR_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_OUTCLR_PIN8_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN8_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN8_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 7 : Pin 7 */
#define GPIO_OUTCLR_PIN7_Pos  (7UL)                           /*!< Position of PIN7 field. */
#define GPIO_OUTCLR_PIN7_Msk  (0x1UL << GPIO_OUTCLR_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_OUTCLR_PIN7_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN7_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN7_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 6 : Pin 6 */
#define GPIO_OUTCLR_PIN6_Pos  (6UL)                           /*!< Position of PIN6 field. */
#define GPIO_OUTCLR_PIN6_Msk  (0x1UL << GPIO_OUTCLR_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_OUTCLR_PIN6_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN6_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN6_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 5 : Pin 5 */
#define GPIO_OUTCLR_PIN5_Pos  (5UL)                           /*!< Position of PIN5 field. */
#define GPIO_OUTCLR_PIN5_Msk  (0x1UL << GPIO_OUTCLR_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_OUTCLR_PIN5_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN5_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN5_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 4 : Pin 4 */
#define GPIO_OUTCLR_PIN4_Pos  (4UL)                           /*!< Position of PIN4 field. */
#define GPIO_OUTCLR_PIN4_Msk  (0x1UL << GPIO_OUTCLR_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_OUTCLR_PIN4_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN4_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN4_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 3 : Pin 3 */
#define GPIO_OUTCLR_PIN3_Pos  (3UL)                           /*!< Position of PIN3 field. */
#define GPIO_OUTCLR_PIN3_Msk  (0x1UL << GPIO_OUTCLR_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_OUTCLR_PIN3_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN3_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN3_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 2 : Pin 2 */
#define GPIO_OUTCLR_PIN2_Pos  (2UL)                           /*!< Position of PIN2 field. */
#define GPIO_OUTCLR_PIN2_Msk  (0x1UL << GPIO_OUTCLR_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_OUTCLR_PIN2_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN2_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN2_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 1 : Pin 1 */
#define GPIO_OUTCLR_PIN1_Pos  (1UL)                           /*!< Position of PIN1 field. */
#define GPIO_OUTCLR_PIN1_Msk  (0x1UL << GPIO_OUTCLR_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_OUTCLR_PIN1_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN1_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN1_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 0 : Pin 0 */
#define GPIO_OUTCLR_PIN0_Pos  (0UL)                           /*!< Position of PIN0 field. */
#define GPIO_OUTCLR_PIN0_Msk  (0x1UL << GPIO_OUTCLR_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_OUTCLR_PIN0_Low  (0UL)                           /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN0_High (1UL)                           /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN0_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Register: GPIO_IN */
/* Description: Read GPIO port */

/* Bit 31 : Pin 31 */
#define GPIO_IN_PIN31_Pos        (31UL)                       /*!< Position of PIN31 field. */
#define GPIO_IN_PIN31_Msk        (0x1UL << GPIO_IN_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_IN_PIN31_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN31_High       (1UL)                        /*!< Pin input is high */

/* Bit 30 : Pin 30 */
#define GPIO_IN_PIN30_Pos        (30UL)                       /*!< Position of PIN30 field. */
#define GPIO_IN_PIN30_Msk        (0x1UL << GPIO_IN_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_IN_PIN30_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN30_High       (1UL)                        /*!< Pin input is high */

/* Bit 29 : Pin 29 */
#define GPIO_IN_PIN29_Pos        (29UL)                       /*!< Position of PIN29 field. */
#define GPIO_IN_PIN29_Msk        (0x1UL << GPIO_IN_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_IN_PIN29_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN29_High       (1UL)                        /*!< Pin input is high */

/* Bit 28 : Pin 28 */
#define GPIO_IN_PIN28_Pos        (28UL)                       /*!< Position of PIN28 field. */
#define GPIO_IN_PIN28_Msk        (0x1UL << GPIO_IN_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_IN_PIN28_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN28_High       (1UL)                        /*!< Pin input is high */

/* Bit 27 : Pin 27 */
#define GPIO_IN_PIN27_Pos        (27UL)                       /*!< Position of PIN27 field. */
#define GPIO_IN_PIN27_Msk        (0x1UL << GPIO_IN_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_IN_PIN27_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN27_High       (1UL)                        /*!< Pin input is high */

/* Bit 26 : Pin 26 */
#define GPIO_IN_PIN26_Pos        (26UL)                       /*!< Position of PIN26 field. */
#define GPIO_IN_PIN26_Msk        (0x1UL << GPIO_IN_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_IN_PIN26_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN26_High       (1UL)                        /*!< Pin input is high */

/* Bit 25 : Pin 25 */
#define GPIO_IN_PIN25_Pos        (25UL)                       /*!< Position of PIN25 field. */
#define GPIO_IN_PIN25_Msk        (0x1UL << GPIO_IN_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_IN_PIN25_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN25_High       (1UL)                        /*!< Pin input is high */

/* Bit 24 : Pin 24 */
#define GPIO_IN_PIN24_Pos        (24UL)                       /*!< Position of PIN24 field. */
#define GPIO_IN_PIN24_Msk        (0x1UL << GPIO_IN_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_IN_PIN24_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN24_High       (1UL)                        /*!< Pin input is high */

/* Bit 23 : Pin 23 */
#define GPIO_IN_PIN23_Pos        (23UL)                       /*!< Position of PIN23 field. */
#define GPIO_IN_PIN23_Msk        (0x1UL << GPIO_IN_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_IN_PIN23_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN23_High       (1UL)                        /*!< Pin input is high */

/* Bit 22 : Pin 22 */
#define GPIO_IN_PIN22_Pos        (22UL)                       /*!< Position of PIN22 field. */
#define GPIO_IN_PIN22_Msk        (0x1UL << GPIO_IN_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_IN_PIN22_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN22_High       (1UL)                        /*!< Pin input is high */

/* Bit 21 : Pin 21 */
#define GPIO_IN_PIN21_Pos        (21UL)                       /*!< Position of PIN21 field. */
#define GPIO_IN_PIN21_Msk        (0x1UL << GPIO_IN_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_IN_PIN21_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN21_High       (1UL)                        /*!< Pin input is high */

/* Bit 20 : Pin 20 */
#define GPIO_IN_PIN20_Pos        (20UL)                       /*!< Position of PIN20 field. */
#define GPIO_IN_PIN20_Msk        (0x1UL << GPIO_IN_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_IN_PIN20_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN20_High       (1UL)                        /*!< Pin input is high */

/* Bit 19 : Pin 19 */
#define GPIO_IN_PIN19_Pos        (19UL)                       /*!< Position of PIN19 field. */
#define GPIO_IN_PIN19_Msk        (0x1UL << GPIO_IN_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_IN_PIN19_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN19_High       (1UL)                        /*!< Pin input is high */

/* Bit 18 : Pin 18 */
#define GPIO_IN_PIN18_Pos        (18UL)                       /*!< Position of PIN18 field. */
#define GPIO_IN_PIN18_Msk        (0x1UL << GPIO_IN_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_IN_PIN18_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN18_High       (1UL)                        /*!< Pin input is high */

/* Bit 17 : Pin 17 */
#define GPIO_IN_PIN17_Pos        (17UL)                       /*!< Position of PIN17 field. */
#define GPIO_IN_PIN17_Msk        (0x1UL << GPIO_IN_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_IN_PIN17_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN17_High       (1UL)                        /*!< Pin input is high */

/* Bit 16 : Pin 16 */
#define GPIO_IN_PIN16_Pos        (16UL)                       /*!< Position of PIN16 field. */
#define GPIO_IN_PIN16_Msk        (0x1UL << GPIO_IN_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_IN_PIN16_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN16_High       (1UL)                        /*!< Pin input is high */

/* Bit 15 : Pin 15 */
#define GPIO_IN_PIN15_Pos        (15UL)                       /*!< Position of PIN15 field. */
#define GPIO_IN_PIN15_Msk        (0x1UL << GPIO_IN_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_IN_PIN15_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN15_High       (1UL)                        /*!< Pin input is high */

/* Bit 14 : Pin 14 */
#define GPIO_IN_PIN14_Pos        (14UL)                       /*!< Position of PIN14 field. */
#define GPIO_IN_PIN14_Msk        (0x1UL << GPIO_IN_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_IN_PIN14_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN14_High       (1UL)                        /*!< Pin input is high */

/* Bit 13 : Pin 13 */
#define GPIO_IN_PIN13_Pos        (13UL)                       /*!< Position of PIN13 field. */
#define GPIO_IN_PIN13_Msk        (0x1UL << GPIO_IN_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_IN_PIN13_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN13_High       (1UL)                        /*!< Pin input is high */

/* Bit 12 : Pin 12 */
#define GPIO_IN_PIN12_Pos        (12UL)                       /*!< Position of PIN12 field. */
#define GPIO_IN_PIN12_Msk        (0x1UL << GPIO_IN_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_IN_PIN12_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN12_High       (1UL)                        /*!< Pin input is high */

/* Bit 11 : Pin 11 */
#define GPIO_IN_PIN11_Pos        (11UL)                       /*!< Position of PIN11 field. */
#define GPIO_IN_PIN11_Msk        (0x1UL << GPIO_IN_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_IN_PIN11_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN11_High       (1UL)                        /*!< Pin input is high */

/* Bit 10 : Pin 10 */
#define GPIO_IN_PIN10_Pos        (10UL)                       /*!< Position of PIN10 field. */
#define GPIO_IN_PIN10_Msk        (0x1UL << GPIO_IN_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_IN_PIN10_Low        (0UL)                        /*!< Pin input is low */
#define GPIO_IN_PIN10_High       (1UL)                        /*!< Pin input is high */

/* Bit 9 : Pin 9 */
#define GPIO_IN_PIN9_Pos         (9UL)                       /*!< Position of PIN9 field. */
#define GPIO_IN_PIN9_Msk         (0x1UL << GPIO_IN_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_IN_PIN9_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN9_High        (1UL)                       /*!< Pin input is high */

/* Bit 8 : Pin 8 */
#define GPIO_IN_PIN8_Pos         (8UL)                       /*!< Position of PIN8 field. */
#define GPIO_IN_PIN8_Msk         (0x1UL << GPIO_IN_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_IN_PIN8_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN8_High        (1UL)                       /*!< Pin input is high */

/* Bit 7 : Pin 7 */
#define GPIO_IN_PIN7_Pos         (7UL)                       /*!< Position of PIN7 field. */
#define GPIO_IN_PIN7_Msk         (0x1UL << GPIO_IN_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_IN_PIN7_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN7_High        (1UL)                       /*!< Pin input is high */

/* Bit 6 : Pin 6 */
#define GPIO_IN_PIN6_Pos         (6UL)                       /*!< Position of PIN6 field. */
#define GPIO_IN_PIN6_Msk         (0x1UL << GPIO_IN_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_IN_PIN6_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN6_High        (1UL)                       /*!< Pin input is high */

/* Bit 5 : Pin 5 */
#define GPIO_IN_PIN5_Pos         (5UL)                       /*!< Position of PIN5 field. */
#define GPIO_IN_PIN5_Msk         (0x1UL << GPIO_IN_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_IN_PIN5_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN5_High        (1UL)                       /*!< Pin input is high */

/* Bit 4 : Pin 4 */
#define GPIO_IN_PIN4_Pos         (4UL)                       /*!< Position of PIN4 field. */
#define GPIO_IN_PIN4_Msk         (0x1UL << GPIO_IN_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_IN_PIN4_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN4_High        (1UL)                       /*!< Pin input is high */

/* Bit 3 : Pin 3 */
#define GPIO_IN_PIN3_Pos         (3UL)                       /*!< Position of PIN3 field. */
#define GPIO_IN_PIN3_Msk         (0x1UL << GPIO_IN_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_IN_PIN3_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN3_High        (1UL)                       /*!< Pin input is high */

/* Bit 2 : Pin 2 */
#define GPIO_IN_PIN2_Pos         (2UL)                       /*!< Position of PIN2 field. */
#define GPIO_IN_PIN2_Msk         (0x1UL << GPIO_IN_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_IN_PIN2_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN2_High        (1UL)                       /*!< Pin input is high */

/* Bit 1 : Pin 1 */
#define GPIO_IN_PIN1_Pos         (1UL)                       /*!< Position of PIN1 field. */
#define GPIO_IN_PIN1_Msk         (0x1UL << GPIO_IN_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_IN_PIN1_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN1_High        (1UL)                       /*!< Pin input is high */

/* Bit 0 : Pin 0 */
#define GPIO_IN_PIN0_Pos         (0UL)                       /*!< Position of PIN0 field. */
#define GPIO_IN_PIN0_Msk         (0x1UL << GPIO_IN_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_IN_PIN0_Low         (0UL)                       /*!< Pin input is low */
#define GPIO_IN_PIN0_High        (1UL)                       /*!< Pin input is high */

/* Register: GPIO_DIR */
/* Description: Direction of GPIO pins */

/* Bit 31 : Pin 31 */
#define GPIO_DIR_PIN31_Pos       (31UL)                        /*!< Position of PIN31 field. */
#define GPIO_DIR_PIN31_Msk       (0x1UL << GPIO_DIR_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_DIR_PIN31_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN31_Output    (1UL)                         /*!< Pin set as output */

/* Bit 30 : Pin 30 */
#define GPIO_DIR_PIN30_Pos       (30UL)                        /*!< Position of PIN30 field. */
#define GPIO_DIR_PIN30_Msk       (0x1UL << GPIO_DIR_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_DIR_PIN30_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN30_Output    (1UL)                         /*!< Pin set as output */

/* Bit 29 : Pin 29 */
#define GPIO_DIR_PIN29_Pos       (29UL)                        /*!< Position of PIN29 field. */
#define GPIO_DIR_PIN29_Msk       (0x1UL << GPIO_DIR_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_DIR_PIN29_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN29_Output    (1UL)                         /*!< Pin set as output */

/* Bit 28 : Pin 28 */
#define GPIO_DIR_PIN28_Pos       (28UL)                        /*!< Position of PIN28 field. */
#define GPIO_DIR_PIN28_Msk       (0x1UL << GPIO_DIR_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_DIR_PIN28_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN28_Output    (1UL)                         /*!< Pin set as output */

/* Bit 27 : Pin 27 */
#define GPIO_DIR_PIN27_Pos       (27UL)                        /*!< Position of PIN27 field. */
#define GPIO_DIR_PIN27_Msk       (0x1UL << GPIO_DIR_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_DIR_PIN27_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN27_Output    (1UL)                         /*!< Pin set as output */

/* Bit 26 : Pin 26 */
#define GPIO_DIR_PIN26_Pos       (26UL)                        /*!< Position of PIN26 field. */
#define GPIO_DIR_PIN26_Msk       (0x1UL << GPIO_DIR_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_DIR_PIN26_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN26_Output    (1UL)                         /*!< Pin set as output */

/* Bit 25 : Pin 25 */
#define GPIO_DIR_PIN25_Pos       (25UL)                        /*!< Position of PIN25 field. */
#define GPIO_DIR_PIN25_Msk       (0x1UL << GPIO_DIR_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_DIR_PIN25_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN25_Output    (1UL)                         /*!< Pin set as output */

/* Bit 24 : Pin 24 */
#define GPIO_DIR_PIN24_Pos       (24UL)                        /*!< Position of PIN24 field. */
#define GPIO_DIR_PIN24_Msk       (0x1UL << GPIO_DIR_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_DIR_PIN24_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN24_Output    (1UL)                         /*!< Pin set as output */

/* Bit 23 : Pin 23 */
#define GPIO_DIR_PIN23_Pos       (23UL)                        /*!< Position of PIN23 field. */
#define GPIO_DIR_PIN23_Msk       (0x1UL << GPIO_DIR_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_DIR_PIN23_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN23_Output    (1UL)                         /*!< Pin set as output */

/* Bit 22 : Pin 22 */
#define GPIO_DIR_PIN22_Pos       (22UL)                        /*!< Position of PIN22 field. */
#define GPIO_DIR_PIN22_Msk       (0x1UL << GPIO_DIR_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_DIR_PIN22_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN22_Output    (1UL)                         /*!< Pin set as output */

/* Bit 21 : Pin 21 */
#define GPIO_DIR_PIN21_Pos       (21UL)                        /*!< Position of PIN21 field. */
#define GPIO_DIR_PIN21_Msk       (0x1UL << GPIO_DIR_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_DIR_PIN21_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN21_Output    (1UL)                         /*!< Pin set as output */

/* Bit 20 : Pin 20 */
#define GPIO_DIR_PIN20_Pos       (20UL)                        /*!< Position of PIN20 field. */
#define GPIO_DIR_PIN20_Msk       (0x1UL << GPIO_DIR_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_DIR_PIN20_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN20_Output    (1UL)                         /*!< Pin set as output */

/* Bit 19 : Pin 19 */
#define GPIO_DIR_PIN19_Pos       (19UL)                        /*!< Position of PIN19 field. */
#define GPIO_DIR_PIN19_Msk       (0x1UL << GPIO_DIR_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_DIR_PIN19_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN19_Output    (1UL)                         /*!< Pin set as output */

/* Bit 18 : Pin 18 */
#define GPIO_DIR_PIN18_Pos       (18UL)                        /*!< Position of PIN18 field. */
#define GPIO_DIR_PIN18_Msk       (0x1UL << GPIO_DIR_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_DIR_PIN18_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN18_Output    (1UL)                         /*!< Pin set as output */

/* Bit 17 : Pin 17 */
#define GPIO_DIR_PIN17_Pos       (17UL)                        /*!< Position of PIN17 field. */
#define GPIO_DIR_PIN17_Msk       (0x1UL << GPIO_DIR_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_DIR_PIN17_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN17_Output    (1UL)                         /*!< Pin set as output */

/* Bit 16 : Pin 16 */
#define GPIO_DIR_PIN16_Pos       (16UL)                        /*!< Position of PIN16 field. */
#define GPIO_DIR_PIN16_Msk       (0x1UL << GPIO_DIR_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_DIR_PIN16_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN16_Output    (1UL)                         /*!< Pin set as output */

/* Bit 15 : Pin 15 */
#define GPIO_DIR_PIN15_Pos       (15UL)                        /*!< Position of PIN15 field. */
#define GPIO_DIR_PIN15_Msk       (0x1UL << GPIO_DIR_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_DIR_PIN15_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN15_Output    (1UL)                         /*!< Pin set as output */

/* Bit 14 : Pin 14 */
#define GPIO_DIR_PIN14_Pos       (14UL)                        /*!< Position of PIN14 field. */
#define GPIO_DIR_PIN14_Msk       (0x1UL << GPIO_DIR_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_DIR_PIN14_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN14_Output    (1UL)                         /*!< Pin set as output */

/* Bit 13 : Pin 13 */
#define GPIO_DIR_PIN13_Pos       (13UL)                        /*!< Position of PIN13 field. */
#define GPIO_DIR_PIN13_Msk       (0x1UL << GPIO_DIR_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_DIR_PIN13_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN13_Output    (1UL)                         /*!< Pin set as output */

/* Bit 12 : Pin 12 */
#define GPIO_DIR_PIN12_Pos       (12UL)                        /*!< Position of PIN12 field. */
#define GPIO_DIR_PIN12_Msk       (0x1UL << GPIO_DIR_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_DIR_PIN12_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN12_Output    (1UL)                         /*!< Pin set as output */

/* Bit 11 : Pin 11 */
#define GPIO_DIR_PIN11_Pos       (11UL)                        /*!< Position of PIN11 field. */
#define GPIO_DIR_PIN11_Msk       (0x1UL << GPIO_DIR_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_DIR_PIN11_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN11_Output    (1UL)                         /*!< Pin set as output */

/* Bit 10 : Pin 10 */
#define GPIO_DIR_PIN10_Pos       (10UL)                        /*!< Position of PIN10 field. */
#define GPIO_DIR_PIN10_Msk       (0x1UL << GPIO_DIR_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_DIR_PIN10_Input     (0UL)                         /*!< Pin set as input */
#define GPIO_DIR_PIN10_Output    (1UL)                         /*!< Pin set as output */

/* Bit 9 : Pin 9 */
#define GPIO_DIR_PIN9_Pos        (9UL)                        /*!< Position of PIN9 field. */
#define GPIO_DIR_PIN9_Msk        (0x1UL << GPIO_DIR_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_DIR_PIN9_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN9_Output     (1UL)                        /*!< Pin set as output */

/* Bit 8 : Pin 8 */
#define GPIO_DIR_PIN8_Pos        (8UL)                        /*!< Position of PIN8 field. */
#define GPIO_DIR_PIN8_Msk        (0x1UL << GPIO_DIR_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_DIR_PIN8_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN8_Output     (1UL)                        /*!< Pin set as output */

/* Bit 7 : Pin 7 */
#define GPIO_DIR_PIN7_Pos        (7UL)                        /*!< Position of PIN7 field. */
#define GPIO_DIR_PIN7_Msk        (0x1UL << GPIO_DIR_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_DIR_PIN7_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN7_Output     (1UL)                        /*!< Pin set as output */

/* Bit 6 : Pin 6 */
#define GPIO_DIR_PIN6_Pos        (6UL)                        /*!< Position of PIN6 field. */
#define GPIO_DIR_PIN6_Msk        (0x1UL << GPIO_DIR_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_DIR_PIN6_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN6_Output     (1UL)                        /*!< Pin set as output */

/* Bit 5 : Pin 5 */
#define GPIO_DIR_PIN5_Pos        (5UL)                        /*!< Position of PIN5 field. */
#define GPIO_DIR_PIN5_Msk        (0x1UL << GPIO_DIR_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_DIR_PIN5_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN5_Output     (1UL)                        /*!< Pin set as output */

/* Bit 4 : Pin 4 */
#define GPIO_DIR_PIN4_Pos        (4UL)                        /*!< Position of PIN4 field. */
#define GPIO_DIR_PIN4_Msk        (0x1UL << GPIO_DIR_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_DIR_PIN4_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN4_Output     (1UL)                        /*!< Pin set as output */

/* Bit 3 : Pin 3 */
#define GPIO_DIR_PIN3_Pos        (3UL)                        /*!< Position of PIN3 field. */
#define GPIO_DIR_PIN3_Msk        (0x1UL << GPIO_DIR_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_DIR_PIN3_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN3_Output     (1UL)                        /*!< Pin set as output */

/* Bit 2 : Pin 2 */
#define GPIO_DIR_PIN2_Pos        (2UL)                        /*!< Position of PIN2 field. */
#define GPIO_DIR_PIN2_Msk        (0x1UL << GPIO_DIR_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_DIR_PIN2_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN2_Output     (1UL)                        /*!< Pin set as output */

/* Bit 1 : Pin 1 */
#define GPIO_DIR_PIN1_Pos        (1UL)                        /*!< Position of PIN1 field. */
#define GPIO_DIR_PIN1_Msk        (0x1UL << GPIO_DIR_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_DIR_PIN1_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN1_Output     (1UL)                        /*!< Pin set as output */

/* Bit 0 : Pin 0 */
#define GPIO_DIR_PIN0_Pos        (0UL)                        /*!< Position of PIN0 field. */
#define GPIO_DIR_PIN0_Msk        (0x1UL << GPIO_DIR_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_DIR_PIN0_Input      (0UL)                        /*!< Pin set as input */
#define GPIO_DIR_PIN0_Output     (1UL)                        /*!< Pin set as output */

/* Register: GPIO_DIRSET */
/* Description: DIR set register */

/* Bit 31 : Set as output pin 31 */
#define GPIO_DIRSET_PIN31_Pos    (31UL)                           /*!< Position of PIN31 field. */
#define GPIO_DIRSET_PIN31_Msk    (0x1UL << GPIO_DIRSET_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_DIRSET_PIN31_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN31_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN31_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 30 : Set as output pin 30 */
#define GPIO_DIRSET_PIN30_Pos    (30UL)                           /*!< Position of PIN30 field. */
#define GPIO_DIRSET_PIN30_Msk    (0x1UL << GPIO_DIRSET_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_DIRSET_PIN30_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN30_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN30_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 29 : Set as output pin 29 */
#define GPIO_DIRSET_PIN29_Pos    (29UL)                           /*!< Position of PIN29 field. */
#define GPIO_DIRSET_PIN29_Msk    (0x1UL << GPIO_DIRSET_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_DIRSET_PIN29_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN29_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN29_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 28 : Set as output pin 28 */
#define GPIO_DIRSET_PIN28_Pos    (28UL)                           /*!< Position of PIN28 field. */
#define GPIO_DIRSET_PIN28_Msk    (0x1UL << GPIO_DIRSET_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_DIRSET_PIN28_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN28_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN28_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 27 : Set as output pin 27 */
#define GPIO_DIRSET_PIN27_Pos    (27UL)                           /*!< Position of PIN27 field. */
#define GPIO_DIRSET_PIN27_Msk    (0x1UL << GPIO_DIRSET_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_DIRSET_PIN27_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN27_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN27_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 26 : Set as output pin 26 */
#define GPIO_DIRSET_PIN26_Pos    (26UL)                           /*!< Position of PIN26 field. */
#define GPIO_DIRSET_PIN26_Msk    (0x1UL << GPIO_DIRSET_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_DIRSET_PIN26_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN26_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN26_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 25 : Set as output pin 25 */
#define GPIO_DIRSET_PIN25_Pos    (25UL)                           /*!< Position of PIN25 field. */
#define GPIO_DIRSET_PIN25_Msk    (0x1UL << GPIO_DIRSET_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_DIRSET_PIN25_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN25_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN25_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 24 : Set as output pin 24 */
#define GPIO_DIRSET_PIN24_Pos    (24UL)                           /*!< Position of PIN24 field. */
#define GPIO_DIRSET_PIN24_Msk    (0x1UL << GPIO_DIRSET_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_DIRSET_PIN24_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN24_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN24_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 23 : Set as output pin 23 */
#define GPIO_DIRSET_PIN23_Pos    (23UL)                           /*!< Position of PIN23 field. */
#define GPIO_DIRSET_PIN23_Msk    (0x1UL << GPIO_DIRSET_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_DIRSET_PIN23_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN23_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN23_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 22 : Set as output pin 22 */
#define GPIO_DIRSET_PIN22_Pos    (22UL)                           /*!< Position of PIN22 field. */
#define GPIO_DIRSET_PIN22_Msk    (0x1UL << GPIO_DIRSET_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_DIRSET_PIN22_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN22_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN22_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 21 : Set as output pin 21 */
#define GPIO_DIRSET_PIN21_Pos    (21UL)                           /*!< Position of PIN21 field. */
#define GPIO_DIRSET_PIN21_Msk    (0x1UL << GPIO_DIRSET_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_DIRSET_PIN21_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN21_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN21_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 20 : Set as output pin 20 */
#define GPIO_DIRSET_PIN20_Pos    (20UL)                           /*!< Position of PIN20 field. */
#define GPIO_DIRSET_PIN20_Msk    (0x1UL << GPIO_DIRSET_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_DIRSET_PIN20_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN20_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN20_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 19 : Set as output pin 19 */
#define GPIO_DIRSET_PIN19_Pos    (19UL)                           /*!< Position of PIN19 field. */
#define GPIO_DIRSET_PIN19_Msk    (0x1UL << GPIO_DIRSET_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_DIRSET_PIN19_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN19_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN19_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 18 : Set as output pin 18 */
#define GPIO_DIRSET_PIN18_Pos    (18UL)                           /*!< Position of PIN18 field. */
#define GPIO_DIRSET_PIN18_Msk    (0x1UL << GPIO_DIRSET_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_DIRSET_PIN18_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN18_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN18_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 17 : Set as output pin 17 */
#define GPIO_DIRSET_PIN17_Pos    (17UL)                           /*!< Position of PIN17 field. */
#define GPIO_DIRSET_PIN17_Msk    (0x1UL << GPIO_DIRSET_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_DIRSET_PIN17_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN17_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN17_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 16 : Set as output pin 16 */
#define GPIO_DIRSET_PIN16_Pos    (16UL)                           /*!< Position of PIN16 field. */
#define GPIO_DIRSET_PIN16_Msk    (0x1UL << GPIO_DIRSET_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_DIRSET_PIN16_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN16_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN16_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 15 : Set as output pin 15 */
#define GPIO_DIRSET_PIN15_Pos    (15UL)                           /*!< Position of PIN15 field. */
#define GPIO_DIRSET_PIN15_Msk    (0x1UL << GPIO_DIRSET_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_DIRSET_PIN15_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN15_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN15_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 14 : Set as output pin 14 */
#define GPIO_DIRSET_PIN14_Pos    (14UL)                           /*!< Position of PIN14 field. */
#define GPIO_DIRSET_PIN14_Msk    (0x1UL << GPIO_DIRSET_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_DIRSET_PIN14_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN14_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN14_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 13 : Set as output pin 13 */
#define GPIO_DIRSET_PIN13_Pos    (13UL)                           /*!< Position of PIN13 field. */
#define GPIO_DIRSET_PIN13_Msk    (0x1UL << GPIO_DIRSET_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_DIRSET_PIN13_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN13_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN13_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 12 : Set as output pin 12 */
#define GPIO_DIRSET_PIN12_Pos    (12UL)                           /*!< Position of PIN12 field. */
#define GPIO_DIRSET_PIN12_Msk    (0x1UL << GPIO_DIRSET_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_DIRSET_PIN12_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN12_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN12_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 11 : Set as output pin 11 */
#define GPIO_DIRSET_PIN11_Pos    (11UL)                           /*!< Position of PIN11 field. */
#define GPIO_DIRSET_PIN11_Msk    (0x1UL << GPIO_DIRSET_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_DIRSET_PIN11_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN11_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN11_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 10 : Set as output pin 10 */
#define GPIO_DIRSET_PIN10_Pos    (10UL)                           /*!< Position of PIN10 field. */
#define GPIO_DIRSET_PIN10_Msk    (0x1UL << GPIO_DIRSET_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_DIRSET_PIN10_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN10_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN10_Set                                                                      \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 9 : Set as output pin 9 */
#define GPIO_DIRSET_PIN9_Pos    (9UL)                           /*!< Position of PIN9 field. */
#define GPIO_DIRSET_PIN9_Msk    (0x1UL << GPIO_DIRSET_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_DIRSET_PIN9_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN9_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN9_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 8 : Set as output pin 8 */
#define GPIO_DIRSET_PIN8_Pos    (8UL)                           /*!< Position of PIN8 field. */
#define GPIO_DIRSET_PIN8_Msk    (0x1UL << GPIO_DIRSET_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_DIRSET_PIN8_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN8_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN8_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 7 : Set as output pin 7 */
#define GPIO_DIRSET_PIN7_Pos    (7UL)                           /*!< Position of PIN7 field. */
#define GPIO_DIRSET_PIN7_Msk    (0x1UL << GPIO_DIRSET_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_DIRSET_PIN7_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN7_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN7_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 6 : Set as output pin 6 */
#define GPIO_DIRSET_PIN6_Pos    (6UL)                           /*!< Position of PIN6 field. */
#define GPIO_DIRSET_PIN6_Msk    (0x1UL << GPIO_DIRSET_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_DIRSET_PIN6_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN6_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN6_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 5 : Set as output pin 5 */
#define GPIO_DIRSET_PIN5_Pos    (5UL)                           /*!< Position of PIN5 field. */
#define GPIO_DIRSET_PIN5_Msk    (0x1UL << GPIO_DIRSET_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_DIRSET_PIN5_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN5_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN5_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 4 : Set as output pin 4 */
#define GPIO_DIRSET_PIN4_Pos    (4UL)                           /*!< Position of PIN4 field. */
#define GPIO_DIRSET_PIN4_Msk    (0x1UL << GPIO_DIRSET_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_DIRSET_PIN4_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN4_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN4_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 3 : Set as output pin 3 */
#define GPIO_DIRSET_PIN3_Pos    (3UL)                           /*!< Position of PIN3 field. */
#define GPIO_DIRSET_PIN3_Msk    (0x1UL << GPIO_DIRSET_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_DIRSET_PIN3_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN3_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN3_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 2 : Set as output pin 2 */
#define GPIO_DIRSET_PIN2_Pos    (2UL)                           /*!< Position of PIN2 field. */
#define GPIO_DIRSET_PIN2_Msk    (0x1UL << GPIO_DIRSET_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_DIRSET_PIN2_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN2_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN2_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 1 : Set as output pin 1 */
#define GPIO_DIRSET_PIN1_Pos    (1UL)                           /*!< Position of PIN1 field. */
#define GPIO_DIRSET_PIN1_Msk    (0x1UL << GPIO_DIRSET_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_DIRSET_PIN1_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN1_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN1_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 0 : Set as output pin 0 */
#define GPIO_DIRSET_PIN0_Pos    (0UL)                           /*!< Position of PIN0 field. */
#define GPIO_DIRSET_PIN0_Msk    (0x1UL << GPIO_DIRSET_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_DIRSET_PIN0_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN0_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN0_Set                                                                       \
  (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Register: GPIO_DIRCLR */
/* Description: DIR clear register */

/* Bit 31 : Set as input pin 31 */
#define GPIO_DIRCLR_PIN31_Pos    (31UL)                           /*!< Position of PIN31 field. */
#define GPIO_DIRCLR_PIN31_Msk    (0x1UL << GPIO_DIRCLR_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_DIRCLR_PIN31_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN31_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN31_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 30 : Set as input pin 30 */
#define GPIO_DIRCLR_PIN30_Pos    (30UL)                           /*!< Position of PIN30 field. */
#define GPIO_DIRCLR_PIN30_Msk    (0x1UL << GPIO_DIRCLR_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_DIRCLR_PIN30_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN30_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN30_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 29 : Set as input pin 29 */
#define GPIO_DIRCLR_PIN29_Pos    (29UL)                           /*!< Position of PIN29 field. */
#define GPIO_DIRCLR_PIN29_Msk    (0x1UL << GPIO_DIRCLR_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_DIRCLR_PIN29_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN29_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN29_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 28 : Set as input pin 28 */
#define GPIO_DIRCLR_PIN28_Pos    (28UL)                           /*!< Position of PIN28 field. */
#define GPIO_DIRCLR_PIN28_Msk    (0x1UL << GPIO_DIRCLR_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_DIRCLR_PIN28_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN28_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN28_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 27 : Set as input pin 27 */
#define GPIO_DIRCLR_PIN27_Pos    (27UL)                           /*!< Position of PIN27 field. */
#define GPIO_DIRCLR_PIN27_Msk    (0x1UL << GPIO_DIRCLR_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_DIRCLR_PIN27_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN27_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN27_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 26 : Set as input pin 26 */
#define GPIO_DIRCLR_PIN26_Pos    (26UL)                           /*!< Position of PIN26 field. */
#define GPIO_DIRCLR_PIN26_Msk    (0x1UL << GPIO_DIRCLR_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_DIRCLR_PIN26_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN26_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN26_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 25 : Set as input pin 25 */
#define GPIO_DIRCLR_PIN25_Pos    (25UL)                           /*!< Position of PIN25 field. */
#define GPIO_DIRCLR_PIN25_Msk    (0x1UL << GPIO_DIRCLR_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_DIRCLR_PIN25_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN25_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN25_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 24 : Set as input pin 24 */
#define GPIO_DIRCLR_PIN24_Pos    (24UL)                           /*!< Position of PIN24 field. */
#define GPIO_DIRCLR_PIN24_Msk    (0x1UL << GPIO_DIRCLR_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_DIRCLR_PIN24_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN24_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN24_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 23 : Set as input pin 23 */
#define GPIO_DIRCLR_PIN23_Pos    (23UL)                           /*!< Position of PIN23 field. */
#define GPIO_DIRCLR_PIN23_Msk    (0x1UL << GPIO_DIRCLR_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_DIRCLR_PIN23_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN23_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN23_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 22 : Set as input pin 22 */
#define GPIO_DIRCLR_PIN22_Pos    (22UL)                           /*!< Position of PIN22 field. */
#define GPIO_DIRCLR_PIN22_Msk    (0x1UL << GPIO_DIRCLR_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_DIRCLR_PIN22_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN22_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN22_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 21 : Set as input pin 21 */
#define GPIO_DIRCLR_PIN21_Pos    (21UL)                           /*!< Position of PIN21 field. */
#define GPIO_DIRCLR_PIN21_Msk    (0x1UL << GPIO_DIRCLR_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_DIRCLR_PIN21_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN21_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN21_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 20 : Set as input pin 20 */
#define GPIO_DIRCLR_PIN20_Pos    (20UL)                           /*!< Position of PIN20 field. */
#define GPIO_DIRCLR_PIN20_Msk    (0x1UL << GPIO_DIRCLR_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_DIRCLR_PIN20_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN20_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN20_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 19 : Set as input pin 19 */
#define GPIO_DIRCLR_PIN19_Pos    (19UL)                           /*!< Position of PIN19 field. */
#define GPIO_DIRCLR_PIN19_Msk    (0x1UL << GPIO_DIRCLR_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_DIRCLR_PIN19_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN19_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN19_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 18 : Set as input pin 18 */
#define GPIO_DIRCLR_PIN18_Pos    (18UL)                           /*!< Position of PIN18 field. */
#define GPIO_DIRCLR_PIN18_Msk    (0x1UL << GPIO_DIRCLR_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_DIRCLR_PIN18_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN18_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN18_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 17 : Set as input pin 17 */
#define GPIO_DIRCLR_PIN17_Pos    (17UL)                           /*!< Position of PIN17 field. */
#define GPIO_DIRCLR_PIN17_Msk    (0x1UL << GPIO_DIRCLR_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_DIRCLR_PIN17_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN17_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN17_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 16 : Set as input pin 16 */
#define GPIO_DIRCLR_PIN16_Pos    (16UL)                           /*!< Position of PIN16 field. */
#define GPIO_DIRCLR_PIN16_Msk    (0x1UL << GPIO_DIRCLR_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_DIRCLR_PIN16_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN16_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN16_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 15 : Set as input pin 15 */
#define GPIO_DIRCLR_PIN15_Pos    (15UL)                           /*!< Position of PIN15 field. */
#define GPIO_DIRCLR_PIN15_Msk    (0x1UL << GPIO_DIRCLR_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_DIRCLR_PIN15_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN15_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN15_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 14 : Set as input pin 14 */
#define GPIO_DIRCLR_PIN14_Pos    (14UL)                           /*!< Position of PIN14 field. */
#define GPIO_DIRCLR_PIN14_Msk    (0x1UL << GPIO_DIRCLR_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_DIRCLR_PIN14_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN14_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN14_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 13 : Set as input pin 13 */
#define GPIO_DIRCLR_PIN13_Pos    (13UL)                           /*!< Position of PIN13 field. */
#define GPIO_DIRCLR_PIN13_Msk    (0x1UL << GPIO_DIRCLR_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_DIRCLR_PIN13_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN13_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN13_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 12 : Set as input pin 12 */
#define GPIO_DIRCLR_PIN12_Pos    (12UL)                           /*!< Position of PIN12 field. */
#define GPIO_DIRCLR_PIN12_Msk    (0x1UL << GPIO_DIRCLR_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_DIRCLR_PIN12_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN12_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN12_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 11 : Set as input pin 11 */
#define GPIO_DIRCLR_PIN11_Pos    (11UL)                           /*!< Position of PIN11 field. */
#define GPIO_DIRCLR_PIN11_Msk    (0x1UL << GPIO_DIRCLR_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_DIRCLR_PIN11_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN11_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN11_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 10 : Set as input pin 10 */
#define GPIO_DIRCLR_PIN10_Pos    (10UL)                           /*!< Position of PIN10 field. */
#define GPIO_DIRCLR_PIN10_Msk    (0x1UL << GPIO_DIRCLR_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_DIRCLR_PIN10_Input  (0UL)                            /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN10_Output (1UL)                            /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN10_Clear                                                                    \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 9 : Set as input pin 9 */
#define GPIO_DIRCLR_PIN9_Pos    (9UL)                           /*!< Position of PIN9 field. */
#define GPIO_DIRCLR_PIN9_Msk    (0x1UL << GPIO_DIRCLR_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_DIRCLR_PIN9_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN9_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN9_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 8 : Set as input pin 8 */
#define GPIO_DIRCLR_PIN8_Pos    (8UL)                           /*!< Position of PIN8 field. */
#define GPIO_DIRCLR_PIN8_Msk    (0x1UL << GPIO_DIRCLR_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_DIRCLR_PIN8_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN8_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN8_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 7 : Set as input pin 7 */
#define GPIO_DIRCLR_PIN7_Pos    (7UL)                           /*!< Position of PIN7 field. */
#define GPIO_DIRCLR_PIN7_Msk    (0x1UL << GPIO_DIRCLR_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_DIRCLR_PIN7_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN7_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN7_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 6 : Set as input pin 6 */
#define GPIO_DIRCLR_PIN6_Pos    (6UL)                           /*!< Position of PIN6 field. */
#define GPIO_DIRCLR_PIN6_Msk    (0x1UL << GPIO_DIRCLR_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_DIRCLR_PIN6_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN6_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN6_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 5 : Set as input pin 5 */
#define GPIO_DIRCLR_PIN5_Pos    (5UL)                           /*!< Position of PIN5 field. */
#define GPIO_DIRCLR_PIN5_Msk    (0x1UL << GPIO_DIRCLR_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_DIRCLR_PIN5_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN5_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN5_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 4 : Set as input pin 4 */
#define GPIO_DIRCLR_PIN4_Pos    (4UL)                           /*!< Position of PIN4 field. */
#define GPIO_DIRCLR_PIN4_Msk    (0x1UL << GPIO_DIRCLR_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_DIRCLR_PIN4_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN4_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN4_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 3 : Set as input pin 3 */
#define GPIO_DIRCLR_PIN3_Pos    (3UL)                           /*!< Position of PIN3 field. */
#define GPIO_DIRCLR_PIN3_Msk    (0x1UL << GPIO_DIRCLR_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_DIRCLR_PIN3_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN3_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN3_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 2 : Set as input pin 2 */
#define GPIO_DIRCLR_PIN2_Pos    (2UL)                           /*!< Position of PIN2 field. */
#define GPIO_DIRCLR_PIN2_Msk    (0x1UL << GPIO_DIRCLR_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_DIRCLR_PIN2_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN2_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN2_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 1 : Set as input pin 1 */
#define GPIO_DIRCLR_PIN1_Pos    (1UL)                           /*!< Position of PIN1 field. */
#define GPIO_DIRCLR_PIN1_Msk    (0x1UL << GPIO_DIRCLR_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_DIRCLR_PIN1_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN1_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN1_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 0 : Set as input pin 0 */
#define GPIO_DIRCLR_PIN0_Pos    (0UL)                           /*!< Position of PIN0 field. */
#define GPIO_DIRCLR_PIN0_Msk    (0x1UL << GPIO_DIRCLR_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_DIRCLR_PIN0_Input  (0UL)                           /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN0_Output (1UL)                           /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN0_Clear                                                                     \
  (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Register: GPIO_LATCH */
/* Description: Latch register indicating what GPIO pins that have met the criteria set in the PIN_CNF[n].SENSE registers */

/* Bit 31 : Status on whether PIN31 has met criteria set in PIN_CNF31.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN31_Pos           (31UL) /*!< Position of PIN31 field. */
#define GPIO_LATCH_PIN31_Msk           (0x1UL << GPIO_LATCH_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_LATCH_PIN31_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN31_Latched       (1UL) /*!< Criteria has been met */

/* Bit 30 : Status on whether PIN30 has met criteria set in PIN_CNF30.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN30_Pos           (30UL) /*!< Position of PIN30 field. */
#define GPIO_LATCH_PIN30_Msk           (0x1UL << GPIO_LATCH_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_LATCH_PIN30_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN30_Latched       (1UL) /*!< Criteria has been met */

/* Bit 29 : Status on whether PIN29 has met criteria set in PIN_CNF29.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN29_Pos           (29UL) /*!< Position of PIN29 field. */
#define GPIO_LATCH_PIN29_Msk           (0x1UL << GPIO_LATCH_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_LATCH_PIN29_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN29_Latched       (1UL) /*!< Criteria has been met */

/* Bit 28 : Status on whether PIN28 has met criteria set in PIN_CNF28.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN28_Pos           (28UL) /*!< Position of PIN28 field. */
#define GPIO_LATCH_PIN28_Msk           (0x1UL << GPIO_LATCH_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_LATCH_PIN28_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN28_Latched       (1UL) /*!< Criteria has been met */

/* Bit 27 : Status on whether PIN27 has met criteria set in PIN_CNF27.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN27_Pos           (27UL) /*!< Position of PIN27 field. */
#define GPIO_LATCH_PIN27_Msk           (0x1UL << GPIO_LATCH_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_LATCH_PIN27_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN27_Latched       (1UL) /*!< Criteria has been met */

/* Bit 26 : Status on whether PIN26 has met criteria set in PIN_CNF26.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN26_Pos           (26UL) /*!< Position of PIN26 field. */
#define GPIO_LATCH_PIN26_Msk           (0x1UL << GPIO_LATCH_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_LATCH_PIN26_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN26_Latched       (1UL) /*!< Criteria has been met */

/* Bit 25 : Status on whether PIN25 has met criteria set in PIN_CNF25.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN25_Pos           (25UL) /*!< Position of PIN25 field. */
#define GPIO_LATCH_PIN25_Msk           (0x1UL << GPIO_LATCH_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_LATCH_PIN25_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN25_Latched       (1UL) /*!< Criteria has been met */

/* Bit 24 : Status on whether PIN24 has met criteria set in PIN_CNF24.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN24_Pos           (24UL) /*!< Position of PIN24 field. */
#define GPIO_LATCH_PIN24_Msk           (0x1UL << GPIO_LATCH_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_LATCH_PIN24_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN24_Latched       (1UL) /*!< Criteria has been met */

/* Bit 23 : Status on whether PIN23 has met criteria set in PIN_CNF23.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN23_Pos           (23UL) /*!< Position of PIN23 field. */
#define GPIO_LATCH_PIN23_Msk           (0x1UL << GPIO_LATCH_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_LATCH_PIN23_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN23_Latched       (1UL) /*!< Criteria has been met */

/* Bit 22 : Status on whether PIN22 has met criteria set in PIN_CNF22.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN22_Pos           (22UL) /*!< Position of PIN22 field. */
#define GPIO_LATCH_PIN22_Msk           (0x1UL << GPIO_LATCH_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_LATCH_PIN22_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN22_Latched       (1UL) /*!< Criteria has been met */

/* Bit 21 : Status on whether PIN21 has met criteria set in PIN_CNF21.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN21_Pos           (21UL) /*!< Position of PIN21 field. */
#define GPIO_LATCH_PIN21_Msk           (0x1UL << GPIO_LATCH_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_LATCH_PIN21_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN21_Latched       (1UL) /*!< Criteria has been met */

/* Bit 20 : Status on whether PIN20 has met criteria set in PIN_CNF20.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN20_Pos           (20UL) /*!< Position of PIN20 field. */
#define GPIO_LATCH_PIN20_Msk           (0x1UL << GPIO_LATCH_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_LATCH_PIN20_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN20_Latched       (1UL) /*!< Criteria has been met */

/* Bit 19 : Status on whether PIN19 has met criteria set in PIN_CNF19.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN19_Pos           (19UL) /*!< Position of PIN19 field. */
#define GPIO_LATCH_PIN19_Msk           (0x1UL << GPIO_LATCH_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_LATCH_PIN19_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN19_Latched       (1UL) /*!< Criteria has been met */

/* Bit 18 : Status on whether PIN18 has met criteria set in PIN_CNF18.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN18_Pos           (18UL) /*!< Position of PIN18 field. */
#define GPIO_LATCH_PIN18_Msk           (0x1UL << GPIO_LATCH_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_LATCH_PIN18_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN18_Latched       (1UL) /*!< Criteria has been met */

/* Bit 17 : Status on whether PIN17 has met criteria set in PIN_CNF17.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN17_Pos           (17UL) /*!< Position of PIN17 field. */
#define GPIO_LATCH_PIN17_Msk           (0x1UL << GPIO_LATCH_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_LATCH_PIN17_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN17_Latched       (1UL) /*!< Criteria has been met */

/* Bit 16 : Status on whether PIN16 has met criteria set in PIN_CNF16.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN16_Pos           (16UL) /*!< Position of PIN16 field. */
#define GPIO_LATCH_PIN16_Msk           (0x1UL << GPIO_LATCH_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_LATCH_PIN16_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN16_Latched       (1UL) /*!< Criteria has been met */

/* Bit 15 : Status on whether PIN15 has met criteria set in PIN_CNF15.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN15_Pos           (15UL) /*!< Position of PIN15 field. */
#define GPIO_LATCH_PIN15_Msk           (0x1UL << GPIO_LATCH_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_LATCH_PIN15_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN15_Latched       (1UL) /*!< Criteria has been met */

/* Bit 14 : Status on whether PIN14 has met criteria set in PIN_CNF14.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN14_Pos           (14UL) /*!< Position of PIN14 field. */
#define GPIO_LATCH_PIN14_Msk           (0x1UL << GPIO_LATCH_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_LATCH_PIN14_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN14_Latched       (1UL) /*!< Criteria has been met */

/* Bit 13 : Status on whether PIN13 has met criteria set in PIN_CNF13.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN13_Pos           (13UL) /*!< Position of PIN13 field. */
#define GPIO_LATCH_PIN13_Msk           (0x1UL << GPIO_LATCH_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_LATCH_PIN13_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN13_Latched       (1UL) /*!< Criteria has been met */

/* Bit 12 : Status on whether PIN12 has met criteria set in PIN_CNF12.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN12_Pos           (12UL) /*!< Position of PIN12 field. */
#define GPIO_LATCH_PIN12_Msk           (0x1UL << GPIO_LATCH_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_LATCH_PIN12_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN12_Latched       (1UL) /*!< Criteria has been met */

/* Bit 11 : Status on whether PIN11 has met criteria set in PIN_CNF11.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN11_Pos           (11UL) /*!< Position of PIN11 field. */
#define GPIO_LATCH_PIN11_Msk           (0x1UL << GPIO_LATCH_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_LATCH_PIN11_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN11_Latched       (1UL) /*!< Criteria has been met */

/* Bit 10 : Status on whether PIN10 has met criteria set in PIN_CNF10.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN10_Pos           (10UL) /*!< Position of PIN10 field. */
#define GPIO_LATCH_PIN10_Msk           (0x1UL << GPIO_LATCH_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_LATCH_PIN10_NotLatched    (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN10_Latched       (1UL) /*!< Criteria has been met */

/* Bit 9 : Status on whether PIN9 has met criteria set in PIN_CNF9.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN9_Pos            (9UL) /*!< Position of PIN9 field. */
#define GPIO_LATCH_PIN9_Msk            (0x1UL << GPIO_LATCH_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_LATCH_PIN9_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN9_Latched        (1UL) /*!< Criteria has been met */

/* Bit 8 : Status on whether PIN8 has met criteria set in PIN_CNF8.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN8_Pos            (8UL) /*!< Position of PIN8 field. */
#define GPIO_LATCH_PIN8_Msk            (0x1UL << GPIO_LATCH_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_LATCH_PIN8_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN8_Latched        (1UL) /*!< Criteria has been met */

/* Bit 7 : Status on whether PIN7 has met criteria set in PIN_CNF7.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN7_Pos            (7UL) /*!< Position of PIN7 field. */
#define GPIO_LATCH_PIN7_Msk            (0x1UL << GPIO_LATCH_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_LATCH_PIN7_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN7_Latched        (1UL) /*!< Criteria has been met */

/* Bit 6 : Status on whether PIN6 has met criteria set in PIN_CNF6.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN6_Pos            (6UL) /*!< Position of PIN6 field. */
#define GPIO_LATCH_PIN6_Msk            (0x1UL << GPIO_LATCH_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_LATCH_PIN6_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN6_Latched        (1UL) /*!< Criteria has been met */

/* Bit 5 : Status on whether PIN5 has met criteria set in PIN_CNF5.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN5_Pos            (5UL) /*!< Position of PIN5 field. */
#define GPIO_LATCH_PIN5_Msk            (0x1UL << GPIO_LATCH_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_LATCH_PIN5_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN5_Latched        (1UL) /*!< Criteria has been met */

/* Bit 4 : Status on whether PIN4 has met criteria set in PIN_CNF4.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN4_Pos            (4UL) /*!< Position of PIN4 field. */
#define GPIO_LATCH_PIN4_Msk            (0x1UL << GPIO_LATCH_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_LATCH_PIN4_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN4_Latched        (1UL) /*!< Criteria has been met */

/* Bit 3 : Status on whether PIN3 has met criteria set in PIN_CNF3.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN3_Pos            (3UL) /*!< Position of PIN3 field. */
#define GPIO_LATCH_PIN3_Msk            (0x1UL << GPIO_LATCH_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_LATCH_PIN3_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN3_Latched        (1UL) /*!< Criteria has been met */

/* Bit 2 : Status on whether PIN2 has met criteria set in PIN_CNF2.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN2_Pos            (2UL) /*!< Position of PIN2 field. */
#define GPIO_LATCH_PIN2_Msk            (0x1UL << GPIO_LATCH_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_LATCH_PIN2_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN2_Latched        (1UL) /*!< Criteria has been met */

/* Bit 1 : Status on whether PIN1 has met criteria set in PIN_CNF1.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN1_Pos            (1UL) /*!< Position of PIN1 field. */
#define GPIO_LATCH_PIN1_Msk            (0x1UL << GPIO_LATCH_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_LATCH_PIN1_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN1_Latched        (1UL) /*!< Criteria has been met */

/* Bit 0 : Status on whether PIN0 has met criteria set in PIN_CNF0.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN0_Pos            (0UL) /*!< Position of PIN0 field. */
#define GPIO_LATCH_PIN0_Msk            (0x1UL << GPIO_LATCH_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_LATCH_PIN0_NotLatched     (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN0_Latched        (1UL) /*!< Criteria has been met */

/* Register: GPIO_DETECTMODE */
/* Description: Select between default DETECT signal behaviour and LDETECT mode */

/* Bit 0 : Select between default DETECT signal behaviour and LDETECT mode */
#define GPIO_DETECTMODE_DETECTMODE_Pos (0UL) /*!< Position of DETECTMODE field. */
#define GPIO_DETECTMODE_DETECTMODE_Msk                                                             \
  (0x1UL << GPIO_DETECTMODE_DETECTMODE_Pos) /*!< Bit mask of DETECTMODE field. */
#define GPIO_DETECTMODE_DETECTMODE_Default                                                         \
  (0UL) /*!< DETECT directly connected to PIN DETECT signals */
#define GPIO_DETECTMODE_DETECTMODE_LDETECT (1UL) /*!< Use the latched LDETECT behaviour */

/* Register: GPIO_PIN_CNF */
/* Description: Description collection: Configuration of GPIO pins */

/* Bits 17..16 : Pin sensing mechanism */
#define GPIO_PIN_CNF_SENSE_Pos             (16UL) /*!< Position of SENSE field. */
#define GPIO_PIN_CNF_SENSE_Msk             (0x3UL << GPIO_PIN_CNF_SENSE_Pos) /*!< Bit mask of SENSE field. */
#define GPIO_PIN_CNF_SENSE_Disabled        (0UL)                             /*!< Disabled */
#define GPIO_PIN_CNF_SENSE_High            (2UL) /*!< Sense for high level */
#define GPIO_PIN_CNF_SENSE_Low             (3UL) /*!< Sense for low level */

/* Bits 10..8 : Drive configuration */
#define GPIO_PIN_CNF_DRIVE_Pos             (8UL) /*!< Position of DRIVE field. */
#define GPIO_PIN_CNF_DRIVE_Msk             (0x7UL << GPIO_PIN_CNF_DRIVE_Pos) /*!< Bit mask of DRIVE field. */
#define GPIO_PIN_CNF_DRIVE_S0S1            (0UL) /*!< Standard '0', standard '1' */
#define GPIO_PIN_CNF_DRIVE_H0S1            (1UL) /*!< High drive '0', standard '1' */
#define GPIO_PIN_CNF_DRIVE_S0H1            (2UL) /*!< Standard '0', high drive '1' */
#define GPIO_PIN_CNF_DRIVE_H0H1            (3UL) /*!< High drive '0', high 'drive '1'' */
#define GPIO_PIN_CNF_DRIVE_D0S1                                                                    \
  (4UL) /*!< Disconnect '0' standard '1' (normally used for wired-or connections) */
#define GPIO_PIN_CNF_DRIVE_D0H1                                                                    \
  (5UL) /*!< Disconnect '0', high drive '1' (normally used for wired-or connections) */
#define GPIO_PIN_CNF_DRIVE_S0D1                                                                    \
  (6UL) /*!< Standard '0'. disconnect '1' (normally used for wired-and connections) */
#define GPIO_PIN_CNF_DRIVE_H0D1                                                                    \
  (7UL) /*!< High drive '0', disconnect '1' (normally used for wired-and connections) */

/* Bits 3..2 : Pull configuration */
#define GPIO_PIN_CNF_PULL_Pos                   (2UL) /*!< Position of PULL field. */
#define GPIO_PIN_CNF_PULL_Msk                   (0x3UL << GPIO_PIN_CNF_PULL_Pos) /*!< Bit mask of PULL field. */
#define GPIO_PIN_CNF_PULL_Disabled              (0UL)                            /*!< No pull */
#define GPIO_PIN_CNF_PULL_Pulldown              (1UL) /*!< Pull down on pin */
#define GPIO_PIN_CNF_PULL_Pullup                (3UL) /*!< Pull up on pin */

/* Bit 1 : Connect or disconnect input buffer */
#define GPIO_PIN_CNF_INPUT_Pos                  (1UL) /*!< Position of INPUT field. */
#define GPIO_PIN_CNF_INPUT_Msk                  (0x1UL << GPIO_PIN_CNF_INPUT_Pos) /*!< Bit mask of INPUT field. */
#define GPIO_PIN_CNF_INPUT_Connect              (0UL) /*!< Connect input buffer */
#define GPIO_PIN_CNF_INPUT_Disconnect           (1UL) /*!< Disconnect input buffer */

/* Bit 0 : Pin direction. Same physical register as DIR register */
#define GPIO_PIN_CNF_DIR_Pos                    (0UL) /*!< Position of DIR field. */
#define GPIO_PIN_CNF_DIR_Msk                    (0x1UL << GPIO_PIN_CNF_DIR_Pos) /*!< Bit mask of DIR field. */
#define GPIO_PIN_CNF_DIR_Input                  (0UL) /*!< Configure pin as an input pin */
#define GPIO_PIN_CNF_DIR_Output                 (1UL) /*!< Configure pin as an output pin */


/* Peripheral: POWER */
/* Description: Power control */

/* Register: POWER_TASKS_CONSTLAT */
/* Description: Enable Constant Latency mode */

/* Bit 0 : Enable Constant Latency mode */
#define POWER_TASKS_CONSTLAT_TASKS_CONSTLAT_Pos (0UL) /*!< Position of TASKS_CONSTLAT field. */
#define POWER_TASKS_CONSTLAT_TASKS_CONSTLAT_Msk                                                    \
  (0x1UL << POWER_TASKS_CONSTLAT_TASKS_CONSTLAT_Pos)      /*!< Bit mask of TASKS_CONSTLAT field. */
#define POWER_TASKS_CONSTLAT_TASKS_CONSTLAT_Trigger (1UL) /*!< Trigger task */

/* Register: POWER_TASKS_LOWPWR */
/* Description: Enable Low-power mode (variable latency) */

/* Bit 0 : Enable Low-power mode (variable latency) */
#define POWER_TASKS_LOWPWR_TASKS_LOWPWR_Pos         (0UL) /*!< Position of TASKS_LOWPWR field. */
#define POWER_TASKS_LOWPWR_TASKS_LOWPWR_Msk                                                        \
  (0x1UL << POWER_TASKS_LOWPWR_TASKS_LOWPWR_Pos)      /*!< Bit mask of TASKS_LOWPWR field. */
#define POWER_TASKS_LOWPWR_TASKS_LOWPWR_Trigger (1UL) /*!< Trigger task */

/* Register: POWER_EVENTS_POFWARN */
/* Description: Power failure warning */

/* Bit 0 : Power failure warning */
#define POWER_EVENTS_POFWARN_EVENTS_POFWARN_Pos (0UL) /*!< Position of EVENTS_POFWARN field. */
#define POWER_EVENTS_POFWARN_EVENTS_POFWARN_Msk                                                    \
  (0x1UL << POWER_EVENTS_POFWARN_EVENTS_POFWARN_Pos) /*!< Bit mask of EVENTS_POFWARN field. */
#define POWER_EVENTS_POFWARN_EVENTS_POFWARN_NotGenerated (0UL) /*!< Event not generated */
#define POWER_EVENTS_POFWARN_EVENTS_POFWARN_Generated    (1UL) /*!< Event generated */

/* Register: POWER_EVENTS_SLEEPENTER */
/* Description: CPU entered WFI/WFE sleep */

/* Bit 0 : CPU entered WFI/WFE sleep */
#define POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_Pos                                              \
  (0UL) /*!< Position of EVENTS_SLEEPENTER field. */
#define POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_Msk                                              \
  (0x1UL                                                                                           \
   << POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_Pos) /*!< Bit mask of EVENTS_SLEEPENTER field. */
#define POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_NotGenerated (0UL) /*!< Event not generated */
#define POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_Generated    (1UL) /*!< Event generated */

/* Register: POWER_EVENTS_SLEEPEXIT */
/* Description: CPU exited WFI/WFE sleep */

/* Bit 0 : CPU exited WFI/WFE sleep */
#define POWER_EVENTS_SLEEPEXIT_EVENTS_SLEEPEXIT_Pos                                                \
  (0UL) /*!< Position of EVENTS_SLEEPEXIT field. */
#define POWER_EVENTS_SLEEPEXIT_EVENTS_SLEEPEXIT_Msk                                                \
  (0x1UL << POWER_EVENTS_SLEEPEXIT_EVENTS_SLEEPEXIT_Pos) /*!< Bit mask of EVENTS_SLEEPEXIT field. */
#define POWER_EVENTS_SLEEPEXIT_EVENTS_SLEEPEXIT_NotGenerated (0UL) /*!< Event not generated */
#define POWER_EVENTS_SLEEPEXIT_EVENTS_SLEEPEXIT_Generated    (1UL) /*!< Event generated */

/* Register: POWER_EVENTS_USBDETECTED */
/* Description: Voltage supply detected on VBUS */

/* Bit 0 : Voltage supply detected on VBUS */
#define POWER_EVENTS_USBDETECTED_EVENTS_USBDETECTED_Pos                                            \
  (0UL) /*!< Position of EVENTS_USBDETECTED field. */
#define POWER_EVENTS_USBDETECTED_EVENTS_USBDETECTED_Msk                                            \
  (0x1UL                                                                                           \
   << POWER_EVENTS_USBDETECTED_EVENTS_USBDETECTED_Pos) /*!< Bit mask of EVENTS_USBDETECTED field. */
#define POWER_EVENTS_USBDETECTED_EVENTS_USBDETECTED_NotGenerated (0UL) /*!< Event not generated */
#define POWER_EVENTS_USBDETECTED_EVENTS_USBDETECTED_Generated    (1UL) /*!< Event generated */

/* Register: POWER_EVENTS_USBREMOVED */
/* Description: Voltage supply removed from VBUS */

/* Bit 0 : Voltage supply removed from VBUS */
#define POWER_EVENTS_USBREMOVED_EVENTS_USBREMOVED_Pos                                              \
  (0UL) /*!< Position of EVENTS_USBREMOVED field. */
#define POWER_EVENTS_USBREMOVED_EVENTS_USBREMOVED_Msk                                              \
  (0x1UL                                                                                           \
   << POWER_EVENTS_USBREMOVED_EVENTS_USBREMOVED_Pos) /*!< Bit mask of EVENTS_USBREMOVED field. */
#define POWER_EVENTS_USBREMOVED_EVENTS_USBREMOVED_NotGenerated (0UL) /*!< Event not generated */
#define POWER_EVENTS_USBREMOVED_EVENTS_USBREMOVED_Generated    (1UL) /*!< Event generated */

/* Register: POWER_EVENTS_USBPWRRDY */
/* Description: USB 3.3 V supply ready */

/* Bit 0 : USB 3.3 V supply ready */
#define POWER_EVENTS_USBPWRRDY_EVENTS_USBPWRRDY_Pos                                                \
  (0UL) /*!< Position of EVENTS_USBPWRRDY field. */
#define POWER_EVENTS_USBPWRRDY_EVENTS_USBPWRRDY_Msk                                                \
  (0x1UL << POWER_EVENTS_USBPWRRDY_EVENTS_USBPWRRDY_Pos) /*!< Bit mask of EVENTS_USBPWRRDY field. */
#define POWER_EVENTS_USBPWRRDY_EVENTS_USBPWRRDY_NotGenerated (0UL) /*!< Event not generated */
#define POWER_EVENTS_USBPWRRDY_EVENTS_USBPWRRDY_Generated    (1UL) /*!< Event generated */

/* Register: POWER_INTENSET */
/* Description: Enable interrupt */

/* Bit 9 : Write '1' to enable interrupt for event USBPWRRDY */
#define POWER_INTENSET_USBPWRRDY_Pos                         (9UL) /*!< Position of USBPWRRDY field. */
#define POWER_INTENSET_USBPWRRDY_Msk                                                               \
  (0x1UL << POWER_INTENSET_USBPWRRDY_Pos)       /*!< Bit mask of USBPWRRDY field. */
#define POWER_INTENSET_USBPWRRDY_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_USBPWRRDY_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_USBPWRRDY_Set      (1UL) /*!< Enable */

/* Bit 8 : Write '1' to enable interrupt for event USBREMOVED */
#define POWER_INTENSET_USBREMOVED_Pos     (8UL) /*!< Position of USBREMOVED field. */
#define POWER_INTENSET_USBREMOVED_Msk                                                              \
  (0x1UL << POWER_INTENSET_USBREMOVED_Pos)       /*!< Bit mask of USBREMOVED field. */
#define POWER_INTENSET_USBREMOVED_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_USBREMOVED_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_USBREMOVED_Set      (1UL) /*!< Enable */

/* Bit 7 : Write '1' to enable interrupt for event USBDETECTED */
#define POWER_INTENSET_USBDETECTED_Pos     (7UL) /*!< Position of USBDETECTED field. */
#define POWER_INTENSET_USBDETECTED_Msk                                                             \
  (0x1UL << POWER_INTENSET_USBDETECTED_Pos)       /*!< Bit mask of USBDETECTED field. */
#define POWER_INTENSET_USBDETECTED_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_USBDETECTED_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_USBDETECTED_Set      (1UL) /*!< Enable */

/* Bit 6 : Write '1' to enable interrupt for event SLEEPEXIT */
#define POWER_INTENSET_SLEEPEXIT_Pos        (6UL) /*!< Position of SLEEPEXIT field. */
#define POWER_INTENSET_SLEEPEXIT_Msk                                                               \
  (0x1UL << POWER_INTENSET_SLEEPEXIT_Pos)       /*!< Bit mask of SLEEPEXIT field. */
#define POWER_INTENSET_SLEEPEXIT_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_SLEEPEXIT_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_SLEEPEXIT_Set      (1UL) /*!< Enable */

/* Bit 5 : Write '1' to enable interrupt for event SLEEPENTER */
#define POWER_INTENSET_SLEEPENTER_Pos     (5UL) /*!< Position of SLEEPENTER field. */
#define POWER_INTENSET_SLEEPENTER_Msk                                                              \
  (0x1UL << POWER_INTENSET_SLEEPENTER_Pos)       /*!< Bit mask of SLEEPENTER field. */
#define POWER_INTENSET_SLEEPENTER_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_SLEEPENTER_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_SLEEPENTER_Set      (1UL) /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event POFWARN */
#define POWER_INTENSET_POFWARN_Pos         (2UL) /*!< Position of POFWARN field. */
#define POWER_INTENSET_POFWARN_Msk                                                                 \
  (0x1UL << POWER_INTENSET_POFWARN_Pos)       /*!< Bit mask of POFWARN field. */
#define POWER_INTENSET_POFWARN_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_POFWARN_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_POFWARN_Set      (1UL) /*!< Enable */

/* Register: POWER_INTENCLR */
/* Description: Disable interrupt */

/* Bit 9 : Write '1' to disable interrupt for event USBPWRRDY */
#define POWER_INTENCLR_USBPWRRDY_Pos    (9UL) /*!< Position of USBPWRRDY field. */
#define POWER_INTENCLR_USBPWRRDY_Msk                                                               \
  (0x1UL << POWER_INTENCLR_USBPWRRDY_Pos)       /*!< Bit mask of USBPWRRDY field. */
#define POWER_INTENCLR_USBPWRRDY_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_USBPWRRDY_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_USBPWRRDY_Clear    (1UL) /*!< Disable */

/* Bit 8 : Write '1' to disable interrupt for event USBREMOVED */
#define POWER_INTENCLR_USBREMOVED_Pos     (8UL) /*!< Position of USBREMOVED field. */
#define POWER_INTENCLR_USBREMOVED_Msk                                                              \
  (0x1UL << POWER_INTENCLR_USBREMOVED_Pos)       /*!< Bit mask of USBREMOVED field. */
#define POWER_INTENCLR_USBREMOVED_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_USBREMOVED_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_USBREMOVED_Clear    (1UL) /*!< Disable */

/* Bit 7 : Write '1' to disable interrupt for event USBDETECTED */
#define POWER_INTENCLR_USBDETECTED_Pos     (7UL) /*!< Position of USBDETECTED field. */
#define POWER_INTENCLR_USBDETECTED_Msk                                                             \
  (0x1UL << POWER_INTENCLR_USBDETECTED_Pos)       /*!< Bit mask of USBDETECTED field. */
#define POWER_INTENCLR_USBDETECTED_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_USBDETECTED_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_USBDETECTED_Clear    (1UL) /*!< Disable */

/* Bit 6 : Write '1' to disable interrupt for event SLEEPEXIT */
#define POWER_INTENCLR_SLEEPEXIT_Pos        (6UL) /*!< Position of SLEEPEXIT field. */
#define POWER_INTENCLR_SLEEPEXIT_Msk                                                               \
  (0x1UL << POWER_INTENCLR_SLEEPEXIT_Pos)       /*!< Bit mask of SLEEPEXIT field. */
#define POWER_INTENCLR_SLEEPEXIT_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_SLEEPEXIT_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_SLEEPEXIT_Clear    (1UL) /*!< Disable */

/* Bit 5 : Write '1' to disable interrupt for event SLEEPENTER */
#define POWER_INTENCLR_SLEEPENTER_Pos     (5UL) /*!< Position of SLEEPENTER field. */
#define POWER_INTENCLR_SLEEPENTER_Msk                                                              \
  (0x1UL << POWER_INTENCLR_SLEEPENTER_Pos)       /*!< Bit mask of SLEEPENTER field. */
#define POWER_INTENCLR_SLEEPENTER_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_SLEEPENTER_Enabled  (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_SLEEPENTER_Clear    (1UL) /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event POFWARN */
#define POWER_INTENCLR_POFWARN_Pos         (2UL) /*!< Position of POFWARN field. */
#define POWER_INTENCLR_POFWARN_Msk                                                                 \
  (0x1UL << POWER_INTENCLR_POFWARN_Pos)        /*!< Bit mask of POFWARN field. */
#define POWER_INTENCLR_POFWARN_Disabled  (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_POFWARN_Enabled   (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_POFWARN_Clear     (1UL) /*!< Disable */

/* Register: POWER_RESETREAS */
/* Description: Reset reason */

/* Bit 20 : Reset due to wake up from System OFF mode by VBUS rising into valid range */
#define POWER_RESETREAS_VBUS_Pos         (20UL) /*!< Position of VBUS field. */
#define POWER_RESETREAS_VBUS_Msk         (0x1UL << POWER_RESETREAS_VBUS_Pos) /*!< Bit mask of VBUS field. */
#define POWER_RESETREAS_VBUS_NotDetected (0UL)                               /*!< Not detected */
#define POWER_RESETREAS_VBUS_Detected    (1UL)                               /*!< Detected */

/* Bit 18 : Reset due to wake up from System OFF mode when wakeup is triggered from entering into debug interface mode */
#define POWER_RESETREAS_DIF_Pos          (18UL) /*!< Position of DIF field. */
#define POWER_RESETREAS_DIF_Msk          (0x1UL << POWER_RESETREAS_DIF_Pos) /*!< Bit mask of DIF field. */
#define POWER_RESETREAS_DIF_NotDetected  (0UL)                              /*!< Not detected */
#define POWER_RESETREAS_DIF_Detected     (1UL)                              /*!< Detected */

/* Bit 16 : Reset due to wake up from System OFF mode when wakeup is triggered from DETECT signal from GPIO */
#define POWER_RESETREAS_OFF_Pos          (16UL) /*!< Position of OFF field. */
#define POWER_RESETREAS_OFF_Msk          (0x1UL << POWER_RESETREAS_OFF_Pos) /*!< Bit mask of OFF field. */
#define POWER_RESETREAS_OFF_NotDetected  (0UL)                              /*!< Not detected */
#define POWER_RESETREAS_OFF_Detected     (1UL)                              /*!< Detected */

/* Bit 3 : Reset from CPU lock-up detected */
#define POWER_RESETREAS_LOCKUP_Pos       (3UL) /*!< Position of LOCKUP field. */
#define POWER_RESETREAS_LOCKUP_Msk                                                                 \
  (0x1UL << POWER_RESETREAS_LOCKUP_Pos)          /*!< Bit mask of LOCKUP field. */
#define POWER_RESETREAS_LOCKUP_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_LOCKUP_Detected    (1UL) /*!< Detected */

/* Bit 2 : Reset from soft reset detected */
#define POWER_RESETREAS_SREQ_Pos           (2UL) /*!< Position of SREQ field. */
#define POWER_RESETREAS_SREQ_Msk           (0x1UL << POWER_RESETREAS_SREQ_Pos) /*!< Bit mask of SREQ field. */
#define POWER_RESETREAS_SREQ_NotDetected   (0UL)                               /*!< Not detected */
#define POWER_RESETREAS_SREQ_Detected      (1UL)                               /*!< Detected */

/* Bit 1 : Reset from watchdog detected */
#define POWER_RESETREAS_DOG_Pos            (1UL) /*!< Position of DOG field. */
#define POWER_RESETREAS_DOG_Msk            (0x1UL << POWER_RESETREAS_DOG_Pos) /*!< Bit mask of DOG field. */
#define POWER_RESETREAS_DOG_NotDetected    (0UL)                              /*!< Not detected */
#define POWER_RESETREAS_DOG_Detected       (1UL)                              /*!< Detected */

/* Bit 0 : Reset from pin-reset detected */
#define POWER_RESETREAS_RESETPIN_Pos       (0UL) /*!< Position of RESETPIN field. */
#define POWER_RESETREAS_RESETPIN_Msk                                                               \
  (0x1UL << POWER_RESETREAS_RESETPIN_Pos)          /*!< Bit mask of RESETPIN field. */
#define POWER_RESETREAS_RESETPIN_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_RESETPIN_Detected    (1UL) /*!< Detected */

/* Register: POWER_RAMSTATUS */
/* Description: Deprecated register - RAM status register */

/* Bit 1 : RAM block 1 is on or off/powering up */
#define POWER_RAMSTATUS_RAMBLOCK1_Pos        (1UL) /*!< Position of RAMBLOCK1 field. */
#define POWER_RAMSTATUS_RAMBLOCK1_Msk                                                              \
  (0x1UL << POWER_RAMSTATUS_RAMBLOCK1_Pos)  /*!< Bit mask of RAMBLOCK1 field. */
#define POWER_RAMSTATUS_RAMBLOCK1_Off (0UL) /*!< Off */
#define POWER_RAMSTATUS_RAMBLOCK1_On  (1UL) /*!< On */

/* Bit 0 : RAM block 0 is on or off/powering up */
#define POWER_RAMSTATUS_RAMBLOCK0_Pos (0UL) /*!< Position of RAMBLOCK0 field. */
#define POWER_RAMSTATUS_RAMBLOCK0_Msk                                                              \
  (0x1UL << POWER_RAMSTATUS_RAMBLOCK0_Pos)     /*!< Bit mask of RAMBLOCK0 field. */
#define POWER_RAMSTATUS_RAMBLOCK0_Off    (0UL) /*!< Off */
#define POWER_RAMSTATUS_RAMBLOCK0_On     (1UL) /*!< On */

/* Register: POWER_USBREGSTATUS */
/* Description: USB supply status */

/* Bit 1 : USB supply output settling time elapsed */
#define POWER_USBREGSTATUS_OUTPUTRDY_Pos (1UL) /*!< Position of OUTPUTRDY field. */
#define POWER_USBREGSTATUS_OUTPUTRDY_Msk                                                           \
  (0x1UL << POWER_USBREGSTATUS_OUTPUTRDY_Pos)       /*!< Bit mask of OUTPUTRDY field. */
#define POWER_USBREGSTATUS_OUTPUTRDY_NotReady (0UL) /*!< USBREG output settling time not elapsed */
#define POWER_USBREGSTATUS_OUTPUTRDY_Ready                                                         \
  (1UL) /*!< USBREG output settling time elapsed (same information as USBPWRRDY event) */

/* Bit 0 : VBUS input detection status (USBDETECTED and USBREMOVED events are derived from this information) */
#define POWER_USBREGSTATUS_VBUSDETECT_Pos (0UL) /*!< Position of VBUSDETECT field. */
#define POWER_USBREGSTATUS_VBUSDETECT_Msk                                                          \
  (0x1UL << POWER_USBREGSTATUS_VBUSDETECT_Pos)          /*!< Bit mask of VBUSDETECT field. */
#define POWER_USBREGSTATUS_VBUSDETECT_NoVbus      (0UL) /*!< VBUS voltage below valid threshold */
#define POWER_USBREGSTATUS_VBUSDETECT_VbusPresent (1UL) /*!< VBUS voltage above valid threshold */

/* Register: POWER_SYSTEMOFF */
/* Description: System OFF register */

/* Bit 0 : Enable System OFF mode */
#define POWER_SYSTEMOFF_SYSTEMOFF_Pos             (0UL) /*!< Position of SYSTEMOFF field. */
#define POWER_SYSTEMOFF_SYSTEMOFF_Msk                                                              \
  (0x1UL << POWER_SYSTEMOFF_SYSTEMOFF_Pos)    /*!< Bit mask of SYSTEMOFF field. */
#define POWER_SYSTEMOFF_SYSTEMOFF_Enter (1UL) /*!< Enable System OFF mode */

/* Register: POWER_POFCON */
/* Description: Power-fail comparator configuration */

/* Bits 11..8 : Power-fail comparator threshold setting for high voltage mode (supply connected to VDDH only). This setting does not apply for normal voltage mode (supply connected to both VDD and VDDH). */
#define POWER_POFCON_THRESHOLDVDDH_Pos  (8UL) /*!< Position of THRESHOLDVDDH field. */
#define POWER_POFCON_THRESHOLDVDDH_Msk                                                             \
  (0xFUL << POWER_POFCON_THRESHOLDVDDH_Pos)   /*!< Bit mask of THRESHOLDVDDH field. */
#define POWER_POFCON_THRESHOLDVDDH_V27 (0UL)  /*!< Set threshold to 2.7 V */
#define POWER_POFCON_THRESHOLDVDDH_V28 (1UL)  /*!< Set threshold to 2.8 V */
#define POWER_POFCON_THRESHOLDVDDH_V29 (2UL)  /*!< Set threshold to 2.9 V */
#define POWER_POFCON_THRESHOLDVDDH_V30 (3UL)  /*!< Set threshold to 3.0 V */
#define POWER_POFCON_THRESHOLDVDDH_V31 (4UL)  /*!< Set threshold to 3.1 V */
#define POWER_POFCON_THRESHOLDVDDH_V32 (5UL)  /*!< Set threshold to 3.2 V */
#define POWER_POFCON_THRESHOLDVDDH_V33 (6UL)  /*!< Set threshold to 3.3 V */
#define POWER_POFCON_THRESHOLDVDDH_V34 (7UL)  /*!< Set threshold to 3.4 V */
#define POWER_POFCON_THRESHOLDVDDH_V35 (8UL)  /*!< Set threshold to 3.5 V */
#define POWER_POFCON_THRESHOLDVDDH_V36 (9UL)  /*!< Set threshold to 3.6 V */
#define POWER_POFCON_THRESHOLDVDDH_V37 (10UL) /*!< Set threshold to 3.7 V */
#define POWER_POFCON_THRESHOLDVDDH_V38 (11UL) /*!< Set threshold to 3.8 V */
#define POWER_POFCON_THRESHOLDVDDH_V39 (12UL) /*!< Set threshold to 3.9 V */
#define POWER_POFCON_THRESHOLDVDDH_V40 (13UL) /*!< Set threshold to 4.0 V */
#define POWER_POFCON_THRESHOLDVDDH_V41 (14UL) /*!< Set threshold to 4.1 V */
#define POWER_POFCON_THRESHOLDVDDH_V42 (15UL) /*!< Set threshold to 4.2 V */

/* Bits 4..1 : Power-fail comparator threshold setting. This setting applies both for normal voltage mode (supply connected to both VDD and VDDH) and high voltage mode (supply connected to VDDH only). Values 0-3 set threshold below 1.7 V and should not be used as brown out detection will be activated before power failure warning on such low voltages. */
#define POWER_POFCON_THRESHOLD_Pos     (1UL) /*!< Position of THRESHOLD field. */
#define POWER_POFCON_THRESHOLD_Msk                                                                 \
  (0xFUL << POWER_POFCON_THRESHOLD_Pos)    /*!< Bit mask of THRESHOLD field. */
#define POWER_POFCON_THRESHOLD_V17  (4UL)  /*!< Set threshold to 1.7 V */
#define POWER_POFCON_THRESHOLD_V18  (5UL)  /*!< Set threshold to 1.8 V */
#define POWER_POFCON_THRESHOLD_V19  (6UL)  /*!< Set threshold to 1.9 V */
#define POWER_POFCON_THRESHOLD_V20  (7UL)  /*!< Set threshold to 2.0 V */
#define POWER_POFCON_THRESHOLD_V21  (8UL)  /*!< Set threshold to 2.1 V */
#define POWER_POFCON_THRESHOLD_V22  (9UL)  /*!< Set threshold to 2.2 V */
#define POWER_POFCON_THRESHOLD_V23  (10UL) /*!< Set threshold to 2.3 V */
#define POWER_POFCON_THRESHOLD_V24  (11UL) /*!< Set threshold to 2.4 V */
#define POWER_POFCON_THRESHOLD_V25  (12UL) /*!< Set threshold to 2.5 V */
#define POWER_POFCON_THRESHOLD_V26  (13UL) /*!< Set threshold to 2.6 V */
#define POWER_POFCON_THRESHOLD_V27  (14UL) /*!< Set threshold to 2.7 V */
#define POWER_POFCON_THRESHOLD_V28  (15UL) /*!< Set threshold to 2.8 V */

/* Bit 0 : Enable or disable power failure warning */
#define POWER_POFCON_POF_Pos        (0UL)                           /*!< Position of POF field. */
#define POWER_POFCON_POF_Msk        (0x1UL << POWER_POFCON_POF_Pos) /*!< Bit mask of POF field. */
#define POWER_POFCON_POF_Disabled   (0UL)                           /*!< Disable */
#define POWER_POFCON_POF_Enabled    (1UL)                           /*!< Enable */

/* Register: POWER_GPREGRET */
/* Description: General purpose retention register */

/* Bits 7..0 : General purpose retention register */
#define POWER_GPREGRET_GPREGRET_Pos (0UL) /*!< Position of GPREGRET field. */
#define POWER_GPREGRET_GPREGRET_Msk                                                                \
  (0xFFUL << POWER_GPREGRET_GPREGRET_Pos) /*!< Bit mask of GPREGRET field. */

/* Register: POWER_GPREGRET2 */
/* Description: General purpose retention register */

/* Bits 7..0 : General purpose retention register */
#define POWER_GPREGRET2_GPREGRET_Pos (0UL) /*!< Position of GPREGRET field. */
#define POWER_GPREGRET2_GPREGRET_Msk                                                               \
  (0xFFUL << POWER_GPREGRET2_GPREGRET_Pos) /*!< Bit mask of GPREGRET field. */

/* Register: POWER_DCDCEN */
/* Description: Enable DC/DC converter for REG1 stage */

/* Bit 0 : Enable DC/DC converter for REG1 stage. */
#define POWER_DCDCEN_DCDCEN_Pos               (0UL) /*!< Position of DCDCEN field. */
#define POWER_DCDCEN_DCDCEN_Msk               (0x1UL << POWER_DCDCEN_DCDCEN_Pos) /*!< Bit mask of DCDCEN field. */
#define POWER_DCDCEN_DCDCEN_Disabled          (0UL)                              /*!< Disable */
#define POWER_DCDCEN_DCDCEN_Enabled           (1UL)                              /*!< Enable */

/* Register: POWER_MAINREGSTATUS */
/* Description: Main supply status */

/* Bit 0 : Main supply status */
#define POWER_MAINREGSTATUS_MAINREGSTATUS_Pos (0UL) /*!< Position of MAINREGSTATUS field. */
#define POWER_MAINREGSTATUS_MAINREGSTATUS_Msk                                                      \
  (0x1UL << POWER_MAINREGSTATUS_MAINREGSTATUS_Pos) /*!< Bit mask of MAINREGSTATUS field. */
#define POWER_MAINREGSTATUS_MAINREGSTATUS_Normal                                                   \
  (0UL) /*!< Normal voltage mode. Voltage supplied on VDD. */
#define POWER_MAINREGSTATUS_MAINREGSTATUS_High                                                     \
  (1UL) /*!< High voltage mode. Voltage supplied on VDDH. */

/* Register: POWER_RAM_POWER */
/* Description: Description cluster: RAMn power control register */

/* Bit 17 : Keep retention on RAM section S1 when RAM section is off */
#define POWER_RAM_POWER_S1RETENTION_Pos (17UL) /*!< Position of S1RETENTION field. */
#define POWER_RAM_POWER_S1RETENTION_Msk                                                            \
  (0x1UL << POWER_RAM_POWER_S1RETENTION_Pos)  /*!< Bit mask of S1RETENTION field. */
#define POWER_RAM_POWER_S1RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S1RETENTION_On  (1UL) /*!< On */

/* Bit 16 : Keep retention on RAM section S0 when RAM section is off */
#define POWER_RAM_POWER_S0RETENTION_Pos (16UL) /*!< Position of S0RETENTION field. */
#define POWER_RAM_POWER_S0RETENTION_Msk                                                            \
  (0x1UL << POWER_RAM_POWER_S0RETENTION_Pos)  /*!< Bit mask of S0RETENTION field. */
#define POWER_RAM_POWER_S0RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S0RETENTION_On  (1UL) /*!< On */

/* Bit 1 : Keep RAM section S1 on or off in System ON mode. */
#define POWER_RAM_POWER_S1POWER_Pos     (1UL) /*!< Position of S1POWER field. */
#define POWER_RAM_POWER_S1POWER_Msk                                                                \
  (0x1UL << POWER_RAM_POWER_S1POWER_Pos)  /*!< Bit mask of S1POWER field. */
#define POWER_RAM_POWER_S1POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S1POWER_On  (1UL) /*!< On */

/* Bit 0 : Keep RAM section S0 on or off in System ON mode. */
#define POWER_RAM_POWER_S0POWER_Pos (0UL) /*!< Position of S0POWER field. */
#define POWER_RAM_POWER_S0POWER_Msk                                                                \
  (0x1UL << POWER_RAM_POWER_S0POWER_Pos)         /*!< Bit mask of S0POWER field. */
#define POWER_RAM_POWER_S0POWER_Off        (0UL) /*!< Off */
#define POWER_RAM_POWER_S0POWER_On         (1UL) /*!< On */

/* Register: POWER_RAM_POWERSET */
/* Description: Description cluster: RAMn power control set register */

/* Bit 17 : Keep retention on RAM section S1 when RAM section is switched off */
#define POWER_RAM_POWERSET_S1RETENTION_Pos (17UL) /*!< Position of S1RETENTION field. */
#define POWER_RAM_POWERSET_S1RETENTION_Msk                                                         \
  (0x1UL << POWER_RAM_POWERSET_S1RETENTION_Pos)  /*!< Bit mask of S1RETENTION field. */
#define POWER_RAM_POWERSET_S1RETENTION_On  (1UL) /*!< On */

/* Bit 16 : Keep retention on RAM section S0 when RAM section is switched off */
#define POWER_RAM_POWERSET_S0RETENTION_Pos (16UL) /*!< Position of S0RETENTION field. */
#define POWER_RAM_POWERSET_S0RETENTION_Msk                                                         \
  (0x1UL << POWER_RAM_POWERSET_S0RETENTION_Pos) /*!< Bit mask of S0RETENTION field. */
#define POWER_RAM_POWERSET_S0RETENTION_On (1UL) /*!< On */

/* Bit 1 : Keep RAM section S1 of RAMn on or off in System ON mode */
#define POWER_RAM_POWERSET_S1POWER_Pos    (1UL) /*!< Position of S1POWER field. */
#define POWER_RAM_POWERSET_S1POWER_Msk                                                             \
  (0x1UL << POWER_RAM_POWERSET_S1POWER_Pos)  /*!< Bit mask of S1POWER field. */
#define POWER_RAM_POWERSET_S1POWER_On  (1UL) /*!< On */

/* Bit 0 : Keep RAM section S0 of RAMn on or off in System ON mode */
#define POWER_RAM_POWERSET_S0POWER_Pos (0UL) /*!< Position of S0POWER field. */
#define POWER_RAM_POWERSET_S0POWER_Msk                                                             \
  (0x1UL << POWER_RAM_POWERSET_S0POWER_Pos)      /*!< Bit mask of S0POWER field. */
#define POWER_RAM_POWERSET_S0POWER_On      (1UL) /*!< On */

/* Register: POWER_RAM_POWERCLR */
/* Description: Description cluster: RAMn power control clear register */

/* Bit 17 : Keep retention on RAM section S1 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S1RETENTION_Pos (17UL) /*!< Position of S1RETENTION field. */
#define POWER_RAM_POWERCLR_S1RETENTION_Msk                                                         \
  (0x1UL << POWER_RAM_POWERCLR_S1RETENTION_Pos)  /*!< Bit mask of S1RETENTION field. */
#define POWER_RAM_POWERCLR_S1RETENTION_Off (1UL) /*!< Off */

/* Bit 16 : Keep retention on RAM section S0 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S0RETENTION_Pos (16UL) /*!< Position of S0RETENTION field. */
#define POWER_RAM_POWERCLR_S0RETENTION_Msk                                                         \
  (0x1UL << POWER_RAM_POWERCLR_S0RETENTION_Pos)  /*!< Bit mask of S0RETENTION field. */
#define POWER_RAM_POWERCLR_S0RETENTION_Off (1UL) /*!< Off */

/* Bit 1 : Keep RAM section S1 of RAMn on or off in System ON mode */
#define POWER_RAM_POWERCLR_S1POWER_Pos     (1UL) /*!< Position of S1POWER field. */
#define POWER_RAM_POWERCLR_S1POWER_Msk                                                             \
  (0x1UL << POWER_RAM_POWERCLR_S1POWER_Pos)  /*!< Bit mask of S1POWER field. */
#define POWER_RAM_POWERCLR_S1POWER_Off (1UL) /*!< Off */

/* Bit 0 : Keep RAM section S0 of RAMn on or off in System ON mode */
#define POWER_RAM_POWERCLR_S0POWER_Pos (0UL) /*!< Position of S0POWER field. */
#define POWER_RAM_POWERCLR_S0POWER_Msk                                                             \
  (0x1UL << POWER_RAM_POWERCLR_S0POWER_Pos)  /*!< Bit mask of S0POWER field. */
#define POWER_RAM_POWERCLR_S0POWER_Off (1UL) /*!< Off */


/* Peripheral: PPI */
/* Description: Programmable Peripheral Interconnect */

/* Register: PPI_TASKS_CHG_EN */
/* Description: Description cluster: Enable channel group n */

/* Bit 0 : Enable channel group n */
#define PPI_TASKS_CHG_EN_EN_Pos        (0UL) /*!< Position of EN field. */
#define PPI_TASKS_CHG_EN_EN_Msk        (0x1UL << PPI_TASKS_CHG_EN_EN_Pos) /*!< Bit mask of EN field. */
#define PPI_TASKS_CHG_EN_EN_Trigger    (1UL)                              /*!< Trigger task */

/* Register: PPI_TASKS_CHG_DIS */
/* Description: Description cluster: Disable channel group n */

/* Bit 0 : Disable channel group n */
#define PPI_TASKS_CHG_DIS_DIS_Pos      (0UL) /*!< Position of DIS field. */
#define PPI_TASKS_CHG_DIS_DIS_Msk                                                                  \
  (0x1UL << PPI_TASKS_CHG_DIS_DIS_Pos)         /*!< Bit mask of DIS field. */
#define PPI_TASKS_CHG_DIS_DIS_Trigger    (1UL) /*!< Trigger task */

/* Register: PPI_CHEN */
/* Description: Channel enable register */

/* Bit 31 : Enable or disable channel 31 */
#define PPI_CHEN_CH31_Pos                (31UL) /*!< Position of CH31 field. */
#define PPI_CHEN_CH31_Msk                (0x1UL << PPI_CHEN_CH31_Pos) /*!< Bit mask of CH31 field. */
#define PPI_CHEN_CH31_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH31_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 30 : Enable or disable channel 30 */
#define PPI_CHEN_CH30_Pos                (30UL) /*!< Position of CH30 field. */
#define PPI_CHEN_CH30_Msk                (0x1UL << PPI_CHEN_CH30_Pos) /*!< Bit mask of CH30 field. */
#define PPI_CHEN_CH30_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH30_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 29 : Enable or disable channel 29 */
#define PPI_CHEN_CH29_Pos                (29UL) /*!< Position of CH29 field. */
#define PPI_CHEN_CH29_Msk                (0x1UL << PPI_CHEN_CH29_Pos) /*!< Bit mask of CH29 field. */
#define PPI_CHEN_CH29_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH29_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 28 : Enable or disable channel 28 */
#define PPI_CHEN_CH28_Pos                (28UL) /*!< Position of CH28 field. */
#define PPI_CHEN_CH28_Msk                (0x1UL << PPI_CHEN_CH28_Pos) /*!< Bit mask of CH28 field. */
#define PPI_CHEN_CH28_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH28_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 27 : Enable or disable channel 27 */
#define PPI_CHEN_CH27_Pos                (27UL) /*!< Position of CH27 field. */
#define PPI_CHEN_CH27_Msk                (0x1UL << PPI_CHEN_CH27_Pos) /*!< Bit mask of CH27 field. */
#define PPI_CHEN_CH27_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH27_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 26 : Enable or disable channel 26 */
#define PPI_CHEN_CH26_Pos                (26UL) /*!< Position of CH26 field. */
#define PPI_CHEN_CH26_Msk                (0x1UL << PPI_CHEN_CH26_Pos) /*!< Bit mask of CH26 field. */
#define PPI_CHEN_CH26_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH26_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 25 : Enable or disable channel 25 */
#define PPI_CHEN_CH25_Pos                (25UL) /*!< Position of CH25 field. */
#define PPI_CHEN_CH25_Msk                (0x1UL << PPI_CHEN_CH25_Pos) /*!< Bit mask of CH25 field. */
#define PPI_CHEN_CH25_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH25_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 24 : Enable or disable channel 24 */
#define PPI_CHEN_CH24_Pos                (24UL) /*!< Position of CH24 field. */
#define PPI_CHEN_CH24_Msk                (0x1UL << PPI_CHEN_CH24_Pos) /*!< Bit mask of CH24 field. */
#define PPI_CHEN_CH24_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH24_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 23 : Enable or disable channel 23 */
#define PPI_CHEN_CH23_Pos                (23UL) /*!< Position of CH23 field. */
#define PPI_CHEN_CH23_Msk                (0x1UL << PPI_CHEN_CH23_Pos) /*!< Bit mask of CH23 field. */
#define PPI_CHEN_CH23_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH23_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 22 : Enable or disable channel 22 */
#define PPI_CHEN_CH22_Pos                (22UL) /*!< Position of CH22 field. */
#define PPI_CHEN_CH22_Msk                (0x1UL << PPI_CHEN_CH22_Pos) /*!< Bit mask of CH22 field. */
#define PPI_CHEN_CH22_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH22_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 21 : Enable or disable channel 21 */
#define PPI_CHEN_CH21_Pos                (21UL) /*!< Position of CH21 field. */
#define PPI_CHEN_CH21_Msk                (0x1UL << PPI_CHEN_CH21_Pos) /*!< Bit mask of CH21 field. */
#define PPI_CHEN_CH21_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH21_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 20 : Enable or disable channel 20 */
#define PPI_CHEN_CH20_Pos                (20UL) /*!< Position of CH20 field. */
#define PPI_CHEN_CH20_Msk                (0x1UL << PPI_CHEN_CH20_Pos) /*!< Bit mask of CH20 field. */
#define PPI_CHEN_CH20_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH20_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 19 : Enable or disable channel 19 */
#define PPI_CHEN_CH19_Pos                (19UL) /*!< Position of CH19 field. */
#define PPI_CHEN_CH19_Msk                (0x1UL << PPI_CHEN_CH19_Pos) /*!< Bit mask of CH19 field. */
#define PPI_CHEN_CH19_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH19_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 18 : Enable or disable channel 18 */
#define PPI_CHEN_CH18_Pos                (18UL) /*!< Position of CH18 field. */
#define PPI_CHEN_CH18_Msk                (0x1UL << PPI_CHEN_CH18_Pos) /*!< Bit mask of CH18 field. */
#define PPI_CHEN_CH18_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH18_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 17 : Enable or disable channel 17 */
#define PPI_CHEN_CH17_Pos                (17UL) /*!< Position of CH17 field. */
#define PPI_CHEN_CH17_Msk                (0x1UL << PPI_CHEN_CH17_Pos) /*!< Bit mask of CH17 field. */
#define PPI_CHEN_CH17_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH17_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 16 : Enable or disable channel 16 */
#define PPI_CHEN_CH16_Pos                (16UL) /*!< Position of CH16 field. */
#define PPI_CHEN_CH16_Msk                (0x1UL << PPI_CHEN_CH16_Pos) /*!< Bit mask of CH16 field. */
#define PPI_CHEN_CH16_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH16_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 15 : Enable or disable channel 15 */
#define PPI_CHEN_CH15_Pos                (15UL) /*!< Position of CH15 field. */
#define PPI_CHEN_CH15_Msk                (0x1UL << PPI_CHEN_CH15_Pos) /*!< Bit mask of CH15 field. */
#define PPI_CHEN_CH15_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH15_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 14 : Enable or disable channel 14 */
#define PPI_CHEN_CH14_Pos                (14UL) /*!< Position of CH14 field. */
#define PPI_CHEN_CH14_Msk                (0x1UL << PPI_CHEN_CH14_Pos) /*!< Bit mask of CH14 field. */
#define PPI_CHEN_CH14_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH14_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 13 : Enable or disable channel 13 */
#define PPI_CHEN_CH13_Pos                (13UL) /*!< Position of CH13 field. */
#define PPI_CHEN_CH13_Msk                (0x1UL << PPI_CHEN_CH13_Pos) /*!< Bit mask of CH13 field. */
#define PPI_CHEN_CH13_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH13_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 12 : Enable or disable channel 12 */
#define PPI_CHEN_CH12_Pos                (12UL) /*!< Position of CH12 field. */
#define PPI_CHEN_CH12_Msk                (0x1UL << PPI_CHEN_CH12_Pos) /*!< Bit mask of CH12 field. */
#define PPI_CHEN_CH12_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH12_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 11 : Enable or disable channel 11 */
#define PPI_CHEN_CH11_Pos                (11UL) /*!< Position of CH11 field. */
#define PPI_CHEN_CH11_Msk                (0x1UL << PPI_CHEN_CH11_Pos) /*!< Bit mask of CH11 field. */
#define PPI_CHEN_CH11_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH11_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 10 : Enable or disable channel 10 */
#define PPI_CHEN_CH10_Pos                (10UL) /*!< Position of CH10 field. */
#define PPI_CHEN_CH10_Msk                (0x1UL << PPI_CHEN_CH10_Pos) /*!< Bit mask of CH10 field. */
#define PPI_CHEN_CH10_Disabled           (0UL)                        /*!< Disable channel */
#define PPI_CHEN_CH10_Enabled            (1UL)                        /*!< Enable channel */

/* Bit 9 : Enable or disable channel 9 */
#define PPI_CHEN_CH9_Pos                 (9UL)                       /*!< Position of CH9 field. */
#define PPI_CHEN_CH9_Msk                 (0x1UL << PPI_CHEN_CH9_Pos) /*!< Bit mask of CH9 field. */
#define PPI_CHEN_CH9_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH9_Enabled             (1UL)                       /*!< Enable channel */

/* Bit 8 : Enable or disable channel 8 */
#define PPI_CHEN_CH8_Pos                 (8UL)                       /*!< Position of CH8 field. */
#define PPI_CHEN_CH8_Msk                 (0x1UL << PPI_CHEN_CH8_Pos) /*!< Bit mask of CH8 field. */
#define PPI_CHEN_CH8_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH8_Enabled             (1UL)                       /*!< Enable channel */

/* Bit 7 : Enable or disable channel 7 */
#define PPI_CHEN_CH7_Pos                 (7UL)                       /*!< Position of CH7 field. */
#define PPI_CHEN_CH7_Msk                 (0x1UL << PPI_CHEN_CH7_Pos) /*!< Bit mask of CH7 field. */
#define PPI_CHEN_CH7_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH7_Enabled             (1UL)                       /*!< Enable channel */

/* Bit 6 : Enable or disable channel 6 */
#define PPI_CHEN_CH6_Pos                 (6UL)                       /*!< Position of CH6 field. */
#define PPI_CHEN_CH6_Msk                 (0x1UL << PPI_CHEN_CH6_Pos) /*!< Bit mask of CH6 field. */
#define PPI_CHEN_CH6_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH6_Enabled             (1UL)                       /*!< Enable channel */

/* Bit 5 : Enable or disable channel 5 */
#define PPI_CHEN_CH5_Pos                 (5UL)                       /*!< Position of CH5 field. */
#define PPI_CHEN_CH5_Msk                 (0x1UL << PPI_CHEN_CH5_Pos) /*!< Bit mask of CH5 field. */
#define PPI_CHEN_CH5_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH5_Enabled             (1UL)                       /*!< Enable channel */

/* Bit 4 : Enable or disable channel 4 */
#define PPI_CHEN_CH4_Pos                 (4UL)                       /*!< Position of CH4 field. */
#define PPI_CHEN_CH4_Msk                 (0x1UL << PPI_CHEN_CH4_Pos) /*!< Bit mask of CH4 field. */
#define PPI_CHEN_CH4_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH4_Enabled             (1UL)                       /*!< Enable channel */

/* Bit 3 : Enable or disable channel 3 */
#define PPI_CHEN_CH3_Pos                 (3UL)                       /*!< Position of CH3 field. */
#define PPI_CHEN_CH3_Msk                 (0x1UL << PPI_CHEN_CH3_Pos) /*!< Bit mask of CH3 field. */
#define PPI_CHEN_CH3_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH3_Enabled             (1UL)                       /*!< Enable channel */

/* Bit 2 : Enable or disable channel 2 */
#define PPI_CHEN_CH2_Pos                 (2UL)                       /*!< Position of CH2 field. */
#define PPI_CHEN_CH2_Msk                 (0x1UL << PPI_CHEN_CH2_Pos) /*!< Bit mask of CH2 field. */
#define PPI_CHEN_CH2_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH2_Enabled             (1UL)                       /*!< Enable channel */

/* Bit 1 : Enable or disable channel 1 */
#define PPI_CHEN_CH1_Pos                 (1UL)                       /*!< Position of CH1 field. */
#define PPI_CHEN_CH1_Msk                 (0x1UL << PPI_CHEN_CH1_Pos) /*!< Bit mask of CH1 field. */
#define PPI_CHEN_CH1_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH1_Enabled             (1UL)                       /*!< Enable channel */

/* Bit 0 : Enable or disable channel 0 */
#define PPI_CHEN_CH0_Pos                 (0UL)                       /*!< Position of CH0 field. */
#define PPI_CHEN_CH0_Msk                 (0x1UL << PPI_CHEN_CH0_Pos) /*!< Bit mask of CH0 field. */
#define PPI_CHEN_CH0_Disabled            (0UL)                       /*!< Disable channel */
#define PPI_CHEN_CH0_Enabled             (1UL)                       /*!< Enable channel */

/* Register: PPI_CHENSET */
/* Description: Channel enable set register */

/* Bit 31 : Channel 31 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH31_Pos             (31UL) /*!< Position of CH31 field. */
#define PPI_CHENSET_CH31_Msk             (0x1UL << PPI_CHENSET_CH31_Pos) /*!< Bit mask of CH31 field. */
#define PPI_CHENSET_CH31_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH31_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH31_Set             (1UL) /*!< Write: Enable channel */

/* Bit 30 : Channel 30 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH30_Pos             (30UL) /*!< Position of CH30 field. */
#define PPI_CHENSET_CH30_Msk             (0x1UL << PPI_CHENSET_CH30_Pos) /*!< Bit mask of CH30 field. */
#define PPI_CHENSET_CH30_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH30_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH30_Set             (1UL) /*!< Write: Enable channel */

/* Bit 29 : Channel 29 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH29_Pos             (29UL) /*!< Position of CH29 field. */
#define PPI_CHENSET_CH29_Msk             (0x1UL << PPI_CHENSET_CH29_Pos) /*!< Bit mask of CH29 field. */
#define PPI_CHENSET_CH29_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH29_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH29_Set             (1UL) /*!< Write: Enable channel */

/* Bit 28 : Channel 28 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH28_Pos             (28UL) /*!< Position of CH28 field. */
#define PPI_CHENSET_CH28_Msk             (0x1UL << PPI_CHENSET_CH28_Pos) /*!< Bit mask of CH28 field. */
#define PPI_CHENSET_CH28_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH28_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH28_Set             (1UL) /*!< Write: Enable channel */

/* Bit 27 : Channel 27 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH27_Pos             (27UL) /*!< Position of CH27 field. */
#define PPI_CHENSET_CH27_Msk             (0x1UL << PPI_CHENSET_CH27_Pos) /*!< Bit mask of CH27 field. */
#define PPI_CHENSET_CH27_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH27_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH27_Set             (1UL) /*!< Write: Enable channel */

/* Bit 26 : Channel 26 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH26_Pos             (26UL) /*!< Position of CH26 field. */
#define PPI_CHENSET_CH26_Msk             (0x1UL << PPI_CHENSET_CH26_Pos) /*!< Bit mask of CH26 field. */
#define PPI_CHENSET_CH26_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH26_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH26_Set             (1UL) /*!< Write: Enable channel */

/* Bit 25 : Channel 25 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH25_Pos             (25UL) /*!< Position of CH25 field. */
#define PPI_CHENSET_CH25_Msk             (0x1UL << PPI_CHENSET_CH25_Pos) /*!< Bit mask of CH25 field. */
#define PPI_CHENSET_CH25_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH25_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH25_Set             (1UL) /*!< Write: Enable channel */

/* Bit 24 : Channel 24 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH24_Pos             (24UL) /*!< Position of CH24 field. */
#define PPI_CHENSET_CH24_Msk             (0x1UL << PPI_CHENSET_CH24_Pos) /*!< Bit mask of CH24 field. */
#define PPI_CHENSET_CH24_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH24_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH24_Set             (1UL) /*!< Write: Enable channel */

/* Bit 23 : Channel 23 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH23_Pos             (23UL) /*!< Position of CH23 field. */
#define PPI_CHENSET_CH23_Msk             (0x1UL << PPI_CHENSET_CH23_Pos) /*!< Bit mask of CH23 field. */
#define PPI_CHENSET_CH23_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH23_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH23_Set             (1UL) /*!< Write: Enable channel */

/* Bit 22 : Channel 22 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH22_Pos             (22UL) /*!< Position of CH22 field. */
#define PPI_CHENSET_CH22_Msk             (0x1UL << PPI_CHENSET_CH22_Pos) /*!< Bit mask of CH22 field. */
#define PPI_CHENSET_CH22_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH22_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH22_Set             (1UL) /*!< Write: Enable channel */

/* Bit 21 : Channel 21 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH21_Pos             (21UL) /*!< Position of CH21 field. */
#define PPI_CHENSET_CH21_Msk             (0x1UL << PPI_CHENSET_CH21_Pos) /*!< Bit mask of CH21 field. */
#define PPI_CHENSET_CH21_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH21_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH21_Set             (1UL) /*!< Write: Enable channel */

/* Bit 20 : Channel 20 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH20_Pos             (20UL) /*!< Position of CH20 field. */
#define PPI_CHENSET_CH20_Msk             (0x1UL << PPI_CHENSET_CH20_Pos) /*!< Bit mask of CH20 field. */
#define PPI_CHENSET_CH20_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH20_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH20_Set             (1UL) /*!< Write: Enable channel */

/* Bit 19 : Channel 19 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH19_Pos             (19UL) /*!< Position of CH19 field. */
#define PPI_CHENSET_CH19_Msk             (0x1UL << PPI_CHENSET_CH19_Pos) /*!< Bit mask of CH19 field. */
#define PPI_CHENSET_CH19_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH19_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH19_Set             (1UL) /*!< Write: Enable channel */

/* Bit 18 : Channel 18 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH18_Pos             (18UL) /*!< Position of CH18 field. */
#define PPI_CHENSET_CH18_Msk             (0x1UL << PPI_CHENSET_CH18_Pos) /*!< Bit mask of CH18 field. */
#define PPI_CHENSET_CH18_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH18_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH18_Set             (1UL) /*!< Write: Enable channel */

/* Bit 17 : Channel 17 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH17_Pos             (17UL) /*!< Position of CH17 field. */
#define PPI_CHENSET_CH17_Msk             (0x1UL << PPI_CHENSET_CH17_Pos) /*!< Bit mask of CH17 field. */
#define PPI_CHENSET_CH17_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH17_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH17_Set             (1UL) /*!< Write: Enable channel */

/* Bit 16 : Channel 16 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH16_Pos             (16UL) /*!< Position of CH16 field. */
#define PPI_CHENSET_CH16_Msk             (0x1UL << PPI_CHENSET_CH16_Pos) /*!< Bit mask of CH16 field. */
#define PPI_CHENSET_CH16_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH16_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH16_Set             (1UL) /*!< Write: Enable channel */

/* Bit 15 : Channel 15 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH15_Pos             (15UL) /*!< Position of CH15 field. */
#define PPI_CHENSET_CH15_Msk             (0x1UL << PPI_CHENSET_CH15_Pos) /*!< Bit mask of CH15 field. */
#define PPI_CHENSET_CH15_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH15_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH15_Set             (1UL) /*!< Write: Enable channel */

/* Bit 14 : Channel 14 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH14_Pos             (14UL) /*!< Position of CH14 field. */
#define PPI_CHENSET_CH14_Msk             (0x1UL << PPI_CHENSET_CH14_Pos) /*!< Bit mask of CH14 field. */
#define PPI_CHENSET_CH14_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH14_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH14_Set             (1UL) /*!< Write: Enable channel */

/* Bit 13 : Channel 13 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH13_Pos             (13UL) /*!< Position of CH13 field. */
#define PPI_CHENSET_CH13_Msk             (0x1UL << PPI_CHENSET_CH13_Pos) /*!< Bit mask of CH13 field. */
#define PPI_CHENSET_CH13_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH13_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH13_Set             (1UL) /*!< Write: Enable channel */

/* Bit 12 : Channel 12 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH12_Pos             (12UL) /*!< Position of CH12 field. */
#define PPI_CHENSET_CH12_Msk             (0x1UL << PPI_CHENSET_CH12_Pos) /*!< Bit mask of CH12 field. */
#define PPI_CHENSET_CH12_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH12_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH12_Set             (1UL) /*!< Write: Enable channel */

/* Bit 11 : Channel 11 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH11_Pos             (11UL) /*!< Position of CH11 field. */
#define PPI_CHENSET_CH11_Msk             (0x1UL << PPI_CHENSET_CH11_Pos) /*!< Bit mask of CH11 field. */
#define PPI_CHENSET_CH11_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH11_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH11_Set             (1UL) /*!< Write: Enable channel */

/* Bit 10 : Channel 10 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH10_Pos             (10UL) /*!< Position of CH10 field. */
#define PPI_CHENSET_CH10_Msk             (0x1UL << PPI_CHENSET_CH10_Pos) /*!< Bit mask of CH10 field. */
#define PPI_CHENSET_CH10_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH10_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH10_Set             (1UL) /*!< Write: Enable channel */

/* Bit 9 : Channel 9 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH9_Pos              (9UL) /*!< Position of CH9 field. */
#define PPI_CHENSET_CH9_Msk              (0x1UL << PPI_CHENSET_CH9_Pos) /*!< Bit mask of CH9 field. */
#define PPI_CHENSET_CH9_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH9_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH9_Set              (1UL) /*!< Write: Enable channel */

/* Bit 8 : Channel 8 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH8_Pos              (8UL) /*!< Position of CH8 field. */
#define PPI_CHENSET_CH8_Msk              (0x1UL << PPI_CHENSET_CH8_Pos) /*!< Bit mask of CH8 field. */
#define PPI_CHENSET_CH8_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH8_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH8_Set              (1UL) /*!< Write: Enable channel */

/* Bit 7 : Channel 7 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH7_Pos              (7UL) /*!< Position of CH7 field. */
#define PPI_CHENSET_CH7_Msk              (0x1UL << PPI_CHENSET_CH7_Pos) /*!< Bit mask of CH7 field. */
#define PPI_CHENSET_CH7_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH7_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH7_Set              (1UL) /*!< Write: Enable channel */

/* Bit 6 : Channel 6 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH6_Pos              (6UL) /*!< Position of CH6 field. */
#define PPI_CHENSET_CH6_Msk              (0x1UL << PPI_CHENSET_CH6_Pos) /*!< Bit mask of CH6 field. */
#define PPI_CHENSET_CH6_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH6_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH6_Set              (1UL) /*!< Write: Enable channel */

/* Bit 5 : Channel 5 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH5_Pos              (5UL) /*!< Position of CH5 field. */
#define PPI_CHENSET_CH5_Msk              (0x1UL << PPI_CHENSET_CH5_Pos) /*!< Bit mask of CH5 field. */
#define PPI_CHENSET_CH5_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH5_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH5_Set              (1UL) /*!< Write: Enable channel */

/* Bit 4 : Channel 4 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH4_Pos              (4UL) /*!< Position of CH4 field. */
#define PPI_CHENSET_CH4_Msk              (0x1UL << PPI_CHENSET_CH4_Pos) /*!< Bit mask of CH4 field. */
#define PPI_CHENSET_CH4_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH4_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH4_Set              (1UL) /*!< Write: Enable channel */

/* Bit 3 : Channel 3 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH3_Pos              (3UL) /*!< Position of CH3 field. */
#define PPI_CHENSET_CH3_Msk              (0x1UL << PPI_CHENSET_CH3_Pos) /*!< Bit mask of CH3 field. */
#define PPI_CHENSET_CH3_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH3_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH3_Set              (1UL) /*!< Write: Enable channel */

/* Bit 2 : Channel 2 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH2_Pos              (2UL) /*!< Position of CH2 field. */
#define PPI_CHENSET_CH2_Msk              (0x1UL << PPI_CHENSET_CH2_Pos) /*!< Bit mask of CH2 field. */
#define PPI_CHENSET_CH2_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH2_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH2_Set              (1UL) /*!< Write: Enable channel */

/* Bit 1 : Channel 1 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH1_Pos              (1UL) /*!< Position of CH1 field. */
#define PPI_CHENSET_CH1_Msk              (0x1UL << PPI_CHENSET_CH1_Pos) /*!< Bit mask of CH1 field. */
#define PPI_CHENSET_CH1_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH1_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH1_Set              (1UL) /*!< Write: Enable channel */

/* Bit 0 : Channel 0 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH0_Pos              (0UL) /*!< Position of CH0 field. */
#define PPI_CHENSET_CH0_Msk              (0x1UL << PPI_CHENSET_CH0_Pos) /*!< Bit mask of CH0 field. */
#define PPI_CHENSET_CH0_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH0_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH0_Set              (1UL) /*!< Write: Enable channel */

/* Register: PPI_CHENCLR */
/* Description: Channel enable clear register */

/* Bit 31 : Channel 31 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH31_Pos             (31UL) /*!< Position of CH31 field. */
#define PPI_CHENCLR_CH31_Msk             (0x1UL << PPI_CHENCLR_CH31_Pos) /*!< Bit mask of CH31 field. */
#define PPI_CHENCLR_CH31_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH31_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH31_Clear           (1UL) /*!< Write: disable channel */

/* Bit 30 : Channel 30 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH30_Pos             (30UL) /*!< Position of CH30 field. */
#define PPI_CHENCLR_CH30_Msk             (0x1UL << PPI_CHENCLR_CH30_Pos) /*!< Bit mask of CH30 field. */
#define PPI_CHENCLR_CH30_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH30_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH30_Clear           (1UL) /*!< Write: disable channel */

/* Bit 29 : Channel 29 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH29_Pos             (29UL) /*!< Position of CH29 field. */
#define PPI_CHENCLR_CH29_Msk             (0x1UL << PPI_CHENCLR_CH29_Pos) /*!< Bit mask of CH29 field. */
#define PPI_CHENCLR_CH29_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH29_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH29_Clear           (1UL) /*!< Write: disable channel */

/* Bit 28 : Channel 28 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH28_Pos             (28UL) /*!< Position of CH28 field. */
#define PPI_CHENCLR_CH28_Msk             (0x1UL << PPI_CHENCLR_CH28_Pos) /*!< Bit mask of CH28 field. */
#define PPI_CHENCLR_CH28_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH28_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH28_Clear           (1UL) /*!< Write: disable channel */

/* Bit 27 : Channel 27 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH27_Pos             (27UL) /*!< Position of CH27 field. */
#define PPI_CHENCLR_CH27_Msk             (0x1UL << PPI_CHENCLR_CH27_Pos) /*!< Bit mask of CH27 field. */
#define PPI_CHENCLR_CH27_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH27_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH27_Clear           (1UL) /*!< Write: disable channel */

/* Bit 26 : Channel 26 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH26_Pos             (26UL) /*!< Position of CH26 field. */
#define PPI_CHENCLR_CH26_Msk             (0x1UL << PPI_CHENCLR_CH26_Pos) /*!< Bit mask of CH26 field. */
#define PPI_CHENCLR_CH26_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH26_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH26_Clear           (1UL) /*!< Write: disable channel */

/* Bit 25 : Channel 25 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH25_Pos             (25UL) /*!< Position of CH25 field. */
#define PPI_CHENCLR_CH25_Msk             (0x1UL << PPI_CHENCLR_CH25_Pos) /*!< Bit mask of CH25 field. */
#define PPI_CHENCLR_CH25_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH25_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH25_Clear           (1UL) /*!< Write: disable channel */

/* Bit 24 : Channel 24 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH24_Pos             (24UL) /*!< Position of CH24 field. */
#define PPI_CHENCLR_CH24_Msk             (0x1UL << PPI_CHENCLR_CH24_Pos) /*!< Bit mask of CH24 field. */
#define PPI_CHENCLR_CH24_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH24_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH24_Clear           (1UL) /*!< Write: disable channel */

/* Bit 23 : Channel 23 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH23_Pos             (23UL) /*!< Position of CH23 field. */
#define PPI_CHENCLR_CH23_Msk             (0x1UL << PPI_CHENCLR_CH23_Pos) /*!< Bit mask of CH23 field. */
#define PPI_CHENCLR_CH23_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH23_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH23_Clear           (1UL) /*!< Write: disable channel */

/* Bit 22 : Channel 22 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH22_Pos             (22UL) /*!< Position of CH22 field. */
#define PPI_CHENCLR_CH22_Msk             (0x1UL << PPI_CHENCLR_CH22_Pos) /*!< Bit mask of CH22 field. */
#define PPI_CHENCLR_CH22_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH22_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH22_Clear           (1UL) /*!< Write: disable channel */

/* Bit 21 : Channel 21 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH21_Pos             (21UL) /*!< Position of CH21 field. */
#define PPI_CHENCLR_CH21_Msk             (0x1UL << PPI_CHENCLR_CH21_Pos) /*!< Bit mask of CH21 field. */
#define PPI_CHENCLR_CH21_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH21_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH21_Clear           (1UL) /*!< Write: disable channel */

/* Bit 20 : Channel 20 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH20_Pos             (20UL) /*!< Position of CH20 field. */
#define PPI_CHENCLR_CH20_Msk             (0x1UL << PPI_CHENCLR_CH20_Pos) /*!< Bit mask of CH20 field. */
#define PPI_CHENCLR_CH20_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH20_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH20_Clear           (1UL) /*!< Write: disable channel */

/* Bit 19 : Channel 19 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH19_Pos             (19UL) /*!< Position of CH19 field. */
#define PPI_CHENCLR_CH19_Msk             (0x1UL << PPI_CHENCLR_CH19_Pos) /*!< Bit mask of CH19 field. */
#define PPI_CHENCLR_CH19_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH19_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH19_Clear           (1UL) /*!< Write: disable channel */

/* Bit 18 : Channel 18 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH18_Pos             (18UL) /*!< Position of CH18 field. */
#define PPI_CHENCLR_CH18_Msk             (0x1UL << PPI_CHENCLR_CH18_Pos) /*!< Bit mask of CH18 field. */
#define PPI_CHENCLR_CH18_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH18_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH18_Clear           (1UL) /*!< Write: disable channel */

/* Bit 17 : Channel 17 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH17_Pos             (17UL) /*!< Position of CH17 field. */
#define PPI_CHENCLR_CH17_Msk             (0x1UL << PPI_CHENCLR_CH17_Pos) /*!< Bit mask of CH17 field. */
#define PPI_CHENCLR_CH17_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH17_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH17_Clear           (1UL) /*!< Write: disable channel */

/* Bit 16 : Channel 16 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH16_Pos             (16UL) /*!< Position of CH16 field. */
#define PPI_CHENCLR_CH16_Msk             (0x1UL << PPI_CHENCLR_CH16_Pos) /*!< Bit mask of CH16 field. */
#define PPI_CHENCLR_CH16_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH16_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH16_Clear           (1UL) /*!< Write: disable channel */

/* Bit 15 : Channel 15 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH15_Pos             (15UL) /*!< Position of CH15 field. */
#define PPI_CHENCLR_CH15_Msk             (0x1UL << PPI_CHENCLR_CH15_Pos) /*!< Bit mask of CH15 field. */
#define PPI_CHENCLR_CH15_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH15_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH15_Clear           (1UL) /*!< Write: disable channel */

/* Bit 14 : Channel 14 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH14_Pos             (14UL) /*!< Position of CH14 field. */
#define PPI_CHENCLR_CH14_Msk             (0x1UL << PPI_CHENCLR_CH14_Pos) /*!< Bit mask of CH14 field. */
#define PPI_CHENCLR_CH14_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH14_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH14_Clear           (1UL) /*!< Write: disable channel */

/* Bit 13 : Channel 13 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH13_Pos             (13UL) /*!< Position of CH13 field. */
#define PPI_CHENCLR_CH13_Msk             (0x1UL << PPI_CHENCLR_CH13_Pos) /*!< Bit mask of CH13 field. */
#define PPI_CHENCLR_CH13_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH13_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH13_Clear           (1UL) /*!< Write: disable channel */

/* Bit 12 : Channel 12 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH12_Pos             (12UL) /*!< Position of CH12 field. */
#define PPI_CHENCLR_CH12_Msk             (0x1UL << PPI_CHENCLR_CH12_Pos) /*!< Bit mask of CH12 field. */
#define PPI_CHENCLR_CH12_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH12_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH12_Clear           (1UL) /*!< Write: disable channel */

/* Bit 11 : Channel 11 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH11_Pos             (11UL) /*!< Position of CH11 field. */
#define PPI_CHENCLR_CH11_Msk             (0x1UL << PPI_CHENCLR_CH11_Pos) /*!< Bit mask of CH11 field. */
#define PPI_CHENCLR_CH11_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH11_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH11_Clear           (1UL) /*!< Write: disable channel */

/* Bit 10 : Channel 10 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH10_Pos             (10UL) /*!< Position of CH10 field. */
#define PPI_CHENCLR_CH10_Msk             (0x1UL << PPI_CHENCLR_CH10_Pos) /*!< Bit mask of CH10 field. */
#define PPI_CHENCLR_CH10_Disabled        (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH10_Enabled         (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH10_Clear           (1UL) /*!< Write: disable channel */

/* Bit 9 : Channel 9 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH9_Pos              (9UL) /*!< Position of CH9 field. */
#define PPI_CHENCLR_CH9_Msk              (0x1UL << PPI_CHENCLR_CH9_Pos) /*!< Bit mask of CH9 field. */
#define PPI_CHENCLR_CH9_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH9_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH9_Clear            (1UL) /*!< Write: disable channel */

/* Bit 8 : Channel 8 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH8_Pos              (8UL) /*!< Position of CH8 field. */
#define PPI_CHENCLR_CH8_Msk              (0x1UL << PPI_CHENCLR_CH8_Pos) /*!< Bit mask of CH8 field. */
#define PPI_CHENCLR_CH8_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH8_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH8_Clear            (1UL) /*!< Write: disable channel */

/* Bit 7 : Channel 7 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH7_Pos              (7UL) /*!< Position of CH7 field. */
#define PPI_CHENCLR_CH7_Msk              (0x1UL << PPI_CHENCLR_CH7_Pos) /*!< Bit mask of CH7 field. */
#define PPI_CHENCLR_CH7_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH7_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH7_Clear            (1UL) /*!< Write: disable channel */

/* Bit 6 : Channel 6 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH6_Pos              (6UL) /*!< Position of CH6 field. */
#define PPI_CHENCLR_CH6_Msk              (0x1UL << PPI_CHENCLR_CH6_Pos) /*!< Bit mask of CH6 field. */
#define PPI_CHENCLR_CH6_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH6_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH6_Clear            (1UL) /*!< Write: disable channel */

/* Bit 5 : Channel 5 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH5_Pos              (5UL) /*!< Position of CH5 field. */
#define PPI_CHENCLR_CH5_Msk              (0x1UL << PPI_CHENCLR_CH5_Pos) /*!< Bit mask of CH5 field. */
#define PPI_CHENCLR_CH5_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH5_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH5_Clear            (1UL) /*!< Write: disable channel */

/* Bit 4 : Channel 4 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH4_Pos              (4UL) /*!< Position of CH4 field. */
#define PPI_CHENCLR_CH4_Msk              (0x1UL << PPI_CHENCLR_CH4_Pos) /*!< Bit mask of CH4 field. */
#define PPI_CHENCLR_CH4_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH4_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH4_Clear            (1UL) /*!< Write: disable channel */

/* Bit 3 : Channel 3 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH3_Pos              (3UL) /*!< Position of CH3 field. */
#define PPI_CHENCLR_CH3_Msk              (0x1UL << PPI_CHENCLR_CH3_Pos) /*!< Bit mask of CH3 field. */
#define PPI_CHENCLR_CH3_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH3_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH3_Clear            (1UL) /*!< Write: disable channel */

/* Bit 2 : Channel 2 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH2_Pos              (2UL) /*!< Position of CH2 field. */
#define PPI_CHENCLR_CH2_Msk              (0x1UL << PPI_CHENCLR_CH2_Pos) /*!< Bit mask of CH2 field. */
#define PPI_CHENCLR_CH2_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH2_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH2_Clear            (1UL) /*!< Write: disable channel */

/* Bit 1 : Channel 1 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH1_Pos              (1UL) /*!< Position of CH1 field. */
#define PPI_CHENCLR_CH1_Msk              (0x1UL << PPI_CHENCLR_CH1_Pos) /*!< Bit mask of CH1 field. */
#define PPI_CHENCLR_CH1_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH1_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH1_Clear            (1UL) /*!< Write: disable channel */

/* Bit 0 : Channel 0 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH0_Pos              (0UL) /*!< Position of CH0 field. */
#define PPI_CHENCLR_CH0_Msk              (0x1UL << PPI_CHENCLR_CH0_Pos) /*!< Bit mask of CH0 field. */
#define PPI_CHENCLR_CH0_Disabled         (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH0_Enabled          (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH0_Clear            (1UL) /*!< Write: disable channel */

/* Register: PPI_CH_EEP */
/* Description: Description cluster: Channel n event end-point */

/* Bits 31..0 : Pointer to event register. Accepts only addresses to registers from the Event group. */
#define PPI_CH_EEP_EEP_Pos               (0UL) /*!< Position of EEP field. */
#define PPI_CH_EEP_EEP_Msk               (0xFFFFFFFFUL << PPI_CH_EEP_EEP_Pos) /*!< Bit mask of EEP field. */

/* Register: PPI_CH_TEP */
/* Description: Description cluster: Channel n task end-point */

/* Bits 31..0 : Pointer to task register. Accepts only addresses to registers from the Task group. */
#define PPI_CH_TEP_TEP_Pos               (0UL) /*!< Position of TEP field. */
#define PPI_CH_TEP_TEP_Msk               (0xFFFFFFFFUL << PPI_CH_TEP_TEP_Pos) /*!< Bit mask of TEP field. */

/* Register: PPI_CHG */
/* Description: Description collection: Channel group n */

/* Bit 31 : Include or exclude channel 31 */
#define PPI_CHG_CH31_Pos                 (31UL)                      /*!< Position of CH31 field. */
#define PPI_CHG_CH31_Msk                 (0x1UL << PPI_CHG_CH31_Pos) /*!< Bit mask of CH31 field. */
#define PPI_CHG_CH31_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH31_Included            (1UL)                       /*!< Include */

/* Bit 30 : Include or exclude channel 30 */
#define PPI_CHG_CH30_Pos                 (30UL)                      /*!< Position of CH30 field. */
#define PPI_CHG_CH30_Msk                 (0x1UL << PPI_CHG_CH30_Pos) /*!< Bit mask of CH30 field. */
#define PPI_CHG_CH30_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH30_Included            (1UL)                       /*!< Include */

/* Bit 29 : Include or exclude channel 29 */
#define PPI_CHG_CH29_Pos                 (29UL)                      /*!< Position of CH29 field. */
#define PPI_CHG_CH29_Msk                 (0x1UL << PPI_CHG_CH29_Pos) /*!< Bit mask of CH29 field. */
#define PPI_CHG_CH29_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH29_Included            (1UL)                       /*!< Include */

/* Bit 28 : Include or exclude channel 28 */
#define PPI_CHG_CH28_Pos                 (28UL)                      /*!< Position of CH28 field. */
#define PPI_CHG_CH28_Msk                 (0x1UL << PPI_CHG_CH28_Pos) /*!< Bit mask of CH28 field. */
#define PPI_CHG_CH28_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH28_Included            (1UL)                       /*!< Include */

/* Bit 27 : Include or exclude channel 27 */
#define PPI_CHG_CH27_Pos                 (27UL)                      /*!< Position of CH27 field. */
#define PPI_CHG_CH27_Msk                 (0x1UL << PPI_CHG_CH27_Pos) /*!< Bit mask of CH27 field. */
#define PPI_CHG_CH27_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH27_Included            (1UL)                       /*!< Include */

/* Bit 26 : Include or exclude channel 26 */
#define PPI_CHG_CH26_Pos                 (26UL)                      /*!< Position of CH26 field. */
#define PPI_CHG_CH26_Msk                 (0x1UL << PPI_CHG_CH26_Pos) /*!< Bit mask of CH26 field. */
#define PPI_CHG_CH26_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH26_Included            (1UL)                       /*!< Include */

/* Bit 25 : Include or exclude channel 25 */
#define PPI_CHG_CH25_Pos                 (25UL)                      /*!< Position of CH25 field. */
#define PPI_CHG_CH25_Msk                 (0x1UL << PPI_CHG_CH25_Pos) /*!< Bit mask of CH25 field. */
#define PPI_CHG_CH25_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH25_Included            (1UL)                       /*!< Include */

/* Bit 24 : Include or exclude channel 24 */
#define PPI_CHG_CH24_Pos                 (24UL)                      /*!< Position of CH24 field. */
#define PPI_CHG_CH24_Msk                 (0x1UL << PPI_CHG_CH24_Pos) /*!< Bit mask of CH24 field. */
#define PPI_CHG_CH24_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH24_Included            (1UL)                       /*!< Include */

/* Bit 23 : Include or exclude channel 23 */
#define PPI_CHG_CH23_Pos                 (23UL)                      /*!< Position of CH23 field. */
#define PPI_CHG_CH23_Msk                 (0x1UL << PPI_CHG_CH23_Pos) /*!< Bit mask of CH23 field. */
#define PPI_CHG_CH23_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH23_Included            (1UL)                       /*!< Include */

/* Bit 22 : Include or exclude channel 22 */
#define PPI_CHG_CH22_Pos                 (22UL)                      /*!< Position of CH22 field. */
#define PPI_CHG_CH22_Msk                 (0x1UL << PPI_CHG_CH22_Pos) /*!< Bit mask of CH22 field. */
#define PPI_CHG_CH22_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH22_Included            (1UL)                       /*!< Include */

/* Bit 21 : Include or exclude channel 21 */
#define PPI_CHG_CH21_Pos                 (21UL)                      /*!< Position of CH21 field. */
#define PPI_CHG_CH21_Msk                 (0x1UL << PPI_CHG_CH21_Pos) /*!< Bit mask of CH21 field. */
#define PPI_CHG_CH21_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH21_Included            (1UL)                       /*!< Include */

/* Bit 20 : Include or exclude channel 20 */
#define PPI_CHG_CH20_Pos                 (20UL)                      /*!< Position of CH20 field. */
#define PPI_CHG_CH20_Msk                 (0x1UL << PPI_CHG_CH20_Pos) /*!< Bit mask of CH20 field. */
#define PPI_CHG_CH20_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH20_Included            (1UL)                       /*!< Include */

/* Bit 19 : Include or exclude channel 19 */
#define PPI_CHG_CH19_Pos                 (19UL)                      /*!< Position of CH19 field. */
#define PPI_CHG_CH19_Msk                 (0x1UL << PPI_CHG_CH19_Pos) /*!< Bit mask of CH19 field. */
#define PPI_CHG_CH19_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH19_Included            (1UL)                       /*!< Include */

/* Bit 18 : Include or exclude channel 18 */
#define PPI_CHG_CH18_Pos                 (18UL)                      /*!< Position of CH18 field. */
#define PPI_CHG_CH18_Msk                 (0x1UL << PPI_CHG_CH18_Pos) /*!< Bit mask of CH18 field. */
#define PPI_CHG_CH18_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH18_Included            (1UL)                       /*!< Include */

/* Bit 17 : Include or exclude channel 17 */
#define PPI_CHG_CH17_Pos                 (17UL)                      /*!< Position of CH17 field. */
#define PPI_CHG_CH17_Msk                 (0x1UL << PPI_CHG_CH17_Pos) /*!< Bit mask of CH17 field. */
#define PPI_CHG_CH17_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH17_Included            (1UL)                       /*!< Include */

/* Bit 16 : Include or exclude channel 16 */
#define PPI_CHG_CH16_Pos                 (16UL)                      /*!< Position of CH16 field. */
#define PPI_CHG_CH16_Msk                 (0x1UL << PPI_CHG_CH16_Pos) /*!< Bit mask of CH16 field. */
#define PPI_CHG_CH16_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH16_Included            (1UL)                       /*!< Include */

/* Bit 15 : Include or exclude channel 15 */
#define PPI_CHG_CH15_Pos                 (15UL)                      /*!< Position of CH15 field. */
#define PPI_CHG_CH15_Msk                 (0x1UL << PPI_CHG_CH15_Pos) /*!< Bit mask of CH15 field. */
#define PPI_CHG_CH15_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH15_Included            (1UL)                       /*!< Include */

/* Bit 14 : Include or exclude channel 14 */
#define PPI_CHG_CH14_Pos                 (14UL)                      /*!< Position of CH14 field. */
#define PPI_CHG_CH14_Msk                 (0x1UL << PPI_CHG_CH14_Pos) /*!< Bit mask of CH14 field. */
#define PPI_CHG_CH14_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH14_Included            (1UL)                       /*!< Include */

/* Bit 13 : Include or exclude channel 13 */
#define PPI_CHG_CH13_Pos                 (13UL)                      /*!< Position of CH13 field. */
#define PPI_CHG_CH13_Msk                 (0x1UL << PPI_CHG_CH13_Pos) /*!< Bit mask of CH13 field. */
#define PPI_CHG_CH13_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH13_Included            (1UL)                       /*!< Include */

/* Bit 12 : Include or exclude channel 12 */
#define PPI_CHG_CH12_Pos                 (12UL)                      /*!< Position of CH12 field. */
#define PPI_CHG_CH12_Msk                 (0x1UL << PPI_CHG_CH12_Pos) /*!< Bit mask of CH12 field. */
#define PPI_CHG_CH12_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH12_Included            (1UL)                       /*!< Include */

/* Bit 11 : Include or exclude channel 11 */
#define PPI_CHG_CH11_Pos                 (11UL)                      /*!< Position of CH11 field. */
#define PPI_CHG_CH11_Msk                 (0x1UL << PPI_CHG_CH11_Pos) /*!< Bit mask of CH11 field. */
#define PPI_CHG_CH11_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH11_Included            (1UL)                       /*!< Include */

/* Bit 10 : Include or exclude channel 10 */
#define PPI_CHG_CH10_Pos                 (10UL)                      /*!< Position of CH10 field. */
#define PPI_CHG_CH10_Msk                 (0x1UL << PPI_CHG_CH10_Pos) /*!< Bit mask of CH10 field. */
#define PPI_CHG_CH10_Excluded            (0UL)                       /*!< Exclude */
#define PPI_CHG_CH10_Included            (1UL)                       /*!< Include */

/* Bit 9 : Include or exclude channel 9 */
#define PPI_CHG_CH9_Pos                  (9UL)                      /*!< Position of CH9 field. */
#define PPI_CHG_CH9_Msk                  (0x1UL << PPI_CHG_CH9_Pos) /*!< Bit mask of CH9 field. */
#define PPI_CHG_CH9_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH9_Included             (1UL)                      /*!< Include */

/* Bit 8 : Include or exclude channel 8 */
#define PPI_CHG_CH8_Pos                  (8UL)                      /*!< Position of CH8 field. */
#define PPI_CHG_CH8_Msk                  (0x1UL << PPI_CHG_CH8_Pos) /*!< Bit mask of CH8 field. */
#define PPI_CHG_CH8_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH8_Included             (1UL)                      /*!< Include */

/* Bit 7 : Include or exclude channel 7 */
#define PPI_CHG_CH7_Pos                  (7UL)                      /*!< Position of CH7 field. */
#define PPI_CHG_CH7_Msk                  (0x1UL << PPI_CHG_CH7_Pos) /*!< Bit mask of CH7 field. */
#define PPI_CHG_CH7_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH7_Included             (1UL)                      /*!< Include */

/* Bit 6 : Include or exclude channel 6 */
#define PPI_CHG_CH6_Pos                  (6UL)                      /*!< Position of CH6 field. */
#define PPI_CHG_CH6_Msk                  (0x1UL << PPI_CHG_CH6_Pos) /*!< Bit mask of CH6 field. */
#define PPI_CHG_CH6_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH6_Included             (1UL)                      /*!< Include */

/* Bit 5 : Include or exclude channel 5 */
#define PPI_CHG_CH5_Pos                  (5UL)                      /*!< Position of CH5 field. */
#define PPI_CHG_CH5_Msk                  (0x1UL << PPI_CHG_CH5_Pos) /*!< Bit mask of CH5 field. */
#define PPI_CHG_CH5_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH5_Included             (1UL)                      /*!< Include */

/* Bit 4 : Include or exclude channel 4 */
#define PPI_CHG_CH4_Pos                  (4UL)                      /*!< Position of CH4 field. */
#define PPI_CHG_CH4_Msk                  (0x1UL << PPI_CHG_CH4_Pos) /*!< Bit mask of CH4 field. */
#define PPI_CHG_CH4_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH4_Included             (1UL)                      /*!< Include */

/* Bit 3 : Include or exclude channel 3 */
#define PPI_CHG_CH3_Pos                  (3UL)                      /*!< Position of CH3 field. */
#define PPI_CHG_CH3_Msk                  (0x1UL << PPI_CHG_CH3_Pos) /*!< Bit mask of CH3 field. */
#define PPI_CHG_CH3_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH3_Included             (1UL)                      /*!< Include */

/* Bit 2 : Include or exclude channel 2 */
#define PPI_CHG_CH2_Pos                  (2UL)                      /*!< Position of CH2 field. */
#define PPI_CHG_CH2_Msk                  (0x1UL << PPI_CHG_CH2_Pos) /*!< Bit mask of CH2 field. */
#define PPI_CHG_CH2_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH2_Included             (1UL)                      /*!< Include */

/* Bit 1 : Include or exclude channel 1 */
#define PPI_CHG_CH1_Pos                  (1UL)                      /*!< Position of CH1 field. */
#define PPI_CHG_CH1_Msk                  (0x1UL << PPI_CHG_CH1_Pos) /*!< Bit mask of CH1 field. */
#define PPI_CHG_CH1_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH1_Included             (1UL)                      /*!< Include */

/* Bit 0 : Include or exclude channel 0 */
#define PPI_CHG_CH0_Pos                  (0UL)                      /*!< Position of CH0 field. */
#define PPI_CHG_CH0_Msk                  (0x1UL << PPI_CHG_CH0_Pos) /*!< Bit mask of CH0 field. */
#define PPI_CHG_CH0_Excluded             (0UL)                      /*!< Exclude */
#define PPI_CHG_CH0_Included             (1UL)                      /*!< Include */

/* Register: PPI_FORK_TEP */
/* Description: Description cluster: Channel n task end-point */

/* Bits 31..0 : Pointer to task register */
#define PPI_FORK_TEP_TEP_Pos             (0UL) /*!< Position of TEP field. */
#define PPI_FORK_TEP_TEP_Msk             (0xFFFFFFFFUL << PPI_FORK_TEP_TEP_Pos) /*!< Bit mask of TEP field. */


/* Peripheral: QDEC */
/* Description: Quadrature Decoder */

/* Register: QDEC_TASKS_START */
/* Description: Task starting the quadrature decoder */

/* Bit 0 : Task starting the quadrature decoder */
#define QDEC_TASKS_START_TASKS_START_Pos (0UL) /*!< Position of TASKS_START field. */
#define QDEC_TASKS_START_TASKS_START_Msk                                                           \
  (0x1UL << QDEC_TASKS_START_TASKS_START_Pos)      /*!< Bit mask of TASKS_START field. */
#define QDEC_TASKS_START_TASKS_START_Trigger (1UL) /*!< Trigger task */

/* Register: QDEC_TASKS_STOP */
/* Description: Task stopping the quadrature decoder */

/* Bit 0 : Task stopping the quadrature decoder */
#define QDEC_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define QDEC_TASKS_STOP_TASKS_STOP_Msk                                                             \
  (0x1UL << QDEC_TASKS_STOP_TASKS_STOP_Pos)              /*!< Bit mask of TASKS_STOP field. */
#define QDEC_TASKS_STOP_TASKS_STOP_Trigger         (1UL) /*!< Trigger task */

/* Register: QDEC_TASKS_READCLRACC */
/* Description: Read and clear ACC and ACCDBL */

/* Bit 0 : Read and clear ACC and ACCDBL */
#define QDEC_TASKS_READCLRACC_TASKS_READCLRACC_Pos (0UL) /*!< Position of TASKS_READCLRACC field. */
#define QDEC_TASKS_READCLRACC_TASKS_READCLRACC_Msk                                                 \
  (0x1UL << QDEC_TASKS_READCLRACC_TASKS_READCLRACC_Pos) /*!< Bit mask of TASKS_READCLRACC field. */
#define QDEC_TASKS_READCLRACC_TASKS_READCLRACC_Trigger (1UL) /*!< Trigger task */

/* Register: QDEC_TASKS_RDCLRACC */
/* Description: Read and clear ACC */

/* Bit 0 : Read and clear ACC */
#define QDEC_TASKS_RDCLRACC_TASKS_RDCLRACC_Pos         (0UL) /*!< Position of TASKS_RDCLRACC field. */
#define QDEC_TASKS_RDCLRACC_TASKS_RDCLRACC_Msk                                                     \
  (0x1UL << QDEC_TASKS_RDCLRACC_TASKS_RDCLRACC_Pos)      /*!< Bit mask of TASKS_RDCLRACC field. */
#define QDEC_TASKS_RDCLRACC_TASKS_RDCLRACC_Trigger (1UL) /*!< Trigger task */

/* Register: QDEC_TASKS_RDCLRDBL */
/* Description: Read and clear ACCDBL */

/* Bit 0 : Read and clear ACCDBL */
#define QDEC_TASKS_RDCLRDBL_TASKS_RDCLRDBL_Pos     (0UL) /*!< Position of TASKS_RDCLRDBL field. */
#define QDEC_TASKS_RDCLRDBL_TASKS_RDCLRDBL_Msk                                                     \
  (0x1UL << QDEC_TASKS_RDCLRDBL_TASKS_RDCLRDBL_Pos)      /*!< Bit mask of TASKS_RDCLRDBL field. */
#define QDEC_TASKS_RDCLRDBL_TASKS_RDCLRDBL_Trigger (1UL) /*!< Trigger task */

/* Register: QDEC_EVENTS_SAMPLERDY */
/* Description: Event being generated for every new sample value written to the SAMPLE register */

/* Bit 0 : Event being generated for every new sample value written to the SAMPLE register */
#define QDEC_EVENTS_SAMPLERDY_EVENTS_SAMPLERDY_Pos (0UL) /*!< Position of EVENTS_SAMPLERDY field. */
#define QDEC_EVENTS_SAMPLERDY_EVENTS_SAMPLERDY_Msk                                                 \
  (0x1UL << QDEC_EVENTS_SAMPLERDY_EVENTS_SAMPLERDY_Pos) /*!< Bit mask of EVENTS_SAMPLERDY field. */
#define QDEC_EVENTS_SAMPLERDY_EVENTS_SAMPLERDY_NotGenerated (0UL) /*!< Event not generated */
#define QDEC_EVENTS_SAMPLERDY_EVENTS_SAMPLERDY_Generated    (1UL) /*!< Event generated */

/* Register: QDEC_EVENTS_REPORTRDY */
/* Description: Non-null report ready */

/* Bit 0 : Non-null report ready */
#define QDEC_EVENTS_REPORTRDY_EVENTS_REPORTRDY_Pos          (0UL) /*!< Position of EVENTS_REPORTRDY field. */
#define QDEC_EVENTS_REPORTRDY_EVENTS_REPORTRDY_Msk                                                 \
  (0x1UL << QDEC_EVENTS_REPORTRDY_EVENTS_REPORTRDY_Pos) /*!< Bit mask of EVENTS_REPORTRDY field. */
#define QDEC_EVENTS_REPORTRDY_EVENTS_REPORTRDY_NotGenerated (0UL) /*!< Event not generated */
#define QDEC_EVENTS_REPORTRDY_EVENTS_REPORTRDY_Generated    (1UL) /*!< Event generated */

/* Register: QDEC_EVENTS_ACCOF */
/* Description: ACC or ACCDBL register overflow */

/* Bit 0 : ACC or ACCDBL register overflow */
#define QDEC_EVENTS_ACCOF_EVENTS_ACCOF_Pos                  (0UL) /*!< Position of EVENTS_ACCOF field. */
#define QDEC_EVENTS_ACCOF_EVENTS_ACCOF_Msk                                                         \
  (0x1UL << QDEC_EVENTS_ACCOF_EVENTS_ACCOF_Pos)           /*!< Bit mask of EVENTS_ACCOF field. */
#define QDEC_EVENTS_ACCOF_EVENTS_ACCOF_NotGenerated (0UL) /*!< Event not generated */
#define QDEC_EVENTS_ACCOF_EVENTS_ACCOF_Generated    (1UL) /*!< Event generated */

/* Register: QDEC_EVENTS_DBLRDY */
/* Description: Double displacement(s) detected */

/* Bit 0 : Double displacement(s) detected */
#define QDEC_EVENTS_DBLRDY_EVENTS_DBLRDY_Pos        (0UL) /*!< Position of EVENTS_DBLRDY field. */
#define QDEC_EVENTS_DBLRDY_EVENTS_DBLRDY_Msk                                                       \
  (0x1UL << QDEC_EVENTS_DBLRDY_EVENTS_DBLRDY_Pos)           /*!< Bit mask of EVENTS_DBLRDY field. */
#define QDEC_EVENTS_DBLRDY_EVENTS_DBLRDY_NotGenerated (0UL) /*!< Event not generated */
#define QDEC_EVENTS_DBLRDY_EVENTS_DBLRDY_Generated    (1UL) /*!< Event generated */

/* Register: QDEC_EVENTS_STOPPED */
/* Description: QDEC has been stopped */

/* Bit 0 : QDEC has been stopped */
#define QDEC_EVENTS_STOPPED_EVENTS_STOPPED_Pos        (0UL) /*!< Position of EVENTS_STOPPED field. */
#define QDEC_EVENTS_STOPPED_EVENTS_STOPPED_Msk                                                     \
  (0x1UL << QDEC_EVENTS_STOPPED_EVENTS_STOPPED_Pos) /*!< Bit mask of EVENTS_STOPPED field. */
#define QDEC_EVENTS_STOPPED_EVENTS_STOPPED_NotGenerated (0UL) /*!< Event not generated */
#define QDEC_EVENTS_STOPPED_EVENTS_STOPPED_Generated    (1UL) /*!< Event generated */

/* Register: QDEC_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 6 : Shortcut between event SAMPLERDY and task READCLRACC */
#define QDEC_SHORTS_SAMPLERDY_READCLRACC_Pos            (6UL) /*!< Position of SAMPLERDY_READCLRACC field. */
#define QDEC_SHORTS_SAMPLERDY_READCLRACC_Msk                                                       \
  (0x1UL << QDEC_SHORTS_SAMPLERDY_READCLRACC_Pos) /*!< Bit mask of SAMPLERDY_READCLRACC field. */
#define QDEC_SHORTS_SAMPLERDY_READCLRACC_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_SAMPLERDY_READCLRACC_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 5 : Shortcut between event DBLRDY and task STOP */
#define QDEC_SHORTS_DBLRDY_STOP_Pos               (5UL) /*!< Position of DBLRDY_STOP field. */
#define QDEC_SHORTS_DBLRDY_STOP_Msk                                                                \
  (0x1UL << QDEC_SHORTS_DBLRDY_STOP_Pos)       /*!< Bit mask of DBLRDY_STOP field. */
#define QDEC_SHORTS_DBLRDY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_DBLRDY_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 4 : Shortcut between event DBLRDY and task RDCLRDBL */
#define QDEC_SHORTS_DBLRDY_RDCLRDBL_Pos  (4UL) /*!< Position of DBLRDY_RDCLRDBL field. */
#define QDEC_SHORTS_DBLRDY_RDCLRDBL_Msk                                                            \
  (0x1UL << QDEC_SHORTS_DBLRDY_RDCLRDBL_Pos)       /*!< Bit mask of DBLRDY_RDCLRDBL field. */
#define QDEC_SHORTS_DBLRDY_RDCLRDBL_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_DBLRDY_RDCLRDBL_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between event REPORTRDY and task STOP */
#define QDEC_SHORTS_REPORTRDY_STOP_Pos       (3UL) /*!< Position of REPORTRDY_STOP field. */
#define QDEC_SHORTS_REPORTRDY_STOP_Msk                                                             \
  (0x1UL << QDEC_SHORTS_REPORTRDY_STOP_Pos)       /*!< Bit mask of REPORTRDY_STOP field. */
#define QDEC_SHORTS_REPORTRDY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_REPORTRDY_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between event REPORTRDY and task RDCLRACC */
#define QDEC_SHORTS_REPORTRDY_RDCLRACC_Pos  (2UL) /*!< Position of REPORTRDY_RDCLRACC field. */
#define QDEC_SHORTS_REPORTRDY_RDCLRACC_Msk                                                         \
  (0x1UL << QDEC_SHORTS_REPORTRDY_RDCLRACC_Pos)       /*!< Bit mask of REPORTRDY_RDCLRACC field. */
#define QDEC_SHORTS_REPORTRDY_RDCLRACC_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_REPORTRDY_RDCLRACC_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between event SAMPLERDY and task STOP */
#define QDEC_SHORTS_SAMPLERDY_STOP_Pos          (1UL) /*!< Position of SAMPLERDY_STOP field. */
#define QDEC_SHORTS_SAMPLERDY_STOP_Msk                                                             \
  (0x1UL << QDEC_SHORTS_SAMPLERDY_STOP_Pos)        /*!< Bit mask of SAMPLERDY_STOP field. */
#define QDEC_SHORTS_SAMPLERDY_STOP_Disabled  (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_SAMPLERDY_STOP_Enabled   (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between event REPORTRDY and task READCLRACC */
#define QDEC_SHORTS_REPORTRDY_READCLRACC_Pos (0UL) /*!< Position of REPORTRDY_READCLRACC field. */
#define QDEC_SHORTS_REPORTRDY_READCLRACC_Msk                                                       \
  (0x1UL << QDEC_SHORTS_REPORTRDY_READCLRACC_Pos) /*!< Bit mask of REPORTRDY_READCLRACC field. */
#define QDEC_SHORTS_REPORTRDY_READCLRACC_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_REPORTRDY_READCLRACC_Enabled  (1UL) /*!< Enable shortcut */

/* Register: QDEC_INTENSET */
/* Description: Enable interrupt */

/* Bit 4 : Write '1' to enable interrupt for event STOPPED */
#define QDEC_INTENSET_STOPPED_Pos                 (4UL) /*!< Position of STOPPED field. */
#define QDEC_INTENSET_STOPPED_Msk                                                                  \
  (0x1UL << QDEC_INTENSET_STOPPED_Pos)       /*!< Bit mask of STOPPED field. */
#define QDEC_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENSET_STOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define QDEC_INTENSET_STOPPED_Set      (1UL) /*!< Enable */

/* Bit 3 : Write '1' to enable interrupt for event DBLRDY */
#define QDEC_INTENSET_DBLRDY_Pos       (3UL) /*!< Position of DBLRDY field. */
#define QDEC_INTENSET_DBLRDY_Msk                                                                   \
  (0x1UL << QDEC_INTENSET_DBLRDY_Pos)       /*!< Bit mask of DBLRDY field. */
#define QDEC_INTENSET_DBLRDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENSET_DBLRDY_Enabled  (1UL) /*!< Read: Enabled */
#define QDEC_INTENSET_DBLRDY_Set      (1UL) /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event ACCOF */
#define QDEC_INTENSET_ACCOF_Pos       (2UL) /*!< Position of ACCOF field. */
#define QDEC_INTENSET_ACCOF_Msk       (0x1UL << QDEC_INTENSET_ACCOF_Pos) /*!< Bit mask of ACCOF field. */
#define QDEC_INTENSET_ACCOF_Disabled  (0UL)                              /*!< Read: Disabled */
#define QDEC_INTENSET_ACCOF_Enabled   (1UL)                              /*!< Read: Enabled */
#define QDEC_INTENSET_ACCOF_Set       (1UL)                              /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event REPORTRDY */
#define QDEC_INTENSET_REPORTRDY_Pos   (1UL) /*!< Position of REPORTRDY field. */
#define QDEC_INTENSET_REPORTRDY_Msk                                                                \
  (0x1UL << QDEC_INTENSET_REPORTRDY_Pos)       /*!< Bit mask of REPORTRDY field. */
#define QDEC_INTENSET_REPORTRDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENSET_REPORTRDY_Enabled  (1UL) /*!< Read: Enabled */
#define QDEC_INTENSET_REPORTRDY_Set      (1UL) /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event SAMPLERDY */
#define QDEC_INTENSET_SAMPLERDY_Pos      (0UL) /*!< Position of SAMPLERDY field. */
#define QDEC_INTENSET_SAMPLERDY_Msk                                                                \
  (0x1UL << QDEC_INTENSET_SAMPLERDY_Pos)       /*!< Bit mask of SAMPLERDY field. */
#define QDEC_INTENSET_SAMPLERDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENSET_SAMPLERDY_Enabled  (1UL) /*!< Read: Enabled */
#define QDEC_INTENSET_SAMPLERDY_Set      (1UL) /*!< Enable */

/* Register: QDEC_INTENCLR */
/* Description: Disable interrupt */

/* Bit 4 : Write '1' to disable interrupt for event STOPPED */
#define QDEC_INTENCLR_STOPPED_Pos        (4UL) /*!< Position of STOPPED field. */
#define QDEC_INTENCLR_STOPPED_Msk                                                                  \
  (0x1UL << QDEC_INTENCLR_STOPPED_Pos)       /*!< Bit mask of STOPPED field. */
#define QDEC_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENCLR_STOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define QDEC_INTENCLR_STOPPED_Clear    (1UL) /*!< Disable */

/* Bit 3 : Write '1' to disable interrupt for event DBLRDY */
#define QDEC_INTENCLR_DBLRDY_Pos       (3UL) /*!< Position of DBLRDY field. */
#define QDEC_INTENCLR_DBLRDY_Msk                                                                   \
  (0x1UL << QDEC_INTENCLR_DBLRDY_Pos)       /*!< Bit mask of DBLRDY field. */
#define QDEC_INTENCLR_DBLRDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENCLR_DBLRDY_Enabled  (1UL) /*!< Read: Enabled */
#define QDEC_INTENCLR_DBLRDY_Clear    (1UL) /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event ACCOF */
#define QDEC_INTENCLR_ACCOF_Pos       (2UL) /*!< Position of ACCOF field. */
#define QDEC_INTENCLR_ACCOF_Msk       (0x1UL << QDEC_INTENCLR_ACCOF_Pos) /*!< Bit mask of ACCOF field. */
#define QDEC_INTENCLR_ACCOF_Disabled  (0UL)                              /*!< Read: Disabled */
#define QDEC_INTENCLR_ACCOF_Enabled   (1UL)                              /*!< Read: Enabled */
#define QDEC_INTENCLR_ACCOF_Clear     (1UL)                              /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event REPORTRDY */
#define QDEC_INTENCLR_REPORTRDY_Pos   (1UL) /*!< Position of REPORTRDY field. */
#define QDEC_INTENCLR_REPORTRDY_Msk                                                                \
  (0x1UL << QDEC_INTENCLR_REPORTRDY_Pos)       /*!< Bit mask of REPORTRDY field. */
#define QDEC_INTENCLR_REPORTRDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENCLR_REPORTRDY_Enabled  (1UL) /*!< Read: Enabled */
#define QDEC_INTENCLR_REPORTRDY_Clear    (1UL) /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event SAMPLERDY */
#define QDEC_INTENCLR_SAMPLERDY_Pos      (0UL) /*!< Position of SAMPLERDY field. */
#define QDEC_INTENCLR_SAMPLERDY_Msk                                                                \
  (0x1UL << QDEC_INTENCLR_SAMPLERDY_Pos)       /*!< Bit mask of SAMPLERDY field. */
#define QDEC_INTENCLR_SAMPLERDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENCLR_SAMPLERDY_Enabled  (1UL) /*!< Read: Enabled */
#define QDEC_INTENCLR_SAMPLERDY_Clear    (1UL) /*!< Disable */

/* Register: QDEC_ENABLE */
/* Description: Enable the quadrature decoder */

/* Bit 0 : Enable or disable the quadrature decoder */
#define QDEC_ENABLE_ENABLE_Pos           (0UL) /*!< Position of ENABLE field. */
#define QDEC_ENABLE_ENABLE_Msk           (0x1UL << QDEC_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define QDEC_ENABLE_ENABLE_Disabled      (0UL)                             /*!< Disable */
#define QDEC_ENABLE_ENABLE_Enabled       (1UL)                             /*!< Enable */

/* Register: QDEC_LEDPOL */
/* Description: LED output pin polarity */

/* Bit 0 : LED output pin polarity */
#define QDEC_LEDPOL_LEDPOL_Pos           (0UL) /*!< Position of LEDPOL field. */
#define QDEC_LEDPOL_LEDPOL_Msk           (0x1UL << QDEC_LEDPOL_LEDPOL_Pos) /*!< Bit mask of LEDPOL field. */
#define QDEC_LEDPOL_LEDPOL_ActiveLow     (0UL) /*!< Led active on output pin low */
#define QDEC_LEDPOL_LEDPOL_ActiveHigh    (1UL) /*!< Led active on output pin high */

/* Register: QDEC_SAMPLEPER */
/* Description: Sample period */

/* Bits 3..0 : Sample period. The SAMPLE register will be updated for every new sample */
#define QDEC_SAMPLEPER_SAMPLEPER_Pos     (0UL) /*!< Position of SAMPLEPER field. */
#define QDEC_SAMPLEPER_SAMPLEPER_Msk                                                               \
  (0xFUL << QDEC_SAMPLEPER_SAMPLEPER_Pos)       /*!< Bit mask of SAMPLEPER field. */
#define QDEC_SAMPLEPER_SAMPLEPER_128us   (0UL)  /*!< 128 us */
#define QDEC_SAMPLEPER_SAMPLEPER_256us   (1UL)  /*!< 256 us */
#define QDEC_SAMPLEPER_SAMPLEPER_512us   (2UL)  /*!< 512 us */
#define QDEC_SAMPLEPER_SAMPLEPER_1024us  (3UL)  /*!< 1024 us */
#define QDEC_SAMPLEPER_SAMPLEPER_2048us  (4UL)  /*!< 2048 us */
#define QDEC_SAMPLEPER_SAMPLEPER_4096us  (5UL)  /*!< 4096 us */
#define QDEC_SAMPLEPER_SAMPLEPER_8192us  (6UL)  /*!< 8192 us */
#define QDEC_SAMPLEPER_SAMPLEPER_16384us (7UL)  /*!< 16384 us */
#define QDEC_SAMPLEPER_SAMPLEPER_32ms    (8UL)  /*!< 32768 us */
#define QDEC_SAMPLEPER_SAMPLEPER_65ms    (9UL)  /*!< 65536 us */
#define QDEC_SAMPLEPER_SAMPLEPER_131ms   (10UL) /*!< 131072 us */

/* Register: QDEC_SAMPLE */
/* Description: Motion sample value */

/* Bits 31..0 : Last motion sample */
#define QDEC_SAMPLE_SAMPLE_Pos           (0UL) /*!< Position of SAMPLE field. */
#define QDEC_SAMPLE_SAMPLE_Msk                                                                     \
  (0xFFFFFFFFUL << QDEC_SAMPLE_SAMPLE_Pos) /*!< Bit mask of SAMPLE field. */

/* Register: QDEC_REPORTPER */
/* Description: Number of samples to be taken before REPORTRDY and DBLRDY events can be generated */

/* Bits 3..0 : Specifies the number of samples to be accumulated in the ACC register before the REPORTRDY and DBLRDY events can be generated */
#define QDEC_REPORTPER_REPORTPER_Pos (0UL) /*!< Position of REPORTPER field. */
#define QDEC_REPORTPER_REPORTPER_Msk                                                               \
  (0xFUL << QDEC_REPORTPER_REPORTPER_Pos)      /*!< Bit mask of REPORTPER field. */
#define QDEC_REPORTPER_REPORTPER_10Smpl  (0UL) /*!< 10 samples / report */
#define QDEC_REPORTPER_REPORTPER_40Smpl  (1UL) /*!< 40 samples / report */
#define QDEC_REPORTPER_REPORTPER_80Smpl  (2UL) /*!< 80 samples / report */
#define QDEC_REPORTPER_REPORTPER_120Smpl (3UL) /*!< 120 samples / report */
#define QDEC_REPORTPER_REPORTPER_160Smpl (4UL) /*!< 160 samples / report */
#define QDEC_REPORTPER_REPORTPER_200Smpl (5UL) /*!< 200 samples / report */
#define QDEC_REPORTPER_REPORTPER_240Smpl (6UL) /*!< 240 samples / report */
#define QDEC_REPORTPER_REPORTPER_280Smpl (7UL) /*!< 280 samples / report */
#define QDEC_REPORTPER_REPORTPER_1Smpl   (8UL) /*!< 1 sample / report */

/* Register: QDEC_ACC */
/* Description: Register accumulating the valid transitions */

/* Bits 31..0 : Register accumulating all valid samples (not double transition) read from the SAMPLE register */
#define QDEC_ACC_ACC_Pos                 (0UL) /*!< Position of ACC field. */
#define QDEC_ACC_ACC_Msk                 (0xFFFFFFFFUL << QDEC_ACC_ACC_Pos) /*!< Bit mask of ACC field. */

/* Register: QDEC_ACCREAD */
/* Description: Snapshot of the ACC register, updated by the READCLRACC or RDCLRACC task */

/* Bits 31..0 : Snapshot of the ACC register. */
#define QDEC_ACCREAD_ACCREAD_Pos         (0UL) /*!< Position of ACCREAD field. */
#define QDEC_ACCREAD_ACCREAD_Msk                                                                   \
  (0xFFFFFFFFUL << QDEC_ACCREAD_ACCREAD_Pos) /*!< Bit mask of ACCREAD field. */

/* Register: QDEC_PSEL_LED */
/* Description: Pin select for LED signal */

/* Bit 31 : Connection */
#define QDEC_PSEL_LED_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QDEC_PSEL_LED_CONNECT_Msk                                                                  \
  (0x1UL << QDEC_PSEL_LED_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define QDEC_PSEL_LED_CONNECT_Connected    (0UL) /*!< Connect */
#define QDEC_PSEL_LED_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define QDEC_PSEL_LED_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define QDEC_PSEL_LED_PIN_Msk              (0x1FUL << QDEC_PSEL_LED_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QDEC_PSEL_A */
/* Description: Pin select for A signal */

/* Bit 31 : Connection */
#define QDEC_PSEL_A_CONNECT_Pos            (31UL) /*!< Position of CONNECT field. */
#define QDEC_PSEL_A_CONNECT_Msk                                                                    \
  (0x1UL << QDEC_PSEL_A_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define QDEC_PSEL_A_CONNECT_Connected    (0UL) /*!< Connect */
#define QDEC_PSEL_A_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define QDEC_PSEL_A_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define QDEC_PSEL_A_PIN_Msk              (0x1FUL << QDEC_PSEL_A_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QDEC_PSEL_B */
/* Description: Pin select for B signal */

/* Bit 31 : Connection */
#define QDEC_PSEL_B_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define QDEC_PSEL_B_CONNECT_Msk                                                                    \
  (0x1UL << QDEC_PSEL_B_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define QDEC_PSEL_B_CONNECT_Connected    (0UL) /*!< Connect */
#define QDEC_PSEL_B_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define QDEC_PSEL_B_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define QDEC_PSEL_B_PIN_Msk              (0x1FUL << QDEC_PSEL_B_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QDEC_DBFEN */
/* Description: Enable input debounce filters */

/* Bit 0 : Enable input debounce filters */
#define QDEC_DBFEN_DBFEN_Pos             (0UL) /*!< Position of DBFEN field. */
#define QDEC_DBFEN_DBFEN_Msk             (0x1UL << QDEC_DBFEN_DBFEN_Pos) /*!< Bit mask of DBFEN field. */
#define QDEC_DBFEN_DBFEN_Disabled        (0UL) /*!< Debounce input filters disabled */
#define QDEC_DBFEN_DBFEN_Enabled         (1UL) /*!< Debounce input filters enabled */

/* Register: QDEC_LEDPRE */
/* Description: Time period the LED is switched ON prior to sampling */

/* Bits 8..0 : Period in us the LED is switched on prior to sampling */
#define QDEC_LEDPRE_LEDPRE_Pos           (0UL) /*!< Position of LEDPRE field. */
#define QDEC_LEDPRE_LEDPRE_Msk           (0x1FFUL << QDEC_LEDPRE_LEDPRE_Pos) /*!< Bit mask of LEDPRE field. */

/* Register: QDEC_ACCDBL */
/* Description: Register accumulating the number of detected double transitions */

/* Bits 3..0 : Register accumulating the number of detected double or illegal transitions. ( SAMPLE = 2 ). */
#define QDEC_ACCDBL_ACCDBL_Pos           (0UL) /*!< Position of ACCDBL field. */
#define QDEC_ACCDBL_ACCDBL_Msk           (0xFUL << QDEC_ACCDBL_ACCDBL_Pos) /*!< Bit mask of ACCDBL field. */

/* Register: QDEC_ACCDBLREAD */
/* Description: Snapshot of the ACCDBL, updated by the READCLRACC or RDCLRDBL task */

/* Bits 3..0 : Snapshot of the ACCDBL register. This field is updated when the READCLRACC or RDCLRDBL task is triggered. */
#define QDEC_ACCDBLREAD_ACCDBLREAD_Pos   (0UL) /*!< Position of ACCDBLREAD field. */
#define QDEC_ACCDBLREAD_ACCDBLREAD_Msk                                                             \
  (0xFUL << QDEC_ACCDBLREAD_ACCDBLREAD_Pos) /*!< Bit mask of ACCDBLREAD field. */


/* Peripheral: RADIO */
/* Description: 2.4 GHz radio */

/* Register: RADIO_TASKS_TXEN */
/* Description: Enable RADIO in TX mode */

/* Bit 0 : Enable RADIO in TX mode */
#define RADIO_TASKS_TXEN_TASKS_TXEN_Pos (0UL) /*!< Position of TASKS_TXEN field. */
#define RADIO_TASKS_TXEN_TASKS_TXEN_Msk                                                            \
  (0x1UL << RADIO_TASKS_TXEN_TASKS_TXEN_Pos)      /*!< Bit mask of TASKS_TXEN field. */
#define RADIO_TASKS_TXEN_TASKS_TXEN_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_RXEN */
/* Description: Enable RADIO in RX mode */

/* Bit 0 : Enable RADIO in RX mode */
#define RADIO_TASKS_RXEN_TASKS_RXEN_Pos     (0UL) /*!< Position of TASKS_RXEN field. */
#define RADIO_TASKS_RXEN_TASKS_RXEN_Msk                                                            \
  (0x1UL << RADIO_TASKS_RXEN_TASKS_RXEN_Pos)      /*!< Bit mask of TASKS_RXEN field. */
#define RADIO_TASKS_RXEN_TASKS_RXEN_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_START */
/* Description: Start RADIO */

/* Bit 0 : Start RADIO */
#define RADIO_TASKS_START_TASKS_START_Pos   (0UL) /*!< Position of TASKS_START field. */
#define RADIO_TASKS_START_TASKS_START_Msk                                                          \
  (0x1UL << RADIO_TASKS_START_TASKS_START_Pos)      /*!< Bit mask of TASKS_START field. */
#define RADIO_TASKS_START_TASKS_START_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_STOP */
/* Description: Stop RADIO */

/* Bit 0 : Stop RADIO */
#define RADIO_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define RADIO_TASKS_STOP_TASKS_STOP_Msk                                                            \
  (0x1UL << RADIO_TASKS_STOP_TASKS_STOP_Pos)        /*!< Bit mask of TASKS_STOP field. */
#define RADIO_TASKS_STOP_TASKS_STOP_Trigger   (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_DISABLE */
/* Description: Disable RADIO */

/* Bit 0 : Disable RADIO */
#define RADIO_TASKS_DISABLE_TASKS_DISABLE_Pos (0UL) /*!< Position of TASKS_DISABLE field. */
#define RADIO_TASKS_DISABLE_TASKS_DISABLE_Msk                                                      \
  (0x1UL << RADIO_TASKS_DISABLE_TASKS_DISABLE_Pos)      /*!< Bit mask of TASKS_DISABLE field. */
#define RADIO_TASKS_DISABLE_TASKS_DISABLE_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_RSSISTART */
/* Description: Start the RSSI and take one single sample of the receive signal strength */

/* Bit 0 : Start the RSSI and take one single sample of the receive signal strength */
#define RADIO_TASKS_RSSISTART_TASKS_RSSISTART_Pos (0UL) /*!< Position of TASKS_RSSISTART field. */
#define RADIO_TASKS_RSSISTART_TASKS_RSSISTART_Msk                                                  \
  (0x1UL << RADIO_TASKS_RSSISTART_TASKS_RSSISTART_Pos) /*!< Bit mask of TASKS_RSSISTART field. */
#define RADIO_TASKS_RSSISTART_TASKS_RSSISTART_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_RSSISTOP */
/* Description: Stop the RSSI measurement */

/* Bit 0 : Stop the RSSI measurement */
#define RADIO_TASKS_RSSISTOP_TASKS_RSSISTOP_Pos       (0UL) /*!< Position of TASKS_RSSISTOP field. */
#define RADIO_TASKS_RSSISTOP_TASKS_RSSISTOP_Msk                                                    \
  (0x1UL << RADIO_TASKS_RSSISTOP_TASKS_RSSISTOP_Pos)      /*!< Bit mask of TASKS_RSSISTOP field. */
#define RADIO_TASKS_RSSISTOP_TASKS_RSSISTOP_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_BCSTART */
/* Description: Start the bit counter */

/* Bit 0 : Start the bit counter */
#define RADIO_TASKS_BCSTART_TASKS_BCSTART_Pos       (0UL) /*!< Position of TASKS_BCSTART field. */
#define RADIO_TASKS_BCSTART_TASKS_BCSTART_Msk                                                      \
  (0x1UL << RADIO_TASKS_BCSTART_TASKS_BCSTART_Pos)      /*!< Bit mask of TASKS_BCSTART field. */
#define RADIO_TASKS_BCSTART_TASKS_BCSTART_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_BCSTOP */
/* Description: Stop the bit counter */

/* Bit 0 : Stop the bit counter */
#define RADIO_TASKS_BCSTOP_TASKS_BCSTOP_Pos       (0UL) /*!< Position of TASKS_BCSTOP field. */
#define RADIO_TASKS_BCSTOP_TASKS_BCSTOP_Msk                                                        \
  (0x1UL << RADIO_TASKS_BCSTOP_TASKS_BCSTOP_Pos)      /*!< Bit mask of TASKS_BCSTOP field. */
#define RADIO_TASKS_BCSTOP_TASKS_BCSTOP_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_EDSTART */
/* Description: Start the energy detect measurement used in IEEE 802.15.4 mode */

/* Bit 0 : Start the energy detect measurement used in IEEE 802.15.4 mode */
#define RADIO_TASKS_EDSTART_TASKS_EDSTART_Pos   (0UL) /*!< Position of TASKS_EDSTART field. */
#define RADIO_TASKS_EDSTART_TASKS_EDSTART_Msk                                                      \
  (0x1UL << RADIO_TASKS_EDSTART_TASKS_EDSTART_Pos)      /*!< Bit mask of TASKS_EDSTART field. */
#define RADIO_TASKS_EDSTART_TASKS_EDSTART_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_EDSTOP */
/* Description: Stop the energy detect measurement */

/* Bit 0 : Stop the energy detect measurement */
#define RADIO_TASKS_EDSTOP_TASKS_EDSTOP_Pos       (0UL) /*!< Position of TASKS_EDSTOP field. */
#define RADIO_TASKS_EDSTOP_TASKS_EDSTOP_Msk                                                        \
  (0x1UL << RADIO_TASKS_EDSTOP_TASKS_EDSTOP_Pos)      /*!< Bit mask of TASKS_EDSTOP field. */
#define RADIO_TASKS_EDSTOP_TASKS_EDSTOP_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_CCASTART */
/* Description: Start the clear channel assessment used in IEEE 802.15.4 mode */

/* Bit 0 : Start the clear channel assessment used in IEEE 802.15.4 mode */
#define RADIO_TASKS_CCASTART_TASKS_CCASTART_Pos (0UL) /*!< Position of TASKS_CCASTART field. */
#define RADIO_TASKS_CCASTART_TASKS_CCASTART_Msk                                                    \
  (0x1UL << RADIO_TASKS_CCASTART_TASKS_CCASTART_Pos)      /*!< Bit mask of TASKS_CCASTART field. */
#define RADIO_TASKS_CCASTART_TASKS_CCASTART_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_TASKS_CCASTOP */
/* Description: Stop the clear channel assessment */

/* Bit 0 : Stop the clear channel assessment */
#define RADIO_TASKS_CCASTOP_TASKS_CCASTOP_Pos       (0UL) /*!< Position of TASKS_CCASTOP field. */
#define RADIO_TASKS_CCASTOP_TASKS_CCASTOP_Msk                                                      \
  (0x1UL << RADIO_TASKS_CCASTOP_TASKS_CCASTOP_Pos)      /*!< Bit mask of TASKS_CCASTOP field. */
#define RADIO_TASKS_CCASTOP_TASKS_CCASTOP_Trigger (1UL) /*!< Trigger task */

/* Register: RADIO_EVENTS_READY */
/* Description: RADIO has ramped up and is ready to be started */

/* Bit 0 : RADIO has ramped up and is ready to be started */
#define RADIO_EVENTS_READY_EVENTS_READY_Pos       (0UL) /*!< Position of EVENTS_READY field. */
#define RADIO_EVENTS_READY_EVENTS_READY_Msk                                                        \
  (0x1UL << RADIO_EVENTS_READY_EVENTS_READY_Pos)           /*!< Bit mask of EVENTS_READY field. */
#define RADIO_EVENTS_READY_EVENTS_READY_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_READY_EVENTS_READY_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_ADDRESS */
/* Description: Address sent or received */

/* Bit 0 : Address sent or received */
#define RADIO_EVENTS_ADDRESS_EVENTS_ADDRESS_Pos      (0UL) /*!< Position of EVENTS_ADDRESS field. */
#define RADIO_EVENTS_ADDRESS_EVENTS_ADDRESS_Msk                                                    \
  (0x1UL << RADIO_EVENTS_ADDRESS_EVENTS_ADDRESS_Pos) /*!< Bit mask of EVENTS_ADDRESS field. */
#define RADIO_EVENTS_ADDRESS_EVENTS_ADDRESS_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_ADDRESS_EVENTS_ADDRESS_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_PAYLOAD */
/* Description: Packet payload sent or received */

/* Bit 0 : Packet payload sent or received */
#define RADIO_EVENTS_PAYLOAD_EVENTS_PAYLOAD_Pos          (0UL) /*!< Position of EVENTS_PAYLOAD field. */
#define RADIO_EVENTS_PAYLOAD_EVENTS_PAYLOAD_Msk                                                    \
  (0x1UL << RADIO_EVENTS_PAYLOAD_EVENTS_PAYLOAD_Pos) /*!< Bit mask of EVENTS_PAYLOAD field. */
#define RADIO_EVENTS_PAYLOAD_EVENTS_PAYLOAD_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_PAYLOAD_EVENTS_PAYLOAD_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_END */
/* Description: Packet sent or received */

/* Bit 0 : Packet sent or received */
#define RADIO_EVENTS_END_EVENTS_END_Pos                  (0UL) /*!< Position of EVENTS_END field. */
#define RADIO_EVENTS_END_EVENTS_END_Msk                                                            \
  (0x1UL << RADIO_EVENTS_END_EVENTS_END_Pos)            /*!< Bit mask of EVENTS_END field. */
#define RADIO_EVENTS_END_EVENTS_END_NotGenerated  (0UL) /*!< Event not generated */
#define RADIO_EVENTS_END_EVENTS_END_Generated     (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_DISABLED */
/* Description: RADIO has been disabled */

/* Bit 0 : RADIO has been disabled */
#define RADIO_EVENTS_DISABLED_EVENTS_DISABLED_Pos (0UL) /*!< Position of EVENTS_DISABLED field. */
#define RADIO_EVENTS_DISABLED_EVENTS_DISABLED_Msk                                                  \
  (0x1UL << RADIO_EVENTS_DISABLED_EVENTS_DISABLED_Pos) /*!< Bit mask of EVENTS_DISABLED field. */
#define RADIO_EVENTS_DISABLED_EVENTS_DISABLED_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_DISABLED_EVENTS_DISABLED_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_DEVMATCH */
/* Description: A device address match occurred on the last received packet */

/* Bit 0 : A device address match occurred on the last received packet */
#define RADIO_EVENTS_DEVMATCH_EVENTS_DEVMATCH_Pos          (0UL) /*!< Position of EVENTS_DEVMATCH field. */
#define RADIO_EVENTS_DEVMATCH_EVENTS_DEVMATCH_Msk                                                  \
  (0x1UL << RADIO_EVENTS_DEVMATCH_EVENTS_DEVMATCH_Pos) /*!< Bit mask of EVENTS_DEVMATCH field. */
#define RADIO_EVENTS_DEVMATCH_EVENTS_DEVMATCH_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_DEVMATCH_EVENTS_DEVMATCH_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_DEVMISS */
/* Description: No device address match occurred on the last received packet */

/* Bit 0 : No device address match occurred on the last received packet */
#define RADIO_EVENTS_DEVMISS_EVENTS_DEVMISS_Pos            (0UL) /*!< Position of EVENTS_DEVMISS field. */
#define RADIO_EVENTS_DEVMISS_EVENTS_DEVMISS_Msk                                                    \
  (0x1UL << RADIO_EVENTS_DEVMISS_EVENTS_DEVMISS_Pos) /*!< Bit mask of EVENTS_DEVMISS field. */
#define RADIO_EVENTS_DEVMISS_EVENTS_DEVMISS_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_DEVMISS_EVENTS_DEVMISS_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_RSSIEND */
/* Description: Sampling of receive signal strength complete */

/* Bit 0 : Sampling of receive signal strength complete */
#define RADIO_EVENTS_RSSIEND_EVENTS_RSSIEND_Pos          (0UL) /*!< Position of EVENTS_RSSIEND field. */
#define RADIO_EVENTS_RSSIEND_EVENTS_RSSIEND_Msk                                                    \
  (0x1UL << RADIO_EVENTS_RSSIEND_EVENTS_RSSIEND_Pos) /*!< Bit mask of EVENTS_RSSIEND field. */
#define RADIO_EVENTS_RSSIEND_EVENTS_RSSIEND_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_RSSIEND_EVENTS_RSSIEND_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_BCMATCH */
/* Description: Bit counter reached bit count value */

/* Bit 0 : Bit counter reached bit count value */
#define RADIO_EVENTS_BCMATCH_EVENTS_BCMATCH_Pos          (0UL) /*!< Position of EVENTS_BCMATCH field. */
#define RADIO_EVENTS_BCMATCH_EVENTS_BCMATCH_Msk                                                    \
  (0x1UL << RADIO_EVENTS_BCMATCH_EVENTS_BCMATCH_Pos) /*!< Bit mask of EVENTS_BCMATCH field. */
#define RADIO_EVENTS_BCMATCH_EVENTS_BCMATCH_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_BCMATCH_EVENTS_BCMATCH_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_CRCOK */
/* Description: Packet received with CRC ok */

/* Bit 0 : Packet received with CRC ok */
#define RADIO_EVENTS_CRCOK_EVENTS_CRCOK_Pos              (0UL) /*!< Position of EVENTS_CRCOK field. */
#define RADIO_EVENTS_CRCOK_EVENTS_CRCOK_Msk                                                        \
  (0x1UL << RADIO_EVENTS_CRCOK_EVENTS_CRCOK_Pos)           /*!< Bit mask of EVENTS_CRCOK field. */
#define RADIO_EVENTS_CRCOK_EVENTS_CRCOK_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_CRCOK_EVENTS_CRCOK_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_CRCERROR */
/* Description: Packet received with CRC error */

/* Bit 0 : Packet received with CRC error */
#define RADIO_EVENTS_CRCERROR_EVENTS_CRCERROR_Pos    (0UL) /*!< Position of EVENTS_CRCERROR field. */
#define RADIO_EVENTS_CRCERROR_EVENTS_CRCERROR_Msk                                                  \
  (0x1UL << RADIO_EVENTS_CRCERROR_EVENTS_CRCERROR_Pos) /*!< Bit mask of EVENTS_CRCERROR field. */
#define RADIO_EVENTS_CRCERROR_EVENTS_CRCERROR_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_CRCERROR_EVENTS_CRCERROR_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_FRAMESTART */
/* Description: IEEE 802.15.4 length field received */

/* Bit 0 : IEEE 802.15.4 length field received */
#define RADIO_EVENTS_FRAMESTART_EVENTS_FRAMESTART_Pos                                              \
  (0UL) /*!< Position of EVENTS_FRAMESTART field. */
#define RADIO_EVENTS_FRAMESTART_EVENTS_FRAMESTART_Msk                                              \
  (0x1UL                                                                                           \
   << RADIO_EVENTS_FRAMESTART_EVENTS_FRAMESTART_Pos) /*!< Bit mask of EVENTS_FRAMESTART field. */
#define RADIO_EVENTS_FRAMESTART_EVENTS_FRAMESTART_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_FRAMESTART_EVENTS_FRAMESTART_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_EDEND */
/* Description: Sampling of energy detection complete. A new ED sample is ready for readout from the RADIO.EDSAMPLE register */

/* Bit 0 : Sampling of energy detection complete. A new ED sample is ready for readout from the RADIO.EDSAMPLE register */
#define RADIO_EVENTS_EDEND_EVENTS_EDEND_Pos                    (0UL) /*!< Position of EVENTS_EDEND field. */
#define RADIO_EVENTS_EDEND_EVENTS_EDEND_Msk                                                        \
  (0x1UL << RADIO_EVENTS_EDEND_EVENTS_EDEND_Pos)           /*!< Bit mask of EVENTS_EDEND field. */
#define RADIO_EVENTS_EDEND_EVENTS_EDEND_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_EDEND_EVENTS_EDEND_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_EDSTOPPED */
/* Description: The sampling of energy detection has stopped */

/* Bit 0 : The sampling of energy detection has stopped */
#define RADIO_EVENTS_EDSTOPPED_EVENTS_EDSTOPPED_Pos                                                \
  (0UL) /*!< Position of EVENTS_EDSTOPPED field. */
#define RADIO_EVENTS_EDSTOPPED_EVENTS_EDSTOPPED_Msk                                                \
  (0x1UL << RADIO_EVENTS_EDSTOPPED_EVENTS_EDSTOPPED_Pos) /*!< Bit mask of EVENTS_EDSTOPPED field. */
#define RADIO_EVENTS_EDSTOPPED_EVENTS_EDSTOPPED_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_EDSTOPPED_EVENTS_EDSTOPPED_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_CCAIDLE */
/* Description: Wireless medium in idle - clear to send */

/* Bit 0 : Wireless medium in idle - clear to send */
#define RADIO_EVENTS_CCAIDLE_EVENTS_CCAIDLE_Pos              (0UL) /*!< Position of EVENTS_CCAIDLE field. */
#define RADIO_EVENTS_CCAIDLE_EVENTS_CCAIDLE_Msk                                                    \
  (0x1UL << RADIO_EVENTS_CCAIDLE_EVENTS_CCAIDLE_Pos) /*!< Bit mask of EVENTS_CCAIDLE field. */
#define RADIO_EVENTS_CCAIDLE_EVENTS_CCAIDLE_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_CCAIDLE_EVENTS_CCAIDLE_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_CCABUSY */
/* Description: Wireless medium busy - do not send */

/* Bit 0 : Wireless medium busy - do not send */
#define RADIO_EVENTS_CCABUSY_EVENTS_CCABUSY_Pos          (0UL) /*!< Position of EVENTS_CCABUSY field. */
#define RADIO_EVENTS_CCABUSY_EVENTS_CCABUSY_Msk                                                    \
  (0x1UL << RADIO_EVENTS_CCABUSY_EVENTS_CCABUSY_Pos) /*!< Bit mask of EVENTS_CCABUSY field. */
#define RADIO_EVENTS_CCABUSY_EVENTS_CCABUSY_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_CCABUSY_EVENTS_CCABUSY_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_CCASTOPPED */
/* Description: The CCA has stopped */

/* Bit 0 : The CCA has stopped */
#define RADIO_EVENTS_CCASTOPPED_EVENTS_CCASTOPPED_Pos                                              \
  (0UL) /*!< Position of EVENTS_CCASTOPPED field. */
#define RADIO_EVENTS_CCASTOPPED_EVENTS_CCASTOPPED_Msk                                              \
  (0x1UL                                                                                           \
   << RADIO_EVENTS_CCASTOPPED_EVENTS_CCASTOPPED_Pos) /*!< Bit mask of EVENTS_CCASTOPPED field. */
#define RADIO_EVENTS_CCASTOPPED_EVENTS_CCASTOPPED_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_CCASTOPPED_EVENTS_CCASTOPPED_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_RATEBOOST */
/* Description: Ble_LR CI field received, receive mode is changed from Ble_LR125Kbit to Ble_LR500Kbit. */

/* Bit 0 : Ble_LR CI field received, receive mode is changed from Ble_LR125Kbit to Ble_LR500Kbit. */
#define RADIO_EVENTS_RATEBOOST_EVENTS_RATEBOOST_Pos                                                \
  (0UL) /*!< Position of EVENTS_RATEBOOST field. */
#define RADIO_EVENTS_RATEBOOST_EVENTS_RATEBOOST_Msk                                                \
  (0x1UL << RADIO_EVENTS_RATEBOOST_EVENTS_RATEBOOST_Pos) /*!< Bit mask of EVENTS_RATEBOOST field. */
#define RADIO_EVENTS_RATEBOOST_EVENTS_RATEBOOST_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_RATEBOOST_EVENTS_RATEBOOST_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_TXREADY */
/* Description: RADIO has ramped up and is ready to be started TX path */

/* Bit 0 : RADIO has ramped up and is ready to be started TX path */
#define RADIO_EVENTS_TXREADY_EVENTS_TXREADY_Pos              (0UL) /*!< Position of EVENTS_TXREADY field. */
#define RADIO_EVENTS_TXREADY_EVENTS_TXREADY_Msk                                                    \
  (0x1UL << RADIO_EVENTS_TXREADY_EVENTS_TXREADY_Pos) /*!< Bit mask of EVENTS_TXREADY field. */
#define RADIO_EVENTS_TXREADY_EVENTS_TXREADY_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_TXREADY_EVENTS_TXREADY_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_RXREADY */
/* Description: RADIO has ramped up and is ready to be started RX path */

/* Bit 0 : RADIO has ramped up and is ready to be started RX path */
#define RADIO_EVENTS_RXREADY_EVENTS_RXREADY_Pos          (0UL) /*!< Position of EVENTS_RXREADY field. */
#define RADIO_EVENTS_RXREADY_EVENTS_RXREADY_Msk                                                    \
  (0x1UL << RADIO_EVENTS_RXREADY_EVENTS_RXREADY_Pos) /*!< Bit mask of EVENTS_RXREADY field. */
#define RADIO_EVENTS_RXREADY_EVENTS_RXREADY_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_RXREADY_EVENTS_RXREADY_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_MHRMATCH */
/* Description: MAC header match found */

/* Bit 0 : MAC header match found */
#define RADIO_EVENTS_MHRMATCH_EVENTS_MHRMATCH_Pos        (0UL) /*!< Position of EVENTS_MHRMATCH field. */
#define RADIO_EVENTS_MHRMATCH_EVENTS_MHRMATCH_Msk                                                  \
  (0x1UL << RADIO_EVENTS_MHRMATCH_EVENTS_MHRMATCH_Pos) /*!< Bit mask of EVENTS_MHRMATCH field. */
#define RADIO_EVENTS_MHRMATCH_EVENTS_MHRMATCH_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_MHRMATCH_EVENTS_MHRMATCH_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_SYNC */
/* Description: Preamble indicator */

/* Bit 0 : Preamble indicator */
#define RADIO_EVENTS_SYNC_EVENTS_SYNC_Pos                  (0UL) /*!< Position of EVENTS_SYNC field. */
#define RADIO_EVENTS_SYNC_EVENTS_SYNC_Msk                                                          \
  (0x1UL << RADIO_EVENTS_SYNC_EVENTS_SYNC_Pos)           /*!< Bit mask of EVENTS_SYNC field. */
#define RADIO_EVENTS_SYNC_EVENTS_SYNC_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_SYNC_EVENTS_SYNC_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_PHYEND */
/* Description: Generated when last bit is sent on air, or received from air */

/* Bit 0 : Generated when last bit is sent on air, or received from air */
#define RADIO_EVENTS_PHYEND_EVENTS_PHYEND_Pos      (0UL) /*!< Position of EVENTS_PHYEND field. */
#define RADIO_EVENTS_PHYEND_EVENTS_PHYEND_Msk                                                      \
  (0x1UL << RADIO_EVENTS_PHYEND_EVENTS_PHYEND_Pos) /*!< Bit mask of EVENTS_PHYEND field. */
#define RADIO_EVENTS_PHYEND_EVENTS_PHYEND_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_PHYEND_EVENTS_PHYEND_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_EVENTS_CTEPRESENT */
/* Description: CTE is present (early warning right after receiving CTEInfo byte) */

/* Bit 0 : CTE is present (early warning right after receiving CTEInfo byte) */
#define RADIO_EVENTS_CTEPRESENT_EVENTS_CTEPRESENT_Pos                                              \
  (0UL) /*!< Position of EVENTS_CTEPRESENT field. */
#define RADIO_EVENTS_CTEPRESENT_EVENTS_CTEPRESENT_Msk                                              \
  (0x1UL                                                                                           \
   << RADIO_EVENTS_CTEPRESENT_EVENTS_CTEPRESENT_Pos) /*!< Bit mask of EVENTS_CTEPRESENT field. */
#define RADIO_EVENTS_CTEPRESENT_EVENTS_CTEPRESENT_NotGenerated (0UL) /*!< Event not generated */
#define RADIO_EVENTS_CTEPRESENT_EVENTS_CTEPRESENT_Generated    (1UL) /*!< Event generated */

/* Register: RADIO_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 21 : Shortcut between event PHYEND and task START */
#define RADIO_SHORTS_PHYEND_START_Pos                          (21UL) /*!< Position of PHYEND_START field. */
#define RADIO_SHORTS_PHYEND_START_Msk                                                              \
  (0x1UL << RADIO_SHORTS_PHYEND_START_Pos)       /*!< Bit mask of PHYEND_START field. */
#define RADIO_SHORTS_PHYEND_START_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_PHYEND_START_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 20 : Shortcut between event PHYEND and task DISABLE */
#define RADIO_SHORTS_PHYEND_DISABLE_Pos    (20UL) /*!< Position of PHYEND_DISABLE field. */
#define RADIO_SHORTS_PHYEND_DISABLE_Msk                                                            \
  (0x1UL << RADIO_SHORTS_PHYEND_DISABLE_Pos)       /*!< Bit mask of PHYEND_DISABLE field. */
#define RADIO_SHORTS_PHYEND_DISABLE_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_PHYEND_DISABLE_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 19 : Shortcut between event RXREADY and task START */
#define RADIO_SHORTS_RXREADY_START_Pos       (19UL) /*!< Position of RXREADY_START field. */
#define RADIO_SHORTS_RXREADY_START_Msk                                                             \
  (0x1UL << RADIO_SHORTS_RXREADY_START_Pos)       /*!< Bit mask of RXREADY_START field. */
#define RADIO_SHORTS_RXREADY_START_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_RXREADY_START_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 18 : Shortcut between event TXREADY and task START */
#define RADIO_SHORTS_TXREADY_START_Pos      (18UL) /*!< Position of TXREADY_START field. */
#define RADIO_SHORTS_TXREADY_START_Msk                                                             \
  (0x1UL << RADIO_SHORTS_TXREADY_START_Pos)       /*!< Bit mask of TXREADY_START field. */
#define RADIO_SHORTS_TXREADY_START_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_TXREADY_START_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 17 : Shortcut between event CCAIDLE and task STOP */
#define RADIO_SHORTS_CCAIDLE_STOP_Pos       (17UL) /*!< Position of CCAIDLE_STOP field. */
#define RADIO_SHORTS_CCAIDLE_STOP_Msk                                                              \
  (0x1UL << RADIO_SHORTS_CCAIDLE_STOP_Pos)       /*!< Bit mask of CCAIDLE_STOP field. */
#define RADIO_SHORTS_CCAIDLE_STOP_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_CCAIDLE_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 16 : Shortcut between event EDEND and task DISABLE */
#define RADIO_SHORTS_EDEND_DISABLE_Pos     (16UL) /*!< Position of EDEND_DISABLE field. */
#define RADIO_SHORTS_EDEND_DISABLE_Msk                                                             \
  (0x1UL << RADIO_SHORTS_EDEND_DISABLE_Pos)       /*!< Bit mask of EDEND_DISABLE field. */
#define RADIO_SHORTS_EDEND_DISABLE_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_EDEND_DISABLE_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 15 : Shortcut between event READY and task EDSTART */
#define RADIO_SHORTS_READY_EDSTART_Pos      (15UL) /*!< Position of READY_EDSTART field. */
#define RADIO_SHORTS_READY_EDSTART_Msk                                                             \
  (0x1UL << RADIO_SHORTS_READY_EDSTART_Pos)       /*!< Bit mask of READY_EDSTART field. */
#define RADIO_SHORTS_READY_EDSTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_READY_EDSTART_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 14 : Shortcut between event FRAMESTART and task BCSTART */
#define RADIO_SHORTS_FRAMESTART_BCSTART_Pos (14UL) /*!< Position of FRAMESTART_BCSTART field. */
#define RADIO_SHORTS_FRAMESTART_BCSTART_Msk                                                        \
  (0x1UL << RADIO_SHORTS_FRAMESTART_BCSTART_Pos)       /*!< Bit mask of FRAMESTART_BCSTART field. */
#define RADIO_SHORTS_FRAMESTART_BCSTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_FRAMESTART_BCSTART_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 13 : Shortcut between event CCABUSY and task DISABLE */
#define RADIO_SHORTS_CCABUSY_DISABLE_Pos         (13UL) /*!< Position of CCABUSY_DISABLE field. */
#define RADIO_SHORTS_CCABUSY_DISABLE_Msk                                                           \
  (0x1UL << RADIO_SHORTS_CCABUSY_DISABLE_Pos)       /*!< Bit mask of CCABUSY_DISABLE field. */
#define RADIO_SHORTS_CCABUSY_DISABLE_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_CCABUSY_DISABLE_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 12 : Shortcut between event CCAIDLE and task TXEN */
#define RADIO_SHORTS_CCAIDLE_TXEN_Pos         (12UL) /*!< Position of CCAIDLE_TXEN field. */
#define RADIO_SHORTS_CCAIDLE_TXEN_Msk                                                              \
  (0x1UL << RADIO_SHORTS_CCAIDLE_TXEN_Pos)       /*!< Bit mask of CCAIDLE_TXEN field. */
#define RADIO_SHORTS_CCAIDLE_TXEN_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_CCAIDLE_TXEN_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 11 : Shortcut between event RXREADY and task CCASTART */
#define RADIO_SHORTS_RXREADY_CCASTART_Pos  (11UL) /*!< Position of RXREADY_CCASTART field. */
#define RADIO_SHORTS_RXREADY_CCASTART_Msk                                                          \
  (0x1UL << RADIO_SHORTS_RXREADY_CCASTART_Pos)       /*!< Bit mask of RXREADY_CCASTART field. */
#define RADIO_SHORTS_RXREADY_CCASTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_RXREADY_CCASTART_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 8 : Shortcut between event DISABLED and task RSSISTOP */
#define RADIO_SHORTS_DISABLED_RSSISTOP_Pos     (8UL) /*!< Position of DISABLED_RSSISTOP field. */
#define RADIO_SHORTS_DISABLED_RSSISTOP_Msk                                                         \
  (0x1UL << RADIO_SHORTS_DISABLED_RSSISTOP_Pos)       /*!< Bit mask of DISABLED_RSSISTOP field. */
#define RADIO_SHORTS_DISABLED_RSSISTOP_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_DISABLED_RSSISTOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 6 : Shortcut between event ADDRESS and task BCSTART */
#define RADIO_SHORTS_ADDRESS_BCSTART_Pos        (6UL) /*!< Position of ADDRESS_BCSTART field. */
#define RADIO_SHORTS_ADDRESS_BCSTART_Msk                                                           \
  (0x1UL << RADIO_SHORTS_ADDRESS_BCSTART_Pos)       /*!< Bit mask of ADDRESS_BCSTART field. */
#define RADIO_SHORTS_ADDRESS_BCSTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_ADDRESS_BCSTART_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 5 : Shortcut between event END and task START */
#define RADIO_SHORTS_END_START_Pos            (5UL) /*!< Position of END_START field. */
#define RADIO_SHORTS_END_START_Msk                                                                 \
  (0x1UL << RADIO_SHORTS_END_START_Pos)          /*!< Bit mask of END_START field. */
#define RADIO_SHORTS_END_START_Disabled    (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_END_START_Enabled     (1UL) /*!< Enable shortcut */

/* Bit 4 : Shortcut between event ADDRESS and task RSSISTART */
#define RADIO_SHORTS_ADDRESS_RSSISTART_Pos (4UL) /*!< Position of ADDRESS_RSSISTART field. */
#define RADIO_SHORTS_ADDRESS_RSSISTART_Msk                                                         \
  (0x1UL << RADIO_SHORTS_ADDRESS_RSSISTART_Pos)       /*!< Bit mask of ADDRESS_RSSISTART field. */
#define RADIO_SHORTS_ADDRESS_RSSISTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_ADDRESS_RSSISTART_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between event DISABLED and task RXEN */
#define RADIO_SHORTS_DISABLED_RXEN_Pos          (3UL) /*!< Position of DISABLED_RXEN field. */
#define RADIO_SHORTS_DISABLED_RXEN_Msk                                                             \
  (0x1UL << RADIO_SHORTS_DISABLED_RXEN_Pos)       /*!< Bit mask of DISABLED_RXEN field. */
#define RADIO_SHORTS_DISABLED_RXEN_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_DISABLED_RXEN_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between event DISABLED and task TXEN */
#define RADIO_SHORTS_DISABLED_TXEN_Pos      (2UL) /*!< Position of DISABLED_TXEN field. */
#define RADIO_SHORTS_DISABLED_TXEN_Msk                                                             \
  (0x1UL << RADIO_SHORTS_DISABLED_TXEN_Pos)       /*!< Bit mask of DISABLED_TXEN field. */
#define RADIO_SHORTS_DISABLED_TXEN_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_DISABLED_TXEN_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between event END and task DISABLE */
#define RADIO_SHORTS_END_DISABLE_Pos        (1UL) /*!< Position of END_DISABLE field. */
#define RADIO_SHORTS_END_DISABLE_Msk                                                               \
  (0x1UL << RADIO_SHORTS_END_DISABLE_Pos)       /*!< Bit mask of END_DISABLE field. */
#define RADIO_SHORTS_END_DISABLE_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_END_DISABLE_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between event READY and task START */
#define RADIO_SHORTS_READY_START_Pos      (0UL) /*!< Position of READY_START field. */
#define RADIO_SHORTS_READY_START_Msk                                                               \
  (0x1UL << RADIO_SHORTS_READY_START_Pos)       /*!< Bit mask of READY_START field. */
#define RADIO_SHORTS_READY_START_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_READY_START_Enabled  (1UL) /*!< Enable shortcut */

/* Register: RADIO_INTENSET */
/* Description: Enable interrupt */

/* Bit 28 : Write '1' to enable interrupt for event CTEPRESENT */
#define RADIO_INTENSET_CTEPRESENT_Pos     (28UL) /*!< Position of CTEPRESENT field. */
#define RADIO_INTENSET_CTEPRESENT_Msk                                                              \
  (0x1UL << RADIO_INTENSET_CTEPRESENT_Pos)       /*!< Bit mask of CTEPRESENT field. */
#define RADIO_INTENSET_CTEPRESENT_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CTEPRESENT_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CTEPRESENT_Set      (1UL) /*!< Enable */

/* Bit 27 : Write '1' to enable interrupt for event PHYEND */
#define RADIO_INTENSET_PHYEND_Pos          (27UL) /*!< Position of PHYEND field. */
#define RADIO_INTENSET_PHYEND_Msk                                                                  \
  (0x1UL << RADIO_INTENSET_PHYEND_Pos)       /*!< Bit mask of PHYEND field. */
#define RADIO_INTENSET_PHYEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_PHYEND_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_PHYEND_Set      (1UL) /*!< Enable */

/* Bit 26 : Write '1' to enable interrupt for event SYNC */
#define RADIO_INTENSET_SYNC_Pos        (26UL) /*!< Position of SYNC field. */
#define RADIO_INTENSET_SYNC_Msk        (0x1UL << RADIO_INTENSET_SYNC_Pos) /*!< Bit mask of SYNC field. */
#define RADIO_INTENSET_SYNC_Disabled   (0UL)                              /*!< Read: Disabled */
#define RADIO_INTENSET_SYNC_Enabled    (1UL)                              /*!< Read: Enabled */
#define RADIO_INTENSET_SYNC_Set        (1UL)                              /*!< Enable */

/* Bit 23 : Write '1' to enable interrupt for event MHRMATCH */
#define RADIO_INTENSET_MHRMATCH_Pos    (23UL) /*!< Position of MHRMATCH field. */
#define RADIO_INTENSET_MHRMATCH_Msk                                                                \
  (0x1UL << RADIO_INTENSET_MHRMATCH_Pos)       /*!< Bit mask of MHRMATCH field. */
#define RADIO_INTENSET_MHRMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_MHRMATCH_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_MHRMATCH_Set      (1UL) /*!< Enable */

/* Bit 22 : Write '1' to enable interrupt for event RXREADY */
#define RADIO_INTENSET_RXREADY_Pos       (22UL) /*!< Position of RXREADY field. */
#define RADIO_INTENSET_RXREADY_Msk                                                                 \
  (0x1UL << RADIO_INTENSET_RXREADY_Pos)       /*!< Bit mask of RXREADY field. */
#define RADIO_INTENSET_RXREADY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_RXREADY_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_RXREADY_Set      (1UL) /*!< Enable */

/* Bit 21 : Write '1' to enable interrupt for event TXREADY */
#define RADIO_INTENSET_TXREADY_Pos      (21UL) /*!< Position of TXREADY field. */
#define RADIO_INTENSET_TXREADY_Msk                                                                 \
  (0x1UL << RADIO_INTENSET_TXREADY_Pos)       /*!< Bit mask of TXREADY field. */
#define RADIO_INTENSET_TXREADY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_TXREADY_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_TXREADY_Set      (1UL) /*!< Enable */

/* Bit 20 : Write '1' to enable interrupt for event RATEBOOST */
#define RADIO_INTENSET_RATEBOOST_Pos    (20UL) /*!< Position of RATEBOOST field. */
#define RADIO_INTENSET_RATEBOOST_Msk                                                               \
  (0x1UL << RADIO_INTENSET_RATEBOOST_Pos)       /*!< Bit mask of RATEBOOST field. */
#define RADIO_INTENSET_RATEBOOST_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_RATEBOOST_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_RATEBOOST_Set      (1UL) /*!< Enable */

/* Bit 19 : Write '1' to enable interrupt for event CCASTOPPED */
#define RADIO_INTENSET_CCASTOPPED_Pos     (19UL) /*!< Position of CCASTOPPED field. */
#define RADIO_INTENSET_CCASTOPPED_Msk                                                              \
  (0x1UL << RADIO_INTENSET_CCASTOPPED_Pos)       /*!< Bit mask of CCASTOPPED field. */
#define RADIO_INTENSET_CCASTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CCASTOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CCASTOPPED_Set      (1UL) /*!< Enable */

/* Bit 18 : Write '1' to enable interrupt for event CCABUSY */
#define RADIO_INTENSET_CCABUSY_Pos         (18UL) /*!< Position of CCABUSY field. */
#define RADIO_INTENSET_CCABUSY_Msk                                                                 \
  (0x1UL << RADIO_INTENSET_CCABUSY_Pos)       /*!< Bit mask of CCABUSY field. */
#define RADIO_INTENSET_CCABUSY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CCABUSY_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CCABUSY_Set      (1UL) /*!< Enable */

/* Bit 17 : Write '1' to enable interrupt for event CCAIDLE */
#define RADIO_INTENSET_CCAIDLE_Pos      (17UL) /*!< Position of CCAIDLE field. */
#define RADIO_INTENSET_CCAIDLE_Msk                                                                 \
  (0x1UL << RADIO_INTENSET_CCAIDLE_Pos)       /*!< Bit mask of CCAIDLE field. */
#define RADIO_INTENSET_CCAIDLE_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CCAIDLE_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CCAIDLE_Set      (1UL) /*!< Enable */

/* Bit 16 : Write '1' to enable interrupt for event EDSTOPPED */
#define RADIO_INTENSET_EDSTOPPED_Pos    (16UL) /*!< Position of EDSTOPPED field. */
#define RADIO_INTENSET_EDSTOPPED_Msk                                                               \
  (0x1UL << RADIO_INTENSET_EDSTOPPED_Pos)       /*!< Bit mask of EDSTOPPED field. */
#define RADIO_INTENSET_EDSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_EDSTOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_EDSTOPPED_Set      (1UL) /*!< Enable */

/* Bit 15 : Write '1' to enable interrupt for event EDEND */
#define RADIO_INTENSET_EDEND_Pos          (15UL) /*!< Position of EDEND field. */
#define RADIO_INTENSET_EDEND_Msk                                                                   \
  (0x1UL << RADIO_INTENSET_EDEND_Pos)       /*!< Bit mask of EDEND field. */
#define RADIO_INTENSET_EDEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_EDEND_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_EDEND_Set      (1UL) /*!< Enable */

/* Bit 14 : Write '1' to enable interrupt for event FRAMESTART */
#define RADIO_INTENSET_FRAMESTART_Pos (14UL) /*!< Position of FRAMESTART field. */
#define RADIO_INTENSET_FRAMESTART_Msk                                                              \
  (0x1UL << RADIO_INTENSET_FRAMESTART_Pos)       /*!< Bit mask of FRAMESTART field. */
#define RADIO_INTENSET_FRAMESTART_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_FRAMESTART_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_FRAMESTART_Set      (1UL) /*!< Enable */

/* Bit 13 : Write '1' to enable interrupt for event CRCERROR */
#define RADIO_INTENSET_CRCERROR_Pos        (13UL) /*!< Position of CRCERROR field. */
#define RADIO_INTENSET_CRCERROR_Msk                                                                \
  (0x1UL << RADIO_INTENSET_CRCERROR_Pos)       /*!< Bit mask of CRCERROR field. */
#define RADIO_INTENSET_CRCERROR_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CRCERROR_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CRCERROR_Set      (1UL) /*!< Enable */

/* Bit 12 : Write '1' to enable interrupt for event CRCOK */
#define RADIO_INTENSET_CRCOK_Pos         (12UL) /*!< Position of CRCOK field. */
#define RADIO_INTENSET_CRCOK_Msk                                                                   \
  (0x1UL << RADIO_INTENSET_CRCOK_Pos)       /*!< Bit mask of CRCOK field. */
#define RADIO_INTENSET_CRCOK_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CRCOK_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CRCOK_Set      (1UL) /*!< Enable */

/* Bit 10 : Write '1' to enable interrupt for event BCMATCH */
#define RADIO_INTENSET_BCMATCH_Pos    (10UL) /*!< Position of BCMATCH field. */
#define RADIO_INTENSET_BCMATCH_Msk                                                                 \
  (0x1UL << RADIO_INTENSET_BCMATCH_Pos)       /*!< Bit mask of BCMATCH field. */
#define RADIO_INTENSET_BCMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_BCMATCH_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_BCMATCH_Set      (1UL) /*!< Enable */

/* Bit 7 : Write '1' to enable interrupt for event RSSIEND */
#define RADIO_INTENSET_RSSIEND_Pos      (7UL) /*!< Position of RSSIEND field. */
#define RADIO_INTENSET_RSSIEND_Msk                                                                 \
  (0x1UL << RADIO_INTENSET_RSSIEND_Pos)       /*!< Bit mask of RSSIEND field. */
#define RADIO_INTENSET_RSSIEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_RSSIEND_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_RSSIEND_Set      (1UL) /*!< Enable */

/* Bit 6 : Write '1' to enable interrupt for event DEVMISS */
#define RADIO_INTENSET_DEVMISS_Pos      (6UL) /*!< Position of DEVMISS field. */
#define RADIO_INTENSET_DEVMISS_Msk                                                                 \
  (0x1UL << RADIO_INTENSET_DEVMISS_Pos)       /*!< Bit mask of DEVMISS field. */
#define RADIO_INTENSET_DEVMISS_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_DEVMISS_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_DEVMISS_Set      (1UL) /*!< Enable */

/* Bit 5 : Write '1' to enable interrupt for event DEVMATCH */
#define RADIO_INTENSET_DEVMATCH_Pos     (5UL) /*!< Position of DEVMATCH field. */
#define RADIO_INTENSET_DEVMATCH_Msk                                                                \
  (0x1UL << RADIO_INTENSET_DEVMATCH_Pos)       /*!< Bit mask of DEVMATCH field. */
#define RADIO_INTENSET_DEVMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_DEVMATCH_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_DEVMATCH_Set      (1UL) /*!< Enable */

/* Bit 4 : Write '1' to enable interrupt for event DISABLED */
#define RADIO_INTENSET_DISABLED_Pos      (4UL) /*!< Position of DISABLED field. */
#define RADIO_INTENSET_DISABLED_Msk                                                                \
  (0x1UL << RADIO_INTENSET_DISABLED_Pos)       /*!< Bit mask of DISABLED field. */
#define RADIO_INTENSET_DISABLED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_DISABLED_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_DISABLED_Set      (1UL) /*!< Enable */

/* Bit 3 : Write '1' to enable interrupt for event END */
#define RADIO_INTENSET_END_Pos           (3UL) /*!< Position of END field. */
#define RADIO_INTENSET_END_Msk           (0x1UL << RADIO_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define RADIO_INTENSET_END_Disabled      (0UL)                             /*!< Read: Disabled */
#define RADIO_INTENSET_END_Enabled       (1UL)                             /*!< Read: Enabled */
#define RADIO_INTENSET_END_Set           (1UL)                             /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event PAYLOAD */
#define RADIO_INTENSET_PAYLOAD_Pos       (2UL) /*!< Position of PAYLOAD field. */
#define RADIO_INTENSET_PAYLOAD_Msk                                                                 \
  (0x1UL << RADIO_INTENSET_PAYLOAD_Pos)       /*!< Bit mask of PAYLOAD field. */
#define RADIO_INTENSET_PAYLOAD_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_PAYLOAD_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_PAYLOAD_Set      (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event ADDRESS */
#define RADIO_INTENSET_ADDRESS_Pos      (1UL) /*!< Position of ADDRESS field. */
#define RADIO_INTENSET_ADDRESS_Msk                                                                 \
  (0x1UL << RADIO_INTENSET_ADDRESS_Pos)       /*!< Bit mask of ADDRESS field. */
#define RADIO_INTENSET_ADDRESS_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_ADDRESS_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_ADDRESS_Set      (1UL) /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event READY */
#define RADIO_INTENSET_READY_Pos        (0UL) /*!< Position of READY field. */
#define RADIO_INTENSET_READY_Msk                                                                   \
  (0x1UL << RADIO_INTENSET_READY_Pos)       /*!< Bit mask of READY field. */
#define RADIO_INTENSET_READY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_READY_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_READY_Set      (1UL) /*!< Enable */

/* Register: RADIO_INTENCLR */
/* Description: Disable interrupt */

/* Bit 28 : Write '1' to disable interrupt for event CTEPRESENT */
#define RADIO_INTENCLR_CTEPRESENT_Pos (28UL) /*!< Position of CTEPRESENT field. */
#define RADIO_INTENCLR_CTEPRESENT_Msk                                                              \
  (0x1UL << RADIO_INTENCLR_CTEPRESENT_Pos)       /*!< Bit mask of CTEPRESENT field. */
#define RADIO_INTENCLR_CTEPRESENT_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CTEPRESENT_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CTEPRESENT_Clear    (1UL) /*!< Disable */

/* Bit 27 : Write '1' to disable interrupt for event PHYEND */
#define RADIO_INTENCLR_PHYEND_Pos          (27UL) /*!< Position of PHYEND field. */
#define RADIO_INTENCLR_PHYEND_Msk                                                                  \
  (0x1UL << RADIO_INTENCLR_PHYEND_Pos)       /*!< Bit mask of PHYEND field. */
#define RADIO_INTENCLR_PHYEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_PHYEND_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_PHYEND_Clear    (1UL) /*!< Disable */

/* Bit 26 : Write '1' to disable interrupt for event SYNC */
#define RADIO_INTENCLR_SYNC_Pos        (26UL) /*!< Position of SYNC field. */
#define RADIO_INTENCLR_SYNC_Msk        (0x1UL << RADIO_INTENCLR_SYNC_Pos) /*!< Bit mask of SYNC field. */
#define RADIO_INTENCLR_SYNC_Disabled   (0UL)                              /*!< Read: Disabled */
#define RADIO_INTENCLR_SYNC_Enabled    (1UL)                              /*!< Read: Enabled */
#define RADIO_INTENCLR_SYNC_Clear      (1UL)                              /*!< Disable */

/* Bit 23 : Write '1' to disable interrupt for event MHRMATCH */
#define RADIO_INTENCLR_MHRMATCH_Pos    (23UL) /*!< Position of MHRMATCH field. */
#define RADIO_INTENCLR_MHRMATCH_Msk                                                                \
  (0x1UL << RADIO_INTENCLR_MHRMATCH_Pos)       /*!< Bit mask of MHRMATCH field. */
#define RADIO_INTENCLR_MHRMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_MHRMATCH_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_MHRMATCH_Clear    (1UL) /*!< Disable */

/* Bit 22 : Write '1' to disable interrupt for event RXREADY */
#define RADIO_INTENCLR_RXREADY_Pos       (22UL) /*!< Position of RXREADY field. */
#define RADIO_INTENCLR_RXREADY_Msk                                                                 \
  (0x1UL << RADIO_INTENCLR_RXREADY_Pos)       /*!< Bit mask of RXREADY field. */
#define RADIO_INTENCLR_RXREADY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_RXREADY_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_RXREADY_Clear    (1UL) /*!< Disable */

/* Bit 21 : Write '1' to disable interrupt for event TXREADY */
#define RADIO_INTENCLR_TXREADY_Pos      (21UL) /*!< Position of TXREADY field. */
#define RADIO_INTENCLR_TXREADY_Msk                                                                 \
  (0x1UL << RADIO_INTENCLR_TXREADY_Pos)       /*!< Bit mask of TXREADY field. */
#define RADIO_INTENCLR_TXREADY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_TXREADY_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_TXREADY_Clear    (1UL) /*!< Disable */

/* Bit 20 : Write '1' to disable interrupt for event RATEBOOST */
#define RADIO_INTENCLR_RATEBOOST_Pos    (20UL) /*!< Position of RATEBOOST field. */
#define RADIO_INTENCLR_RATEBOOST_Msk                                                               \
  (0x1UL << RADIO_INTENCLR_RATEBOOST_Pos)       /*!< Bit mask of RATEBOOST field. */
#define RADIO_INTENCLR_RATEBOOST_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_RATEBOOST_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_RATEBOOST_Clear    (1UL) /*!< Disable */

/* Bit 19 : Write '1' to disable interrupt for event CCASTOPPED */
#define RADIO_INTENCLR_CCASTOPPED_Pos     (19UL) /*!< Position of CCASTOPPED field. */
#define RADIO_INTENCLR_CCASTOPPED_Msk                                                              \
  (0x1UL << RADIO_INTENCLR_CCASTOPPED_Pos)       /*!< Bit mask of CCASTOPPED field. */
#define RADIO_INTENCLR_CCASTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CCASTOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CCASTOPPED_Clear    (1UL) /*!< Disable */

/* Bit 18 : Write '1' to disable interrupt for event CCABUSY */
#define RADIO_INTENCLR_CCABUSY_Pos         (18UL) /*!< Position of CCABUSY field. */
#define RADIO_INTENCLR_CCABUSY_Msk                                                                 \
  (0x1UL << RADIO_INTENCLR_CCABUSY_Pos)       /*!< Bit mask of CCABUSY field. */
#define RADIO_INTENCLR_CCABUSY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CCABUSY_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CCABUSY_Clear    (1UL) /*!< Disable */

/* Bit 17 : Write '1' to disable interrupt for event CCAIDLE */
#define RADIO_INTENCLR_CCAIDLE_Pos      (17UL) /*!< Position of CCAIDLE field. */
#define RADIO_INTENCLR_CCAIDLE_Msk                                                                 \
  (0x1UL << RADIO_INTENCLR_CCAIDLE_Pos)       /*!< Bit mask of CCAIDLE field. */
#define RADIO_INTENCLR_CCAIDLE_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CCAIDLE_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CCAIDLE_Clear    (1UL) /*!< Disable */

/* Bit 16 : Write '1' to disable interrupt for event EDSTOPPED */
#define RADIO_INTENCLR_EDSTOPPED_Pos    (16UL) /*!< Position of EDSTOPPED field. */
#define RADIO_INTENCLR_EDSTOPPED_Msk                                                               \
  (0x1UL << RADIO_INTENCLR_EDSTOPPED_Pos)       /*!< Bit mask of EDSTOPPED field. */
#define RADIO_INTENCLR_EDSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_EDSTOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_EDSTOPPED_Clear    (1UL) /*!< Disable */

/* Bit 15 : Write '1' to disable interrupt for event EDEND */
#define RADIO_INTENCLR_EDEND_Pos          (15UL) /*!< Position of EDEND field. */
#define RADIO_INTENCLR_EDEND_Msk                                                                   \
  (0x1UL << RADIO_INTENCLR_EDEND_Pos)       /*!< Bit mask of EDEND field. */
#define RADIO_INTENCLR_EDEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_EDEND_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_EDEND_Clear    (1UL) /*!< Disable */

/* Bit 14 : Write '1' to disable interrupt for event FRAMESTART */
#define RADIO_INTENCLR_FRAMESTART_Pos (14UL) /*!< Position of FRAMESTART field. */
#define RADIO_INTENCLR_FRAMESTART_Msk                                                              \
  (0x1UL << RADIO_INTENCLR_FRAMESTART_Pos)       /*!< Bit mask of FRAMESTART field. */
#define RADIO_INTENCLR_FRAMESTART_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_FRAMESTART_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_FRAMESTART_Clear    (1UL) /*!< Disable */

/* Bit 13 : Write '1' to disable interrupt for event CRCERROR */
#define RADIO_INTENCLR_CRCERROR_Pos        (13UL) /*!< Position of CRCERROR field. */
#define RADIO_INTENCLR_CRCERROR_Msk                                                                \
  (0x1UL << RADIO_INTENCLR_CRCERROR_Pos)       /*!< Bit mask of CRCERROR field. */
#define RADIO_INTENCLR_CRCERROR_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CRCERROR_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CRCERROR_Clear    (1UL) /*!< Disable */

/* Bit 12 : Write '1' to disable interrupt for event CRCOK */
#define RADIO_INTENCLR_CRCOK_Pos         (12UL) /*!< Position of CRCOK field. */
#define RADIO_INTENCLR_CRCOK_Msk                                                                   \
  (0x1UL << RADIO_INTENCLR_CRCOK_Pos)       /*!< Bit mask of CRCOK field. */
#define RADIO_INTENCLR_CRCOK_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CRCOK_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CRCOK_Clear    (1UL) /*!< Disable */

/* Bit 10 : Write '1' to disable interrupt for event BCMATCH */
#define RADIO_INTENCLR_BCMATCH_Pos    (10UL) /*!< Position of BCMATCH field. */
#define RADIO_INTENCLR_BCMATCH_Msk                                                                 \
  (0x1UL << RADIO_INTENCLR_BCMATCH_Pos)       /*!< Bit mask of BCMATCH field. */
#define RADIO_INTENCLR_BCMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_BCMATCH_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_BCMATCH_Clear    (1UL) /*!< Disable */

/* Bit 7 : Write '1' to disable interrupt for event RSSIEND */
#define RADIO_INTENCLR_RSSIEND_Pos      (7UL) /*!< Position of RSSIEND field. */
#define RADIO_INTENCLR_RSSIEND_Msk                                                                 \
  (0x1UL << RADIO_INTENCLR_RSSIEND_Pos)       /*!< Bit mask of RSSIEND field. */
#define RADIO_INTENCLR_RSSIEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_RSSIEND_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_RSSIEND_Clear    (1UL) /*!< Disable */

/* Bit 6 : Write '1' to disable interrupt for event DEVMISS */
#define RADIO_INTENCLR_DEVMISS_Pos      (6UL) /*!< Position of DEVMISS field. */
#define RADIO_INTENCLR_DEVMISS_Msk                                                                 \
  (0x1UL << RADIO_INTENCLR_DEVMISS_Pos)       /*!< Bit mask of DEVMISS field. */
#define RADIO_INTENCLR_DEVMISS_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_DEVMISS_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_DEVMISS_Clear    (1UL) /*!< Disable */

/* Bit 5 : Write '1' to disable interrupt for event DEVMATCH */
#define RADIO_INTENCLR_DEVMATCH_Pos     (5UL) /*!< Position of DEVMATCH field. */
#define RADIO_INTENCLR_DEVMATCH_Msk                                                                \
  (0x1UL << RADIO_INTENCLR_DEVMATCH_Pos)       /*!< Bit mask of DEVMATCH field. */
#define RADIO_INTENCLR_DEVMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_DEVMATCH_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_DEVMATCH_Clear    (1UL) /*!< Disable */

/* Bit 4 : Write '1' to disable interrupt for event DISABLED */
#define RADIO_INTENCLR_DISABLED_Pos      (4UL) /*!< Position of DISABLED field. */
#define RADIO_INTENCLR_DISABLED_Msk                                                                \
  (0x1UL << RADIO_INTENCLR_DISABLED_Pos)       /*!< Bit mask of DISABLED field. */
#define RADIO_INTENCLR_DISABLED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_DISABLED_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_DISABLED_Clear    (1UL) /*!< Disable */

/* Bit 3 : Write '1' to disable interrupt for event END */
#define RADIO_INTENCLR_END_Pos           (3UL) /*!< Position of END field. */
#define RADIO_INTENCLR_END_Msk           (0x1UL << RADIO_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define RADIO_INTENCLR_END_Disabled      (0UL)                             /*!< Read: Disabled */
#define RADIO_INTENCLR_END_Enabled       (1UL)                             /*!< Read: Enabled */
#define RADIO_INTENCLR_END_Clear         (1UL)                             /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event PAYLOAD */
#define RADIO_INTENCLR_PAYLOAD_Pos       (2UL) /*!< Position of PAYLOAD field. */
#define RADIO_INTENCLR_PAYLOAD_Msk                                                                 \
  (0x1UL << RADIO_INTENCLR_PAYLOAD_Pos)       /*!< Bit mask of PAYLOAD field. */
#define RADIO_INTENCLR_PAYLOAD_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_PAYLOAD_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_PAYLOAD_Clear    (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event ADDRESS */
#define RADIO_INTENCLR_ADDRESS_Pos      (1UL) /*!< Position of ADDRESS field. */
#define RADIO_INTENCLR_ADDRESS_Msk                                                                 \
  (0x1UL << RADIO_INTENCLR_ADDRESS_Pos)       /*!< Bit mask of ADDRESS field. */
#define RADIO_INTENCLR_ADDRESS_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_ADDRESS_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_ADDRESS_Clear    (1UL) /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event READY */
#define RADIO_INTENCLR_READY_Pos        (0UL) /*!< Position of READY field. */
#define RADIO_INTENCLR_READY_Msk                                                                   \
  (0x1UL << RADIO_INTENCLR_READY_Pos)       /*!< Bit mask of READY field. */
#define RADIO_INTENCLR_READY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_READY_Enabled  (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_READY_Clear    (1UL) /*!< Disable */

/* Register: RADIO_CRCSTATUS */
/* Description: CRC status */

/* Bit 0 : CRC status of packet received */
#define RADIO_CRCSTATUS_CRCSTATUS_Pos (0UL) /*!< Position of CRCSTATUS field. */
#define RADIO_CRCSTATUS_CRCSTATUS_Msk                                                              \
  (0x1UL << RADIO_CRCSTATUS_CRCSTATUS_Pos)       /*!< Bit mask of CRCSTATUS field. */
#define RADIO_CRCSTATUS_CRCSTATUS_CRCError (0UL) /*!< Packet received with CRC error */
#define RADIO_CRCSTATUS_CRCSTATUS_CRCOk    (1UL) /*!< Packet received with CRC ok */

/* Register: RADIO_RXMATCH */
/* Description: Received address */

/* Bits 2..0 : Received address */
#define RADIO_RXMATCH_RXMATCH_Pos          (0UL) /*!< Position of RXMATCH field. */
#define RADIO_RXMATCH_RXMATCH_Msk                                                                  \
  (0x7UL << RADIO_RXMATCH_RXMATCH_Pos) /*!< Bit mask of RXMATCH field. */

/* Register: RADIO_RXCRC */
/* Description: CRC field of previously received packet */

/* Bits 23..0 : CRC field of previously received packet */
#define RADIO_RXCRC_RXCRC_Pos    (0UL) /*!< Position of RXCRC field. */
#define RADIO_RXCRC_RXCRC_Msk    (0xFFFFFFUL << RADIO_RXCRC_RXCRC_Pos) /*!< Bit mask of RXCRC field. */

/* Register: RADIO_DAI */
/* Description: Device address match index */

/* Bits 2..0 : Device address match index */
#define RADIO_DAI_DAI_Pos        (0UL)                        /*!< Position of DAI field. */
#define RADIO_DAI_DAI_Msk        (0x7UL << RADIO_DAI_DAI_Pos) /*!< Bit mask of DAI field. */

/* Register: RADIO_PDUSTAT */
/* Description: Payload status */

/* Bits 2..1 : Status on what rate packet is received with in Long Range */
#define RADIO_PDUSTAT_CISTAT_Pos (1UL) /*!< Position of CISTAT field. */
#define RADIO_PDUSTAT_CISTAT_Msk                                                                   \
  (0x3UL << RADIO_PDUSTAT_CISTAT_Pos)        /*!< Bit mask of CISTAT field. */
#define RADIO_PDUSTAT_CISTAT_LR125kbit (0UL) /*!< Frame is received at 125 kbps */
#define RADIO_PDUSTAT_CISTAT_LR500kbit (1UL) /*!< Frame is received at 500 kbps */

/* Bit 0 : Status on payload length vs. PCNF1.MAXLEN */
#define RADIO_PDUSTAT_PDUSTAT_Pos      (0UL) /*!< Position of PDUSTAT field. */
#define RADIO_PDUSTAT_PDUSTAT_Msk                                                                  \
  (0x1UL << RADIO_PDUSTAT_PDUSTAT_Pos)          /*!< Bit mask of PDUSTAT field. */
#define RADIO_PDUSTAT_PDUSTAT_LessThan    (0UL) /*!< Payload less than PCNF1.MAXLEN */
#define RADIO_PDUSTAT_PDUSTAT_GreaterThan (1UL) /*!< Payload greater than PCNF1.MAXLEN */

/* Register: RADIO_CTESTATUS */
/* Description: CTEInfo parsed from received packet */

/* Bits 7..6 : CTEType parsed from packet */
#define RADIO_CTESTATUS_CTETYPE_Pos       (6UL) /*!< Position of CTETYPE field. */
#define RADIO_CTESTATUS_CTETYPE_Msk                                                                \
  (0x3UL << RADIO_CTESTATUS_CTETYPE_Pos) /*!< Bit mask of CTETYPE field. */

/* Bit 5 : RFU parsed from packet */
#define RADIO_CTESTATUS_RFU_Pos     (5UL) /*!< Position of RFU field. */
#define RADIO_CTESTATUS_RFU_Msk     (0x1UL << RADIO_CTESTATUS_RFU_Pos) /*!< Bit mask of RFU field. */

/* Bits 4..0 : CTETime parsed from packet */
#define RADIO_CTESTATUS_CTETIME_Pos (0UL) /*!< Position of CTETIME field. */
#define RADIO_CTESTATUS_CTETIME_Msk                                                                \
  (0x1FUL << RADIO_CTESTATUS_CTETIME_Pos) /*!< Bit mask of CTETIME field. */

/* Register: RADIO_DFESTATUS */
/* Description: DFE status information */

/* Bit 4 : Internal state of sampling state machine */
#define RADIO_DFESTATUS_SAMPLINGSTATE_Pos (4UL) /*!< Position of SAMPLINGSTATE field. */
#define RADIO_DFESTATUS_SAMPLINGSTATE_Msk                                                          \
  (0x1UL << RADIO_DFESTATUS_SAMPLINGSTATE_Pos)       /*!< Bit mask of SAMPLINGSTATE field. */
#define RADIO_DFESTATUS_SAMPLINGSTATE_Idle     (0UL) /*!< Sampling state Idle */
#define RADIO_DFESTATUS_SAMPLINGSTATE_Sampling (1UL) /*!< Sampling state Sampling */

/* Bits 2..0 : Internal state of switching state machine */
#define RADIO_DFESTATUS_SWITCHINGSTATE_Pos     (0UL) /*!< Position of SWITCHINGSTATE field. */
#define RADIO_DFESTATUS_SWITCHINGSTATE_Msk                                                         \
  (0x7UL << RADIO_DFESTATUS_SWITCHINGSTATE_Pos)        /*!< Bit mask of SWITCHINGSTATE field. */
#define RADIO_DFESTATUS_SWITCHINGSTATE_Idle      (0UL) /*!< Switching state Idle */
#define RADIO_DFESTATUS_SWITCHINGSTATE_Offset    (1UL) /*!< Switching state Offset */
#define RADIO_DFESTATUS_SWITCHINGSTATE_Guard     (2UL) /*!< Switching state Guard */
#define RADIO_DFESTATUS_SWITCHINGSTATE_Ref       (3UL) /*!< Switching state Ref */
#define RADIO_DFESTATUS_SWITCHINGSTATE_Switching (4UL) /*!< Switching state Switching */
#define RADIO_DFESTATUS_SWITCHINGSTATE_Ending    (5UL) /*!< Switching state Ending */

/* Register: RADIO_PACKETPTR */
/* Description: Packet pointer */

/* Bits 31..0 : Packet pointer */
#define RADIO_PACKETPTR_PACKETPTR_Pos            (0UL) /*!< Position of PACKETPTR field. */
#define RADIO_PACKETPTR_PACKETPTR_Msk                                                              \
  (0xFFFFFFFFUL << RADIO_PACKETPTR_PACKETPTR_Pos) /*!< Bit mask of PACKETPTR field. */

/* Register: RADIO_FREQUENCY */
/* Description: Frequency */

/* Bit 8 : Channel map selection. */
#define RADIO_FREQUENCY_MAP_Pos       (8UL) /*!< Position of MAP field. */
#define RADIO_FREQUENCY_MAP_Msk       (0x1UL << RADIO_FREQUENCY_MAP_Pos) /*!< Bit mask of MAP field. */
#define RADIO_FREQUENCY_MAP_Default   (0UL) /*!< Channel map between 2400 MHZ .. 2500 MHz */
#define RADIO_FREQUENCY_MAP_Low       (1UL) /*!< Channel map between 2360 MHZ .. 2460 MHz */

/* Bits 6..0 : Radio channel frequency */
#define RADIO_FREQUENCY_FREQUENCY_Pos (0UL) /*!< Position of FREQUENCY field. */
#define RADIO_FREQUENCY_FREQUENCY_Msk                                                              \
  (0x7FUL << RADIO_FREQUENCY_FREQUENCY_Pos) /*!< Bit mask of FREQUENCY field. */

/* Register: RADIO_TXPOWER */
/* Description: Output power */

/* Bits 7..0 : RADIO output power */
#define RADIO_TXPOWER_TXPOWER_Pos (0UL) /*!< Position of TXPOWER field. */
#define RADIO_TXPOWER_TXPOWER_Msk                                                                  \
  (0xFFUL << RADIO_TXPOWER_TXPOWER_Pos)             /*!< Bit mask of TXPOWER field. */
#define RADIO_TXPOWER_TXPOWER_0dBm         (0x0UL)  /*!< 0 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos2dBm      (0x2UL)  /*!< +2 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos3dBm      (0x3UL)  /*!< +3 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos4dBm      (0x4UL)  /*!< +4 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos5dBm      (0x5UL)  /*!< +5 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos6dBm      (0x6UL)  /*!< +6 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos7dBm      (0x7UL)  /*!< +7 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos8dBm      (0x8UL)  /*!< +8 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg40dBm     (0xD8UL) /*!< -40 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg30dBm     (0xE2UL) /*!< Deprecated enumerator -  -40 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg20dBm     (0xECUL) /*!< -20 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg16dBm     (0xF0UL) /*!< -16 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg12dBm     (0xF4UL) /*!< -12 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg8dBm      (0xF8UL) /*!< -8 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg4dBm      (0xFCUL) /*!< -4 dBm */

/* Register: RADIO_MODE */
/* Description: Data rate and modulation */

/* Bits 3..0 : Radio data rate and modulation setting. The radio supports frequency-shift keying (FSK) modulation. */
#define RADIO_MODE_MODE_Pos                (0UL) /*!< Position of MODE field. */
#define RADIO_MODE_MODE_Msk                (0xFUL << RADIO_MODE_MODE_Pos) /*!< Bit mask of MODE field. */
#define RADIO_MODE_MODE_Nrf_1Mbit          (0UL) /*!< 1 Mbps Nordic proprietary radio mode */
#define RADIO_MODE_MODE_Nrf_2Mbit          (1UL) /*!< 2 Mbps Nordic proprietary radio mode */
#define RADIO_MODE_MODE_Ble_1Mbit          (3UL) /*!< 1 Mbps BLE */
#define RADIO_MODE_MODE_Ble_2Mbit          (4UL) /*!< 2 Mbps BLE */
#define RADIO_MODE_MODE_Ble_LR125Kbit      (5UL) /*!< Long range 125 kbps TX, 125 kbps and 500 kbps RX */
#define RADIO_MODE_MODE_Ble_LR500Kbit      (6UL) /*!< Long range 500 kbps TX, 125 kbps and 500 kbps RX */
#define RADIO_MODE_MODE_Ieee802154_250Kbit (15UL) /*!< IEEE 802.15.4-2006 250 kbps */

/* Register: RADIO_PCNF0 */
/* Description: Packet configuration register 0 */

/* Bits 30..29 : Length of TERM field in Long Range operation */
#define RADIO_PCNF0_TERMLEN_Pos            (29UL) /*!< Position of TERMLEN field. */
#define RADIO_PCNF0_TERMLEN_Msk                                                                    \
  (0x3UL << RADIO_PCNF0_TERMLEN_Pos) /*!< Bit mask of TERMLEN field. */

/* Bit 26 : Indicates if LENGTH field contains CRC or not */
#define RADIO_PCNF0_CRCINC_Pos       (26UL) /*!< Position of CRCINC field. */
#define RADIO_PCNF0_CRCINC_Msk       (0x1UL << RADIO_PCNF0_CRCINC_Pos) /*!< Bit mask of CRCINC field. */
#define RADIO_PCNF0_CRCINC_Exclude   (0UL) /*!< LENGTH does not contain CRC */
#define RADIO_PCNF0_CRCINC_Include   (1UL) /*!< LENGTH includes CRC */

/* Bits 25..24 : Length of preamble on air. Decision point: TASKS_START task */
#define RADIO_PCNF0_PLEN_Pos         (24UL)                          /*!< Position of PLEN field. */
#define RADIO_PCNF0_PLEN_Msk         (0x3UL << RADIO_PCNF0_PLEN_Pos) /*!< Bit mask of PLEN field. */
#define RADIO_PCNF0_PLEN_8bit        (0UL)                           /*!< 8-bit preamble */
#define RADIO_PCNF0_PLEN_16bit       (1UL)                           /*!< 16-bit preamble */
#define RADIO_PCNF0_PLEN_32bitZero   (2UL) /*!< 32-bit zero preamble - used for IEEE 802.15.4 */
#define RADIO_PCNF0_PLEN_LongRange   (3UL) /*!< Preamble - used for BLE long range */

/* Bits 23..22 : Length of code indicator - long range */
#define RADIO_PCNF0_CILEN_Pos        (22UL) /*!< Position of CILEN field. */
#define RADIO_PCNF0_CILEN_Msk        (0x3UL << RADIO_PCNF0_CILEN_Pos) /*!< Bit mask of CILEN field. */

/* Bit 20 : Include or exclude S1 field in RAM */
#define RADIO_PCNF0_S1INCL_Pos       (20UL) /*!< Position of S1INCL field. */
#define RADIO_PCNF0_S1INCL_Msk       (0x1UL << RADIO_PCNF0_S1INCL_Pos) /*!< Bit mask of S1INCL field. */
#define RADIO_PCNF0_S1INCL_Automatic (0UL) /*!< Include S1 field in RAM only if S1LEN &gt; 0 */
#define RADIO_PCNF0_S1INCL_Include   (1UL) /*!< Always include S1 field in RAM independent of S1LEN */

/* Bits 19..16 : Length on air of S1 field in number of bits. */
#define RADIO_PCNF0_S1LEN_Pos        (16UL) /*!< Position of S1LEN field. */
#define RADIO_PCNF0_S1LEN_Msk        (0xFUL << RADIO_PCNF0_S1LEN_Pos) /*!< Bit mask of S1LEN field. */

/* Bit 8 : Length on air of S0 field in number of bytes. */
#define RADIO_PCNF0_S0LEN_Pos        (8UL) /*!< Position of S0LEN field. */
#define RADIO_PCNF0_S0LEN_Msk        (0x1UL << RADIO_PCNF0_S0LEN_Pos) /*!< Bit mask of S0LEN field. */

/* Bits 3..0 : Length on air of LENGTH field in number of bits. */
#define RADIO_PCNF0_LFLEN_Pos        (0UL) /*!< Position of LFLEN field. */
#define RADIO_PCNF0_LFLEN_Msk        (0xFUL << RADIO_PCNF0_LFLEN_Pos) /*!< Bit mask of LFLEN field. */

/* Register: RADIO_PCNF1 */
/* Description: Packet configuration register 1 */

/* Bit 25 : Enable or disable packet whitening */
#define RADIO_PCNF1_WHITEEN_Pos      (25UL) /*!< Position of WHITEEN field. */
#define RADIO_PCNF1_WHITEEN_Msk                                                                    \
  (0x1UL << RADIO_PCNF1_WHITEEN_Pos)       /*!< Bit mask of WHITEEN field. */
#define RADIO_PCNF1_WHITEEN_Disabled (0UL) /*!< Disable */
#define RADIO_PCNF1_WHITEEN_Enabled  (1UL) /*!< Enable */

/* Bit 24 : On-air endianness of packet, this applies to the S0, LENGTH, S1, and the PAYLOAD fields. */
#define RADIO_PCNF1_ENDIAN_Pos       (24UL) /*!< Position of ENDIAN field. */
#define RADIO_PCNF1_ENDIAN_Msk       (0x1UL << RADIO_PCNF1_ENDIAN_Pos) /*!< Bit mask of ENDIAN field. */
#define RADIO_PCNF1_ENDIAN_Little    (0UL) /*!< Least significant bit on air first */
#define RADIO_PCNF1_ENDIAN_Big       (1UL) /*!< Most significant bit on air first */

/* Bits 18..16 : Base address length in number of bytes */
#define RADIO_PCNF1_BALEN_Pos        (16UL) /*!< Position of BALEN field. */
#define RADIO_PCNF1_BALEN_Msk        (0x7UL << RADIO_PCNF1_BALEN_Pos) /*!< Bit mask of BALEN field. */

/* Bits 15..8 : Static length in number of bytes */
#define RADIO_PCNF1_STATLEN_Pos      (8UL) /*!< Position of STATLEN field. */
#define RADIO_PCNF1_STATLEN_Msk                                                                    \
  (0xFFUL << RADIO_PCNF1_STATLEN_Pos) /*!< Bit mask of STATLEN field. */

/* Bits 7..0 : Maximum length of packet payload. If the packet payload is larger than MAXLEN, the radio will truncate the payload to MAXLEN. */
#define RADIO_PCNF1_MAXLEN_Pos (0UL)                              /*!< Position of MAXLEN field. */
#define RADIO_PCNF1_MAXLEN_Msk (0xFFUL << RADIO_PCNF1_MAXLEN_Pos) /*!< Bit mask of MAXLEN field. */

/* Register: RADIO_BASE0 */
/* Description: Base address 0 */

/* Bits 31..0 : Base address 0 */
#define RADIO_BASE0_BASE0_Pos  (0UL) /*!< Position of BASE0 field. */
#define RADIO_BASE0_BASE0_Msk                                                                      \
  (0xFFFFFFFFUL << RADIO_BASE0_BASE0_Pos) /*!< Bit mask of BASE0 field. */

/* Register: RADIO_BASE1 */
/* Description: Base address 1 */

/* Bits 31..0 : Base address 1 */
#define RADIO_BASE1_BASE1_Pos (0UL) /*!< Position of BASE1 field. */
#define RADIO_BASE1_BASE1_Msk                                                                      \
  (0xFFFFFFFFUL << RADIO_BASE1_BASE1_Pos) /*!< Bit mask of BASE1 field. */

/* Register: RADIO_PREFIX0 */
/* Description: Prefixes bytes for logical addresses 0-3 */

/* Bits 31..24 : Address prefix 3. */
#define RADIO_PREFIX0_AP3_Pos         (24UL) /*!< Position of AP3 field. */
#define RADIO_PREFIX0_AP3_Msk         (0xFFUL << RADIO_PREFIX0_AP3_Pos) /*!< Bit mask of AP3 field. */

/* Bits 23..16 : Address prefix 2. */
#define RADIO_PREFIX0_AP2_Pos         (16UL) /*!< Position of AP2 field. */
#define RADIO_PREFIX0_AP2_Msk         (0xFFUL << RADIO_PREFIX0_AP2_Pos) /*!< Bit mask of AP2 field. */

/* Bits 15..8 : Address prefix 1. */
#define RADIO_PREFIX0_AP1_Pos         (8UL) /*!< Position of AP1 field. */
#define RADIO_PREFIX0_AP1_Msk         (0xFFUL << RADIO_PREFIX0_AP1_Pos) /*!< Bit mask of AP1 field. */

/* Bits 7..0 : Address prefix 0. */
#define RADIO_PREFIX0_AP0_Pos         (0UL) /*!< Position of AP0 field. */
#define RADIO_PREFIX0_AP0_Msk         (0xFFUL << RADIO_PREFIX0_AP0_Pos) /*!< Bit mask of AP0 field. */

/* Register: RADIO_PREFIX1 */
/* Description: Prefixes bytes for logical addresses 4-7 */

/* Bits 31..24 : Address prefix 7. */
#define RADIO_PREFIX1_AP7_Pos         (24UL) /*!< Position of AP7 field. */
#define RADIO_PREFIX1_AP7_Msk         (0xFFUL << RADIO_PREFIX1_AP7_Pos) /*!< Bit mask of AP7 field. */

/* Bits 23..16 : Address prefix 6. */
#define RADIO_PREFIX1_AP6_Pos         (16UL) /*!< Position of AP6 field. */
#define RADIO_PREFIX1_AP6_Msk         (0xFFUL << RADIO_PREFIX1_AP6_Pos) /*!< Bit mask of AP6 field. */

/* Bits 15..8 : Address prefix 5. */
#define RADIO_PREFIX1_AP5_Pos         (8UL) /*!< Position of AP5 field. */
#define RADIO_PREFIX1_AP5_Msk         (0xFFUL << RADIO_PREFIX1_AP5_Pos) /*!< Bit mask of AP5 field. */

/* Bits 7..0 : Address prefix 4. */
#define RADIO_PREFIX1_AP4_Pos         (0UL) /*!< Position of AP4 field. */
#define RADIO_PREFIX1_AP4_Msk         (0xFFUL << RADIO_PREFIX1_AP4_Pos) /*!< Bit mask of AP4 field. */

/* Register: RADIO_TXADDRESS */
/* Description: Transmit address select */

/* Bits 2..0 : Transmit address select */
#define RADIO_TXADDRESS_TXADDRESS_Pos (0UL) /*!< Position of TXADDRESS field. */
#define RADIO_TXADDRESS_TXADDRESS_Msk                                                              \
  (0x7UL << RADIO_TXADDRESS_TXADDRESS_Pos) /*!< Bit mask of TXADDRESS field. */

/* Register: RADIO_RXADDRESSES */
/* Description: Receive address select */

/* Bit 7 : Enable or disable reception on logical address 7. */
#define RADIO_RXADDRESSES_ADDR7_Pos (7UL) /*!< Position of ADDR7 field. */
#define RADIO_RXADDRESSES_ADDR7_Msk                                                                \
  (0x1UL << RADIO_RXADDRESSES_ADDR7_Pos)       /*!< Bit mask of ADDR7 field. */
#define RADIO_RXADDRESSES_ADDR7_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR7_Enabled  (1UL) /*!< Enable */

/* Bit 6 : Enable or disable reception on logical address 6. */
#define RADIO_RXADDRESSES_ADDR6_Pos      (6UL) /*!< Position of ADDR6 field. */
#define RADIO_RXADDRESSES_ADDR6_Msk                                                                \
  (0x1UL << RADIO_RXADDRESSES_ADDR6_Pos)       /*!< Bit mask of ADDR6 field. */
#define RADIO_RXADDRESSES_ADDR6_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR6_Enabled  (1UL) /*!< Enable */

/* Bit 5 : Enable or disable reception on logical address 5. */
#define RADIO_RXADDRESSES_ADDR5_Pos      (5UL) /*!< Position of ADDR5 field. */
#define RADIO_RXADDRESSES_ADDR5_Msk                                                                \
  (0x1UL << RADIO_RXADDRESSES_ADDR5_Pos)       /*!< Bit mask of ADDR5 field. */
#define RADIO_RXADDRESSES_ADDR5_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR5_Enabled  (1UL) /*!< Enable */

/* Bit 4 : Enable or disable reception on logical address 4. */
#define RADIO_RXADDRESSES_ADDR4_Pos      (4UL) /*!< Position of ADDR4 field. */
#define RADIO_RXADDRESSES_ADDR4_Msk                                                                \
  (0x1UL << RADIO_RXADDRESSES_ADDR4_Pos)       /*!< Bit mask of ADDR4 field. */
#define RADIO_RXADDRESSES_ADDR4_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR4_Enabled  (1UL) /*!< Enable */

/* Bit 3 : Enable or disable reception on logical address 3. */
#define RADIO_RXADDRESSES_ADDR3_Pos      (3UL) /*!< Position of ADDR3 field. */
#define RADIO_RXADDRESSES_ADDR3_Msk                                                                \
  (0x1UL << RADIO_RXADDRESSES_ADDR3_Pos)       /*!< Bit mask of ADDR3 field. */
#define RADIO_RXADDRESSES_ADDR3_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR3_Enabled  (1UL) /*!< Enable */

/* Bit 2 : Enable or disable reception on logical address 2. */
#define RADIO_RXADDRESSES_ADDR2_Pos      (2UL) /*!< Position of ADDR2 field. */
#define RADIO_RXADDRESSES_ADDR2_Msk                                                                \
  (0x1UL << RADIO_RXADDRESSES_ADDR2_Pos)       /*!< Bit mask of ADDR2 field. */
#define RADIO_RXADDRESSES_ADDR2_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR2_Enabled  (1UL) /*!< Enable */

/* Bit 1 : Enable or disable reception on logical address 1. */
#define RADIO_RXADDRESSES_ADDR1_Pos      (1UL) /*!< Position of ADDR1 field. */
#define RADIO_RXADDRESSES_ADDR1_Msk                                                                \
  (0x1UL << RADIO_RXADDRESSES_ADDR1_Pos)       /*!< Bit mask of ADDR1 field. */
#define RADIO_RXADDRESSES_ADDR1_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR1_Enabled  (1UL) /*!< Enable */

/* Bit 0 : Enable or disable reception on logical address 0. */
#define RADIO_RXADDRESSES_ADDR0_Pos      (0UL) /*!< Position of ADDR0 field. */
#define RADIO_RXADDRESSES_ADDR0_Msk                                                                \
  (0x1UL << RADIO_RXADDRESSES_ADDR0_Pos)       /*!< Bit mask of ADDR0 field. */
#define RADIO_RXADDRESSES_ADDR0_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR0_Enabled  (1UL) /*!< Enable */

/* Register: RADIO_CRCCNF */
/* Description: CRC configuration */

/* Bits 9..8 : Include or exclude packet address field out of CRC calculation. */
#define RADIO_CRCCNF_SKIPADDR_Pos        (8UL) /*!< Position of SKIPADDR field. */
#define RADIO_CRCCNF_SKIPADDR_Msk                                                                  \
  (0x3UL << RADIO_CRCCNF_SKIPADDR_Pos)      /*!< Bit mask of SKIPADDR field. */
#define RADIO_CRCCNF_SKIPADDR_Include (0UL) /*!< CRC calculation includes address field */
#define RADIO_CRCCNF_SKIPADDR_Skip                                                                 \
  (1UL) /*!< CRC calculation does not include address field. The CRC calculation will start at the first byte after the address. */
#define RADIO_CRCCNF_SKIPADDR_Ieee802154                                                           \
  (2UL) /*!< CRC calculation as per 802.15.4 standard. Starting at first byte after length field. */

/* Bits 1..0 : CRC length in number of bytes. */
#define RADIO_CRCCNF_LEN_Pos      (0UL)                           /*!< Position of LEN field. */
#define RADIO_CRCCNF_LEN_Msk      (0x3UL << RADIO_CRCCNF_LEN_Pos) /*!< Bit mask of LEN field. */
#define RADIO_CRCCNF_LEN_Disabled (0UL) /*!< CRC length is zero and CRC calculation is disabled */
#define RADIO_CRCCNF_LEN_One      (1UL) /*!< CRC length is one byte and CRC calculation is enabled */
#define RADIO_CRCCNF_LEN_Two      (2UL) /*!< CRC length is two bytes and CRC calculation is enabled */
#define RADIO_CRCCNF_LEN_Three                                                                     \
  (3UL) /*!< CRC length is three bytes and CRC calculation is enabled */

/* Register: RADIO_CRCPOLY */
/* Description: CRC polynomial */

/* Bits 23..0 : CRC polynomial */
#define RADIO_CRCPOLY_CRCPOLY_Pos (0UL) /*!< Position of CRCPOLY field. */
#define RADIO_CRCPOLY_CRCPOLY_Msk                                                                  \
  (0xFFFFFFUL << RADIO_CRCPOLY_CRCPOLY_Pos) /*!< Bit mask of CRCPOLY field. */

/* Register: RADIO_CRCINIT */
/* Description: CRC initial value */

/* Bits 23..0 : CRC initial value */
#define RADIO_CRCINIT_CRCINIT_Pos (0UL) /*!< Position of CRCINIT field. */
#define RADIO_CRCINIT_CRCINIT_Msk                                                                  \
  (0xFFFFFFUL << RADIO_CRCINIT_CRCINIT_Pos) /*!< Bit mask of CRCINIT field. */

/* Register: RADIO_TIFS */
/* Description: Interframe spacing in us */

/* Bits 9..0 : Interframe spacing in us */
#define RADIO_TIFS_TIFS_Pos             (0UL) /*!< Position of TIFS field. */
#define RADIO_TIFS_TIFS_Msk             (0x3FFUL << RADIO_TIFS_TIFS_Pos) /*!< Bit mask of TIFS field. */

/* Register: RADIO_RSSISAMPLE */
/* Description: RSSI sample */

/* Bits 6..0 : RSSI sample */
#define RADIO_RSSISAMPLE_RSSISAMPLE_Pos (0UL) /*!< Position of RSSISAMPLE field. */
#define RADIO_RSSISAMPLE_RSSISAMPLE_Msk                                                            \
  (0x7FUL << RADIO_RSSISAMPLE_RSSISAMPLE_Pos) /*!< Bit mask of RSSISAMPLE field. */

/* Register: RADIO_STATE */
/* Description: Current radio state */

/* Bits 3..0 : Current radio state */
#define RADIO_STATE_STATE_Pos             (0UL) /*!< Position of STATE field. */
#define RADIO_STATE_STATE_Msk             (0xFUL << RADIO_STATE_STATE_Pos) /*!< Bit mask of STATE field. */
#define RADIO_STATE_STATE_Disabled        (0UL)  /*!< RADIO is in the Disabled state */
#define RADIO_STATE_STATE_RxRu            (1UL)  /*!< RADIO is in the RXRU state */
#define RADIO_STATE_STATE_RxIdle          (2UL)  /*!< RADIO is in the RXIDLE state */
#define RADIO_STATE_STATE_Rx              (3UL)  /*!< RADIO is in the RX state */
#define RADIO_STATE_STATE_RxDisable       (4UL)  /*!< RADIO is in the RXDISABLED state */
#define RADIO_STATE_STATE_TxRu            (9UL)  /*!< RADIO is in the TXRU state */
#define RADIO_STATE_STATE_TxIdle          (10UL) /*!< RADIO is in the TXIDLE state */
#define RADIO_STATE_STATE_Tx              (11UL) /*!< RADIO is in the TX state */
#define RADIO_STATE_STATE_TxDisable       (12UL) /*!< RADIO is in the TXDISABLED state */

/* Register: RADIO_DATAWHITEIV */
/* Description: Data whitening initial value */

/* Bits 6..0 : Data whitening initial value. Bit 6 is hardwired to '1', writing '0' to it has no effect, and it will always be read back and used by the device as '1'. */
#define RADIO_DATAWHITEIV_DATAWHITEIV_Pos (0UL) /*!< Position of DATAWHITEIV field. */
#define RADIO_DATAWHITEIV_DATAWHITEIV_Msk                                                          \
  (0x7FUL << RADIO_DATAWHITEIV_DATAWHITEIV_Pos) /*!< Bit mask of DATAWHITEIV field. */

/* Register: RADIO_BCC */
/* Description: Bit counter compare */

/* Bits 31..0 : Bit counter compare */
#define RADIO_BCC_BCC_Pos                   (0UL) /*!< Position of BCC field. */
#define RADIO_BCC_BCC_Msk                   (0xFFFFFFFFUL << RADIO_BCC_BCC_Pos) /*!< Bit mask of BCC field. */

/* Register: RADIO_DAB */
/* Description: Description collection: Device address base segment n */

/* Bits 31..0 : Device address base segment n */
#define RADIO_DAB_DAB_Pos                   (0UL) /*!< Position of DAB field. */
#define RADIO_DAB_DAB_Msk                   (0xFFFFFFFFUL << RADIO_DAB_DAB_Pos) /*!< Bit mask of DAB field. */

/* Register: RADIO_DAP */
/* Description: Description collection: Device address prefix n */

/* Bits 15..0 : Device address prefix n */
#define RADIO_DAP_DAP_Pos                   (0UL) /*!< Position of DAP field. */
#define RADIO_DAP_DAP_Msk                   (0xFFFFUL << RADIO_DAP_DAP_Pos) /*!< Bit mask of DAP field. */

/* Register: RADIO_DACNF */
/* Description: Device address match configuration */

/* Bit 15 : TxAdd for device address 7 */
#define RADIO_DACNF_TXADD7_Pos              (15UL) /*!< Position of TXADD7 field. */
#define RADIO_DACNF_TXADD7_Msk              (0x1UL << RADIO_DACNF_TXADD7_Pos) /*!< Bit mask of TXADD7 field. */

/* Bit 14 : TxAdd for device address 6 */
#define RADIO_DACNF_TXADD6_Pos              (14UL) /*!< Position of TXADD6 field. */
#define RADIO_DACNF_TXADD6_Msk              (0x1UL << RADIO_DACNF_TXADD6_Pos) /*!< Bit mask of TXADD6 field. */

/* Bit 13 : TxAdd for device address 5 */
#define RADIO_DACNF_TXADD5_Pos              (13UL) /*!< Position of TXADD5 field. */
#define RADIO_DACNF_TXADD5_Msk              (0x1UL << RADIO_DACNF_TXADD5_Pos) /*!< Bit mask of TXADD5 field. */

/* Bit 12 : TxAdd for device address 4 */
#define RADIO_DACNF_TXADD4_Pos              (12UL) /*!< Position of TXADD4 field. */
#define RADIO_DACNF_TXADD4_Msk              (0x1UL << RADIO_DACNF_TXADD4_Pos) /*!< Bit mask of TXADD4 field. */

/* Bit 11 : TxAdd for device address 3 */
#define RADIO_DACNF_TXADD3_Pos              (11UL) /*!< Position of TXADD3 field. */
#define RADIO_DACNF_TXADD3_Msk              (0x1UL << RADIO_DACNF_TXADD3_Pos) /*!< Bit mask of TXADD3 field. */

/* Bit 10 : TxAdd for device address 2 */
#define RADIO_DACNF_TXADD2_Pos              (10UL) /*!< Position of TXADD2 field. */
#define RADIO_DACNF_TXADD2_Msk              (0x1UL << RADIO_DACNF_TXADD2_Pos) /*!< Bit mask of TXADD2 field. */

/* Bit 9 : TxAdd for device address 1 */
#define RADIO_DACNF_TXADD1_Pos              (9UL) /*!< Position of TXADD1 field. */
#define RADIO_DACNF_TXADD1_Msk              (0x1UL << RADIO_DACNF_TXADD1_Pos) /*!< Bit mask of TXADD1 field. */

/* Bit 8 : TxAdd for device address 0 */
#define RADIO_DACNF_TXADD0_Pos              (8UL) /*!< Position of TXADD0 field. */
#define RADIO_DACNF_TXADD0_Msk              (0x1UL << RADIO_DACNF_TXADD0_Pos) /*!< Bit mask of TXADD0 field. */

/* Bit 7 : Enable or disable device address matching using device address 7 */
#define RADIO_DACNF_ENA7_Pos                (7UL) /*!< Position of ENA7 field. */
#define RADIO_DACNF_ENA7_Msk                (0x1UL << RADIO_DACNF_ENA7_Pos) /*!< Bit mask of ENA7 field. */
#define RADIO_DACNF_ENA7_Disabled           (0UL)                           /*!< Disabled */
#define RADIO_DACNF_ENA7_Enabled            (1UL)                           /*!< Enabled */

/* Bit 6 : Enable or disable device address matching using device address 6 */
#define RADIO_DACNF_ENA6_Pos                (6UL) /*!< Position of ENA6 field. */
#define RADIO_DACNF_ENA6_Msk                (0x1UL << RADIO_DACNF_ENA6_Pos) /*!< Bit mask of ENA6 field. */
#define RADIO_DACNF_ENA6_Disabled           (0UL)                           /*!< Disabled */
#define RADIO_DACNF_ENA6_Enabled            (1UL)                           /*!< Enabled */

/* Bit 5 : Enable or disable device address matching using device address 5 */
#define RADIO_DACNF_ENA5_Pos                (5UL) /*!< Position of ENA5 field. */
#define RADIO_DACNF_ENA5_Msk                (0x1UL << RADIO_DACNF_ENA5_Pos) /*!< Bit mask of ENA5 field. */
#define RADIO_DACNF_ENA5_Disabled           (0UL)                           /*!< Disabled */
#define RADIO_DACNF_ENA5_Enabled            (1UL)                           /*!< Enabled */

/* Bit 4 : Enable or disable device address matching using device address 4 */
#define RADIO_DACNF_ENA4_Pos                (4UL) /*!< Position of ENA4 field. */
#define RADIO_DACNF_ENA4_Msk                (0x1UL << RADIO_DACNF_ENA4_Pos) /*!< Bit mask of ENA4 field. */
#define RADIO_DACNF_ENA4_Disabled           (0UL)                           /*!< Disabled */
#define RADIO_DACNF_ENA4_Enabled            (1UL)                           /*!< Enabled */

/* Bit 3 : Enable or disable device address matching using device address 3 */
#define RADIO_DACNF_ENA3_Pos                (3UL) /*!< Position of ENA3 field. */
#define RADIO_DACNF_ENA3_Msk                (0x1UL << RADIO_DACNF_ENA3_Pos) /*!< Bit mask of ENA3 field. */
#define RADIO_DACNF_ENA3_Disabled           (0UL)                           /*!< Disabled */
#define RADIO_DACNF_ENA3_Enabled            (1UL)                           /*!< Enabled */

/* Bit 2 : Enable or disable device address matching using device address 2 */
#define RADIO_DACNF_ENA2_Pos                (2UL) /*!< Position of ENA2 field. */
#define RADIO_DACNF_ENA2_Msk                (0x1UL << RADIO_DACNF_ENA2_Pos) /*!< Bit mask of ENA2 field. */
#define RADIO_DACNF_ENA2_Disabled           (0UL)                           /*!< Disabled */
#define RADIO_DACNF_ENA2_Enabled            (1UL)                           /*!< Enabled */

/* Bit 1 : Enable or disable device address matching using device address 1 */
#define RADIO_DACNF_ENA1_Pos                (1UL) /*!< Position of ENA1 field. */
#define RADIO_DACNF_ENA1_Msk                (0x1UL << RADIO_DACNF_ENA1_Pos) /*!< Bit mask of ENA1 field. */
#define RADIO_DACNF_ENA1_Disabled           (0UL)                           /*!< Disabled */
#define RADIO_DACNF_ENA1_Enabled            (1UL)                           /*!< Enabled */

/* Bit 0 : Enable or disable device address matching using device address 0 */
#define RADIO_DACNF_ENA0_Pos                (0UL) /*!< Position of ENA0 field. */
#define RADIO_DACNF_ENA0_Msk                (0x1UL << RADIO_DACNF_ENA0_Pos) /*!< Bit mask of ENA0 field. */
#define RADIO_DACNF_ENA0_Disabled           (0UL)                           /*!< Disabled */
#define RADIO_DACNF_ENA0_Enabled            (1UL)                           /*!< Enabled */

/* Register: RADIO_MHRMATCHCONF */
/* Description: Search pattern configuration */

/* Bits 31..0 : Search pattern configuration */
#define RADIO_MHRMATCHCONF_MHRMATCHCONF_Pos (0UL) /*!< Position of MHRMATCHCONF field. */
#define RADIO_MHRMATCHCONF_MHRMATCHCONF_Msk                                                        \
  (0xFFFFFFFFUL << RADIO_MHRMATCHCONF_MHRMATCHCONF_Pos) /*!< Bit mask of MHRMATCHCONF field. */

/* Register: RADIO_MHRMATCHMAS */
/* Description: Pattern mask */

/* Bits 31..0 : Pattern mask */
#define RADIO_MHRMATCHMAS_MHRMATCHMAS_Pos (0UL) /*!< Position of MHRMATCHMAS field. */
#define RADIO_MHRMATCHMAS_MHRMATCHMAS_Msk                                                          \
  (0xFFFFFFFFUL << RADIO_MHRMATCHMAS_MHRMATCHMAS_Pos) /*!< Bit mask of MHRMATCHMAS field. */

/* Register: RADIO_MODECNF0 */
/* Description: Radio mode configuration register 0 */

/* Bits 9..8 : Default TX value */
#define RADIO_MODECNF0_DTX_Pos    (8UL)                             /*!< Position of DTX field. */
#define RADIO_MODECNF0_DTX_Msk    (0x3UL << RADIO_MODECNF0_DTX_Pos) /*!< Bit mask of DTX field. */
#define RADIO_MODECNF0_DTX_B1     (0UL)                             /*!< Transmit '1' */
#define RADIO_MODECNF0_DTX_B0     (1UL)                             /*!< Transmit '0' */
#define RADIO_MODECNF0_DTX_Center (2UL) /*!< Transmit center frequency */

/* Bit 0 : Radio ramp-up time */
#define RADIO_MODECNF0_RU_Pos     (0UL)                            /*!< Position of RU field. */
#define RADIO_MODECNF0_RU_Msk     (0x1UL << RADIO_MODECNF0_RU_Pos) /*!< Bit mask of RU field. */
#define RADIO_MODECNF0_RU_Default                                                                  \
  (0UL) /*!< Default ramp-up time (tRXEN and tTXEN), compatible with firmware written for nRF51 */
#define RADIO_MODECNF0_RU_Fast                                                                     \
  (1UL) /*!< Fast ramp-up (tRXEN,FAST and tTXEN,FAST), see electrical specification for more information */

/* Register: RADIO_SFD */
/* Description: IEEE 802.15.4 start of frame delimiter */

/* Bits 7..0 : IEEE 802.15.4 start of frame delimiter */
#define RADIO_SFD_SFD_Pos        (0UL)                         /*!< Position of SFD field. */
#define RADIO_SFD_SFD_Msk        (0xFFUL << RADIO_SFD_SFD_Pos) /*!< Bit mask of SFD field. */

/* Register: RADIO_EDCNT */
/* Description: IEEE 802.15.4 energy detect loop count */

/* Bits 20..0 : IEEE 802.15.4 energy detect loop count */
#define RADIO_EDCNT_EDCNT_Pos    (0UL) /*!< Position of EDCNT field. */
#define RADIO_EDCNT_EDCNT_Msk    (0x1FFFFFUL << RADIO_EDCNT_EDCNT_Pos) /*!< Bit mask of EDCNT field. */

/* Register: RADIO_EDSAMPLE */
/* Description: IEEE 802.15.4 energy detect level */

/* Bits 7..0 : IEEE 802.15.4 energy detect level */
#define RADIO_EDSAMPLE_EDLVL_Pos (0UL) /*!< Position of EDLVL field. */
#define RADIO_EDSAMPLE_EDLVL_Msk                                                                   \
  (0xFFUL << RADIO_EDSAMPLE_EDLVL_Pos) /*!< Bit mask of EDLVL field. */

/* Register: RADIO_CCACTRL */
/* Description: IEEE 802.15.4 clear channel assessment control */

/* Bits 31..24 : Limit for occurrences above CCACORRTHRES. When not equal to zero the corrolator based signal detect is enabled. */
#define RADIO_CCACTRL_CCACORRCNT_Pos (24UL) /*!< Position of CCACORRCNT field. */
#define RADIO_CCACTRL_CCACORRCNT_Msk                                                               \
  (0xFFUL << RADIO_CCACTRL_CCACORRCNT_Pos) /*!< Bit mask of CCACORRCNT field. */

/* Bits 23..16 : CCA correlator busy threshold. Only relevant to CarrierMode, CarrierAndEdMode, and CarrierOrEdMode. */
#define RADIO_CCACTRL_CCACORRTHRES_Pos (16UL) /*!< Position of CCACORRTHRES field. */
#define RADIO_CCACTRL_CCACORRTHRES_Msk                                                             \
  (0xFFUL << RADIO_CCACTRL_CCACORRTHRES_Pos) /*!< Bit mask of CCACORRTHRES field. */

/* Bits 15..8 : CCA energy busy threshold. Used in all the CCA modes except CarrierMode. */
#define RADIO_CCACTRL_CCAEDTHRES_Pos (8UL) /*!< Position of CCAEDTHRES field. */
#define RADIO_CCACTRL_CCAEDTHRES_Msk                                                               \
  (0xFFUL << RADIO_CCACTRL_CCAEDTHRES_Pos) /*!< Bit mask of CCAEDTHRES field. */

/* Bits 2..0 : CCA mode of operation */
#define RADIO_CCACTRL_CCAMODE_Pos (0UL) /*!< Position of CCAMODE field. */
#define RADIO_CCACTRL_CCAMODE_Msk                                                                  \
  (0x7UL << RADIO_CCACTRL_CCAMODE_Pos)               /*!< Bit mask of CCAMODE field. */
#define RADIO_CCACTRL_CCAMODE_EdMode           (0UL) /*!< Energy above threshold */
#define RADIO_CCACTRL_CCAMODE_CarrierMode      (1UL) /*!< Carrier seen */
#define RADIO_CCACTRL_CCAMODE_CarrierAndEdMode (2UL) /*!< Energy above threshold AND carrier seen */
#define RADIO_CCACTRL_CCAMODE_CarrierOrEdMode  (3UL) /*!< Energy above threshold OR carrier seen */
#define RADIO_CCACTRL_CCAMODE_EdModeTest1                                                          \
  (4UL) /*!< Energy above threshold test mode that will abort when first ED measurement over threshold is seen. No averaging. */

/* Register: RADIO_DFEMODE */
/* Description: Whether to use Angle-of-Arrival (AOA) or Angle-of-Departure (AOD) */

/* Bits 1..0 : Direction finding operation mode */
#define RADIO_DFEMODE_DFEOPMODE_Pos (0UL) /*!< Position of DFEOPMODE field. */
#define RADIO_DFEMODE_DFEOPMODE_Msk                                                                \
  (0x3UL << RADIO_DFEMODE_DFEOPMODE_Pos)       /*!< Bit mask of DFEOPMODE field. */
#define RADIO_DFEMODE_DFEOPMODE_Disabled (0UL) /*!< Direction finding mode disabled */
#define RADIO_DFEMODE_DFEOPMODE_AoD      (2UL) /*!< Direction finding mode set to AoD */
#define RADIO_DFEMODE_DFEOPMODE_AoA      (3UL) /*!< Direction finding mode set to AoA */

/* Register: RADIO_CTEINLINECONF */
/* Description: Configuration for CTE inline mode */

/* Bits 31..24 : S0 bit mask to set which bit to match */
#define RADIO_CTEINLINECONF_S0MASK_Pos   (24UL) /*!< Position of S0MASK field. */
#define RADIO_CTEINLINECONF_S0MASK_Msk                                                             \
  (0xFFUL << RADIO_CTEINLINECONF_S0MASK_Pos) /*!< Bit mask of S0MASK field. */

/* Bits 23..16 : S0 bit pattern to match */
#define RADIO_CTEINLINECONF_S0CONF_Pos (16UL) /*!< Position of S0CONF field. */
#define RADIO_CTEINLINECONF_S0CONF_Msk                                                             \
  (0xFFUL << RADIO_CTEINLINECONF_S0CONF_Pos) /*!< Bit mask of S0CONF field. */

/* Bits 15..13 : Spacing between samples for the samples in the SWITCHING period when CTEINLINEMODE is set */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE2US_Pos                                                 \
  (13UL) /*!< Position of CTEINLINERXMODE2US field. */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE2US_Msk                                                 \
  (0x7UL                                                                                           \
   << RADIO_CTEINLINECONF_CTEINLINERXMODE2US_Pos) /*!< Bit mask of CTEINLINERXMODE2US field. */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE2US_4us   (1UL) /*!< 4us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE2US_2us   (2UL) /*!< 2us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE2US_1us   (3UL) /*!< 1us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE2US_500ns (4UL) /*!< 0.5us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE2US_250ns (5UL) /*!< 0.25us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE2US_125ns (6UL) /*!< 0.125us */

/* Bits 12..10 : Spacing between samples for the samples in the SWITCHING period when CTEINLINEMODE is set */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE1US_Pos                                                 \
  (10UL) /*!< Position of CTEINLINERXMODE1US field. */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE1US_Msk                                                 \
  (0x7UL                                                                                           \
   << RADIO_CTEINLINECONF_CTEINLINERXMODE1US_Pos) /*!< Bit mask of CTEINLINERXMODE1US field. */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE1US_4us   (1UL) /*!< 4us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE1US_2us   (2UL) /*!< 2us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE1US_1us   (3UL) /*!< 1us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE1US_500ns (4UL) /*!< 0.5us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE1US_250ns (5UL) /*!< 0.25us */
#define RADIO_CTEINLINECONF_CTEINLINERXMODE1US_125ns (6UL) /*!< 0.125us */

/* Bits 7..6 : Max range of CTETime */
#define RADIO_CTEINLINECONF_CTETIMEVALIDRANGE_Pos    (6UL) /*!< Position of CTETIMEVALIDRANGE field. */
#define RADIO_CTEINLINECONF_CTETIMEVALIDRANGE_Msk                                                  \
  (0x3UL << RADIO_CTEINLINECONF_CTETIMEVALIDRANGE_Pos) /*!< Bit mask of CTETIMEVALIDRANGE field. */
#define RADIO_CTEINLINECONF_CTETIMEVALIDRANGE_20                                                   \
  (0UL) /*!< 20 in 8us unit (default) Set to 20 if parsed CTETime is larger han 20 */
#define RADIO_CTEINLINECONF_CTETIMEVALIDRANGE_31 (1UL) /*!< 31 in 8us unit */
#define RADIO_CTEINLINECONF_CTETIMEVALIDRANGE_63 (2UL) /*!< 63 in 8us unit */

/* Bit 4 : Sampling/switching if CRC is not OK */
#define RADIO_CTEINLINECONF_CTEERRORHANDLING_Pos (4UL) /*!< Position of CTEERRORHANDLING field. */
#define RADIO_CTEINLINECONF_CTEERRORHANDLING_Msk                                                   \
  (0x1UL << RADIO_CTEINLINECONF_CTEERRORHANDLING_Pos) /*!< Bit mask of CTEERRORHANDLING field. */
#define RADIO_CTEINLINECONF_CTEERRORHANDLING_No                                                    \
  (0UL) /*!< No sampling and antenna switching when CRC is not OK */
#define RADIO_CTEINLINECONF_CTEERRORHANDLING_Yes                                                   \
  (1UL) /*!< Sampling and antenna switching also when CRC is not OK */

/* Bit 3 : CTEInfo is S1 byte or not */
#define RADIO_CTEINLINECONF_CTEINFOINS1_Pos (3UL) /*!< Position of CTEINFOINS1 field. */
#define RADIO_CTEINLINECONF_CTEINFOINS1_Msk                                                        \
  (0x1UL << RADIO_CTEINLINECONF_CTEINFOINS1_Pos) /*!< Bit mask of CTEINFOINS1 field. */
#define RADIO_CTEINLINECONF_CTEINFOINS1_NotInS1                                                    \
  (0UL) /*!< CTEInfo is NOT in S1 byte (advertising PDU) */
#define RADIO_CTEINLINECONF_CTEINFOINS1_InS1    (1UL) /*!< CTEInfo is in S1 byte (data PDU) */

/* Bit 0 : Enable parsing of CTEInfo from received packet in BLE modes */
#define RADIO_CTEINLINECONF_CTEINLINECTRLEN_Pos (0UL) /*!< Position of CTEINLINECTRLEN field. */
#define RADIO_CTEINLINECONF_CTEINLINECTRLEN_Msk                                                    \
  (0x1UL << RADIO_CTEINLINECONF_CTEINLINECTRLEN_Pos) /*!< Bit mask of CTEINLINECTRLEN field. */
#define RADIO_CTEINLINECONF_CTEINLINECTRLEN_Disabled (0UL) /*!< Parsing of CTEInfo is disabled */
#define RADIO_CTEINLINECONF_CTEINLINECTRLEN_Enabled  (1UL) /*!< Parsing of CTEInfo is enabled */

/* Register: RADIO_DFECTRL1 */
/* Description: Various configuration for Direction finding */

/* Bits 27..24 : Gain will be lowered by the specified number of gain steps at the start of CTE */
#define RADIO_DFECTRL1_AGCBACKOFFGAIN_Pos            (24UL) /*!< Position of AGCBACKOFFGAIN field. */
#define RADIO_DFECTRL1_AGCBACKOFFGAIN_Msk                                                          \
  (0xFUL << RADIO_DFECTRL1_AGCBACKOFFGAIN_Pos) /*!< Bit mask of AGCBACKOFFGAIN field. */

/* Bits 23..20 : Repeat each individual antenna pattern N times sequentially, i.e. P0, P0, P1, P1, P2, P2, P3, P3, etc. */
#define RADIO_DFECTRL1_REPEATPATTERN_Pos (20UL) /*!< Position of REPEATPATTERN field. */
#define RADIO_DFECTRL1_REPEATPATTERN_Msk                                                           \
  (0xFUL << RADIO_DFECTRL1_REPEATPATTERN_Pos)       /*!< Bit mask of REPEATPATTERN field. */
#define RADIO_DFECTRL1_REPEATPATTERN_NoRepeat (0UL) /*!< Do not repeat (1 time in total) */

/* Bits 18..16 : Interval between samples in the SWITCHING period when CTEINLINECTRLEN is 0 */
#define RADIO_DFECTRL1_TSAMPLESPACING_Pos     (16UL) /*!< Position of TSAMPLESPACING field. */
#define RADIO_DFECTRL1_TSAMPLESPACING_Msk                                                          \
  (0x7UL << RADIO_DFECTRL1_TSAMPLESPACING_Pos)    /*!< Bit mask of TSAMPLESPACING field. */
#define RADIO_DFECTRL1_TSAMPLESPACING_4us   (1UL) /*!< 4us */
#define RADIO_DFECTRL1_TSAMPLESPACING_2us   (2UL) /*!< 2us */
#define RADIO_DFECTRL1_TSAMPLESPACING_1us   (3UL) /*!< 1us */
#define RADIO_DFECTRL1_TSAMPLESPACING_500ns (4UL) /*!< 0.5us */
#define RADIO_DFECTRL1_TSAMPLESPACING_250ns (5UL) /*!< 0.25us */
#define RADIO_DFECTRL1_TSAMPLESPACING_125ns (6UL) /*!< 0.125us */

/* Bit 15 : Whether to sample I/Q or magnitude/phase */
#define RADIO_DFECTRL1_SAMPLETYPE_Pos       (15UL) /*!< Position of SAMPLETYPE field. */
#define RADIO_DFECTRL1_SAMPLETYPE_Msk                                                              \
  (0x1UL << RADIO_DFECTRL1_SAMPLETYPE_Pos)         /*!< Bit mask of SAMPLETYPE field. */
#define RADIO_DFECTRL1_SAMPLETYPE_IQ         (0UL) /*!< Complex samples in I and Q */
#define RADIO_DFECTRL1_SAMPLETYPE_MagPhase   (1UL) /*!< Complex samples as magnitude and phase */

/* Bits 14..12 : Interval between samples in the REFERENCE period */
#define RADIO_DFECTRL1_TSAMPLESPACINGREF_Pos (12UL) /*!< Position of TSAMPLESPACINGREF field. */
#define RADIO_DFECTRL1_TSAMPLESPACINGREF_Msk                                                       \
  (0x7UL << RADIO_DFECTRL1_TSAMPLESPACINGREF_Pos)    /*!< Bit mask of TSAMPLESPACINGREF field. */
#define RADIO_DFECTRL1_TSAMPLESPACINGREF_4us   (1UL) /*!< 4us */
#define RADIO_DFECTRL1_TSAMPLESPACINGREF_2us   (2UL) /*!< 2us */
#define RADIO_DFECTRL1_TSAMPLESPACINGREF_1us   (3UL) /*!< 1us */
#define RADIO_DFECTRL1_TSAMPLESPACINGREF_500ns (4UL) /*!< 0.5us */
#define RADIO_DFECTRL1_TSAMPLESPACINGREF_250ns (5UL) /*!< 0.25us */
#define RADIO_DFECTRL1_TSAMPLESPACINGREF_125ns (6UL) /*!< 0.125us */

/* Bits 10..8 : Interval between every time the antenna is changed in the SWITCHING state */
#define RADIO_DFECTRL1_TSWITCHSPACING_Pos      (8UL) /*!< Position of TSWITCHSPACING field. */
#define RADIO_DFECTRL1_TSWITCHSPACING_Msk                                                          \
  (0x7UL << RADIO_DFECTRL1_TSWITCHSPACING_Pos)  /*!< Bit mask of TSWITCHSPACING field. */
#define RADIO_DFECTRL1_TSWITCHSPACING_4us (1UL) /*!< 4us */
#define RADIO_DFECTRL1_TSWITCHSPACING_2us (2UL) /*!< 2us */
#define RADIO_DFECTRL1_TSWITCHSPACING_1us (3UL) /*!< 1us */

/* Bit 7 : Add CTE extension and do antenna switching/sampling in this extension */
#define RADIO_DFECTRL1_DFEINEXTENSION_Pos (7UL) /*!< Position of DFEINEXTENSION field. */
#define RADIO_DFECTRL1_DFEINEXTENSION_Msk                                                          \
  (0x1UL << RADIO_DFECTRL1_DFEINEXTENSION_Pos) /*!< Bit mask of DFEINEXTENSION field. */
#define RADIO_DFECTRL1_DFEINEXTENSION_Payload                                                      \
  (0UL) /*!< Antenna switching/sampling is done in the packet payload */
#define RADIO_DFECTRL1_DFEINEXTENSION_CRC (1UL) /*!< AoA/AoD procedure triggered at end of CRC */

/* Bits 5..0 : Length of the AoA/AoD procedure in number of 8 us units */
#define RADIO_DFECTRL1_NUMBEROF8US_Pos    (0UL) /*!< Position of NUMBEROF8US field. */
#define RADIO_DFECTRL1_NUMBEROF8US_Msk                                                             \
  (0x3FUL << RADIO_DFECTRL1_NUMBEROF8US_Pos) /*!< Bit mask of NUMBEROF8US field. */

/* Register: RADIO_DFECTRL2 */
/* Description: Start offset for Direction finding */

/* Bits 27..16 : Signed value offset before starting sampling in number of 16M cycles relative to the beginning of the REFERENCE state - 12 us after switching start */
#define RADIO_DFECTRL2_TSAMPLEOFFSET_Pos (16UL) /*!< Position of TSAMPLEOFFSET field. */
#define RADIO_DFECTRL2_TSAMPLEOFFSET_Msk                                                           \
  (0xFFFUL << RADIO_DFECTRL2_TSAMPLEOFFSET_Pos) /*!< Bit mask of TSAMPLEOFFSET field. */

/* Bits 12..0 : Signed value offset after the end of the CRC before starting switching in number of 16M cycles */
#define RADIO_DFECTRL2_TSWITCHOFFSET_Pos (0UL) /*!< Position of TSWITCHOFFSET field. */
#define RADIO_DFECTRL2_TSWITCHOFFSET_Msk                                                           \
  (0x1FFFUL << RADIO_DFECTRL2_TSWITCHOFFSET_Pos) /*!< Bit mask of TSWITCHOFFSET field. */

/* Register: RADIO_SWITCHPATTERN */
/* Description: GPIO patterns to be used for each antenna */

/* Bits 7..0 : Fill array of GPIO patterns for antenna control */
#define RADIO_SWITCHPATTERN_SWITCHPATTERN_Pos (0UL) /*!< Position of SWITCHPATTERN field. */
#define RADIO_SWITCHPATTERN_SWITCHPATTERN_Msk                                                      \
  (0xFFUL << RADIO_SWITCHPATTERN_SWITCHPATTERN_Pos) /*!< Bit mask of SWITCHPATTERN field. */

/* Register: RADIO_CLEARPATTERN */
/* Description: Clear the GPIO pattern array for antenna control */

/* Bit 0 : Clears GPIO pattern array for antenna control */
#define RADIO_CLEARPATTERN_CLEARPATTERN_Pos (0UL) /*!< Position of CLEARPATTERN field. */
#define RADIO_CLEARPATTERN_CLEARPATTERN_Msk                                                        \
  (0x1UL << RADIO_CLEARPATTERN_CLEARPATTERN_Pos)    /*!< Bit mask of CLEARPATTERN field. */
#define RADIO_CLEARPATTERN_CLEARPATTERN_Clear (1UL) /*!< Clear the GPIO pattern */

/* Register: RADIO_PSEL_DFEGPIO */
/* Description: Description collection: Pin select for DFE pin n */

/* Bit 31 : Connection */
#define RADIO_PSEL_DFEGPIO_CONNECT_Pos        (31UL) /*!< Position of CONNECT field. */
#define RADIO_PSEL_DFEGPIO_CONNECT_Msk                                                             \
  (0x1UL << RADIO_PSEL_DFEGPIO_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define RADIO_PSEL_DFEGPIO_CONNECT_Connected    (0UL) /*!< Connect */
#define RADIO_PSEL_DFEGPIO_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define RADIO_PSEL_DFEGPIO_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define RADIO_PSEL_DFEGPIO_PIN_Msk                                                                 \
  (0x1FUL << RADIO_PSEL_DFEGPIO_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: RADIO_DFEPACKET_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define RADIO_DFEPACKET_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define RADIO_DFEPACKET_PTR_PTR_Msk                                                                \
  (0xFFFFFFFFUL << RADIO_DFEPACKET_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: RADIO_DFEPACKET_MAXCNT */
/* Description: Maximum number of buffer words to transfer */

/* Bits 13..0 : Maximum number of buffer words to transfer */
#define RADIO_DFEPACKET_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define RADIO_DFEPACKET_MAXCNT_MAXCNT_Msk                                                          \
  (0x3FFFUL << RADIO_DFEPACKET_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: RADIO_DFEPACKET_AMOUNT */
/* Description: Number of samples transferred in the last transaction */

/* Bits 15..0 : Number of samples transferred in the last transaction */
#define RADIO_DFEPACKET_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define RADIO_DFEPACKET_AMOUNT_AMOUNT_Msk                                                          \
  (0xFFFFUL << RADIO_DFEPACKET_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: RADIO_POWER */
/* Description: Peripheral power control */

/* Bit 0 : Peripheral power control. The peripheral and its registers will be reset to its initial state by switching the peripheral off and then back on again. */
#define RADIO_POWER_POWER_Pos           (0UL) /*!< Position of POWER field. */
#define RADIO_POWER_POWER_Msk           (0x1UL << RADIO_POWER_POWER_Pos) /*!< Bit mask of POWER field. */
#define RADIO_POWER_POWER_Disabled      (0UL) /*!< Peripheral is powered off */
#define RADIO_POWER_POWER_Enabled       (1UL) /*!< Peripheral is powered on */


/* Peripheral: RNG */
/* Description: Random Number Generator */

/* Register: RNG_TASKS_START */
/* Description: Task starting the random number generator */

/* Bit 0 : Task starting the random number generator */
#define RNG_TASKS_START_TASKS_START_Pos (0UL) /*!< Position of TASKS_START field. */
#define RNG_TASKS_START_TASKS_START_Msk                                                            \
  (0x1UL << RNG_TASKS_START_TASKS_START_Pos)      /*!< Bit mask of TASKS_START field. */
#define RNG_TASKS_START_TASKS_START_Trigger (1UL) /*!< Trigger task */

/* Register: RNG_TASKS_STOP */
/* Description: Task stopping the random number generator */

/* Bit 0 : Task stopping the random number generator */
#define RNG_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define RNG_TASKS_STOP_TASKS_STOP_Msk                                                              \
  (0x1UL << RNG_TASKS_STOP_TASKS_STOP_Pos)        /*!< Bit mask of TASKS_STOP field. */
#define RNG_TASKS_STOP_TASKS_STOP_Trigger   (1UL) /*!< Trigger task */

/* Register: RNG_EVENTS_VALRDY */
/* Description: Event being generated for every new random number written to the VALUE register */

/* Bit 0 : Event being generated for every new random number written to the VALUE register */
#define RNG_EVENTS_VALRDY_EVENTS_VALRDY_Pos (0UL) /*!< Position of EVENTS_VALRDY field. */
#define RNG_EVENTS_VALRDY_EVENTS_VALRDY_Msk                                                        \
  (0x1UL << RNG_EVENTS_VALRDY_EVENTS_VALRDY_Pos)           /*!< Bit mask of EVENTS_VALRDY field. */
#define RNG_EVENTS_VALRDY_EVENTS_VALRDY_NotGenerated (0UL) /*!< Event not generated */
#define RNG_EVENTS_VALRDY_EVENTS_VALRDY_Generated    (1UL) /*!< Event generated */

/* Register: RNG_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 0 : Shortcut between event VALRDY and task STOP */
#define RNG_SHORTS_VALRDY_STOP_Pos                   (0UL) /*!< Position of VALRDY_STOP field. */
#define RNG_SHORTS_VALRDY_STOP_Msk                                                                 \
  (0x1UL << RNG_SHORTS_VALRDY_STOP_Pos)       /*!< Bit mask of VALRDY_STOP field. */
#define RNG_SHORTS_VALRDY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define RNG_SHORTS_VALRDY_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Register: RNG_INTENSET */
/* Description: Enable interrupt */

/* Bit 0 : Write '1' to enable interrupt for event VALRDY */
#define RNG_INTENSET_VALRDY_Pos         (0UL) /*!< Position of VALRDY field. */
#define RNG_INTENSET_VALRDY_Msk         (0x1UL << RNG_INTENSET_VALRDY_Pos) /*!< Bit mask of VALRDY field. */
#define RNG_INTENSET_VALRDY_Disabled    (0UL)                              /*!< Read: Disabled */
#define RNG_INTENSET_VALRDY_Enabled     (1UL)                              /*!< Read: Enabled */
#define RNG_INTENSET_VALRDY_Set         (1UL)                              /*!< Enable */

/* Register: RNG_INTENCLR */
/* Description: Disable interrupt */

/* Bit 0 : Write '1' to disable interrupt for event VALRDY */
#define RNG_INTENCLR_VALRDY_Pos         (0UL) /*!< Position of VALRDY field. */
#define RNG_INTENCLR_VALRDY_Msk         (0x1UL << RNG_INTENCLR_VALRDY_Pos) /*!< Bit mask of VALRDY field. */
#define RNG_INTENCLR_VALRDY_Disabled    (0UL)                              /*!< Read: Disabled */
#define RNG_INTENCLR_VALRDY_Enabled     (1UL)                              /*!< Read: Enabled */
#define RNG_INTENCLR_VALRDY_Clear       (1UL)                              /*!< Disable */

/* Register: RNG_CONFIG */
/* Description: Configuration register */

/* Bit 0 : Bias correction */
#define RNG_CONFIG_DERCEN_Pos           (0UL) /*!< Position of DERCEN field. */
#define RNG_CONFIG_DERCEN_Msk           (0x1UL << RNG_CONFIG_DERCEN_Pos) /*!< Bit mask of DERCEN field. */
#define RNG_CONFIG_DERCEN_Disabled      (0UL)                            /*!< Disabled */
#define RNG_CONFIG_DERCEN_Enabled       (1UL)                            /*!< Enabled */

/* Register: RNG_VALUE */
/* Description: Output random number */

/* Bits 7..0 : Generated random number */
#define RNG_VALUE_VALUE_Pos             (0UL) /*!< Position of VALUE field. */
#define RNG_VALUE_VALUE_Msk             (0xFFUL << RNG_VALUE_VALUE_Pos) /*!< Bit mask of VALUE field. */


/* Peripheral: RTC */
/* Description: Real time counter 0 */

/* Register: RTC_TASKS_START */
/* Description: Start RTC COUNTER */

/* Bit 0 : Start RTC COUNTER */
#define RTC_TASKS_START_TASKS_START_Pos (0UL) /*!< Position of TASKS_START field. */
#define RTC_TASKS_START_TASKS_START_Msk                                                            \
  (0x1UL << RTC_TASKS_START_TASKS_START_Pos)      /*!< Bit mask of TASKS_START field. */
#define RTC_TASKS_START_TASKS_START_Trigger (1UL) /*!< Trigger task */

/* Register: RTC_TASKS_STOP */
/* Description: Stop RTC COUNTER */

/* Bit 0 : Stop RTC COUNTER */
#define RTC_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define RTC_TASKS_STOP_TASKS_STOP_Msk                                                              \
  (0x1UL << RTC_TASKS_STOP_TASKS_STOP_Pos)      /*!< Bit mask of TASKS_STOP field. */
#define RTC_TASKS_STOP_TASKS_STOP_Trigger (1UL) /*!< Trigger task */

/* Register: RTC_TASKS_CLEAR */
/* Description: Clear RTC COUNTER */

/* Bit 0 : Clear RTC COUNTER */
#define RTC_TASKS_CLEAR_TASKS_CLEAR_Pos   (0UL) /*!< Position of TASKS_CLEAR field. */
#define RTC_TASKS_CLEAR_TASKS_CLEAR_Msk                                                            \
  (0x1UL << RTC_TASKS_CLEAR_TASKS_CLEAR_Pos)            /*!< Bit mask of TASKS_CLEAR field. */
#define RTC_TASKS_CLEAR_TASKS_CLEAR_Trigger       (1UL) /*!< Trigger task */

/* Register: RTC_TASKS_TRIGOVRFLW */
/* Description: Set COUNTER to 0xFFFFF0 */

/* Bit 0 : Set COUNTER to 0xFFFFF0 */
#define RTC_TASKS_TRIGOVRFLW_TASKS_TRIGOVRFLW_Pos (0UL) /*!< Position of TASKS_TRIGOVRFLW field. */
#define RTC_TASKS_TRIGOVRFLW_TASKS_TRIGOVRFLW_Msk                                                  \
  (0x1UL << RTC_TASKS_TRIGOVRFLW_TASKS_TRIGOVRFLW_Pos) /*!< Bit mask of TASKS_TRIGOVRFLW field. */
#define RTC_TASKS_TRIGOVRFLW_TASKS_TRIGOVRFLW_Trigger (1UL) /*!< Trigger task */

/* Register: RTC_EVENTS_TICK */
/* Description: Event on COUNTER increment */

/* Bit 0 : Event on COUNTER increment */
#define RTC_EVENTS_TICK_EVENTS_TICK_Pos               (0UL) /*!< Position of EVENTS_TICK field. */
#define RTC_EVENTS_TICK_EVENTS_TICK_Msk                                                            \
  (0x1UL << RTC_EVENTS_TICK_EVENTS_TICK_Pos)           /*!< Bit mask of EVENTS_TICK field. */
#define RTC_EVENTS_TICK_EVENTS_TICK_NotGenerated (0UL) /*!< Event not generated */
#define RTC_EVENTS_TICK_EVENTS_TICK_Generated    (1UL) /*!< Event generated */

/* Register: RTC_EVENTS_OVRFLW */
/* Description: Event on COUNTER overflow */

/* Bit 0 : Event on COUNTER overflow */
#define RTC_EVENTS_OVRFLW_EVENTS_OVRFLW_Pos      (0UL) /*!< Position of EVENTS_OVRFLW field. */
#define RTC_EVENTS_OVRFLW_EVENTS_OVRFLW_Msk                                                        \
  (0x1UL << RTC_EVENTS_OVRFLW_EVENTS_OVRFLW_Pos)           /*!< Bit mask of EVENTS_OVRFLW field. */
#define RTC_EVENTS_OVRFLW_EVENTS_OVRFLW_NotGenerated (0UL) /*!< Event not generated */
#define RTC_EVENTS_OVRFLW_EVENTS_OVRFLW_Generated    (1UL) /*!< Event generated */

/* Register: RTC_EVENTS_COMPARE */
/* Description: Description collection: Compare event on CC[n] match */

/* Bit 0 : Compare event on CC[n] match */
#define RTC_EVENTS_COMPARE_EVENTS_COMPARE_Pos        (0UL) /*!< Position of EVENTS_COMPARE field. */
#define RTC_EVENTS_COMPARE_EVENTS_COMPARE_Msk                                                      \
  (0x1UL << RTC_EVENTS_COMPARE_EVENTS_COMPARE_Pos) /*!< Bit mask of EVENTS_COMPARE field. */
#define RTC_EVENTS_COMPARE_EVENTS_COMPARE_NotGenerated (0UL) /*!< Event not generated */
#define RTC_EVENTS_COMPARE_EVENTS_COMPARE_Generated    (1UL) /*!< Event generated */

/* Register: RTC_INTENSET */
/* Description: Enable interrupt */

/* Bit 19 : Write '1' to enable interrupt for event COMPARE[3] */
#define RTC_INTENSET_COMPARE3_Pos                      (19UL) /*!< Position of COMPARE3 field. */
#define RTC_INTENSET_COMPARE3_Msk                                                                  \
  (0x1UL << RTC_INTENSET_COMPARE3_Pos)       /*!< Bit mask of COMPARE3 field. */
#define RTC_INTENSET_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_COMPARE3_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_COMPARE3_Set      (1UL) /*!< Enable */

/* Bit 18 : Write '1' to enable interrupt for event COMPARE[2] */
#define RTC_INTENSET_COMPARE2_Pos      (18UL) /*!< Position of COMPARE2 field. */
#define RTC_INTENSET_COMPARE2_Msk                                                                  \
  (0x1UL << RTC_INTENSET_COMPARE2_Pos)       /*!< Bit mask of COMPARE2 field. */
#define RTC_INTENSET_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_COMPARE2_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_COMPARE2_Set      (1UL) /*!< Enable */

/* Bit 17 : Write '1' to enable interrupt for event COMPARE[1] */
#define RTC_INTENSET_COMPARE1_Pos      (17UL) /*!< Position of COMPARE1 field. */
#define RTC_INTENSET_COMPARE1_Msk                                                                  \
  (0x1UL << RTC_INTENSET_COMPARE1_Pos)       /*!< Bit mask of COMPARE1 field. */
#define RTC_INTENSET_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_COMPARE1_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_COMPARE1_Set      (1UL) /*!< Enable */

/* Bit 16 : Write '1' to enable interrupt for event COMPARE[0] */
#define RTC_INTENSET_COMPARE0_Pos      (16UL) /*!< Position of COMPARE0 field. */
#define RTC_INTENSET_COMPARE0_Msk                                                                  \
  (0x1UL << RTC_INTENSET_COMPARE0_Pos)       /*!< Bit mask of COMPARE0 field. */
#define RTC_INTENSET_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_COMPARE0_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_COMPARE0_Set      (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event OVRFLW */
#define RTC_INTENSET_OVRFLW_Pos        (1UL) /*!< Position of OVRFLW field. */
#define RTC_INTENSET_OVRFLW_Msk        (0x1UL << RTC_INTENSET_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_INTENSET_OVRFLW_Disabled   (0UL)                              /*!< Read: Disabled */
#define RTC_INTENSET_OVRFLW_Enabled    (1UL)                              /*!< Read: Enabled */
#define RTC_INTENSET_OVRFLW_Set        (1UL)                              /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event TICK */
#define RTC_INTENSET_TICK_Pos          (0UL) /*!< Position of TICK field. */
#define RTC_INTENSET_TICK_Msk          (0x1UL << RTC_INTENSET_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_INTENSET_TICK_Disabled     (0UL)                            /*!< Read: Disabled */
#define RTC_INTENSET_TICK_Enabled      (1UL)                            /*!< Read: Enabled */
#define RTC_INTENSET_TICK_Set          (1UL)                            /*!< Enable */

/* Register: RTC_INTENCLR */
/* Description: Disable interrupt */

/* Bit 19 : Write '1' to disable interrupt for event COMPARE[3] */
#define RTC_INTENCLR_COMPARE3_Pos      (19UL) /*!< Position of COMPARE3 field. */
#define RTC_INTENCLR_COMPARE3_Msk                                                                  \
  (0x1UL << RTC_INTENCLR_COMPARE3_Pos)       /*!< Bit mask of COMPARE3 field. */
#define RTC_INTENCLR_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_COMPARE3_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_COMPARE3_Clear    (1UL) /*!< Disable */

/* Bit 18 : Write '1' to disable interrupt for event COMPARE[2] */
#define RTC_INTENCLR_COMPARE2_Pos      (18UL) /*!< Position of COMPARE2 field. */
#define RTC_INTENCLR_COMPARE2_Msk                                                                  \
  (0x1UL << RTC_INTENCLR_COMPARE2_Pos)       /*!< Bit mask of COMPARE2 field. */
#define RTC_INTENCLR_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_COMPARE2_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_COMPARE2_Clear    (1UL) /*!< Disable */

/* Bit 17 : Write '1' to disable interrupt for event COMPARE[1] */
#define RTC_INTENCLR_COMPARE1_Pos      (17UL) /*!< Position of COMPARE1 field. */
#define RTC_INTENCLR_COMPARE1_Msk                                                                  \
  (0x1UL << RTC_INTENCLR_COMPARE1_Pos)       /*!< Bit mask of COMPARE1 field. */
#define RTC_INTENCLR_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_COMPARE1_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_COMPARE1_Clear    (1UL) /*!< Disable */

/* Bit 16 : Write '1' to disable interrupt for event COMPARE[0] */
#define RTC_INTENCLR_COMPARE0_Pos      (16UL) /*!< Position of COMPARE0 field. */
#define RTC_INTENCLR_COMPARE0_Msk                                                                  \
  (0x1UL << RTC_INTENCLR_COMPARE0_Pos)       /*!< Bit mask of COMPARE0 field. */
#define RTC_INTENCLR_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_COMPARE0_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_COMPARE0_Clear    (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event OVRFLW */
#define RTC_INTENCLR_OVRFLW_Pos        (1UL) /*!< Position of OVRFLW field. */
#define RTC_INTENCLR_OVRFLW_Msk        (0x1UL << RTC_INTENCLR_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_INTENCLR_OVRFLW_Disabled   (0UL)                              /*!< Read: Disabled */
#define RTC_INTENCLR_OVRFLW_Enabled    (1UL)                              /*!< Read: Enabled */
#define RTC_INTENCLR_OVRFLW_Clear      (1UL)                              /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event TICK */
#define RTC_INTENCLR_TICK_Pos          (0UL) /*!< Position of TICK field. */
#define RTC_INTENCLR_TICK_Msk          (0x1UL << RTC_INTENCLR_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_INTENCLR_TICK_Disabled     (0UL)                            /*!< Read: Disabled */
#define RTC_INTENCLR_TICK_Enabled      (1UL)                            /*!< Read: Enabled */
#define RTC_INTENCLR_TICK_Clear        (1UL)                            /*!< Disable */

/* Register: RTC_EVTEN */
/* Description: Enable or disable event routing */

/* Bit 19 : Enable or disable event routing for event COMPARE[3] */
#define RTC_EVTEN_COMPARE3_Pos         (19UL) /*!< Position of COMPARE3 field. */
#define RTC_EVTEN_COMPARE3_Msk         (0x1UL << RTC_EVTEN_COMPARE3_Pos) /*!< Bit mask of COMPARE3 field. */
#define RTC_EVTEN_COMPARE3_Disabled    (0UL)                             /*!< Disable */
#define RTC_EVTEN_COMPARE3_Enabled     (1UL)                             /*!< Disable */

/* Bit 18 : Enable or disable event routing for event COMPARE[2] */
#define RTC_EVTEN_COMPARE2_Pos         (18UL) /*!< Position of COMPARE2 field. */
#define RTC_EVTEN_COMPARE2_Msk         (0x1UL << RTC_EVTEN_COMPARE2_Pos) /*!< Bit mask of COMPARE2 field. */
#define RTC_EVTEN_COMPARE2_Disabled    (0UL)                             /*!< Disable */
#define RTC_EVTEN_COMPARE2_Enabled     (1UL)                             /*!< Disable */

/* Bit 17 : Enable or disable event routing for event COMPARE[1] */
#define RTC_EVTEN_COMPARE1_Pos         (17UL) /*!< Position of COMPARE1 field. */
#define RTC_EVTEN_COMPARE1_Msk         (0x1UL << RTC_EVTEN_COMPARE1_Pos) /*!< Bit mask of COMPARE1 field. */
#define RTC_EVTEN_COMPARE1_Disabled    (0UL)                             /*!< Disable */
#define RTC_EVTEN_COMPARE1_Enabled     (1UL)                             /*!< Disable */

/* Bit 16 : Enable or disable event routing for event COMPARE[0] */
#define RTC_EVTEN_COMPARE0_Pos         (16UL) /*!< Position of COMPARE0 field. */
#define RTC_EVTEN_COMPARE0_Msk         (0x1UL << RTC_EVTEN_COMPARE0_Pos) /*!< Bit mask of COMPARE0 field. */
#define RTC_EVTEN_COMPARE0_Disabled    (0UL)                             /*!< Disable */
#define RTC_EVTEN_COMPARE0_Enabled     (1UL)                             /*!< Disable */

/* Bit 1 : Enable or disable event routing for event OVRFLW */
#define RTC_EVTEN_OVRFLW_Pos           (1UL) /*!< Position of OVRFLW field. */
#define RTC_EVTEN_OVRFLW_Msk           (0x1UL << RTC_EVTEN_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_EVTEN_OVRFLW_Disabled      (0UL)                           /*!< Disable */
#define RTC_EVTEN_OVRFLW_Enabled       (1UL)                           /*!< Disable */

/* Bit 0 : Enable or disable event routing for event TICK */
#define RTC_EVTEN_TICK_Pos             (0UL)                         /*!< Position of TICK field. */
#define RTC_EVTEN_TICK_Msk             (0x1UL << RTC_EVTEN_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_EVTEN_TICK_Disabled        (0UL)                         /*!< Disable */
#define RTC_EVTEN_TICK_Enabled         (1UL)                         /*!< Disable */

/* Register: RTC_EVTENSET */
/* Description: Enable event routing */

/* Bit 19 : Write '1' to enable event routing for event COMPARE[3] */
#define RTC_EVTENSET_COMPARE3_Pos      (19UL) /*!< Position of COMPARE3 field. */
#define RTC_EVTENSET_COMPARE3_Msk                                                                  \
  (0x1UL << RTC_EVTENSET_COMPARE3_Pos)       /*!< Bit mask of COMPARE3 field. */
#define RTC_EVTENSET_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_COMPARE3_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_COMPARE3_Set      (1UL) /*!< Enable */

/* Bit 18 : Write '1' to enable event routing for event COMPARE[2] */
#define RTC_EVTENSET_COMPARE2_Pos      (18UL) /*!< Position of COMPARE2 field. */
#define RTC_EVTENSET_COMPARE2_Msk                                                                  \
  (0x1UL << RTC_EVTENSET_COMPARE2_Pos)       /*!< Bit mask of COMPARE2 field. */
#define RTC_EVTENSET_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_COMPARE2_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_COMPARE2_Set      (1UL) /*!< Enable */

/* Bit 17 : Write '1' to enable event routing for event COMPARE[1] */
#define RTC_EVTENSET_COMPARE1_Pos      (17UL) /*!< Position of COMPARE1 field. */
#define RTC_EVTENSET_COMPARE1_Msk                                                                  \
  (0x1UL << RTC_EVTENSET_COMPARE1_Pos)       /*!< Bit mask of COMPARE1 field. */
#define RTC_EVTENSET_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_COMPARE1_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_COMPARE1_Set      (1UL) /*!< Enable */

/* Bit 16 : Write '1' to enable event routing for event COMPARE[0] */
#define RTC_EVTENSET_COMPARE0_Pos      (16UL) /*!< Position of COMPARE0 field. */
#define RTC_EVTENSET_COMPARE0_Msk                                                                  \
  (0x1UL << RTC_EVTENSET_COMPARE0_Pos)       /*!< Bit mask of COMPARE0 field. */
#define RTC_EVTENSET_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_COMPARE0_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_COMPARE0_Set      (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable event routing for event OVRFLW */
#define RTC_EVTENSET_OVRFLW_Pos        (1UL) /*!< Position of OVRFLW field. */
#define RTC_EVTENSET_OVRFLW_Msk        (0x1UL << RTC_EVTENSET_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_EVTENSET_OVRFLW_Disabled   (0UL)                              /*!< Read: Disabled */
#define RTC_EVTENSET_OVRFLW_Enabled    (1UL)                              /*!< Read: Enabled */
#define RTC_EVTENSET_OVRFLW_Set        (1UL)                              /*!< Enable */

/* Bit 0 : Write '1' to enable event routing for event TICK */
#define RTC_EVTENSET_TICK_Pos          (0UL) /*!< Position of TICK field. */
#define RTC_EVTENSET_TICK_Msk          (0x1UL << RTC_EVTENSET_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_EVTENSET_TICK_Disabled     (0UL)                            /*!< Read: Disabled */
#define RTC_EVTENSET_TICK_Enabled      (1UL)                            /*!< Read: Enabled */
#define RTC_EVTENSET_TICK_Set          (1UL)                            /*!< Enable */

/* Register: RTC_EVTENCLR */
/* Description: Disable event routing */

/* Bit 19 : Write '1' to disable event routing for event COMPARE[3] */
#define RTC_EVTENCLR_COMPARE3_Pos      (19UL) /*!< Position of COMPARE3 field. */
#define RTC_EVTENCLR_COMPARE3_Msk                                                                  \
  (0x1UL << RTC_EVTENCLR_COMPARE3_Pos)       /*!< Bit mask of COMPARE3 field. */
#define RTC_EVTENCLR_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_COMPARE3_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_COMPARE3_Clear    (1UL) /*!< Disable */

/* Bit 18 : Write '1' to disable event routing for event COMPARE[2] */
#define RTC_EVTENCLR_COMPARE2_Pos      (18UL) /*!< Position of COMPARE2 field. */
#define RTC_EVTENCLR_COMPARE2_Msk                                                                  \
  (0x1UL << RTC_EVTENCLR_COMPARE2_Pos)       /*!< Bit mask of COMPARE2 field. */
#define RTC_EVTENCLR_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_COMPARE2_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_COMPARE2_Clear    (1UL) /*!< Disable */

/* Bit 17 : Write '1' to disable event routing for event COMPARE[1] */
#define RTC_EVTENCLR_COMPARE1_Pos      (17UL) /*!< Position of COMPARE1 field. */
#define RTC_EVTENCLR_COMPARE1_Msk                                                                  \
  (0x1UL << RTC_EVTENCLR_COMPARE1_Pos)       /*!< Bit mask of COMPARE1 field. */
#define RTC_EVTENCLR_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_COMPARE1_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_COMPARE1_Clear    (1UL) /*!< Disable */

/* Bit 16 : Write '1' to disable event routing for event COMPARE[0] */
#define RTC_EVTENCLR_COMPARE0_Pos      (16UL) /*!< Position of COMPARE0 field. */
#define RTC_EVTENCLR_COMPARE0_Msk                                                                  \
  (0x1UL << RTC_EVTENCLR_COMPARE0_Pos)       /*!< Bit mask of COMPARE0 field. */
#define RTC_EVTENCLR_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_COMPARE0_Enabled  (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_COMPARE0_Clear    (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable event routing for event OVRFLW */
#define RTC_EVTENCLR_OVRFLW_Pos        (1UL) /*!< Position of OVRFLW field. */
#define RTC_EVTENCLR_OVRFLW_Msk        (0x1UL << RTC_EVTENCLR_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_EVTENCLR_OVRFLW_Disabled   (0UL)                              /*!< Read: Disabled */
#define RTC_EVTENCLR_OVRFLW_Enabled    (1UL)                              /*!< Read: Enabled */
#define RTC_EVTENCLR_OVRFLW_Clear      (1UL)                              /*!< Disable */

/* Bit 0 : Write '1' to disable event routing for event TICK */
#define RTC_EVTENCLR_TICK_Pos          (0UL) /*!< Position of TICK field. */
#define RTC_EVTENCLR_TICK_Msk          (0x1UL << RTC_EVTENCLR_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_EVTENCLR_TICK_Disabled     (0UL)                            /*!< Read: Disabled */
#define RTC_EVTENCLR_TICK_Enabled      (1UL)                            /*!< Read: Enabled */
#define RTC_EVTENCLR_TICK_Clear        (1UL)                            /*!< Disable */

/* Register: RTC_COUNTER */
/* Description: Current COUNTER value */

/* Bits 23..0 : Counter value */
#define RTC_COUNTER_COUNTER_Pos        (0UL) /*!< Position of COUNTER field. */
#define RTC_COUNTER_COUNTER_Msk                                                                    \
  (0xFFFFFFUL << RTC_COUNTER_COUNTER_Pos) /*!< Bit mask of COUNTER field. */

/* Register: RTC_PRESCALER */
/* Description: 12 bit prescaler for COUNTER frequency (32768/(PRESCALER+1)).Must be written when RTC is stopped */

/* Bits 11..0 : Prescaler value */
#define RTC_PRESCALER_PRESCALER_Pos (0UL) /*!< Position of PRESCALER field. */
#define RTC_PRESCALER_PRESCALER_Msk                                                                \
  (0xFFFUL << RTC_PRESCALER_PRESCALER_Pos) /*!< Bit mask of PRESCALER field. */

/* Register: RTC_CC */
/* Description: Description collection: Compare register n */

/* Bits 23..0 : Compare value */
#define RTC_CC_COMPARE_Pos                (0UL) /*!< Position of COMPARE field. */
#define RTC_CC_COMPARE_Msk                (0xFFFFFFUL << RTC_CC_COMPARE_Pos) /*!< Bit mask of COMPARE field. */


/* Peripheral: SPI */
/* Description: Serial Peripheral Interface 0 */

/* Register: SPI_EVENTS_READY */
/* Description: TXD byte sent and RXD byte received */

/* Bit 0 : TXD byte sent and RXD byte received */
#define SPI_EVENTS_READY_EVENTS_READY_Pos (0UL) /*!< Position of EVENTS_READY field. */
#define SPI_EVENTS_READY_EVENTS_READY_Msk                                                          \
  (0x1UL << SPI_EVENTS_READY_EVENTS_READY_Pos)           /*!< Bit mask of EVENTS_READY field. */
#define SPI_EVENTS_READY_EVENTS_READY_NotGenerated (0UL) /*!< Event not generated */
#define SPI_EVENTS_READY_EVENTS_READY_Generated    (1UL) /*!< Event generated */

/* Register: SPI_INTENSET */
/* Description: Enable interrupt */

/* Bit 2 : Write '1' to enable interrupt for event READY */
#define SPI_INTENSET_READY_Pos                     (2UL) /*!< Position of READY field. */
#define SPI_INTENSET_READY_Msk                     (0x1UL << SPI_INTENSET_READY_Pos) /*!< Bit mask of READY field. */
#define SPI_INTENSET_READY_Disabled                (0UL) /*!< Read: Disabled */
#define SPI_INTENSET_READY_Enabled                 (1UL) /*!< Read: Enabled */
#define SPI_INTENSET_READY_Set                     (1UL) /*!< Enable */

/* Register: SPI_INTENCLR */
/* Description: Disable interrupt */

/* Bit 2 : Write '1' to disable interrupt for event READY */
#define SPI_INTENCLR_READY_Pos                     (2UL) /*!< Position of READY field. */
#define SPI_INTENCLR_READY_Msk                     (0x1UL << SPI_INTENCLR_READY_Pos) /*!< Bit mask of READY field. */
#define SPI_INTENCLR_READY_Disabled                (0UL) /*!< Read: Disabled */
#define SPI_INTENCLR_READY_Enabled                 (1UL) /*!< Read: Enabled */
#define SPI_INTENCLR_READY_Clear                   (1UL) /*!< Disable */

/* Register: SPI_ENABLE */
/* Description: Enable SPI */

/* Bits 3..0 : Enable or disable SPI */
#define SPI_ENABLE_ENABLE_Pos                      (0UL) /*!< Position of ENABLE field. */
#define SPI_ENABLE_ENABLE_Msk                      (0xFUL << SPI_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define SPI_ENABLE_ENABLE_Disabled                 (0UL) /*!< Disable SPI */
#define SPI_ENABLE_ENABLE_Enabled                  (1UL) /*!< Enable SPI */

/* Register: SPI_PSEL_SCK */
/* Description: Pin select for SCK */

/* Bit 31 : Connection */
#define SPI_PSEL_SCK_CONNECT_Pos                   (31UL) /*!< Position of CONNECT field. */
#define SPI_PSEL_SCK_CONNECT_Msk                                                                   \
  (0x1UL << SPI_PSEL_SCK_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPI_PSEL_SCK_CONNECT_Connected    (0UL) /*!< Connect */
#define SPI_PSEL_SCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPI_PSEL_SCK_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPI_PSEL_SCK_PIN_Msk              (0x1FUL << SPI_PSEL_SCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPI_PSEL_MOSI */
/* Description: Pin select for MOSI signal */

/* Bit 31 : Connection */
#define SPI_PSEL_MOSI_CONNECT_Pos         (31UL) /*!< Position of CONNECT field. */
#define SPI_PSEL_MOSI_CONNECT_Msk                                                                  \
  (0x1UL << SPI_PSEL_MOSI_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPI_PSEL_MOSI_CONNECT_Connected    (0UL) /*!< Connect */
#define SPI_PSEL_MOSI_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPI_PSEL_MOSI_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPI_PSEL_MOSI_PIN_Msk              (0x1FUL << SPI_PSEL_MOSI_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPI_PSEL_MISO */
/* Description: Pin select for MISO signal */

/* Bit 31 : Connection */
#define SPI_PSEL_MISO_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define SPI_PSEL_MISO_CONNECT_Msk                                                                  \
  (0x1UL << SPI_PSEL_MISO_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPI_PSEL_MISO_CONNECT_Connected    (0UL) /*!< Connect */
#define SPI_PSEL_MISO_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPI_PSEL_MISO_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPI_PSEL_MISO_PIN_Msk              (0x1FUL << SPI_PSEL_MISO_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPI_RXD */
/* Description: RXD register */

/* Bits 7..0 : RX data received. Double buffered */
#define SPI_RXD_RXD_Pos                    (0UL) /*!< Position of RXD field. */
#define SPI_RXD_RXD_Msk                    (0xFFUL << SPI_RXD_RXD_Pos) /*!< Bit mask of RXD field. */

/* Register: SPI_TXD */
/* Description: TXD register */

/* Bits 7..0 : TX data to send. Double buffered */
#define SPI_TXD_TXD_Pos                    (0UL) /*!< Position of TXD field. */
#define SPI_TXD_TXD_Msk                    (0xFFUL << SPI_TXD_TXD_Pos) /*!< Bit mask of TXD field. */

/* Register: SPI_FREQUENCY */
/* Description: SPI frequency. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : SPI master data rate */
#define SPI_FREQUENCY_FREQUENCY_Pos        (0UL) /*!< Position of FREQUENCY field. */
#define SPI_FREQUENCY_FREQUENCY_Msk                                                                \
  (0xFFFFFFFFUL << SPI_FREQUENCY_FREQUENCY_Pos)     /*!< Bit mask of FREQUENCY field. */
#define SPI_FREQUENCY_FREQUENCY_K125 (0x02000000UL) /*!< 125 kbps */
#define SPI_FREQUENCY_FREQUENCY_K250 (0x04000000UL) /*!< 250 kbps */
#define SPI_FREQUENCY_FREQUENCY_K500 (0x08000000UL) /*!< 500 kbps */
#define SPI_FREQUENCY_FREQUENCY_M1   (0x10000000UL) /*!< 1 Mbps */
#define SPI_FREQUENCY_FREQUENCY_M2   (0x20000000UL) /*!< 2 Mbps */
#define SPI_FREQUENCY_FREQUENCY_M4   (0x40000000UL) /*!< 4 Mbps */
#define SPI_FREQUENCY_FREQUENCY_M8   (0x80000000UL) /*!< 8 Mbps */

/* Register: SPI_CONFIG */
/* Description: Configuration register */

/* Bit 2 : Serial clock (SCK) polarity */
#define SPI_CONFIG_CPOL_Pos          (2UL)                          /*!< Position of CPOL field. */
#define SPI_CONFIG_CPOL_Msk          (0x1UL << SPI_CONFIG_CPOL_Pos) /*!< Bit mask of CPOL field. */
#define SPI_CONFIG_CPOL_ActiveHigh   (0UL)                          /*!< Active high */
#define SPI_CONFIG_CPOL_ActiveLow    (1UL)                          /*!< Active low */

/* Bit 1 : Serial clock (SCK) phase */
#define SPI_CONFIG_CPHA_Pos          (1UL)                          /*!< Position of CPHA field. */
#define SPI_CONFIG_CPHA_Msk          (0x1UL << SPI_CONFIG_CPHA_Pos) /*!< Bit mask of CPHA field. */
#define SPI_CONFIG_CPHA_Leading                                                                    \
  (0UL) /*!< Sample on leading edge of clock, shift serial data on trailing edge */
#define SPI_CONFIG_CPHA_Trailing                                                                   \
  (1UL) /*!< Sample on trailing edge of clock, shift serial data on leading edge */

/* Bit 0 : Bit order */
#define SPI_CONFIG_ORDER_Pos             (0UL) /*!< Position of ORDER field. */
#define SPI_CONFIG_ORDER_Msk             (0x1UL << SPI_CONFIG_ORDER_Pos) /*!< Bit mask of ORDER field. */
#define SPI_CONFIG_ORDER_MsbFirst        (0UL) /*!< Most significant bit shifted out first */
#define SPI_CONFIG_ORDER_LsbFirst        (1UL) /*!< Least significant bit shifted out first */


/* Peripheral: SPIM */
/* Description: Serial Peripheral Interface Master with EasyDMA 0 */

/* Register: SPIM_TASKS_START */
/* Description: Start SPI transaction */

/* Bit 0 : Start SPI transaction */
#define SPIM_TASKS_START_TASKS_START_Pos (0UL) /*!< Position of TASKS_START field. */
#define SPIM_TASKS_START_TASKS_START_Msk                                                           \
  (0x1UL << SPIM_TASKS_START_TASKS_START_Pos)      /*!< Bit mask of TASKS_START field. */
#define SPIM_TASKS_START_TASKS_START_Trigger (1UL) /*!< Trigger task */

/* Register: SPIM_TASKS_STOP */
/* Description: Stop SPI transaction */

/* Bit 0 : Stop SPI transaction */
#define SPIM_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define SPIM_TASKS_STOP_TASKS_STOP_Msk                                                             \
  (0x1UL << SPIM_TASKS_STOP_TASKS_STOP_Pos)        /*!< Bit mask of TASKS_STOP field. */
#define SPIM_TASKS_STOP_TASKS_STOP_Trigger   (1UL) /*!< Trigger task */

/* Register: SPIM_TASKS_SUSPEND */
/* Description: Suspend SPI transaction */

/* Bit 0 : Suspend SPI transaction */
#define SPIM_TASKS_SUSPEND_TASKS_SUSPEND_Pos (0UL) /*!< Position of TASKS_SUSPEND field. */
#define SPIM_TASKS_SUSPEND_TASKS_SUSPEND_Msk                                                       \
  (0x1UL << SPIM_TASKS_SUSPEND_TASKS_SUSPEND_Pos)      /*!< Bit mask of TASKS_SUSPEND field. */
#define SPIM_TASKS_SUSPEND_TASKS_SUSPEND_Trigger (1UL) /*!< Trigger task */

/* Register: SPIM_TASKS_RESUME */
/* Description: Resume SPI transaction */

/* Bit 0 : Resume SPI transaction */
#define SPIM_TASKS_RESUME_TASKS_RESUME_Pos       (0UL) /*!< Position of TASKS_RESUME field. */
#define SPIM_TASKS_RESUME_TASKS_RESUME_Msk                                                         \
  (0x1UL << SPIM_TASKS_RESUME_TASKS_RESUME_Pos)      /*!< Bit mask of TASKS_RESUME field. */
#define SPIM_TASKS_RESUME_TASKS_RESUME_Trigger (1UL) /*!< Trigger task */

/* Register: SPIM_EVENTS_STOPPED */
/* Description: SPI transaction has stopped */

/* Bit 0 : SPI transaction has stopped */
#define SPIM_EVENTS_STOPPED_EVENTS_STOPPED_Pos (0UL) /*!< Position of EVENTS_STOPPED field. */
#define SPIM_EVENTS_STOPPED_EVENTS_STOPPED_Msk                                                     \
  (0x1UL << SPIM_EVENTS_STOPPED_EVENTS_STOPPED_Pos) /*!< Bit mask of EVENTS_STOPPED field. */
#define SPIM_EVENTS_STOPPED_EVENTS_STOPPED_NotGenerated (0UL) /*!< Event not generated */
#define SPIM_EVENTS_STOPPED_EVENTS_STOPPED_Generated    (1UL) /*!< Event generated */

/* Register: SPIM_EVENTS_ENDRX */
/* Description: End of RXD buffer reached */

/* Bit 0 : End of RXD buffer reached */
#define SPIM_EVENTS_ENDRX_EVENTS_ENDRX_Pos              (0UL) /*!< Position of EVENTS_ENDRX field. */
#define SPIM_EVENTS_ENDRX_EVENTS_ENDRX_Msk                                                         \
  (0x1UL << SPIM_EVENTS_ENDRX_EVENTS_ENDRX_Pos)           /*!< Bit mask of EVENTS_ENDRX field. */
#define SPIM_EVENTS_ENDRX_EVENTS_ENDRX_NotGenerated (0UL) /*!< Event not generated */
#define SPIM_EVENTS_ENDRX_EVENTS_ENDRX_Generated    (1UL) /*!< Event generated */

/* Register: SPIM_EVENTS_END */
/* Description: End of RXD buffer and TXD buffer reached */

/* Bit 0 : End of RXD buffer and TXD buffer reached */
#define SPIM_EVENTS_END_EVENTS_END_Pos              (0UL) /*!< Position of EVENTS_END field. */
#define SPIM_EVENTS_END_EVENTS_END_Msk                                                             \
  (0x1UL << SPIM_EVENTS_END_EVENTS_END_Pos)           /*!< Bit mask of EVENTS_END field. */
#define SPIM_EVENTS_END_EVENTS_END_NotGenerated (0UL) /*!< Event not generated */
#define SPIM_EVENTS_END_EVENTS_END_Generated    (1UL) /*!< Event generated */

/* Register: SPIM_EVENTS_ENDTX */
/* Description: End of TXD buffer reached */

/* Bit 0 : End of TXD buffer reached */
#define SPIM_EVENTS_ENDTX_EVENTS_ENDTX_Pos      (0UL) /*!< Position of EVENTS_ENDTX field. */
#define SPIM_EVENTS_ENDTX_EVENTS_ENDTX_Msk                                                         \
  (0x1UL << SPIM_EVENTS_ENDTX_EVENTS_ENDTX_Pos)           /*!< Bit mask of EVENTS_ENDTX field. */
#define SPIM_EVENTS_ENDTX_EVENTS_ENDTX_NotGenerated (0UL) /*!< Event not generated */
#define SPIM_EVENTS_ENDTX_EVENTS_ENDTX_Generated    (1UL) /*!< Event generated */

/* Register: SPIM_EVENTS_STARTED */
/* Description: Transaction started */

/* Bit 0 : Transaction started */
#define SPIM_EVENTS_STARTED_EVENTS_STARTED_Pos      (0UL) /*!< Position of EVENTS_STARTED field. */
#define SPIM_EVENTS_STARTED_EVENTS_STARTED_Msk                                                     \
  (0x1UL << SPIM_EVENTS_STARTED_EVENTS_STARTED_Pos) /*!< Bit mask of EVENTS_STARTED field. */
#define SPIM_EVENTS_STARTED_EVENTS_STARTED_NotGenerated (0UL) /*!< Event not generated */
#define SPIM_EVENTS_STARTED_EVENTS_STARTED_Generated    (1UL) /*!< Event generated */

/* Register: SPIM_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 17 : Shortcut between event END and task START */
#define SPIM_SHORTS_END_START_Pos                       (17UL) /*!< Position of END_START field. */
#define SPIM_SHORTS_END_START_Msk                                                                  \
  (0x1UL << SPIM_SHORTS_END_START_Pos)       /*!< Bit mask of END_START field. */
#define SPIM_SHORTS_END_START_Disabled (0UL) /*!< Disable shortcut */
#define SPIM_SHORTS_END_START_Enabled  (1UL) /*!< Enable shortcut */

/* Register: SPIM_INTENSET */
/* Description: Enable interrupt */

/* Bit 19 : Write '1' to enable interrupt for event STARTED */
#define SPIM_INTENSET_STARTED_Pos      (19UL) /*!< Position of STARTED field. */
#define SPIM_INTENSET_STARTED_Msk                                                                  \
  (0x1UL << SPIM_INTENSET_STARTED_Pos)       /*!< Bit mask of STARTED field. */
#define SPIM_INTENSET_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENSET_STARTED_Enabled  (1UL) /*!< Read: Enabled */
#define SPIM_INTENSET_STARTED_Set      (1UL) /*!< Enable */

/* Bit 8 : Write '1' to enable interrupt for event ENDTX */
#define SPIM_INTENSET_ENDTX_Pos        (8UL) /*!< Position of ENDTX field. */
#define SPIM_INTENSET_ENDTX_Msk        (0x1UL << SPIM_INTENSET_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define SPIM_INTENSET_ENDTX_Disabled   (0UL)                              /*!< Read: Disabled */
#define SPIM_INTENSET_ENDTX_Enabled    (1UL)                              /*!< Read: Enabled */
#define SPIM_INTENSET_ENDTX_Set        (1UL)                              /*!< Enable */

/* Bit 6 : Write '1' to enable interrupt for event END */
#define SPIM_INTENSET_END_Pos          (6UL) /*!< Position of END field. */
#define SPIM_INTENSET_END_Msk          (0x1UL << SPIM_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define SPIM_INTENSET_END_Disabled     (0UL)                            /*!< Read: Disabled */
#define SPIM_INTENSET_END_Enabled      (1UL)                            /*!< Read: Enabled */
#define SPIM_INTENSET_END_Set          (1UL)                            /*!< Enable */

/* Bit 4 : Write '1' to enable interrupt for event ENDRX */
#define SPIM_INTENSET_ENDRX_Pos        (4UL) /*!< Position of ENDRX field. */
#define SPIM_INTENSET_ENDRX_Msk        (0x1UL << SPIM_INTENSET_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define SPIM_INTENSET_ENDRX_Disabled   (0UL)                              /*!< Read: Disabled */
#define SPIM_INTENSET_ENDRX_Enabled    (1UL)                              /*!< Read: Enabled */
#define SPIM_INTENSET_ENDRX_Set        (1UL)                              /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event STOPPED */
#define SPIM_INTENSET_STOPPED_Pos      (1UL) /*!< Position of STOPPED field. */
#define SPIM_INTENSET_STOPPED_Msk                                                                  \
  (0x1UL << SPIM_INTENSET_STOPPED_Pos)       /*!< Bit mask of STOPPED field. */
#define SPIM_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENSET_STOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define SPIM_INTENSET_STOPPED_Set      (1UL) /*!< Enable */

/* Register: SPIM_INTENCLR */
/* Description: Disable interrupt */

/* Bit 19 : Write '1' to disable interrupt for event STARTED */
#define SPIM_INTENCLR_STARTED_Pos      (19UL) /*!< Position of STARTED field. */
#define SPIM_INTENCLR_STARTED_Msk                                                                  \
  (0x1UL << SPIM_INTENCLR_STARTED_Pos)       /*!< Bit mask of STARTED field. */
#define SPIM_INTENCLR_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENCLR_STARTED_Enabled  (1UL) /*!< Read: Enabled */
#define SPIM_INTENCLR_STARTED_Clear    (1UL) /*!< Disable */

/* Bit 8 : Write '1' to disable interrupt for event ENDTX */
#define SPIM_INTENCLR_ENDTX_Pos        (8UL) /*!< Position of ENDTX field. */
#define SPIM_INTENCLR_ENDTX_Msk        (0x1UL << SPIM_INTENCLR_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define SPIM_INTENCLR_ENDTX_Disabled   (0UL)                              /*!< Read: Disabled */
#define SPIM_INTENCLR_ENDTX_Enabled    (1UL)                              /*!< Read: Enabled */
#define SPIM_INTENCLR_ENDTX_Clear      (1UL)                              /*!< Disable */

/* Bit 6 : Write '1' to disable interrupt for event END */
#define SPIM_INTENCLR_END_Pos          (6UL) /*!< Position of END field. */
#define SPIM_INTENCLR_END_Msk          (0x1UL << SPIM_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define SPIM_INTENCLR_END_Disabled     (0UL)                            /*!< Read: Disabled */
#define SPIM_INTENCLR_END_Enabled      (1UL)                            /*!< Read: Enabled */
#define SPIM_INTENCLR_END_Clear        (1UL)                            /*!< Disable */

/* Bit 4 : Write '1' to disable interrupt for event ENDRX */
#define SPIM_INTENCLR_ENDRX_Pos        (4UL) /*!< Position of ENDRX field. */
#define SPIM_INTENCLR_ENDRX_Msk        (0x1UL << SPIM_INTENCLR_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define SPIM_INTENCLR_ENDRX_Disabled   (0UL)                              /*!< Read: Disabled */
#define SPIM_INTENCLR_ENDRX_Enabled    (1UL)                              /*!< Read: Enabled */
#define SPIM_INTENCLR_ENDRX_Clear      (1UL)                              /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event STOPPED */
#define SPIM_INTENCLR_STOPPED_Pos      (1UL) /*!< Position of STOPPED field. */
#define SPIM_INTENCLR_STOPPED_Msk                                                                  \
  (0x1UL << SPIM_INTENCLR_STOPPED_Pos)       /*!< Bit mask of STOPPED field. */
#define SPIM_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENCLR_STOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define SPIM_INTENCLR_STOPPED_Clear    (1UL) /*!< Disable */

/* Register: SPIM_ENABLE */
/* Description: Enable SPIM */

/* Bits 3..0 : Enable or disable SPIM */
#define SPIM_ENABLE_ENABLE_Pos         (0UL) /*!< Position of ENABLE field. */
#define SPIM_ENABLE_ENABLE_Msk         (0xFUL << SPIM_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define SPIM_ENABLE_ENABLE_Disabled    (0UL)                             /*!< Disable SPIM */
#define SPIM_ENABLE_ENABLE_Enabled     (7UL)                             /*!< Enable SPIM */

/* Register: SPIM_PSEL_SCK */
/* Description: Pin select for SCK */

/* Bit 31 : Connection */
#define SPIM_PSEL_SCK_CONNECT_Pos      (31UL) /*!< Position of CONNECT field. */
#define SPIM_PSEL_SCK_CONNECT_Msk                                                                  \
  (0x1UL << SPIM_PSEL_SCK_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPIM_PSEL_SCK_CONNECT_Connected    (0UL) /*!< Connect */
#define SPIM_PSEL_SCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPIM_PSEL_SCK_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPIM_PSEL_SCK_PIN_Msk              (0x1FUL << SPIM_PSEL_SCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIM_PSEL_MOSI */
/* Description: Pin select for MOSI signal */

/* Bit 31 : Connection */
#define SPIM_PSEL_MOSI_CONNECT_Pos         (31UL) /*!< Position of CONNECT field. */
#define SPIM_PSEL_MOSI_CONNECT_Msk                                                                 \
  (0x1UL << SPIM_PSEL_MOSI_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPIM_PSEL_MOSI_CONNECT_Connected    (0UL) /*!< Connect */
#define SPIM_PSEL_MOSI_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPIM_PSEL_MOSI_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPIM_PSEL_MOSI_PIN_Msk              (0x1FUL << SPIM_PSEL_MOSI_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIM_PSEL_MISO */
/* Description: Pin select for MISO signal */

/* Bit 31 : Connection */
#define SPIM_PSEL_MISO_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define SPIM_PSEL_MISO_CONNECT_Msk                                                                 \
  (0x1UL << SPIM_PSEL_MISO_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPIM_PSEL_MISO_CONNECT_Connected    (0UL) /*!< Connect */
#define SPIM_PSEL_MISO_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPIM_PSEL_MISO_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPIM_PSEL_MISO_PIN_Msk              (0x1FUL << SPIM_PSEL_MISO_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIM_FREQUENCY */
/* Description: SPI frequency. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : SPI master data rate */
#define SPIM_FREQUENCY_FREQUENCY_Pos        (0UL) /*!< Position of FREQUENCY field. */
#define SPIM_FREQUENCY_FREQUENCY_Msk                                                               \
  (0xFFFFFFFFUL << SPIM_FREQUENCY_FREQUENCY_Pos)     /*!< Bit mask of FREQUENCY field. */
#define SPIM_FREQUENCY_FREQUENCY_K125 (0x02000000UL) /*!< 125 kbps */
#define SPIM_FREQUENCY_FREQUENCY_K250 (0x04000000UL) /*!< 250 kbps */
#define SPIM_FREQUENCY_FREQUENCY_K500 (0x08000000UL) /*!< 500 kbps */
#define SPIM_FREQUENCY_FREQUENCY_M1   (0x10000000UL) /*!< 1 Mbps */
#define SPIM_FREQUENCY_FREQUENCY_M2   (0x20000000UL) /*!< 2 Mbps */
#define SPIM_FREQUENCY_FREQUENCY_M4   (0x40000000UL) /*!< 4 Mbps */
#define SPIM_FREQUENCY_FREQUENCY_M8   (0x80000000UL) /*!< 8 Mbps */

/* Register: SPIM_RXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define SPIM_RXD_PTR_PTR_Pos          (0UL) /*!< Position of PTR field. */
#define SPIM_RXD_PTR_PTR_Msk          (0xFFFFFFFFUL << SPIM_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: SPIM_RXD_MAXCNT */
/* Description: Maximum number of bytes in receive buffer */

/* Bits 14..0 : Maximum number of bytes in receive buffer */
#define SPIM_RXD_MAXCNT_MAXCNT_Pos    (0UL) /*!< Position of MAXCNT field. */
#define SPIM_RXD_MAXCNT_MAXCNT_Msk                                                                 \
  (0x7FFFUL << SPIM_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: SPIM_RXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 14..0 : Number of bytes transferred in the last transaction */
#define SPIM_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define SPIM_RXD_AMOUNT_AMOUNT_Msk                                                                 \
  (0x7FFFUL << SPIM_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: SPIM_RXD_LIST */
/* Description: EasyDMA list type */

/* Bits 1..0 : List type */
#define SPIM_RXD_LIST_LIST_Pos       (0UL) /*!< Position of LIST field. */
#define SPIM_RXD_LIST_LIST_Msk       (0x3UL << SPIM_RXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define SPIM_RXD_LIST_LIST_Disabled  (0UL)                             /*!< Disable EasyDMA list */
#define SPIM_RXD_LIST_LIST_ArrayList (1UL)                             /*!< Use array list */

/* Register: SPIM_TXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define SPIM_TXD_PTR_PTR_Pos         (0UL) /*!< Position of PTR field. */
#define SPIM_TXD_PTR_PTR_Msk         (0xFFFFFFFFUL << SPIM_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: SPIM_TXD_MAXCNT */
/* Description: Number of bytes in transmit buffer */

/* Bits 14..0 : Maximum number of bytes in transmit buffer */
#define SPIM_TXD_MAXCNT_MAXCNT_Pos   (0UL) /*!< Position of MAXCNT field. */
#define SPIM_TXD_MAXCNT_MAXCNT_Msk                                                                 \
  (0x7FFFUL << SPIM_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: SPIM_TXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 14..0 : Number of bytes transferred in the last transaction */
#define SPIM_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define SPIM_TXD_AMOUNT_AMOUNT_Msk                                                                 \
  (0x7FFFUL << SPIM_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: SPIM_TXD_LIST */
/* Description: EasyDMA list type */

/* Bits 1..0 : List type */
#define SPIM_TXD_LIST_LIST_Pos       (0UL) /*!< Position of LIST field. */
#define SPIM_TXD_LIST_LIST_Msk       (0x3UL << SPIM_TXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define SPIM_TXD_LIST_LIST_Disabled  (0UL)                             /*!< Disable EasyDMA list */
#define SPIM_TXD_LIST_LIST_ArrayList (1UL)                             /*!< Use array list */

/* Register: SPIM_CONFIG */
/* Description: Configuration register */

/* Bit 2 : Serial clock (SCK) polarity */
#define SPIM_CONFIG_CPOL_Pos         (2UL)                           /*!< Position of CPOL field. */
#define SPIM_CONFIG_CPOL_Msk         (0x1UL << SPIM_CONFIG_CPOL_Pos) /*!< Bit mask of CPOL field. */
#define SPIM_CONFIG_CPOL_ActiveHigh  (0UL)                           /*!< Active high */
#define SPIM_CONFIG_CPOL_ActiveLow   (1UL)                           /*!< Active low */

/* Bit 1 : Serial clock (SCK) phase */
#define SPIM_CONFIG_CPHA_Pos         (1UL)                           /*!< Position of CPHA field. */
#define SPIM_CONFIG_CPHA_Msk         (0x1UL << SPIM_CONFIG_CPHA_Pos) /*!< Bit mask of CPHA field. */
#define SPIM_CONFIG_CPHA_Leading                                                                   \
  (0UL) /*!< Sample on leading edge of clock, shift serial data on trailing edge */
#define SPIM_CONFIG_CPHA_Trailing                                                                  \
  (1UL) /*!< Sample on trailing edge of clock, shift serial data on leading edge */

/* Bit 0 : Bit order */
#define SPIM_CONFIG_ORDER_Pos                (0UL) /*!< Position of ORDER field. */
#define SPIM_CONFIG_ORDER_Msk                (0x1UL << SPIM_CONFIG_ORDER_Pos) /*!< Bit mask of ORDER field. */
#define SPIM_CONFIG_ORDER_MsbFirst           (0UL) /*!< Most significant bit shifted out first */
#define SPIM_CONFIG_ORDER_LsbFirst           (1UL) /*!< Least significant bit shifted out first */

/* Register: SPIM_ORC */
/* Description: Byte transmitted after TXD.MAXCNT bytes have been transmitted in the case when RXD.MAXCNT is greater than TXD.MAXCNT */

/* Bits 7..0 : Byte transmitted after TXD.MAXCNT bytes have been transmitted in the case when RXD.MAXCNT is greater than TXD.MAXCNT. */
#define SPIM_ORC_ORC_Pos                     (0UL) /*!< Position of ORC field. */
#define SPIM_ORC_ORC_Msk                     (0xFFUL << SPIM_ORC_ORC_Pos) /*!< Bit mask of ORC field. */


/* Peripheral: SPIS */
/* Description: SPI Slave 0 */

/* Register: SPIS_TASKS_ACQUIRE */
/* Description: Acquire SPI semaphore */

/* Bit 0 : Acquire SPI semaphore */
#define SPIS_TASKS_ACQUIRE_TASKS_ACQUIRE_Pos (0UL) /*!< Position of TASKS_ACQUIRE field. */
#define SPIS_TASKS_ACQUIRE_TASKS_ACQUIRE_Msk                                                       \
  (0x1UL << SPIS_TASKS_ACQUIRE_TASKS_ACQUIRE_Pos)      /*!< Bit mask of TASKS_ACQUIRE field. */
#define SPIS_TASKS_ACQUIRE_TASKS_ACQUIRE_Trigger (1UL) /*!< Trigger task */

/* Register: SPIS_TASKS_RELEASE */
/* Description: Release SPI semaphore, enabling the SPI slave to acquire it */

/* Bit 0 : Release SPI semaphore, enabling the SPI slave to acquire it */
#define SPIS_TASKS_RELEASE_TASKS_RELEASE_Pos     (0UL) /*!< Position of TASKS_RELEASE field. */
#define SPIS_TASKS_RELEASE_TASKS_RELEASE_Msk                                                       \
  (0x1UL << SPIS_TASKS_RELEASE_TASKS_RELEASE_Pos)      /*!< Bit mask of TASKS_RELEASE field. */
#define SPIS_TASKS_RELEASE_TASKS_RELEASE_Trigger (1UL) /*!< Trigger task */

/* Register: SPIS_EVENTS_END */
/* Description: Granted transaction completed */

/* Bit 0 : Granted transaction completed */
#define SPIS_EVENTS_END_EVENTS_END_Pos           (0UL) /*!< Position of EVENTS_END field. */
#define SPIS_EVENTS_END_EVENTS_END_Msk                                                             \
  (0x1UL << SPIS_EVENTS_END_EVENTS_END_Pos)           /*!< Bit mask of EVENTS_END field. */
#define SPIS_EVENTS_END_EVENTS_END_NotGenerated (0UL) /*!< Event not generated */
#define SPIS_EVENTS_END_EVENTS_END_Generated    (1UL) /*!< Event generated */

/* Register: SPIS_EVENTS_ENDRX */
/* Description: End of RXD buffer reached */

/* Bit 0 : End of RXD buffer reached */
#define SPIS_EVENTS_ENDRX_EVENTS_ENDRX_Pos      (0UL) /*!< Position of EVENTS_ENDRX field. */
#define SPIS_EVENTS_ENDRX_EVENTS_ENDRX_Msk                                                         \
  (0x1UL << SPIS_EVENTS_ENDRX_EVENTS_ENDRX_Pos)           /*!< Bit mask of EVENTS_ENDRX field. */
#define SPIS_EVENTS_ENDRX_EVENTS_ENDRX_NotGenerated (0UL) /*!< Event not generated */
#define SPIS_EVENTS_ENDRX_EVENTS_ENDRX_Generated    (1UL) /*!< Event generated */

/* Register: SPIS_EVENTS_ACQUIRED */
/* Description: Semaphore acquired */

/* Bit 0 : Semaphore acquired */
#define SPIS_EVENTS_ACQUIRED_EVENTS_ACQUIRED_Pos    (0UL) /*!< Position of EVENTS_ACQUIRED field. */
#define SPIS_EVENTS_ACQUIRED_EVENTS_ACQUIRED_Msk                                                   \
  (0x1UL << SPIS_EVENTS_ACQUIRED_EVENTS_ACQUIRED_Pos) /*!< Bit mask of EVENTS_ACQUIRED field. */
#define SPIS_EVENTS_ACQUIRED_EVENTS_ACQUIRED_NotGenerated (0UL) /*!< Event not generated */
#define SPIS_EVENTS_ACQUIRED_EVENTS_ACQUIRED_Generated    (1UL) /*!< Event generated */

/* Register: SPIS_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 2 : Shortcut between event END and task ACQUIRE */
#define SPIS_SHORTS_END_ACQUIRE_Pos                       (2UL) /*!< Position of END_ACQUIRE field. */
#define SPIS_SHORTS_END_ACQUIRE_Msk                                                                \
  (0x1UL << SPIS_SHORTS_END_ACQUIRE_Pos)       /*!< Bit mask of END_ACQUIRE field. */
#define SPIS_SHORTS_END_ACQUIRE_Disabled (0UL) /*!< Disable shortcut */
#define SPIS_SHORTS_END_ACQUIRE_Enabled  (1UL) /*!< Enable shortcut */

/* Register: SPIS_INTENSET */
/* Description: Enable interrupt */

/* Bit 10 : Write '1' to enable interrupt for event ACQUIRED */
#define SPIS_INTENSET_ACQUIRED_Pos       (10UL) /*!< Position of ACQUIRED field. */
#define SPIS_INTENSET_ACQUIRED_Msk                                                                 \
  (0x1UL << SPIS_INTENSET_ACQUIRED_Pos)       /*!< Bit mask of ACQUIRED field. */
#define SPIS_INTENSET_ACQUIRED_Disabled (0UL) /*!< Read: Disabled */
#define SPIS_INTENSET_ACQUIRED_Enabled  (1UL) /*!< Read: Enabled */
#define SPIS_INTENSET_ACQUIRED_Set      (1UL) /*!< Enable */

/* Bit 4 : Write '1' to enable interrupt for event ENDRX */
#define SPIS_INTENSET_ENDRX_Pos         (4UL) /*!< Position of ENDRX field. */
#define SPIS_INTENSET_ENDRX_Msk         (0x1UL << SPIS_INTENSET_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define SPIS_INTENSET_ENDRX_Disabled    (0UL)                              /*!< Read: Disabled */
#define SPIS_INTENSET_ENDRX_Enabled     (1UL)                              /*!< Read: Enabled */
#define SPIS_INTENSET_ENDRX_Set         (1UL)                              /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event END */
#define SPIS_INTENSET_END_Pos           (1UL) /*!< Position of END field. */
#define SPIS_INTENSET_END_Msk           (0x1UL << SPIS_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define SPIS_INTENSET_END_Disabled      (0UL)                            /*!< Read: Disabled */
#define SPIS_INTENSET_END_Enabled       (1UL)                            /*!< Read: Enabled */
#define SPIS_INTENSET_END_Set           (1UL)                            /*!< Enable */

/* Register: SPIS_INTENCLR */
/* Description: Disable interrupt */

/* Bit 10 : Write '1' to disable interrupt for event ACQUIRED */
#define SPIS_INTENCLR_ACQUIRED_Pos      (10UL) /*!< Position of ACQUIRED field. */
#define SPIS_INTENCLR_ACQUIRED_Msk                                                                 \
  (0x1UL << SPIS_INTENCLR_ACQUIRED_Pos)       /*!< Bit mask of ACQUIRED field. */
#define SPIS_INTENCLR_ACQUIRED_Disabled (0UL) /*!< Read: Disabled */
#define SPIS_INTENCLR_ACQUIRED_Enabled  (1UL) /*!< Read: Enabled */
#define SPIS_INTENCLR_ACQUIRED_Clear    (1UL) /*!< Disable */

/* Bit 4 : Write '1' to disable interrupt for event ENDRX */
#define SPIS_INTENCLR_ENDRX_Pos         (4UL) /*!< Position of ENDRX field. */
#define SPIS_INTENCLR_ENDRX_Msk         (0x1UL << SPIS_INTENCLR_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define SPIS_INTENCLR_ENDRX_Disabled    (0UL)                              /*!< Read: Disabled */
#define SPIS_INTENCLR_ENDRX_Enabled     (1UL)                              /*!< Read: Enabled */
#define SPIS_INTENCLR_ENDRX_Clear       (1UL)                              /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event END */
#define SPIS_INTENCLR_END_Pos           (1UL) /*!< Position of END field. */
#define SPIS_INTENCLR_END_Msk           (0x1UL << SPIS_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define SPIS_INTENCLR_END_Disabled      (0UL)                            /*!< Read: Disabled */
#define SPIS_INTENCLR_END_Enabled       (1UL)                            /*!< Read: Enabled */
#define SPIS_INTENCLR_END_Clear         (1UL)                            /*!< Disable */

/* Register: SPIS_SEMSTAT */
/* Description: Semaphore status register */

/* Bits 1..0 : Semaphore status */
#define SPIS_SEMSTAT_SEMSTAT_Pos        (0UL) /*!< Position of SEMSTAT field. */
#define SPIS_SEMSTAT_SEMSTAT_Msk                                                                   \
  (0x3UL << SPIS_SEMSTAT_SEMSTAT_Pos)   /*!< Bit mask of SEMSTAT field. */
#define SPIS_SEMSTAT_SEMSTAT_Free (0UL) /*!< Semaphore is free */
#define SPIS_SEMSTAT_SEMSTAT_CPU  (1UL) /*!< Semaphore is assigned to CPU */
#define SPIS_SEMSTAT_SEMSTAT_SPIS (2UL) /*!< Semaphore is assigned to SPI slave */
#define SPIS_SEMSTAT_SEMSTAT_CPUPending                                                            \
  (3UL) /*!< Semaphore is assigned to SPI but a handover to the CPU is pending */

/* Register: SPIS_STATUS */
/* Description: Status from last transaction */

/* Bit 1 : RX buffer overflow detected, and prevented */
#define SPIS_STATUS_OVERFLOW_Pos (1UL) /*!< Position of OVERFLOW field. */
#define SPIS_STATUS_OVERFLOW_Msk                                                                   \
  (0x1UL << SPIS_STATUS_OVERFLOW_Pos)         /*!< Bit mask of OVERFLOW field. */
#define SPIS_STATUS_OVERFLOW_NotPresent (0UL) /*!< Read: error not present */
#define SPIS_STATUS_OVERFLOW_Present    (1UL) /*!< Read: error present */
#define SPIS_STATUS_OVERFLOW_Clear      (1UL) /*!< Write: clear error on writing '1' */

/* Bit 0 : TX buffer over-read detected, and prevented */
#define SPIS_STATUS_OVERREAD_Pos        (0UL) /*!< Position of OVERREAD field. */
#define SPIS_STATUS_OVERREAD_Msk                                                                   \
  (0x1UL << SPIS_STATUS_OVERREAD_Pos)         /*!< Bit mask of OVERREAD field. */
#define SPIS_STATUS_OVERREAD_NotPresent (0UL) /*!< Read: error not present */
#define SPIS_STATUS_OVERREAD_Present    (1UL) /*!< Read: error present */
#define SPIS_STATUS_OVERREAD_Clear      (1UL) /*!< Write: clear error on writing '1' */

/* Register: SPIS_ENABLE */
/* Description: Enable SPI slave */

/* Bits 3..0 : Enable or disable SPI slave */
#define SPIS_ENABLE_ENABLE_Pos          (0UL) /*!< Position of ENABLE field. */
#define SPIS_ENABLE_ENABLE_Msk          (0xFUL << SPIS_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define SPIS_ENABLE_ENABLE_Disabled     (0UL)                             /*!< Disable SPI slave */
#define SPIS_ENABLE_ENABLE_Enabled      (2UL)                             /*!< Enable SPI slave */

/* Register: SPIS_PSEL_SCK */
/* Description: Pin select for SCK */

/* Bit 31 : Connection */
#define SPIS_PSEL_SCK_CONNECT_Pos       (31UL) /*!< Position of CONNECT field. */
#define SPIS_PSEL_SCK_CONNECT_Msk                                                                  \
  (0x1UL << SPIS_PSEL_SCK_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPIS_PSEL_SCK_CONNECT_Connected    (0UL) /*!< Connect */
#define SPIS_PSEL_SCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPIS_PSEL_SCK_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPIS_PSEL_SCK_PIN_Msk              (0x1FUL << SPIS_PSEL_SCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIS_PSEL_MISO */
/* Description: Pin select for MISO signal */

/* Bit 31 : Connection */
#define SPIS_PSEL_MISO_CONNECT_Pos         (31UL) /*!< Position of CONNECT field. */
#define SPIS_PSEL_MISO_CONNECT_Msk                                                                 \
  (0x1UL << SPIS_PSEL_MISO_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPIS_PSEL_MISO_CONNECT_Connected    (0UL) /*!< Connect */
#define SPIS_PSEL_MISO_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPIS_PSEL_MISO_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPIS_PSEL_MISO_PIN_Msk              (0x1FUL << SPIS_PSEL_MISO_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIS_PSEL_MOSI */
/* Description: Pin select for MOSI signal */

/* Bit 31 : Connection */
#define SPIS_PSEL_MOSI_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define SPIS_PSEL_MOSI_CONNECT_Msk                                                                 \
  (0x1UL << SPIS_PSEL_MOSI_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPIS_PSEL_MOSI_CONNECT_Connected    (0UL) /*!< Connect */
#define SPIS_PSEL_MOSI_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPIS_PSEL_MOSI_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPIS_PSEL_MOSI_PIN_Msk              (0x1FUL << SPIS_PSEL_MOSI_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIS_PSEL_CSN */
/* Description: Pin select for CSN signal */

/* Bit 31 : Connection */
#define SPIS_PSEL_CSN_CONNECT_Pos           (31UL) /*!< Position of CONNECT field. */
#define SPIS_PSEL_CSN_CONNECT_Msk                                                                  \
  (0x1UL << SPIS_PSEL_CSN_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define SPIS_PSEL_CSN_CONNECT_Connected    (0UL) /*!< Connect */
#define SPIS_PSEL_CSN_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define SPIS_PSEL_CSN_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define SPIS_PSEL_CSN_PIN_Msk              (0x1FUL << SPIS_PSEL_CSN_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIS_RXD_PTR */
/* Description: RXD data pointer */

/* Bits 31..0 : RXD data pointer */
#define SPIS_RXD_PTR_PTR_Pos               (0UL) /*!< Position of PTR field. */
#define SPIS_RXD_PTR_PTR_Msk               (0xFFFFFFFFUL << SPIS_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: SPIS_RXD_MAXCNT */
/* Description: Maximum number of bytes in receive buffer */

/* Bits 14..0 : Maximum number of bytes in receive buffer */
#define SPIS_RXD_MAXCNT_MAXCNT_Pos         (0UL) /*!< Position of MAXCNT field. */
#define SPIS_RXD_MAXCNT_MAXCNT_Msk                                                                 \
  (0x7FFFUL << SPIS_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: SPIS_RXD_AMOUNT */
/* Description: Number of bytes received in last granted transaction */

/* Bits 14..0 : Number of bytes received in the last granted transaction */
#define SPIS_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define SPIS_RXD_AMOUNT_AMOUNT_Msk                                                                 \
  (0x7FFFUL << SPIS_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: SPIS_RXD_LIST */
/* Description: EasyDMA list type */

/* Bits 1..0 : List type */
#define SPIS_RXD_LIST_LIST_Pos       (0UL) /*!< Position of LIST field. */
#define SPIS_RXD_LIST_LIST_Msk       (0x3UL << SPIS_RXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define SPIS_RXD_LIST_LIST_Disabled  (0UL)                             /*!< Disable EasyDMA list */
#define SPIS_RXD_LIST_LIST_ArrayList (1UL)                             /*!< Use array list */

/* Register: SPIS_TXD_PTR */
/* Description: TXD data pointer */

/* Bits 31..0 : TXD data pointer */
#define SPIS_TXD_PTR_PTR_Pos         (0UL) /*!< Position of PTR field. */
#define SPIS_TXD_PTR_PTR_Msk         (0xFFFFFFFFUL << SPIS_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: SPIS_TXD_MAXCNT */
/* Description: Maximum number of bytes in transmit buffer */

/* Bits 14..0 : Maximum number of bytes in transmit buffer */
#define SPIS_TXD_MAXCNT_MAXCNT_Pos   (0UL) /*!< Position of MAXCNT field. */
#define SPIS_TXD_MAXCNT_MAXCNT_Msk                                                                 \
  (0x7FFFUL << SPIS_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: SPIS_TXD_AMOUNT */
/* Description: Number of bytes transmitted in last granted transaction */

/* Bits 14..0 : Number of bytes transmitted in last granted transaction */
#define SPIS_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define SPIS_TXD_AMOUNT_AMOUNT_Msk                                                                 \
  (0x7FFFUL << SPIS_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: SPIS_TXD_LIST */
/* Description: EasyDMA list type */

/* Bits 1..0 : List type */
#define SPIS_TXD_LIST_LIST_Pos       (0UL) /*!< Position of LIST field. */
#define SPIS_TXD_LIST_LIST_Msk       (0x3UL << SPIS_TXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define SPIS_TXD_LIST_LIST_Disabled  (0UL)                             /*!< Disable EasyDMA list */
#define SPIS_TXD_LIST_LIST_ArrayList (1UL)                             /*!< Use array list */

/* Register: SPIS_CONFIG */
/* Description: Configuration register */

/* Bit 2 : Serial clock (SCK) polarity */
#define SPIS_CONFIG_CPOL_Pos         (2UL)                           /*!< Position of CPOL field. */
#define SPIS_CONFIG_CPOL_Msk         (0x1UL << SPIS_CONFIG_CPOL_Pos) /*!< Bit mask of CPOL field. */
#define SPIS_CONFIG_CPOL_ActiveHigh  (0UL)                           /*!< Active high */
#define SPIS_CONFIG_CPOL_ActiveLow   (1UL)                           /*!< Active low */

/* Bit 1 : Serial clock (SCK) phase */
#define SPIS_CONFIG_CPHA_Pos         (1UL)                           /*!< Position of CPHA field. */
#define SPIS_CONFIG_CPHA_Msk         (0x1UL << SPIS_CONFIG_CPHA_Pos) /*!< Bit mask of CPHA field. */
#define SPIS_CONFIG_CPHA_Leading                                                                   \
  (0UL) /*!< Sample on leading edge of clock, shift serial data on trailing edge */
#define SPIS_CONFIG_CPHA_Trailing                                                                  \
  (1UL) /*!< Sample on trailing edge of clock, shift serial data on leading edge */

/* Bit 0 : Bit order */
#define SPIS_CONFIG_ORDER_Pos            (0UL) /*!< Position of ORDER field. */
#define SPIS_CONFIG_ORDER_Msk            (0x1UL << SPIS_CONFIG_ORDER_Pos) /*!< Bit mask of ORDER field. */
#define SPIS_CONFIG_ORDER_MsbFirst       (0UL) /*!< Most significant bit shifted out first */
#define SPIS_CONFIG_ORDER_LsbFirst       (1UL) /*!< Least significant bit shifted out first */

/* Register: SPIS_DEF */
/* Description: Default character. Character clocked out in case of an ignored transaction. */

/* Bits 7..0 : Default character. Character clocked out in case of an ignored transaction. */
#define SPIS_DEF_DEF_Pos                 (0UL)                        /*!< Position of DEF field. */
#define SPIS_DEF_DEF_Msk                 (0xFFUL << SPIS_DEF_DEF_Pos) /*!< Bit mask of DEF field. */

/* Register: SPIS_ORC */
/* Description: Over-read character */

/* Bits 7..0 : Over-read character. Character clocked out after an over-read of the transmit buffer. */
#define SPIS_ORC_ORC_Pos                 (0UL)                        /*!< Position of ORC field. */
#define SPIS_ORC_ORC_Msk                 (0xFFUL << SPIS_ORC_ORC_Pos) /*!< Bit mask of ORC field. */


/* Peripheral: TEMP */
/* Description: Temperature Sensor */

/* Register: TEMP_TASKS_START */
/* Description: Start temperature measurement */

/* Bit 0 : Start temperature measurement */
#define TEMP_TASKS_START_TASKS_START_Pos (0UL) /*!< Position of TASKS_START field. */
#define TEMP_TASKS_START_TASKS_START_Msk                                                           \
  (0x1UL << TEMP_TASKS_START_TASKS_START_Pos)      /*!< Bit mask of TASKS_START field. */
#define TEMP_TASKS_START_TASKS_START_Trigger (1UL) /*!< Trigger task */

/* Register: TEMP_TASKS_STOP */
/* Description: Stop temperature measurement */

/* Bit 0 : Stop temperature measurement */
#define TEMP_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define TEMP_TASKS_STOP_TASKS_STOP_Msk                                                             \
  (0x1UL << TEMP_TASKS_STOP_TASKS_STOP_Pos)          /*!< Bit mask of TASKS_STOP field. */
#define TEMP_TASKS_STOP_TASKS_STOP_Trigger     (1UL) /*!< Trigger task */

/* Register: TEMP_EVENTS_DATARDY */
/* Description: Temperature measurement complete, data ready */

/* Bit 0 : Temperature measurement complete, data ready */
#define TEMP_EVENTS_DATARDY_EVENTS_DATARDY_Pos (0UL) /*!< Position of EVENTS_DATARDY field. */
#define TEMP_EVENTS_DATARDY_EVENTS_DATARDY_Msk                                                     \
  (0x1UL << TEMP_EVENTS_DATARDY_EVENTS_DATARDY_Pos) /*!< Bit mask of EVENTS_DATARDY field. */
#define TEMP_EVENTS_DATARDY_EVENTS_DATARDY_NotGenerated (0UL) /*!< Event not generated */
#define TEMP_EVENTS_DATARDY_EVENTS_DATARDY_Generated    (1UL) /*!< Event generated */

/* Register: TEMP_INTENSET */
/* Description: Enable interrupt */

/* Bit 0 : Write '1' to enable interrupt for event DATARDY */
#define TEMP_INTENSET_DATARDY_Pos                       (0UL) /*!< Position of DATARDY field. */
#define TEMP_INTENSET_DATARDY_Msk                                                                  \
  (0x1UL << TEMP_INTENSET_DATARDY_Pos)       /*!< Bit mask of DATARDY field. */
#define TEMP_INTENSET_DATARDY_Disabled (0UL) /*!< Read: Disabled */
#define TEMP_INTENSET_DATARDY_Enabled  (1UL) /*!< Read: Enabled */
#define TEMP_INTENSET_DATARDY_Set      (1UL) /*!< Enable */

/* Register: TEMP_INTENCLR */
/* Description: Disable interrupt */

/* Bit 0 : Write '1' to disable interrupt for event DATARDY */
#define TEMP_INTENCLR_DATARDY_Pos      (0UL) /*!< Position of DATARDY field. */
#define TEMP_INTENCLR_DATARDY_Msk                                                                  \
  (0x1UL << TEMP_INTENCLR_DATARDY_Pos)          /*!< Bit mask of DATARDY field. */
#define TEMP_INTENCLR_DATARDY_Disabled    (0UL) /*!< Read: Disabled */
#define TEMP_INTENCLR_DATARDY_Enabled     (1UL) /*!< Read: Enabled */
#define TEMP_INTENCLR_DATARDY_Clear       (1UL) /*!< Disable */

/* Register: TEMP_TEMP */
/* Description: Temperature in degC (0.25deg steps) */

/* Bits 31..0 : Temperature in degC (0.25deg steps) */
#define TEMP_TEMP_TEMP_Pos                (0UL) /*!< Position of TEMP field. */
#define TEMP_TEMP_TEMP_Msk                (0xFFFFFFFFUL << TEMP_TEMP_TEMP_Pos) /*!< Bit mask of TEMP field. */

/* Register: TEMP_A0 */
/* Description: Slope of 1st piece wise linear function */

/* Bits 11..0 : Slope of 1st piece wise linear function */
#define TEMP_A0_A0_Pos                    (0UL)                       /*!< Position of A0 field. */
#define TEMP_A0_A0_Msk                    (0xFFFUL << TEMP_A0_A0_Pos) /*!< Bit mask of A0 field. */

/* Register: TEMP_A1 */
/* Description: Slope of 2nd piece wise linear function */

/* Bits 11..0 : Slope of 2nd piece wise linear function */
#define TEMP_A1_A1_Pos                    (0UL)                       /*!< Position of A1 field. */
#define TEMP_A1_A1_Msk                    (0xFFFUL << TEMP_A1_A1_Pos) /*!< Bit mask of A1 field. */

/* Register: TEMP_A2 */
/* Description: Slope of 3rd piece wise linear function */

/* Bits 11..0 : Slope of 3rd piece wise linear function */
#define TEMP_A2_A2_Pos                    (0UL)                       /*!< Position of A2 field. */
#define TEMP_A2_A2_Msk                    (0xFFFUL << TEMP_A2_A2_Pos) /*!< Bit mask of A2 field. */

/* Register: TEMP_A3 */
/* Description: Slope of 4th piece wise linear function */

/* Bits 11..0 : Slope of 4th piece wise linear function */
#define TEMP_A3_A3_Pos                    (0UL)                       /*!< Position of A3 field. */
#define TEMP_A3_A3_Msk                    (0xFFFUL << TEMP_A3_A3_Pos) /*!< Bit mask of A3 field. */

/* Register: TEMP_A4 */
/* Description: Slope of 5th piece wise linear function */

/* Bits 11..0 : Slope of 5th piece wise linear function */
#define TEMP_A4_A4_Pos                    (0UL)                       /*!< Position of A4 field. */
#define TEMP_A4_A4_Msk                    (0xFFFUL << TEMP_A4_A4_Pos) /*!< Bit mask of A4 field. */

/* Register: TEMP_A5 */
/* Description: Slope of 6th piece wise linear function */

/* Bits 11..0 : Slope of 6th piece wise linear function */
#define TEMP_A5_A5_Pos                    (0UL)                       /*!< Position of A5 field. */
#define TEMP_A5_A5_Msk                    (0xFFFUL << TEMP_A5_A5_Pos) /*!< Bit mask of A5 field. */

/* Register: TEMP_B0 */
/* Description: y-intercept of 1st piece wise linear function */

/* Bits 13..0 : y-intercept of 1st piece wise linear function */
#define TEMP_B0_B0_Pos                    (0UL)                        /*!< Position of B0 field. */
#define TEMP_B0_B0_Msk                    (0x3FFFUL << TEMP_B0_B0_Pos) /*!< Bit mask of B0 field. */

/* Register: TEMP_B1 */
/* Description: y-intercept of 2nd piece wise linear function */

/* Bits 13..0 : y-intercept of 2nd piece wise linear function */
#define TEMP_B1_B1_Pos                    (0UL)                        /*!< Position of B1 field. */
#define TEMP_B1_B1_Msk                    (0x3FFFUL << TEMP_B1_B1_Pos) /*!< Bit mask of B1 field. */

/* Register: TEMP_B2 */
/* Description: y-intercept of 3rd piece wise linear function */

/* Bits 13..0 : y-intercept of 3rd piece wise linear function */
#define TEMP_B2_B2_Pos                    (0UL)                        /*!< Position of B2 field. */
#define TEMP_B2_B2_Msk                    (0x3FFFUL << TEMP_B2_B2_Pos) /*!< Bit mask of B2 field. */

/* Register: TEMP_B3 */
/* Description: y-intercept of 4th piece wise linear function */

/* Bits 13..0 : y-intercept of 4th piece wise linear function */
#define TEMP_B3_B3_Pos                    (0UL)                        /*!< Position of B3 field. */
#define TEMP_B3_B3_Msk                    (0x3FFFUL << TEMP_B3_B3_Pos) /*!< Bit mask of B3 field. */

/* Register: TEMP_B4 */
/* Description: y-intercept of 5th piece wise linear function */

/* Bits 13..0 : y-intercept of 5th piece wise linear function */
#define TEMP_B4_B4_Pos                    (0UL)                        /*!< Position of B4 field. */
#define TEMP_B4_B4_Msk                    (0x3FFFUL << TEMP_B4_B4_Pos) /*!< Bit mask of B4 field. */

/* Register: TEMP_B5 */
/* Description: y-intercept of 6th piece wise linear function */

/* Bits 13..0 : y-intercept of 6th piece wise linear function */
#define TEMP_B5_B5_Pos                    (0UL)                        /*!< Position of B5 field. */
#define TEMP_B5_B5_Msk                    (0x3FFFUL << TEMP_B5_B5_Pos) /*!< Bit mask of B5 field. */

/* Register: TEMP_T0 */
/* Description: End point of 1st piece wise linear function */

/* Bits 7..0 : End point of 1st piece wise linear function */
#define TEMP_T0_T0_Pos                    (0UL)                      /*!< Position of T0 field. */
#define TEMP_T0_T0_Msk                    (0xFFUL << TEMP_T0_T0_Pos) /*!< Bit mask of T0 field. */

/* Register: TEMP_T1 */
/* Description: End point of 2nd piece wise linear function */

/* Bits 7..0 : End point of 2nd piece wise linear function */
#define TEMP_T1_T1_Pos                    (0UL)                      /*!< Position of T1 field. */
#define TEMP_T1_T1_Msk                    (0xFFUL << TEMP_T1_T1_Pos) /*!< Bit mask of T1 field. */

/* Register: TEMP_T2 */
/* Description: End point of 3rd piece wise linear function */

/* Bits 7..0 : End point of 3rd piece wise linear function */
#define TEMP_T2_T2_Pos                    (0UL)                      /*!< Position of T2 field. */
#define TEMP_T2_T2_Msk                    (0xFFUL << TEMP_T2_T2_Pos) /*!< Bit mask of T2 field. */

/* Register: TEMP_T3 */
/* Description: End point of 4th piece wise linear function */

/* Bits 7..0 : End point of 4th piece wise linear function */
#define TEMP_T3_T3_Pos                    (0UL)                      /*!< Position of T3 field. */
#define TEMP_T3_T3_Msk                    (0xFFUL << TEMP_T3_T3_Pos) /*!< Bit mask of T3 field. */

/* Register: TEMP_T4 */
/* Description: End point of 5th piece wise linear function */

/* Bits 7..0 : End point of 5th piece wise linear function */
#define TEMP_T4_T4_Pos                    (0UL)                      /*!< Position of T4 field. */
#define TEMP_T4_T4_Msk                    (0xFFUL << TEMP_T4_T4_Pos) /*!< Bit mask of T4 field. */


/* Peripheral: TIMER */
/* Description: Timer/Counter 0 */

/* Register: TIMER_TASKS_START */
/* Description: Start Timer */

/* Bit 0 : Start Timer */
#define TIMER_TASKS_START_TASKS_START_Pos (0UL) /*!< Position of TASKS_START field. */
#define TIMER_TASKS_START_TASKS_START_Msk                                                          \
  (0x1UL << TIMER_TASKS_START_TASKS_START_Pos)      /*!< Bit mask of TASKS_START field. */
#define TIMER_TASKS_START_TASKS_START_Trigger (1UL) /*!< Trigger task */

/* Register: TIMER_TASKS_STOP */
/* Description: Stop Timer */

/* Bit 0 : Stop Timer */
#define TIMER_TASKS_STOP_TASKS_STOP_Pos       (0UL) /*!< Position of TASKS_STOP field. */
#define TIMER_TASKS_STOP_TASKS_STOP_Msk                                                            \
  (0x1UL << TIMER_TASKS_STOP_TASKS_STOP_Pos)      /*!< Bit mask of TASKS_STOP field. */
#define TIMER_TASKS_STOP_TASKS_STOP_Trigger (1UL) /*!< Trigger task */

/* Register: TIMER_TASKS_COUNT */
/* Description: Increment Timer (Counter mode only) */

/* Bit 0 : Increment Timer (Counter mode only) */
#define TIMER_TASKS_COUNT_TASKS_COUNT_Pos   (0UL) /*!< Position of TASKS_COUNT field. */
#define TIMER_TASKS_COUNT_TASKS_COUNT_Msk                                                          \
  (0x1UL << TIMER_TASKS_COUNT_TASKS_COUNT_Pos)      /*!< Bit mask of TASKS_COUNT field. */
#define TIMER_TASKS_COUNT_TASKS_COUNT_Trigger (1UL) /*!< Trigger task */

/* Register: TIMER_TASKS_CLEAR */
/* Description: Clear time */

/* Bit 0 : Clear time */
#define TIMER_TASKS_CLEAR_TASKS_CLEAR_Pos     (0UL) /*!< Position of TASKS_CLEAR field. */
#define TIMER_TASKS_CLEAR_TASKS_CLEAR_Msk                                                          \
  (0x1UL << TIMER_TASKS_CLEAR_TASKS_CLEAR_Pos)        /*!< Bit mask of TASKS_CLEAR field. */
#define TIMER_TASKS_CLEAR_TASKS_CLEAR_Trigger   (1UL) /*!< Trigger task */

/* Register: TIMER_TASKS_SHUTDOWN */
/* Description: Deprecated register - Shut down timer */

/* Bit 0 : Deprecated field -  Shut down timer */
#define TIMER_TASKS_SHUTDOWN_TASKS_SHUTDOWN_Pos (0UL) /*!< Position of TASKS_SHUTDOWN field. */
#define TIMER_TASKS_SHUTDOWN_TASKS_SHUTDOWN_Msk                                                    \
  (0x1UL << TIMER_TASKS_SHUTDOWN_TASKS_SHUTDOWN_Pos)      /*!< Bit mask of TASKS_SHUTDOWN field. */
#define TIMER_TASKS_SHUTDOWN_TASKS_SHUTDOWN_Trigger (1UL) /*!< Trigger task */

/* Register: TIMER_TASKS_CAPTURE */
/* Description: Description collection: Capture Timer value to CC[n] register */

/* Bit 0 : Capture Timer value to CC[n] register */
#define TIMER_TASKS_CAPTURE_TASKS_CAPTURE_Pos       (0UL) /*!< Position of TASKS_CAPTURE field. */
#define TIMER_TASKS_CAPTURE_TASKS_CAPTURE_Msk                                                      \
  (0x1UL << TIMER_TASKS_CAPTURE_TASKS_CAPTURE_Pos)      /*!< Bit mask of TASKS_CAPTURE field. */
#define TIMER_TASKS_CAPTURE_TASKS_CAPTURE_Trigger (1UL) /*!< Trigger task */

/* Register: TIMER_EVENTS_COMPARE */
/* Description: Description collection: Compare event on CC[n] match */

/* Bit 0 : Compare event on CC[n] match */
#define TIMER_EVENTS_COMPARE_EVENTS_COMPARE_Pos   (0UL) /*!< Position of EVENTS_COMPARE field. */
#define TIMER_EVENTS_COMPARE_EVENTS_COMPARE_Msk                                                    \
  (0x1UL << TIMER_EVENTS_COMPARE_EVENTS_COMPARE_Pos) /*!< Bit mask of EVENTS_COMPARE field. */
#define TIMER_EVENTS_COMPARE_EVENTS_COMPARE_NotGenerated (0UL) /*!< Event not generated */
#define TIMER_EVENTS_COMPARE_EVENTS_COMPARE_Generated    (1UL) /*!< Event generated */

/* Register: TIMER_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 13 : Shortcut between event COMPARE[5] and task STOP */
#define TIMER_SHORTS_COMPARE5_STOP_Pos                   (13UL) /*!< Position of COMPARE5_STOP field. */
#define TIMER_SHORTS_COMPARE5_STOP_Msk                                                             \
  (0x1UL << TIMER_SHORTS_COMPARE5_STOP_Pos)       /*!< Bit mask of COMPARE5_STOP field. */
#define TIMER_SHORTS_COMPARE5_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE5_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 12 : Shortcut between event COMPARE[4] and task STOP */
#define TIMER_SHORTS_COMPARE4_STOP_Pos      (12UL) /*!< Position of COMPARE4_STOP field. */
#define TIMER_SHORTS_COMPARE4_STOP_Msk                                                             \
  (0x1UL << TIMER_SHORTS_COMPARE4_STOP_Pos)       /*!< Bit mask of COMPARE4_STOP field. */
#define TIMER_SHORTS_COMPARE4_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE4_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 11 : Shortcut between event COMPARE[3] and task STOP */
#define TIMER_SHORTS_COMPARE3_STOP_Pos      (11UL) /*!< Position of COMPARE3_STOP field. */
#define TIMER_SHORTS_COMPARE3_STOP_Msk                                                             \
  (0x1UL << TIMER_SHORTS_COMPARE3_STOP_Pos)       /*!< Bit mask of COMPARE3_STOP field. */
#define TIMER_SHORTS_COMPARE3_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE3_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 10 : Shortcut between event COMPARE[2] and task STOP */
#define TIMER_SHORTS_COMPARE2_STOP_Pos      (10UL) /*!< Position of COMPARE2_STOP field. */
#define TIMER_SHORTS_COMPARE2_STOP_Msk                                                             \
  (0x1UL << TIMER_SHORTS_COMPARE2_STOP_Pos)       /*!< Bit mask of COMPARE2_STOP field. */
#define TIMER_SHORTS_COMPARE2_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE2_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 9 : Shortcut between event COMPARE[1] and task STOP */
#define TIMER_SHORTS_COMPARE1_STOP_Pos      (9UL) /*!< Position of COMPARE1_STOP field. */
#define TIMER_SHORTS_COMPARE1_STOP_Msk                                                             \
  (0x1UL << TIMER_SHORTS_COMPARE1_STOP_Pos)       /*!< Bit mask of COMPARE1_STOP field. */
#define TIMER_SHORTS_COMPARE1_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE1_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 8 : Shortcut between event COMPARE[0] and task STOP */
#define TIMER_SHORTS_COMPARE0_STOP_Pos      (8UL) /*!< Position of COMPARE0_STOP field. */
#define TIMER_SHORTS_COMPARE0_STOP_Msk                                                             \
  (0x1UL << TIMER_SHORTS_COMPARE0_STOP_Pos)       /*!< Bit mask of COMPARE0_STOP field. */
#define TIMER_SHORTS_COMPARE0_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE0_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 5 : Shortcut between event COMPARE[5] and task CLEAR */
#define TIMER_SHORTS_COMPARE5_CLEAR_Pos     (5UL) /*!< Position of COMPARE5_CLEAR field. */
#define TIMER_SHORTS_COMPARE5_CLEAR_Msk                                                            \
  (0x1UL << TIMER_SHORTS_COMPARE5_CLEAR_Pos)       /*!< Bit mask of COMPARE5_CLEAR field. */
#define TIMER_SHORTS_COMPARE5_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE5_CLEAR_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 4 : Shortcut between event COMPARE[4] and task CLEAR */
#define TIMER_SHORTS_COMPARE4_CLEAR_Pos      (4UL) /*!< Position of COMPARE4_CLEAR field. */
#define TIMER_SHORTS_COMPARE4_CLEAR_Msk                                                            \
  (0x1UL << TIMER_SHORTS_COMPARE4_CLEAR_Pos)       /*!< Bit mask of COMPARE4_CLEAR field. */
#define TIMER_SHORTS_COMPARE4_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE4_CLEAR_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between event COMPARE[3] and task CLEAR */
#define TIMER_SHORTS_COMPARE3_CLEAR_Pos      (3UL) /*!< Position of COMPARE3_CLEAR field. */
#define TIMER_SHORTS_COMPARE3_CLEAR_Msk                                                            \
  (0x1UL << TIMER_SHORTS_COMPARE3_CLEAR_Pos)       /*!< Bit mask of COMPARE3_CLEAR field. */
#define TIMER_SHORTS_COMPARE3_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE3_CLEAR_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between event COMPARE[2] and task CLEAR */
#define TIMER_SHORTS_COMPARE2_CLEAR_Pos      (2UL) /*!< Position of COMPARE2_CLEAR field. */
#define TIMER_SHORTS_COMPARE2_CLEAR_Msk                                                            \
  (0x1UL << TIMER_SHORTS_COMPARE2_CLEAR_Pos)       /*!< Bit mask of COMPARE2_CLEAR field. */
#define TIMER_SHORTS_COMPARE2_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE2_CLEAR_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between event COMPARE[1] and task CLEAR */
#define TIMER_SHORTS_COMPARE1_CLEAR_Pos      (1UL) /*!< Position of COMPARE1_CLEAR field. */
#define TIMER_SHORTS_COMPARE1_CLEAR_Msk                                                            \
  (0x1UL << TIMER_SHORTS_COMPARE1_CLEAR_Pos)       /*!< Bit mask of COMPARE1_CLEAR field. */
#define TIMER_SHORTS_COMPARE1_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE1_CLEAR_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between event COMPARE[0] and task CLEAR */
#define TIMER_SHORTS_COMPARE0_CLEAR_Pos      (0UL) /*!< Position of COMPARE0_CLEAR field. */
#define TIMER_SHORTS_COMPARE0_CLEAR_Msk                                                            \
  (0x1UL << TIMER_SHORTS_COMPARE0_CLEAR_Pos)       /*!< Bit mask of COMPARE0_CLEAR field. */
#define TIMER_SHORTS_COMPARE0_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE0_CLEAR_Enabled  (1UL) /*!< Enable shortcut */

/* Register: TIMER_INTENSET */
/* Description: Enable interrupt */

/* Bit 21 : Write '1' to enable interrupt for event COMPARE[5] */
#define TIMER_INTENSET_COMPARE5_Pos          (21UL) /*!< Position of COMPARE5 field. */
#define TIMER_INTENSET_COMPARE5_Msk                                                                \
  (0x1UL << TIMER_INTENSET_COMPARE5_Pos)       /*!< Bit mask of COMPARE5 field. */
#define TIMER_INTENSET_COMPARE5_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE5_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE5_Set      (1UL) /*!< Enable */

/* Bit 20 : Write '1' to enable interrupt for event COMPARE[4] */
#define TIMER_INTENSET_COMPARE4_Pos      (20UL) /*!< Position of COMPARE4 field. */
#define TIMER_INTENSET_COMPARE4_Msk                                                                \
  (0x1UL << TIMER_INTENSET_COMPARE4_Pos)       /*!< Bit mask of COMPARE4 field. */
#define TIMER_INTENSET_COMPARE4_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE4_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE4_Set      (1UL) /*!< Enable */

/* Bit 19 : Write '1' to enable interrupt for event COMPARE[3] */
#define TIMER_INTENSET_COMPARE3_Pos      (19UL) /*!< Position of COMPARE3 field. */
#define TIMER_INTENSET_COMPARE3_Msk                                                                \
  (0x1UL << TIMER_INTENSET_COMPARE3_Pos)       /*!< Bit mask of COMPARE3 field. */
#define TIMER_INTENSET_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE3_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE3_Set      (1UL) /*!< Enable */

/* Bit 18 : Write '1' to enable interrupt for event COMPARE[2] */
#define TIMER_INTENSET_COMPARE2_Pos      (18UL) /*!< Position of COMPARE2 field. */
#define TIMER_INTENSET_COMPARE2_Msk                                                                \
  (0x1UL << TIMER_INTENSET_COMPARE2_Pos)       /*!< Bit mask of COMPARE2 field. */
#define TIMER_INTENSET_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE2_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE2_Set      (1UL) /*!< Enable */

/* Bit 17 : Write '1' to enable interrupt for event COMPARE[1] */
#define TIMER_INTENSET_COMPARE1_Pos      (17UL) /*!< Position of COMPARE1 field. */
#define TIMER_INTENSET_COMPARE1_Msk                                                                \
  (0x1UL << TIMER_INTENSET_COMPARE1_Pos)       /*!< Bit mask of COMPARE1 field. */
#define TIMER_INTENSET_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE1_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE1_Set      (1UL) /*!< Enable */

/* Bit 16 : Write '1' to enable interrupt for event COMPARE[0] */
#define TIMER_INTENSET_COMPARE0_Pos      (16UL) /*!< Position of COMPARE0 field. */
#define TIMER_INTENSET_COMPARE0_Msk                                                                \
  (0x1UL << TIMER_INTENSET_COMPARE0_Pos)       /*!< Bit mask of COMPARE0 field. */
#define TIMER_INTENSET_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE0_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE0_Set      (1UL) /*!< Enable */

/* Register: TIMER_INTENCLR */
/* Description: Disable interrupt */

/* Bit 21 : Write '1' to disable interrupt for event COMPARE[5] */
#define TIMER_INTENCLR_COMPARE5_Pos      (21UL) /*!< Position of COMPARE5 field. */
#define TIMER_INTENCLR_COMPARE5_Msk                                                                \
  (0x1UL << TIMER_INTENCLR_COMPARE5_Pos)       /*!< Bit mask of COMPARE5 field. */
#define TIMER_INTENCLR_COMPARE5_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE5_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE5_Clear    (1UL) /*!< Disable */

/* Bit 20 : Write '1' to disable interrupt for event COMPARE[4] */
#define TIMER_INTENCLR_COMPARE4_Pos      (20UL) /*!< Position of COMPARE4 field. */
#define TIMER_INTENCLR_COMPARE4_Msk                                                                \
  (0x1UL << TIMER_INTENCLR_COMPARE4_Pos)       /*!< Bit mask of COMPARE4 field. */
#define TIMER_INTENCLR_COMPARE4_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE4_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE4_Clear    (1UL) /*!< Disable */

/* Bit 19 : Write '1' to disable interrupt for event COMPARE[3] */
#define TIMER_INTENCLR_COMPARE3_Pos      (19UL) /*!< Position of COMPARE3 field. */
#define TIMER_INTENCLR_COMPARE3_Msk                                                                \
  (0x1UL << TIMER_INTENCLR_COMPARE3_Pos)       /*!< Bit mask of COMPARE3 field. */
#define TIMER_INTENCLR_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE3_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE3_Clear    (1UL) /*!< Disable */

/* Bit 18 : Write '1' to disable interrupt for event COMPARE[2] */
#define TIMER_INTENCLR_COMPARE2_Pos      (18UL) /*!< Position of COMPARE2 field. */
#define TIMER_INTENCLR_COMPARE2_Msk                                                                \
  (0x1UL << TIMER_INTENCLR_COMPARE2_Pos)       /*!< Bit mask of COMPARE2 field. */
#define TIMER_INTENCLR_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE2_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE2_Clear    (1UL) /*!< Disable */

/* Bit 17 : Write '1' to disable interrupt for event COMPARE[1] */
#define TIMER_INTENCLR_COMPARE1_Pos      (17UL) /*!< Position of COMPARE1 field. */
#define TIMER_INTENCLR_COMPARE1_Msk                                                                \
  (0x1UL << TIMER_INTENCLR_COMPARE1_Pos)       /*!< Bit mask of COMPARE1 field. */
#define TIMER_INTENCLR_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE1_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE1_Clear    (1UL) /*!< Disable */

/* Bit 16 : Write '1' to disable interrupt for event COMPARE[0] */
#define TIMER_INTENCLR_COMPARE0_Pos      (16UL) /*!< Position of COMPARE0 field. */
#define TIMER_INTENCLR_COMPARE0_Msk                                                                \
  (0x1UL << TIMER_INTENCLR_COMPARE0_Pos)       /*!< Bit mask of COMPARE0 field. */
#define TIMER_INTENCLR_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE0_Enabled  (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE0_Clear    (1UL) /*!< Disable */

/* Register: TIMER_MODE */
/* Description: Timer mode selection */

/* Bits 1..0 : Timer mode */
#define TIMER_MODE_MODE_Pos              (0UL) /*!< Position of MODE field. */
#define TIMER_MODE_MODE_Msk              (0x3UL << TIMER_MODE_MODE_Pos) /*!< Bit mask of MODE field. */
#define TIMER_MODE_MODE_Timer            (0UL)                          /*!< Select Timer mode */
#define TIMER_MODE_MODE_Counter          (1UL) /*!< Deprecated enumerator -  Select Counter mode */
#define TIMER_MODE_MODE_LowPowerCounter  (2UL) /*!< Select Low Power Counter mode */

/* Register: TIMER_BITMODE */
/* Description: Configure the number of bits used by the TIMER */

/* Bits 1..0 : Timer bit width */
#define TIMER_BITMODE_BITMODE_Pos        (0UL) /*!< Position of BITMODE field. */
#define TIMER_BITMODE_BITMODE_Msk                                                                  \
  (0x3UL << TIMER_BITMODE_BITMODE_Pos)      /*!< Bit mask of BITMODE field. */
#define TIMER_BITMODE_BITMODE_16Bit   (0UL) /*!< 16 bit timer bit width */
#define TIMER_BITMODE_BITMODE_08Bit   (1UL) /*!< 8 bit timer bit width */
#define TIMER_BITMODE_BITMODE_24Bit   (2UL) /*!< 24 bit timer bit width */
#define TIMER_BITMODE_BITMODE_32Bit   (3UL) /*!< 32 bit timer bit width */

/* Register: TIMER_PRESCALER */
/* Description: Timer prescaler register */

/* Bits 3..0 : Prescaler value */
#define TIMER_PRESCALER_PRESCALER_Pos (0UL) /*!< Position of PRESCALER field. */
#define TIMER_PRESCALER_PRESCALER_Msk                                                              \
  (0xFUL << TIMER_PRESCALER_PRESCALER_Pos) /*!< Bit mask of PRESCALER field. */

/* Register: TIMER_CC */
/* Description: Description collection: Capture/Compare register n */

/* Bits 31..0 : Capture/Compare value */
#define TIMER_CC_CC_Pos                     (0UL) /*!< Position of CC field. */
#define TIMER_CC_CC_Msk                     (0xFFFFFFFFUL << TIMER_CC_CC_Pos) /*!< Bit mask of CC field. */


/* Peripheral: TWI */
/* Description: I2C compatible Two-Wire Interface 0 */

/* Register: TWI_TASKS_STARTRX */
/* Description: Start TWI receive sequence */

/* Bit 0 : Start TWI receive sequence */
#define TWI_TASKS_STARTRX_TASKS_STARTRX_Pos (0UL) /*!< Position of TASKS_STARTRX field. */
#define TWI_TASKS_STARTRX_TASKS_STARTRX_Msk                                                        \
  (0x1UL << TWI_TASKS_STARTRX_TASKS_STARTRX_Pos)      /*!< Bit mask of TASKS_STARTRX field. */
#define TWI_TASKS_STARTRX_TASKS_STARTRX_Trigger (1UL) /*!< Trigger task */

/* Register: TWI_TASKS_STARTTX */
/* Description: Start TWI transmit sequence */

/* Bit 0 : Start TWI transmit sequence */
#define TWI_TASKS_STARTTX_TASKS_STARTTX_Pos     (0UL) /*!< Position of TASKS_STARTTX field. */
#define TWI_TASKS_STARTTX_TASKS_STARTTX_Msk                                                        \
  (0x1UL << TWI_TASKS_STARTTX_TASKS_STARTTX_Pos)      /*!< Bit mask of TASKS_STARTTX field. */
#define TWI_TASKS_STARTTX_TASKS_STARTTX_Trigger (1UL) /*!< Trigger task */

/* Register: TWI_TASKS_STOP */
/* Description: Stop TWI transaction */

/* Bit 0 : Stop TWI transaction */
#define TWI_TASKS_STOP_TASKS_STOP_Pos           (0UL) /*!< Position of TASKS_STOP field. */
#define TWI_TASKS_STOP_TASKS_STOP_Msk                                                              \
  (0x1UL << TWI_TASKS_STOP_TASKS_STOP_Pos)        /*!< Bit mask of TASKS_STOP field. */
#define TWI_TASKS_STOP_TASKS_STOP_Trigger   (1UL) /*!< Trigger task */

/* Register: TWI_TASKS_SUSPEND */
/* Description: Suspend TWI transaction */

/* Bit 0 : Suspend TWI transaction */
#define TWI_TASKS_SUSPEND_TASKS_SUSPEND_Pos (0UL) /*!< Position of TASKS_SUSPEND field. */
#define TWI_TASKS_SUSPEND_TASKS_SUSPEND_Msk                                                        \
  (0x1UL << TWI_TASKS_SUSPEND_TASKS_SUSPEND_Pos)      /*!< Bit mask of TASKS_SUSPEND field. */
#define TWI_TASKS_SUSPEND_TASKS_SUSPEND_Trigger (1UL) /*!< Trigger task */

/* Register: TWI_TASKS_RESUME */
/* Description: Resume TWI transaction */

/* Bit 0 : Resume TWI transaction */
#define TWI_TASKS_RESUME_TASKS_RESUME_Pos       (0UL) /*!< Position of TASKS_RESUME field. */
#define TWI_TASKS_RESUME_TASKS_RESUME_Msk                                                          \
  (0x1UL << TWI_TASKS_RESUME_TASKS_RESUME_Pos)      /*!< Bit mask of TASKS_RESUME field. */
#define TWI_TASKS_RESUME_TASKS_RESUME_Trigger (1UL) /*!< Trigger task */

/* Register: TWI_EVENTS_STOPPED */
/* Description: TWI stopped */

/* Bit 0 : TWI stopped */
#define TWI_EVENTS_STOPPED_EVENTS_STOPPED_Pos (0UL) /*!< Position of EVENTS_STOPPED field. */
#define TWI_EVENTS_STOPPED_EVENTS_STOPPED_Msk                                                      \
  (0x1UL << TWI_EVENTS_STOPPED_EVENTS_STOPPED_Pos) /*!< Bit mask of EVENTS_STOPPED field. */
#define TWI_EVENTS_STOPPED_EVENTS_STOPPED_NotGenerated (0UL) /*!< Event not generated */
#define TWI_EVENTS_STOPPED_EVENTS_STOPPED_Generated    (1UL) /*!< Event generated */

/* Register: TWI_EVENTS_RXDREADY */
/* Description: TWI RXD byte received */

/* Bit 0 : TWI RXD byte received */
#define TWI_EVENTS_RXDREADY_EVENTS_RXDREADY_Pos        (0UL) /*!< Position of EVENTS_RXDREADY field. */
#define TWI_EVENTS_RXDREADY_EVENTS_RXDREADY_Msk                                                    \
  (0x1UL << TWI_EVENTS_RXDREADY_EVENTS_RXDREADY_Pos) /*!< Bit mask of EVENTS_RXDREADY field. */
#define TWI_EVENTS_RXDREADY_EVENTS_RXDREADY_NotGenerated (0UL) /*!< Event not generated */
#define TWI_EVENTS_RXDREADY_EVENTS_RXDREADY_Generated    (1UL) /*!< Event generated */

/* Register: TWI_EVENTS_TXDSENT */
/* Description: TWI TXD byte sent */

/* Bit 0 : TWI TXD byte sent */
#define TWI_EVENTS_TXDSENT_EVENTS_TXDSENT_Pos            (0UL) /*!< Position of EVENTS_TXDSENT field. */
#define TWI_EVENTS_TXDSENT_EVENTS_TXDSENT_Msk                                                      \
  (0x1UL << TWI_EVENTS_TXDSENT_EVENTS_TXDSENT_Pos) /*!< Bit mask of EVENTS_TXDSENT field. */
#define TWI_EVENTS_TXDSENT_EVENTS_TXDSENT_NotGenerated (0UL) /*!< Event not generated */
#define TWI_EVENTS_TXDSENT_EVENTS_TXDSENT_Generated    (1UL) /*!< Event generated */

/* Register: TWI_EVENTS_ERROR */
/* Description: TWI error */

/* Bit 0 : TWI error */
#define TWI_EVENTS_ERROR_EVENTS_ERROR_Pos              (0UL) /*!< Position of EVENTS_ERROR field. */
#define TWI_EVENTS_ERROR_EVENTS_ERROR_Msk                                                          \
  (0x1UL << TWI_EVENTS_ERROR_EVENTS_ERROR_Pos)           /*!< Bit mask of EVENTS_ERROR field. */
#define TWI_EVENTS_ERROR_EVENTS_ERROR_NotGenerated (0UL) /*!< Event not generated */
#define TWI_EVENTS_ERROR_EVENTS_ERROR_Generated    (1UL) /*!< Event generated */

/* Register: TWI_EVENTS_BB */
/* Description: TWI byte boundary, generated before each byte that is sent or received */

/* Bit 0 : TWI byte boundary, generated before each byte that is sent or received */
#define TWI_EVENTS_BB_EVENTS_BB_Pos                (0UL) /*!< Position of EVENTS_BB field. */
#define TWI_EVENTS_BB_EVENTS_BB_Msk                                                                \
  (0x1UL << TWI_EVENTS_BB_EVENTS_BB_Pos)                /*!< Bit mask of EVENTS_BB field. */
#define TWI_EVENTS_BB_EVENTS_BB_NotGenerated      (0UL) /*!< Event not generated */
#define TWI_EVENTS_BB_EVENTS_BB_Generated         (1UL) /*!< Event generated */

/* Register: TWI_EVENTS_SUSPENDED */
/* Description: TWI entered the suspended state */

/* Bit 0 : TWI entered the suspended state */
#define TWI_EVENTS_SUSPENDED_EVENTS_SUSPENDED_Pos (0UL) /*!< Position of EVENTS_SUSPENDED field. */
#define TWI_EVENTS_SUSPENDED_EVENTS_SUSPENDED_Msk                                                  \
  (0x1UL << TWI_EVENTS_SUSPENDED_EVENTS_SUSPENDED_Pos) /*!< Bit mask of EVENTS_SUSPENDED field. */
#define TWI_EVENTS_SUSPENDED_EVENTS_SUSPENDED_NotGenerated (0UL) /*!< Event not generated */
#define TWI_EVENTS_SUSPENDED_EVENTS_SUSPENDED_Generated    (1UL) /*!< Event generated */

/* Register: TWI_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 1 : Shortcut between event BB and task STOP */
#define TWI_SHORTS_BB_STOP_Pos                             (1UL) /*!< Position of BB_STOP field. */
#define TWI_SHORTS_BB_STOP_Msk                             (0x1UL << TWI_SHORTS_BB_STOP_Pos) /*!< Bit mask of BB_STOP field. */
#define TWI_SHORTS_BB_STOP_Disabled                        (0UL) /*!< Disable shortcut */
#define TWI_SHORTS_BB_STOP_Enabled                         (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between event BB and task SUSPEND */
#define TWI_SHORTS_BB_SUSPEND_Pos                          (0UL) /*!< Position of BB_SUSPEND field. */
#define TWI_SHORTS_BB_SUSPEND_Msk                                                                  \
  (0x1UL << TWI_SHORTS_BB_SUSPEND_Pos)       /*!< Bit mask of BB_SUSPEND field. */
#define TWI_SHORTS_BB_SUSPEND_Disabled (0UL) /*!< Disable shortcut */
#define TWI_SHORTS_BB_SUSPEND_Enabled  (1UL) /*!< Enable shortcut */

/* Register: TWI_INTENSET */
/* Description: Enable interrupt */

/* Bit 18 : Write '1' to enable interrupt for event SUSPENDED */
#define TWI_INTENSET_SUSPENDED_Pos     (18UL) /*!< Position of SUSPENDED field. */
#define TWI_INTENSET_SUSPENDED_Msk                                                                 \
  (0x1UL << TWI_INTENSET_SUSPENDED_Pos)       /*!< Bit mask of SUSPENDED field. */
#define TWI_INTENSET_SUSPENDED_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_SUSPENDED_Enabled  (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_SUSPENDED_Set      (1UL) /*!< Enable */

/* Bit 14 : Write '1' to enable interrupt for event BB */
#define TWI_INTENSET_BB_Pos             (14UL)                         /*!< Position of BB field. */
#define TWI_INTENSET_BB_Msk             (0x1UL << TWI_INTENSET_BB_Pos) /*!< Bit mask of BB field. */
#define TWI_INTENSET_BB_Disabled        (0UL)                          /*!< Read: Disabled */
#define TWI_INTENSET_BB_Enabled         (1UL)                          /*!< Read: Enabled */
#define TWI_INTENSET_BB_Set             (1UL)                          /*!< Enable */

/* Bit 9 : Write '1' to enable interrupt for event ERROR */
#define TWI_INTENSET_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define TWI_INTENSET_ERROR_Msk          (0x1UL << TWI_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWI_INTENSET_ERROR_Disabled     (0UL)                             /*!< Read: Disabled */
#define TWI_INTENSET_ERROR_Enabled      (1UL)                             /*!< Read: Enabled */
#define TWI_INTENSET_ERROR_Set          (1UL)                             /*!< Enable */

/* Bit 7 : Write '1' to enable interrupt for event TXDSENT */
#define TWI_INTENSET_TXDSENT_Pos        (7UL) /*!< Position of TXDSENT field. */
#define TWI_INTENSET_TXDSENT_Msk                                                                   \
  (0x1UL << TWI_INTENSET_TXDSENT_Pos)       /*!< Bit mask of TXDSENT field. */
#define TWI_INTENSET_TXDSENT_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_TXDSENT_Enabled  (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_TXDSENT_Set      (1UL) /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event RXDREADY */
#define TWI_INTENSET_RXDREADY_Pos     (2UL) /*!< Position of RXDREADY field. */
#define TWI_INTENSET_RXDREADY_Msk                                                                  \
  (0x1UL << TWI_INTENSET_RXDREADY_Pos)       /*!< Bit mask of RXDREADY field. */
#define TWI_INTENSET_RXDREADY_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_RXDREADY_Enabled  (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_RXDREADY_Set      (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event STOPPED */
#define TWI_INTENSET_STOPPED_Pos       (1UL) /*!< Position of STOPPED field. */
#define TWI_INTENSET_STOPPED_Msk                                                                   \
  (0x1UL << TWI_INTENSET_STOPPED_Pos)       /*!< Bit mask of STOPPED field. */
#define TWI_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_STOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_STOPPED_Set      (1UL) /*!< Enable */

/* Register: TWI_INTENCLR */
/* Description: Disable interrupt */

/* Bit 18 : Write '1' to disable interrupt for event SUSPENDED */
#define TWI_INTENCLR_SUSPENDED_Pos    (18UL) /*!< Position of SUSPENDED field. */
#define TWI_INTENCLR_SUSPENDED_Msk                                                                 \
  (0x1UL << TWI_INTENCLR_SUSPENDED_Pos)       /*!< Bit mask of SUSPENDED field. */
#define TWI_INTENCLR_SUSPENDED_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_SUSPENDED_Enabled  (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_SUSPENDED_Clear    (1UL) /*!< Disable */

/* Bit 14 : Write '1' to disable interrupt for event BB */
#define TWI_INTENCLR_BB_Pos             (14UL)                         /*!< Position of BB field. */
#define TWI_INTENCLR_BB_Msk             (0x1UL << TWI_INTENCLR_BB_Pos) /*!< Bit mask of BB field. */
#define TWI_INTENCLR_BB_Disabled        (0UL)                          /*!< Read: Disabled */
#define TWI_INTENCLR_BB_Enabled         (1UL)                          /*!< Read: Enabled */
#define TWI_INTENCLR_BB_Clear           (1UL)                          /*!< Disable */

/* Bit 9 : Write '1' to disable interrupt for event ERROR */
#define TWI_INTENCLR_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define TWI_INTENCLR_ERROR_Msk          (0x1UL << TWI_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWI_INTENCLR_ERROR_Disabled     (0UL)                             /*!< Read: Disabled */
#define TWI_INTENCLR_ERROR_Enabled      (1UL)                             /*!< Read: Enabled */
#define TWI_INTENCLR_ERROR_Clear        (1UL)                             /*!< Disable */

/* Bit 7 : Write '1' to disable interrupt for event TXDSENT */
#define TWI_INTENCLR_TXDSENT_Pos        (7UL) /*!< Position of TXDSENT field. */
#define TWI_INTENCLR_TXDSENT_Msk                                                                   \
  (0x1UL << TWI_INTENCLR_TXDSENT_Pos)       /*!< Bit mask of TXDSENT field. */
#define TWI_INTENCLR_TXDSENT_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_TXDSENT_Enabled  (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_TXDSENT_Clear    (1UL) /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event RXDREADY */
#define TWI_INTENCLR_RXDREADY_Pos     (2UL) /*!< Position of RXDREADY field. */
#define TWI_INTENCLR_RXDREADY_Msk                                                                  \
  (0x1UL << TWI_INTENCLR_RXDREADY_Pos)       /*!< Bit mask of RXDREADY field. */
#define TWI_INTENCLR_RXDREADY_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_RXDREADY_Enabled  (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_RXDREADY_Clear    (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event STOPPED */
#define TWI_INTENCLR_STOPPED_Pos       (1UL) /*!< Position of STOPPED field. */
#define TWI_INTENCLR_STOPPED_Msk                                                                   \
  (0x1UL << TWI_INTENCLR_STOPPED_Pos)       /*!< Bit mask of STOPPED field. */
#define TWI_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_STOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_STOPPED_Clear    (1UL) /*!< Disable */

/* Register: TWI_ERRORSRC */
/* Description: Error source */

/* Bit 2 : NACK received after sending a data byte (write '1' to clear) */
#define TWI_ERRORSRC_DNACK_Pos        (2UL) /*!< Position of DNACK field. */
#define TWI_ERRORSRC_DNACK_Msk        (0x1UL << TWI_ERRORSRC_DNACK_Pos) /*!< Bit mask of DNACK field. */
#define TWI_ERRORSRC_DNACK_NotPresent (0UL) /*!< Read: error not present */
#define TWI_ERRORSRC_DNACK_Present    (1UL) /*!< Read: error present */

/* Bit 1 : NACK received after sending the address (write '1' to clear) */
#define TWI_ERRORSRC_ANACK_Pos        (1UL) /*!< Position of ANACK field. */
#define TWI_ERRORSRC_ANACK_Msk        (0x1UL << TWI_ERRORSRC_ANACK_Pos) /*!< Bit mask of ANACK field. */
#define TWI_ERRORSRC_ANACK_NotPresent (0UL) /*!< Read: error not present */
#define TWI_ERRORSRC_ANACK_Present    (1UL) /*!< Read: error present */

/* Bit 0 : Overrun error */
#define TWI_ERRORSRC_OVERRUN_Pos      (0UL) /*!< Position of OVERRUN field. */
#define TWI_ERRORSRC_OVERRUN_Msk                                                                   \
  (0x1UL << TWI_ERRORSRC_OVERRUN_Pos)         /*!< Bit mask of OVERRUN field. */
#define TWI_ERRORSRC_OVERRUN_NotPresent (0UL) /*!< Read: no overrun occurred */
#define TWI_ERRORSRC_OVERRUN_Present    (1UL) /*!< Read: overrun occurred */

/* Register: TWI_ENABLE */
/* Description: Enable TWI */

/* Bits 3..0 : Enable or disable TWI */
#define TWI_ENABLE_ENABLE_Pos           (0UL) /*!< Position of ENABLE field. */
#define TWI_ENABLE_ENABLE_Msk           (0xFUL << TWI_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define TWI_ENABLE_ENABLE_Disabled      (0UL)                            /*!< Disable TWI */
#define TWI_ENABLE_ENABLE_Enabled       (5UL)                            /*!< Enable TWI */

/* Register: TWI_PSEL_SCL */
/* Description: Pin select for SCL */

/* Bit 31 : Connection */
#define TWI_PSEL_SCL_CONNECT_Pos        (31UL) /*!< Position of CONNECT field. */
#define TWI_PSEL_SCL_CONNECT_Msk                                                                   \
  (0x1UL << TWI_PSEL_SCL_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define TWI_PSEL_SCL_CONNECT_Connected    (0UL) /*!< Connect */
#define TWI_PSEL_SCL_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define TWI_PSEL_SCL_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define TWI_PSEL_SCL_PIN_Msk              (0x1FUL << TWI_PSEL_SCL_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWI_PSEL_SDA */
/* Description: Pin select for SDA */

/* Bit 31 : Connection */
#define TWI_PSEL_SDA_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define TWI_PSEL_SDA_CONNECT_Msk                                                                   \
  (0x1UL << TWI_PSEL_SDA_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define TWI_PSEL_SDA_CONNECT_Connected    (0UL) /*!< Connect */
#define TWI_PSEL_SDA_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define TWI_PSEL_SDA_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define TWI_PSEL_SDA_PIN_Msk              (0x1FUL << TWI_PSEL_SDA_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWI_RXD */
/* Description: RXD register */

/* Bits 7..0 : RXD register */
#define TWI_RXD_RXD_Pos                   (0UL)                       /*!< Position of RXD field. */
#define TWI_RXD_RXD_Msk                   (0xFFUL << TWI_RXD_RXD_Pos) /*!< Bit mask of RXD field. */

/* Register: TWI_TXD */
/* Description: TXD register */

/* Bits 7..0 : TXD register */
#define TWI_TXD_TXD_Pos                   (0UL)                       /*!< Position of TXD field. */
#define TWI_TXD_TXD_Msk                   (0xFFUL << TWI_TXD_TXD_Pos) /*!< Bit mask of TXD field. */

/* Register: TWI_FREQUENCY */
/* Description: TWI frequency. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : TWI master clock frequency */
#define TWI_FREQUENCY_FREQUENCY_Pos       (0UL) /*!< Position of FREQUENCY field. */
#define TWI_FREQUENCY_FREQUENCY_Msk                                                                \
  (0xFFFFFFFFUL << TWI_FREQUENCY_FREQUENCY_Pos)     /*!< Bit mask of FREQUENCY field. */
#define TWI_FREQUENCY_FREQUENCY_K100 (0x01980000UL) /*!< 100 kbps */
#define TWI_FREQUENCY_FREQUENCY_K250 (0x04000000UL) /*!< 250 kbps */
#define TWI_FREQUENCY_FREQUENCY_K400 (0x06680000UL) /*!< 400 kbps (actual rate 410.256 kbps) */

/* Register: TWI_ADDRESS */
/* Description: Address used in the TWI transfer */

/* Bits 6..0 : Address used in the TWI transfer */
#define TWI_ADDRESS_ADDRESS_Pos      (0UL) /*!< Position of ADDRESS field. */
#define TWI_ADDRESS_ADDRESS_Msk                                                                    \
  (0x7FUL << TWI_ADDRESS_ADDRESS_Pos) /*!< Bit mask of ADDRESS field. */


/* Peripheral: TWIM */
/* Description: I2C compatible Two-Wire Master Interface with EasyDMA 0 */

/* Register: TWIM_TASKS_STARTRX */
/* Description: Start TWI receive sequence */

/* Bit 0 : Start TWI receive sequence */
#define TWIM_TASKS_STARTRX_TASKS_STARTRX_Pos (0UL) /*!< Position of TASKS_STARTRX field. */
#define TWIM_TASKS_STARTRX_TASKS_STARTRX_Msk                                                       \
  (0x1UL << TWIM_TASKS_STARTRX_TASKS_STARTRX_Pos)      /*!< Bit mask of TASKS_STARTRX field. */
#define TWIM_TASKS_STARTRX_TASKS_STARTRX_Trigger (1UL) /*!< Trigger task */

/* Register: TWIM_TASKS_STARTTX */
/* Description: Start TWI transmit sequence */

/* Bit 0 : Start TWI transmit sequence */
#define TWIM_TASKS_STARTTX_TASKS_STARTTX_Pos     (0UL) /*!< Position of TASKS_STARTTX field. */
#define TWIM_TASKS_STARTTX_TASKS_STARTTX_Msk                                                       \
  (0x1UL << TWIM_TASKS_STARTTX_TASKS_STARTTX_Pos)      /*!< Bit mask of TASKS_STARTTX field. */
#define TWIM_TASKS_STARTTX_TASKS_STARTTX_Trigger (1UL) /*!< Trigger task */

/* Register: TWIM_TASKS_STOP */
/* Description: Stop TWI transaction. Must be issued while the TWI master is not suspended. */

/* Bit 0 : Stop TWI transaction. Must be issued while the TWI master is not suspended. */
#define TWIM_TASKS_STOP_TASKS_STOP_Pos           (0UL) /*!< Position of TASKS_STOP field. */
#define TWIM_TASKS_STOP_TASKS_STOP_Msk                                                             \
  (0x1UL << TWIM_TASKS_STOP_TASKS_STOP_Pos)        /*!< Bit mask of TASKS_STOP field. */
#define TWIM_TASKS_STOP_TASKS_STOP_Trigger   (1UL) /*!< Trigger task */

/* Register: TWIM_TASKS_SUSPEND */
/* Description: Suspend TWI transaction */

/* Bit 0 : Suspend TWI transaction */
#define TWIM_TASKS_SUSPEND_TASKS_SUSPEND_Pos (0UL) /*!< Position of TASKS_SUSPEND field. */
#define TWIM_TASKS_SUSPEND_TASKS_SUSPEND_Msk                                                       \
  (0x1UL << TWIM_TASKS_SUSPEND_TASKS_SUSPEND_Pos)      /*!< Bit mask of TASKS_SUSPEND field. */
#define TWIM_TASKS_SUSPEND_TASKS_SUSPEND_Trigger (1UL) /*!< Trigger task */

/* Register: TWIM_TASKS_RESUME */
/* Description: Resume TWI transaction */

/* Bit 0 : Resume TWI transaction */
#define TWIM_TASKS_RESUME_TASKS_RESUME_Pos       (0UL) /*!< Position of TASKS_RESUME field. */
#define TWIM_TASKS_RESUME_TASKS_RESUME_Msk                                                         \
  (0x1UL << TWIM_TASKS_RESUME_TASKS_RESUME_Pos)      /*!< Bit mask of TASKS_RESUME field. */
#define TWIM_TASKS_RESUME_TASKS_RESUME_Trigger (1UL) /*!< Trigger task */

/* Register: TWIM_EVENTS_STOPPED */
/* Description: TWI stopped */

/* Bit 0 : TWI stopped */
#define TWIM_EVENTS_STOPPED_EVENTS_STOPPED_Pos (0UL) /*!< Position of EVENTS_STOPPED field. */
#define TWIM_EVENTS_STOPPED_EVENTS_STOPPED_Msk                                                     \
  (0x1UL << TWIM_EVENTS_STOPPED_EVENTS_STOPPED_Pos) /*!< Bit mask of EVENTS_STOPPED field. */
#define TWIM_EVENTS_STOPPED_EVENTS_STOPPED_NotGenerated (0UL) /*!< Event not generated */
#define TWIM_EVENTS_STOPPED_EVENTS_STOPPED_Generated    (1UL) /*!< Event generated */

/* Register: TWIM_EVENTS_ERROR */
/* Description: TWI error */

/* Bit 0 : TWI error */
#define TWIM_EVENTS_ERROR_EVENTS_ERROR_Pos              (0UL) /*!< Position of EVENTS_ERROR field. */
#define TWIM_EVENTS_ERROR_EVENTS_ERROR_Msk                                                         \
  (0x1UL << TWIM_EVENTS_ERROR_EVENTS_ERROR_Pos)           /*!< Bit mask of EVENTS_ERROR field. */
#define TWIM_EVENTS_ERROR_EVENTS_ERROR_NotGenerated (0UL) /*!< Event not generated */
#define TWIM_EVENTS_ERROR_EVENTS_ERROR_Generated    (1UL) /*!< Event generated */

/* Register: TWIM_EVENTS_SUSPENDED */
/* Description: Last byte has been sent out after the SUSPEND task has been issued, TWI traffic is now suspended. */

/* Bit 0 : Last byte has been sent out after the SUSPEND task has been issued, TWI traffic is now suspended. */
#define TWIM_EVENTS_SUSPENDED_EVENTS_SUSPENDED_Pos  (0UL) /*!< Position of EVENTS_SUSPENDED field. */
#define TWIM_EVENTS_SUSPENDED_EVENTS_SUSPENDED_Msk                                                 \
  (0x1UL << TWIM_EVENTS_SUSPENDED_EVENTS_SUSPENDED_Pos) /*!< Bit mask of EVENTS_SUSPENDED field. */
#define TWIM_EVENTS_SUSPENDED_EVENTS_SUSPENDED_NotGenerated (0UL) /*!< Event not generated */
#define TWIM_EVENTS_SUSPENDED_EVENTS_SUSPENDED_Generated    (1UL) /*!< Event generated */

/* Register: TWIM_EVENTS_RXSTARTED */
/* Description: Receive sequence started */

/* Bit 0 : Receive sequence started */
#define TWIM_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Pos          (0UL) /*!< Position of EVENTS_RXSTARTED field. */
#define TWIM_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Msk                                                 \
  (0x1UL << TWIM_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Pos) /*!< Bit mask of EVENTS_RXSTARTED field. */
#define TWIM_EVENTS_RXSTARTED_EVENTS_RXSTARTED_NotGenerated (0UL) /*!< Event not generated */
#define TWIM_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Generated    (1UL) /*!< Event generated */

/* Register: TWIM_EVENTS_TXSTARTED */
/* Description: Transmit sequence started */

/* Bit 0 : Transmit sequence started */
#define TWIM_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Pos          (0UL) /*!< Position of EVENTS_TXSTARTED field. */
#define TWIM_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Msk                                                 \
  (0x1UL << TWIM_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Pos) /*!< Bit mask of EVENTS_TXSTARTED field. */
#define TWIM_EVENTS_TXSTARTED_EVENTS_TXSTARTED_NotGenerated (0UL) /*!< Event not generated */
#define TWIM_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Generated    (1UL) /*!< Event generated */

/* Register: TWIM_EVENTS_LASTRX */
/* Description: Byte boundary, starting to receive the last byte */

/* Bit 0 : Byte boundary, starting to receive the last byte */
#define TWIM_EVENTS_LASTRX_EVENTS_LASTRX_Pos                (0UL) /*!< Position of EVENTS_LASTRX field. */
#define TWIM_EVENTS_LASTRX_EVENTS_LASTRX_Msk                                                       \
  (0x1UL << TWIM_EVENTS_LASTRX_EVENTS_LASTRX_Pos)           /*!< Bit mask of EVENTS_LASTRX field. */
#define TWIM_EVENTS_LASTRX_EVENTS_LASTRX_NotGenerated (0UL) /*!< Event not generated */
#define TWIM_EVENTS_LASTRX_EVENTS_LASTRX_Generated    (1UL) /*!< Event generated */

/* Register: TWIM_EVENTS_LASTTX */
/* Description: Byte boundary, starting to transmit the last byte */

/* Bit 0 : Byte boundary, starting to transmit the last byte */
#define TWIM_EVENTS_LASTTX_EVENTS_LASTTX_Pos          (0UL) /*!< Position of EVENTS_LASTTX field. */
#define TWIM_EVENTS_LASTTX_EVENTS_LASTTX_Msk                                                       \
  (0x1UL << TWIM_EVENTS_LASTTX_EVENTS_LASTTX_Pos)           /*!< Bit mask of EVENTS_LASTTX field. */
#define TWIM_EVENTS_LASTTX_EVENTS_LASTTX_NotGenerated (0UL) /*!< Event not generated */
#define TWIM_EVENTS_LASTTX_EVENTS_LASTTX_Generated    (1UL) /*!< Event generated */

/* Register: TWIM_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 12 : Shortcut between event LASTRX and task STOP */
#define TWIM_SHORTS_LASTRX_STOP_Pos                   (12UL) /*!< Position of LASTRX_STOP field. */
#define TWIM_SHORTS_LASTRX_STOP_Msk                                                                \
  (0x1UL << TWIM_SHORTS_LASTRX_STOP_Pos)       /*!< Bit mask of LASTRX_STOP field. */
#define TWIM_SHORTS_LASTRX_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTRX_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 11 : Shortcut between event LASTRX and task SUSPEND */
#define TWIM_SHORTS_LASTRX_SUSPEND_Pos   (11UL) /*!< Position of LASTRX_SUSPEND field. */
#define TWIM_SHORTS_LASTRX_SUSPEND_Msk                                                             \
  (0x1UL << TWIM_SHORTS_LASTRX_SUSPEND_Pos)       /*!< Bit mask of LASTRX_SUSPEND field. */
#define TWIM_SHORTS_LASTRX_SUSPEND_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTRX_SUSPEND_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 10 : Shortcut between event LASTRX and task STARTTX */
#define TWIM_SHORTS_LASTRX_STARTTX_Pos      (10UL) /*!< Position of LASTRX_STARTTX field. */
#define TWIM_SHORTS_LASTRX_STARTTX_Msk                                                             \
  (0x1UL << TWIM_SHORTS_LASTRX_STARTTX_Pos)       /*!< Bit mask of LASTRX_STARTTX field. */
#define TWIM_SHORTS_LASTRX_STARTTX_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTRX_STARTTX_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 9 : Shortcut between event LASTTX and task STOP */
#define TWIM_SHORTS_LASTTX_STOP_Pos         (9UL) /*!< Position of LASTTX_STOP field. */
#define TWIM_SHORTS_LASTTX_STOP_Msk                                                                \
  (0x1UL << TWIM_SHORTS_LASTTX_STOP_Pos)       /*!< Bit mask of LASTTX_STOP field. */
#define TWIM_SHORTS_LASTTX_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTTX_STOP_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 8 : Shortcut between event LASTTX and task SUSPEND */
#define TWIM_SHORTS_LASTTX_SUSPEND_Pos   (8UL) /*!< Position of LASTTX_SUSPEND field. */
#define TWIM_SHORTS_LASTTX_SUSPEND_Msk                                                             \
  (0x1UL << TWIM_SHORTS_LASTTX_SUSPEND_Pos)       /*!< Bit mask of LASTTX_SUSPEND field. */
#define TWIM_SHORTS_LASTTX_SUSPEND_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTTX_SUSPEND_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 7 : Shortcut between event LASTTX and task STARTRX */
#define TWIM_SHORTS_LASTTX_STARTRX_Pos      (7UL) /*!< Position of LASTTX_STARTRX field. */
#define TWIM_SHORTS_LASTTX_STARTRX_Msk                                                             \
  (0x1UL << TWIM_SHORTS_LASTTX_STARTRX_Pos)       /*!< Bit mask of LASTTX_STARTRX field. */
#define TWIM_SHORTS_LASTTX_STARTRX_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTTX_STARTRX_Enabled  (1UL) /*!< Enable shortcut */

/* Register: TWIM_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 24 : Enable or disable interrupt for event LASTTX */
#define TWIM_INTEN_LASTTX_Pos               (24UL) /*!< Position of LASTTX field. */
#define TWIM_INTEN_LASTTX_Msk               (0x1UL << TWIM_INTEN_LASTTX_Pos) /*!< Bit mask of LASTTX field. */
#define TWIM_INTEN_LASTTX_Disabled          (0UL)                            /*!< Disable */
#define TWIM_INTEN_LASTTX_Enabled           (1UL)                            /*!< Enable */

/* Bit 23 : Enable or disable interrupt for event LASTRX */
#define TWIM_INTEN_LASTRX_Pos               (23UL) /*!< Position of LASTRX field. */
#define TWIM_INTEN_LASTRX_Msk               (0x1UL << TWIM_INTEN_LASTRX_Pos) /*!< Bit mask of LASTRX field. */
#define TWIM_INTEN_LASTRX_Disabled          (0UL)                            /*!< Disable */
#define TWIM_INTEN_LASTRX_Enabled           (1UL)                            /*!< Enable */

/* Bit 20 : Enable or disable interrupt for event TXSTARTED */
#define TWIM_INTEN_TXSTARTED_Pos            (20UL) /*!< Position of TXSTARTED field. */
#define TWIM_INTEN_TXSTARTED_Msk                                                                   \
  (0x1UL << TWIM_INTEN_TXSTARTED_Pos)       /*!< Bit mask of TXSTARTED field. */
#define TWIM_INTEN_TXSTARTED_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_TXSTARTED_Enabled  (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for event RXSTARTED */
#define TWIM_INTEN_RXSTARTED_Pos      (19UL) /*!< Position of RXSTARTED field. */
#define TWIM_INTEN_RXSTARTED_Msk                                                                   \
  (0x1UL << TWIM_INTEN_RXSTARTED_Pos)       /*!< Bit mask of RXSTARTED field. */
#define TWIM_INTEN_RXSTARTED_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_RXSTARTED_Enabled  (1UL) /*!< Enable */

/* Bit 18 : Enable or disable interrupt for event SUSPENDED */
#define TWIM_INTEN_SUSPENDED_Pos      (18UL) /*!< Position of SUSPENDED field. */
#define TWIM_INTEN_SUSPENDED_Msk                                                                   \
  (0x1UL << TWIM_INTEN_SUSPENDED_Pos)       /*!< Bit mask of SUSPENDED field. */
#define TWIM_INTEN_SUSPENDED_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_SUSPENDED_Enabled  (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for event ERROR */
#define TWIM_INTEN_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define TWIM_INTEN_ERROR_Msk          (0x1UL << TWIM_INTEN_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIM_INTEN_ERROR_Disabled     (0UL)                           /*!< Disable */
#define TWIM_INTEN_ERROR_Enabled      (1UL)                           /*!< Enable */

/* Bit 1 : Enable or disable interrupt for event STOPPED */
#define TWIM_INTEN_STOPPED_Pos        (1UL) /*!< Position of STOPPED field. */
#define TWIM_INTEN_STOPPED_Msk        (0x1UL << TWIM_INTEN_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWIM_INTEN_STOPPED_Disabled   (0UL)                             /*!< Disable */
#define TWIM_INTEN_STOPPED_Enabled    (1UL)                             /*!< Enable */

/* Register: TWIM_INTENSET */
/* Description: Enable interrupt */

/* Bit 24 : Write '1' to enable interrupt for event LASTTX */
#define TWIM_INTENSET_LASTTX_Pos      (24UL) /*!< Position of LASTTX field. */
#define TWIM_INTENSET_LASTTX_Msk                                                                   \
  (0x1UL << TWIM_INTENSET_LASTTX_Pos)       /*!< Bit mask of LASTTX field. */
#define TWIM_INTENSET_LASTTX_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_LASTTX_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_LASTTX_Set      (1UL) /*!< Enable */

/* Bit 23 : Write '1' to enable interrupt for event LASTRX */
#define TWIM_INTENSET_LASTRX_Pos      (23UL) /*!< Position of LASTRX field. */
#define TWIM_INTENSET_LASTRX_Msk                                                                   \
  (0x1UL << TWIM_INTENSET_LASTRX_Pos)       /*!< Bit mask of LASTRX field. */
#define TWIM_INTENSET_LASTRX_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_LASTRX_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_LASTRX_Set      (1UL) /*!< Enable */

/* Bit 20 : Write '1' to enable interrupt for event TXSTARTED */
#define TWIM_INTENSET_TXSTARTED_Pos   (20UL) /*!< Position of TXSTARTED field. */
#define TWIM_INTENSET_TXSTARTED_Msk                                                                \
  (0x1UL << TWIM_INTENSET_TXSTARTED_Pos)       /*!< Bit mask of TXSTARTED field. */
#define TWIM_INTENSET_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_TXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_TXSTARTED_Set      (1UL) /*!< Enable */

/* Bit 19 : Write '1' to enable interrupt for event RXSTARTED */
#define TWIM_INTENSET_RXSTARTED_Pos      (19UL) /*!< Position of RXSTARTED field. */
#define TWIM_INTENSET_RXSTARTED_Msk                                                                \
  (0x1UL << TWIM_INTENSET_RXSTARTED_Pos)       /*!< Bit mask of RXSTARTED field. */
#define TWIM_INTENSET_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_RXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_RXSTARTED_Set      (1UL) /*!< Enable */

/* Bit 18 : Write '1' to enable interrupt for event SUSPENDED */
#define TWIM_INTENSET_SUSPENDED_Pos      (18UL) /*!< Position of SUSPENDED field. */
#define TWIM_INTENSET_SUSPENDED_Msk                                                                \
  (0x1UL << TWIM_INTENSET_SUSPENDED_Pos)       /*!< Bit mask of SUSPENDED field. */
#define TWIM_INTENSET_SUSPENDED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_SUSPENDED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_SUSPENDED_Set      (1UL) /*!< Enable */

/* Bit 9 : Write '1' to enable interrupt for event ERROR */
#define TWIM_INTENSET_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define TWIM_INTENSET_ERROR_Msk          (0x1UL << TWIM_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIM_INTENSET_ERROR_Disabled     (0UL)                              /*!< Read: Disabled */
#define TWIM_INTENSET_ERROR_Enabled      (1UL)                              /*!< Read: Enabled */
#define TWIM_INTENSET_ERROR_Set          (1UL)                              /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event STOPPED */
#define TWIM_INTENSET_STOPPED_Pos        (1UL) /*!< Position of STOPPED field. */
#define TWIM_INTENSET_STOPPED_Msk                                                                  \
  (0x1UL << TWIM_INTENSET_STOPPED_Pos)       /*!< Bit mask of STOPPED field. */
#define TWIM_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_STOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_STOPPED_Set      (1UL) /*!< Enable */

/* Register: TWIM_INTENCLR */
/* Description: Disable interrupt */

/* Bit 24 : Write '1' to disable interrupt for event LASTTX */
#define TWIM_INTENCLR_LASTTX_Pos       (24UL) /*!< Position of LASTTX field. */
#define TWIM_INTENCLR_LASTTX_Msk                                                                   \
  (0x1UL << TWIM_INTENCLR_LASTTX_Pos)       /*!< Bit mask of LASTTX field. */
#define TWIM_INTENCLR_LASTTX_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_LASTTX_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_LASTTX_Clear    (1UL) /*!< Disable */

/* Bit 23 : Write '1' to disable interrupt for event LASTRX */
#define TWIM_INTENCLR_LASTRX_Pos      (23UL) /*!< Position of LASTRX field. */
#define TWIM_INTENCLR_LASTRX_Msk                                                                   \
  (0x1UL << TWIM_INTENCLR_LASTRX_Pos)       /*!< Bit mask of LASTRX field. */
#define TWIM_INTENCLR_LASTRX_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_LASTRX_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_LASTRX_Clear    (1UL) /*!< Disable */

/* Bit 20 : Write '1' to disable interrupt for event TXSTARTED */
#define TWIM_INTENCLR_TXSTARTED_Pos   (20UL) /*!< Position of TXSTARTED field. */
#define TWIM_INTENCLR_TXSTARTED_Msk                                                                \
  (0x1UL << TWIM_INTENCLR_TXSTARTED_Pos)       /*!< Bit mask of TXSTARTED field. */
#define TWIM_INTENCLR_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_TXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_TXSTARTED_Clear    (1UL) /*!< Disable */

/* Bit 19 : Write '1' to disable interrupt for event RXSTARTED */
#define TWIM_INTENCLR_RXSTARTED_Pos      (19UL) /*!< Position of RXSTARTED field. */
#define TWIM_INTENCLR_RXSTARTED_Msk                                                                \
  (0x1UL << TWIM_INTENCLR_RXSTARTED_Pos)       /*!< Bit mask of RXSTARTED field. */
#define TWIM_INTENCLR_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_RXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_RXSTARTED_Clear    (1UL) /*!< Disable */

/* Bit 18 : Write '1' to disable interrupt for event SUSPENDED */
#define TWIM_INTENCLR_SUSPENDED_Pos      (18UL) /*!< Position of SUSPENDED field. */
#define TWIM_INTENCLR_SUSPENDED_Msk                                                                \
  (0x1UL << TWIM_INTENCLR_SUSPENDED_Pos)       /*!< Bit mask of SUSPENDED field. */
#define TWIM_INTENCLR_SUSPENDED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_SUSPENDED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_SUSPENDED_Clear    (1UL) /*!< Disable */

/* Bit 9 : Write '1' to disable interrupt for event ERROR */
#define TWIM_INTENCLR_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define TWIM_INTENCLR_ERROR_Msk          (0x1UL << TWIM_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIM_INTENCLR_ERROR_Disabled     (0UL)                              /*!< Read: Disabled */
#define TWIM_INTENCLR_ERROR_Enabled      (1UL)                              /*!< Read: Enabled */
#define TWIM_INTENCLR_ERROR_Clear        (1UL)                              /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event STOPPED */
#define TWIM_INTENCLR_STOPPED_Pos        (1UL) /*!< Position of STOPPED field. */
#define TWIM_INTENCLR_STOPPED_Msk                                                                  \
  (0x1UL << TWIM_INTENCLR_STOPPED_Pos)        /*!< Bit mask of STOPPED field. */
#define TWIM_INTENCLR_STOPPED_Disabled  (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_STOPPED_Enabled   (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_STOPPED_Clear     (1UL) /*!< Disable */

/* Register: TWIM_ERRORSRC */
/* Description: Error source */

/* Bit 2 : NACK received after sending a data byte (write '1' to clear) */
#define TWIM_ERRORSRC_DNACK_Pos         (2UL) /*!< Position of DNACK field. */
#define TWIM_ERRORSRC_DNACK_Msk         (0x1UL << TWIM_ERRORSRC_DNACK_Pos) /*!< Bit mask of DNACK field. */
#define TWIM_ERRORSRC_DNACK_NotReceived (0UL) /*!< Error did not occur */
#define TWIM_ERRORSRC_DNACK_Received    (1UL) /*!< Error occurred */

/* Bit 1 : NACK received after sending the address (write '1' to clear) */
#define TWIM_ERRORSRC_ANACK_Pos         (1UL) /*!< Position of ANACK field. */
#define TWIM_ERRORSRC_ANACK_Msk         (0x1UL << TWIM_ERRORSRC_ANACK_Pos) /*!< Bit mask of ANACK field. */
#define TWIM_ERRORSRC_ANACK_NotReceived (0UL) /*!< Error did not occur */
#define TWIM_ERRORSRC_ANACK_Received    (1UL) /*!< Error occurred */

/* Bit 0 : Overrun error */
#define TWIM_ERRORSRC_OVERRUN_Pos       (0UL) /*!< Position of OVERRUN field. */
#define TWIM_ERRORSRC_OVERRUN_Msk                                                                  \
  (0x1UL << TWIM_ERRORSRC_OVERRUN_Pos)          /*!< Bit mask of OVERRUN field. */
#define TWIM_ERRORSRC_OVERRUN_NotReceived (0UL) /*!< Error did not occur */
#define TWIM_ERRORSRC_OVERRUN_Received    (1UL) /*!< Error occurred */

/* Register: TWIM_ENABLE */
/* Description: Enable TWIM */

/* Bits 3..0 : Enable or disable TWIM */
#define TWIM_ENABLE_ENABLE_Pos            (0UL) /*!< Position of ENABLE field. */
#define TWIM_ENABLE_ENABLE_Msk            (0xFUL << TWIM_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define TWIM_ENABLE_ENABLE_Disabled       (0UL)                             /*!< Disable TWIM */
#define TWIM_ENABLE_ENABLE_Enabled        (6UL)                             /*!< Enable TWIM */

/* Register: TWIM_PSEL_SCL */
/* Description: Pin select for SCL signal */

/* Bit 31 : Connection */
#define TWIM_PSEL_SCL_CONNECT_Pos         (31UL) /*!< Position of CONNECT field. */
#define TWIM_PSEL_SCL_CONNECT_Msk                                                                  \
  (0x1UL << TWIM_PSEL_SCL_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define TWIM_PSEL_SCL_CONNECT_Connected    (0UL) /*!< Connect */
#define TWIM_PSEL_SCL_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define TWIM_PSEL_SCL_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define TWIM_PSEL_SCL_PIN_Msk              (0x1FUL << TWIM_PSEL_SCL_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWIM_PSEL_SDA */
/* Description: Pin select for SDA signal */

/* Bit 31 : Connection */
#define TWIM_PSEL_SDA_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define TWIM_PSEL_SDA_CONNECT_Msk                                                                  \
  (0x1UL << TWIM_PSEL_SDA_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define TWIM_PSEL_SDA_CONNECT_Connected    (0UL) /*!< Connect */
#define TWIM_PSEL_SDA_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define TWIM_PSEL_SDA_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define TWIM_PSEL_SDA_PIN_Msk              (0x1FUL << TWIM_PSEL_SDA_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWIM_FREQUENCY */
/* Description: TWI frequency. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : TWI master clock frequency */
#define TWIM_FREQUENCY_FREQUENCY_Pos       (0UL) /*!< Position of FREQUENCY field. */
#define TWIM_FREQUENCY_FREQUENCY_Msk                                                               \
  (0xFFFFFFFFUL << TWIM_FREQUENCY_FREQUENCY_Pos)     /*!< Bit mask of FREQUENCY field. */
#define TWIM_FREQUENCY_FREQUENCY_K100 (0x01980000UL) /*!< 100 kbps */
#define TWIM_FREQUENCY_FREQUENCY_K250 (0x04000000UL) /*!< 250 kbps */
#define TWIM_FREQUENCY_FREQUENCY_K400 (0x06400000UL) /*!< 400 kbps */

/* Register: TWIM_RXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define TWIM_RXD_PTR_PTR_Pos          (0UL) /*!< Position of PTR field. */
#define TWIM_RXD_PTR_PTR_Msk          (0xFFFFFFFFUL << TWIM_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: TWIM_RXD_MAXCNT */
/* Description: Maximum number of bytes in receive buffer */

/* Bits 14..0 : Maximum number of bytes in receive buffer */
#define TWIM_RXD_MAXCNT_MAXCNT_Pos    (0UL) /*!< Position of MAXCNT field. */
#define TWIM_RXD_MAXCNT_MAXCNT_Msk                                                                 \
  (0x7FFFUL << TWIM_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: TWIM_RXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 14..0 : Number of bytes transferred in the last transaction. In case of NACK error, includes the NACK'ed byte. */
#define TWIM_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define TWIM_RXD_AMOUNT_AMOUNT_Msk                                                                 \
  (0x7FFFUL << TWIM_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: TWIM_RXD_LIST */
/* Description: EasyDMA list type */

/* Bits 2..0 : List type */
#define TWIM_RXD_LIST_LIST_Pos       (0UL) /*!< Position of LIST field. */
#define TWIM_RXD_LIST_LIST_Msk       (0x7UL << TWIM_RXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define TWIM_RXD_LIST_LIST_Disabled  (0UL)                             /*!< Disable EasyDMA list */
#define TWIM_RXD_LIST_LIST_ArrayList (1UL)                             /*!< Use array list */

/* Register: TWIM_TXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define TWIM_TXD_PTR_PTR_Pos         (0UL) /*!< Position of PTR field. */
#define TWIM_TXD_PTR_PTR_Msk         (0xFFFFFFFFUL << TWIM_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: TWIM_TXD_MAXCNT */
/* Description: Maximum number of bytes in transmit buffer */

/* Bits 14..0 : Maximum number of bytes in transmit buffer */
#define TWIM_TXD_MAXCNT_MAXCNT_Pos   (0UL) /*!< Position of MAXCNT field. */
#define TWIM_TXD_MAXCNT_MAXCNT_Msk                                                                 \
  (0x7FFFUL << TWIM_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: TWIM_TXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 14..0 : Number of bytes transferred in the last transaction. In case of NACK error, includes the NACK'ed byte. */
#define TWIM_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define TWIM_TXD_AMOUNT_AMOUNT_Msk                                                                 \
  (0x7FFFUL << TWIM_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: TWIM_TXD_LIST */
/* Description: EasyDMA list type */

/* Bits 2..0 : List type */
#define TWIM_TXD_LIST_LIST_Pos       (0UL) /*!< Position of LIST field. */
#define TWIM_TXD_LIST_LIST_Msk       (0x7UL << TWIM_TXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define TWIM_TXD_LIST_LIST_Disabled  (0UL)                             /*!< Disable EasyDMA list */
#define TWIM_TXD_LIST_LIST_ArrayList (1UL)                             /*!< Use array list */

/* Register: TWIM_ADDRESS */
/* Description: Address used in the TWI transfer */

/* Bits 6..0 : Address used in the TWI transfer */
#define TWIM_ADDRESS_ADDRESS_Pos     (0UL) /*!< Position of ADDRESS field. */
#define TWIM_ADDRESS_ADDRESS_Msk                                                                   \
  (0x7FUL << TWIM_ADDRESS_ADDRESS_Pos) /*!< Bit mask of ADDRESS field. */


/* Peripheral: TWIS */
/* Description: I2C compatible Two-Wire Slave Interface with EasyDMA 0 */

/* Register: TWIS_TASKS_STOP */
/* Description: Stop TWI transaction */

/* Bit 0 : Stop TWI transaction */
#define TWIS_TASKS_STOP_TASKS_STOP_Pos (0UL) /*!< Position of TASKS_STOP field. */
#define TWIS_TASKS_STOP_TASKS_STOP_Msk                                                             \
  (0x1UL << TWIS_TASKS_STOP_TASKS_STOP_Pos)        /*!< Bit mask of TASKS_STOP field. */
#define TWIS_TASKS_STOP_TASKS_STOP_Trigger   (1UL) /*!< Trigger task */

/* Register: TWIS_TASKS_SUSPEND */
/* Description: Suspend TWI transaction */

/* Bit 0 : Suspend TWI transaction */
#define TWIS_TASKS_SUSPEND_TASKS_SUSPEND_Pos (0UL) /*!< Position of TASKS_SUSPEND field. */
#define TWIS_TASKS_SUSPEND_TASKS_SUSPEND_Msk                                                       \
  (0x1UL << TWIS_TASKS_SUSPEND_TASKS_SUSPEND_Pos)      /*!< Bit mask of TASKS_SUSPEND field. */
#define TWIS_TASKS_SUSPEND_TASKS_SUSPEND_Trigger (1UL) /*!< Trigger task */

/* Register: TWIS_TASKS_RESUME */
/* Description: Resume TWI transaction */

/* Bit 0 : Resume TWI transaction */
#define TWIS_TASKS_RESUME_TASKS_RESUME_Pos       (0UL) /*!< Position of TASKS_RESUME field. */
#define TWIS_TASKS_RESUME_TASKS_RESUME_Msk                                                         \
  (0x1UL << TWIS_TASKS_RESUME_TASKS_RESUME_Pos)        /*!< Bit mask of TASKS_RESUME field. */
#define TWIS_TASKS_RESUME_TASKS_RESUME_Trigger   (1UL) /*!< Trigger task */

/* Register: TWIS_TASKS_PREPARERX */
/* Description: Prepare the TWI slave to respond to a write command */

/* Bit 0 : Prepare the TWI slave to respond to a write command */
#define TWIS_TASKS_PREPARERX_TASKS_PREPARERX_Pos (0UL) /*!< Position of TASKS_PREPARERX field. */
#define TWIS_TASKS_PREPARERX_TASKS_PREPARERX_Msk                                                   \
  (0x1UL << TWIS_TASKS_PREPARERX_TASKS_PREPARERX_Pos) /*!< Bit mask of TASKS_PREPARERX field. */
#define TWIS_TASKS_PREPARERX_TASKS_PREPARERX_Trigger (1UL) /*!< Trigger task */

/* Register: TWIS_TASKS_PREPARETX */
/* Description: Prepare the TWI slave to respond to a read command */

/* Bit 0 : Prepare the TWI slave to respond to a read command */
#define TWIS_TASKS_PREPARETX_TASKS_PREPARETX_Pos     (0UL) /*!< Position of TASKS_PREPARETX field. */
#define TWIS_TASKS_PREPARETX_TASKS_PREPARETX_Msk                                                   \
  (0x1UL << TWIS_TASKS_PREPARETX_TASKS_PREPARETX_Pos) /*!< Bit mask of TASKS_PREPARETX field. */
#define TWIS_TASKS_PREPARETX_TASKS_PREPARETX_Trigger (1UL) /*!< Trigger task */

/* Register: TWIS_EVENTS_STOPPED */
/* Description: TWI stopped */

/* Bit 0 : TWI stopped */
#define TWIS_EVENTS_STOPPED_EVENTS_STOPPED_Pos       (0UL) /*!< Position of EVENTS_STOPPED field. */
#define TWIS_EVENTS_STOPPED_EVENTS_STOPPED_Msk                                                     \
  (0x1UL << TWIS_EVENTS_STOPPED_EVENTS_STOPPED_Pos) /*!< Bit mask of EVENTS_STOPPED field. */
#define TWIS_EVENTS_STOPPED_EVENTS_STOPPED_NotGenerated (0UL) /*!< Event not generated */
#define TWIS_EVENTS_STOPPED_EVENTS_STOPPED_Generated    (1UL) /*!< Event generated */

/* Register: TWIS_EVENTS_ERROR */
/* Description: TWI error */

/* Bit 0 : TWI error */
#define TWIS_EVENTS_ERROR_EVENTS_ERROR_Pos              (0UL) /*!< Position of EVENTS_ERROR field. */
#define TWIS_EVENTS_ERROR_EVENTS_ERROR_Msk                                                         \
  (0x1UL << TWIS_EVENTS_ERROR_EVENTS_ERROR_Pos)           /*!< Bit mask of EVENTS_ERROR field. */
#define TWIS_EVENTS_ERROR_EVENTS_ERROR_NotGenerated (0UL) /*!< Event not generated */
#define TWIS_EVENTS_ERROR_EVENTS_ERROR_Generated    (1UL) /*!< Event generated */

/* Register: TWIS_EVENTS_RXSTARTED */
/* Description: Receive sequence started */

/* Bit 0 : Receive sequence started */
#define TWIS_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Pos  (0UL) /*!< Position of EVENTS_RXSTARTED field. */
#define TWIS_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Msk                                                 \
  (0x1UL << TWIS_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Pos) /*!< Bit mask of EVENTS_RXSTARTED field. */
#define TWIS_EVENTS_RXSTARTED_EVENTS_RXSTARTED_NotGenerated (0UL) /*!< Event not generated */
#define TWIS_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Generated    (1UL) /*!< Event generated */

/* Register: TWIS_EVENTS_TXSTARTED */
/* Description: Transmit sequence started */

/* Bit 0 : Transmit sequence started */
#define TWIS_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Pos          (0UL) /*!< Position of EVENTS_TXSTARTED field. */
#define TWIS_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Msk                                                 \
  (0x1UL << TWIS_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Pos) /*!< Bit mask of EVENTS_TXSTARTED field. */
#define TWIS_EVENTS_TXSTARTED_EVENTS_TXSTARTED_NotGenerated (0UL) /*!< Event not generated */
#define TWIS_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Generated    (1UL) /*!< Event generated */

/* Register: TWIS_EVENTS_WRITE */
/* Description: Write command received */

/* Bit 0 : Write command received */
#define TWIS_EVENTS_WRITE_EVENTS_WRITE_Pos                  (0UL) /*!< Position of EVENTS_WRITE field. */
#define TWIS_EVENTS_WRITE_EVENTS_WRITE_Msk                                                         \
  (0x1UL << TWIS_EVENTS_WRITE_EVENTS_WRITE_Pos)           /*!< Bit mask of EVENTS_WRITE field. */
#define TWIS_EVENTS_WRITE_EVENTS_WRITE_NotGenerated (0UL) /*!< Event not generated */
#define TWIS_EVENTS_WRITE_EVENTS_WRITE_Generated    (1UL) /*!< Event generated */

/* Register: TWIS_EVENTS_READ */
/* Description: Read command received */

/* Bit 0 : Read command received */
#define TWIS_EVENTS_READ_EVENTS_READ_Pos            (0UL) /*!< Position of EVENTS_READ field. */
#define TWIS_EVENTS_READ_EVENTS_READ_Msk                                                           \
  (0x1UL << TWIS_EVENTS_READ_EVENTS_READ_Pos)           /*!< Bit mask of EVENTS_READ field. */
#define TWIS_EVENTS_READ_EVENTS_READ_NotGenerated (0UL) /*!< Event not generated */
#define TWIS_EVENTS_READ_EVENTS_READ_Generated    (1UL) /*!< Event generated */

/* Register: TWIS_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 14 : Shortcut between event READ and task SUSPEND */
#define TWIS_SHORTS_READ_SUSPEND_Pos              (14UL) /*!< Position of READ_SUSPEND field. */
#define TWIS_SHORTS_READ_SUSPEND_Msk                                                               \
  (0x1UL << TWIS_SHORTS_READ_SUSPEND_Pos)       /*!< Bit mask of READ_SUSPEND field. */
#define TWIS_SHORTS_READ_SUSPEND_Disabled (0UL) /*!< Disable shortcut */
#define TWIS_SHORTS_READ_SUSPEND_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 13 : Shortcut between event WRITE and task SUSPEND */
#define TWIS_SHORTS_WRITE_SUSPEND_Pos     (13UL) /*!< Position of WRITE_SUSPEND field. */
#define TWIS_SHORTS_WRITE_SUSPEND_Msk                                                              \
  (0x1UL << TWIS_SHORTS_WRITE_SUSPEND_Pos)       /*!< Bit mask of WRITE_SUSPEND field. */
#define TWIS_SHORTS_WRITE_SUSPEND_Disabled (0UL) /*!< Disable shortcut */
#define TWIS_SHORTS_WRITE_SUSPEND_Enabled  (1UL) /*!< Enable shortcut */

/* Register: TWIS_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 26 : Enable or disable interrupt for event READ */
#define TWIS_INTEN_READ_Pos                (26UL) /*!< Position of READ field. */
#define TWIS_INTEN_READ_Msk                (0x1UL << TWIS_INTEN_READ_Pos) /*!< Bit mask of READ field. */
#define TWIS_INTEN_READ_Disabled           (0UL)                          /*!< Disable */
#define TWIS_INTEN_READ_Enabled            (1UL)                          /*!< Enable */

/* Bit 25 : Enable or disable interrupt for event WRITE */
#define TWIS_INTEN_WRITE_Pos               (25UL) /*!< Position of WRITE field. */
#define TWIS_INTEN_WRITE_Msk               (0x1UL << TWIS_INTEN_WRITE_Pos) /*!< Bit mask of WRITE field. */
#define TWIS_INTEN_WRITE_Disabled          (0UL)                           /*!< Disable */
#define TWIS_INTEN_WRITE_Enabled           (1UL)                           /*!< Enable */

/* Bit 20 : Enable or disable interrupt for event TXSTARTED */
#define TWIS_INTEN_TXSTARTED_Pos           (20UL) /*!< Position of TXSTARTED field. */
#define TWIS_INTEN_TXSTARTED_Msk                                                                   \
  (0x1UL << TWIS_INTEN_TXSTARTED_Pos)       /*!< Bit mask of TXSTARTED field. */
#define TWIS_INTEN_TXSTARTED_Disabled (0UL) /*!< Disable */
#define TWIS_INTEN_TXSTARTED_Enabled  (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for event RXSTARTED */
#define TWIS_INTEN_RXSTARTED_Pos      (19UL) /*!< Position of RXSTARTED field. */
#define TWIS_INTEN_RXSTARTED_Msk                                                                   \
  (0x1UL << TWIS_INTEN_RXSTARTED_Pos)       /*!< Bit mask of RXSTARTED field. */
#define TWIS_INTEN_RXSTARTED_Disabled (0UL) /*!< Disable */
#define TWIS_INTEN_RXSTARTED_Enabled  (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for event ERROR */
#define TWIS_INTEN_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define TWIS_INTEN_ERROR_Msk          (0x1UL << TWIS_INTEN_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIS_INTEN_ERROR_Disabled     (0UL)                           /*!< Disable */
#define TWIS_INTEN_ERROR_Enabled      (1UL)                           /*!< Enable */

/* Bit 1 : Enable or disable interrupt for event STOPPED */
#define TWIS_INTEN_STOPPED_Pos        (1UL) /*!< Position of STOPPED field. */
#define TWIS_INTEN_STOPPED_Msk        (0x1UL << TWIS_INTEN_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWIS_INTEN_STOPPED_Disabled   (0UL)                             /*!< Disable */
#define TWIS_INTEN_STOPPED_Enabled    (1UL)                             /*!< Enable */

/* Register: TWIS_INTENSET */
/* Description: Enable interrupt */

/* Bit 26 : Write '1' to enable interrupt for event READ */
#define TWIS_INTENSET_READ_Pos        (26UL) /*!< Position of READ field. */
#define TWIS_INTENSET_READ_Msk        (0x1UL << TWIS_INTENSET_READ_Pos) /*!< Bit mask of READ field. */
#define TWIS_INTENSET_READ_Disabled   (0UL)                             /*!< Read: Disabled */
#define TWIS_INTENSET_READ_Enabled    (1UL)                             /*!< Read: Enabled */
#define TWIS_INTENSET_READ_Set        (1UL)                             /*!< Enable */

/* Bit 25 : Write '1' to enable interrupt for event WRITE */
#define TWIS_INTENSET_WRITE_Pos       (25UL) /*!< Position of WRITE field. */
#define TWIS_INTENSET_WRITE_Msk       (0x1UL << TWIS_INTENSET_WRITE_Pos) /*!< Bit mask of WRITE field. */
#define TWIS_INTENSET_WRITE_Disabled  (0UL)                              /*!< Read: Disabled */
#define TWIS_INTENSET_WRITE_Enabled   (1UL)                              /*!< Read: Enabled */
#define TWIS_INTENSET_WRITE_Set       (1UL)                              /*!< Enable */

/* Bit 20 : Write '1' to enable interrupt for event TXSTARTED */
#define TWIS_INTENSET_TXSTARTED_Pos   (20UL) /*!< Position of TXSTARTED field. */
#define TWIS_INTENSET_TXSTARTED_Msk                                                                \
  (0x1UL << TWIS_INTENSET_TXSTARTED_Pos)       /*!< Bit mask of TXSTARTED field. */
#define TWIS_INTENSET_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENSET_TXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIS_INTENSET_TXSTARTED_Set      (1UL) /*!< Enable */

/* Bit 19 : Write '1' to enable interrupt for event RXSTARTED */
#define TWIS_INTENSET_RXSTARTED_Pos      (19UL) /*!< Position of RXSTARTED field. */
#define TWIS_INTENSET_RXSTARTED_Msk                                                                \
  (0x1UL << TWIS_INTENSET_RXSTARTED_Pos)       /*!< Bit mask of RXSTARTED field. */
#define TWIS_INTENSET_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENSET_RXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIS_INTENSET_RXSTARTED_Set      (1UL) /*!< Enable */

/* Bit 9 : Write '1' to enable interrupt for event ERROR */
#define TWIS_INTENSET_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define TWIS_INTENSET_ERROR_Msk          (0x1UL << TWIS_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIS_INTENSET_ERROR_Disabled     (0UL)                              /*!< Read: Disabled */
#define TWIS_INTENSET_ERROR_Enabled      (1UL)                              /*!< Read: Enabled */
#define TWIS_INTENSET_ERROR_Set          (1UL)                              /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event STOPPED */
#define TWIS_INTENSET_STOPPED_Pos        (1UL) /*!< Position of STOPPED field. */
#define TWIS_INTENSET_STOPPED_Msk                                                                  \
  (0x1UL << TWIS_INTENSET_STOPPED_Pos)       /*!< Bit mask of STOPPED field. */
#define TWIS_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENSET_STOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIS_INTENSET_STOPPED_Set      (1UL) /*!< Enable */

/* Register: TWIS_INTENCLR */
/* Description: Disable interrupt */

/* Bit 26 : Write '1' to disable interrupt for event READ */
#define TWIS_INTENCLR_READ_Pos         (26UL) /*!< Position of READ field. */
#define TWIS_INTENCLR_READ_Msk         (0x1UL << TWIS_INTENCLR_READ_Pos) /*!< Bit mask of READ field. */
#define TWIS_INTENCLR_READ_Disabled    (0UL)                             /*!< Read: Disabled */
#define TWIS_INTENCLR_READ_Enabled     (1UL)                             /*!< Read: Enabled */
#define TWIS_INTENCLR_READ_Clear       (1UL)                             /*!< Disable */

/* Bit 25 : Write '1' to disable interrupt for event WRITE */
#define TWIS_INTENCLR_WRITE_Pos        (25UL) /*!< Position of WRITE field. */
#define TWIS_INTENCLR_WRITE_Msk        (0x1UL << TWIS_INTENCLR_WRITE_Pos) /*!< Bit mask of WRITE field. */
#define TWIS_INTENCLR_WRITE_Disabled   (0UL)                              /*!< Read: Disabled */
#define TWIS_INTENCLR_WRITE_Enabled    (1UL)                              /*!< Read: Enabled */
#define TWIS_INTENCLR_WRITE_Clear      (1UL)                              /*!< Disable */

/* Bit 20 : Write '1' to disable interrupt for event TXSTARTED */
#define TWIS_INTENCLR_TXSTARTED_Pos    (20UL) /*!< Position of TXSTARTED field. */
#define TWIS_INTENCLR_TXSTARTED_Msk                                                                \
  (0x1UL << TWIS_INTENCLR_TXSTARTED_Pos)       /*!< Bit mask of TXSTARTED field. */
#define TWIS_INTENCLR_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENCLR_TXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIS_INTENCLR_TXSTARTED_Clear    (1UL) /*!< Disable */

/* Bit 19 : Write '1' to disable interrupt for event RXSTARTED */
#define TWIS_INTENCLR_RXSTARTED_Pos      (19UL) /*!< Position of RXSTARTED field. */
#define TWIS_INTENCLR_RXSTARTED_Msk                                                                \
  (0x1UL << TWIS_INTENCLR_RXSTARTED_Pos)       /*!< Bit mask of RXSTARTED field. */
#define TWIS_INTENCLR_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENCLR_RXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIS_INTENCLR_RXSTARTED_Clear    (1UL) /*!< Disable */

/* Bit 9 : Write '1' to disable interrupt for event ERROR */
#define TWIS_INTENCLR_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define TWIS_INTENCLR_ERROR_Msk          (0x1UL << TWIS_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIS_INTENCLR_ERROR_Disabled     (0UL)                              /*!< Read: Disabled */
#define TWIS_INTENCLR_ERROR_Enabled      (1UL)                              /*!< Read: Enabled */
#define TWIS_INTENCLR_ERROR_Clear        (1UL)                              /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event STOPPED */
#define TWIS_INTENCLR_STOPPED_Pos        (1UL) /*!< Position of STOPPED field. */
#define TWIS_INTENCLR_STOPPED_Msk                                                                  \
  (0x1UL << TWIS_INTENCLR_STOPPED_Pos)       /*!< Bit mask of STOPPED field. */
#define TWIS_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENCLR_STOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define TWIS_INTENCLR_STOPPED_Clear    (1UL) /*!< Disable */

/* Register: TWIS_ERRORSRC */
/* Description: Error source */

/* Bit 3 : TX buffer over-read detected, and prevented */
#define TWIS_ERRORSRC_OVERREAD_Pos     (3UL) /*!< Position of OVERREAD field. */
#define TWIS_ERRORSRC_OVERREAD_Msk                                                                 \
  (0x1UL << TWIS_ERRORSRC_OVERREAD_Pos)          /*!< Bit mask of OVERREAD field. */
#define TWIS_ERRORSRC_OVERREAD_NotDetected (0UL) /*!< Error did not occur */
#define TWIS_ERRORSRC_OVERREAD_Detected    (1UL) /*!< Error occurred */

/* Bit 2 : NACK sent after receiving a data byte */
#define TWIS_ERRORSRC_DNACK_Pos            (2UL) /*!< Position of DNACK field. */
#define TWIS_ERRORSRC_DNACK_Msk            (0x1UL << TWIS_ERRORSRC_DNACK_Pos) /*!< Bit mask of DNACK field. */
#define TWIS_ERRORSRC_DNACK_NotReceived    (0UL) /*!< Error did not occur */
#define TWIS_ERRORSRC_DNACK_Received       (1UL) /*!< Error occurred */

/* Bit 0 : RX buffer overflow detected, and prevented */
#define TWIS_ERRORSRC_OVERFLOW_Pos         (0UL) /*!< Position of OVERFLOW field. */
#define TWIS_ERRORSRC_OVERFLOW_Msk                                                                 \
  (0x1UL << TWIS_ERRORSRC_OVERFLOW_Pos)          /*!< Bit mask of OVERFLOW field. */
#define TWIS_ERRORSRC_OVERFLOW_NotDetected (0UL) /*!< Error did not occur */
#define TWIS_ERRORSRC_OVERFLOW_Detected    (1UL) /*!< Error occurred */

/* Register: TWIS_MATCH */
/* Description: Status register indicating which address had a match */

/* Bit 0 : Which of the addresses in {ADDRESS} matched the incoming address */
#define TWIS_MATCH_MATCH_Pos               (0UL) /*!< Position of MATCH field. */
#define TWIS_MATCH_MATCH_Msk               (0x1UL << TWIS_MATCH_MATCH_Pos) /*!< Bit mask of MATCH field. */

/* Register: TWIS_ENABLE */
/* Description: Enable TWIS */

/* Bits 3..0 : Enable or disable TWIS */
#define TWIS_ENABLE_ENABLE_Pos             (0UL) /*!< Position of ENABLE field. */
#define TWIS_ENABLE_ENABLE_Msk             (0xFUL << TWIS_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define TWIS_ENABLE_ENABLE_Disabled        (0UL)                             /*!< Disable TWIS */
#define TWIS_ENABLE_ENABLE_Enabled         (9UL)                             /*!< Enable TWIS */

/* Register: TWIS_PSEL_SCL */
/* Description: Pin select for SCL signal */

/* Bit 31 : Connection */
#define TWIS_PSEL_SCL_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define TWIS_PSEL_SCL_CONNECT_Msk                                                                  \
  (0x1UL << TWIS_PSEL_SCL_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define TWIS_PSEL_SCL_CONNECT_Connected    (0UL) /*!< Connect */
#define TWIS_PSEL_SCL_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define TWIS_PSEL_SCL_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define TWIS_PSEL_SCL_PIN_Msk              (0x1FUL << TWIS_PSEL_SCL_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWIS_PSEL_SDA */
/* Description: Pin select for SDA signal */

/* Bit 31 : Connection */
#define TWIS_PSEL_SDA_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define TWIS_PSEL_SDA_CONNECT_Msk                                                                  \
  (0x1UL << TWIS_PSEL_SDA_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define TWIS_PSEL_SDA_CONNECT_Connected    (0UL) /*!< Connect */
#define TWIS_PSEL_SDA_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define TWIS_PSEL_SDA_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define TWIS_PSEL_SDA_PIN_Msk              (0x1FUL << TWIS_PSEL_SDA_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWIS_RXD_PTR */
/* Description: RXD Data pointer */

/* Bits 31..0 : RXD Data pointer */
#define TWIS_RXD_PTR_PTR_Pos               (0UL) /*!< Position of PTR field. */
#define TWIS_RXD_PTR_PTR_Msk               (0xFFFFFFFFUL << TWIS_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: TWIS_RXD_MAXCNT */
/* Description: Maximum number of bytes in RXD buffer */

/* Bits 14..0 : Maximum number of bytes in RXD buffer */
#define TWIS_RXD_MAXCNT_MAXCNT_Pos         (0UL) /*!< Position of MAXCNT field. */
#define TWIS_RXD_MAXCNT_MAXCNT_Msk                                                                 \
  (0x7FFFUL << TWIS_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: TWIS_RXD_AMOUNT */
/* Description: Number of bytes transferred in the last RXD transaction */

/* Bits 14..0 : Number of bytes transferred in the last RXD transaction */
#define TWIS_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define TWIS_RXD_AMOUNT_AMOUNT_Msk                                                                 \
  (0x7FFFUL << TWIS_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: TWIS_RXD_LIST */
/* Description: EasyDMA list type */

/* Bits 1..0 : List type */
#define TWIS_RXD_LIST_LIST_Pos       (0UL) /*!< Position of LIST field. */
#define TWIS_RXD_LIST_LIST_Msk       (0x3UL << TWIS_RXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define TWIS_RXD_LIST_LIST_Disabled  (0UL)                             /*!< Disable EasyDMA list */
#define TWIS_RXD_LIST_LIST_ArrayList (1UL)                             /*!< Use array list */

/* Register: TWIS_TXD_PTR */
/* Description: TXD Data pointer */

/* Bits 31..0 : TXD Data pointer */
#define TWIS_TXD_PTR_PTR_Pos         (0UL) /*!< Position of PTR field. */
#define TWIS_TXD_PTR_PTR_Msk         (0xFFFFFFFFUL << TWIS_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: TWIS_TXD_MAXCNT */
/* Description: Maximum number of bytes in TXD buffer */

/* Bits 14..0 : Maximum number of bytes in TXD buffer */
#define TWIS_TXD_MAXCNT_MAXCNT_Pos   (0UL) /*!< Position of MAXCNT field. */
#define TWIS_TXD_MAXCNT_MAXCNT_Msk                                                                 \
  (0x7FFFUL << TWIS_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: TWIS_TXD_AMOUNT */
/* Description: Number of bytes transferred in the last TXD transaction */

/* Bits 14..0 : Number of bytes transferred in the last TXD transaction */
#define TWIS_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define TWIS_TXD_AMOUNT_AMOUNT_Msk                                                                 \
  (0x7FFFUL << TWIS_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: TWIS_TXD_LIST */
/* Description: EasyDMA list type */

/* Bits 1..0 : List type */
#define TWIS_TXD_LIST_LIST_Pos       (0UL) /*!< Position of LIST field. */
#define TWIS_TXD_LIST_LIST_Msk       (0x3UL << TWIS_TXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define TWIS_TXD_LIST_LIST_Disabled  (0UL)                             /*!< Disable EasyDMA list */
#define TWIS_TXD_LIST_LIST_ArrayList (1UL)                             /*!< Use array list */

/* Register: TWIS_ADDRESS */
/* Description: Description collection: TWI slave address n */

/* Bits 6..0 : TWI slave address */
#define TWIS_ADDRESS_ADDRESS_Pos     (0UL) /*!< Position of ADDRESS field. */
#define TWIS_ADDRESS_ADDRESS_Msk                                                                   \
  (0x7FUL << TWIS_ADDRESS_ADDRESS_Pos) /*!< Bit mask of ADDRESS field. */

/* Register: TWIS_CONFIG */
/* Description: Configuration register for the address match mechanism */

/* Bit 1 : Enable or disable address matching on ADDRESS[1] */
#define TWIS_CONFIG_ADDRESS1_Pos (1UL) /*!< Position of ADDRESS1 field. */
#define TWIS_CONFIG_ADDRESS1_Msk                                                                   \
  (0x1UL << TWIS_CONFIG_ADDRESS1_Pos)       /*!< Bit mask of ADDRESS1 field. */
#define TWIS_CONFIG_ADDRESS1_Disabled (0UL) /*!< Disabled */
#define TWIS_CONFIG_ADDRESS1_Enabled  (1UL) /*!< Enabled */

/* Bit 0 : Enable or disable address matching on ADDRESS[0] */
#define TWIS_CONFIG_ADDRESS0_Pos      (0UL) /*!< Position of ADDRESS0 field. */
#define TWIS_CONFIG_ADDRESS0_Msk                                                                   \
  (0x1UL << TWIS_CONFIG_ADDRESS0_Pos)              /*!< Bit mask of ADDRESS0 field. */
#define TWIS_CONFIG_ADDRESS0_Disabled        (0UL) /*!< Disabled */
#define TWIS_CONFIG_ADDRESS0_Enabled         (1UL) /*!< Enabled */

/* Register: TWIS_ORC */
/* Description: Over-read character. Character sent out in case of an over-read of the transmit buffer. */

/* Bits 7..0 : Over-read character. Character sent out in case of an over-read of the transmit buffer. */
#define TWIS_ORC_ORC_Pos                     (0UL) /*!< Position of ORC field. */
#define TWIS_ORC_ORC_Msk                     (0xFFUL << TWIS_ORC_ORC_Pos) /*!< Bit mask of ORC field. */


/* Peripheral: UART */
/* Description: Universal Asynchronous Receiver/Transmitter */

/* Register: UART_TASKS_STARTRX */
/* Description: Start UART receiver */

/* Bit 0 : Start UART receiver */
#define UART_TASKS_STARTRX_TASKS_STARTRX_Pos (0UL) /*!< Position of TASKS_STARTRX field. */
#define UART_TASKS_STARTRX_TASKS_STARTRX_Msk                                                       \
  (0x1UL << UART_TASKS_STARTRX_TASKS_STARTRX_Pos)      /*!< Bit mask of TASKS_STARTRX field. */
#define UART_TASKS_STARTRX_TASKS_STARTRX_Trigger (1UL) /*!< Trigger task */

/* Register: UART_TASKS_STOPRX */
/* Description: Stop UART receiver */

/* Bit 0 : Stop UART receiver */
#define UART_TASKS_STOPRX_TASKS_STOPRX_Pos       (0UL) /*!< Position of TASKS_STOPRX field. */
#define UART_TASKS_STOPRX_TASKS_STOPRX_Msk                                                         \
  (0x1UL << UART_TASKS_STOPRX_TASKS_STOPRX_Pos)      /*!< Bit mask of TASKS_STOPRX field. */
#define UART_TASKS_STOPRX_TASKS_STOPRX_Trigger (1UL) /*!< Trigger task */

/* Register: UART_TASKS_STARTTX */
/* Description: Start UART transmitter */

/* Bit 0 : Start UART transmitter */
#define UART_TASKS_STARTTX_TASKS_STARTTX_Pos   (0UL) /*!< Position of TASKS_STARTTX field. */
#define UART_TASKS_STARTTX_TASKS_STARTTX_Msk                                                       \
  (0x1UL << UART_TASKS_STARTTX_TASKS_STARTTX_Pos)      /*!< Bit mask of TASKS_STARTTX field. */
#define UART_TASKS_STARTTX_TASKS_STARTTX_Trigger (1UL) /*!< Trigger task */

/* Register: UART_TASKS_STOPTX */
/* Description: Stop UART transmitter */

/* Bit 0 : Stop UART transmitter */
#define UART_TASKS_STOPTX_TASKS_STOPTX_Pos       (0UL) /*!< Position of TASKS_STOPTX field. */
#define UART_TASKS_STOPTX_TASKS_STOPTX_Msk                                                         \
  (0x1UL << UART_TASKS_STOPTX_TASKS_STOPTX_Pos)      /*!< Bit mask of TASKS_STOPTX field. */
#define UART_TASKS_STOPTX_TASKS_STOPTX_Trigger (1UL) /*!< Trigger task */

/* Register: UART_TASKS_SUSPEND */
/* Description: Suspend UART */

/* Bit 0 : Suspend UART */
#define UART_TASKS_SUSPEND_TASKS_SUSPEND_Pos   (0UL) /*!< Position of TASKS_SUSPEND field. */
#define UART_TASKS_SUSPEND_TASKS_SUSPEND_Msk                                                       \
  (0x1UL << UART_TASKS_SUSPEND_TASKS_SUSPEND_Pos)      /*!< Bit mask of TASKS_SUSPEND field. */
#define UART_TASKS_SUSPEND_TASKS_SUSPEND_Trigger (1UL) /*!< Trigger task */

/* Register: UART_EVENTS_CTS */
/* Description: CTS is activated (set low). Clear To Send. */

/* Bit 0 : CTS is activated (set low). Clear To Send. */
#define UART_EVENTS_CTS_EVENTS_CTS_Pos           (0UL) /*!< Position of EVENTS_CTS field. */
#define UART_EVENTS_CTS_EVENTS_CTS_Msk                                                             \
  (0x1UL << UART_EVENTS_CTS_EVENTS_CTS_Pos)           /*!< Bit mask of EVENTS_CTS field. */
#define UART_EVENTS_CTS_EVENTS_CTS_NotGenerated (0UL) /*!< Event not generated */
#define UART_EVENTS_CTS_EVENTS_CTS_Generated    (1UL) /*!< Event generated */

/* Register: UART_EVENTS_NCTS */
/* Description: CTS is deactivated (set high). Not Clear To Send. */

/* Bit 0 : CTS is deactivated (set high). Not Clear To Send. */
#define UART_EVENTS_NCTS_EVENTS_NCTS_Pos        (0UL) /*!< Position of EVENTS_NCTS field. */
#define UART_EVENTS_NCTS_EVENTS_NCTS_Msk                                                           \
  (0x1UL << UART_EVENTS_NCTS_EVENTS_NCTS_Pos)           /*!< Bit mask of EVENTS_NCTS field. */
#define UART_EVENTS_NCTS_EVENTS_NCTS_NotGenerated (0UL) /*!< Event not generated */
#define UART_EVENTS_NCTS_EVENTS_NCTS_Generated    (1UL) /*!< Event generated */

/* Register: UART_EVENTS_RXDRDY */
/* Description: Data received in RXD */

/* Bit 0 : Data received in RXD */
#define UART_EVENTS_RXDRDY_EVENTS_RXDRDY_Pos      (0UL) /*!< Position of EVENTS_RXDRDY field. */
#define UART_EVENTS_RXDRDY_EVENTS_RXDRDY_Msk                                                       \
  (0x1UL << UART_EVENTS_RXDRDY_EVENTS_RXDRDY_Pos)           /*!< Bit mask of EVENTS_RXDRDY field. */
#define UART_EVENTS_RXDRDY_EVENTS_RXDRDY_NotGenerated (0UL) /*!< Event not generated */
#define UART_EVENTS_RXDRDY_EVENTS_RXDRDY_Generated    (1UL) /*!< Event generated */

/* Register: UART_EVENTS_TXDRDY */
/* Description: Data sent from TXD */

/* Bit 0 : Data sent from TXD */
#define UART_EVENTS_TXDRDY_EVENTS_TXDRDY_Pos          (0UL) /*!< Position of EVENTS_TXDRDY field. */
#define UART_EVENTS_TXDRDY_EVENTS_TXDRDY_Msk                                                       \
  (0x1UL << UART_EVENTS_TXDRDY_EVENTS_TXDRDY_Pos)           /*!< Bit mask of EVENTS_TXDRDY field. */
#define UART_EVENTS_TXDRDY_EVENTS_TXDRDY_NotGenerated (0UL) /*!< Event not generated */
#define UART_EVENTS_TXDRDY_EVENTS_TXDRDY_Generated    (1UL) /*!< Event generated */

/* Register: UART_EVENTS_ERROR */
/* Description: Error detected */

/* Bit 0 : Error detected */
#define UART_EVENTS_ERROR_EVENTS_ERROR_Pos            (0UL) /*!< Position of EVENTS_ERROR field. */
#define UART_EVENTS_ERROR_EVENTS_ERROR_Msk                                                         \
  (0x1UL << UART_EVENTS_ERROR_EVENTS_ERROR_Pos)           /*!< Bit mask of EVENTS_ERROR field. */
#define UART_EVENTS_ERROR_EVENTS_ERROR_NotGenerated (0UL) /*!< Event not generated */
#define UART_EVENTS_ERROR_EVENTS_ERROR_Generated    (1UL) /*!< Event generated */

/* Register: UART_EVENTS_RXTO */
/* Description: Receiver timeout */

/* Bit 0 : Receiver timeout */
#define UART_EVENTS_RXTO_EVENTS_RXTO_Pos            (0UL) /*!< Position of EVENTS_RXTO field. */
#define UART_EVENTS_RXTO_EVENTS_RXTO_Msk                                                           \
  (0x1UL << UART_EVENTS_RXTO_EVENTS_RXTO_Pos)           /*!< Bit mask of EVENTS_RXTO field. */
#define UART_EVENTS_RXTO_EVENTS_RXTO_NotGenerated (0UL) /*!< Event not generated */
#define UART_EVENTS_RXTO_EVENTS_RXTO_Generated    (1UL) /*!< Event generated */

/* Register: UART_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 4 : Shortcut between event NCTS and task STOPRX */
#define UART_SHORTS_NCTS_STOPRX_Pos               (4UL) /*!< Position of NCTS_STOPRX field. */
#define UART_SHORTS_NCTS_STOPRX_Msk                                                                \
  (0x1UL << UART_SHORTS_NCTS_STOPRX_Pos)       /*!< Bit mask of NCTS_STOPRX field. */
#define UART_SHORTS_NCTS_STOPRX_Disabled (0UL) /*!< Disable shortcut */
#define UART_SHORTS_NCTS_STOPRX_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between event CTS and task STARTRX */
#define UART_SHORTS_CTS_STARTRX_Pos      (3UL) /*!< Position of CTS_STARTRX field. */
#define UART_SHORTS_CTS_STARTRX_Msk                                                                \
  (0x1UL << UART_SHORTS_CTS_STARTRX_Pos)       /*!< Bit mask of CTS_STARTRX field. */
#define UART_SHORTS_CTS_STARTRX_Disabled (0UL) /*!< Disable shortcut */
#define UART_SHORTS_CTS_STARTRX_Enabled  (1UL) /*!< Enable shortcut */

/* Register: UART_INTENSET */
/* Description: Enable interrupt */

/* Bit 17 : Write '1' to enable interrupt for event RXTO */
#define UART_INTENSET_RXTO_Pos           (17UL) /*!< Position of RXTO field. */
#define UART_INTENSET_RXTO_Msk           (0x1UL << UART_INTENSET_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UART_INTENSET_RXTO_Disabled      (0UL)                             /*!< Read: Disabled */
#define UART_INTENSET_RXTO_Enabled       (1UL)                             /*!< Read: Enabled */
#define UART_INTENSET_RXTO_Set           (1UL)                             /*!< Enable */

/* Bit 9 : Write '1' to enable interrupt for event ERROR */
#define UART_INTENSET_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define UART_INTENSET_ERROR_Msk          (0x1UL << UART_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define UART_INTENSET_ERROR_Disabled     (0UL)                              /*!< Read: Disabled */
#define UART_INTENSET_ERROR_Enabled      (1UL)                              /*!< Read: Enabled */
#define UART_INTENSET_ERROR_Set          (1UL)                              /*!< Enable */

/* Bit 7 : Write '1' to enable interrupt for event TXDRDY */
#define UART_INTENSET_TXDRDY_Pos         (7UL) /*!< Position of TXDRDY field. */
#define UART_INTENSET_TXDRDY_Msk                                                                   \
  (0x1UL << UART_INTENSET_TXDRDY_Pos)       /*!< Bit mask of TXDRDY field. */
#define UART_INTENSET_TXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENSET_TXDRDY_Enabled  (1UL) /*!< Read: Enabled */
#define UART_INTENSET_TXDRDY_Set      (1UL) /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event RXDRDY */
#define UART_INTENSET_RXDRDY_Pos      (2UL) /*!< Position of RXDRDY field. */
#define UART_INTENSET_RXDRDY_Msk                                                                   \
  (0x1UL << UART_INTENSET_RXDRDY_Pos)       /*!< Bit mask of RXDRDY field. */
#define UART_INTENSET_RXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENSET_RXDRDY_Enabled  (1UL) /*!< Read: Enabled */
#define UART_INTENSET_RXDRDY_Set      (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event NCTS */
#define UART_INTENSET_NCTS_Pos        (1UL) /*!< Position of NCTS field. */
#define UART_INTENSET_NCTS_Msk        (0x1UL << UART_INTENSET_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UART_INTENSET_NCTS_Disabled   (0UL)                             /*!< Read: Disabled */
#define UART_INTENSET_NCTS_Enabled    (1UL)                             /*!< Read: Enabled */
#define UART_INTENSET_NCTS_Set        (1UL)                             /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event CTS */
#define UART_INTENSET_CTS_Pos         (0UL) /*!< Position of CTS field. */
#define UART_INTENSET_CTS_Msk         (0x1UL << UART_INTENSET_CTS_Pos) /*!< Bit mask of CTS field. */
#define UART_INTENSET_CTS_Disabled    (0UL)                            /*!< Read: Disabled */
#define UART_INTENSET_CTS_Enabled     (1UL)                            /*!< Read: Enabled */
#define UART_INTENSET_CTS_Set         (1UL)                            /*!< Enable */

/* Register: UART_INTENCLR */
/* Description: Disable interrupt */

/* Bit 17 : Write '1' to disable interrupt for event RXTO */
#define UART_INTENCLR_RXTO_Pos        (17UL) /*!< Position of RXTO field. */
#define UART_INTENCLR_RXTO_Msk        (0x1UL << UART_INTENCLR_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UART_INTENCLR_RXTO_Disabled   (0UL)                             /*!< Read: Disabled */
#define UART_INTENCLR_RXTO_Enabled    (1UL)                             /*!< Read: Enabled */
#define UART_INTENCLR_RXTO_Clear      (1UL)                             /*!< Disable */

/* Bit 9 : Write '1' to disable interrupt for event ERROR */
#define UART_INTENCLR_ERROR_Pos       (9UL) /*!< Position of ERROR field. */
#define UART_INTENCLR_ERROR_Msk       (0x1UL << UART_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define UART_INTENCLR_ERROR_Disabled  (0UL)                              /*!< Read: Disabled */
#define UART_INTENCLR_ERROR_Enabled   (1UL)                              /*!< Read: Enabled */
#define UART_INTENCLR_ERROR_Clear     (1UL)                              /*!< Disable */

/* Bit 7 : Write '1' to disable interrupt for event TXDRDY */
#define UART_INTENCLR_TXDRDY_Pos      (7UL) /*!< Position of TXDRDY field. */
#define UART_INTENCLR_TXDRDY_Msk                                                                   \
  (0x1UL << UART_INTENCLR_TXDRDY_Pos)       /*!< Bit mask of TXDRDY field. */
#define UART_INTENCLR_TXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENCLR_TXDRDY_Enabled  (1UL) /*!< Read: Enabled */
#define UART_INTENCLR_TXDRDY_Clear    (1UL) /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event RXDRDY */
#define UART_INTENCLR_RXDRDY_Pos      (2UL) /*!< Position of RXDRDY field. */
#define UART_INTENCLR_RXDRDY_Msk                                                                   \
  (0x1UL << UART_INTENCLR_RXDRDY_Pos)        /*!< Bit mask of RXDRDY field. */
#define UART_INTENCLR_RXDRDY_Disabled  (0UL) /*!< Read: Disabled */
#define UART_INTENCLR_RXDRDY_Enabled   (1UL) /*!< Read: Enabled */
#define UART_INTENCLR_RXDRDY_Clear     (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event NCTS */
#define UART_INTENCLR_NCTS_Pos         (1UL) /*!< Position of NCTS field. */
#define UART_INTENCLR_NCTS_Msk         (0x1UL << UART_INTENCLR_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UART_INTENCLR_NCTS_Disabled    (0UL)                             /*!< Read: Disabled */
#define UART_INTENCLR_NCTS_Enabled     (1UL)                             /*!< Read: Enabled */
#define UART_INTENCLR_NCTS_Clear       (1UL)                             /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event CTS */
#define UART_INTENCLR_CTS_Pos          (0UL) /*!< Position of CTS field. */
#define UART_INTENCLR_CTS_Msk          (0x1UL << UART_INTENCLR_CTS_Pos) /*!< Bit mask of CTS field. */
#define UART_INTENCLR_CTS_Disabled     (0UL)                            /*!< Read: Disabled */
#define UART_INTENCLR_CTS_Enabled      (1UL)                            /*!< Read: Enabled */
#define UART_INTENCLR_CTS_Clear        (1UL)                            /*!< Disable */

/* Register: UART_ERRORSRC */
/* Description: Error source */

/* Bit 3 : Break condition */
#define UART_ERRORSRC_BREAK_Pos        (3UL) /*!< Position of BREAK field. */
#define UART_ERRORSRC_BREAK_Msk        (0x1UL << UART_ERRORSRC_BREAK_Pos) /*!< Bit mask of BREAK field. */
#define UART_ERRORSRC_BREAK_NotPresent (0UL) /*!< Read: error not present */
#define UART_ERRORSRC_BREAK_Present    (1UL) /*!< Read: error present */

/* Bit 2 : Framing error occurred */
#define UART_ERRORSRC_FRAMING_Pos      (2UL) /*!< Position of FRAMING field. */
#define UART_ERRORSRC_FRAMING_Msk                                                                  \
  (0x1UL << UART_ERRORSRC_FRAMING_Pos)         /*!< Bit mask of FRAMING field. */
#define UART_ERRORSRC_FRAMING_NotPresent (0UL) /*!< Read: error not present */
#define UART_ERRORSRC_FRAMING_Present    (1UL) /*!< Read: error present */

/* Bit 1 : Parity error */
#define UART_ERRORSRC_PARITY_Pos         (1UL) /*!< Position of PARITY field. */
#define UART_ERRORSRC_PARITY_Msk                                                                   \
  (0x1UL << UART_ERRORSRC_PARITY_Pos)         /*!< Bit mask of PARITY field. */
#define UART_ERRORSRC_PARITY_NotPresent (0UL) /*!< Read: error not present */
#define UART_ERRORSRC_PARITY_Present    (1UL) /*!< Read: error present */

/* Bit 0 : Overrun error */
#define UART_ERRORSRC_OVERRUN_Pos       (0UL) /*!< Position of OVERRUN field. */
#define UART_ERRORSRC_OVERRUN_Msk                                                                  \
  (0x1UL << UART_ERRORSRC_OVERRUN_Pos)         /*!< Bit mask of OVERRUN field. */
#define UART_ERRORSRC_OVERRUN_NotPresent (0UL) /*!< Read: error not present */
#define UART_ERRORSRC_OVERRUN_Present    (1UL) /*!< Read: error present */

/* Register: UART_ENABLE */
/* Description: Enable UART */

/* Bits 3..0 : Enable or disable UART */
#define UART_ENABLE_ENABLE_Pos           (0UL) /*!< Position of ENABLE field. */
#define UART_ENABLE_ENABLE_Msk           (0xFUL << UART_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define UART_ENABLE_ENABLE_Disabled      (0UL)                             /*!< Disable UART */
#define UART_ENABLE_ENABLE_Enabled       (4UL)                             /*!< Enable UART */

/* Register: UART_PSEL_RTS */
/* Description: Pin select for RTS */

/* Bit 31 : Connection */
#define UART_PSEL_RTS_CONNECT_Pos        (31UL) /*!< Position of CONNECT field. */
#define UART_PSEL_RTS_CONNECT_Msk                                                                  \
  (0x1UL << UART_PSEL_RTS_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define UART_PSEL_RTS_CONNECT_Connected    (0UL) /*!< Connect */
#define UART_PSEL_RTS_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define UART_PSEL_RTS_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define UART_PSEL_RTS_PIN_Msk              (0x1FUL << UART_PSEL_RTS_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UART_PSEL_TXD */
/* Description: Pin select for TXD */

/* Bit 31 : Connection */
#define UART_PSEL_TXD_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define UART_PSEL_TXD_CONNECT_Msk                                                                  \
  (0x1UL << UART_PSEL_TXD_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define UART_PSEL_TXD_CONNECT_Connected    (0UL) /*!< Connect */
#define UART_PSEL_TXD_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define UART_PSEL_TXD_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define UART_PSEL_TXD_PIN_Msk              (0x1FUL << UART_PSEL_TXD_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UART_PSEL_CTS */
/* Description: Pin select for CTS */

/* Bit 31 : Connection */
#define UART_PSEL_CTS_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define UART_PSEL_CTS_CONNECT_Msk                                                                  \
  (0x1UL << UART_PSEL_CTS_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define UART_PSEL_CTS_CONNECT_Connected    (0UL) /*!< Connect */
#define UART_PSEL_CTS_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define UART_PSEL_CTS_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define UART_PSEL_CTS_PIN_Msk              (0x1FUL << UART_PSEL_CTS_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UART_PSEL_RXD */
/* Description: Pin select for RXD */

/* Bit 31 : Connection */
#define UART_PSEL_RXD_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define UART_PSEL_RXD_CONNECT_Msk                                                                  \
  (0x1UL << UART_PSEL_RXD_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define UART_PSEL_RXD_CONNECT_Connected    (0UL) /*!< Connect */
#define UART_PSEL_RXD_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define UART_PSEL_RXD_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define UART_PSEL_RXD_PIN_Msk              (0x1FUL << UART_PSEL_RXD_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UART_RXD */
/* Description: RXD register */

/* Bits 7..0 : RX data received in previous transfers, double buffered */
#define UART_RXD_RXD_Pos                   (0UL) /*!< Position of RXD field. */
#define UART_RXD_RXD_Msk                   (0xFFUL << UART_RXD_RXD_Pos) /*!< Bit mask of RXD field. */

/* Register: UART_TXD */
/* Description: TXD register */

/* Bits 7..0 : TX data to be transferred */
#define UART_TXD_TXD_Pos                   (0UL) /*!< Position of TXD field. */
#define UART_TXD_TXD_Msk                   (0xFFUL << UART_TXD_TXD_Pos) /*!< Bit mask of TXD field. */

/* Register: UART_BAUDRATE */
/* Description: Baud rate. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : Baud rate */
#define UART_BAUDRATE_BAUDRATE_Pos         (0UL) /*!< Position of BAUDRATE field. */
#define UART_BAUDRATE_BAUDRATE_Msk                                                                 \
  (0xFFFFFFFFUL << UART_BAUDRATE_BAUDRATE_Pos)           /*!< Bit mask of BAUDRATE field. */
#define UART_BAUDRATE_BAUDRATE_Baud1200   (0x0004F000UL) /*!< 1200 baud (actual rate: 1205) */
#define UART_BAUDRATE_BAUDRATE_Baud2400   (0x0009D000UL) /*!< 2400 baud (actual rate: 2396) */
#define UART_BAUDRATE_BAUDRATE_Baud4800   (0x0013B000UL) /*!< 4800 baud (actual rate: 4808) */
#define UART_BAUDRATE_BAUDRATE_Baud9600   (0x00275000UL) /*!< 9600 baud (actual rate: 9598) */
#define UART_BAUDRATE_BAUDRATE_Baud14400  (0x003B0000UL) /*!< 14400 baud (actual rate: 14414) */
#define UART_BAUDRATE_BAUDRATE_Baud19200  (0x004EA000UL) /*!< 19200 baud (actual rate: 19208) */
#define UART_BAUDRATE_BAUDRATE_Baud28800  (0x0075F000UL) /*!< 28800 baud (actual rate: 28829) */
#define UART_BAUDRATE_BAUDRATE_Baud31250  (0x00800000UL) /*!< 31250 baud */
#define UART_BAUDRATE_BAUDRATE_Baud38400  (0x009D5000UL) /*!< 38400 baud (actual rate: 38462) */
#define UART_BAUDRATE_BAUDRATE_Baud56000  (0x00E50000UL) /*!< 56000 baud (actual rate: 55944) */
#define UART_BAUDRATE_BAUDRATE_Baud57600  (0x00EBF000UL) /*!< 57600 baud (actual rate: 57762) */
#define UART_BAUDRATE_BAUDRATE_Baud76800  (0x013A9000UL) /*!< 76800 baud (actual rate: 76923) */
#define UART_BAUDRATE_BAUDRATE_Baud115200 (0x01D7E000UL) /*!< 115200 baud (actual rate: 115942) */
#define UART_BAUDRATE_BAUDRATE_Baud230400 (0x03AFB000UL) /*!< 230400 baud (actual rate: 231884) */
#define UART_BAUDRATE_BAUDRATE_Baud250000 (0x04000000UL) /*!< 250000 baud */
#define UART_BAUDRATE_BAUDRATE_Baud460800 (0x075F7000UL) /*!< 460800 baud (actual rate: 470588) */
#define UART_BAUDRATE_BAUDRATE_Baud921600 (0x0EBED000UL) /*!< 921600 baud (actual rate: 941176) */
#define UART_BAUDRATE_BAUDRATE_Baud1M     (0x10000000UL) /*!< 1Mega baud */

/* Register: UART_CONFIG */
/* Description: Configuration of parity and hardware flow control */

/* Bit 8 : Even or odd parity type */
#define UART_CONFIG_PARITYTYPE_Pos        (8UL) /*!< Position of PARITYTYPE field. */
#define UART_CONFIG_PARITYTYPE_Msk                                                                 \
  (0x1UL << UART_CONFIG_PARITYTYPE_Pos)             /*!< Bit mask of PARITYTYPE field. */
#define UART_CONFIG_PARITYTYPE_Even           (0UL) /*!< Even parity */
#define UART_CONFIG_PARITYTYPE_Odd            (1UL) /*!< Odd parity */

/* Bit 4 : Stop bits */
#define UART_CONFIG_STOP_Pos                  (4UL) /*!< Position of STOP field. */
#define UART_CONFIG_STOP_Msk                  (0x1UL << UART_CONFIG_STOP_Pos) /*!< Bit mask of STOP field. */
#define UART_CONFIG_STOP_One                  (0UL)                           /*!< One stop bit */
#define UART_CONFIG_STOP_Two                  (1UL)                           /*!< Two stop bits */

/* Bits 3..1 : Parity */
#define UART_CONFIG_PARITY_Pos                (1UL) /*!< Position of PARITY field. */
#define UART_CONFIG_PARITY_Msk                (0x7UL << UART_CONFIG_PARITY_Pos) /*!< Bit mask of PARITY field. */
#define UART_CONFIG_PARITY_Excluded           (0x0UL) /*!< Exclude parity bit */
#define UART_CONFIG_PARITY_Included           (0x7UL) /*!< Include parity bit */

/* Bit 0 : Hardware flow control */
#define UART_CONFIG_HWFC_Pos                  (0UL) /*!< Position of HWFC field. */
#define UART_CONFIG_HWFC_Msk                  (0x1UL << UART_CONFIG_HWFC_Pos) /*!< Bit mask of HWFC field. */
#define UART_CONFIG_HWFC_Disabled             (0UL)                           /*!< Disabled */
#define UART_CONFIG_HWFC_Enabled              (1UL)                           /*!< Enabled */


/* Peripheral: UARTE */
/* Description: UART with EasyDMA */

/* Register: UARTE_TASKS_STARTRX */
/* Description: Start UART receiver */

/* Bit 0 : Start UART receiver */
#define UARTE_TASKS_STARTRX_TASKS_STARTRX_Pos (0UL) /*!< Position of TASKS_STARTRX field. */
#define UARTE_TASKS_STARTRX_TASKS_STARTRX_Msk                                                      \
  (0x1UL << UARTE_TASKS_STARTRX_TASKS_STARTRX_Pos)      /*!< Bit mask of TASKS_STARTRX field. */
#define UARTE_TASKS_STARTRX_TASKS_STARTRX_Trigger (1UL) /*!< Trigger task */

/* Register: UARTE_TASKS_STOPRX */
/* Description: Stop UART receiver */

/* Bit 0 : Stop UART receiver */
#define UARTE_TASKS_STOPRX_TASKS_STOPRX_Pos       (0UL) /*!< Position of TASKS_STOPRX field. */
#define UARTE_TASKS_STOPRX_TASKS_STOPRX_Msk                                                        \
  (0x1UL << UARTE_TASKS_STOPRX_TASKS_STOPRX_Pos)      /*!< Bit mask of TASKS_STOPRX field. */
#define UARTE_TASKS_STOPRX_TASKS_STOPRX_Trigger (1UL) /*!< Trigger task */

/* Register: UARTE_TASKS_STARTTX */
/* Description: Start UART transmitter */

/* Bit 0 : Start UART transmitter */
#define UARTE_TASKS_STARTTX_TASKS_STARTTX_Pos   (0UL) /*!< Position of TASKS_STARTTX field. */
#define UARTE_TASKS_STARTTX_TASKS_STARTTX_Msk                                                      \
  (0x1UL << UARTE_TASKS_STARTTX_TASKS_STARTTX_Pos)      /*!< Bit mask of TASKS_STARTTX field. */
#define UARTE_TASKS_STARTTX_TASKS_STARTTX_Trigger (1UL) /*!< Trigger task */

/* Register: UARTE_TASKS_STOPTX */
/* Description: Stop UART transmitter */

/* Bit 0 : Stop UART transmitter */
#define UARTE_TASKS_STOPTX_TASKS_STOPTX_Pos       (0UL) /*!< Position of TASKS_STOPTX field. */
#define UARTE_TASKS_STOPTX_TASKS_STOPTX_Msk                                                        \
  (0x1UL << UARTE_TASKS_STOPTX_TASKS_STOPTX_Pos)      /*!< Bit mask of TASKS_STOPTX field. */
#define UARTE_TASKS_STOPTX_TASKS_STOPTX_Trigger (1UL) /*!< Trigger task */

/* Register: UARTE_TASKS_FLUSHRX */
/* Description: Flush RX FIFO into RX buffer */

/* Bit 0 : Flush RX FIFO into RX buffer */
#define UARTE_TASKS_FLUSHRX_TASKS_FLUSHRX_Pos   (0UL) /*!< Position of TASKS_FLUSHRX field. */
#define UARTE_TASKS_FLUSHRX_TASKS_FLUSHRX_Msk                                                      \
  (0x1UL << UARTE_TASKS_FLUSHRX_TASKS_FLUSHRX_Pos)      /*!< Bit mask of TASKS_FLUSHRX field. */
#define UARTE_TASKS_FLUSHRX_TASKS_FLUSHRX_Trigger (1UL) /*!< Trigger task */

/* Register: UARTE_EVENTS_CTS */
/* Description: CTS is activated (set low). Clear To Send. */

/* Bit 0 : CTS is activated (set low). Clear To Send. */
#define UARTE_EVENTS_CTS_EVENTS_CTS_Pos           (0UL) /*!< Position of EVENTS_CTS field. */
#define UARTE_EVENTS_CTS_EVENTS_CTS_Msk                                                            \
  (0x1UL << UARTE_EVENTS_CTS_EVENTS_CTS_Pos)           /*!< Bit mask of EVENTS_CTS field. */
#define UARTE_EVENTS_CTS_EVENTS_CTS_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_CTS_EVENTS_CTS_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_NCTS */
/* Description: CTS is deactivated (set high). Not Clear To Send. */

/* Bit 0 : CTS is deactivated (set high). Not Clear To Send. */
#define UARTE_EVENTS_NCTS_EVENTS_NCTS_Pos        (0UL) /*!< Position of EVENTS_NCTS field. */
#define UARTE_EVENTS_NCTS_EVENTS_NCTS_Msk                                                          \
  (0x1UL << UARTE_EVENTS_NCTS_EVENTS_NCTS_Pos)           /*!< Bit mask of EVENTS_NCTS field. */
#define UARTE_EVENTS_NCTS_EVENTS_NCTS_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_NCTS_EVENTS_NCTS_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_RXDRDY */
/* Description: Data received in RXD (but potentially not yet transferred to Data RAM) */

/* Bit 0 : Data received in RXD (but potentially not yet transferred to Data RAM) */
#define UARTE_EVENTS_RXDRDY_EVENTS_RXDRDY_Pos      (0UL) /*!< Position of EVENTS_RXDRDY field. */
#define UARTE_EVENTS_RXDRDY_EVENTS_RXDRDY_Msk                                                      \
  (0x1UL << UARTE_EVENTS_RXDRDY_EVENTS_RXDRDY_Pos) /*!< Bit mask of EVENTS_RXDRDY field. */
#define UARTE_EVENTS_RXDRDY_EVENTS_RXDRDY_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_RXDRDY_EVENTS_RXDRDY_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_ENDRX */
/* Description: Receive buffer is filled up */

/* Bit 0 : Receive buffer is filled up */
#define UARTE_EVENTS_ENDRX_EVENTS_ENDRX_Pos            (0UL) /*!< Position of EVENTS_ENDRX field. */
#define UARTE_EVENTS_ENDRX_EVENTS_ENDRX_Msk                                                        \
  (0x1UL << UARTE_EVENTS_ENDRX_EVENTS_ENDRX_Pos)           /*!< Bit mask of EVENTS_ENDRX field. */
#define UARTE_EVENTS_ENDRX_EVENTS_ENDRX_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_ENDRX_EVENTS_ENDRX_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_TXDRDY */
/* Description: Data sent from TXD */

/* Bit 0 : Data sent from TXD */
#define UARTE_EVENTS_TXDRDY_EVENTS_TXDRDY_Pos        (0UL) /*!< Position of EVENTS_TXDRDY field. */
#define UARTE_EVENTS_TXDRDY_EVENTS_TXDRDY_Msk                                                      \
  (0x1UL << UARTE_EVENTS_TXDRDY_EVENTS_TXDRDY_Pos) /*!< Bit mask of EVENTS_TXDRDY field. */
#define UARTE_EVENTS_TXDRDY_EVENTS_TXDRDY_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_TXDRDY_EVENTS_TXDRDY_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_ENDTX */
/* Description: Last TX byte transmitted */

/* Bit 0 : Last TX byte transmitted */
#define UARTE_EVENTS_ENDTX_EVENTS_ENDTX_Pos            (0UL) /*!< Position of EVENTS_ENDTX field. */
#define UARTE_EVENTS_ENDTX_EVENTS_ENDTX_Msk                                                        \
  (0x1UL << UARTE_EVENTS_ENDTX_EVENTS_ENDTX_Pos)           /*!< Bit mask of EVENTS_ENDTX field. */
#define UARTE_EVENTS_ENDTX_EVENTS_ENDTX_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_ENDTX_EVENTS_ENDTX_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_ERROR */
/* Description: Error detected */

/* Bit 0 : Error detected */
#define UARTE_EVENTS_ERROR_EVENTS_ERROR_Pos          (0UL) /*!< Position of EVENTS_ERROR field. */
#define UARTE_EVENTS_ERROR_EVENTS_ERROR_Msk                                                        \
  (0x1UL << UARTE_EVENTS_ERROR_EVENTS_ERROR_Pos)           /*!< Bit mask of EVENTS_ERROR field. */
#define UARTE_EVENTS_ERROR_EVENTS_ERROR_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_ERROR_EVENTS_ERROR_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_RXTO */
/* Description: Receiver timeout */

/* Bit 0 : Receiver timeout */
#define UARTE_EVENTS_RXTO_EVENTS_RXTO_Pos            (0UL) /*!< Position of EVENTS_RXTO field. */
#define UARTE_EVENTS_RXTO_EVENTS_RXTO_Msk                                                          \
  (0x1UL << UARTE_EVENTS_RXTO_EVENTS_RXTO_Pos)           /*!< Bit mask of EVENTS_RXTO field. */
#define UARTE_EVENTS_RXTO_EVENTS_RXTO_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_RXTO_EVENTS_RXTO_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_RXSTARTED */
/* Description: UART receiver has started */

/* Bit 0 : UART receiver has started */
#define UARTE_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Pos                                                \
  (0UL) /*!< Position of EVENTS_RXSTARTED field. */
#define UARTE_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Msk                                                \
  (0x1UL << UARTE_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Pos) /*!< Bit mask of EVENTS_RXSTARTED field. */
#define UARTE_EVENTS_RXSTARTED_EVENTS_RXSTARTED_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_RXSTARTED_EVENTS_RXSTARTED_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_TXSTARTED */
/* Description: UART transmitter has started */

/* Bit 0 : UART transmitter has started */
#define UARTE_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Pos                                                \
  (0UL) /*!< Position of EVENTS_TXSTARTED field. */
#define UARTE_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Msk                                                \
  (0x1UL << UARTE_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Pos) /*!< Bit mask of EVENTS_TXSTARTED field. */
#define UARTE_EVENTS_TXSTARTED_EVENTS_TXSTARTED_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_TXSTARTED_EVENTS_TXSTARTED_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_EVENTS_TXSTOPPED */
/* Description: Transmitter stopped */

/* Bit 0 : Transmitter stopped */
#define UARTE_EVENTS_TXSTOPPED_EVENTS_TXSTOPPED_Pos                                                \
  (0UL) /*!< Position of EVENTS_TXSTOPPED field. */
#define UARTE_EVENTS_TXSTOPPED_EVENTS_TXSTOPPED_Msk                                                \
  (0x1UL << UARTE_EVENTS_TXSTOPPED_EVENTS_TXSTOPPED_Pos) /*!< Bit mask of EVENTS_TXSTOPPED field. */
#define UARTE_EVENTS_TXSTOPPED_EVENTS_TXSTOPPED_NotGenerated (0UL) /*!< Event not generated */
#define UARTE_EVENTS_TXSTOPPED_EVENTS_TXSTOPPED_Generated    (1UL) /*!< Event generated */

/* Register: UARTE_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 6 : Shortcut between event ENDRX and task STOPRX */
#define UARTE_SHORTS_ENDRX_STOPRX_Pos                        (6UL) /*!< Position of ENDRX_STOPRX field. */
#define UARTE_SHORTS_ENDRX_STOPRX_Msk                                                              \
  (0x1UL << UARTE_SHORTS_ENDRX_STOPRX_Pos)       /*!< Bit mask of ENDRX_STOPRX field. */
#define UARTE_SHORTS_ENDRX_STOPRX_Disabled (0UL) /*!< Disable shortcut */
#define UARTE_SHORTS_ENDRX_STOPRX_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 5 : Shortcut between event ENDRX and task STARTRX */
#define UARTE_SHORTS_ENDRX_STARTRX_Pos     (5UL) /*!< Position of ENDRX_STARTRX field. */
#define UARTE_SHORTS_ENDRX_STARTRX_Msk                                                             \
  (0x1UL << UARTE_SHORTS_ENDRX_STARTRX_Pos)       /*!< Bit mask of ENDRX_STARTRX field. */
#define UARTE_SHORTS_ENDRX_STARTRX_Disabled (0UL) /*!< Disable shortcut */
#define UARTE_SHORTS_ENDRX_STARTRX_Enabled  (1UL) /*!< Enable shortcut */

/* Register: UARTE_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 22 : Enable or disable interrupt for event TXSTOPPED */
#define UARTE_INTEN_TXSTOPPED_Pos           (22UL) /*!< Position of TXSTOPPED field. */
#define UARTE_INTEN_TXSTOPPED_Msk                                                                  \
  (0x1UL << UARTE_INTEN_TXSTOPPED_Pos)       /*!< Bit mask of TXSTOPPED field. */
#define UARTE_INTEN_TXSTOPPED_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_TXSTOPPED_Enabled  (1UL) /*!< Enable */

/* Bit 20 : Enable or disable interrupt for event TXSTARTED */
#define UARTE_INTEN_TXSTARTED_Pos      (20UL) /*!< Position of TXSTARTED field. */
#define UARTE_INTEN_TXSTARTED_Msk                                                                  \
  (0x1UL << UARTE_INTEN_TXSTARTED_Pos)       /*!< Bit mask of TXSTARTED field. */
#define UARTE_INTEN_TXSTARTED_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_TXSTARTED_Enabled  (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for event RXSTARTED */
#define UARTE_INTEN_RXSTARTED_Pos      (19UL) /*!< Position of RXSTARTED field. */
#define UARTE_INTEN_RXSTARTED_Msk                                                                  \
  (0x1UL << UARTE_INTEN_RXSTARTED_Pos)       /*!< Bit mask of RXSTARTED field. */
#define UARTE_INTEN_RXSTARTED_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_RXSTARTED_Enabled  (1UL) /*!< Enable */

/* Bit 17 : Enable or disable interrupt for event RXTO */
#define UARTE_INTEN_RXTO_Pos           (17UL) /*!< Position of RXTO field. */
#define UARTE_INTEN_RXTO_Msk           (0x1UL << UARTE_INTEN_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UARTE_INTEN_RXTO_Disabled      (0UL)                           /*!< Disable */
#define UARTE_INTEN_RXTO_Enabled       (1UL)                           /*!< Enable */

/* Bit 9 : Enable or disable interrupt for event ERROR */
#define UARTE_INTEN_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define UARTE_INTEN_ERROR_Msk          (0x1UL << UARTE_INTEN_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define UARTE_INTEN_ERROR_Disabled     (0UL)                            /*!< Disable */
#define UARTE_INTEN_ERROR_Enabled      (1UL)                            /*!< Enable */

/* Bit 8 : Enable or disable interrupt for event ENDTX */
#define UARTE_INTEN_ENDTX_Pos          (8UL) /*!< Position of ENDTX field. */
#define UARTE_INTEN_ENDTX_Msk          (0x1UL << UARTE_INTEN_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define UARTE_INTEN_ENDTX_Disabled     (0UL)                            /*!< Disable */
#define UARTE_INTEN_ENDTX_Enabled      (1UL)                            /*!< Enable */

/* Bit 7 : Enable or disable interrupt for event TXDRDY */
#define UARTE_INTEN_TXDRDY_Pos         (7UL) /*!< Position of TXDRDY field. */
#define UARTE_INTEN_TXDRDY_Msk         (0x1UL << UARTE_INTEN_TXDRDY_Pos) /*!< Bit mask of TXDRDY field. */
#define UARTE_INTEN_TXDRDY_Disabled    (0UL)                             /*!< Disable */
#define UARTE_INTEN_TXDRDY_Enabled     (1UL)                             /*!< Enable */

/* Bit 4 : Enable or disable interrupt for event ENDRX */
#define UARTE_INTEN_ENDRX_Pos          (4UL) /*!< Position of ENDRX field. */
#define UARTE_INTEN_ENDRX_Msk          (0x1UL << UARTE_INTEN_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define UARTE_INTEN_ENDRX_Disabled     (0UL)                            /*!< Disable */
#define UARTE_INTEN_ENDRX_Enabled      (1UL)                            /*!< Enable */

/* Bit 2 : Enable or disable interrupt for event RXDRDY */
#define UARTE_INTEN_RXDRDY_Pos         (2UL) /*!< Position of RXDRDY field. */
#define UARTE_INTEN_RXDRDY_Msk         (0x1UL << UARTE_INTEN_RXDRDY_Pos) /*!< Bit mask of RXDRDY field. */
#define UARTE_INTEN_RXDRDY_Disabled    (0UL)                             /*!< Disable */
#define UARTE_INTEN_RXDRDY_Enabled     (1UL)                             /*!< Enable */

/* Bit 1 : Enable or disable interrupt for event NCTS */
#define UARTE_INTEN_NCTS_Pos           (1UL) /*!< Position of NCTS field. */
#define UARTE_INTEN_NCTS_Msk           (0x1UL << UARTE_INTEN_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UARTE_INTEN_NCTS_Disabled      (0UL)                           /*!< Disable */
#define UARTE_INTEN_NCTS_Enabled       (1UL)                           /*!< Enable */

/* Bit 0 : Enable or disable interrupt for event CTS */
#define UARTE_INTEN_CTS_Pos            (0UL)                          /*!< Position of CTS field. */
#define UARTE_INTEN_CTS_Msk            (0x1UL << UARTE_INTEN_CTS_Pos) /*!< Bit mask of CTS field. */
#define UARTE_INTEN_CTS_Disabled       (0UL)                          /*!< Disable */
#define UARTE_INTEN_CTS_Enabled        (1UL)                          /*!< Enable */

/* Register: UARTE_INTENSET */
/* Description: Enable interrupt */

/* Bit 22 : Write '1' to enable interrupt for event TXSTOPPED */
#define UARTE_INTENSET_TXSTOPPED_Pos   (22UL) /*!< Position of TXSTOPPED field. */
#define UARTE_INTENSET_TXSTOPPED_Msk                                                               \
  (0x1UL << UARTE_INTENSET_TXSTOPPED_Pos)       /*!< Bit mask of TXSTOPPED field. */
#define UARTE_INTENSET_TXSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_TXSTOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_TXSTOPPED_Set      (1UL) /*!< Enable */

/* Bit 20 : Write '1' to enable interrupt for event TXSTARTED */
#define UARTE_INTENSET_TXSTARTED_Pos      (20UL) /*!< Position of TXSTARTED field. */
#define UARTE_INTENSET_TXSTARTED_Msk                                                               \
  (0x1UL << UARTE_INTENSET_TXSTARTED_Pos)       /*!< Bit mask of TXSTARTED field. */
#define UARTE_INTENSET_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_TXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_TXSTARTED_Set      (1UL) /*!< Enable */

/* Bit 19 : Write '1' to enable interrupt for event RXSTARTED */
#define UARTE_INTENSET_RXSTARTED_Pos      (19UL) /*!< Position of RXSTARTED field. */
#define UARTE_INTENSET_RXSTARTED_Msk                                                               \
  (0x1UL << UARTE_INTENSET_RXSTARTED_Pos)       /*!< Bit mask of RXSTARTED field. */
#define UARTE_INTENSET_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_RXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_RXSTARTED_Set      (1UL) /*!< Enable */

/* Bit 17 : Write '1' to enable interrupt for event RXTO */
#define UARTE_INTENSET_RXTO_Pos           (17UL) /*!< Position of RXTO field. */
#define UARTE_INTENSET_RXTO_Msk           (0x1UL << UARTE_INTENSET_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UARTE_INTENSET_RXTO_Disabled      (0UL)                              /*!< Read: Disabled */
#define UARTE_INTENSET_RXTO_Enabled       (1UL)                              /*!< Read: Enabled */
#define UARTE_INTENSET_RXTO_Set           (1UL)                              /*!< Enable */

/* Bit 9 : Write '1' to enable interrupt for event ERROR */
#define UARTE_INTENSET_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define UARTE_INTENSET_ERROR_Msk                                                                   \
  (0x1UL << UARTE_INTENSET_ERROR_Pos)       /*!< Bit mask of ERROR field. */
#define UARTE_INTENSET_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_ERROR_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_ERROR_Set      (1UL) /*!< Enable */

/* Bit 8 : Write '1' to enable interrupt for event ENDTX */
#define UARTE_INTENSET_ENDTX_Pos      (8UL) /*!< Position of ENDTX field. */
#define UARTE_INTENSET_ENDTX_Msk                                                                   \
  (0x1UL << UARTE_INTENSET_ENDTX_Pos)       /*!< Bit mask of ENDTX field. */
#define UARTE_INTENSET_ENDTX_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_ENDTX_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_ENDTX_Set      (1UL) /*!< Enable */

/* Bit 7 : Write '1' to enable interrupt for event TXDRDY */
#define UARTE_INTENSET_TXDRDY_Pos     (7UL) /*!< Position of TXDRDY field. */
#define UARTE_INTENSET_TXDRDY_Msk                                                                  \
  (0x1UL << UARTE_INTENSET_TXDRDY_Pos)       /*!< Bit mask of TXDRDY field. */
#define UARTE_INTENSET_TXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_TXDRDY_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_TXDRDY_Set      (1UL) /*!< Enable */

/* Bit 4 : Write '1' to enable interrupt for event ENDRX */
#define UARTE_INTENSET_ENDRX_Pos       (4UL) /*!< Position of ENDRX field. */
#define UARTE_INTENSET_ENDRX_Msk                                                                   \
  (0x1UL << UARTE_INTENSET_ENDRX_Pos)       /*!< Bit mask of ENDRX field. */
#define UARTE_INTENSET_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_ENDRX_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_ENDRX_Set      (1UL) /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event RXDRDY */
#define UARTE_INTENSET_RXDRDY_Pos     (2UL) /*!< Position of RXDRDY field. */
#define UARTE_INTENSET_RXDRDY_Msk                                                                  \
  (0x1UL << UARTE_INTENSET_RXDRDY_Pos)       /*!< Bit mask of RXDRDY field. */
#define UARTE_INTENSET_RXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_RXDRDY_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_RXDRDY_Set      (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event NCTS */
#define UARTE_INTENSET_NCTS_Pos        (1UL) /*!< Position of NCTS field. */
#define UARTE_INTENSET_NCTS_Msk        (0x1UL << UARTE_INTENSET_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UARTE_INTENSET_NCTS_Disabled   (0UL)                              /*!< Read: Disabled */
#define UARTE_INTENSET_NCTS_Enabled    (1UL)                              /*!< Read: Enabled */
#define UARTE_INTENSET_NCTS_Set        (1UL)                              /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event CTS */
#define UARTE_INTENSET_CTS_Pos         (0UL) /*!< Position of CTS field. */
#define UARTE_INTENSET_CTS_Msk         (0x1UL << UARTE_INTENSET_CTS_Pos) /*!< Bit mask of CTS field. */
#define UARTE_INTENSET_CTS_Disabled    (0UL)                             /*!< Read: Disabled */
#define UARTE_INTENSET_CTS_Enabled     (1UL)                             /*!< Read: Enabled */
#define UARTE_INTENSET_CTS_Set         (1UL)                             /*!< Enable */

/* Register: UARTE_INTENCLR */
/* Description: Disable interrupt */

/* Bit 22 : Write '1' to disable interrupt for event TXSTOPPED */
#define UARTE_INTENCLR_TXSTOPPED_Pos   (22UL) /*!< Position of TXSTOPPED field. */
#define UARTE_INTENCLR_TXSTOPPED_Msk                                                               \
  (0x1UL << UARTE_INTENCLR_TXSTOPPED_Pos)       /*!< Bit mask of TXSTOPPED field. */
#define UARTE_INTENCLR_TXSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_TXSTOPPED_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_TXSTOPPED_Clear    (1UL) /*!< Disable */

/* Bit 20 : Write '1' to disable interrupt for event TXSTARTED */
#define UARTE_INTENCLR_TXSTARTED_Pos      (20UL) /*!< Position of TXSTARTED field. */
#define UARTE_INTENCLR_TXSTARTED_Msk                                                               \
  (0x1UL << UARTE_INTENCLR_TXSTARTED_Pos)       /*!< Bit mask of TXSTARTED field. */
#define UARTE_INTENCLR_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_TXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_TXSTARTED_Clear    (1UL) /*!< Disable */

/* Bit 19 : Write '1' to disable interrupt for event RXSTARTED */
#define UARTE_INTENCLR_RXSTARTED_Pos      (19UL) /*!< Position of RXSTARTED field. */
#define UARTE_INTENCLR_RXSTARTED_Msk                                                               \
  (0x1UL << UARTE_INTENCLR_RXSTARTED_Pos)       /*!< Bit mask of RXSTARTED field. */
#define UARTE_INTENCLR_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_RXSTARTED_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_RXSTARTED_Clear    (1UL) /*!< Disable */

/* Bit 17 : Write '1' to disable interrupt for event RXTO */
#define UARTE_INTENCLR_RXTO_Pos           (17UL) /*!< Position of RXTO field. */
#define UARTE_INTENCLR_RXTO_Msk           (0x1UL << UARTE_INTENCLR_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UARTE_INTENCLR_RXTO_Disabled      (0UL)                              /*!< Read: Disabled */
#define UARTE_INTENCLR_RXTO_Enabled       (1UL)                              /*!< Read: Enabled */
#define UARTE_INTENCLR_RXTO_Clear         (1UL)                              /*!< Disable */

/* Bit 9 : Write '1' to disable interrupt for event ERROR */
#define UARTE_INTENCLR_ERROR_Pos          (9UL) /*!< Position of ERROR field. */
#define UARTE_INTENCLR_ERROR_Msk                                                                   \
  (0x1UL << UARTE_INTENCLR_ERROR_Pos)       /*!< Bit mask of ERROR field. */
#define UARTE_INTENCLR_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_ERROR_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_ERROR_Clear    (1UL) /*!< Disable */

/* Bit 8 : Write '1' to disable interrupt for event ENDTX */
#define UARTE_INTENCLR_ENDTX_Pos      (8UL) /*!< Position of ENDTX field. */
#define UARTE_INTENCLR_ENDTX_Msk                                                                   \
  (0x1UL << UARTE_INTENCLR_ENDTX_Pos)       /*!< Bit mask of ENDTX field. */
#define UARTE_INTENCLR_ENDTX_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_ENDTX_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_ENDTX_Clear    (1UL) /*!< Disable */

/* Bit 7 : Write '1' to disable interrupt for event TXDRDY */
#define UARTE_INTENCLR_TXDRDY_Pos     (7UL) /*!< Position of TXDRDY field. */
#define UARTE_INTENCLR_TXDRDY_Msk                                                                  \
  (0x1UL << UARTE_INTENCLR_TXDRDY_Pos)       /*!< Bit mask of TXDRDY field. */
#define UARTE_INTENCLR_TXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_TXDRDY_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_TXDRDY_Clear    (1UL) /*!< Disable */

/* Bit 4 : Write '1' to disable interrupt for event ENDRX */
#define UARTE_INTENCLR_ENDRX_Pos       (4UL) /*!< Position of ENDRX field. */
#define UARTE_INTENCLR_ENDRX_Msk                                                                   \
  (0x1UL << UARTE_INTENCLR_ENDRX_Pos)       /*!< Bit mask of ENDRX field. */
#define UARTE_INTENCLR_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_ENDRX_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_ENDRX_Clear    (1UL) /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event RXDRDY */
#define UARTE_INTENCLR_RXDRDY_Pos     (2UL) /*!< Position of RXDRDY field. */
#define UARTE_INTENCLR_RXDRDY_Msk                                                                  \
  (0x1UL << UARTE_INTENCLR_RXDRDY_Pos)       /*!< Bit mask of RXDRDY field. */
#define UARTE_INTENCLR_RXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_RXDRDY_Enabled  (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_RXDRDY_Clear    (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event NCTS */
#define UARTE_INTENCLR_NCTS_Pos        (1UL) /*!< Position of NCTS field. */
#define UARTE_INTENCLR_NCTS_Msk        (0x1UL << UARTE_INTENCLR_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UARTE_INTENCLR_NCTS_Disabled   (0UL)                              /*!< Read: Disabled */
#define UARTE_INTENCLR_NCTS_Enabled    (1UL)                              /*!< Read: Enabled */
#define UARTE_INTENCLR_NCTS_Clear      (1UL)                              /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event CTS */
#define UARTE_INTENCLR_CTS_Pos         (0UL) /*!< Position of CTS field. */
#define UARTE_INTENCLR_CTS_Msk         (0x1UL << UARTE_INTENCLR_CTS_Pos) /*!< Bit mask of CTS field. */
#define UARTE_INTENCLR_CTS_Disabled    (0UL)                             /*!< Read: Disabled */
#define UARTE_INTENCLR_CTS_Enabled     (1UL)                             /*!< Read: Enabled */
#define UARTE_INTENCLR_CTS_Clear       (1UL)                             /*!< Disable */

/* Register: UARTE_ERRORSRC */
/* Description: Error source Note : this register is read / write one to clear. */

/* Bit 3 : Break condition */
#define UARTE_ERRORSRC_BREAK_Pos       (3UL) /*!< Position of BREAK field. */
#define UARTE_ERRORSRC_BREAK_Msk                                                                   \
  (0x1UL << UARTE_ERRORSRC_BREAK_Pos)         /*!< Bit mask of BREAK field. */
#define UARTE_ERRORSRC_BREAK_NotPresent (0UL) /*!< Read: error not present */
#define UARTE_ERRORSRC_BREAK_Present    (1UL) /*!< Read: error present */

/* Bit 2 : Framing error occurred */
#define UARTE_ERRORSRC_FRAMING_Pos      (2UL) /*!< Position of FRAMING field. */
#define UARTE_ERRORSRC_FRAMING_Msk                                                                 \
  (0x1UL << UARTE_ERRORSRC_FRAMING_Pos)         /*!< Bit mask of FRAMING field. */
#define UARTE_ERRORSRC_FRAMING_NotPresent (0UL) /*!< Read: error not present */
#define UARTE_ERRORSRC_FRAMING_Present    (1UL) /*!< Read: error present */

/* Bit 1 : Parity error */
#define UARTE_ERRORSRC_PARITY_Pos         (1UL) /*!< Position of PARITY field. */
#define UARTE_ERRORSRC_PARITY_Msk                                                                  \
  (0x1UL << UARTE_ERRORSRC_PARITY_Pos)         /*!< Bit mask of PARITY field. */
#define UARTE_ERRORSRC_PARITY_NotPresent (0UL) /*!< Read: error not present */
#define UARTE_ERRORSRC_PARITY_Present    (1UL) /*!< Read: error present */

/* Bit 0 : Overrun error */
#define UARTE_ERRORSRC_OVERRUN_Pos       (0UL) /*!< Position of OVERRUN field. */
#define UARTE_ERRORSRC_OVERRUN_Msk                                                                 \
  (0x1UL << UARTE_ERRORSRC_OVERRUN_Pos)         /*!< Bit mask of OVERRUN field. */
#define UARTE_ERRORSRC_OVERRUN_NotPresent (0UL) /*!< Read: error not present */
#define UARTE_ERRORSRC_OVERRUN_Present    (1UL) /*!< Read: error present */

/* Register: UARTE_ENABLE */
/* Description: Enable UART */

/* Bits 3..0 : Enable or disable UARTE */
#define UARTE_ENABLE_ENABLE_Pos           (0UL) /*!< Position of ENABLE field. */
#define UARTE_ENABLE_ENABLE_Msk           (0xFUL << UARTE_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define UARTE_ENABLE_ENABLE_Disabled      (0UL)                              /*!< Disable UARTE */
#define UARTE_ENABLE_ENABLE_Enabled       (8UL)                              /*!< Enable UARTE */

/* Register: UARTE_PSEL_RTS */
/* Description: Pin select for RTS signal */

/* Bit 31 : Connection */
#define UARTE_PSEL_RTS_CONNECT_Pos        (31UL) /*!< Position of CONNECT field. */
#define UARTE_PSEL_RTS_CONNECT_Msk                                                                 \
  (0x1UL << UARTE_PSEL_RTS_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define UARTE_PSEL_RTS_CONNECT_Connected    (0UL) /*!< Connect */
#define UARTE_PSEL_RTS_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define UARTE_PSEL_RTS_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define UARTE_PSEL_RTS_PIN_Msk              (0x1FUL << UARTE_PSEL_RTS_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UARTE_PSEL_TXD */
/* Description: Pin select for TXD signal */

/* Bit 31 : Connection */
#define UARTE_PSEL_TXD_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define UARTE_PSEL_TXD_CONNECT_Msk                                                                 \
  (0x1UL << UARTE_PSEL_TXD_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define UARTE_PSEL_TXD_CONNECT_Connected    (0UL) /*!< Connect */
#define UARTE_PSEL_TXD_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define UARTE_PSEL_TXD_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define UARTE_PSEL_TXD_PIN_Msk              (0x1FUL << UARTE_PSEL_TXD_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UARTE_PSEL_CTS */
/* Description: Pin select for CTS signal */

/* Bit 31 : Connection */
#define UARTE_PSEL_CTS_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define UARTE_PSEL_CTS_CONNECT_Msk                                                                 \
  (0x1UL << UARTE_PSEL_CTS_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define UARTE_PSEL_CTS_CONNECT_Connected    (0UL) /*!< Connect */
#define UARTE_PSEL_CTS_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define UARTE_PSEL_CTS_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define UARTE_PSEL_CTS_PIN_Msk              (0x1FUL << UARTE_PSEL_CTS_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UARTE_PSEL_RXD */
/* Description: Pin select for RXD signal */

/* Bit 31 : Connection */
#define UARTE_PSEL_RXD_CONNECT_Pos          (31UL) /*!< Position of CONNECT field. */
#define UARTE_PSEL_RXD_CONNECT_Msk                                                                 \
  (0x1UL << UARTE_PSEL_RXD_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define UARTE_PSEL_RXD_CONNECT_Connected    (0UL) /*!< Connect */
#define UARTE_PSEL_RXD_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : Pin number */
#define UARTE_PSEL_RXD_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define UARTE_PSEL_RXD_PIN_Msk              (0x1FUL << UARTE_PSEL_RXD_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UARTE_BAUDRATE */
/* Description: Baud rate. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : Baud rate */
#define UARTE_BAUDRATE_BAUDRATE_Pos         (0UL) /*!< Position of BAUDRATE field. */
#define UARTE_BAUDRATE_BAUDRATE_Msk                                                                \
  (0xFFFFFFFFUL << UARTE_BAUDRATE_BAUDRATE_Pos)           /*!< Bit mask of BAUDRATE field. */
#define UARTE_BAUDRATE_BAUDRATE_Baud1200   (0x0004F000UL) /*!< 1200 baud (actual rate: 1205) */
#define UARTE_BAUDRATE_BAUDRATE_Baud2400   (0x0009D000UL) /*!< 2400 baud (actual rate: 2396) */
#define UARTE_BAUDRATE_BAUDRATE_Baud4800   (0x0013B000UL) /*!< 4800 baud (actual rate: 4808) */
#define UARTE_BAUDRATE_BAUDRATE_Baud9600   (0x00275000UL) /*!< 9600 baud (actual rate: 9598) */
#define UARTE_BAUDRATE_BAUDRATE_Baud14400  (0x003AF000UL) /*!< 14400 baud (actual rate: 14401) */
#define UARTE_BAUDRATE_BAUDRATE_Baud19200  (0x004EA000UL) /*!< 19200 baud (actual rate: 19208) */
#define UARTE_BAUDRATE_BAUDRATE_Baud28800  (0x0075C000UL) /*!< 28800 baud (actual rate: 28777) */
#define UARTE_BAUDRATE_BAUDRATE_Baud31250  (0x00800000UL) /*!< 31250 baud */
#define UARTE_BAUDRATE_BAUDRATE_Baud38400  (0x009D0000UL) /*!< 38400 baud (actual rate: 38369) */
#define UARTE_BAUDRATE_BAUDRATE_Baud56000  (0x00E50000UL) /*!< 56000 baud (actual rate: 55944) */
#define UARTE_BAUDRATE_BAUDRATE_Baud57600  (0x00EB0000UL) /*!< 57600 baud (actual rate: 57554) */
#define UARTE_BAUDRATE_BAUDRATE_Baud76800  (0x013A9000UL) /*!< 76800 baud (actual rate: 76923) */
#define UARTE_BAUDRATE_BAUDRATE_Baud115200 (0x01D60000UL) /*!< 115200 baud (actual rate: 115108) */
#define UARTE_BAUDRATE_BAUDRATE_Baud230400 (0x03B00000UL) /*!< 230400 baud (actual rate: 231884) */
#define UARTE_BAUDRATE_BAUDRATE_Baud250000 (0x04000000UL) /*!< 250000 baud */
#define UARTE_BAUDRATE_BAUDRATE_Baud460800 (0x07400000UL) /*!< 460800 baud (actual rate: 457143) */
#define UARTE_BAUDRATE_BAUDRATE_Baud921600 (0x0F000000UL) /*!< 921600 baud (actual rate: 941176) */
#define UARTE_BAUDRATE_BAUDRATE_Baud1M     (0x10000000UL) /*!< 1Mega baud */

/* Register: UARTE_RXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define UARTE_RXD_PTR_PTR_Pos              (0UL) /*!< Position of PTR field. */
#define UARTE_RXD_PTR_PTR_Msk              (0xFFFFFFFFUL << UARTE_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: UARTE_RXD_MAXCNT */
/* Description: Maximum number of bytes in receive buffer */

/* Bits 14..0 : Maximum number of bytes in receive buffer */
#define UARTE_RXD_MAXCNT_MAXCNT_Pos        (0UL) /*!< Position of MAXCNT field. */
#define UARTE_RXD_MAXCNT_MAXCNT_Msk                                                                \
  (0x7FFFUL << UARTE_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: UARTE_RXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 14..0 : Number of bytes transferred in the last transaction */
#define UARTE_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define UARTE_RXD_AMOUNT_AMOUNT_Msk                                                                \
  (0x7FFFUL << UARTE_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: UARTE_TXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define UARTE_TXD_PTR_PTR_Pos       (0UL) /*!< Position of PTR field. */
#define UARTE_TXD_PTR_PTR_Msk       (0xFFFFFFFFUL << UARTE_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: UARTE_TXD_MAXCNT */
/* Description: Maximum number of bytes in transmit buffer */

/* Bits 14..0 : Maximum number of bytes in transmit buffer */
#define UARTE_TXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define UARTE_TXD_MAXCNT_MAXCNT_Msk                                                                \
  (0x7FFFUL << UARTE_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: UARTE_TXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 14..0 : Number of bytes transferred in the last transaction */
#define UARTE_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define UARTE_TXD_AMOUNT_AMOUNT_Msk                                                                \
  (0x7FFFUL << UARTE_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: UARTE_CONFIG */
/* Description: Configuration of parity and hardware flow control */

/* Bit 8 : Even or odd parity type */
#define UARTE_CONFIG_PARITYTYPE_Pos (8UL) /*!< Position of PARITYTYPE field. */
#define UARTE_CONFIG_PARITYTYPE_Msk                                                                \
  (0x1UL << UARTE_CONFIG_PARITYTYPE_Pos)   /*!< Bit mask of PARITYTYPE field. */
#define UARTE_CONFIG_PARITYTYPE_Even (0UL) /*!< Even parity */
#define UARTE_CONFIG_PARITYTYPE_Odd  (1UL) /*!< Odd parity */

/* Bit 4 : Stop bits */
#define UARTE_CONFIG_STOP_Pos        (4UL) /*!< Position of STOP field. */
#define UARTE_CONFIG_STOP_Msk        (0x1UL << UARTE_CONFIG_STOP_Pos) /*!< Bit mask of STOP field. */
#define UARTE_CONFIG_STOP_One        (0UL)                            /*!< One stop bit */
#define UARTE_CONFIG_STOP_Two        (1UL)                            /*!< Two stop bits */

/* Bits 3..1 : Parity */
#define UARTE_CONFIG_PARITY_Pos      (1UL) /*!< Position of PARITY field. */
#define UARTE_CONFIG_PARITY_Msk      (0x7UL << UARTE_CONFIG_PARITY_Pos) /*!< Bit mask of PARITY field. */
#define UARTE_CONFIG_PARITY_Excluded (0x0UL)                            /*!< Exclude parity bit */
#define UARTE_CONFIG_PARITY_Included (0x7UL) /*!< Include even parity bit */

/* Bit 0 : Hardware flow control */
#define UARTE_CONFIG_HWFC_Pos        (0UL) /*!< Position of HWFC field. */
#define UARTE_CONFIG_HWFC_Msk        (0x1UL << UARTE_CONFIG_HWFC_Pos) /*!< Bit mask of HWFC field. */
#define UARTE_CONFIG_HWFC_Disabled   (0UL)                            /*!< Disabled */
#define UARTE_CONFIG_HWFC_Enabled    (1UL)                            /*!< Enabled */


/* Peripheral: UICR */
/* Description: User information configuration registers */

/* Register: UICR_NRFFW */
/* Description: Description collection: Reserved for Nordic firmware design */

/* Bits 31..0 : Reserved for Nordic firmware design */
#define UICR_NRFFW_NRFFW_Pos         (0UL) /*!< Position of NRFFW field. */
#define UICR_NRFFW_NRFFW_Msk         (0xFFFFFFFFUL << UICR_NRFFW_NRFFW_Pos) /*!< Bit mask of NRFFW field. */

/* Register: UICR_NRFHW */
/* Description: Description collection: Reserved for Nordic hardware design */

/* Bits 31..0 : Reserved for Nordic hardware design */
#define UICR_NRFHW_NRFHW_Pos         (0UL) /*!< Position of NRFHW field. */
#define UICR_NRFHW_NRFHW_Msk         (0xFFFFFFFFUL << UICR_NRFHW_NRFHW_Pos) /*!< Bit mask of NRFHW field. */

/* Register: UICR_CUSTOMER */
/* Description: Description collection: Reserved for customer */

/* Bits 31..0 : Reserved for customer */
#define UICR_CUSTOMER_CUSTOMER_Pos   (0UL) /*!< Position of CUSTOMER field. */
#define UICR_CUSTOMER_CUSTOMER_Msk                                                                 \
  (0xFFFFFFFFUL << UICR_CUSTOMER_CUSTOMER_Pos) /*!< Bit mask of CUSTOMER field. */

/* Register: UICR_PSELRESET */
/* Description: Description collection: Mapping of the nRESET function (see POWER chapter for details) */

/* Bit 31 : Connection */
#define UICR_PSELRESET_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UICR_PSELRESET_CONNECT_Msk                                                                 \
  (0x1UL << UICR_PSELRESET_CONNECT_Pos)           /*!< Bit mask of CONNECT field. */
#define UICR_PSELRESET_CONNECT_Connected    (0UL) /*!< Connect */
#define UICR_PSELRESET_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 4..0 : GPIO pin number onto which nRESET is exposed */
#define UICR_PSELRESET_PIN_Pos              (0UL) /*!< Position of PIN field. */
#define UICR_PSELRESET_PIN_Msk              (0x1FUL << UICR_PSELRESET_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UICR_APPROTECT */
/* Description: Access port protection */

/* Bits 7..0 : Enable or disable access port protection. */
#define UICR_APPROTECT_PALL_Pos             (0UL) /*!< Position of PALL field. */
#define UICR_APPROTECT_PALL_Msk             (0xFFUL << UICR_APPROTECT_PALL_Pos) /*!< Bit mask of PALL field. */
#define UICR_APPROTECT_PALL_Enabled         (0x00UL)                            /*!< Enable */
#define UICR_APPROTECT_PALL_Disabled        (0xFFUL)                            /*!< Disable */

/* Register: UICR_DEBUGCTRL */
/* Description: Processor debug control */

/* Bits 15..8 : Configure CPU flash patch and breakpoint (FPB) unit behavior */
#define UICR_DEBUGCTRL_CPUFPBEN_Pos         (8UL) /*!< Position of CPUFPBEN field. */
#define UICR_DEBUGCTRL_CPUFPBEN_Msk                                                                \
  (0xFFUL << UICR_DEBUGCTRL_CPUFPBEN_Pos) /*!< Bit mask of CPUFPBEN field. */
#define UICR_DEBUGCTRL_CPUFPBEN_Disabled                                                           \
  (0x00UL) /*!< Disable CPU FPB unit. Writes into the FPB registers will be ignored. */
#define UICR_DEBUGCTRL_CPUFPBEN_Enabled          (0xFFUL) /*!< Enable CPU FPB unit (default behavior) */

/* Register: UICR_REGOUT0 */
/* Description: Output voltage from REG0 regulator stage. The maximum output voltage from this stage is given as VDDH - VREG0DROP. */

/* Bits 2..0 : Output voltage from REG0 regulator stage. */
#define UICR_REGOUT0_VOUT_Pos                    (0UL) /*!< Position of VOUT field. */
#define UICR_REGOUT0_VOUT_Msk                    (0x7UL << UICR_REGOUT0_VOUT_Pos) /*!< Bit mask of VOUT field. */
#define UICR_REGOUT0_VOUT_1V8                    (0UL)                            /*!< 1.8 V */
#define UICR_REGOUT0_VOUT_2V1                    (1UL)                            /*!< 2.1 V */
#define UICR_REGOUT0_VOUT_2V4                    (2UL)                            /*!< 2.4 V */
#define UICR_REGOUT0_VOUT_2V7                    (3UL)                            /*!< 2.7 V */
#define UICR_REGOUT0_VOUT_3V0                    (4UL)                            /*!< 3.0 V */
#define UICR_REGOUT0_VOUT_3V3                    (5UL)                            /*!< 3.3 V */
#define UICR_REGOUT0_VOUT_DEFAULT                (7UL) /*!< Default voltage: 1.8 V */


/* Peripheral: USBD */
/* Description: Universal serial bus device */

/* Register: USBD_TASKS_STARTEPIN */
/* Description: Description collection: Captures the EPIN[n].PTR and EPIN[n].MAXCNT registers values, and enables endpoint IN n to respond to traffic from host */

/* Bit 0 : Captures the EPIN[n].PTR and EPIN[n].MAXCNT registers values, and enables endpoint IN n to respond to traffic from host */
#define USBD_TASKS_STARTEPIN_TASKS_STARTEPIN_Pos (0UL) /*!< Position of TASKS_STARTEPIN field. */
#define USBD_TASKS_STARTEPIN_TASKS_STARTEPIN_Msk                                                   \
  (0x1UL << USBD_TASKS_STARTEPIN_TASKS_STARTEPIN_Pos) /*!< Bit mask of TASKS_STARTEPIN field. */
#define USBD_TASKS_STARTEPIN_TASKS_STARTEPIN_Trigger (1UL) /*!< Trigger task */

/* Register: USBD_TASKS_STARTISOIN */
/* Description: Captures the ISOIN.PTR and ISOIN.MAXCNT registers values, and enables sending data on ISO endpoint */

/* Bit 0 : Captures the ISOIN.PTR and ISOIN.MAXCNT registers values, and enables sending data on ISO endpoint */
#define USBD_TASKS_STARTISOIN_TASKS_STARTISOIN_Pos   (0UL) /*!< Position of TASKS_STARTISOIN field. */
#define USBD_TASKS_STARTISOIN_TASKS_STARTISOIN_Msk                                                 \
  (0x1UL << USBD_TASKS_STARTISOIN_TASKS_STARTISOIN_Pos) /*!< Bit mask of TASKS_STARTISOIN field. */
#define USBD_TASKS_STARTISOIN_TASKS_STARTISOIN_Trigger (1UL) /*!< Trigger task */

/* Register: USBD_TASKS_STARTEPOUT */
/* Description: Description collection: Captures the EPOUT[n].PTR and EPOUT[n].MAXCNT registers values, and enables endpoint n to respond to traffic from host */

/* Bit 0 : Captures the EPOUT[n].PTR and EPOUT[n].MAXCNT registers values, and enables endpoint n to respond to traffic from host */
#define USBD_TASKS_STARTEPOUT_TASKS_STARTEPOUT_Pos     (0UL) /*!< Position of TASKS_STARTEPOUT field. */
#define USBD_TASKS_STARTEPOUT_TASKS_STARTEPOUT_Msk                                                 \
  (0x1UL << USBD_TASKS_STARTEPOUT_TASKS_STARTEPOUT_Pos) /*!< Bit mask of TASKS_STARTEPOUT field. */
#define USBD_TASKS_STARTEPOUT_TASKS_STARTEPOUT_Trigger (1UL) /*!< Trigger task */

/* Register: USBD_TASKS_STARTISOOUT */
/* Description: Captures the ISOOUT.PTR and ISOOUT.MAXCNT registers values, and enables receiving of data on ISO endpoint */

/* Bit 0 : Captures the ISOOUT.PTR and ISOOUT.MAXCNT registers values, and enables receiving of data on ISO endpoint */
#define USBD_TASKS_STARTISOOUT_TASKS_STARTISOOUT_Pos                                               \
  (0UL) /*!< Position of TASKS_STARTISOOUT field. */
#define USBD_TASKS_STARTISOOUT_TASKS_STARTISOOUT_Msk                                               \
  (0x1UL                                                                                           \
   << USBD_TASKS_STARTISOOUT_TASKS_STARTISOOUT_Pos) /*!< Bit mask of TASKS_STARTISOOUT field. */
#define USBD_TASKS_STARTISOOUT_TASKS_STARTISOOUT_Trigger (1UL) /*!< Trigger task */

/* Register: USBD_TASKS_EP0RCVOUT */
/* Description: Allows OUT data stage on control endpoint 0 */

/* Bit 0 : Allows OUT data stage on control endpoint 0 */
#define USBD_TASKS_EP0RCVOUT_TASKS_EP0RCVOUT_Pos         (0UL) /*!< Position of TASKS_EP0RCVOUT field. */
#define USBD_TASKS_EP0RCVOUT_TASKS_EP0RCVOUT_Msk                                                   \
  (0x1UL << USBD_TASKS_EP0RCVOUT_TASKS_EP0RCVOUT_Pos) /*!< Bit mask of TASKS_EP0RCVOUT field. */
#define USBD_TASKS_EP0RCVOUT_TASKS_EP0RCVOUT_Trigger (1UL) /*!< Trigger task */

/* Register: USBD_TASKS_EP0STATUS */
/* Description: Allows status stage on control endpoint 0 */

/* Bit 0 : Allows status stage on control endpoint 0 */
#define USBD_TASKS_EP0STATUS_TASKS_EP0STATUS_Pos     (0UL) /*!< Position of TASKS_EP0STATUS field. */
#define USBD_TASKS_EP0STATUS_TASKS_EP0STATUS_Msk                                                   \
  (0x1UL << USBD_TASKS_EP0STATUS_TASKS_EP0STATUS_Pos) /*!< Bit mask of TASKS_EP0STATUS field. */
#define USBD_TASKS_EP0STATUS_TASKS_EP0STATUS_Trigger (1UL) /*!< Trigger task */

/* Register: USBD_TASKS_EP0STALL */
/* Description: Stalls data and status stage on control endpoint 0 */

/* Bit 0 : Stalls data and status stage on control endpoint 0 */
#define USBD_TASKS_EP0STALL_TASKS_EP0STALL_Pos       (0UL) /*!< Position of TASKS_EP0STALL field. */
#define USBD_TASKS_EP0STALL_TASKS_EP0STALL_Msk                                                     \
  (0x1UL << USBD_TASKS_EP0STALL_TASKS_EP0STALL_Pos)      /*!< Bit mask of TASKS_EP0STALL field. */
#define USBD_TASKS_EP0STALL_TASKS_EP0STALL_Trigger (1UL) /*!< Trigger task */

/* Register: USBD_TASKS_DPDMDRIVE */
/* Description: Forces D+ and D- lines into the state defined in the DPDMVALUE register */

/* Bit 0 : Forces D+ and D- lines into the state defined in the DPDMVALUE register */
#define USBD_TASKS_DPDMDRIVE_TASKS_DPDMDRIVE_Pos   (0UL) /*!< Position of TASKS_DPDMDRIVE field. */
#define USBD_TASKS_DPDMDRIVE_TASKS_DPDMDRIVE_Msk                                                   \
  (0x1UL << USBD_TASKS_DPDMDRIVE_TASKS_DPDMDRIVE_Pos) /*!< Bit mask of TASKS_DPDMDRIVE field. */
#define USBD_TASKS_DPDMDRIVE_TASKS_DPDMDRIVE_Trigger (1UL) /*!< Trigger task */

/* Register: USBD_TASKS_DPDMNODRIVE */
/* Description: Stops forcing D+ and D- lines into any state (USB engine takes control) */

/* Bit 0 : Stops forcing D+ and D- lines into any state (USB engine takes control) */
#define USBD_TASKS_DPDMNODRIVE_TASKS_DPDMNODRIVE_Pos                                               \
  (0UL) /*!< Position of TASKS_DPDMNODRIVE field. */
#define USBD_TASKS_DPDMNODRIVE_TASKS_DPDMNODRIVE_Msk                                               \
  (0x1UL                                                                                           \
   << USBD_TASKS_DPDMNODRIVE_TASKS_DPDMNODRIVE_Pos) /*!< Bit mask of TASKS_DPDMNODRIVE field. */
#define USBD_TASKS_DPDMNODRIVE_TASKS_DPDMNODRIVE_Trigger (1UL) /*!< Trigger task */

/* Register: USBD_EVENTS_USBRESET */
/* Description: Signals that a USB reset condition has been detected on USB lines */

/* Bit 0 : Signals that a USB reset condition has been detected on USB lines */
#define USBD_EVENTS_USBRESET_EVENTS_USBRESET_Pos         (0UL) /*!< Position of EVENTS_USBRESET field. */
#define USBD_EVENTS_USBRESET_EVENTS_USBRESET_Msk                                                   \
  (0x1UL << USBD_EVENTS_USBRESET_EVENTS_USBRESET_Pos) /*!< Bit mask of EVENTS_USBRESET field. */
#define USBD_EVENTS_USBRESET_EVENTS_USBRESET_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_USBRESET_EVENTS_USBRESET_Generated    (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_STARTED */
/* Description: Confirms that the EPIN[n].PTR and EPIN[n].MAXCNT, or EPOUT[n].PTR and EPOUT[n].MAXCNT registers have been captured on all endpoints reported in the EPSTATUS register */

/* Bit 0 : Confirms that the EPIN[n].PTR and EPIN[n].MAXCNT, or EPOUT[n].PTR and EPOUT[n].MAXCNT registers have been captured on all endpoints reported in the EPSTATUS register */
#define USBD_EVENTS_STARTED_EVENTS_STARTED_Pos            (0UL) /*!< Position of EVENTS_STARTED field. */
#define USBD_EVENTS_STARTED_EVENTS_STARTED_Msk                                                     \
  (0x1UL << USBD_EVENTS_STARTED_EVENTS_STARTED_Pos) /*!< Bit mask of EVENTS_STARTED field. */
#define USBD_EVENTS_STARTED_EVENTS_STARTED_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_STARTED_EVENTS_STARTED_Generated    (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_ENDEPIN */
/* Description: Description collection: The whole EPIN[n] buffer has been consumed. The buffer can be accessed safely by software. */

/* Bit 0 : The whole EPIN[n] buffer has been consumed. The buffer can be accessed safely by software. */
#define USBD_EVENTS_ENDEPIN_EVENTS_ENDEPIN_Pos          (0UL) /*!< Position of EVENTS_ENDEPIN field. */
#define USBD_EVENTS_ENDEPIN_EVENTS_ENDEPIN_Msk                                                     \
  (0x1UL << USBD_EVENTS_ENDEPIN_EVENTS_ENDEPIN_Pos) /*!< Bit mask of EVENTS_ENDEPIN field. */
#define USBD_EVENTS_ENDEPIN_EVENTS_ENDEPIN_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_ENDEPIN_EVENTS_ENDEPIN_Generated    (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_EP0DATADONE */
/* Description: An acknowledged data transfer has taken place on the control endpoint */

/* Bit 0 : An acknowledged data transfer has taken place on the control endpoint */
#define USBD_EVENTS_EP0DATADONE_EVENTS_EP0DATADONE_Pos                                             \
  (0UL) /*!< Position of EVENTS_EP0DATADONE field. */
#define USBD_EVENTS_EP0DATADONE_EVENTS_EP0DATADONE_Msk                                             \
  (0x1UL                                                                                           \
   << USBD_EVENTS_EP0DATADONE_EVENTS_EP0DATADONE_Pos) /*!< Bit mask of EVENTS_EP0DATADONE field. */
#define USBD_EVENTS_EP0DATADONE_EVENTS_EP0DATADONE_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_EP0DATADONE_EVENTS_EP0DATADONE_Generated    (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_ENDISOIN */
/* Description: The whole ISOIN buffer has been consumed. The buffer can be accessed safely by software. */

/* Bit 0 : The whole ISOIN buffer has been consumed. The buffer can be accessed safely by software. */
#define USBD_EVENTS_ENDISOIN_EVENTS_ENDISOIN_Pos                (0UL) /*!< Position of EVENTS_ENDISOIN field. */
#define USBD_EVENTS_ENDISOIN_EVENTS_ENDISOIN_Msk                                                   \
  (0x1UL << USBD_EVENTS_ENDISOIN_EVENTS_ENDISOIN_Pos) /*!< Bit mask of EVENTS_ENDISOIN field. */
#define USBD_EVENTS_ENDISOIN_EVENTS_ENDISOIN_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_ENDISOIN_EVENTS_ENDISOIN_Generated    (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_ENDEPOUT */
/* Description: Description collection: The whole EPOUT[n] buffer has been consumed. The buffer can be accessed safely by software. */

/* Bit 0 : The whole EPOUT[n] buffer has been consumed. The buffer can be accessed safely by software. */
#define USBD_EVENTS_ENDEPOUT_EVENTS_ENDEPOUT_Pos          (0UL) /*!< Position of EVENTS_ENDEPOUT field. */
#define USBD_EVENTS_ENDEPOUT_EVENTS_ENDEPOUT_Msk                                                   \
  (0x1UL << USBD_EVENTS_ENDEPOUT_EVENTS_ENDEPOUT_Pos) /*!< Bit mask of EVENTS_ENDEPOUT field. */
#define USBD_EVENTS_ENDEPOUT_EVENTS_ENDEPOUT_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_ENDEPOUT_EVENTS_ENDEPOUT_Generated    (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_ENDISOOUT */
/* Description: The whole ISOOUT buffer has been consumed. The buffer can be accessed safely by software. */

/* Bit 0 : The whole ISOOUT buffer has been consumed. The buffer can be accessed safely by software. */
#define USBD_EVENTS_ENDISOOUT_EVENTS_ENDISOOUT_Pos        (0UL) /*!< Position of EVENTS_ENDISOOUT field. */
#define USBD_EVENTS_ENDISOOUT_EVENTS_ENDISOOUT_Msk                                                 \
  (0x1UL << USBD_EVENTS_ENDISOOUT_EVENTS_ENDISOOUT_Pos) /*!< Bit mask of EVENTS_ENDISOOUT field. */
#define USBD_EVENTS_ENDISOOUT_EVENTS_ENDISOOUT_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_ENDISOOUT_EVENTS_ENDISOOUT_Generated    (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_SOF */
/* Description: Signals that a SOF (start of frame) condition has been detected on USB lines */

/* Bit 0 : Signals that a SOF (start of frame) condition has been detected on USB lines */
#define USBD_EVENTS_SOF_EVENTS_SOF_Pos                      (0UL) /*!< Position of EVENTS_SOF field. */
#define USBD_EVENTS_SOF_EVENTS_SOF_Msk                                                             \
  (0x1UL << USBD_EVENTS_SOF_EVENTS_SOF_Pos)            /*!< Bit mask of EVENTS_SOF field. */
#define USBD_EVENTS_SOF_EVENTS_SOF_NotGenerated  (0UL) /*!< Event not generated */
#define USBD_EVENTS_SOF_EVENTS_SOF_Generated     (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_USBEVENT */
/* Description: An event or an error not covered by specific events has occurred. Check EVENTCAUSE register to find the cause. */

/* Bit 0 : An event or an error not covered by specific events has occurred. Check EVENTCAUSE register to find the cause. */
#define USBD_EVENTS_USBEVENT_EVENTS_USBEVENT_Pos (0UL) /*!< Position of EVENTS_USBEVENT field. */
#define USBD_EVENTS_USBEVENT_EVENTS_USBEVENT_Msk                                                   \
  (0x1UL << USBD_EVENTS_USBEVENT_EVENTS_USBEVENT_Pos) /*!< Bit mask of EVENTS_USBEVENT field. */
#define USBD_EVENTS_USBEVENT_EVENTS_USBEVENT_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_USBEVENT_EVENTS_USBEVENT_Generated    (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_EP0SETUP */
/* Description: A valid SETUP token has been received (and acknowledged) on the control endpoint */

/* Bit 0 : A valid SETUP token has been received (and acknowledged) on the control endpoint */
#define USBD_EVENTS_EP0SETUP_EVENTS_EP0SETUP_Pos          (0UL) /*!< Position of EVENTS_EP0SETUP field. */
#define USBD_EVENTS_EP0SETUP_EVENTS_EP0SETUP_Msk                                                   \
  (0x1UL << USBD_EVENTS_EP0SETUP_EVENTS_EP0SETUP_Pos) /*!< Bit mask of EVENTS_EP0SETUP field. */
#define USBD_EVENTS_EP0SETUP_EVENTS_EP0SETUP_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_EP0SETUP_EVENTS_EP0SETUP_Generated    (1UL) /*!< Event generated */

/* Register: USBD_EVENTS_EPDATA */
/* Description: A data transfer has occurred on a data endpoint, indicated by the EPDATASTATUS register */

/* Bit 0 : A data transfer has occurred on a data endpoint, indicated by the EPDATASTATUS register */
#define USBD_EVENTS_EPDATA_EVENTS_EPDATA_Pos              (0UL) /*!< Position of EVENTS_EPDATA field. */
#define USBD_EVENTS_EPDATA_EVENTS_EPDATA_Msk                                                       \
  (0x1UL << USBD_EVENTS_EPDATA_EVENTS_EPDATA_Pos)           /*!< Bit mask of EVENTS_EPDATA field. */
#define USBD_EVENTS_EPDATA_EVENTS_EPDATA_NotGenerated (0UL) /*!< Event not generated */
#define USBD_EVENTS_EPDATA_EVENTS_EPDATA_Generated    (1UL) /*!< Event generated */

/* Register: USBD_SHORTS */
/* Description: Shortcuts between local events and tasks */

/* Bit 4 : Shortcut between event ENDEPOUT[0] and task EP0RCVOUT */
#define USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Pos           (4UL) /*!< Position of ENDEPOUT0_EP0RCVOUT field. */
#define USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Msk                                                        \
  (0x1UL << USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Pos) /*!< Bit mask of ENDEPOUT0_EP0RCVOUT field. */
#define USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between event ENDEPOUT[0] and task EP0STATUS */
#define USBD_SHORTS_ENDEPOUT0_EP0STATUS_Pos      (3UL) /*!< Position of ENDEPOUT0_EP0STATUS field. */
#define USBD_SHORTS_ENDEPOUT0_EP0STATUS_Msk                                                        \
  (0x1UL << USBD_SHORTS_ENDEPOUT0_EP0STATUS_Pos) /*!< Bit mask of ENDEPOUT0_EP0STATUS field. */
#define USBD_SHORTS_ENDEPOUT0_EP0STATUS_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_ENDEPOUT0_EP0STATUS_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between event EP0DATADONE and task EP0STATUS */
#define USBD_SHORTS_EP0DATADONE_EP0STATUS_Pos    (2UL) /*!< Position of EP0DATADONE_EP0STATUS field. */
#define USBD_SHORTS_EP0DATADONE_EP0STATUS_Msk                                                      \
  (0x1UL << USBD_SHORTS_EP0DATADONE_EP0STATUS_Pos) /*!< Bit mask of EP0DATADONE_EP0STATUS field. */
#define USBD_SHORTS_EP0DATADONE_EP0STATUS_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_EP0DATADONE_EP0STATUS_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between event EP0DATADONE and task STARTEPOUT[0] */
#define USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Pos                                                    \
  (1UL) /*!< Position of EP0DATADONE_STARTEPOUT0 field. */
#define USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Msk                                                    \
  (0x1UL                                                                                           \
   << USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Pos) /*!< Bit mask of EP0DATADONE_STARTEPOUT0 field. */
#define USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Enabled  (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between event EP0DATADONE and task STARTEPIN[0] */
#define USBD_SHORTS_EP0DATADONE_STARTEPIN0_Pos                                                     \
  (0UL) /*!< Position of EP0DATADONE_STARTEPIN0 field. */
#define USBD_SHORTS_EP0DATADONE_STARTEPIN0_Msk                                                     \
  (0x1UL                                                                                           \
   << USBD_SHORTS_EP0DATADONE_STARTEPIN0_Pos) /*!< Bit mask of EP0DATADONE_STARTEPIN0 field. */
#define USBD_SHORTS_EP0DATADONE_STARTEPIN0_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_EP0DATADONE_STARTEPIN0_Enabled  (1UL) /*!< Enable shortcut */

/* Register: USBD_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 24 : Enable or disable interrupt for event EPDATA */
#define USBD_INTEN_EPDATA_Pos                       (24UL) /*!< Position of EPDATA field. */
#define USBD_INTEN_EPDATA_Msk                       (0x1UL << USBD_INTEN_EPDATA_Pos) /*!< Bit mask of EPDATA field. */
#define USBD_INTEN_EPDATA_Disabled                  (0UL)                            /*!< Disable */
#define USBD_INTEN_EPDATA_Enabled                   (1UL)                            /*!< Enable */

/* Bit 23 : Enable or disable interrupt for event EP0SETUP */
#define USBD_INTEN_EP0SETUP_Pos                     (23UL) /*!< Position of EP0SETUP field. */
#define USBD_INTEN_EP0SETUP_Msk                                                                    \
  (0x1UL << USBD_INTEN_EP0SETUP_Pos)       /*!< Bit mask of EP0SETUP field. */
#define USBD_INTEN_EP0SETUP_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_EP0SETUP_Enabled  (1UL) /*!< Enable */

/* Bit 22 : Enable or disable interrupt for event USBEVENT */
#define USBD_INTEN_USBEVENT_Pos      (22UL) /*!< Position of USBEVENT field. */
#define USBD_INTEN_USBEVENT_Msk                                                                    \
  (0x1UL << USBD_INTEN_USBEVENT_Pos)       /*!< Bit mask of USBEVENT field. */
#define USBD_INTEN_USBEVENT_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_USBEVENT_Enabled  (1UL) /*!< Enable */

/* Bit 21 : Enable or disable interrupt for event SOF */
#define USBD_INTEN_SOF_Pos           (21UL)                        /*!< Position of SOF field. */
#define USBD_INTEN_SOF_Msk           (0x1UL << USBD_INTEN_SOF_Pos) /*!< Bit mask of SOF field. */
#define USBD_INTEN_SOF_Disabled      (0UL)                         /*!< Disable */
#define USBD_INTEN_SOF_Enabled       (1UL)                         /*!< Enable */

/* Bit 20 : Enable or disable interrupt for event ENDISOOUT */
#define USBD_INTEN_ENDISOOUT_Pos     (20UL) /*!< Position of ENDISOOUT field. */
#define USBD_INTEN_ENDISOOUT_Msk                                                                   \
  (0x1UL << USBD_INTEN_ENDISOOUT_Pos)       /*!< Bit mask of ENDISOOUT field. */
#define USBD_INTEN_ENDISOOUT_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDISOOUT_Enabled  (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for event ENDEPOUT[7] */
#define USBD_INTEN_ENDEPOUT7_Pos      (19UL) /*!< Position of ENDEPOUT7 field. */
#define USBD_INTEN_ENDEPOUT7_Msk                                                                   \
  (0x1UL << USBD_INTEN_ENDEPOUT7_Pos)       /*!< Bit mask of ENDEPOUT7 field. */
#define USBD_INTEN_ENDEPOUT7_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT7_Enabled  (1UL) /*!< Enable */

/* Bit 18 : Enable or disable interrupt for event ENDEPOUT[6] */
#define USBD_INTEN_ENDEPOUT6_Pos      (18UL) /*!< Position of ENDEPOUT6 field. */
#define USBD_INTEN_ENDEPOUT6_Msk                                                                   \
  (0x1UL << USBD_INTEN_ENDEPOUT6_Pos)       /*!< Bit mask of ENDEPOUT6 field. */
#define USBD_INTEN_ENDEPOUT6_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT6_Enabled  (1UL) /*!< Enable */

/* Bit 17 : Enable or disable interrupt for event ENDEPOUT[5] */
#define USBD_INTEN_ENDEPOUT5_Pos      (17UL) /*!< Position of ENDEPOUT5 field. */
#define USBD_INTEN_ENDEPOUT5_Msk                                                                   \
  (0x1UL << USBD_INTEN_ENDEPOUT5_Pos)       /*!< Bit mask of ENDEPOUT5 field. */
#define USBD_INTEN_ENDEPOUT5_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT5_Enabled  (1UL) /*!< Enable */

/* Bit 16 : Enable or disable interrupt for event ENDEPOUT[4] */
#define USBD_INTEN_ENDEPOUT4_Pos      (16UL) /*!< Position of ENDEPOUT4 field. */
#define USBD_INTEN_ENDEPOUT4_Msk                                                                   \
  (0x1UL << USBD_INTEN_ENDEPOUT4_Pos)       /*!< Bit mask of ENDEPOUT4 field. */
#define USBD_INTEN_ENDEPOUT4_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT4_Enabled  (1UL) /*!< Enable */

/* Bit 15 : Enable or disable interrupt for event ENDEPOUT[3] */
#define USBD_INTEN_ENDEPOUT3_Pos      (15UL) /*!< Position of ENDEPOUT3 field. */
#define USBD_INTEN_ENDEPOUT3_Msk                                                                   \
  (0x1UL << USBD_INTEN_ENDEPOUT3_Pos)       /*!< Bit mask of ENDEPOUT3 field. */
#define USBD_INTEN_ENDEPOUT3_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT3_Enabled  (1UL) /*!< Enable */

/* Bit 14 : Enable or disable interrupt for event ENDEPOUT[2] */
#define USBD_INTEN_ENDEPOUT2_Pos      (14UL) /*!< Position of ENDEPOUT2 field. */
#define USBD_INTEN_ENDEPOUT2_Msk                                                                   \
  (0x1UL << USBD_INTEN_ENDEPOUT2_Pos)       /*!< Bit mask of ENDEPOUT2 field. */
#define USBD_INTEN_ENDEPOUT2_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT2_Enabled  (1UL) /*!< Enable */

/* Bit 13 : Enable or disable interrupt for event ENDEPOUT[1] */
#define USBD_INTEN_ENDEPOUT1_Pos      (13UL) /*!< Position of ENDEPOUT1 field. */
#define USBD_INTEN_ENDEPOUT1_Msk                                                                   \
  (0x1UL << USBD_INTEN_ENDEPOUT1_Pos)       /*!< Bit mask of ENDEPOUT1 field. */
#define USBD_INTEN_ENDEPOUT1_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT1_Enabled  (1UL) /*!< Enable */

/* Bit 12 : Enable or disable interrupt for event ENDEPOUT[0] */
#define USBD_INTEN_ENDEPOUT0_Pos      (12UL) /*!< Position of ENDEPOUT0 field. */
#define USBD_INTEN_ENDEPOUT0_Msk                                                                   \
  (0x1UL << USBD_INTEN_ENDEPOUT0_Pos)       /*!< Bit mask of ENDEPOUT0 field. */
#define USBD_INTEN_ENDEPOUT0_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT0_Enabled  (1UL) /*!< Enable */

/* Bit 11 : Enable or disable interrupt for event ENDISOIN */
#define USBD_INTEN_ENDISOIN_Pos       (11UL) /*!< Position of ENDISOIN field. */
#define USBD_INTEN_ENDISOIN_Msk                                                                    \
  (0x1UL << USBD_INTEN_ENDISOIN_Pos)       /*!< Bit mask of ENDISOIN field. */
#define USBD_INTEN_ENDISOIN_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDISOIN_Enabled  (1UL) /*!< Enable */

/* Bit 10 : Enable or disable interrupt for event EP0DATADONE */
#define USBD_INTEN_EP0DATADONE_Pos   (10UL) /*!< Position of EP0DATADONE field. */
#define USBD_INTEN_EP0DATADONE_Msk                                                                 \
  (0x1UL << USBD_INTEN_EP0DATADONE_Pos)       /*!< Bit mask of EP0DATADONE field. */
#define USBD_INTEN_EP0DATADONE_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_EP0DATADONE_Enabled  (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for event ENDEPIN[7] */
#define USBD_INTEN_ENDEPIN7_Pos         (9UL) /*!< Position of ENDEPIN7 field. */
#define USBD_INTEN_ENDEPIN7_Msk                                                                    \
  (0x1UL << USBD_INTEN_ENDEPIN7_Pos)       /*!< Bit mask of ENDEPIN7 field. */
#define USBD_INTEN_ENDEPIN7_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN7_Enabled  (1UL) /*!< Enable */

/* Bit 8 : Enable or disable interrupt for event ENDEPIN[6] */
#define USBD_INTEN_ENDEPIN6_Pos      (8UL) /*!< Position of ENDEPIN6 field. */
#define USBD_INTEN_ENDEPIN6_Msk                                                                    \
  (0x1UL << USBD_INTEN_ENDEPIN6_Pos)       /*!< Bit mask of ENDEPIN6 field. */
#define USBD_INTEN_ENDEPIN6_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN6_Enabled  (1UL) /*!< Enable */

/* Bit 7 : Enable or disable interrupt for event ENDEPIN[5] */
#define USBD_INTEN_ENDEPIN5_Pos      (7UL) /*!< Position of ENDEPIN5 field. */
#define USBD_INTEN_ENDEPIN5_Msk                                                                    \
  (0x1UL << USBD_INTEN_ENDEPIN5_Pos)       /*!< Bit mask of ENDEPIN5 field. */
#define USBD_INTEN_ENDEPIN5_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN5_Enabled  (1UL) /*!< Enable */

/* Bit 6 : Enable or disable interrupt for event ENDEPIN[4] */
#define USBD_INTEN_ENDEPIN4_Pos      (6UL) /*!< Position of ENDEPIN4 field. */
#define USBD_INTEN_ENDEPIN4_Msk                                                                    \
  (0x1UL << USBD_INTEN_ENDEPIN4_Pos)       /*!< Bit mask of ENDEPIN4 field. */
#define USBD_INTEN_ENDEPIN4_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN4_Enabled  (1UL) /*!< Enable */

/* Bit 5 : Enable or disable interrupt for event ENDEPIN[3] */
#define USBD_INTEN_ENDEPIN3_Pos      (5UL) /*!< Position of ENDEPIN3 field. */
#define USBD_INTEN_ENDEPIN3_Msk                                                                    \
  (0x1UL << USBD_INTEN_ENDEPIN3_Pos)       /*!< Bit mask of ENDEPIN3 field. */
#define USBD_INTEN_ENDEPIN3_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN3_Enabled  (1UL) /*!< Enable */

/* Bit 4 : Enable or disable interrupt for event ENDEPIN[2] */
#define USBD_INTEN_ENDEPIN2_Pos      (4UL) /*!< Position of ENDEPIN2 field. */
#define USBD_INTEN_ENDEPIN2_Msk                                                                    \
  (0x1UL << USBD_INTEN_ENDEPIN2_Pos)       /*!< Bit mask of ENDEPIN2 field. */
#define USBD_INTEN_ENDEPIN2_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN2_Enabled  (1UL) /*!< Enable */

/* Bit 3 : Enable or disable interrupt for event ENDEPIN[1] */
#define USBD_INTEN_ENDEPIN1_Pos      (3UL) /*!< Position of ENDEPIN1 field. */
#define USBD_INTEN_ENDEPIN1_Msk                                                                    \
  (0x1UL << USBD_INTEN_ENDEPIN1_Pos)       /*!< Bit mask of ENDEPIN1 field. */
#define USBD_INTEN_ENDEPIN1_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN1_Enabled  (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for event ENDEPIN[0] */
#define USBD_INTEN_ENDEPIN0_Pos      (2UL) /*!< Position of ENDEPIN0 field. */
#define USBD_INTEN_ENDEPIN0_Msk                                                                    \
  (0x1UL << USBD_INTEN_ENDEPIN0_Pos)       /*!< Bit mask of ENDEPIN0 field. */
#define USBD_INTEN_ENDEPIN0_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN0_Enabled  (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for event STARTED */
#define USBD_INTEN_STARTED_Pos       (1UL) /*!< Position of STARTED field. */
#define USBD_INTEN_STARTED_Msk       (0x1UL << USBD_INTEN_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define USBD_INTEN_STARTED_Disabled  (0UL)                             /*!< Disable */
#define USBD_INTEN_STARTED_Enabled   (1UL)                             /*!< Enable */

/* Bit 0 : Enable or disable interrupt for event USBRESET */
#define USBD_INTEN_USBRESET_Pos      (0UL) /*!< Position of USBRESET field. */
#define USBD_INTEN_USBRESET_Msk                                                                    \
  (0x1UL << USBD_INTEN_USBRESET_Pos)       /*!< Bit mask of USBRESET field. */
#define USBD_INTEN_USBRESET_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_USBRESET_Enabled  (1UL) /*!< Enable */

/* Register: USBD_INTENSET */
/* Description: Enable interrupt */

/* Bit 24 : Write '1' to enable interrupt for event EPDATA */
#define USBD_INTENSET_EPDATA_Pos     (24UL) /*!< Position of EPDATA field. */
#define USBD_INTENSET_EPDATA_Msk                                                                   \
  (0x1UL << USBD_INTENSET_EPDATA_Pos)       /*!< Bit mask of EPDATA field. */
#define USBD_INTENSET_EPDATA_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_EPDATA_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_EPDATA_Set      (1UL) /*!< Enable */

/* Bit 23 : Write '1' to enable interrupt for event EP0SETUP */
#define USBD_INTENSET_EP0SETUP_Pos    (23UL) /*!< Position of EP0SETUP field. */
#define USBD_INTENSET_EP0SETUP_Msk                                                                 \
  (0x1UL << USBD_INTENSET_EP0SETUP_Pos)       /*!< Bit mask of EP0SETUP field. */
#define USBD_INTENSET_EP0SETUP_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_EP0SETUP_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_EP0SETUP_Set      (1UL) /*!< Enable */

/* Bit 22 : Write '1' to enable interrupt for event USBEVENT */
#define USBD_INTENSET_USBEVENT_Pos      (22UL) /*!< Position of USBEVENT field. */
#define USBD_INTENSET_USBEVENT_Msk                                                                 \
  (0x1UL << USBD_INTENSET_USBEVENT_Pos)       /*!< Bit mask of USBEVENT field. */
#define USBD_INTENSET_USBEVENT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_USBEVENT_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_USBEVENT_Set      (1UL) /*!< Enable */

/* Bit 21 : Write '1' to enable interrupt for event SOF */
#define USBD_INTENSET_SOF_Pos           (21UL) /*!< Position of SOF field. */
#define USBD_INTENSET_SOF_Msk           (0x1UL << USBD_INTENSET_SOF_Pos) /*!< Bit mask of SOF field. */
#define USBD_INTENSET_SOF_Disabled      (0UL)                            /*!< Read: Disabled */
#define USBD_INTENSET_SOF_Enabled       (1UL)                            /*!< Read: Enabled */
#define USBD_INTENSET_SOF_Set           (1UL)                            /*!< Enable */

/* Bit 20 : Write '1' to enable interrupt for event ENDISOOUT */
#define USBD_INTENSET_ENDISOOUT_Pos     (20UL) /*!< Position of ENDISOOUT field. */
#define USBD_INTENSET_ENDISOOUT_Msk                                                                \
  (0x1UL << USBD_INTENSET_ENDISOOUT_Pos)       /*!< Bit mask of ENDISOOUT field. */
#define USBD_INTENSET_ENDISOOUT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDISOOUT_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDISOOUT_Set      (1UL) /*!< Enable */

/* Bit 19 : Write '1' to enable interrupt for event ENDEPOUT[7] */
#define USBD_INTENSET_ENDEPOUT7_Pos      (19UL) /*!< Position of ENDEPOUT7 field. */
#define USBD_INTENSET_ENDEPOUT7_Msk                                                                \
  (0x1UL << USBD_INTENSET_ENDEPOUT7_Pos)       /*!< Bit mask of ENDEPOUT7 field. */
#define USBD_INTENSET_ENDEPOUT7_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT7_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT7_Set      (1UL) /*!< Enable */

/* Bit 18 : Write '1' to enable interrupt for event ENDEPOUT[6] */
#define USBD_INTENSET_ENDEPOUT6_Pos      (18UL) /*!< Position of ENDEPOUT6 field. */
#define USBD_INTENSET_ENDEPOUT6_Msk                                                                \
  (0x1UL << USBD_INTENSET_ENDEPOUT6_Pos)       /*!< Bit mask of ENDEPOUT6 field. */
#define USBD_INTENSET_ENDEPOUT6_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT6_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT6_Set      (1UL) /*!< Enable */

/* Bit 17 : Write '1' to enable interrupt for event ENDEPOUT[5] */
#define USBD_INTENSET_ENDEPOUT5_Pos      (17UL) /*!< Position of ENDEPOUT5 field. */
#define USBD_INTENSET_ENDEPOUT5_Msk                                                                \
  (0x1UL << USBD_INTENSET_ENDEPOUT5_Pos)       /*!< Bit mask of ENDEPOUT5 field. */
#define USBD_INTENSET_ENDEPOUT5_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT5_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT5_Set      (1UL) /*!< Enable */

/* Bit 16 : Write '1' to enable interrupt for event ENDEPOUT[4] */
#define USBD_INTENSET_ENDEPOUT4_Pos      (16UL) /*!< Position of ENDEPOUT4 field. */
#define USBD_INTENSET_ENDEPOUT4_Msk                                                                \
  (0x1UL << USBD_INTENSET_ENDEPOUT4_Pos)       /*!< Bit mask of ENDEPOUT4 field. */
#define USBD_INTENSET_ENDEPOUT4_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT4_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT4_Set      (1UL) /*!< Enable */

/* Bit 15 : Write '1' to enable interrupt for event ENDEPOUT[3] */
#define USBD_INTENSET_ENDEPOUT3_Pos      (15UL) /*!< Position of ENDEPOUT3 field. */
#define USBD_INTENSET_ENDEPOUT3_Msk                                                                \
  (0x1UL << USBD_INTENSET_ENDEPOUT3_Pos)       /*!< Bit mask of ENDEPOUT3 field. */
#define USBD_INTENSET_ENDEPOUT3_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT3_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT3_Set      (1UL) /*!< Enable */

/* Bit 14 : Write '1' to enable interrupt for event ENDEPOUT[2] */
#define USBD_INTENSET_ENDEPOUT2_Pos      (14UL) /*!< Position of ENDEPOUT2 field. */
#define USBD_INTENSET_ENDEPOUT2_Msk                                                                \
  (0x1UL << USBD_INTENSET_ENDEPOUT2_Pos)       /*!< Bit mask of ENDEPOUT2 field. */
#define USBD_INTENSET_ENDEPOUT2_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT2_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT2_Set      (1UL) /*!< Enable */

/* Bit 13 : Write '1' to enable interrupt for event ENDEPOUT[1] */
#define USBD_INTENSET_ENDEPOUT1_Pos      (13UL) /*!< Position of ENDEPOUT1 field. */
#define USBD_INTENSET_ENDEPOUT1_Msk                                                                \
  (0x1UL << USBD_INTENSET_ENDEPOUT1_Pos)       /*!< Bit mask of ENDEPOUT1 field. */
#define USBD_INTENSET_ENDEPOUT1_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT1_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT1_Set      (1UL) /*!< Enable */

/* Bit 12 : Write '1' to enable interrupt for event ENDEPOUT[0] */
#define USBD_INTENSET_ENDEPOUT0_Pos      (12UL) /*!< Position of ENDEPOUT0 field. */
#define USBD_INTENSET_ENDEPOUT0_Msk                                                                \
  (0x1UL << USBD_INTENSET_ENDEPOUT0_Pos)       /*!< Bit mask of ENDEPOUT0 field. */
#define USBD_INTENSET_ENDEPOUT0_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT0_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT0_Set      (1UL) /*!< Enable */

/* Bit 11 : Write '1' to enable interrupt for event ENDISOIN */
#define USBD_INTENSET_ENDISOIN_Pos       (11UL) /*!< Position of ENDISOIN field. */
#define USBD_INTENSET_ENDISOIN_Msk                                                                 \
  (0x1UL << USBD_INTENSET_ENDISOIN_Pos)       /*!< Bit mask of ENDISOIN field. */
#define USBD_INTENSET_ENDISOIN_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDISOIN_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDISOIN_Set      (1UL) /*!< Enable */

/* Bit 10 : Write '1' to enable interrupt for event EP0DATADONE */
#define USBD_INTENSET_EP0DATADONE_Pos   (10UL) /*!< Position of EP0DATADONE field. */
#define USBD_INTENSET_EP0DATADONE_Msk                                                              \
  (0x1UL << USBD_INTENSET_EP0DATADONE_Pos)       /*!< Bit mask of EP0DATADONE field. */
#define USBD_INTENSET_EP0DATADONE_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_EP0DATADONE_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_EP0DATADONE_Set      (1UL) /*!< Enable */

/* Bit 9 : Write '1' to enable interrupt for event ENDEPIN[7] */
#define USBD_INTENSET_ENDEPIN7_Pos         (9UL) /*!< Position of ENDEPIN7 field. */
#define USBD_INTENSET_ENDEPIN7_Msk                                                                 \
  (0x1UL << USBD_INTENSET_ENDEPIN7_Pos)       /*!< Bit mask of ENDEPIN7 field. */
#define USBD_INTENSET_ENDEPIN7_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN7_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN7_Set      (1UL) /*!< Enable */

/* Bit 8 : Write '1' to enable interrupt for event ENDEPIN[6] */
#define USBD_INTENSET_ENDEPIN6_Pos      (8UL) /*!< Position of ENDEPIN6 field. */
#define USBD_INTENSET_ENDEPIN6_Msk                                                                 \
  (0x1UL << USBD_INTENSET_ENDEPIN6_Pos)       /*!< Bit mask of ENDEPIN6 field. */
#define USBD_INTENSET_ENDEPIN6_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN6_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN6_Set      (1UL) /*!< Enable */

/* Bit 7 : Write '1' to enable interrupt for event ENDEPIN[5] */
#define USBD_INTENSET_ENDEPIN5_Pos      (7UL) /*!< Position of ENDEPIN5 field. */
#define USBD_INTENSET_ENDEPIN5_Msk                                                                 \
  (0x1UL << USBD_INTENSET_ENDEPIN5_Pos)       /*!< Bit mask of ENDEPIN5 field. */
#define USBD_INTENSET_ENDEPIN5_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN5_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN5_Set      (1UL) /*!< Enable */

/* Bit 6 : Write '1' to enable interrupt for event ENDEPIN[4] */
#define USBD_INTENSET_ENDEPIN4_Pos      (6UL) /*!< Position of ENDEPIN4 field. */
#define USBD_INTENSET_ENDEPIN4_Msk                                                                 \
  (0x1UL << USBD_INTENSET_ENDEPIN4_Pos)       /*!< Bit mask of ENDEPIN4 field. */
#define USBD_INTENSET_ENDEPIN4_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN4_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN4_Set      (1UL) /*!< Enable */

/* Bit 5 : Write '1' to enable interrupt for event ENDEPIN[3] */
#define USBD_INTENSET_ENDEPIN3_Pos      (5UL) /*!< Position of ENDEPIN3 field. */
#define USBD_INTENSET_ENDEPIN3_Msk                                                                 \
  (0x1UL << USBD_INTENSET_ENDEPIN3_Pos)       /*!< Bit mask of ENDEPIN3 field. */
#define USBD_INTENSET_ENDEPIN3_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN3_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN3_Set      (1UL) /*!< Enable */

/* Bit 4 : Write '1' to enable interrupt for event ENDEPIN[2] */
#define USBD_INTENSET_ENDEPIN2_Pos      (4UL) /*!< Position of ENDEPIN2 field. */
#define USBD_INTENSET_ENDEPIN2_Msk                                                                 \
  (0x1UL << USBD_INTENSET_ENDEPIN2_Pos)       /*!< Bit mask of ENDEPIN2 field. */
#define USBD_INTENSET_ENDEPIN2_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN2_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN2_Set      (1UL) /*!< Enable */

/* Bit 3 : Write '1' to enable interrupt for event ENDEPIN[1] */
#define USBD_INTENSET_ENDEPIN1_Pos      (3UL) /*!< Position of ENDEPIN1 field. */
#define USBD_INTENSET_ENDEPIN1_Msk                                                                 \
  (0x1UL << USBD_INTENSET_ENDEPIN1_Pos)       /*!< Bit mask of ENDEPIN1 field. */
#define USBD_INTENSET_ENDEPIN1_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN1_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN1_Set      (1UL) /*!< Enable */

/* Bit 2 : Write '1' to enable interrupt for event ENDEPIN[0] */
#define USBD_INTENSET_ENDEPIN0_Pos      (2UL) /*!< Position of ENDEPIN0 field. */
#define USBD_INTENSET_ENDEPIN0_Msk                                                                 \
  (0x1UL << USBD_INTENSET_ENDEPIN0_Pos)       /*!< Bit mask of ENDEPIN0 field. */
#define USBD_INTENSET_ENDEPIN0_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN0_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN0_Set      (1UL) /*!< Enable */

/* Bit 1 : Write '1' to enable interrupt for event STARTED */
#define USBD_INTENSET_STARTED_Pos       (1UL) /*!< Position of STARTED field. */
#define USBD_INTENSET_STARTED_Msk                                                                  \
  (0x1UL << USBD_INTENSET_STARTED_Pos)       /*!< Bit mask of STARTED field. */
#define USBD_INTENSET_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_STARTED_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_STARTED_Set      (1UL) /*!< Enable */

/* Bit 0 : Write '1' to enable interrupt for event USBRESET */
#define USBD_INTENSET_USBRESET_Pos     (0UL) /*!< Position of USBRESET field. */
#define USBD_INTENSET_USBRESET_Msk                                                                 \
  (0x1UL << USBD_INTENSET_USBRESET_Pos)       /*!< Bit mask of USBRESET field. */
#define USBD_INTENSET_USBRESET_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_USBRESET_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_USBRESET_Set      (1UL) /*!< Enable */

/* Register: USBD_INTENCLR */
/* Description: Disable interrupt */

/* Bit 24 : Write '1' to disable interrupt for event EPDATA */
#define USBD_INTENCLR_EPDATA_Pos        (24UL) /*!< Position of EPDATA field. */
#define USBD_INTENCLR_EPDATA_Msk                                                                   \
  (0x1UL << USBD_INTENCLR_EPDATA_Pos)       /*!< Bit mask of EPDATA field. */
#define USBD_INTENCLR_EPDATA_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_EPDATA_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_EPDATA_Clear    (1UL) /*!< Disable */

/* Bit 23 : Write '1' to disable interrupt for event EP0SETUP */
#define USBD_INTENCLR_EP0SETUP_Pos    (23UL) /*!< Position of EP0SETUP field. */
#define USBD_INTENCLR_EP0SETUP_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_EP0SETUP_Pos)       /*!< Bit mask of EP0SETUP field. */
#define USBD_INTENCLR_EP0SETUP_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_EP0SETUP_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_EP0SETUP_Clear    (1UL) /*!< Disable */

/* Bit 22 : Write '1' to disable interrupt for event USBEVENT */
#define USBD_INTENCLR_USBEVENT_Pos      (22UL) /*!< Position of USBEVENT field. */
#define USBD_INTENCLR_USBEVENT_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_USBEVENT_Pos)       /*!< Bit mask of USBEVENT field. */
#define USBD_INTENCLR_USBEVENT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_USBEVENT_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_USBEVENT_Clear    (1UL) /*!< Disable */

/* Bit 21 : Write '1' to disable interrupt for event SOF */
#define USBD_INTENCLR_SOF_Pos           (21UL) /*!< Position of SOF field. */
#define USBD_INTENCLR_SOF_Msk           (0x1UL << USBD_INTENCLR_SOF_Pos) /*!< Bit mask of SOF field. */
#define USBD_INTENCLR_SOF_Disabled      (0UL)                            /*!< Read: Disabled */
#define USBD_INTENCLR_SOF_Enabled       (1UL)                            /*!< Read: Enabled */
#define USBD_INTENCLR_SOF_Clear         (1UL)                            /*!< Disable */

/* Bit 20 : Write '1' to disable interrupt for event ENDISOOUT */
#define USBD_INTENCLR_ENDISOOUT_Pos     (20UL) /*!< Position of ENDISOOUT field. */
#define USBD_INTENCLR_ENDISOOUT_Msk                                                                \
  (0x1UL << USBD_INTENCLR_ENDISOOUT_Pos)       /*!< Bit mask of ENDISOOUT field. */
#define USBD_INTENCLR_ENDISOOUT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDISOOUT_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDISOOUT_Clear    (1UL) /*!< Disable */

/* Bit 19 : Write '1' to disable interrupt for event ENDEPOUT[7] */
#define USBD_INTENCLR_ENDEPOUT7_Pos      (19UL) /*!< Position of ENDEPOUT7 field. */
#define USBD_INTENCLR_ENDEPOUT7_Msk                                                                \
  (0x1UL << USBD_INTENCLR_ENDEPOUT7_Pos)       /*!< Bit mask of ENDEPOUT7 field. */
#define USBD_INTENCLR_ENDEPOUT7_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT7_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT7_Clear    (1UL) /*!< Disable */

/* Bit 18 : Write '1' to disable interrupt for event ENDEPOUT[6] */
#define USBD_INTENCLR_ENDEPOUT6_Pos      (18UL) /*!< Position of ENDEPOUT6 field. */
#define USBD_INTENCLR_ENDEPOUT6_Msk                                                                \
  (0x1UL << USBD_INTENCLR_ENDEPOUT6_Pos)       /*!< Bit mask of ENDEPOUT6 field. */
#define USBD_INTENCLR_ENDEPOUT6_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT6_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT6_Clear    (1UL) /*!< Disable */

/* Bit 17 : Write '1' to disable interrupt for event ENDEPOUT[5] */
#define USBD_INTENCLR_ENDEPOUT5_Pos      (17UL) /*!< Position of ENDEPOUT5 field. */
#define USBD_INTENCLR_ENDEPOUT5_Msk                                                                \
  (0x1UL << USBD_INTENCLR_ENDEPOUT5_Pos)       /*!< Bit mask of ENDEPOUT5 field. */
#define USBD_INTENCLR_ENDEPOUT5_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT5_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT5_Clear    (1UL) /*!< Disable */

/* Bit 16 : Write '1' to disable interrupt for event ENDEPOUT[4] */
#define USBD_INTENCLR_ENDEPOUT4_Pos      (16UL) /*!< Position of ENDEPOUT4 field. */
#define USBD_INTENCLR_ENDEPOUT4_Msk                                                                \
  (0x1UL << USBD_INTENCLR_ENDEPOUT4_Pos)       /*!< Bit mask of ENDEPOUT4 field. */
#define USBD_INTENCLR_ENDEPOUT4_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT4_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT4_Clear    (1UL) /*!< Disable */

/* Bit 15 : Write '1' to disable interrupt for event ENDEPOUT[3] */
#define USBD_INTENCLR_ENDEPOUT3_Pos      (15UL) /*!< Position of ENDEPOUT3 field. */
#define USBD_INTENCLR_ENDEPOUT3_Msk                                                                \
  (0x1UL << USBD_INTENCLR_ENDEPOUT3_Pos)       /*!< Bit mask of ENDEPOUT3 field. */
#define USBD_INTENCLR_ENDEPOUT3_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT3_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT3_Clear    (1UL) /*!< Disable */

/* Bit 14 : Write '1' to disable interrupt for event ENDEPOUT[2] */
#define USBD_INTENCLR_ENDEPOUT2_Pos      (14UL) /*!< Position of ENDEPOUT2 field. */
#define USBD_INTENCLR_ENDEPOUT2_Msk                                                                \
  (0x1UL << USBD_INTENCLR_ENDEPOUT2_Pos)       /*!< Bit mask of ENDEPOUT2 field. */
#define USBD_INTENCLR_ENDEPOUT2_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT2_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT2_Clear    (1UL) /*!< Disable */

/* Bit 13 : Write '1' to disable interrupt for event ENDEPOUT[1] */
#define USBD_INTENCLR_ENDEPOUT1_Pos      (13UL) /*!< Position of ENDEPOUT1 field. */
#define USBD_INTENCLR_ENDEPOUT1_Msk                                                                \
  (0x1UL << USBD_INTENCLR_ENDEPOUT1_Pos)       /*!< Bit mask of ENDEPOUT1 field. */
#define USBD_INTENCLR_ENDEPOUT1_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT1_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT1_Clear    (1UL) /*!< Disable */

/* Bit 12 : Write '1' to disable interrupt for event ENDEPOUT[0] */
#define USBD_INTENCLR_ENDEPOUT0_Pos      (12UL) /*!< Position of ENDEPOUT0 field. */
#define USBD_INTENCLR_ENDEPOUT0_Msk                                                                \
  (0x1UL << USBD_INTENCLR_ENDEPOUT0_Pos)       /*!< Bit mask of ENDEPOUT0 field. */
#define USBD_INTENCLR_ENDEPOUT0_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT0_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT0_Clear    (1UL) /*!< Disable */

/* Bit 11 : Write '1' to disable interrupt for event ENDISOIN */
#define USBD_INTENCLR_ENDISOIN_Pos       (11UL) /*!< Position of ENDISOIN field. */
#define USBD_INTENCLR_ENDISOIN_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_ENDISOIN_Pos)       /*!< Bit mask of ENDISOIN field. */
#define USBD_INTENCLR_ENDISOIN_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDISOIN_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDISOIN_Clear    (1UL) /*!< Disable */

/* Bit 10 : Write '1' to disable interrupt for event EP0DATADONE */
#define USBD_INTENCLR_EP0DATADONE_Pos   (10UL) /*!< Position of EP0DATADONE field. */
#define USBD_INTENCLR_EP0DATADONE_Msk                                                              \
  (0x1UL << USBD_INTENCLR_EP0DATADONE_Pos)       /*!< Bit mask of EP0DATADONE field. */
#define USBD_INTENCLR_EP0DATADONE_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_EP0DATADONE_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_EP0DATADONE_Clear    (1UL) /*!< Disable */

/* Bit 9 : Write '1' to disable interrupt for event ENDEPIN[7] */
#define USBD_INTENCLR_ENDEPIN7_Pos         (9UL) /*!< Position of ENDEPIN7 field. */
#define USBD_INTENCLR_ENDEPIN7_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_ENDEPIN7_Pos)       /*!< Bit mask of ENDEPIN7 field. */
#define USBD_INTENCLR_ENDEPIN7_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN7_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN7_Clear    (1UL) /*!< Disable */

/* Bit 8 : Write '1' to disable interrupt for event ENDEPIN[6] */
#define USBD_INTENCLR_ENDEPIN6_Pos      (8UL) /*!< Position of ENDEPIN6 field. */
#define USBD_INTENCLR_ENDEPIN6_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_ENDEPIN6_Pos)       /*!< Bit mask of ENDEPIN6 field. */
#define USBD_INTENCLR_ENDEPIN6_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN6_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN6_Clear    (1UL) /*!< Disable */

/* Bit 7 : Write '1' to disable interrupt for event ENDEPIN[5] */
#define USBD_INTENCLR_ENDEPIN5_Pos      (7UL) /*!< Position of ENDEPIN5 field. */
#define USBD_INTENCLR_ENDEPIN5_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_ENDEPIN5_Pos)       /*!< Bit mask of ENDEPIN5 field. */
#define USBD_INTENCLR_ENDEPIN5_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN5_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN5_Clear    (1UL) /*!< Disable */

/* Bit 6 : Write '1' to disable interrupt for event ENDEPIN[4] */
#define USBD_INTENCLR_ENDEPIN4_Pos      (6UL) /*!< Position of ENDEPIN4 field. */
#define USBD_INTENCLR_ENDEPIN4_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_ENDEPIN4_Pos)       /*!< Bit mask of ENDEPIN4 field. */
#define USBD_INTENCLR_ENDEPIN4_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN4_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN4_Clear    (1UL) /*!< Disable */

/* Bit 5 : Write '1' to disable interrupt for event ENDEPIN[3] */
#define USBD_INTENCLR_ENDEPIN3_Pos      (5UL) /*!< Position of ENDEPIN3 field. */
#define USBD_INTENCLR_ENDEPIN3_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_ENDEPIN3_Pos)       /*!< Bit mask of ENDEPIN3 field. */
#define USBD_INTENCLR_ENDEPIN3_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN3_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN3_Clear    (1UL) /*!< Disable */

/* Bit 4 : Write '1' to disable interrupt for event ENDEPIN[2] */
#define USBD_INTENCLR_ENDEPIN2_Pos      (4UL) /*!< Position of ENDEPIN2 field. */
#define USBD_INTENCLR_ENDEPIN2_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_ENDEPIN2_Pos)       /*!< Bit mask of ENDEPIN2 field. */
#define USBD_INTENCLR_ENDEPIN2_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN2_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN2_Clear    (1UL) /*!< Disable */

/* Bit 3 : Write '1' to disable interrupt for event ENDEPIN[1] */
#define USBD_INTENCLR_ENDEPIN1_Pos      (3UL) /*!< Position of ENDEPIN1 field. */
#define USBD_INTENCLR_ENDEPIN1_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_ENDEPIN1_Pos)       /*!< Bit mask of ENDEPIN1 field. */
#define USBD_INTENCLR_ENDEPIN1_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN1_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN1_Clear    (1UL) /*!< Disable */

/* Bit 2 : Write '1' to disable interrupt for event ENDEPIN[0] */
#define USBD_INTENCLR_ENDEPIN0_Pos      (2UL) /*!< Position of ENDEPIN0 field. */
#define USBD_INTENCLR_ENDEPIN0_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_ENDEPIN0_Pos)       /*!< Bit mask of ENDEPIN0 field. */
#define USBD_INTENCLR_ENDEPIN0_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN0_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN0_Clear    (1UL) /*!< Disable */

/* Bit 1 : Write '1' to disable interrupt for event STARTED */
#define USBD_INTENCLR_STARTED_Pos       (1UL) /*!< Position of STARTED field. */
#define USBD_INTENCLR_STARTED_Msk                                                                  \
  (0x1UL << USBD_INTENCLR_STARTED_Pos)       /*!< Bit mask of STARTED field. */
#define USBD_INTENCLR_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_STARTED_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_STARTED_Clear    (1UL) /*!< Disable */

/* Bit 0 : Write '1' to disable interrupt for event USBRESET */
#define USBD_INTENCLR_USBRESET_Pos     (0UL) /*!< Position of USBRESET field. */
#define USBD_INTENCLR_USBRESET_Msk                                                                 \
  (0x1UL << USBD_INTENCLR_USBRESET_Pos)       /*!< Bit mask of USBRESET field. */
#define USBD_INTENCLR_USBRESET_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_USBRESET_Enabled  (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_USBRESET_Clear    (1UL) /*!< Disable */

/* Register: USBD_EVENTCAUSE */
/* Description: Details on what caused the USBEVENT event */

/* Bit 11 : USB device is ready for normal operation. Write '1' to clear. */
#define USBD_EVENTCAUSE_READY_Pos       (11UL) /*!< Position of READY field. */
#define USBD_EVENTCAUSE_READY_Msk                                                                  \
  (0x1UL << USBD_EVENTCAUSE_READY_Pos) /*!< Bit mask of READY field. */
#define USBD_EVENTCAUSE_READY_NotDetected                                                          \
  (0UL) /*!< USBEVENT was not issued due to USBD peripheral ready */
#define USBD_EVENTCAUSE_READY_Ready      (1UL) /*!< USBD peripheral is ready */

/* Bit 10 : USB MAC has been woken up and operational. Write '1' to clear. */
#define USBD_EVENTCAUSE_USBWUALLOWED_Pos (10UL) /*!< Position of USBWUALLOWED field. */
#define USBD_EVENTCAUSE_USBWUALLOWED_Msk                                                           \
  (0x1UL << USBD_EVENTCAUSE_USBWUALLOWED_Pos)         /*!< Bit mask of USBWUALLOWED field. */
#define USBD_EVENTCAUSE_USBWUALLOWED_NotAllowed (0UL) /*!< Wake up not allowed */
#define USBD_EVENTCAUSE_USBWUALLOWED_Allowed    (1UL) /*!< Wake up allowed */

/* Bit 9 : Signals that a RESUME condition (K state or activity restart) has been detected on USB lines. Write '1' to clear. */
#define USBD_EVENTCAUSE_RESUME_Pos              (9UL) /*!< Position of RESUME field. */
#define USBD_EVENTCAUSE_RESUME_Msk                                                                 \
  (0x1UL << USBD_EVENTCAUSE_RESUME_Pos)          /*!< Bit mask of RESUME field. */
#define USBD_EVENTCAUSE_RESUME_NotDetected (0UL) /*!< Resume not detected */
#define USBD_EVENTCAUSE_RESUME_Detected    (1UL) /*!< Resume detected */

/* Bit 8 : Signals that USB lines have been idle long enough for the device to enter suspend. Write '1' to clear. */
#define USBD_EVENTCAUSE_SUSPEND_Pos        (8UL) /*!< Position of SUSPEND field. */
#define USBD_EVENTCAUSE_SUSPEND_Msk                                                                \
  (0x1UL << USBD_EVENTCAUSE_SUSPEND_Pos)          /*!< Bit mask of SUSPEND field. */
#define USBD_EVENTCAUSE_SUSPEND_NotDetected (0UL) /*!< Suspend not detected */
#define USBD_EVENTCAUSE_SUSPEND_Detected    (1UL) /*!< Suspend detected */

/* Bit 0 : CRC error was detected on isochronous OUT endpoint 8. Write '1' to clear. */
#define USBD_EVENTCAUSE_ISOOUTCRC_Pos       (0UL) /*!< Position of ISOOUTCRC field. */
#define USBD_EVENTCAUSE_ISOOUTCRC_Msk                                                              \
  (0x1UL << USBD_EVENTCAUSE_ISOOUTCRC_Pos)          /*!< Bit mask of ISOOUTCRC field. */
#define USBD_EVENTCAUSE_ISOOUTCRC_NotDetected (0UL) /*!< No error detected */
#define USBD_EVENTCAUSE_ISOOUTCRC_Detected    (1UL) /*!< Error detected */

/* Register: USBD_HALTED_EPIN */
/* Description: Description collection: IN endpoint halted status. Can be used as is as response to a GetStatus() request to endpoint. */

/* Bits 15..0 : IN endpoint halted status. Can be used as is as response to a GetStatus() request to endpoint. */
#define USBD_HALTED_EPIN_GETSTATUS_Pos        (0UL) /*!< Position of GETSTATUS field. */
#define USBD_HALTED_EPIN_GETSTATUS_Msk                                                             \
  (0xFFFFUL << USBD_HALTED_EPIN_GETSTATUS_Pos)     /*!< Bit mask of GETSTATUS field. */
#define USBD_HALTED_EPIN_GETSTATUS_NotHalted (0UL) /*!< Endpoint is not halted */
#define USBD_HALTED_EPIN_GETSTATUS_Halted    (1UL) /*!< Endpoint is halted */

/* Register: USBD_HALTED_EPOUT */
/* Description: Description collection: OUT endpoint halted status. Can be used as is as response to a GetStatus() request to endpoint. */

/* Bits 15..0 : OUT endpoint halted status. Can be used as is as response to a GetStatus() request to endpoint. */
#define USBD_HALTED_EPOUT_GETSTATUS_Pos      (0UL) /*!< Position of GETSTATUS field. */
#define USBD_HALTED_EPOUT_GETSTATUS_Msk                                                            \
  (0xFFFFUL << USBD_HALTED_EPOUT_GETSTATUS_Pos)     /*!< Bit mask of GETSTATUS field. */
#define USBD_HALTED_EPOUT_GETSTATUS_NotHalted (0UL) /*!< Endpoint is not halted */
#define USBD_HALTED_EPOUT_GETSTATUS_Halted    (1UL) /*!< Endpoint is halted */

/* Register: USBD_EPSTATUS */
/* Description: Provides information on which endpoint's EasyDMA registers have been captured */

/* Bit 24 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT8_Pos              (24UL) /*!< Position of EPOUT8 field. */
#define USBD_EPSTATUS_EPOUT8_Msk                                                                   \
  (0x1UL << USBD_EPSTATUS_EPOUT8_Pos) /*!< Bit mask of EPOUT8 field. */
#define USBD_EPSTATUS_EPOUT8_NoData                                                                \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT8_DataDone                                                              \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 23 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT7_Pos (23UL) /*!< Position of EPOUT7 field. */
#define USBD_EPSTATUS_EPOUT7_Msk                                                                   \
  (0x1UL << USBD_EPSTATUS_EPOUT7_Pos) /*!< Bit mask of EPOUT7 field. */
#define USBD_EPSTATUS_EPOUT7_NoData                                                                \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT7_DataDone                                                              \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 22 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT6_Pos (22UL) /*!< Position of EPOUT6 field. */
#define USBD_EPSTATUS_EPOUT6_Msk                                                                   \
  (0x1UL << USBD_EPSTATUS_EPOUT6_Pos) /*!< Bit mask of EPOUT6 field. */
#define USBD_EPSTATUS_EPOUT6_NoData                                                                \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT6_DataDone                                                              \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 21 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT5_Pos (21UL) /*!< Position of EPOUT5 field. */
#define USBD_EPSTATUS_EPOUT5_Msk                                                                   \
  (0x1UL << USBD_EPSTATUS_EPOUT5_Pos) /*!< Bit mask of EPOUT5 field. */
#define USBD_EPSTATUS_EPOUT5_NoData                                                                \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT5_DataDone                                                              \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 20 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT4_Pos (20UL) /*!< Position of EPOUT4 field. */
#define USBD_EPSTATUS_EPOUT4_Msk                                                                   \
  (0x1UL << USBD_EPSTATUS_EPOUT4_Pos) /*!< Bit mask of EPOUT4 field. */
#define USBD_EPSTATUS_EPOUT4_NoData                                                                \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT4_DataDone                                                              \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 19 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT3_Pos (19UL) /*!< Position of EPOUT3 field. */
#define USBD_EPSTATUS_EPOUT3_Msk                                                                   \
  (0x1UL << USBD_EPSTATUS_EPOUT3_Pos) /*!< Bit mask of EPOUT3 field. */
#define USBD_EPSTATUS_EPOUT3_NoData                                                                \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT3_DataDone                                                              \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 18 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT2_Pos (18UL) /*!< Position of EPOUT2 field. */
#define USBD_EPSTATUS_EPOUT2_Msk                                                                   \
  (0x1UL << USBD_EPSTATUS_EPOUT2_Pos) /*!< Bit mask of EPOUT2 field. */
#define USBD_EPSTATUS_EPOUT2_NoData                                                                \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT2_DataDone                                                              \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 17 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT1_Pos (17UL) /*!< Position of EPOUT1 field. */
#define USBD_EPSTATUS_EPOUT1_Msk                                                                   \
  (0x1UL << USBD_EPSTATUS_EPOUT1_Pos) /*!< Bit mask of EPOUT1 field. */
#define USBD_EPSTATUS_EPOUT1_NoData                                                                \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT1_DataDone                                                              \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 16 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT0_Pos (16UL) /*!< Position of EPOUT0 field. */
#define USBD_EPSTATUS_EPOUT0_Msk                                                                   \
  (0x1UL << USBD_EPSTATUS_EPOUT0_Pos) /*!< Bit mask of EPOUT0 field. */
#define USBD_EPSTATUS_EPOUT0_NoData                                                                \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT0_DataDone                                                              \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 8 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN8_Pos (8UL)                              /*!< Position of EPIN8 field. */
#define USBD_EPSTATUS_EPIN8_Msk (0x1UL << USBD_EPSTATUS_EPIN8_Pos) /*!< Bit mask of EPIN8 field. */
#define USBD_EPSTATUS_EPIN8_NoData                                                                 \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN8_DataDone                                                               \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 7 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN7_Pos (7UL)                              /*!< Position of EPIN7 field. */
#define USBD_EPSTATUS_EPIN7_Msk (0x1UL << USBD_EPSTATUS_EPIN7_Pos) /*!< Bit mask of EPIN7 field. */
#define USBD_EPSTATUS_EPIN7_NoData                                                                 \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN7_DataDone                                                               \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 6 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN6_Pos (6UL)                              /*!< Position of EPIN6 field. */
#define USBD_EPSTATUS_EPIN6_Msk (0x1UL << USBD_EPSTATUS_EPIN6_Pos) /*!< Bit mask of EPIN6 field. */
#define USBD_EPSTATUS_EPIN6_NoData                                                                 \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN6_DataDone                                                               \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 5 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN5_Pos (5UL)                              /*!< Position of EPIN5 field. */
#define USBD_EPSTATUS_EPIN5_Msk (0x1UL << USBD_EPSTATUS_EPIN5_Pos) /*!< Bit mask of EPIN5 field. */
#define USBD_EPSTATUS_EPIN5_NoData                                                                 \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN5_DataDone                                                               \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 4 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN4_Pos (4UL)                              /*!< Position of EPIN4 field. */
#define USBD_EPSTATUS_EPIN4_Msk (0x1UL << USBD_EPSTATUS_EPIN4_Pos) /*!< Bit mask of EPIN4 field. */
#define USBD_EPSTATUS_EPIN4_NoData                                                                 \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN4_DataDone                                                               \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 3 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN3_Pos (3UL)                              /*!< Position of EPIN3 field. */
#define USBD_EPSTATUS_EPIN3_Msk (0x1UL << USBD_EPSTATUS_EPIN3_Pos) /*!< Bit mask of EPIN3 field. */
#define USBD_EPSTATUS_EPIN3_NoData                                                                 \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN3_DataDone                                                               \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 2 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN2_Pos (2UL)                              /*!< Position of EPIN2 field. */
#define USBD_EPSTATUS_EPIN2_Msk (0x1UL << USBD_EPSTATUS_EPIN2_Pos) /*!< Bit mask of EPIN2 field. */
#define USBD_EPSTATUS_EPIN2_NoData                                                                 \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN2_DataDone                                                               \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 1 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN1_Pos (1UL)                              /*!< Position of EPIN1 field. */
#define USBD_EPSTATUS_EPIN1_Msk (0x1UL << USBD_EPSTATUS_EPIN1_Pos) /*!< Bit mask of EPIN1 field. */
#define USBD_EPSTATUS_EPIN1_NoData                                                                 \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN1_DataDone                                                               \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 0 : Captured state of endpoint's EasyDMA registers. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN0_Pos (0UL)                              /*!< Position of EPIN0 field. */
#define USBD_EPSTATUS_EPIN0_Msk (0x1UL << USBD_EPSTATUS_EPIN0_Pos) /*!< Bit mask of EPIN0 field. */
#define USBD_EPSTATUS_EPIN0_NoData                                                                 \
  (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN0_DataDone                                                               \
  (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Register: USBD_EPDATASTATUS */
/* Description: Provides information on which endpoint(s) an acknowledged data transfer has occurred (EPDATA event) */

/* Bit 23 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT7_Pos (23UL) /*!< Position of EPOUT7 field. */
#define USBD_EPDATASTATUS_EPOUT7_Msk                                                               \
  (0x1UL << USBD_EPDATASTATUS_EPOUT7_Pos) /*!< Bit mask of EPOUT7 field. */
#define USBD_EPDATASTATUS_EPOUT7_NotStarted                                                        \
  (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT7_Started                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 22 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT6_Pos (22UL) /*!< Position of EPOUT6 field. */
#define USBD_EPDATASTATUS_EPOUT6_Msk                                                               \
  (0x1UL << USBD_EPDATASTATUS_EPOUT6_Pos) /*!< Bit mask of EPOUT6 field. */
#define USBD_EPDATASTATUS_EPOUT6_NotStarted                                                        \
  (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT6_Started                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 21 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT5_Pos (21UL) /*!< Position of EPOUT5 field. */
#define USBD_EPDATASTATUS_EPOUT5_Msk                                                               \
  (0x1UL << USBD_EPDATASTATUS_EPOUT5_Pos) /*!< Bit mask of EPOUT5 field. */
#define USBD_EPDATASTATUS_EPOUT5_NotStarted                                                        \
  (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT5_Started                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 20 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT4_Pos (20UL) /*!< Position of EPOUT4 field. */
#define USBD_EPDATASTATUS_EPOUT4_Msk                                                               \
  (0x1UL << USBD_EPDATASTATUS_EPOUT4_Pos) /*!< Bit mask of EPOUT4 field. */
#define USBD_EPDATASTATUS_EPOUT4_NotStarted                                                        \
  (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT4_Started                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 19 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT3_Pos (19UL) /*!< Position of EPOUT3 field. */
#define USBD_EPDATASTATUS_EPOUT3_Msk                                                               \
  (0x1UL << USBD_EPDATASTATUS_EPOUT3_Pos) /*!< Bit mask of EPOUT3 field. */
#define USBD_EPDATASTATUS_EPOUT3_NotStarted                                                        \
  (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT3_Started                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 18 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT2_Pos (18UL) /*!< Position of EPOUT2 field. */
#define USBD_EPDATASTATUS_EPOUT2_Msk                                                               \
  (0x1UL << USBD_EPDATASTATUS_EPOUT2_Pos) /*!< Bit mask of EPOUT2 field. */
#define USBD_EPDATASTATUS_EPOUT2_NotStarted                                                        \
  (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT2_Started                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 17 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT1_Pos (17UL) /*!< Position of EPOUT1 field. */
#define USBD_EPDATASTATUS_EPOUT1_Msk                                                               \
  (0x1UL << USBD_EPDATASTATUS_EPOUT1_Pos) /*!< Bit mask of EPOUT1 field. */
#define USBD_EPDATASTATUS_EPOUT1_NotStarted                                                        \
  (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT1_Started                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 7 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN7_Pos (7UL) /*!< Position of EPIN7 field. */
#define USBD_EPDATASTATUS_EPIN7_Msk                                                                \
  (0x1UL << USBD_EPDATASTATUS_EPIN7_Pos)      /*!< Bit mask of EPIN7 field. */
#define USBD_EPDATASTATUS_EPIN7_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN7_DataDone                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 6 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN6_Pos (6UL) /*!< Position of EPIN6 field. */
#define USBD_EPDATASTATUS_EPIN6_Msk                                                                \
  (0x1UL << USBD_EPDATASTATUS_EPIN6_Pos)      /*!< Bit mask of EPIN6 field. */
#define USBD_EPDATASTATUS_EPIN6_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN6_DataDone                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 5 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN5_Pos (5UL) /*!< Position of EPIN5 field. */
#define USBD_EPDATASTATUS_EPIN5_Msk                                                                \
  (0x1UL << USBD_EPDATASTATUS_EPIN5_Pos)      /*!< Bit mask of EPIN5 field. */
#define USBD_EPDATASTATUS_EPIN5_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN5_DataDone                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 4 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN4_Pos (4UL) /*!< Position of EPIN4 field. */
#define USBD_EPDATASTATUS_EPIN4_Msk                                                                \
  (0x1UL << USBD_EPDATASTATUS_EPIN4_Pos)      /*!< Bit mask of EPIN4 field. */
#define USBD_EPDATASTATUS_EPIN4_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN4_DataDone                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 3 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN3_Pos (3UL) /*!< Position of EPIN3 field. */
#define USBD_EPDATASTATUS_EPIN3_Msk                                                                \
  (0x1UL << USBD_EPDATASTATUS_EPIN3_Pos)      /*!< Bit mask of EPIN3 field. */
#define USBD_EPDATASTATUS_EPIN3_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN3_DataDone                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 2 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN2_Pos (2UL) /*!< Position of EPIN2 field. */
#define USBD_EPDATASTATUS_EPIN2_Msk                                                                \
  (0x1UL << USBD_EPDATASTATUS_EPIN2_Pos)      /*!< Bit mask of EPIN2 field. */
#define USBD_EPDATASTATUS_EPIN2_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN2_DataDone                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 1 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN1_Pos (1UL) /*!< Position of EPIN1 field. */
#define USBD_EPDATASTATUS_EPIN1_Msk                                                                \
  (0x1UL << USBD_EPDATASTATUS_EPIN1_Pos)      /*!< Bit mask of EPIN1 field. */
#define USBD_EPDATASTATUS_EPIN1_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN1_DataDone                                                           \
  (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Register: USBD_USBADDR */
/* Description: Device USB address */

/* Bits 6..0 : Device USB address */
#define USBD_USBADDR_ADDR_Pos            (0UL) /*!< Position of ADDR field. */
#define USBD_USBADDR_ADDR_Msk            (0x7FUL << USBD_USBADDR_ADDR_Pos) /*!< Bit mask of ADDR field. */

/* Register: USBD_BMREQUESTTYPE */
/* Description: SETUP data, byte 0, bmRequestType */

/* Bit 7 : Data transfer direction */
#define USBD_BMREQUESTTYPE_DIRECTION_Pos (7UL) /*!< Position of DIRECTION field. */
#define USBD_BMREQUESTTYPE_DIRECTION_Msk                                                           \
  (0x1UL << USBD_BMREQUESTTYPE_DIRECTION_Pos)           /*!< Bit mask of DIRECTION field. */
#define USBD_BMREQUESTTYPE_DIRECTION_HostToDevice (0UL) /*!< Host-to-device */
#define USBD_BMREQUESTTYPE_DIRECTION_DeviceToHost (1UL) /*!< Device-to-host */

/* Bits 6..5 : Data transfer type */
#define USBD_BMREQUESTTYPE_TYPE_Pos               (5UL) /*!< Position of TYPE field. */
#define USBD_BMREQUESTTYPE_TYPE_Msk                                                                \
  (0x3UL << USBD_BMREQUESTTYPE_TYPE_Pos)       /*!< Bit mask of TYPE field. */
#define USBD_BMREQUESTTYPE_TYPE_Standard (0UL) /*!< Standard */
#define USBD_BMREQUESTTYPE_TYPE_Class    (1UL) /*!< Class */
#define USBD_BMREQUESTTYPE_TYPE_Vendor   (2UL) /*!< Vendor */

/* Bits 4..0 : Data transfer type */
#define USBD_BMREQUESTTYPE_RECIPIENT_Pos (0UL) /*!< Position of RECIPIENT field. */
#define USBD_BMREQUESTTYPE_RECIPIENT_Msk                                                           \
  (0x1FUL << USBD_BMREQUESTTYPE_RECIPIENT_Pos)       /*!< Bit mask of RECIPIENT field. */
#define USBD_BMREQUESTTYPE_RECIPIENT_Device    (0UL) /*!< Device */
#define USBD_BMREQUESTTYPE_RECIPIENT_Interface (1UL) /*!< Interface */
#define USBD_BMREQUESTTYPE_RECIPIENT_Endpoint  (2UL) /*!< Endpoint */
#define USBD_BMREQUESTTYPE_RECIPIENT_Other     (3UL) /*!< Other */

/* Register: USBD_BREQUEST */
/* Description: SETUP data, byte 1, bRequest */

/* Bits 7..0 : SETUP data, byte 1, bRequest. Values provided for standard requests only, user must implement class and vendor values. */
#define USBD_BREQUEST_BREQUEST_Pos             (0UL) /*!< Position of BREQUEST field. */
#define USBD_BREQUEST_BREQUEST_Msk                                                                 \
  (0xFFUL << USBD_BREQUEST_BREQUEST_Pos)                /*!< Bit mask of BREQUEST field. */
#define USBD_BREQUEST_BREQUEST_STD_GET_STATUS     (0UL) /*!< Standard request GET_STATUS */
#define USBD_BREQUEST_BREQUEST_STD_CLEAR_FEATURE  (1UL) /*!< Standard request CLEAR_FEATURE */
#define USBD_BREQUEST_BREQUEST_STD_SET_FEATURE    (3UL) /*!< Standard request SET_FEATURE */
#define USBD_BREQUEST_BREQUEST_STD_SET_ADDRESS    (5UL) /*!< Standard request SET_ADDRESS */
#define USBD_BREQUEST_BREQUEST_STD_GET_DESCRIPTOR (6UL) /*!< Standard request GET_DESCRIPTOR */
#define USBD_BREQUEST_BREQUEST_STD_SET_DESCRIPTOR (7UL) /*!< Standard request SET_DESCRIPTOR */
#define USBD_BREQUEST_BREQUEST_STD_GET_CONFIGURATION                                               \
  (8UL) /*!< Standard request GET_CONFIGURATION */
#define USBD_BREQUEST_BREQUEST_STD_SET_CONFIGURATION                                               \
  (9UL)                                                 /*!< Standard request SET_CONFIGURATION */
#define USBD_BREQUEST_BREQUEST_STD_GET_INTERFACE (10UL) /*!< Standard request GET_INTERFACE */
#define USBD_BREQUEST_BREQUEST_STD_SET_INTERFACE (11UL) /*!< Standard request SET_INTERFACE */
#define USBD_BREQUEST_BREQUEST_STD_SYNCH_FRAME   (12UL) /*!< Standard request SYNCH_FRAME */

/* Register: USBD_WVALUEL */
/* Description: SETUP data, byte 2, LSB of wValue */

/* Bits 7..0 : SETUP data, byte 2, LSB of wValue */
#define USBD_WVALUEL_WVALUEL_Pos                 (0UL) /*!< Position of WVALUEL field. */
#define USBD_WVALUEL_WVALUEL_Msk                                                                   \
  (0xFFUL << USBD_WVALUEL_WVALUEL_Pos) /*!< Bit mask of WVALUEL field. */

/* Register: USBD_WVALUEH */
/* Description: SETUP data, byte 3, MSB of wValue */

/* Bits 7..0 : SETUP data, byte 3, MSB of wValue */
#define USBD_WVALUEH_WVALUEH_Pos (0UL) /*!< Position of WVALUEH field. */
#define USBD_WVALUEH_WVALUEH_Msk                                                                   \
  (0xFFUL << USBD_WVALUEH_WVALUEH_Pos) /*!< Bit mask of WVALUEH field. */

/* Register: USBD_WINDEXL */
/* Description: SETUP data, byte 4, LSB of wIndex */

/* Bits 7..0 : SETUP data, byte 4, LSB of wIndex */
#define USBD_WINDEXL_WINDEXL_Pos (0UL) /*!< Position of WINDEXL field. */
#define USBD_WINDEXL_WINDEXL_Msk                                                                   \
  (0xFFUL << USBD_WINDEXL_WINDEXL_Pos) /*!< Bit mask of WINDEXL field. */

/* Register: USBD_WINDEXH */
/* Description: SETUP data, byte 5, MSB of wIndex */

/* Bits 7..0 : SETUP data, byte 5, MSB of wIndex */
#define USBD_WINDEXH_WINDEXH_Pos (0UL) /*!< Position of WINDEXH field. */
#define USBD_WINDEXH_WINDEXH_Msk                                                                   \
  (0xFFUL << USBD_WINDEXH_WINDEXH_Pos) /*!< Bit mask of WINDEXH field. */

/* Register: USBD_WLENGTHL */
/* Description: SETUP data, byte 6, LSB of wLength */

/* Bits 7..0 : SETUP data, byte 6, LSB of wLength */
#define USBD_WLENGTHL_WLENGTHL_Pos (0UL) /*!< Position of WLENGTHL field. */
#define USBD_WLENGTHL_WLENGTHL_Msk                                                                 \
  (0xFFUL << USBD_WLENGTHL_WLENGTHL_Pos) /*!< Bit mask of WLENGTHL field. */

/* Register: USBD_WLENGTHH */
/* Description: SETUP data, byte 7, MSB of wLength */

/* Bits 7..0 : SETUP data, byte 7, MSB of wLength */
#define USBD_WLENGTHH_WLENGTHH_Pos (0UL) /*!< Position of WLENGTHH field. */
#define USBD_WLENGTHH_WLENGTHH_Msk                                                                 \
  (0xFFUL << USBD_WLENGTHH_WLENGTHH_Pos) /*!< Bit mask of WLENGTHH field. */

/* Register: USBD_SIZE_EPOUT */
/* Description: Description collection: Number of bytes received last in the data stage of this OUT endpoint */

/* Bits 6..0 : Number of bytes received last in the data stage of this OUT endpoint */
#define USBD_SIZE_EPOUT_SIZE_Pos (0UL) /*!< Position of SIZE field. */
#define USBD_SIZE_EPOUT_SIZE_Msk                                                                   \
  (0x7FUL << USBD_SIZE_EPOUT_SIZE_Pos) /*!< Bit mask of SIZE field. */

/* Register: USBD_SIZE_ISOOUT */
/* Description: Number of bytes received last on this ISO OUT data endpoint */

/* Bit 16 : Zero-length data packet received */
#define USBD_SIZE_ISOOUT_ZERO_Pos (16UL) /*!< Position of ZERO field. */
#define USBD_SIZE_ISOOUT_ZERO_Msk                                                                  \
  (0x1UL << USBD_SIZE_ISOOUT_ZERO_Pos)       /*!< Bit mask of ZERO field. */
#define USBD_SIZE_ISOOUT_ZERO_Normal   (0UL) /*!< No zero-length data received, use value in SIZE */
#define USBD_SIZE_ISOOUT_ZERO_ZeroData (1UL) /*!< Zero-length data received, ignore value in SIZE */

/* Bits 9..0 : Number of bytes received last on this ISO OUT data endpoint */
#define USBD_SIZE_ISOOUT_SIZE_Pos      (0UL) /*!< Position of SIZE field. */
#define USBD_SIZE_ISOOUT_SIZE_Msk                                                                  \
  (0x3FFUL << USBD_SIZE_ISOOUT_SIZE_Pos) /*!< Bit mask of SIZE field. */

/* Register: USBD_ENABLE */
/* Description: Enable USB */

/* Bit 0 : Enable USB */
#define USBD_ENABLE_ENABLE_Pos      (0UL) /*!< Position of ENABLE field. */
#define USBD_ENABLE_ENABLE_Msk      (0x1UL << USBD_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define USBD_ENABLE_ENABLE_Disabled (0UL) /*!< USB peripheral is disabled */
#define USBD_ENABLE_ENABLE_Enabled  (1UL) /*!< USB peripheral is enabled */

/* Register: USBD_USBPULLUP */
/* Description: Control of the USB pull-up */

/* Bit 0 : Control of the USB pull-up on the D+ line */
#define USBD_USBPULLUP_CONNECT_Pos  (0UL) /*!< Position of CONNECT field. */
#define USBD_USBPULLUP_CONNECT_Msk                                                                 \
  (0x1UL << USBD_USBPULLUP_CONNECT_Pos)       /*!< Bit mask of CONNECT field. */
#define USBD_USBPULLUP_CONNECT_Disabled (0UL) /*!< Pull-up is disconnected */
#define USBD_USBPULLUP_CONNECT_Enabled  (1UL) /*!< Pull-up is connected to D+ */

/* Register: USBD_DPDMVALUE */
/* Description: State D+ and D- lines will be forced into by the DPDMDRIVE task. The DPDMNODRIVE task reverts the control of the lines to MAC IP (no forcing). */

/* Bits 4..0 : State D+ and D- lines will be forced into by the DPDMDRIVE task */
#define USBD_DPDMVALUE_STATE_Pos        (0UL) /*!< Position of STATE field. */
#define USBD_DPDMVALUE_STATE_Msk                                                                   \
  (0x1FUL << USBD_DPDMVALUE_STATE_Pos) /*!< Bit mask of STATE field. */
#define USBD_DPDMVALUE_STATE_Resume                                                                \
  (1UL) /*!< D+ forced low, D- forced high (K state) for a timing preset in hardware (50 us or 5 ms, depending on bus state) */
#define USBD_DPDMVALUE_STATE_J (2UL) /*!< D+ forced high, D- forced low (J state) */
#define USBD_DPDMVALUE_STATE_K (4UL) /*!< D+ forced low, D- forced high (K state) */

/* Register: USBD_DTOGGLE */
/* Description: Data toggle control and status */

/* Bits 9..8 : Data toggle value */
#define USBD_DTOGGLE_VALUE_Pos (8UL)                             /*!< Position of VALUE field. */
#define USBD_DTOGGLE_VALUE_Msk (0x3UL << USBD_DTOGGLE_VALUE_Pos) /*!< Bit mask of VALUE field. */
#define USBD_DTOGGLE_VALUE_Nop                                                                     \
  (0UL) /*!< No action on data toggle when writing the register with this value */
#define USBD_DTOGGLE_VALUE_Data0    (1UL) /*!< Data toggle is DATA0 on endpoint set by EP and IO */
#define USBD_DTOGGLE_VALUE_Data1    (2UL) /*!< Data toggle is DATA1 on endpoint set by EP and IO */

/* Bit 7 : Selects IN or OUT endpoint */
#define USBD_DTOGGLE_IO_Pos         (7UL)                          /*!< Position of IO field. */
#define USBD_DTOGGLE_IO_Msk         (0x1UL << USBD_DTOGGLE_IO_Pos) /*!< Bit mask of IO field. */
#define USBD_DTOGGLE_IO_Out         (0UL)                          /*!< Selects OUT endpoint */
#define USBD_DTOGGLE_IO_In          (1UL)                          /*!< Selects IN endpoint */

/* Bits 2..0 : Select bulk endpoint number */
#define USBD_DTOGGLE_EP_Pos         (0UL)                          /*!< Position of EP field. */
#define USBD_DTOGGLE_EP_Msk         (0x7UL << USBD_DTOGGLE_EP_Pos) /*!< Bit mask of EP field. */

/* Register: USBD_EPINEN */
/* Description: Endpoint IN enable */

/* Bit 8 : Enable ISO IN endpoint */
#define USBD_EPINEN_ISOIN_Pos       (8UL) /*!< Position of ISOIN field. */
#define USBD_EPINEN_ISOIN_Msk       (0x1UL << USBD_EPINEN_ISOIN_Pos) /*!< Bit mask of ISOIN field. */
#define USBD_EPINEN_ISOIN_Disable   (0UL) /*!< Disable ISO IN endpoint 8 */
#define USBD_EPINEN_ISOIN_Enable    (1UL) /*!< Enable ISO IN endpoint 8 */

/* Bit 7 : Enable IN endpoint 7 */
#define USBD_EPINEN_IN7_Pos         (7UL)                          /*!< Position of IN7 field. */
#define USBD_EPINEN_IN7_Msk         (0x1UL << USBD_EPINEN_IN7_Pos) /*!< Bit mask of IN7 field. */
#define USBD_EPINEN_IN7_Disable     (0UL) /*!< Disable endpoint IN 7 (no response to IN tokens) */
#define USBD_EPINEN_IN7_Enable      (1UL) /*!< Enable endpoint IN 7 (response to IN tokens) */

/* Bit 6 : Enable IN endpoint 6 */
#define USBD_EPINEN_IN6_Pos         (6UL)                          /*!< Position of IN6 field. */
#define USBD_EPINEN_IN6_Msk         (0x1UL << USBD_EPINEN_IN6_Pos) /*!< Bit mask of IN6 field. */
#define USBD_EPINEN_IN6_Disable     (0UL) /*!< Disable endpoint IN 6 (no response to IN tokens) */
#define USBD_EPINEN_IN6_Enable      (1UL) /*!< Enable endpoint IN 6 (response to IN tokens) */

/* Bit 5 : Enable IN endpoint 5 */
#define USBD_EPINEN_IN5_Pos         (5UL)                          /*!< Position of IN5 field. */
#define USBD_EPINEN_IN5_Msk         (0x1UL << USBD_EPINEN_IN5_Pos) /*!< Bit mask of IN5 field. */
#define USBD_EPINEN_IN5_Disable     (0UL) /*!< Disable endpoint IN 5 (no response to IN tokens) */
#define USBD_EPINEN_IN5_Enable      (1UL) /*!< Enable endpoint IN 5 (response to IN tokens) */

/* Bit 4 : Enable IN endpoint 4 */
#define USBD_EPINEN_IN4_Pos         (4UL)                          /*!< Position of IN4 field. */
#define USBD_EPINEN_IN4_Msk         (0x1UL << USBD_EPINEN_IN4_Pos) /*!< Bit mask of IN4 field. */
#define USBD_EPINEN_IN4_Disable     (0UL) /*!< Disable endpoint IN 4 (no response to IN tokens) */
#define USBD_EPINEN_IN4_Enable      (1UL) /*!< Enable endpoint IN 4 (response to IN tokens) */

/* Bit 3 : Enable IN endpoint 3 */
#define USBD_EPINEN_IN3_Pos         (3UL)                          /*!< Position of IN3 field. */
#define USBD_EPINEN_IN3_Msk         (0x1UL << USBD_EPINEN_IN3_Pos) /*!< Bit mask of IN3 field. */
#define USBD_EPINEN_IN3_Disable     (0UL) /*!< Disable endpoint IN 3 (no response to IN tokens) */
#define USBD_EPINEN_IN3_Enable      (1UL) /*!< Enable endpoint IN 3 (response to IN tokens) */

/* Bit 2 : Enable IN endpoint 2 */
#define USBD_EPINEN_IN2_Pos         (2UL)                          /*!< Position of IN2 field. */
#define USBD_EPINEN_IN2_Msk         (0x1UL << USBD_EPINEN_IN2_Pos) /*!< Bit mask of IN2 field. */
#define USBD_EPINEN_IN2_Disable     (0UL) /*!< Disable endpoint IN 2 (no response to IN tokens) */
#define USBD_EPINEN_IN2_Enable      (1UL) /*!< Enable endpoint IN 2 (response to IN tokens) */

/* Bit 1 : Enable IN endpoint 1 */
#define USBD_EPINEN_IN1_Pos         (1UL)                          /*!< Position of IN1 field. */
#define USBD_EPINEN_IN1_Msk         (0x1UL << USBD_EPINEN_IN1_Pos) /*!< Bit mask of IN1 field. */
#define USBD_EPINEN_IN1_Disable     (0UL) /*!< Disable endpoint IN 1 (no response to IN tokens) */
#define USBD_EPINEN_IN1_Enable      (1UL) /*!< Enable endpoint IN 1 (response to IN tokens) */

/* Bit 0 : Enable IN endpoint 0 */
#define USBD_EPINEN_IN0_Pos         (0UL)                          /*!< Position of IN0 field. */
#define USBD_EPINEN_IN0_Msk         (0x1UL << USBD_EPINEN_IN0_Pos) /*!< Bit mask of IN0 field. */
#define USBD_EPINEN_IN0_Disable     (0UL) /*!< Disable endpoint IN 0 (no response to IN tokens) */
#define USBD_EPINEN_IN0_Enable      (1UL) /*!< Enable endpoint IN 0 (response to IN tokens) */

/* Register: USBD_EPOUTEN */
/* Description: Endpoint OUT enable */

/* Bit 8 : Enable ISO OUT endpoint 8 */
#define USBD_EPOUTEN_ISOOUT_Pos     (8UL) /*!< Position of ISOOUT field. */
#define USBD_EPOUTEN_ISOOUT_Msk     (0x1UL << USBD_EPOUTEN_ISOOUT_Pos) /*!< Bit mask of ISOOUT field. */
#define USBD_EPOUTEN_ISOOUT_Disable (0UL) /*!< Disable ISO OUT endpoint 8 */
#define USBD_EPOUTEN_ISOOUT_Enable  (1UL) /*!< Enable ISO OUT endpoint 8 */

/* Bit 7 : Enable OUT endpoint 7 */
#define USBD_EPOUTEN_OUT7_Pos       (7UL)                            /*!< Position of OUT7 field. */
#define USBD_EPOUTEN_OUT7_Msk       (0x1UL << USBD_EPOUTEN_OUT7_Pos) /*!< Bit mask of OUT7 field. */
#define USBD_EPOUTEN_OUT7_Disable   (0UL) /*!< Disable endpoint OUT 7 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT7_Enable    (1UL) /*!< Enable endpoint OUT 7 (response to OUT tokens) */

/* Bit 6 : Enable OUT endpoint 6 */
#define USBD_EPOUTEN_OUT6_Pos       (6UL)                            /*!< Position of OUT6 field. */
#define USBD_EPOUTEN_OUT6_Msk       (0x1UL << USBD_EPOUTEN_OUT6_Pos) /*!< Bit mask of OUT6 field. */
#define USBD_EPOUTEN_OUT6_Disable   (0UL) /*!< Disable endpoint OUT 6 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT6_Enable    (1UL) /*!< Enable endpoint OUT 6 (response to OUT tokens) */

/* Bit 5 : Enable OUT endpoint 5 */
#define USBD_EPOUTEN_OUT5_Pos       (5UL)                            /*!< Position of OUT5 field. */
#define USBD_EPOUTEN_OUT5_Msk       (0x1UL << USBD_EPOUTEN_OUT5_Pos) /*!< Bit mask of OUT5 field. */
#define USBD_EPOUTEN_OUT5_Disable   (0UL) /*!< Disable endpoint OUT 5 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT5_Enable    (1UL) /*!< Enable endpoint OUT 5 (response to OUT tokens) */

/* Bit 4 : Enable OUT endpoint 4 */
#define USBD_EPOUTEN_OUT4_Pos       (4UL)                            /*!< Position of OUT4 field. */
#define USBD_EPOUTEN_OUT4_Msk       (0x1UL << USBD_EPOUTEN_OUT4_Pos) /*!< Bit mask of OUT4 field. */
#define USBD_EPOUTEN_OUT4_Disable   (0UL) /*!< Disable endpoint OUT 4 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT4_Enable    (1UL) /*!< Enable endpoint OUT 4 (response to OUT tokens) */

/* Bit 3 : Enable OUT endpoint 3 */
#define USBD_EPOUTEN_OUT3_Pos       (3UL)                            /*!< Position of OUT3 field. */
#define USBD_EPOUTEN_OUT3_Msk       (0x1UL << USBD_EPOUTEN_OUT3_Pos) /*!< Bit mask of OUT3 field. */
#define USBD_EPOUTEN_OUT3_Disable   (0UL) /*!< Disable endpoint OUT 3 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT3_Enable    (1UL) /*!< Enable endpoint OUT 3 (response to OUT tokens) */

/* Bit 2 : Enable OUT endpoint 2 */
#define USBD_EPOUTEN_OUT2_Pos       (2UL)                            /*!< Position of OUT2 field. */
#define USBD_EPOUTEN_OUT2_Msk       (0x1UL << USBD_EPOUTEN_OUT2_Pos) /*!< Bit mask of OUT2 field. */
#define USBD_EPOUTEN_OUT2_Disable   (0UL) /*!< Disable endpoint OUT 2 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT2_Enable    (1UL) /*!< Enable endpoint OUT 2 (response to OUT tokens) */

/* Bit 1 : Enable OUT endpoint 1 */
#define USBD_EPOUTEN_OUT1_Pos       (1UL)                            /*!< Position of OUT1 field. */
#define USBD_EPOUTEN_OUT1_Msk       (0x1UL << USBD_EPOUTEN_OUT1_Pos) /*!< Bit mask of OUT1 field. */
#define USBD_EPOUTEN_OUT1_Disable   (0UL) /*!< Disable endpoint OUT 1 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT1_Enable    (1UL) /*!< Enable endpoint OUT 1 (response to OUT tokens) */

/* Bit 0 : Enable OUT endpoint 0 */
#define USBD_EPOUTEN_OUT0_Pos       (0UL)                            /*!< Position of OUT0 field. */
#define USBD_EPOUTEN_OUT0_Msk       (0x1UL << USBD_EPOUTEN_OUT0_Pos) /*!< Bit mask of OUT0 field. */
#define USBD_EPOUTEN_OUT0_Disable   (0UL) /*!< Disable endpoint OUT 0 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT0_Enable    (1UL) /*!< Enable endpoint OUT 0 (response to OUT tokens) */

/* Register: USBD_EPSTALL */
/* Description: STALL endpoints */

/* Bit 8 : Stall selected endpoint */
#define USBD_EPSTALL_STALL_Pos      (8UL) /*!< Position of STALL field. */
#define USBD_EPSTALL_STALL_Msk      (0x1UL << USBD_EPSTALL_STALL_Pos) /*!< Bit mask of STALL field. */
#define USBD_EPSTALL_STALL_UnStall  (0UL) /*!< Don't stall selected endpoint */
#define USBD_EPSTALL_STALL_Stall    (1UL) /*!< Stall selected endpoint */

/* Bit 7 : Selects IN or OUT endpoint */
#define USBD_EPSTALL_IO_Pos         (7UL)                          /*!< Position of IO field. */
#define USBD_EPSTALL_IO_Msk         (0x1UL << USBD_EPSTALL_IO_Pos) /*!< Bit mask of IO field. */
#define USBD_EPSTALL_IO_Out         (0UL)                          /*!< Selects OUT endpoint */
#define USBD_EPSTALL_IO_In          (1UL)                          /*!< Selects IN endpoint */

/* Bits 2..0 : Select endpoint number */
#define USBD_EPSTALL_EP_Pos         (0UL)                          /*!< Position of EP field. */
#define USBD_EPSTALL_EP_Msk         (0x7UL << USBD_EPSTALL_EP_Pos) /*!< Bit mask of EP field. */

/* Register: USBD_ISOSPLIT */
/* Description: Controls the split of ISO buffers */

/* Bits 15..0 : Controls the split of ISO buffers */
#define USBD_ISOSPLIT_SPLIT_Pos     (0UL) /*!< Position of SPLIT field. */
#define USBD_ISOSPLIT_SPLIT_Msk                                                                    \
  (0xFFFFUL << USBD_ISOSPLIT_SPLIT_Pos)         /*!< Bit mask of SPLIT field. */
#define USBD_ISOSPLIT_SPLIT_OneDir   (0x0000UL) /*!< Full buffer dedicated to either iso IN or OUT */
#define USBD_ISOSPLIT_SPLIT_HalfIN   (0x0080UL) /*!< Lower half for IN, upper half for OUT */

/* Register: USBD_FRAMECNTR */
/* Description: Returns the current value of the start of frame counter */

/* Bits 10..0 : Returns the current value of the start of frame counter */
#define USBD_FRAMECNTR_FRAMECNTR_Pos (0UL) /*!< Position of FRAMECNTR field. */
#define USBD_FRAMECNTR_FRAMECNTR_Msk                                                               \
  (0x7FFUL << USBD_FRAMECNTR_FRAMECNTR_Pos) /*!< Bit mask of FRAMECNTR field. */

/* Register: USBD_LOWPOWER */
/* Description: Controls USBD peripheral low power mode during USB suspend */

/* Bit 0 : Controls USBD peripheral low-power mode during USB suspend */
#define USBD_LOWPOWER_LOWPOWER_Pos (0UL) /*!< Position of LOWPOWER field. */
#define USBD_LOWPOWER_LOWPOWER_Msk                                                                 \
  (0x1UL << USBD_LOWPOWER_LOWPOWER_Pos) /*!< Bit mask of LOWPOWER field. */
#define USBD_LOWPOWER_LOWPOWER_ForceNormal                                                         \
  (0UL) /*!< Software must write this value to exit low power mode and before performing a remote wake-up */
#define USBD_LOWPOWER_LOWPOWER_LowPower                                                            \
  (1UL) /*!< Software must write this value to enter low power mode after DMA and software have finished interacting with the USB peripheral */

/* Register: USBD_ISOINCONFIG */
/* Description: Controls the response of the ISO IN endpoint to an IN token when no data is ready to be sent */

/* Bit 0 : Controls the response of the ISO IN endpoint to an IN token when no data is ready to be sent */
#define USBD_ISOINCONFIG_RESPONSE_Pos (0UL) /*!< Position of RESPONSE field. */
#define USBD_ISOINCONFIG_RESPONSE_Msk                                                              \
  (0x1UL << USBD_ISOINCONFIG_RESPONSE_Pos)     /*!< Bit mask of RESPONSE field. */
#define USBD_ISOINCONFIG_RESPONSE_NoResp (0UL) /*!< Endpoint does not respond in that case */
#define USBD_ISOINCONFIG_RESPONSE_ZeroData                                                         \
  (1UL) /*!< Endpoint responds with a zero-length data packet in that case */

/* Register: USBD_EPIN_PTR */
/* Description: Description cluster: Data pointer */

/* Bits 31..0 : Data pointer */
#define USBD_EPIN_PTR_PTR_Pos       (0UL) /*!< Position of PTR field. */
#define USBD_EPIN_PTR_PTR_Msk       (0xFFFFFFFFUL << USBD_EPIN_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: USBD_EPIN_MAXCNT */
/* Description: Description cluster: Maximum number of bytes to transfer */

/* Bits 6..0 : Maximum number of bytes to transfer */
#define USBD_EPIN_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define USBD_EPIN_MAXCNT_MAXCNT_Msk                                                                \
  (0x7FUL << USBD_EPIN_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: USBD_EPIN_AMOUNT */
/* Description: Description cluster: Number of bytes transferred in the last transaction */

/* Bits 6..0 : Number of bytes transferred in the last transaction */
#define USBD_EPIN_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define USBD_EPIN_AMOUNT_AMOUNT_Msk                                                                \
  (0x7FUL << USBD_EPIN_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: USBD_ISOIN_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define USBD_ISOIN_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define USBD_ISOIN_PTR_PTR_Msk                                                                     \
  (0xFFFFFFFFUL << USBD_ISOIN_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: USBD_ISOIN_MAXCNT */
/* Description: Maximum number of bytes to transfer */

/* Bits 9..0 : Maximum number of bytes to transfer */
#define USBD_ISOIN_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define USBD_ISOIN_MAXCNT_MAXCNT_Msk                                                               \
  (0x3FFUL << USBD_ISOIN_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: USBD_ISOIN_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 9..0 : Number of bytes transferred in the last transaction */
#define USBD_ISOIN_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define USBD_ISOIN_AMOUNT_AMOUNT_Msk                                                               \
  (0x3FFUL << USBD_ISOIN_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: USBD_EPOUT_PTR */
/* Description: Description cluster: Data pointer */

/* Bits 31..0 : Data pointer */
#define USBD_EPOUT_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define USBD_EPOUT_PTR_PTR_Msk                                                                     \
  (0xFFFFFFFFUL << USBD_EPOUT_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: USBD_EPOUT_MAXCNT */
/* Description: Description cluster: Maximum number of bytes to transfer */

/* Bits 6..0 : Maximum number of bytes to transfer */
#define USBD_EPOUT_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define USBD_EPOUT_MAXCNT_MAXCNT_Msk                                                               \
  (0x7FUL << USBD_EPOUT_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: USBD_EPOUT_AMOUNT */
/* Description: Description cluster: Number of bytes transferred in the last transaction */

/* Bits 6..0 : Number of bytes transferred in the last transaction */
#define USBD_EPOUT_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define USBD_EPOUT_AMOUNT_AMOUNT_Msk                                                               \
  (0x7FUL << USBD_EPOUT_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: USBD_ISOOUT_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define USBD_ISOOUT_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define USBD_ISOOUT_PTR_PTR_Msk                                                                    \
  (0xFFFFFFFFUL << USBD_ISOOUT_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: USBD_ISOOUT_MAXCNT */
/* Description: Maximum number of bytes to transfer */

/* Bits 9..0 : Maximum number of bytes to transfer */
#define USBD_ISOOUT_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define USBD_ISOOUT_MAXCNT_MAXCNT_Msk                                                              \
  (0x3FFUL << USBD_ISOOUT_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: USBD_ISOOUT_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 9..0 : Number of bytes transferred in the last transaction */
#define USBD_ISOOUT_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define USBD_ISOOUT_AMOUNT_AMOUNT_Msk                                                              \
  (0x3FFUL << USBD_ISOOUT_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */


/* Peripheral: WDT */
/* Description: Watchdog Timer */

/* Register: WDT_TASKS_START */
/* Description: Start the watchdog */

/* Bit 0 : Start the watchdog */
#define WDT_TASKS_START_TASKS_START_Pos (0UL) /*!< Position of TASKS_START field. */
#define WDT_TASKS_START_TASKS_START_Msk                                                            \
  (0x1UL << WDT_TASKS_START_TASKS_START_Pos)        /*!< Bit mask of TASKS_START field. */
#define WDT_TASKS_START_TASKS_START_Trigger   (1UL) /*!< Trigger task */

/* Register: WDT_EVENTS_TIMEOUT */
/* Description: Watchdog timeout */

/* Bit 0 : Watchdog timeout */
#define WDT_EVENTS_TIMEOUT_EVENTS_TIMEOUT_Pos (0UL) /*!< Position of EVENTS_TIMEOUT field. */
#define WDT_EVENTS_TIMEOUT_EVENTS_TIMEOUT_Msk                                                      \
  (0x1UL << WDT_EVENTS_TIMEOUT_EVENTS_TIMEOUT_Pos) /*!< Bit mask of EVENTS_TIMEOUT field. */
#define WDT_EVENTS_TIMEOUT_EVENTS_TIMEOUT_NotGenerated (0UL) /*!< Event not generated */
#define WDT_EVENTS_TIMEOUT_EVENTS_TIMEOUT_Generated    (1UL) /*!< Event generated */

/* Register: WDT_INTENSET */
/* Description: Enable interrupt */

/* Bit 0 : Write '1' to enable interrupt for event TIMEOUT */
#define WDT_INTENSET_TIMEOUT_Pos                       (0UL) /*!< Position of TIMEOUT field. */
#define WDT_INTENSET_TIMEOUT_Msk                                                                   \
  (0x1UL << WDT_INTENSET_TIMEOUT_Pos)       /*!< Bit mask of TIMEOUT field. */
#define WDT_INTENSET_TIMEOUT_Disabled (0UL) /*!< Read: Disabled */
#define WDT_INTENSET_TIMEOUT_Enabled  (1UL) /*!< Read: Enabled */
#define WDT_INTENSET_TIMEOUT_Set      (1UL) /*!< Enable */

/* Register: WDT_INTENCLR */
/* Description: Disable interrupt */

/* Bit 0 : Write '1' to disable interrupt for event TIMEOUT */
#define WDT_INTENCLR_TIMEOUT_Pos      (0UL) /*!< Position of TIMEOUT field. */
#define WDT_INTENCLR_TIMEOUT_Msk                                                                   \
  (0x1UL << WDT_INTENCLR_TIMEOUT_Pos)       /*!< Bit mask of TIMEOUT field. */
#define WDT_INTENCLR_TIMEOUT_Disabled (0UL) /*!< Read: Disabled */
#define WDT_INTENCLR_TIMEOUT_Enabled  (1UL) /*!< Read: Enabled */
#define WDT_INTENCLR_TIMEOUT_Clear    (1UL) /*!< Disable */

/* Register: WDT_RUNSTATUS */
/* Description: Run status */

/* Bit 0 : Indicates whether or not the watchdog is running */
#define WDT_RUNSTATUS_RUNSTATUS_Pos   (0UL) /*!< Position of RUNSTATUS field. */
#define WDT_RUNSTATUS_RUNSTATUS_Msk                                                                \
  (0x1UL << WDT_RUNSTATUS_RUNSTATUS_Pos)         /*!< Bit mask of RUNSTATUS field. */
#define WDT_RUNSTATUS_RUNSTATUS_NotRunning (0UL) /*!< Watchdog not running */
#define WDT_RUNSTATUS_RUNSTATUS_Running    (1UL) /*!< Watchdog is running */

/* Register: WDT_REQSTATUS */
/* Description: Request status */

/* Bit 7 : Request status for RR[7] register */
#define WDT_REQSTATUS_RR7_Pos              (7UL) /*!< Position of RR7 field. */
#define WDT_REQSTATUS_RR7_Msk              (0x1UL << WDT_REQSTATUS_RR7_Pos) /*!< Bit mask of RR7 field. */
#define WDT_REQSTATUS_RR7_DisabledOrRequested                                                      \
  (0UL) /*!< RR[7] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR7_EnabledAndUnrequested                                                    \
  (1UL) /*!< RR[7] register is enabled, and are not yet requesting reload */

/* Bit 6 : Request status for RR[6] register */
#define WDT_REQSTATUS_RR6_Pos (6UL)                            /*!< Position of RR6 field. */
#define WDT_REQSTATUS_RR6_Msk (0x1UL << WDT_REQSTATUS_RR6_Pos) /*!< Bit mask of RR6 field. */
#define WDT_REQSTATUS_RR6_DisabledOrRequested                                                      \
  (0UL) /*!< RR[6] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR6_EnabledAndUnrequested                                                    \
  (1UL) /*!< RR[6] register is enabled, and are not yet requesting reload */

/* Bit 5 : Request status for RR[5] register */
#define WDT_REQSTATUS_RR5_Pos (5UL)                            /*!< Position of RR5 field. */
#define WDT_REQSTATUS_RR5_Msk (0x1UL << WDT_REQSTATUS_RR5_Pos) /*!< Bit mask of RR5 field. */
#define WDT_REQSTATUS_RR5_DisabledOrRequested                                                      \
  (0UL) /*!< RR[5] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR5_EnabledAndUnrequested                                                    \
  (1UL) /*!< RR[5] register is enabled, and are not yet requesting reload */

/* Bit 4 : Request status for RR[4] register */
#define WDT_REQSTATUS_RR4_Pos (4UL)                            /*!< Position of RR4 field. */
#define WDT_REQSTATUS_RR4_Msk (0x1UL << WDT_REQSTATUS_RR4_Pos) /*!< Bit mask of RR4 field. */
#define WDT_REQSTATUS_RR4_DisabledOrRequested                                                      \
  (0UL) /*!< RR[4] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR4_EnabledAndUnrequested                                                    \
  (1UL) /*!< RR[4] register is enabled, and are not yet requesting reload */

/* Bit 3 : Request status for RR[3] register */
#define WDT_REQSTATUS_RR3_Pos (3UL)                            /*!< Position of RR3 field. */
#define WDT_REQSTATUS_RR3_Msk (0x1UL << WDT_REQSTATUS_RR3_Pos) /*!< Bit mask of RR3 field. */
#define WDT_REQSTATUS_RR3_DisabledOrRequested                                                      \
  (0UL) /*!< RR[3] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR3_EnabledAndUnrequested                                                    \
  (1UL) /*!< RR[3] register is enabled, and are not yet requesting reload */

/* Bit 2 : Request status for RR[2] register */
#define WDT_REQSTATUS_RR2_Pos (2UL)                            /*!< Position of RR2 field. */
#define WDT_REQSTATUS_RR2_Msk (0x1UL << WDT_REQSTATUS_RR2_Pos) /*!< Bit mask of RR2 field. */
#define WDT_REQSTATUS_RR2_DisabledOrRequested                                                      \
  (0UL) /*!< RR[2] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR2_EnabledAndUnrequested                                                    \
  (1UL) /*!< RR[2] register is enabled, and are not yet requesting reload */

/* Bit 1 : Request status for RR[1] register */
#define WDT_REQSTATUS_RR1_Pos (1UL)                            /*!< Position of RR1 field. */
#define WDT_REQSTATUS_RR1_Msk (0x1UL << WDT_REQSTATUS_RR1_Pos) /*!< Bit mask of RR1 field. */
#define WDT_REQSTATUS_RR1_DisabledOrRequested                                                      \
  (0UL) /*!< RR[1] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR1_EnabledAndUnrequested                                                    \
  (1UL) /*!< RR[1] register is enabled, and are not yet requesting reload */

/* Bit 0 : Request status for RR[0] register */
#define WDT_REQSTATUS_RR0_Pos (0UL)                            /*!< Position of RR0 field. */
#define WDT_REQSTATUS_RR0_Msk (0x1UL << WDT_REQSTATUS_RR0_Pos) /*!< Bit mask of RR0 field. */
#define WDT_REQSTATUS_RR0_DisabledOrRequested                                                      \
  (0UL) /*!< RR[0] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR0_EnabledAndUnrequested                                                    \
  (1UL) /*!< RR[0] register is enabled, and are not yet requesting reload */

/* Register: WDT_CRV */
/* Description: Counter reload value */

/* Bits 31..0 : Counter reload value in number of cycles of the 32.768 kHz clock */
#define WDT_CRV_CRV_Pos       (0UL)                             /*!< Position of CRV field. */
#define WDT_CRV_CRV_Msk       (0xFFFFFFFFUL << WDT_CRV_CRV_Pos) /*!< Bit mask of CRV field. */

/* Register: WDT_RREN */
/* Description: Enable register for reload request registers */

/* Bit 7 : Enable or disable RR[7] register */
#define WDT_RREN_RR7_Pos      (7UL)                       /*!< Position of RR7 field. */
#define WDT_RREN_RR7_Msk      (0x1UL << WDT_RREN_RR7_Pos) /*!< Bit mask of RR7 field. */
#define WDT_RREN_RR7_Disabled (0UL)                       /*!< Disable RR[7] register */
#define WDT_RREN_RR7_Enabled  (1UL)                       /*!< Enable RR[7] register */

/* Bit 6 : Enable or disable RR[6] register */
#define WDT_RREN_RR6_Pos      (6UL)                       /*!< Position of RR6 field. */
#define WDT_RREN_RR6_Msk      (0x1UL << WDT_RREN_RR6_Pos) /*!< Bit mask of RR6 field. */
#define WDT_RREN_RR6_Disabled (0UL)                       /*!< Disable RR[6] register */
#define WDT_RREN_RR6_Enabled  (1UL)                       /*!< Enable RR[6] register */

/* Bit 5 : Enable or disable RR[5] register */
#define WDT_RREN_RR5_Pos      (5UL)                       /*!< Position of RR5 field. */
#define WDT_RREN_RR5_Msk      (0x1UL << WDT_RREN_RR5_Pos) /*!< Bit mask of RR5 field. */
#define WDT_RREN_RR5_Disabled (0UL)                       /*!< Disable RR[5] register */
#define WDT_RREN_RR5_Enabled  (1UL)                       /*!< Enable RR[5] register */

/* Bit 4 : Enable or disable RR[4] register */
#define WDT_RREN_RR4_Pos      (4UL)                       /*!< Position of RR4 field. */
#define WDT_RREN_RR4_Msk      (0x1UL << WDT_RREN_RR4_Pos) /*!< Bit mask of RR4 field. */
#define WDT_RREN_RR4_Disabled (0UL)                       /*!< Disable RR[4] register */
#define WDT_RREN_RR4_Enabled  (1UL)                       /*!< Enable RR[4] register */

/* Bit 3 : Enable or disable RR[3] register */
#define WDT_RREN_RR3_Pos      (3UL)                       /*!< Position of RR3 field. */
#define WDT_RREN_RR3_Msk      (0x1UL << WDT_RREN_RR3_Pos) /*!< Bit mask of RR3 field. */
#define WDT_RREN_RR3_Disabled (0UL)                       /*!< Disable RR[3] register */
#define WDT_RREN_RR3_Enabled  (1UL)                       /*!< Enable RR[3] register */

/* Bit 2 : Enable or disable RR[2] register */
#define WDT_RREN_RR2_Pos      (2UL)                       /*!< Position of RR2 field. */
#define WDT_RREN_RR2_Msk      (0x1UL << WDT_RREN_RR2_Pos) /*!< Bit mask of RR2 field. */
#define WDT_RREN_RR2_Disabled (0UL)                       /*!< Disable RR[2] register */
#define WDT_RREN_RR2_Enabled  (1UL)                       /*!< Enable RR[2] register */

/* Bit 1 : Enable or disable RR[1] register */
#define WDT_RREN_RR1_Pos      (1UL)                       /*!< Position of RR1 field. */
#define WDT_RREN_RR1_Msk      (0x1UL << WDT_RREN_RR1_Pos) /*!< Bit mask of RR1 field. */
#define WDT_RREN_RR1_Disabled (0UL)                       /*!< Disable RR[1] register */
#define WDT_RREN_RR1_Enabled  (1UL)                       /*!< Enable RR[1] register */

/* Bit 0 : Enable or disable RR[0] register */
#define WDT_RREN_RR0_Pos      (0UL)                       /*!< Position of RR0 field. */
#define WDT_RREN_RR0_Msk      (0x1UL << WDT_RREN_RR0_Pos) /*!< Bit mask of RR0 field. */
#define WDT_RREN_RR0_Disabled (0UL)                       /*!< Disable RR[0] register */
#define WDT_RREN_RR0_Enabled  (1UL)                       /*!< Enable RR[0] register */

/* Register: WDT_CONFIG */
/* Description: Configuration register */

/* Bit 3 : Configure the watchdog to either be paused, or kept running, while the CPU is halted by the debugger */
#define WDT_CONFIG_HALT_Pos   (3UL)                          /*!< Position of HALT field. */
#define WDT_CONFIG_HALT_Msk   (0x1UL << WDT_CONFIG_HALT_Pos) /*!< Bit mask of HALT field. */
#define WDT_CONFIG_HALT_Pause (0UL) /*!< Pause watchdog while the CPU is halted by the debugger */
#define WDT_CONFIG_HALT_Run                                                                        \
  (1UL) /*!< Keep the watchdog running while the CPU is halted by the debugger */

/* Bit 0 : Configure the watchdog to either be paused, or kept running, while the CPU is sleeping */
#define WDT_CONFIG_SLEEP_Pos   (0UL)                           /*!< Position of SLEEP field. */
#define WDT_CONFIG_SLEEP_Msk   (0x1UL << WDT_CONFIG_SLEEP_Pos) /*!< Bit mask of SLEEP field. */
#define WDT_CONFIG_SLEEP_Pause (0UL) /*!< Pause watchdog while the CPU is sleeping */
#define WDT_CONFIG_SLEEP_Run   (1UL) /*!< Keep the watchdog running while the CPU is sleeping */

/* Register: WDT_RR */
/* Description: Description collection: Reload request n */

/* Bits 31..0 : Reload request register */
#define WDT_RR_RR_Pos          (0UL)                           /*!< Position of RR field. */
#define WDT_RR_RR_Msk          (0xFFFFFFFFUL << WDT_RR_RR_Pos) /*!< Bit mask of RR field. */
#define WDT_RR_RR_Reload       (0x6E524635UL) /*!< Value to request a reload of the watchdog timer */


/*lint --flb "Leave library region" */
#endif
