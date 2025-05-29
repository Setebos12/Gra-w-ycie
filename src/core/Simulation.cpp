#include "Simulation.h"
#include "../input/InputButton.h"
#include "../logic/board.h"
#include "../ui/hud.h"

using namespace MVC;

Simulation::Simulation()
    : logic_(std::make_unique<Logic>()),
      logger_(std::make_shared<Util::Logger>(Util::Level::INFO)) {
  logEvent_ = std::make_shared<Util::Event<const std::string&, Util::Level>>();
  logEvent_->subscribe<Util::Logger>(std::weak_ptr(logger_), &Util::Logger::log);

  logEvent_->invoke("game started", Util::Level::INFO);

  constexpr int boardWidth = 100;
  constexpr int boardHeight = 100;
  constexpr int cellSize = 10;
       
  constexpr int uiPanelWidth = 300;
  constexpr int margin = 20;
  constexpr int maxFps = 60;

  sf::Vector2u windowSize{
      static_cast<unsigned int>(boardWidth * cellSize + uiPanelWidth +
                                margin * 2),
      static_cast<unsigned int>(std::max(boardHeight * cellSize, 1000) +
                                margin * 2)};

  window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowSize), "Game Of Life");
  window_->setFramerateLimit(maxFps);

  input_ = std::make_unique<Input>(window_);
  render_ = std::make_unique<MVC::Renderer>(window_);

  gameobjects_.emplace_back(
      std::make_unique<Board>("Game of Life Board", boardWidth, boardHeight, logEvent_));

  //gameobjects_.emplace_back(
  //    std::make_unique<Uipanel>(logEvent_, windowSize, uiPanelWidth, margin, boardWidth, boardHeight));

  running = true;
}

void Simulation::run() {
  logic_->start();

  while (running) {
      input_->pollEvents(gameobjects_);
      logic_->step(gameobjects_);
      render_->draw(gameobjects_);
  }
}
