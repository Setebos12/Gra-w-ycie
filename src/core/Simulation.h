#pragma once

#include "../input/Input.h"
#include "../logic/logic.h"
#include <memory>
#include "../render/renderer.h"


namespace MVC {
class Simulation {
public:
  Simulation();

  void run();

private:

  sf::RenderWindow window;

  std::unique_ptr<Input> input_;
  std::unique_ptr<MVC::Logic> logic_;
  std::unique_ptr<MVC::Renderer> render_;

  std::vector<std::unique_ptr<MVC::GameObject>> gameobjects_;
};
} // namespace MVC
