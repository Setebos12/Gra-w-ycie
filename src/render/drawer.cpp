//Filename: drawer.cpp
//
//Implemenation of drawer class
//
//Author: Piotr Pyrak

#include "drawer.h"

using namespace Render;

Drawer::Drawer(const std::string& name, unsigned int height, unsigned int width, int maxFPS) : window_(sf::RenderWindow(sf::VideoMode({height, width}), name)) {
	window_.setFramerateLimit(maxFPS);
}

void Drawer::drawRect(const Vector2& start, const Vector2& end) {

}
