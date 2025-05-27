//Filename: logic.cpp
//
//Implementation of logic
//
//Author: Piotr Pyrak

#include "logic.h"

using namespace MVC;

void Logic::step(std::vector<std::shared_ptr<GameObject>>& all_objects) {
	if (!running_)
		return;

	for (const auto &obj : all_objects) {
		obj->update();
	}
}

void Logic::handleControl(Input& input, int& simDelayMs, bool& running) {
    InputToken token;
    while ((token = input.nextToken()) != InputToken::Unknown) {
        switch (token) {
        case InputToken::Start:
            start();
            input.setmode(0);
            break;
        case InputToken::Stop:
            pause();
            break;
        case InputToken::End:
            running = false;
            break;
        case InputToken::ToggleDraw:
            pause();
            input.setmode(1);
            break;
        case InputToken::SpeedUp:
            simDelayMs = std::max(10, simDelayMs - 10);
            break;
        case InputToken::SpeedDown:
            simDelayMs += 10;
            break;
        default:
            break;
        }
    }
}

void Logic::start() {
	running_ = true;
}

void Logic::pause() {
	running_ = false;
}
