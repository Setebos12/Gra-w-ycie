//Filename: hud.h
//
//Display that shows most important information from simulation to screen
//
//Author: Piotr Pyrak, Krzysztof Rutkowski

#pragma once

#include "../core/gameobject.h"
#include "../render/drawer.h"
#include <sstream>

class Hud : public MVC::GameObject {
public:
    Hud(const std::string& name, const sf::Vector2f& pos)
        : MVC::GameObject(name), position_(pos), generation_(0) {
    }

    void draw(Render::Drawer& drawer) override;
    void update() override {}

    void updateGeneration(int newGeneration_) { generation_ = newGeneration_; }

    std::string printString() const override {
        return "name";
    }

    void readString(const std::string& read) override {
    }

private:
    sf::Vector2f position_;
    int generation_;
};
