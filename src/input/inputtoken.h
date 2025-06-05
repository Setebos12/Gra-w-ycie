//Filename: InputToken.h
//
//Token that is passed to input functions of gameobjects
//
//Author: Piotr Pyrak

#pragma once

#include <SFML/System/Vector2.hpp>

namespace InputPoll {
enum class TokenType {
	LEFT_MOUSE_RELEASED,
	LEFT_MOUSE_PRESSED,
	LEFT_MOUSE_DOWN
};

class InputToken {
public:
	InputToken(TokenType type, sf::Vector2i mousePos) : tokenType_(type), mousePos_(mousePos) {}

	auto getType() const { return tokenType_; }
	const auto& getMousePos() const { return mousePos_; }
private:
	TokenType tokenType_;
	sf::Vector2i mousePos_;
};
} // namespace InputPoll