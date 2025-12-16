#pragma once
#include "raylib.h"
#include <map>
#include <string>
#include "ring.h"
#include <cmath>

extern unsigned long long money;

void handle_shop();
unsigned long long get_ring_price(const unsigned int& ring_number);
void draw_money();