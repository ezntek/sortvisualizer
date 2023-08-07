#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../config.h"
#include "number.h"

Number make_number(int value, size_t idx) {
    float width = (float)WIN_WIDTH / ELEMS - BARS_PADDING;
    float height = value * HEIGHT_SCALE_FACTOR;
    float x = (idx * width) + (BARS_PADDING * idx);
    float y = WIN_HEIGHT - height;

    Rectangle rect = (Rectangle){x, y, width, height};

    return (Number){value, rect};
}

Number* new_number(int value, size_t idx) {
    Number* result = malloc(sizeof(Number));
    *result = make_number(value, idx);

    return result;
}

void render_number(Number* bar, bool is_target) {
    Color rect_color = WHITE;
    if (is_target) {
        rect_color = RED;
    }

    DrawRectangleRec(bar->inner_rect, rect_color);
}

void set_number_value(Number* bar, int new_val) {
    int new_height = new_val * HEIGHT_SCALE_FACTOR;
    int new_y = WIN_HEIGHT - new_height;

    bar->inner_rect.height = new_height;
    bar->inner_rect.y = new_y;
    bar->value = new_val;
};

void number_free(Number* number) { free(number); }

NumberArray* new_number_array(Number** num_array, size_t len) {
    Number** arr = malloc(sizeof(num_array) * len);
    *arr = *num_array;

    NumberArray* res = malloc(sizeof(NumberArray));
    *res = (NumberArray){len, arr};

    return res;
}

NumberArray* new_number_array_random(int count, int max) {
    srand(time(NULL));
    Number** arr = malloc(sizeof(Number) * count);
    for (size_t i = 0; i < count; i++) {
        int randval = ((float)(rand()) / RAND_MAX) * max;
        arr[i] = new_number(randval, i);
    }

    NumberArray* res = malloc(sizeof(NumberArray));
    *res = (NumberArray){count, arr};

    return res;
}

void render_number_array(NumberArray* num_arr) {
    for (size_t idx = 0; idx < num_arr->length; idx++) {
        Number* num = number_array_get(num_arr, idx);
        render_number(num, false); // FIXME: whatever this is
    }
}

void refresh_number_array(NumberArray* num_arr) { return; }

Number* number_array_get(NumberArray* num_arr, size_t idx) {
    if (idx > num_arr->length) {
        return NULL;
    }

    return num_arr->_bars[idx];
}

bool number_array_set(NumberArray* num_arr, size_t idx, Number* new_val) {
    if (idx > num_arr->length) {
        return false;
    }

    num_arr->_bars[idx] = new_val;
    return true;
}

bool number_array_swap(NumberArray* num_arr, size_t idx1, size_t idx2) {
    Number* a = number_array_get(num_arr, idx1);

    if (a == NULL)
        return false;

    Number* b = number_array_get(num_arr, idx2);

    if (b == NULL)
        return false;

    int tmp = a->value;
    set_number_value(a, b->value);
    set_number_value(b, tmp);

    return true;
}

void number_array_free(NumberArray* num_arr) {
    for (size_t idx = 0; idx < num_arr->length; idx++) {
        Number* num = number_array_get(num_arr, idx);
        if (num != NULL)
            free(num);
    };
    free(num_arr);
}
