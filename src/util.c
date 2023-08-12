#define _POSIX_C_SOURCE 200809L
#include <time.h>

#include "../config.h"

void sleep_for_access_delay() {
    struct timespec timespec = (struct timespec){0, ARR_ACCESS_DELAY * 1000000};
    nanosleep(&timespec, NULL);
}
