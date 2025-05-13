//Filename: drawer.h
//
//Provides methods for gameobjects for them to not interact with graphics directly.
//The only class to interact with graphics
//
//Author: Piotr Pyrak

#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

//replace with double ints, in a real class
using Vector2 = int;

namespace Render {
class Drawer {
public:
	Drawer(const std::string& name, unsigned int height, unsigned int width, int maxFPS);
	void refresh();

	//methods for gameobjects to use (will add more as needed)
	void drawRect(const Vector2& start, const Vector2& end);
	void drawText(const std::string& text);
private:
	sf::RenderWindow window_;
};
}
