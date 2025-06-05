// Filename: InputPoller.cpp
//
// Description:
//     Implements the InputPoller class method for detecting and converting
//     mouse input events into a queue of InputTokens.
//
// Authors: Krzysztof Rutkowski, Piotr Pyrak


#include "InputPoller.h"
using namespace INPUT;

std::queue<InputToken> InputPoller::processClicks() {
    std::queue<InputToken> tokens;

    if (!window_ || !window_->hasFocus()) return tokens;

    const auto onMouseReleased = [this, &tokens](const sf::Event::MouseButtonReleased& mousePressed) {
        tokens.emplace(InputToken(TokenType::LEFT_MOUSE_RELEASED, sf::Mouse::getPosition(*window_)));
        };

    const auto onMousePressed = [this, &tokens](const sf::Event::MouseButtonPressed& mousePressed) {
        tokens.emplace(InputToken(TokenType::LEFT_MOUSE_PRESSED, sf::Mouse::getPosition(*window_)));
        };

    window_->handleEvents(onMouseReleased, onMousePressed);

    bool mousePressedNow = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (mousePressedNow) {
        tokens.emplace(InputToken(TokenType::LEFT_MOUSE_DOWN, sf::Mouse::getPosition(*window_)));
    }

    return tokens;
}