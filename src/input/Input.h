#pragma once

#include "InputButton.h"
#include "InputToken.h"
#include "ParserKeyboard.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <queue>
#include <string>
#include "../core/gameobject.h"

namespace MVC {
class Input {
private:
  std::queue<InputToken> Tokens;
  std::queue<sf::Vector2i> boardClicks;
  int mode;

public:
  Input(std::shared_ptr<sf::Window> window, const int mode_ = 0) : mode(mode_) {}
  std::vector<InputButton *> buttons;

  void pollEvents(const std::vector<std::unique_ptr<MVC::GameObject>>& all_objects, int mode = 0);
  std::optional<sf::Vector2i> readBoard(sf::Vector2i &mousePos);

  void addToken(const InputToken token);
  InputToken nextToken();
  sf::Vector2i nextPos();

  void setmode(const int mode_) { mode = mode_; }
  void clear();
};
} // namespace MVC
