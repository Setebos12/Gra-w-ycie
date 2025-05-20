#pragma once

#include <queue>
#include <string>
#include "InputToken.h"

namespace MVC {
	class Input {
	private:
		std::queue<InputToken> Tokens;
	public:
		Input();
		void pollEvents(sf::RenderWindow& window);
		void addToken(const InputToken token);
		InputToken nextToken();
		void clear();
	};
}