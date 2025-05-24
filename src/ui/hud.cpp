#pragma once

#include "hud.h"
#include "../render/drawer.h"

#include <string>
#include <sstream>

void Hud::update_values(const int& generation_number, const int& alive_cells = 0) {
    generation_ = generation_number;
    alive_cells_ = alive_cells;
}

void Hud::draw(Render::Drawer& drawer) {
    std::ostringstream ss;
    ss << "Generation: " << generation_ << std::endl <<"  Alive: " << alive_cells_;
    drawer.drawText(ss.str(), position_, 24, sf::Color::Red);
}

void Hud::update() {
    generation_ += 1;
}