#include "Simulation.h"
#include "board.h"

using namespace MVC;

Simulation::Simulation()
    : input_(std::make_unique<Input>()),
    logic_(std::make_unique<MVC::Logic>()),
    render_(std::make_unique<MVC::Renderer>("Simulation",
        sf::Vector2u{ 1920u, 1800u }))
{
    gameobjects_.emplace_back(std::make_unique<Board>("Game of Life Board", 100, 100));
}

void Simulation::run() {
    while (true) {
        //logic_->step(gameobjects_);
        input_->pollEvents(window);
        logic_->start();
        render_->draw(gameobjects_);
        input_->clear();
    }
}