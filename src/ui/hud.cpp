#pragma once

#include "hud.h"
#include "../render/drawer.h"

#include <string>
#include <sstream>

void Hud::update_values(const int& generation_number, const int& alive_cells) {
    generation_ = generation_number;
    alive_cells_ = alive_cells;
}

void Hud::draw(Drawer& drawer) {
    std::ostringstream ss;
    ss << "Generation: " << generation_ << "  Alive: " << alive_cells_;
    drawer.drawText(ss.str(), 10, 10);
}

void Hud::update() {
    generation_ += 1;
}