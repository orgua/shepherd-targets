
#include "../../armv7-m/olf.c"
#include "../../armv7-m/profile.c"
#include "../../armv7-m/trace.c"

#include "../nrf528xx/clocks.c"
#include "../nrf528xx/platform.c"
#include "../nrf528xx/radio.c"
#include "../nrf528xx/stdio.c"

#include "platform.c"
#include "resource_check.c"

// warn if used runtime environment has not been tested (is not explicitly supported)
// NOTE: This check is not strictly necessary if implementation files are written perfectly generic.
// However, the latter is unrealistic, as it is so easy to miss something (particularly regarding
// untested RTEs). Hence, we warn if an untested RTE is used.
// The check should be updated whenever a new RTE has been tested and gets officially supported afterwards.
#include "gpi/platform_spec.h"
#include "gpi/tools.h"
ASSERT_CT_WARN_STATIC(GPI_ARCH_IS_OS(NONE) &&
                              (GPI_ARCH_IS_CRT(SEGGER1) || GPI_ARCH_IS_CRT(SEGGER2)),
                      untested_runtime_environment__use_GPI_at_your_own_risk);
