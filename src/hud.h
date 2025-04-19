//Filename: hud.h
//
//Display that shows most important information from simulation to screen
//
//Author: Piotr Pyrak

#pragma once

#include "gameobject.h"

class Hud : GameObject {
public:
	Hud(const std::string& name) : GameObject(name) {}

	//more added as needed
	void update_values(const int& generation_number, const int& alive_cells);

	void draw(const Drawer& drawer) override;
	void update() override;
private:
};
