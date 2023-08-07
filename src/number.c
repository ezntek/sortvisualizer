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

void number_render(Number* bar, bool is_target) {
    Color rect_color = WHITE;
    if (is_target) {
        rect_color = RED;
    }

    DrawRectangleRec(bar->inner_rect, rect_color);
}

void number_set_value(Number* bar, int new_val) {
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

void number_array_render(NumberArray* num_arr) {
    for (size_t idx = 0; idx < num_arr->length; idx++) {
        printf("%d: ", (int)idx);
        Number* num = number_array_get(num_arr, idx);
        number_render(num, false); // FIXME: whatever this is
        printf("%d, ", num->value);
    }
    printf("\n\n");
}

Number* number_array_get(NumberArray* num_arr, size_t idx) {
    if (idx > num_arr->length || idx < 0) {
        printf("Attemped to get invalid index %d out of array, exiting.\n",
               (int)idx);
        exit(1);
    }

    return num_arr->_bars[idx];
}

void number_array_set(NumberArray* num_arr, size_t idx, Number* new_val) {
    if (idx > num_arr->length || idx < 0) {
        puts("Attempet to set an item at an invalid index in the array, "
             "exiting.");
        exit(1);
    }

    num_arr->_bars[idx] = new_val;
}

void number_array_swap(NumberArray* num_arr, size_t idx1, size_t idx2) {
    Number* a = number_array_get(num_arr, idx1);
    Number* b = number_array_get(num_arr, idx2);

    int tmp = a->value;
    number_set_value(a, b->value);
    number_set_value(b, tmp);
}

void number_array_free(NumberArray* num_arr) {
    for (size_t idx = 0; idx < num_arr->length; idx++) {
        Number* num = number_array_get(num_arr, idx);
        if (num != NULL)
            free(num);
    };
    free(num_arr);
}
