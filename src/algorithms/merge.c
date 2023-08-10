#include "../util.h"
#include "algorithms.h"

void merge_sort(BarArray* arr, UpdateCallback upd) {
    const size_t arr_len = arr->length;

    const size_t begin = 0;
    const size_t mid = (arr_len - 1) / 2;
    const size_t end = arr_len - 1;
}
