// Filename: drawer.cpp
//
// Implemenation of drawer class
//
// Author: Piotr Pyrak

#include "drawer.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace Render;

Drawer::Drawer(const std::string &name, const sf::Vector2u &size, int maxFPS)
    : window_(sf::RenderWindow(sf::VideoMode(size), name)) {
  window_.setFramerateLimit(maxFPS);
}

void Drawer::drawRect(const sf::Vector2f &position, const sf::Vector2f &size,
                      const sf::Color &fill) {
  auto rect{std::make_unique<sf::RectangleShape>(size)};
  rect->setPosition(position);
  rect->setFillColor(fill);

  rect->setOutlineColor(sf::Color::White);
  rect->setOutlineThickness(0.5f);

  buffer_.emplace_back(std::move(rect));
}




void Drawer::drawText(const std::string & textStr, const sf::Vector2f & position, unsigned int fontSize, const sf::Color & color) {
    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        if (!font.openFromFile("../assets/arial.ttf")) {
            return;
        }
        fontLoaded = true;
    }

    auto text{ std::make_unique<sf::Text>(font) };
    text->setFont(font);
    text->setString(textStr);
    text->setCharacterSize(fontSize);
    text->setFillColor(color);
    text->setPosition(position);

    buffer_.emplace_back(std::move(text));
}


void Drawer::refresh() {
  window_.clear();

  for (const auto &drw : buffer_) {
    window_.draw(*drw);
  }

  buffer_.clear();

  window_.display();
}
