#include <stdio.h>
#include <stdlib.h>

#include "bar.h"
#include "config.h"

Bar make_bar(int value, size_t idx) {
    float bar_width = (float)WIN_WIDTH / ELEMS - BARS_PADDING;
    float bar_height = value * HEIGHT_SCALE_FACTOR;
    float bar_x = idx * bar_width + BARS_PADDING * idx;
    float bar_y = WIN_HEIGHT - bar_height;

    printf("new bar: x:%.1f y:%.1f w:%.1f h:%.1f\n", bar_x, bar_y, bar_width,
           bar_height);
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
    Color color = WHITE;
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
