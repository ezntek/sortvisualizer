#define _POSIX_C_SOURCE 200809L

#include <pthread.h>

#include <bits/pthreadtypes.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../config.h"
#include "number.h"

bool CAN_I_DRAW_PLS = false;

struct Sorter {
    NumberArray* arr;
    pthread_t sorter_thread;
    pthread_mutex_t arr_mutex;
};

// for the thread
typedef struct SortFuncCtx {
    NumberArray* num_arr;
    pthread_mutex_t* arr_mutex;
} SortFuncCtx;

void sleep_us(double time) {
    nanosleep(&(struct timespec){0, time * 1000}, NULL);
}

void* bubble_sort(SortFuncCtx* ctx) {
    size_t arr_len = ctx->num_arr->length;

    for (size_t i = 0; i < arr_len - 1; i++) {
        for (size_t j = 0; j < arr_len - i - 1; j++) {
            pthread_mutex_lock(ctx->arr_mutex);

            bool cond = number_array_get(ctx->num_arr, j)->value >
                        number_array_get(ctx->num_arr, j + 1)->value;
            if (cond)
                number_array_swap(ctx->num_arr, j, j + 1);

            pthread_mutex_unlock(ctx->arr_mutex);

            CAN_I_DRAW_PLS = true;

            sleep_us((ARR_ACCESS_DELAY * 100));
        }
    }

    return NULL;
}

void insert_sort(NumberArray* num_arr) {
    size_t arr_len = num_arr->length;

    for (size_t i = 1; i < arr_len; i++) {
        size_t j = i;

        while (j > 0 && number_array_get(num_arr, j - 1)->value >
                            number_array_get(num_arr, j)->value) {
            number_array_swap(num_arr, j, j - 1);
            j--;

            BeginDrawing();
            ClearBackground(BLACK);
            number_array_render(num_arr);
            EndDrawing();

            sleep_us((ARR_ACCESS_DELAY * 1000));
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
        number_array_render(num_arr);
        EndDrawing();

        sleep_us((ARR_ACCESS_DELAY * 1000));
    }
}

void sorter_init(struct Sorter* s) {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Sort Visualizer");
}

void sorter_deinit(struct Sorter* s) {
    pthread_join(s->sorter_thread, NULL);
    number_array_free(s->arr);
    CloseWindow();
    pthread_exit(0);
}

void run(struct Sorter* s) {
    sorter_init(s);

    SortFuncCtx _ctx = (SortFuncCtx){s->arr, &s->arr_mutex};
    pthread_create(&s->sorter_thread, NULL,
                   (void*)bubble_sort, // BUG: this looks very wrong
                   &_ctx);

    while (!WindowShouldClose()) {
        while (!CAN_I_DRAW_PLS) {
            continue;
        }

        pthread_mutex_lock(&s->arr_mutex);
        BeginDrawing();
        ClearBackground(BLACK);
        number_array_render(s->arr);
        EndDrawing();
        pthread_mutex_unlock(&s->arr_mutex);
        CAN_I_DRAW_PLS = false;
    }
    puts("deinit");
    sorter_deinit(s);
}

int main() {
    NumberArray* num_arr = new_number_array_random(ELEMS, 1000);
    struct Sorter s = (struct Sorter){
        .arr = num_arr,
        .arr_mutex = NULL,
        .sorter_thread = NULL,
    };

    run(&s);
}
