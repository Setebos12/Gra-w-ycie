// Filename: Simulation.cpp
//
// Description:
//     Implements the MVC::Simulation class, handling initialization of the game window,
//     setup of core systems (input, logic, rendering), and execution of the main game loop.
//
// Authors: Piotr Pyrak, Krzysztof Rutkowski, Bartosz Paszkiewicz


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
}

void Simulation::initWindow(std::weak_ptr<MVC::Simulation>&& selfRef) {
    Util::Event<> simEndEvent;
    simEndEvent.subscribe<MVC::Simulation>(std::move(selfRef), &MVC::Simulation::stopRun);

    logEvent_->invoke("game started", Util::Level::INFO);

    constexpr int boardWidth = 100;
    constexpr int boardHeight = 100;
    constexpr int cellSize = 10;

    constexpr int uiPanelWidth = 300;
    constexpr int margin = 20;
    constexpr int maxFps = 120;

    sf::Vector2u windowSize{
        static_cast<unsigned int>(boardWidth * cellSize + uiPanelWidth + margin * 2),
        static_cast<unsigned int>(std::max(boardHeight * cellSize, 1000) + margin * 2)
    };

    // window
    window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowSize), "Game Of Life");
    window_->setFramerateLimit(maxFps);

    //mvc
    input_ = std::make_unique<Input>(window_);
    render_ = std::make_unique<MVC::Renderer>(window_);

    running_ = true;

    auto board = std::make_shared<Board>("Game of Life Board", boardWidth, boardHeight, logEvent_);
    
    //gameobjects
    auto panel = std::make_shared<Uipanel>(
        logEvent_,
        windowSize,
        uiPanelWidth,
        margin,
        boardWidth,
        boardHeight,
        std::weak_ptr(logic_),
        std::weak_ptr(board),
        std::move(simEndEvent));
    gameobjects_.emplace_back(panel);

    gameobjects_.emplace_back(std::move(board));
}

void Simulation::run() {
  logic_->pause();

  while (running_) {
      input_->pollEvents(gameobjects_);
      logic_->step(gameobjects_);
      render_->draw(gameobjects_);

      logEvent_->invoke("frame\n", Util::Level::INFO);
  }
}
