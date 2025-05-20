#pragma once

#include "Input.h"
#include <iostream>

void MVC::Input::pollEvents(sf::RenderWindow& window) {
    ParseKeyBoard parser; // parser

    std::optional<sf::Event> eventOpt;
    while ((eventOpt = window.pollEvent())) {
        const sf::Event& event = *eventOpt;

        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            InputToken token = parser.parseKey(static_cast<int>(keyPressed->scancode));
            addToken(token);
        }

        if (const auto* closed = event.getIf<sf::Event::Closed>()) {
            window.close();
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