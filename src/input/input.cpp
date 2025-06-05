// Filename: Input.cpp
//
// Description:
//     Implements the MVC::Input class method for polling and dispatching user input
//     events to game objects using InputTokens.
//
// Authors: Krzysztof Rutkowski, Piotr Pyrak
#include "input.h"
#include "inputtoken.h"

void MVC::Input::pollEvents(std::vector<std::shared_ptr<GameObject>>& all_objects) {
    logEvent_.value()->invoke("Polling events", Util::Level::DEBUG);

    auto tokens = ip.processClicks();
    while (!tokens.empty()) {
        const auto& token = tokens.front();
        tokens.pop();

        for (const auto& obj : all_objects) {
            if (obj->input(token))
                break;
        }
    }
}
