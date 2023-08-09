#include "algorithms.h"

void insert_sort(BarArray* arr, UpdateCallback upd) {
    size_t arr_len = arr->length;

    for (size_t i = 1; i < arr_len; i++) {
        size_t j = i;

        while (j > 0 && bar_array_get(arr, j - 1) > bar_array_get(arr, j)) {
            bar_array_swap(arr, j - 1, j);
            j--;

            arr->targets.first = j;
            arr->targets.second = j - 1;

            upd(arr);
        }
    }
}
