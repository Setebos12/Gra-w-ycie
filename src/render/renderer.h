//Filename: renderer.h
//
//During a game loop this class is given control and is responsible for drawing objects.
//
//Author: Piotr Pyrak

#pragma once

#include <vector>
#include <memory>
#include "../core/gameobject.h"

class Renderer {
public:
	void draw(std::vector<std::unique_ptr<GameObject>>& all_objects);
private:
	Drawer drawer;
};
