//Filename: renderer.h
//
//During a game loop this class is given control and is responsible for drawing objects.
//
//Author: Piotr Pyrak

#pragma once

#include <vector>
#include <memory>
#include "drawer.h"
#include "irenderobj.h"

namespace MVC {
class Renderer {
public:
	Renderer(std::unique_ptr<Render::Drawer>&& drawer) : drawer_(std::move(drawer)) {}
	Renderer(const std::string& name, unsigned int height, unsigned int width) : drawer_(std::make_unique<Render::Drawer>(name, height, width, 60)) {}
	void draw(const std::vector<std::unique_ptr<Render::IRenderObject>>& all_objects);
private:
	std::unique_ptr<Render::Drawer> drawer_;
};
}
