#include "Simulation.h"

using namespace MVC;

Simulation::Simulation()
    : logic_(std::make_unique<MVC::Logic>()),
      render_(std::make_unique<MVC::Renderer>("Simulation",
                                              sf::Vector2u{1920u, 1800u})) {}

void Simulation::run() {
  while (true) {
    logic_->step(gameobjects_);
    render_->draw(gameobjects_);
  }
}
