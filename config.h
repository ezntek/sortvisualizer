#pragma once

#include "src/util.h"

/* Choose the sorting algorithm.
 *
 * Refer to `src/util.h` for more info.
 */
static Algorithm ALGORITHM = INSERT;

/* Set the window width and height. */
static const int WIN_WIDTH = 1200;
static const int WIN_HEIGHT = 800;

/* Change the padding between bars (pixels). */
static const int BARS_PADDING = 2;

/* Change how many elements are supposed to be sorted.. */
static const int ELEMS = 300;

/* Height scale factor.
 * Changes how much numbers should be scaled on the screen.
 *
 * A scale factor of 1 indicates that a value of 1 results in 1 pixel
 * of height.
 */
static const float HEIGHT_SCALE_FACTOR = 0.8;

/* Set the array access delay (miliseconds.) */
static const float ARR_ACCESS_DELAY = 0.08;
