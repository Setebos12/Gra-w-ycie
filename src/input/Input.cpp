#pragma once

#include "Input.h"

Input::Input() {}

void Input::addToken(const InputToken token) {
    Tokens.push(token);
}

bool Input::isPressed(const InputToken token) const {
    std::queue<InputToken> copy = Tokens;
    while (!copy.empty()) {
        if (copy.front() == token)
            return true;
        copy.pop();
    }
    return false;
}

void Input::clear() {
    while (!Tokens.empty()) {
        Tokens.pop();
    }
}