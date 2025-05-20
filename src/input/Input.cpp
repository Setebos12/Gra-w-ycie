#include "Input.h"
#include "Input.h"
#pragma once

#include "Input.h"

Input::Input() {}

void MVC::Input::pollEvents(sf::RenderWindow& window) {
    sf::Event event;
    ParseKeyBoard parser;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            InputToken token = parser.parseKey(event.key.code);
            addToken(token);
        }
    }
}

void MVC::Input::addToken(const InputToken token) {
    Tokens.push(token);
}

InputToken MVC::Input::nextToken() {
    if (Tokens.empty())
        return InputToken::Unknown;
    InputToken token = Tokens.front();
    Tokens.pop();
    return token;
}

void MVC::Input::clear() {
    while (!Tokens.empty()) {
        Tokens.pop();
    }
}