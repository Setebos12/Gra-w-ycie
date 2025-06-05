// Filename: input.h
//
// Description:
//     Defines the MVC::Input class, responsible for polling and processing
//     input events from the SFML render window.
//     
//
// Authors: Krzysztof Rutkowski, Piotr Pyrak

#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "gameobject.h"
#include "InputPoller.h"

namespace MVC {
class Input {
public:
    Input(std::shared_ptr<sf::RenderWindow> window)
        : ip(InputPoller(window)) {}

    void pollEvents(std::vector<std::shared_ptr<MVC::GameObject>>& all_objects);

private:
    InputPoller ip;
};
} // namespace MVC
