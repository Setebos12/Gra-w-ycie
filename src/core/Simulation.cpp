#include "Simulation.h"
#include "../input/InputButton.h"
#include "../logic/board.h"
#include "../ui/hud.h"

using namespace MVC;

Simulation::Simulation()
    : input_(std::make_unique<Input>()), logic_(std::make_unique<Logic>()),
      logger_(std::make_shared<Util::Logger>(Util::Level::INFO)) {
  logEvent_ = std::make_shared<Util::Event<const std::string&, Util::Level>>();
  logEvent_->subscribe<Util::Logger>(std::weak_ptr(logger_), &Util::Logger::log);

  const int boardWidth = 100;
  const int boardHeight = 100;
  const int cellSize = 10;

  const int uiPanelWidth = 300;
  const int margin = 20;

  sf::Vector2u windowSize{
      static_cast<unsigned int>(boardWidth * cellSize + uiPanelWidth +
                                margin * 2),
      static_cast<unsigned int>(std::max(boardHeight * cellSize, 1200) +
                                margin * 2)};

  render_ = std::make_unique<MVC::Renderer>("Simulation", windowSize);

  uipanel_ = std::make_unique<Uipanel>(logEvent_, windowSize, uiPanelWidth, margin, boardWidth, boardHeight);

  gameobjects_ = uipanel_->getGameObjects();

  simulationDelayMs_ = 100;
  running = true;
}

void Simulation::run() {
  logic_->pause();

  sf::Clock simClock;

  while (running) {
    auto *drawer = render_->getDrawer();
    auto &window = drawer->getWindow();

    updateHud();
    input_->pollEvents(window, uipanel_->inputbuttons);
    render_->draw(gameobjects_);
    logic_->handleControl(*input_, simulationDelayMs_, running);
    handleBoardClicks();
    handleSimulationStep(simClock);

    input_->clear();
    sf::sleep(sf::milliseconds(10));
  }
  auto *drawer = render_->getDrawer();
  drawer->getWindow().close();
}

void Simulation::updateHud() {
  std::shared_ptr<MVC::GameObject> hudobj = std::move(gameobjects_.back());
  if (auto hi = dynamic_cast<Hud *>(hudobj.get())) {
    hi->update_values(0, simulationDelayMs_);
  }
  gameobjects_.back() = std::move(hudobj);
}

void Simulation::handleBoardClicks() {
  sf::Vector2i pos;
  while ((pos = input_->nextPos()) != sf::Vector2i(-1, -1)) {
    if (!gameobjects_.empty()) {
      std::shared_ptr<MVC::GameObject> obj = std::move(gameobjects_.front());
      if (auto boardPtr = dynamic_cast<Board *>(obj.get())) {
        boardPtr->toggleCellState(pos.x, pos.y);
      }
      gameobjects_.front() = std::move(obj);
    }
  }
}

void Simulation::handleSimulationStep(sf::Clock &simClock) {
  if (simClock.getElapsedTime().asMilliseconds() >= simulationDelayMs_) {
    logic_->step(gameobjects_);
    simClock.restart();
  }
}
