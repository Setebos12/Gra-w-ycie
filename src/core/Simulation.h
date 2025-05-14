#pragma once

#include "../input/Input.h"
#include "logic.h"
#include "renderer.h"
#include <memory>

namespace MVC {
class Simulation {
public:
  Simulation();

  void run();

private:
  std::unique_ptr<Input> input_;
  std::unique_ptr<MVC::Logic> logic_;
  std::unique_ptr<MVC::Renderer> render_;

  std::vector<std::unique_ptr<MVC::GameObject>> gameobjects_;
};
} // namespace MVC
