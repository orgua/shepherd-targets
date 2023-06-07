#include "app.h"
#include "peripherals.h"

/**
 * Protothread loop
 *
 * Iterates all threads and enters low power mode when all blocking.
 *
 */
__RAMFUNC int main(void) {

  struct pt pt_application = pt_init();
  while (1) {
    application(&pt_application);
    enter_low_power();
  };
}
