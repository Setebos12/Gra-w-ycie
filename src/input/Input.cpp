#include "Input.h"

void MVC::Input::pollEvents(const std::vector<std::unique_ptr<GameObject>>& all_objects, int mode) {

}

std::optional<sf::Vector2i> MVC::Input::readBoard(sf::Vector2i &mousePos) {
  float cellSize = 10.f;
  int boardWidth = 100;  // Set this to your actual board width
  int boardHeight = 100; // Set this to your actual board height

  int cellX = static_cast<int>(mousePos.x / cellSize);
  int cellY = static_cast<int>(mousePos.y / cellSize);

  if (cellX >= 0 && cellX < boardWidth && cellY >= 0 && cellY < boardHeight) {
    return sf::Vector2i(cellX, cellY);
  }
  return std::nullopt;
}

void MVC::Input::addToken(const InputToken token) { Tokens.push(token); }

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

  while (!boardClicks.empty()) {
    boardClicks.pop();
  }
}

sf::Vector2i MVC::Input::nextPos() {
  if (boardClicks.empty())
    return sf::Vector2i(-1, -1);
  sf::Vector2i pos = boardClicks.front();
  boardClicks.pop();
  return pos;
}
