//Filename: logic.h
//
//During a game loop this class will get control and for a given collection of objects will update them
//
//Author: Piotr Pyrak

#pragma once

#include <vector>
#include <memory>
#include "gameobject.h"

// replace with a real class
using GameState = int;

class Logic {
public:
	void step(std::vector<std::unique_ptr<GameObject>>& all_objects); 
private:
};
