#pragma once

#include "array/array.h"

typedef void (*UpdateCallback)(BarArray*);

typedef enum Algorithm {
    SELECT,
    BUBBLE,
    INSERT,
} Algorithm;

void sleep_for_access_delay();
