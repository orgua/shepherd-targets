
// FLOCKLAB_NODE_ID is a variable with very special handling: on FLOCKLAB, its init value
// gets overridden with the id of the node in the testbed during device programming (by patching
// the elf file before programming). Thus, it is well suited as a node id variable.
//
// ATTENTION: The patching mechanism is a sensible thing. To work properly, the most important
// prerequisite is that FLOCKLAB_NODE_ID is placed in a section of type SHT_PROGBITS (see ELF spec.
// for details), i.e. a section with a 1:1 content image in the elf file (which gets patched then). 
// (In the past it was also required to be the .data section (".data", not ".data.<something>").
// Starting from 2022-02-21 the patch tool looks for a section containing symbol FLOCKLAB_NODE_ID,
// so today FLOCKLAB_NODE_ID can also reside in .rodata or any other section.)
// In projects using the SEGGER linker, the .data segment(s) are typically not stored explicitly
// in the elf file (they have type SHT_NOBITS and get initialized implicitly from .segger.init.data
// via the init table functions). Hence, FLOCKLAB_NODE_ID must not reside in .data in this case.
// We move it to .rodata by declaring it const. However, with const it must be ensured that the
// variable does not get optimized away via constant propagation. A safe way to achieve this is
// to put the variable definition in a different *.c file (so the compiler has no prior knowledge 
// about the value, which renders constant propagation impossible).

#include <inttypes.h>

const uint16_t FLOCKLAB_NODE_ID = 0;
