// Filename: InputPoller.h
//
// Description:
//     Declares the InputPoller class, which captures and processes mouse input events,
//     converting them into InputTokens for further handling.
//
// Authors: Krzysztof Rutkowski, Piotr Pyrak

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <queue>
#include "InputToken.h"

namespace InputPoll {

    class InputPoller {
    public:
        InputPoller(std::shared_ptr<sf::RenderWindow> window);

        std::queue<InputToken> processClicks();

    private:
        std::shared_ptr<sf::RenderWindow> window_;

        const std::function<void(const sf::Event::MouseButtonReleased&)> onMouseReleased_;
        const std::function<void(const sf::Event::MouseButtonPressed&)> onMousePressed_;
        std::queue<InputToken> tokens_;
    };
} // namespace InputPoll