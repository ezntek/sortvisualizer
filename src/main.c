#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>

#include "../config.h"
#include "number.h"

struct Sorter {
    NumberArray* arr;
};

void bubble_sort(NumberArray* num_arr) {
    size_t arr_len = num_arr->length;

    for (size_t i = 0; i < arr_len - 1; i++) {
        for (size_t j = 0; j < arr_len - i - 1; j++) {
            bool cond = number_array_get(num_arr, j)->value >
                        number_array_get(num_arr, j + 1)->value;
            if (cond)
                number_array_swap(num_arr, j, j + 1);

            BeginDrawing();
            ClearBackground(BLACK);
            render_number_array(num_arr);
            EndDrawing();

            usleep((ARR_ACCESS_DELAY * 1000));
        }
    }
}

void select_sort(NumberArray* num_arr) {
    size_t arr_len = num_arr->length;
    size_t min_idx;

    for (size_t i = 0; i < arr_len; i++) {
        min_idx = i;
        for (size_t j = i + 1; j < arr_len; j++) {
            bool cond = number_array_get(num_arr, j)->value <
                        number_array_get(num_arr, min_idx)->value;
            if (cond)
                min_idx = j;
        }
        if (min_idx != i)
            number_array_swap(num_arr, min_idx, i);

        BeginDrawing();
        ClearBackground(BLACK);
        render_number_array(num_arr);
        EndDrawing();

        usleep((ARR_ACCESS_DELAY * 1000));
    }
}

void sorter_init(struct Sorter* s) {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Sort Visualizer");
}

void sorter_deinit(struct Sorter* s) {
    number_array_free(s->arr);
    CloseWindow();
}

void run(struct Sorter* s) {
    sorter_init(s);
    select_sort(s->arr);
    sorter_deinit(s);
}

int main() {
    NumberArray* num_arr = new_number_array_random(ELEMS, 1000);
    struct Sorter s = (struct Sorter){num_arr};

    run(&s);
}
