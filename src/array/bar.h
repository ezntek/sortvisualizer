#pragma once

#include <raylib.h>
#include <stddef.h>

typedef struct Bar {
    int value;
    Rectangle rect;
} Bar;

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
