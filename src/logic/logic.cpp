//Filename: logic.cpp
//
//Implementation of logic
//
//Author: Piotr Pyrak

#include "logic.h"

using namespace MVC;

Logic::Logic() : running_(false), simDelayMs_(100) {}



void Logic::step(std::vector<std::shared_ptr<GameObject>>& all_objects) {
    if (!running_ || simClock_.getElapsedTime().asMilliseconds() < simDelayMs_)
        return;

    for (const auto& obj : all_objects) {
        obj->update();
    }

    simClock_.restart();
}

void Logic::start() {
    running_ = true;
    simClock_.restart();
}

void Logic::pause() {
    running_ = false;
}

void Logic::increaseSpeed() {
    simDelayMs_ = std::max(10, simDelayMs_ - 25);
}

void Logic::decreaseSpeed() {
    simDelayMs_ += 25;
}