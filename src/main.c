#include <raylib.h>
#include <stdlib.h>

#include "config.h"

void init() { InitWindow(WIN_WIDTH, WIN_HEIGHT, "Sort Visualizer"); }

void deinit() { CloseWindow(); }

void loop() {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
}

int main() {
    init();
    while (!WindowShouldClose()) {
        loop();
    }
    deinit();
}
