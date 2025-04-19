#pragma once

#include <memory>


class Input;
class Logic;
class Render;
class Gameobject;

class Simulation {
public:
	Simulation();

	void run();
private:
	std::unique_ptr<Input> input;
	std::unique_ptr<Logic> logic;
	std::unique_ptr<Render> render;

	std::unique_ptr<Gameobject> gameobject;

	bool running;

	void processInput();
	void updateLogic();
	void render();
};