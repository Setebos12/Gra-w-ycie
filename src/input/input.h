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

#include "../core/gameobject.h"
#include "../input/InputPoller.h"

namespace MVC {
class Input {
public:
    Input(std::shared_ptr<sf::RenderWindow> window, std::optional<std::shared_ptr<Util::Event<const std::string&, Util::Level>>> logEvent)
        : ip(INPUT::InputPoller(window)), logEvent_(logEvent) {}

    void pollEvents(std::vector<std::shared_ptr<MVC::GameObject>>& all_objects);

private:
    INPUT::InputPoller ip;
    std::optional<std::shared_ptr<Util::Event<const std::string&, Util::Level>>>
        logEvent_;
};
} // namespace MVC
