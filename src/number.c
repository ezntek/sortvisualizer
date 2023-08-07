#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "number.h"

const int WIN_WIDTH = 1200;
const int WIN_HEIGHT = 800;
const int BARS_PADDING = 2;
const int HEIGHT_SCALE_FACTOR = 2;

Number make_number(int value, size_t idx) {
    int width = WIN_WIDTH / 100 - (BARS_PADDING * 2);
    int height = value * HEIGHT_SCALE_FACTOR;
    int x = (idx * width) + (BARS_PADDING * idx);
    int y = WIN_HEIGHT - height;

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

NumberArray* new_number_array(Number** num_array, size_t len) {
    Number** arr = malloc(sizeof(num_array) * len);
    *arr = *num_array;

    NumberArray* res = malloc(sizeof(NumberArray));
    *res = (NumberArray){len, arr};

    return res;
}

NumberArray* new_number_array_random(int count, int max) {
    int i, j;
    srand(time(NULL));
    Number** arr = malloc(sizeof(Number) * count);
    for (size_t i = 0; i < count; i++)
        arr[i] = new_number(i*2, i);

    NumberArray* res = malloc(sizeof(NumberArray));
    *res = (NumberArray){count, arr};

    i = count;
    while(i != 0){
        j = ((float)(rand()) / RAND_MAX)*i;
        number_array_swap(res, --i, j);
    }

    return res;
}

void render_number_array(NumberArray* num_arr) {
    for (size_t idx = 0; idx < num_arr->length; idx++) {
        Number* num = number_array_get(num_arr, idx);
        render_number(num, false); // FIXME: whatever this is
        printf("%d, ", num->value);
    }
    printf("\n");
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
