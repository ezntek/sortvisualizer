#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array.h"
#include "config.h"
#include "src/array/bar.h"

BarArray* new_bar_array(Bar** bar_slice, size_t length) {
    BarArray* res = malloc(sizeof(BarArray));
    *res = (BarArray){
        ._bars = bar_slice,
        .length = length,
        .accesses = (struct Accesses){0, 0},
        .targets = (struct Targets){0, 0},
    };

    return res;
}

BarArray* new_bar_array_random(int count, int max) {
    BarArray* res = malloc(sizeof(BarArray));
    Bar** bars = malloc(sizeof(Bar*) * count);

    srand(time(NULL));
    for (size_t i = 0; i < count; i++) {
        int value = rand() % max;
        bars[i] = new_bar(value, i);
    }

    *res = (BarArray){
        ._bars = bars,
        .length = count,
        .accesses = (struct Accesses){0, 0},
        .targets = (struct Targets){0, 0},
    };

    return res;
}

void bar_array_render(BarArray* b_arr) {
    for (size_t i = 0; i < b_arr->length; i++) {
        bool is_target = false;
        if (b_arr->targets.first == i || b_arr->targets.second == i)
            is_target = true;
        Bar* bar = b_arr->_bars[i];
        bar_render(bar, is_target);

        printf("%d, ", bar->value);
    }
    printf("\n");
}

int bar_array_get(BarArray* b_arr, size_t idx) {
    if (idx >= b_arr->length) {
        printf(
            "fatal: attemped to index %d which is outside of the array bounds",
            (int)idx);
        exit(1);
    }
    b_arr->accesses.read++;
    sleep_for_access_delay();
    return b_arr->_bars[idx]->value;
}

Bar* bar_array_get_bar(BarArray* b_arr, size_t idx) {
    if (idx >= b_arr->length) {
        printf(
            "fatal: attemped to index %d which is outside of the array bounds",
            (int)idx);
        exit(1);
    }

    b_arr->accesses.read++;
    sleep_for_access_delay();
    return b_arr->_bars[idx];
}

void bar_array_set(BarArray* b_arr, size_t idx, int value) {
    if (idx >= b_arr->length) {
        printf(
            "fatal: attemped to index %d which is outside of the array bounds",
            (int)idx);
        exit(1);
    }

    b_arr->accesses.write++;
    sleep_for_access_delay();
    bar_set_value(bar_array_get_bar(b_arr, idx), value);
}

void bar_array_set_bar(BarArray* b_arr, size_t idx, Bar* bar) {
    if (idx >= b_arr->length) {
        printf(
            "fatal: attemped to index %d which is outside of the array bounds",
            (int)idx);
        exit(1);
    }

    b_arr->accesses.write++;
    sleep_for_access_delay();
    b_arr->_bars[idx] = bar;
}

void bar_array_swap(BarArray* b_arr, size_t idx1, size_t idx2) {
    Bar* a = bar_array_get_bar(b_arr, idx1);
    Bar* b = bar_array_get_bar(b_arr, idx2);

    b_arr->accesses.write += 2;

    int tmp = a->value;
    bar_set_value(a, b->value);
    bar_set_value(b, tmp);
}

BarArray* bar_array_split_left(BarArray* b_arr, size_t idx_until) {
    Bar** bars_slice = malloc(sizeof(Bar*) * idx_until);

    for (size_t i = 0; i < idx_until; i++)
        bars_slice[i] = b_arr->_bars[i];

    return new_bar_array(bars_slice, idx_until);
}

BarArray* bar_array_split_right(BarArray* b_arr, size_t idx_from) {
    size_t length = b_arr->length - idx_from;
    Bar** bars_slice = malloc(sizeof(Bar*) * length);

    for (size_t i = idx_from; i < b_arr->length; i++)
        bars_slice[i - idx_from] = b_arr->_bars[i];

    return new_bar_array(bars_slice, length);
}

void bar_array_unload(BarArray* b_arr) {
    for (size_t i = 0; i < b_arr->length; i++)
        free(b_arr->_bars[i]);
    free(b_arr->_bars); // do free the pointer holding the pointers itself
    free(b_arr);
}
