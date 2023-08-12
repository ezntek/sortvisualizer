#include <stdio.h>
#include <stdlib.h>

#include "../util.h"
#include "algorithms.h"
#include "src/array/array.h"

BarArray* full_arr;

void merge_sort(BarArray* arr, UpdateCallback upd) {
    if (full_arr == NULL)
        full_arr = arr;

    if (arr->length < 2)
        return;

    const size_t mid = arr->length / 2;

    BarArray* left_arr = bar_array_split_left(arr, mid);
    BarArray* right_arr = bar_array_split_right(arr, mid);

    merge_sort(left_arr, upd);
    merge_sort(right_arr, upd);

    size_t l_arr_idx = 0, r_arr_idx = 0, merged_arr_idx = 0;
    for (; l_arr_idx < left_arr->length && r_arr_idx < right_arr->length;
         merged_arr_idx++) {

        int l_arr_curr_item = bar_array_get(left_arr, l_arr_idx);
        int r_arr_curr_item = bar_array_get(right_arr, r_arr_idx);
        if (l_arr_curr_item <= r_arr_curr_item) {
            bar_array_set(arr, merged_arr_idx, l_arr_curr_item);
            l_arr_idx++;
        } else if (l_arr_curr_item > r_arr_curr_item) {
            bar_array_set(arr, merged_arr_idx, r_arr_curr_item);
            r_arr_idx++;
        }
    }

    for (; l_arr_idx < left_arr->length; merged_arr_idx++) {
        bar_array_set(arr, merged_arr_idx, bar_array_get(left_arr, l_arr_idx));
        l_arr_idx++;
    }

    for (; r_arr_idx < right_arr->length; merged_arr_idx++) {
        bar_array_set(arr, merged_arr_idx, bar_array_get(right_arr, r_arr_idx));
        r_arr_idx++;
    }

    upd(full_arr);
}
