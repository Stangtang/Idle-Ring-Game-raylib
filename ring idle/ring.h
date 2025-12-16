#pragma once
#include "raylib.h"
#include <map>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

struct Ring {
    unsigned int ring_number;
    unsigned int radius;
    double current_angle;
    double degrees_per_second;
    Color color;

    Ring(unsigned int n, unsigned int r, double s, Color c)
        : ring_number(n), radius(r), degrees_per_second(s), color(c), current_angle(0) {
    }
};

struct Ring_Info {
    const unsigned int radius;
    const double degrees_per_second;
    const Color color;
};

inline const std::map<unsigned int, Ring_Info> ring_info_map = {
    {1, {50, 100, RED}},
    {2, {83, 90, ORANGE}},
    {3, {116, 80, YELLOW}},
    {4, {149, 70, GREEN}},
    {5, {182, 60, BLUE}},
    {6, {215, 50, PURPLE}},
    {7, {248, 40, PINK}},
    {8, {281, 30, BLACK}},
};

extern unsigned int current_ring;
extern std::vector<Ring> rings;
const unsigned int rings_width = 17;
const unsigned int maximum_number_of_rings = ring_info_map.size();

unsigned int calculate_segments(const unsigned int& radius, const double& current_angle);
void draw_rings(const std::vector<Ring>& rings, const unsigned int& screen_width, const unsigned int& screen_height, const Color& background_color);
void add_new_ring(std::vector<Ring>& rings, const unsigned int& ring_number);