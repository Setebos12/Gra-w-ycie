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

	public:
		std::vector<InputButton*> buttons;

		Input() = default;
		void pollEvents(sf::RenderWindow& window);
		void addToken(const InputToken token);
		InputToken nextToken();
		void clear();
	};
}