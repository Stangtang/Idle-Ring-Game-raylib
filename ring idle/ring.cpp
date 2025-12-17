#include "ring.h"

unsigned int current_ring;
std::vector<Ring> rings;

unsigned int calculate_segments(const unsigned int& radius, const double& current_angle) {
    return (current_angle * 0.6 + 10) * radius;
}

void draw_rings(const std::vector<Ring>& rings, const unsigned int& screen_width, const unsigned int& screen_height, const Color& background_color) {
    Vector2 screen_center = { screen_width / 2, screen_height / 2 };

    for (const Ring& ring : rings) {
        DrawCircleSector(screen_center, ring.radius,
            0 - 90, ring.current_angle - 90,
            calculate_segments(ring.radius, ring.current_angle),
            ring.color);

        if (ring.ring_number == 1) continue;

        DrawCircleSector(screen_center, ring.radius - rings_width,
            0 - 90, ring.current_angle - 90,
            calculate_segments(ring.radius, ring.current_angle),
            background_color);
    }

    const unsigned int rings_text_spacing_multiplier = 120;
    const unsigned int rings_text_padding_from_edge = 5;
    const unsigned int rings_text_y = 5;
    const unsigned int rings_text_font_size = 28;
    const unsigned int comma_distance = 90;
    for (int i = rings.size() - 1; i >= 0; i--) {
        double ring_filled_percentage = 100 * rings[i].current_angle / 360;
        std::ostringstream oss; oss << std::fixed << std::setprecision(2) << ring_filled_percentage << '%';
        std::string ring_filled_percentage_string = oss.str();
        const char* ring_filled_percentage_c_string = ring_filled_percentage_string.c_str();
        DrawText(ring_filled_percentage_c_string,
            rings_text_padding_from_edge + rings_text_spacing_multiplier * (rings.size() - 1 - i), 
            rings_text_y, rings_text_font_size, rings[i].color);
        DrawText(",",
            rings_text_padding_from_edge + rings_text_spacing_multiplier * (rings.size() - 1 - i) + comma_distance,
            rings_text_y, rings_text_font_size, BLACK);
    }
}

void add_new_ring(std::vector<Ring>& rings, const unsigned int& ring_number) {
    rings.emplace(rings.begin(), ring_number,
        ring_info_map.at(ring_number).radius,
        ring_info_map.at(ring_number).speed,
        ring_info_map.at(ring_number).color);
}