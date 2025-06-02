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

    std::queue<InputToken> processClicks();

private:
    std::shared_ptr<sf::RenderWindow> window_;
};
