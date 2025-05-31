//Filename: InputToken.h
//
//Token that is passed to input functions of gameobjects
//
//Author: Piotr Pyrak

#pragma once

#include <SFML/System/Vector2.hpp>

enum class TokenType {
	LEFT_MOUSE_REALESED,
	LEFT_MOUSE_DOWN
};

class InputToken {
public:
	InputToken(TokenType type, sf::Vector2i mousePos) : tokenType_(type), mousePos_(mousePos) {}

	auto getType() { return tokenType_; }
	const auto& getMousePos() { return mousePos_; }
private:
	TokenType tokenType_;
	sf::Vector2i mousePos_;
};