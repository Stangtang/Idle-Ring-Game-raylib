#include "raylib.h"
#include <iostream>
#include <vector>
#include "ring.h"
#include "shop.h"
#include "save.h"

const Color background_color = RAYWHITE;

int main() {
    const unsigned int screen_width = 1500;
    const unsigned int screen_height = 1000;

    InitWindow(screen_width, screen_height, "Idle Ring");
    SetTargetFPS(120);

    load_game();

    if (rings.empty()) {
        rings.emplace_back(1,
            ring_info_map.at(1).radius,
            ring_info_map.at(1).degrees_per_second,
            ring_info_map.at(1).color
        );
        money = 0;
        current_ring = 1;
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        for (int i = 0; i < rings.size(); i++) {
            rings[i].current_angle += rings[i].degrees_per_second * dt;
            if (rings[i].current_angle >= 360) {
                rings[i].current_angle -= 360;
                money += rings.size() - i;
            }
        }

        BeginDrawing();

        ClearBackground(background_color);

        draw_rings(rings, screen_width, screen_height, background_color);

        handle_shop();

        EndDrawing();
    }

    save_game();

    CloseWindow();
}
