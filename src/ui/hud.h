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
        : MVC::GameObject(name), position_(pos), speed(0), generation_(0), alive_cells_(0){
    }

    void update_values(const int alive_cells = 0, const int speed_ = 0);

    void draw(Render::Drawer& drawer) override;
    void update() override;

    std::string printString() const { 
        return "name";
    }

    void readString(const std::string& read) {
    }

private:
    sf::Vector2f position_;
    int speed;
    int generation_;
    int alive_cells_;
};
