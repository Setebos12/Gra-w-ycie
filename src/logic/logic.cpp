//Filename: logic.cpp
//
//Implementation of logic
//
//Author: Piotr Pyrak

#include "logic.h"

using namespace MVC;

void Logic::step(std::vector<std::unique_ptr<GameObject>>& all_objects) {
	if (!running_)
		return;

	for (const auto &obj : all_objects) {
		obj->update();
	}
}

void Logic::start() {
	running_ = true;
}

void Logic::pause() {
	running_ = false;
}
