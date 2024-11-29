
#include "../../armv7-m/trace.c"
#include "../../armv7-m/olf.c"
#include "../../armv7-m/profile.c"

#include "../nrf52840/clocks.c"
#include "../nrf52840/radio.c"

#include "platform.c"

// warn if used runtime environment has not been tested (is not explicitly supported)
// NOTE: This check is not strictly necessary if implementation files are written perfectly generic.
// However, the latter is unrealistic, as it is so easy to miss something (particularly regarding
// untested RTEs). Hence, we warn if an untested RTE is used.
// The check should be updated whenever a new RTE has been tested and gets officially supported afterwards.
#include "gpi/tools.h"
#include "gpi/platform_spec.h"
ASSERT_CT_WARN_STATIC(
	GPI_ARCH_IS_OS(NONE) && GPI_ARCH_IS_CRT(SEGGER1)),
	untested_runtime_environment__use_GPI_at_your_own_risk);
