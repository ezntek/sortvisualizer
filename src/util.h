#pragma once

#include "config.h"
#include <time.h>

inline void access_delay() {
    struct timespec timespec = (struct timespec){0, ARR_ACCESS_DELAY * 1000000};
    nanosleep(&timespec, NULL);
}
