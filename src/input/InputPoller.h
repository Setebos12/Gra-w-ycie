#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <queue>
#include "InputToken.h"

class InputPoller {
public:
    InputPoller(std::shared_ptr<sf::RenderWindow> window) : window_(std::move(window)) {}

    std::queue<InputToken> processClicks() {
        std::queue<InputToken> tokens;

        if (!window_ || !window_->hasFocus()) return tokens;

        const auto onMousePressed = [this, &tokens](const sf::Event::MouseButtonReleased& mousePressed) {
            tokens.emplace(InputToken(TokenType::LEFT_MOUSE_REALESED,sf::Mouse::getPosition(*window_)));
        };

        window_->handleEvents(onMousePressed);

        bool mousePressedNow = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        if (mousePressedNow) {
            tokens.emplace(InputToken(TokenType::LEFT_MOUSE_DOWN, sf::Mouse::getPosition(*window_)));
        }

        return tokens;
    }

private:
    std::shared_ptr<sf::RenderWindow> window_;
};
