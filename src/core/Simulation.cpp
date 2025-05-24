#include "Simulation.h"
#include <iostream>
#include "board.h"
#include "../input/InputButton.h"

using namespace MVC;

Simulation::Simulation()
    : input_(std::make_unique<Input>()),
    logic_(std::make_unique<MVC::Logic>())
{
    const int boardWidth = 100;
    const int boardHeight = 100;
    const int cellSize = 10; 

    const int uiPanelWidth = 300;
    const int margin = 20;

    sf::Vector2u windowSize{
        static_cast<unsigned int>(boardWidth * cellSize + uiPanelWidth + margin * 2),
        static_cast<unsigned int>(std::max(boardHeight * cellSize, 1000) + margin * 2)
    };

    render_ = std::make_unique<MVC::Renderer>("Simulation", windowSize);

    gameobjects_.emplace_back(std::make_unique<Board>("Game of Life Board", boardWidth, boardHeight));

    float buttonX = static_cast<float>(windowSize.x - uiPanelWidth + margin);
    float buttonWidth = 180.f;
    float buttonHeight = 60.f;
    float buttonY = 500.f;


    // SPEED UP above START
    auto speedUpBtn = std::make_unique<InputButton>(
        "SpeedUpButton",
        sf::Vector2f{ buttonX, buttonY - 140.f }, // 2 slots above START
        sf::Vector2f{ buttonWidth, buttonHeight },
        "SPEED UP"
    );
    input_->buttons.push_back(speedUpBtn.get());
    gameobjects_.push_back(std::move(speedUpBtn));

    // SPEED DOWN above START
    auto speedDownBtn = std::make_unique<InputButton>(
        "SpeedDownButton",
        sf::Vector2f{ buttonX, buttonY - 70.f }, // 1 slot above START
        sf::Vector2f{ buttonWidth, buttonHeight },
        "SPEED DOWN"
    );
    input_->buttons.push_back(speedDownBtn.get());
    gameobjects_.push_back(std::move(speedDownBtn));


    auto startBtn = std::make_unique<InputButton>(
        "StartButton",
        sf::Vector2f{ buttonX, buttonY },
        sf::Vector2f{ buttonWidth, buttonHeight },
        "START"
    );
    input_->buttons.push_back(startBtn.get());
    gameobjects_.push_back(std::move(startBtn));

    auto stopBtn = std::make_unique<InputButton>(
        "StopButton",
        sf::Vector2f{ buttonX, buttonY + 100.f },
        sf::Vector2f{ buttonWidth, buttonHeight },
        "STOP"
    );
    input_->buttons.push_back(stopBtn.get());
    gameobjects_.push_back(std::move(stopBtn));

    auto endBtn = std::make_unique<InputButton>(
        "EndButton",
        sf::Vector2f{ buttonX, buttonY + 200.f },
        sf::Vector2f{ buttonWidth, buttonHeight },
        "END"
    );
    input_->buttons.push_back(endBtn.get());
    gameobjects_.push_back(std::move(endBtn));

    auto toggleDrawBtn = std::make_unique<InputButton>(
        "ToggleDrawButton",
        sf::Vector2f{ buttonX, buttonY + 300.f },
        sf::Vector2f{ buttonWidth, buttonHeight },
        "TOGGLE DRAW"
    );
    input_->buttons.push_back(toggleDrawBtn.get());
    gameobjects_.push_back(std::move(toggleDrawBtn));

    auto hud = std::make_unique<Hud>(
        "Hud",
        sf::Vector2f{ buttonX, buttonY + 400.f }
    );
    gameobjects_.push_back(std::move(hud));
}

//void Simulation::run() {
//    while (true) {
//        render_->draw(gameobjects_);
//
//        sf::sleep(sf::seconds(2));
//
//    }
//     
//}

void Simulation::run() {
    bool running = true;
    logic_->pause();

    int simulationDelayMs_ = 100; // Adjustable delay (can be changed by input)
    sf::Clock simClock;

    while (running) {
        auto* drawer = render_->getDrawer();
        auto& window = drawer->getWindow();
        input_->pollEvents(window);
        render_->draw(gameobjects_);

        InputToken token;
        while ((token = input_->nextToken()) != InputToken::Unknown) {
            if (token == InputToken::Start) {
                // s
                logic_->start();
                input_->setmode(0);

            }
            // key p
            else if (token == InputToken::Stop) {
                logic_->pause();
            }
            // key e
            else if (token == InputToken::End) {
                running = false;
                window.close();
            }
            // key d
            else if (token == InputToken::ToggleDraw) {
                logic_->pause();
                input_->setmode(1);

            }
            else if (token == InputToken::SpeedUp) {
                simulationDelayMs_ = std::max(1, simulationDelayMs_ - 10);
            }
            else if (token == InputToken::SpeedDown) {
                simulationDelayMs_ += 10;
            }
        }
        sf::Vector2i pos;
        while ((pos = input_->NextPos()) != sf::Vector2i(-1, -1)) {
            // Find the board object
            Board* board = nullptr;
            if (!gameobjects_.empty()) {
                board = dynamic_cast<Board*>(gameobjects_.front().get());
            }
            if (board) {
                board->toggleCellState(pos.x, pos.y);
            }
        }

        if (simClock.getElapsedTime().asMilliseconds() >= simulationDelayMs_) {
            logic_->step(gameobjects_);
            simClock.restart();
        }

        input_->clear();

        sf::sleep(sf::milliseconds(5));
    }
}

