//Filename: hud.h
//
//Display that shows most important information from simulation to screen
//
//Author: Piotr Pyrak, Krzysztof Rutkowski

#include "hud.h"
using namespace Ui;
void Hud::draw(Render::Drawer& drawer) {
    std::ostringstream ss;
    ss << "Generation: " << generation_;

    drawer.drawText(ss.str(), position_, 24, sf::Color::Red);
}