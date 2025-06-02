// Filename: InputButton.cpp
//
// Description:
//     Implements the InputButton class responsible for drawing a button
//     and handling mouse click interactions.
//
// Author: Krzysztof Rutkowski


#pragma once

#include "../core/gameobject.h"
#include "../util/event.h"
#include <SFML/System/Vector2.hpp>
#include <string>
#include <functional>

class InputButton : public MVC::GameObject {
public:
    InputButton(const std::string& name,
        const sf::Vector2f& position,
        const sf::Vector2f& size,
        const std::string& label,
        Util::Event<>&& onClick)
        : MVC::GameObject(name),
        position_(position),
        size_(size),
        label_(label),
        pressed_(false),
        onClick_(std::move(onClick)) {
    }

    void draw(Render::Drawer& drawer) override;

    void update() override { setPressed(false); }

    std::string printString() const override { return " "; }
    void readString(const std::string& read) override {}

    void setPressed(bool pressed) { pressed_ = pressed; }
    bool isPressed() const { return pressed_; }

    bool input(InputToken& token) override;

    sf::Vector2f position_;
    sf::Vector2f size_;
    std::string label_;

private:
    bool pressed_;

    Util::Event<> onClick_;
};