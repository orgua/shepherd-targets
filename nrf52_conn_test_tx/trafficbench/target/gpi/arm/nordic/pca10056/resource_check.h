
// do not #include "gpi/resource_check.h" because order is vice versa (current file is included there)

// provide resource declaration symbols
#if (2 != GPI_RESOURCE_CHECK_DECLARATION)
	#include "../nrf52840/resource_declarations.h"
#endif
