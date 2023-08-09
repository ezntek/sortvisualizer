#include "algorithms.h"

void select_sort(BarArray* arr, UpdateCallback upd) {
    size_t arr_len = arr->length;

    for (size_t i = 0; i < arr_len; i++) {
        arr->targets.first = i;

        size_t min_elem_idx = i;
        for (size_t j = i + 1; j < arr_len; j++) {
            arr->targets.second = j;

            if (bar_array_get(arr, j) < bar_array_get(arr, min_elem_idx)) {
                min_elem_idx = j;
                upd(arr);
            } else {
                upd(arr);
            }
        }

        if (min_elem_idx != i)
            bar_array_swap(arr, i, min_elem_idx);

        upd(arr);
    }
}
