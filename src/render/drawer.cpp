// Filename: drawer.cpp
//
// Implemenation of drawer class
//
// Author: Piotr Pyrak

#include "drawer.h"
#include <SFML/Graphics/RectangleShape.hpp>

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
  buffer_.emplace_back(std::move(rect));
}

void Drawer::drawText(const std::string &text) {}

void Drawer::refresh() {
  window_.clear();

  for (const auto &drw : buffer_) {
    window_.draw(*drw);
  }

  buffer_.clear();

  window_.display();
}
