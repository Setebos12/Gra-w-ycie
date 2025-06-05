//Filename: logic.h
//
//During a game loop this class will get control and for a given collection of objects will update them
//
//Author: Piotr Pyrak

#pragma once

#include <vector>
#include <memory>
#include "gameobject.h"
#include "board.h"

namespace MVC {
	class Logic {
	public:
		Logic();
		void step(std::vector<std::shared_ptr<GameObject>>& all_objects);

		void increaseSpeed();
		void decreaseSpeed();

		void start();
		void pause();

		bool isRunning() const { return running_; }
	private:
		bool running_;

		int simDelayMs_;

		sf::Clock simClock_;
	};
}
