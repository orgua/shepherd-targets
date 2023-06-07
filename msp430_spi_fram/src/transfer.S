# This is currently not used. There's absolutely no reason for it to be here, but well here it is.

.file "spiloop.s"

#include <msp430fr5962.h>

#define PC r0
#define SP r1
#define SR r2
#define DMA_READ_MASK (DMASRCBYTE | DMADSTBYTE | DMASRCINCR_3 | DMADT_0)
#define DMA_WRITE_MASK (DMASRCBYTE | DMADSTBYTE | DMADSTINCR_3 | DMADT_0)

.section .text

.global cs_handler

cs_handler:
    push r4
    sub #4, SP; make room for 3B command buffer
    mova SP,&DMA0DA; point DMA0 to command buffer on stack
    bic.b #UCRXIFG,&UCA0IFG; Clear RX interrupt
    bis.w #DMAEN,&DMA0CTL; Enable DMA0

    bis.b #BIT6,&P3OUT; set pin high
    bit.w #DMAIFG,&DMA0CTL; DMA interrupt?
    jz $-4
    bic.w #DMAIFG,&DMA0CTL; clear DMA interrupt

    mova @SP, r4; move received data into r4
    adda r12, r4; add base buffer address
    bit.b #0x80,2(SP); test for R/W bit (first byte on stack)
    jz read
write:
    mova r4, &DMA1DA; destination is requested address
    bic.b #UCRXIFG,&UCA0IFG; Clear RX interrupt
    bis.w #DMAEN,&DMA1CTL; Enable DMA1
    jmp handler_end
read:
    mov.b @r4,&UCA0TXBUF; put first byte into buffer
    adda #1, r4; point to second byte
    mova r4, &DMA2SA; source is requested address
    bis.w #DMAEN,&DMA2CTL; Enable DMA2
handler_end:
    bic.b #BIT6,&P3OUT; set pin low
    mova r4, r12
    add #4, SP
    pop r4
    reta

.end
