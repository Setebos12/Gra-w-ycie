#include "Input.h"

void MVC::Input::pollEvents(std::vector<std::unique_ptr<GameObject>>& all_objects) {
    ip.processClicks();
    for (auto& obj : all_objects) {
        obj->input(ip);
    }
}

