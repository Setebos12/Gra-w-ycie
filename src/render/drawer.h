// Filename: drawer.h
//
// Provides methods for gameobjects for them to not interact with graphics
// directly. The only class to interact with graphics
//
// Author: Piotr Pyrak

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

namespace Render {
class Drawer {
public:
  Drawer(const std::string &name, const sf::Vector2u &size, int maxFPS);
  void refresh();

  // methods for gameobjects to use (will add more as needed)
  void drawRect(const sf::Vector2f &position, const sf::Vector2f &size,
                const sf::Color &fill);
  void drawText(const std::string& text, const sf::Vector2f& position, unsigned int fontSize = 24, const sf::Color& color = sf::Color::Black);


  sf::RenderWindow& getWindow() { return window_; }

private:
  sf::RenderWindow window_;
  std::vector<std::unique_ptr<sf::Drawable>> buffer_;
};
} // namespace Render
