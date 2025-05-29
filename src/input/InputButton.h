#pragma once

#include "../core/gameobject.h"
#include <SFML/System/Vector2.hpp>
#include <string>
#include <functional>

class InputButton : public MVC::GameObject {
public:
    InputButton(const std::string& name,
        const sf::Vector2f& position,
        const sf::Vector2f& size,
        const std::string& label,
        std::function<void()> onClick)
        : MVC::GameObject(name),
        position_(position),
        size_(size),
        label_(label),
        pressed_(false),
        onClick_(std::move(onClick)) {
    }

    void draw(Render::Drawer& drawer) override {
        sf::Color color = pressed_ ? sf::Color::Red : sf::Color::Green;
        drawer.drawRect(position_, size_, color);
        drawer.drawText(
            label_,
            sf::Vector2f{
                position_.x + size_.x / 8.f,
                position_.y + size_.y / 8.f
            },
            18,
            sf::Color::Black
        );
    }

    void update() override {}

    std::string printString() const override { return " "; }
    void readString(const std::string& read) override {}

    void setPressed(bool pressed) { pressed_ = pressed; }
    bool isPressed() const { return pressed_; }

    void input(InputEvent& events) {
        events.watchSingleClickRect(position_, size_, [this]() {
            if (onClick_) onClick_();
            });
    }


    sf::Vector2f position_;
    sf::Vector2f size_;
    std::string label_;

private:
    bool pressed_;

    std::function<void()> onClick_;
};