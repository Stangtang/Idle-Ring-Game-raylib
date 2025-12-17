#include "save.h"
#include "ring.h"
#include "shop.h"
#include <fstream>
#include <chrono>

const char* save_file_name = "save.dat";

void save_game() {
    std::ofstream file(save_file_name);
    if (!file.is_open()) return;

    auto now = std::chrono::system_clock::now();
    auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    file << "money " << money << "\n";
    file << "current_ring " << current_ring << "\n";
    file << "timestamp " << now_seconds << "\n";
    file << "#_rings " << rings.size() << "\n";

    for (const Ring& ring : rings) {
        file << ring.ring_number << " " << ring.current_angle << "\n";
    }

    file.close();
}

void load_game() {
    std::ifstream file(save_file_name);
    if (!file.is_open()) return;

    std::string label;
    int64_t saved_seconds;
    unsigned int num_rings;

    file >> label >> money;
    file >> label >> current_ring;
    file >> label >> saved_seconds;
    file >> label >> num_rings;

    for (int i = 0; i < num_rings; i++) {
        unsigned int ring_number;
        double angle;
        file >> ring_number >> angle;

        rings.emplace_back(ring_number,
            ring_info_map.at(ring_number).radius,
            ring_info_map.at(ring_number).speed,
            ring_info_map.at(ring_number).color
        );
        rings.back().current_angle = angle;
    }

    file.close();

    auto now = std::chrono::system_clock::now();
    auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    double seconds_offline = static_cast<double>(now_seconds - saved_seconds);
    if (seconds_offline > 0) {
        for (int i = rings.size() - 1; i >= 0; i--) {
            unsigned long long rotations = static_cast<unsigned long long>((rings[i].speed * seconds_offline) / 360.0);
            money += rotations * (rings.size() - i);
        }
    }
}
