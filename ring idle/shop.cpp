#include "shop.h"

unsigned long long money;

unsigned long long get_ring_price(const unsigned int& ring_number) {
    //return 3.9 * std::pow(1.6, ring_number);
    return static_cast<unsigned long long>(std::round(1.03 * std::pow(2.2, ring_number)));
}

void draw_money() {
    const std::string money_string = "MONEY: $" + std::to_string(money);
    const char* money_c_string = money_string.c_str();
    DrawText(money_c_string, 5, 50, 32, BLACK);
}

void handle_shop() {
    Vector2 mouse_position = GetMousePosition();

    draw_money();

    const unsigned int shop_area_x = 1200;
    const unsigned int shop_area_y = 25;
    const unsigned int shop_area_width = 275;
    const unsigned int shop_area_height = 950;
    Rectangle shop_area = { shop_area_x, shop_area_y, shop_area_width, shop_area_height };
    DrawRectangleRounded(shop_area, 0.125, 10, LIGHTGRAY);
    const char* shop_text = "SHOP";
    const unsigned int shop_text_font_size = 50;
    const unsigned int shop_text_x = (2 * shop_area_x + shop_area_width - MeasureText(shop_text, shop_text_font_size)) / 2;
    DrawText(shop_text, shop_text_x, 50, shop_text_font_size, BLACK);

    const unsigned int buy_ring_button_width = 252;
    const unsigned int buy_ring_button_height = 90;
    const unsigned int buy_ring_button_x = shop_area_x + (shop_area_width - buy_ring_button_width) / 2;
    const unsigned int buy_ring_button_y = 120;
    Rectangle buy_ring_button_area = { buy_ring_button_x, 120, buy_ring_button_width, buy_ring_button_height };
    DrawRectangleRounded(buy_ring_button_area, 0.125, 10, GRAY);
    const unsigned long long next_ring_price = get_ring_price(current_ring + 1);
    const std::string buy_ring_button_text = "BUY NEXT RING: $" + std::to_string(next_ring_price);
    const char* max_rings_text = "MAX RINGS PURCHASED";
    const unsigned int buy_ring_button_font_size = 20;
    const unsigned int buy_ring_button_text_x = (2 * buy_ring_button_x + buy_ring_button_width - MeasureText(buy_ring_button_text.c_str(), buy_ring_button_font_size)) / 2;
    const unsigned int buy_ring_button_text_y = (2 * buy_ring_button_y + buy_ring_button_height - buy_ring_button_font_size) / 2;
    if (current_ring == maximum_number_of_rings) {
        DrawText(max_rings_text, 
            (2 * buy_ring_button_x + buy_ring_button_width - MeasureText(max_rings_text, buy_ring_button_font_size)) / 2,
            (2 * buy_ring_button_y + buy_ring_button_height - buy_ring_button_font_size) / 2,
            buy_ring_button_font_size, BLACK);
    }
    else {
        DrawText(buy_ring_button_text.c_str(), buy_ring_button_text_x, buy_ring_button_text_y, buy_ring_button_font_size, BLACK);
        if (CheckCollisionPointRec(mouse_position, buy_ring_button_area) && 
                                   IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                                   money >= next_ring_price) {
            money -= next_ring_price;
            add_new_ring(rings, current_ring + 1);
            current_ring++;
        }
    }
}