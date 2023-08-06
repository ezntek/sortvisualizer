#include "number.h"
#include <raylib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void render_frame();
void refresh_frame();

void bubble_sort(NumberArray* num_arr) {
    size_t arr_len = num_arr->length;
    for (size_t i = 0; i < arr_len - 1; i++) {
        for (size_t j = 0; j < arr_len - i - 1; j++) {
            bool cond = number_array_get(num_arr, j)->value >
                        number_array_get(num_arr, j + 1)->value;
            if (cond)
                number_array_swap(num_arr, j, j + 1);

            BeginDrawing();
            // printf("render");
            DrawRectangle(50, 50, 100, 100, BLUE);
            ClearBackground(BLACK);
            render_number_array(num_arr);
            EndDrawing();

            nanosleep(&(struct timespec){0, 5000000}, NULL);
        }
    }
}

int main() {
    InitWindow(1200, 800, "Sort Visualizer");

    NumberArray* arr = new_number_array_random(100, 200);

    bubble_sort(arr);

    CloseWindow();
}
