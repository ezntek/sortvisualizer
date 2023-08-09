#pragma once

#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

struct Accesses {
    size_t read;
    size_t write;
};

struct Target {
    size_t first;
    size_t second;
};

typedef struct Bar {
    int value;
    Rectangle rect;
} Bar;

typedef struct BarArray {
    size_t length;

    struct Accesses accesses;
    Bar** _bars;
} BarArray;

// value, parent array index
Bar make_bar(int, size_t);
// value, parent array index
Bar* new_bar(int, size_t);

// bar, is targeted
void bar_render(Bar*, bool);
// bar, new value
void bar_set_value(Bar*, int);
// bar
void bar_unload(Bar*);

// count, max value
BarArray* new_bar_array(int, int);

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
// bar array
void bar_array_unload(BarArray*);
