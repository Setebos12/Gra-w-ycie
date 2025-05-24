#pragma once

#include <queue>
#include <string>
#include "InputToken.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ParserKeyboard.h"
#include "InputButton.h"
namespace MVC {
	class Input {
	private:
		std::queue<InputToken> Tokens;
		std::queue<sf::Vector2i> boardClicks;
	public:
		std::vector<InputButton*> buttons;

		Input() = default;
		void pollEvents(sf::RenderWindow& window, int mode=0);
		std::optional<sf::Vector2i> readBoard(sf::Vector2i& mousePos);

		void addToken(const InputToken token);
		InputToken nextToken();
		sf::Vector2i NextPos();

		void clear();
	};
}