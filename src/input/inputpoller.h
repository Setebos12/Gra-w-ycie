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

namespace INPUT {

    class InputPoller {
    public:
        InputPoller(std::shared_ptr<sf::RenderWindow> window) : window_(std::move(window)) {}

        std::queue<InputToken> processClicks();

    private:
        std::shared_ptr<sf::RenderWindow> window_;
    };
}