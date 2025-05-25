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

  gameobjects_.emplace_back(
      std::make_unique<Board>("Game of Life Board", boardWidth, boardHeight, logEvent_));

  float buttonX = static_cast<float>(windowSize.x - uiPanelWidth + margin);
  float buttonWidth = 180.f;
  float buttonHeight = 60.f;
  float buttonY = 500.f;

  // SPEED UP above START
  auto speedUpBtn = std::make_unique<InputButton>(
      "SpeedUpButton",
      sf::Vector2f{buttonX, buttonY - 140.f}, // 2 slots above START
      sf::Vector2f{buttonWidth, buttonHeight}, "SPEED UP");
  input_->buttons.emplace_back(speedUpBtn.get());
  gameobjects_.emplace_back(std::move(speedUpBtn));

  // SPEED DOWN above START
  auto speedDownBtn = std::make_unique<InputButton>(
      "SpeedDownButton",
      sf::Vector2f{buttonX, buttonY - 70.f}, // 1 slot above START
      sf::Vector2f{buttonWidth, buttonHeight}, "SPEED DOWN");
  input_->buttons.emplace_back(speedDownBtn.get());
  gameobjects_.emplace_back(std::move(speedDownBtn));

  auto startBtn = std::make_unique<InputButton>(
      "StartButton", sf::Vector2f{buttonX, buttonY},
      sf::Vector2f{buttonWidth, buttonHeight}, "START");
  input_->buttons.emplace_back(startBtn.get());
  gameobjects_.emplace_back(std::move(startBtn));

  auto stopBtn = std::make_unique<InputButton>(
      "StopButton", sf::Vector2f{buttonX, buttonY + 100.f},
      sf::Vector2f{buttonWidth, buttonHeight}, "STOP");
  input_->buttons.emplace_back(stopBtn.get());
  gameobjects_.emplace_back(std::move(stopBtn));

  auto endBtn = std::make_unique<InputButton>(
      "EndButton", sf::Vector2f{buttonX, buttonY + 200.f},
      sf::Vector2f{buttonWidth, buttonHeight}, "END");
  input_->buttons.emplace_back(endBtn.get());
  gameobjects_.emplace_back(std::move(endBtn));

  auto toggleDrawBtn = std::make_unique<InputButton>(
      "ToggleDrawButton", sf::Vector2f{buttonX, buttonY + 300.f},
      sf::Vector2f{buttonWidth, buttonHeight}, "TOGGLE DRAW");
  input_->buttons.emplace_back(toggleDrawBtn.get());
  gameobjects_.emplace_back(std::move(toggleDrawBtn));

  auto hud =
      std::make_unique<Hud>("Hud", sf::Vector2f{buttonX, buttonY + 400.f});
  gameobjects_.emplace_back(std::move(hud));

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
    handleInput(window);
    handleBoardClicks();
    handleSimulationStep(simClock);

    input_->clear();
    sf::sleep(sf::milliseconds(10));
  }
  auto *drawer = render_->getDrawer();
  drawer->getWindow().close();
}

void Simulation::updateHud() {
  std::unique_ptr<MVC::GameObject> hudobj = std::move(gameobjects_.back());
  if (auto hi = dynamic_cast<Hud *>(hudobj.get())) {
    hi->update_values(0, simulationDelayMs_);
  }
  gameobjects_.back() = std::move(hudobj);
}

void Simulation::handleInput(sf::RenderWindow &window) {
  input_->pollEvents(window);
  render_->draw(gameobjects_);

  InputToken token;
  while ((token = input_->nextToken()) != InputToken::Unknown) {
    if (token == InputToken::Start) {
      logic_->start();
      input_->setmode(0);
    } else if (token == InputToken::Stop) {
      logic_->pause();
    } else if (token == InputToken::End) {
      running = false;
    } else if (token == InputToken::ToggleDraw) {
      logic_->pause();
      input_->setmode(1);
    } else if (token == InputToken::SpeedUp) {
      simulationDelayMs_ = std::max(10, simulationDelayMs_ - 10);
    } else if (token == InputToken::SpeedDown) {
      simulationDelayMs_ += 10;
    }
  }
}

void Simulation::handleBoardClicks() {
  sf::Vector2i pos;
  while ((pos = input_->nextPos()) != sf::Vector2i(-1, -1)) {
    if (!gameobjects_.empty()) {
      std::unique_ptr<MVC::GameObject> obj = std::move(gameobjects_.front());
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
