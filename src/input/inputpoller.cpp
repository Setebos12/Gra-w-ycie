// Filename: InputPoller.cpp
//
// Description:
//     Implements the InputPoller class method for detecting and converting
//     mouse input events into a queue of InputTokens.
//
// Authors: Krzysztof Rutkowski, Piotr Pyrak


#include "inputpoller.h"

using namespace InputPoll;

InputPoller::InputPoller(std::shared_ptr<sf::RenderWindow> window) : window_(std::move(window)),
    onMouseReleased_([this](const sf::Event::MouseButtonReleased& mousePressed) {
        tokens_.emplace(InputToken(TokenType::LEFT_MOUSE_RELEASED, sf::Mouse::getPosition(*window_)));
    }),
    onMousePressed_([this](const sf::Event::MouseButtonPressed& mousePressed) {
        tokens_.emplace(InputToken(TokenType::LEFT_MOUSE_PRESSED, sf::Mouse::getPosition(*window_)));
    }) {
}

std::queue<InputToken> InputPoller::processClicks() {
    while (!tokens_.empty()) tokens_.pop();

    if (!window_ || !window_->hasFocus()) return tokens_;

    window_->handleEvents(onMouseReleased_, onMousePressed_);

    bool mousePressedNow = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (mousePressedNow) {
        tokens_.emplace(InputToken(TokenType::LEFT_MOUSE_DOWN, sf::Mouse::getPosition(*window_)));
    }

    return tokens_;
}
