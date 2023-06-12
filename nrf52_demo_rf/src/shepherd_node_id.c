
// SHEPHERD_NODE_ID is a variable with special handling: for the SHEPHERD-testbed, its init value
// gets overridden with the id of the node in the testbed during device programming (by patching
// the elf file before programming). Thus, it is well suited as a node id variable.
//
// ATTENTION: The patching mechanism is a sensitive thing. To work properly, the most important
// prerequisite is that SHEPHERD_NODE_ID is placed in a section of type SHT_PROGBITS (see ELF spec.
// for details), i.e. a section with a 1:1 content image in the elf file (which gets patched then).
//
// In projects using the SEGGER linker, the .data segment(s) are typically not stored explicitly
// in the elf file (they have type SHT_NOBITS and get initialized implicitly from .segger.init.data
// via the init table functions). Hence, SHEPHERD_NODE_ID must not reside in .data in this case.
// We move it to .rodata by declaring it const. However, with const it must be ensured that the
// variable does not get optimized away via constant propagation. A safe way to achieve this is
// to put the variable definition in a different *.c file (so the compiler has no prior knowledge
// about the value, which renders constant propagation impossible).

#include <inttypes.h>

const uint16_t SHEPHERD_NODE_ID = 0;
