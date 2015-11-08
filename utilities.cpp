#include "utilities.h"

// Call this will cause the micro to go sleep
void suspend() {
  cli();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}
