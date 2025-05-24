//Filename: hud.h
//
//Display that shows most important information from simulation to screen
//
//Author: Piotr Pyrak, Krzysztof Rutkowski

#pragma once

#include "../core/gameobject.h"

class Hud : public MVC::GameObject {
public:
    Hud(const std::string& name, const sf::Vector2f& pos)
        : MVC::GameObject(name), position_(pos) {
    }

    void update_values(const int& generation_number, const int& alive_cells);

    void draw(Render::Drawer& drawer) override;
    void update() override;

    std::string printString() const { 
        return "name";
    }

    void readString(const std::string& read) {
    }

private:
    sf::Vector2f position_;

    int generation_;
    int alive_cells_;
};
