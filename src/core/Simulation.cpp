#include "Simulation.h"
#include <iostream>
#include "board.h"
#include "../input/InputButton.h"

using namespace MVC;

Simulation::Simulation()
    : input_(std::make_unique<Input>()),
    logic_(std::make_unique<MVC::Logic>()), 
    render_(std::make_unique<MVC::Renderer>("Simulation",
        sf::Vector2u{ 1920u, 1800u }))
{
    gameobjects_.emplace_back(std::make_unique<Board>("Game of Life Board", 100, 100));
    if (!gameobjects_.empty()) {
        Board* board = dynamic_cast<Board*>(gameobjects_.front().get());
        if (board) {
            board->resetBoard();
            int gen = board->getGenerationCount();
            int centerX = 50;
            int centerY = 50;
            board->toggleCellState(centerX, centerY);
            board->toggleCellState(centerX + 1, centerY);
            board->toggleCellState(centerX - 1, centerY);
        }
        logic_->start();
    }
    auto startBtn = std::make_unique<InputButton>(
        "StartButton",
        sf::Vector2f{ 1700.f, 500.f },
        sf::Vector2f{ 180.f, 60.f },
        "START"
    );
    input_->buttons.push_back(startBtn.get());
    gameobjects_.push_back(std::move(startBtn));

    auto stopBtn = std::make_unique<InputButton>(
        "StopButton",
        sf::Vector2f{ 1700.f, 600.f },
        sf::Vector2f{ 180.f, 60.f },
        "STOP"
    );
    input_->buttons.push_back(stopBtn.get());
    gameobjects_.push_back(std::move(stopBtn));

    auto endBtn = std::make_unique<InputButton>(
        "EndButton",
        sf::Vector2f{ 1700.f, 700.f },
        sf::Vector2f{ 180.f, 60.f },
        "END"
    );
    input_->buttons.push_back(endBtn.get());
    gameobjects_.push_back(std::move(endBtn));

    auto toggleDrawBtn = std::make_unique<InputButton>(
        "ToggleDrawButton",
        sf::Vector2f{ 1700.f, 800.f },
        sf::Vector2f{ 180.f, 60.f },
        "TOGGLE DRAW"
    );
    input_->buttons.push_back(toggleDrawBtn.get());
    gameobjects_.push_back(std::move(toggleDrawBtn));


    auto hud = std::make_unique<Hud>(
        "Hud",    
        sf::Vector2f{ 1700.f, 900.f }
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


        logic_->step(gameobjects_);

        input_->clear();

        sf::sleep(sf::milliseconds(20));
    }
}

