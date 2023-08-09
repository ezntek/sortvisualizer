#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "config.h"
#include "util.h"

Bar make_bar(int value, size_t idx) {
    float bar_width = (float)WIN_WIDTH / ELEMS - BARS_PADDING;
    float bar_height = value * HEIGHT_SCALE_FACTOR;
    float bar_x = (idx * bar_width) + (BARS_PADDING * idx);
    float bar_y = WIN_HEIGHT - bar_height;

    Rectangle rect = (Rectangle){bar_x, bar_y, bar_width, bar_height};
    return (Bar){
        .value = value,
        .rect = rect,
    };
}

Bar* new_bar(int value, size_t idx) {
    Bar* res = malloc(sizeof(Bar));
    *res = make_bar(value, idx);

    return res;
}

void bar_render(Bar* bar, bool is_target) {
    Color color = BLACK;
    if (is_target)
        color = RED;

    DrawRectangleRec(bar->rect, color);
}

void bar_set_value(Bar* bar, int new_val) {
    float new_height = new_val * HEIGHT_SCALE_FACTOR;
    bar->rect.y = WIN_HEIGHT - new_height;
    bar->rect.height = new_height;

    bar->value = new_val;
}

void bar_unload(Bar* bar) { free(bar); }

BarArray* new_bar_array(int count, int max) {
    BarArray* res = malloc(sizeof(BarArray));
    Bar** bars = malloc(sizeof(Bar) * count);

    srand(time(NULL));
    for (size_t i = 0; i < max; i++) {
        int value = rand() % max;
        bars[i] = new_bar(value, i);
    }

    *res = (BarArray){
        ._bars = bars,
        .length = count,
        .accesses = (struct Accesses){NULL, NULL},
    };

    return res;
}

void bar_array_render(BarArray* b_arr) {
    for (size_t i = 0; i < b_arr->length; i++) {
        bar_render(b_arr->_bars[i], false);
    }
}

int bar_array_get(BarArray* b_arr, size_t idx) {
    if (idx >= b_arr->length) {
        printf("fatal: attemped to %d outside of the array bounds", (int)idx);
        exit(1);
    }
    b_arr->accesses.read++;
    access_delay();
    return b_arr->_bars[idx]->value;
}

Bar* bar_array_get_bar(BarArray* b_arr, size_t idx) {
    if (idx >= b_arr->length) {
        printf("fatal: attemped to %d outside of the array bounds", (int)idx);
        exit(1);
    }

    b_arr->accesses.read++;
    access_delay();
    return b_arr->_bars[idx];
}

void bar_array_set(BarArray* b_arr, size_t idx, int value) {
    if (idx >= b_arr->length) {
        printf("fatal: attemped to %d outside of the array bounds", (int)idx);
        exit(1);
    }

    b_arr->accesses.write++;
    access_delay();
    bar_set_value(bar_array_get_bar(b_arr, idx), value);
}

void bar_array_set_bar(BarArray* b_arr, size_t idx, Bar* bar) {
    if (idx >= b_arr->length) {
        printf("fatal: attemped to %d outside of the array bounds", (int)idx);
        exit(1);
    }

    b_arr->accesses.write++;
    access_delay();
    b_arr->_bars[idx] = bar;
}

void bar_array_swap(BarArray* b_arr, size_t idx1, size_t idx2) {
    Bar* a = bar_array_get_bar(b_arr, idx1);
    Bar* b = bar_array_get_bar(b_arr, idx1);

    int tmp = a->value;
    bar_set_value(a, b->value);
    bar_set_value(b, tmp);
}

void bar_array_unload(BarArray* b_arr) {
    for (size_t i = 0; i < b_arr->length; i++)
        free(bar_array_get_bar(b_arr, i));
    free(b_arr);
}
