#pragma once

#include "hud.h"
#include "../render/drawer.h"

#include <string>
#include <sstream>

void Hud::update_values(const int alive_cells, const int speed_) {
    alive_cells_ = alive_cells;
    speed = speed_;
}

void Hud::draw(Render::Drawer& drawer) {
    std::ostringstream ss;
    ss << "Generation: " << generation_;
    ss << std::endl << "Time Speed: " << speed;
    drawer.drawText(ss.str(), position_, 24, sf::Color::Red);
}

void Hud::update() {
    generation_ += 1;
}