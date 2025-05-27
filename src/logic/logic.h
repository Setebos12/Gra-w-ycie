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
	//Should also take input, gameobjects maybe should to in update, or a third method for control is needed
	void step(std::vector<std::shared_ptr<GameObject>>& all_objects);

	void handleControl(MVC::Input& input,
		int& simDelayMs,
		bool& running,
		Board& board,
		sf::Clock& simClock,
		std::vector<std::shared_ptr<MVC::GameObject>>& objects);


	void start();
	void pause();

	bool isRunning() { return running_; }
private:
	bool running_;
};
}
