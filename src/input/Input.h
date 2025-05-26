#pragma once

#include "InputButton.h"
#include "InputToken.h"
#include "ParserKeyboard.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <queue>
#include <string>
#include <memory>


namespace MVC {
class Input {
private:
  std::queue<InputToken> Tokens;
  std::queue<sf::Vector2i> boardClicks;
  int mode;
  std::vector<InputButton*> buttons;
public:
  Input(const int mode_ = 0) : mode(mode_) {}


  void pollEvents(sf::RenderWindow &window, int mode = 0);
  std::optional<sf::Vector2i> readBoard(sf::Vector2i &mousePos);
  void addbutton(std::unique_ptr<InputButton>& but);

  void addToken(const InputToken token);
  InputToken nextToken();
  sf::Vector2i nextPos();

  void setmode(const int mode_) { mode = mode_; }
  void clear();
};
} // namespace MVC
