#include "Input.h"
#include "InputToken.h"

void MVC::Input::pollEvents(std::vector<std::shared_ptr<GameObject>>& all_objects) {
    auto tokens = ip.processClicks();
    while (!tokens.empty()) {
        auto token = tokens.front();
        tokens.pop();

        for (auto& obj : all_objects) {
            if (obj->input(token))
                break;
        }
    }
}