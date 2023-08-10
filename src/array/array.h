#pragma once

#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

#include "bar.h"

struct Accesses {
    size_t read;
    size_t write;
};

struct Targets {
    size_t first;
    size_t second;
};

typedef struct BarArray {
    size_t length;

    struct Targets targets;
    struct Accesses accesses;
    Bar** _bars;
} BarArray;

// slice with the Bar*'s inside, length
BarArray* new_bar_array(Bar**, size_t);
// count, max value
BarArray* new_bar_array_random(int, int);

// bar array
void bar_array_render(BarArray*);
// bar array, index -> value
int bar_array_get(BarArray*, size_t);
// bar array, index -> bar
Bar* bar_array_get_bar(BarArray*, size_t);
// bar array, index, value
void bar_array_set(BarArray*, size_t, int);
// bar array, index, value
void bar_array_set_bar(BarArray*, size_t, Bar*);
// bar array, index, index
void bar_array_swap(BarArray*, size_t, size_t);
// bar array, split-until
BarArray* bar_array_split_left(BarArray*, size_t);
// bar array, split-till
BarArray* bar_array_split_right(BarArray*, size_t);
// bar array
void bar_array_unload(BarArray*);
