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
#include "../util/fileIO.h"

using namespace MVC;

Simulation::Simulation(Util::Level log)
    : logic_(std::make_unique<Logic>()),
    logger_(std::make_shared<Util::Logger>(log)),
    running_(true) {
    logEvent_ = std::make_shared<Util::Event<const std::string&, Util::Level>>();
    logEvent_->subscribe<Util::Logger>(std::weak_ptr(logger_), &Util::Logger::log);
}

void Simulation::initWindow(const std::weak_ptr<MVC::Simulation>& selfRef) {
    Util::Event<> simEndEvent;
    simEndEvent.subscribe<MVC::Simulation>(std::weak_ptr(selfRef), &MVC::Simulation::stopRun);

    Util::Event<> saveEvent;
    saveEvent.subscribe<MVC::Simulation>(std::weak_ptr(selfRef), &MVC::Simulation::save);
    Util::Event<> loadEvent;
    loadEvent.subscribe<MVC::Simulation>(std::weak_ptr(selfRef), &MVC::Simulation::load);

    logEvent_->invoke("game started\n", Util::Level::INFO);

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
    input_ = std::make_unique<Input>(window_, logEvent_);
    render_ = std::make_unique<MVC::Renderer>(window_);

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
        std::move(simEndEvent),
        std::move(saveEvent),
        std::move(loadEvent),
        board->getUpdateGenEvent());
    gameobjects_.emplace_back(panel);

    gameobjects_.emplace_back(std::move(board));
}

void Simulation::run() {
  logic_->pause();

  while (running_) {
      input_->pollEvents(gameobjects_);
      logic_->step(gameobjects_);
      render_->draw(gameobjects_);

      logEvent_->invoke("frame\n", Util::Level::DEBUG);
  }
}

void Simulation::save() {
    try {
        FileIO io;
        for (auto& go : gameobjects_) {
            if (go->getSaveState())
                io.write<GameObject>(*go);
        }
    } catch (const std::runtime_error& err) {
        logEvent_->invoke("ERROR: Can't save state: " + std::string(err.what()), Util::Level::ERROR);
    }
}

void Simulation::load() {
    try {
        FileIO io;
        for (auto& go : gameobjects_) {
            if (go->getSaveState())
                io.read<GameObject>(*go);
        }
    } catch (const std::runtime_error& err) {
        logEvent_->invoke("ERROR: Can't load state: " + std::string(err.what()), Util::Level::ERROR);
    }
}