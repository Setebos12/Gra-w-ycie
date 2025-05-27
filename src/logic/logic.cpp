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

void Logic::handleControl(MVC::Input& input,
    int& simDelayMs,
    bool& running,
    Board& board,
    sf::Clock& simClock,
    std::vector<std::shared_ptr<MVC::GameObject>>& objects) {

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

    sf::Vector2i pos;
    while ((pos = input.nextPos()) != sf::Vector2i(-1, -1)) {
        board.toggleCellState(pos.x, pos.y);
    }

    if (simClock.getElapsedTime().asMilliseconds() >= simDelayMs) {
        step(objects);
        simClock.restart();
    }
}


void Logic::start() {
	running_ = true;
}

void Logic::pause() {
	running_ = false;
}
