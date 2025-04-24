#pragma once

#include <memory>
#include "../input/Input.h"
#include "../logic/Logic.h" 
#include "../render/Renderer.h"
#include "GameObject.h"

class Simulation {
public:
Simulation();

void run();
private:
std::unique_ptr<Input> input;
std::unique_ptr<Logic> logic;
std::unique_ptr<Renderer> render;

std::unique_ptr<GameObject> gameobject;

bool running;

void processInput();
void updateLogic();
void render();
};