#include "Simulation.h"
#include <iostream>
#include "board.h"


using namespace MVC;

Simulation::Simulation()
    : input_(std::make_unique<Input>()),
    logic_(std::make_unique<MVC::Logic>()),/* 
    render_(std::make_unique<MVC::Renderer>("Simulation",
        sf::Vector2u{ 1920u, 1800u })),*/
    window(sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "Simulation")) // temporary for input tests , no idea how to get from rederer window ;) 
{
    gameobjects_.emplace_back(std::make_unique<Board>("Game of Life Board", 100, 100));
}

void Simulation::run() {
    bool running = true;
    window.setKeyRepeatEnabled(false);
    while (running && window.isOpen()) {
        input_->pollEvents(window);

        InputToken token;
        while ((token = input_->nextToken()) != InputToken::Unknown) {
            std::cout << "Token received: " << static_cast<int>(token) << std::endl;
            if (token == InputToken::Start) {
                // key s
                std::cout << "Start action triggered" << std::endl;
            }
            // key p
            else if (token == InputToken::Stop) {
                std::cout << "Stop action triggered" << std::endl;
            }
            // key e
            else if (token == InputToken::End) {
                std::cout << "End action triggered - exiting" << std::endl;
                running = false;
                window.close();
            }
            // key d
            else if (token == InputToken::ToggleDraw) {
                std::cout << "ToggleDraw action triggered" << std::endl;
            }
        }

        input_->clear();

        sf::sleep(sf::milliseconds(16));
    }
}