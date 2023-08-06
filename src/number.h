#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef NUMBER_H_
#define NUMBER_H_

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
void render_number(Number*, bool);
// void bar_refresh(Bar*);
void set_number_value(Number*, int);

NumberArray* new_number_array(Number**, size_t);
NumberArray* new_number_array_random(int, int);
void render_number_array(NumberArray*);
void refresh_number_array(NumberArray*);

Number* number_array_get(NumberArray*, size_t);
bool number_array_set(NumberArray*, size_t, Number*);
bool number_array_swap(NumberArray*, size_t, size_t);

#endif
