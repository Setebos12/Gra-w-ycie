// Gra w zycie.cpp : Defines the entry point for the application.
//
// Author: Piotr Pyrak

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Simulation");
	window.setFramerateLimit(144);
	
	sf::Font font;
	if (!font.openFromFile("../../assets/arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return -1;
    }

	sf::Text text {font, "Simulation GAME OF LIFE"};
	
	while (true) {
		window.clear();
		window.draw(text);
		window.display();
	}

	cout << "Simulation GAME OF LIFE" << endl;
	return 0;
}
