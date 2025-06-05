// Filename: drawer.cpp
//
// Implemenation of drawer class
//
// Author: Piotr Pyrak

#include "drawer.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>

using namespace Render;

void Drawer::drawRect(const sf::Vector2f &position, const sf::Vector2f &size,
                      const sf::Color &fill) {
  auto rect{std::make_unique<sf::RectangleShape>(size)};
  rect->setPosition(position);
  rect->setFillColor(fill);


  std::stringstream ss;
  ss << "Drawing rect, pos: (" << position.x << ", " << position.y << ") "
      << "size: (" << size.x << ", " << size.y << ") "
      << "fill: (r=" << fill.r
      << ", g=" << fill.g
      << ", b=" << fill.b
      << ", a=" << fill.a << ")";

  logEvent_->invoke(ss.str(), Util::Level::DEBUG);


  buffer_.emplace_back(std::move(rect));
}

void Drawer::drawText(const std::string & textStr, const sf::Vector2f & position, unsigned int fontSize, const sf::Color & color) {
    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        if (!font.openFromFile("../assets/arial.ttf")) {
            logEvent_->invoke("Failed to load font from ../assets/arial.ttf", Util::Level::ERROR);
            return;
        }
        fontLoaded = true;
        logEvent_->invoke("Font loaded from ../assets/arial.ttf", Util::Level::DEBUG);
    }

    auto text{ std::make_unique<sf::Text>(font) };
    text->setFont(font);
    text->setString(textStr);
    text->setCharacterSize(fontSize);
    text->setFillColor(color);
    text->setPosition(position);


    std::stringstream ss;
    ss << "Drawing text: \"" << textStr << "\" "
        << "at position: (" << position.x << ", " << position.y << ") "
        << "size: " << fontSize << " "
        << "color: (r=" << color.r
        << ", g=" << color.g
        << ", b=" << color.b
        << ", a=" << color.a << ")";

    logEvent_->invoke(ss.str(), Util::Level::DEBUG);


    buffer_.emplace_back(std::move(text));
}

void Drawer::refresh() {
  window_->clear();

  for (const auto &drw : buffer_) {
    window_->draw(*drw);
  }

  buffer_.clear();

  window_->display();
}
