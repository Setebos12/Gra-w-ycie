//Filename: hud.h
//
//Display that shows most important information from simulation to screen
//
//Author: Piotr Pyrak, Krzysztof Rutkowski

#pragma once

#include "../core/gameobject.h"

class Hud : GameObject {
public:
	Hud(const std::string& name) : GameObject(name) {}

	void update_values(const int& generation_number, const int& alive_cells);

	void draw(const Drawer& drawer) override;
	void update() override;
private:
	int generation_;
	int alive_cells_;
};
