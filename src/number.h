#pragma once

#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

// #include "../config.h"
typedef enum BarCompareOp {
    LT,
    GT,
    LEQ,
    GEQ,
    EQ,
    NEQ,
} BarCompareOp;

typedef struct Number {
    int value;
    Rectangle inner_rect;
} Number;

typedef struct NumberArray {
    size_t length;
    Number** _bars;
} NumberArray;

Number make_number(int, size_t);
Number* new_number(int, size_t);

void number_render(Number*, bool);
void number_set_value(Number*, int);
void number_free(Number*);

NumberArray* new_number_array(Number**, size_t);
NumberArray* new_number_array_random(int, int);

void number_array_render(NumberArray*);
Number* number_array_get(NumberArray*, size_t);
void number_array_set(NumberArray*, size_t, Number*);
void number_array_swap(NumberArray*, size_t, size_t);
void number_array_free(NumberArray*);
