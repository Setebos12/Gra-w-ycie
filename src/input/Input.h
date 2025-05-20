#pragma once

#include <queue>
#include <string>
#include "InputToken.h"


class Input {
private:
	std::queue<InputToken> Tokens;
public:
	Input();
	void addToken(const InputToken token);
	bool isPressed(const InputToken token) const;
	void clear();
};