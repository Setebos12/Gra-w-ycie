// Filename: Simulation.h
//
// Description:
//     Declares the MVC::Simulation class, which manages the initialization,
//     main loop, and coordination of core subsystems such as input handling,
//     logic processing, and rendering.
//
// Authors: Piotr Pyrak, Krzysztof Rutkowski, Bartosz Paszkiewicz

#pragma once

#include "../input/Input.h"
#include "../logic/logic.h"
#include "../render/renderer.h"
#include "../util/logger.h"
#include "../util/event.h"
#include <memory>
#include "../ui/uipanel.h"


namespace MVC {
class Simulation {
public:
  Simulation();
  void initWindow(std::weak_ptr<MVC::Simulation>&& selfRef);

  void run();
private:
  void stopRun() { running_ = false; }
  bool running_ = false;
  std::shared_ptr<sf::RenderWindow> window_;

  std::shared_ptr<Util::Logger> logger_;
  std::shared_ptr<Util::Event<const std::string&, Util::Level>> logEvent_;

  std::shared_ptr<MVC::Input> input_;
  std::shared_ptr<MVC::Logic> logic_;
  std::shared_ptr<MVC::Renderer> render_;

  std::vector<std::shared_ptr<MVC::GameObject>> gameobjects_;
};
} // namespace MVC
