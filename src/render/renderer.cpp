//Filename: renderer.cpp
//
//Implementation of renderer (view of MVC)
//
//Author: Piotr Pyrak

#include "renderer.h"

using namespace MVC;

void Renderer::draw(const std::vector<std::unique_ptr<Render::IRenderObject>>& all_objects) {
	for (const auto& obj : all_objects) {
		obj->draw(*drawer_);
	}

	drawer_->refresh();
}
