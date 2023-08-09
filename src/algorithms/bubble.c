#include "algorithms.h"

void bubble_sort(BarArray* arr, UpdateCallback upd) {
    size_t arr_len = arr->length;

    for (size_t i = 0; i < arr_len - 1; i++) {
        for (size_t j = 0; j < arr_len - i - 1; j++) {
            if (bar_array_get(arr, j) > bar_array_get(arr, j + 1))
                bar_array_swap(arr, j, j + 1);

            arr->targets.first = j;
            arr->targets.second = j + 1;

            upd(arr);
        }
    }
}
