#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "algorithms/algorithms.h"
#include "array/array.h"
#include "config.h"
#include "util.h"

struct State {
    BarArray* arr;
};

void init(struct State* state) {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Sort Visualizer");
}

void deinit(struct State* state) {
    bar_array_unload(state->arr);
    CloseWindow();
}

void update(BarArray* arr) {
    if (WindowShouldClose()) {
        bar_array_unload(arr);
        CloseWindow();
        exit(0);
    } // FIXME: use a proper unload function

    char* text;
    asprintf(&text, "Reads: %d, Writes: %d", (int)arr->accesses.read,
             (int)arr->accesses.write);

    BeginDrawing();
    ClearBackground(BLACK);
    bar_array_render(arr);
    DrawText(text, 20, 20, 20, GREEN);
    EndDrawing();
}

void run_sort(BarArray* arr, UpdateCallback upd) {
    switch (ALGORITHM) {
    case BUBBLE:
        bubble_sort(arr, upd);
        return;
    case INSERT:
        insert_sort(arr, upd);
        return;
    case SELECT:
        select_sort(arr, upd);
        return;
    }
}

int main() {
    struct State s = (struct State){new_bar_array_random(ELEMS, 1000)};

    init(&s);
    run_sort(s.arr, update);
    deinit(&s);
}
