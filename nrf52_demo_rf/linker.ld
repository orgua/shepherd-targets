/* details on syntax can be found in GCC linker manual */


MEMORY {
  ROM_DATA (rx) : ORIGIN = 0x0, LENGTH = 1M
  RAM (rwx) :  ORIGIN = 0x20000000, LENGTH = 256k
}

SECTIONS {
        .isr_vector : {
                . = ALIGN(4);
                _isr_vector_start = .;
                KEEP(*(.isr_vector))    /* vector table */
                . = ALIGN(4);
                _isr_vector_end = .;
        } >ROM_DATA

        .text : {
                . = ALIGN(4);
                *(.text)                /* Program code */
                *(.text.*)
                *(.rodata)              /* read only data */
                *(.rodata*)
                . = ALIGN(4);
                _etext = .;             /* _etext is end of program code */
        } >ROM_DATA                        /* this section is code, hence gos to FLASH */


        .data : AT ( _etext ) {         /* AT specifies the LMA (load memory address) */
                . = ALIGN(4);           /* also, this section is for initialized
                                             global/static variables */
                _sdata = .;
                *(.data)
                *(.data.*)
                . = ALIGN(4);
                *(.ramfunctions)
                _edata = .;
        } >RAM                          /* this section go into this RAM */

        .bss : {                        /* this section is for uninitialized global/static
                                        variables, which we set to zero */
                . = ALIGN(4);
                _sbss = .;              /* the . sets the symbol to value of current counter */
                *(.bss)
                *(COMMON)
                . = ALIGN(4);
                _ebss = .;
        } >RAM


        /DISCARD/ :
        {
        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)
        }
}
