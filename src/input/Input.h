#pragma once

#include <set>
#include <string>
#include "InputToken.h"


class Input {
private:
	std::set<InputToken> Tokens;
public:
	void addToken(const InputToken token);
	bool isPressed(const InputToken token) const;
	void clear();
};