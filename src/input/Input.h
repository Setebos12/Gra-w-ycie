#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../core/gameobject.h"
#include "../input/InputEvent.h"

namespace MVC {

    class Input {
    public:
        Input(std::shared_ptr<sf::RenderWindow> window)
            : ip(InputEvent(window)) {
        }

        void pollEvents(std::vector<std::shared_ptr<MVC::GameObject>>& all_objects);

    private:
        InputEvent ip;
    };

} // namespace MVC
