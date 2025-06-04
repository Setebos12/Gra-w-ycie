// Filename: InputButton.cpp
//
// Description:
//     Implements the InputButton class responsible for drawing a button
//     and handling mouse click interactions.
//
// Author: Krzysztof Rutkowski



#include "InputButton.h"

void InputButton::draw(Render::Drawer& drawer)  {
    sf::Color color = pressed_ ? sf::Color::Red : sf::Color::Green;
    drawer.drawRect(position_, size_, color);
    drawer.drawText(
        label_,
        sf::Vector2f{
            position_.x + size_.x / 8.f,
            position_.y + size_.y / 8.f
        },
        18,
        sf::Color::Black
    );
}


bool InputButton::input(InputToken& token) {
    sf::FloatRect rect(position_, size_);
    if (!rect.contains(sf::Vector2f(token.getMousePos()))) {
        return false;
    }

    if (token.getType() == TokenType::LEFT_MOUSE_PRESSED) {
        setPressed(true);
        return false;
    }

    if (!(token.getType() == TokenType::LEFT_MOUSE_RELEASED)) {
        return false;
    }

    setPressed(false);

    onClick_.invoke();

    return true;
}