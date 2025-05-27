//Filename: logic.h
//
//During a game loop this class will get control and for a given collection of objects will update them
//
//Author: Piotr Pyrak

#pragma once

#include <vector>
#include <memory>
#include "../core/gameobject.h"
#include "../input/Input.h"
#include "board.h"

namespace MVC {
class Logic {
public:
	void step(std::vector<std::unique_ptr<GameObject>>& all_objects);

	void start();
	void pause();

	bool isRunning() { return running_; }
private:
	bool running_;
};
}
