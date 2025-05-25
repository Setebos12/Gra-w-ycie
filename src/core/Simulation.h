#pragma once

#include "../input/Input.h"
#include "../logic/logic.h"
#include "../render/renderer.h"
#include "../util/logger.h"
#include "../util/event.h"
#include <memory>

namespace MVC {
class Simulation {
public:
  Simulation();

  void run();

  void updateHud();
  void handleInput(sf::RenderWindow &window);
  void handleBoardClicks();
  void handleSimulationStep(sf::Clock &simClock);

private:
  int simulationDelayMs_;
  bool running;
  sf::RenderWindow window;

  std::shared_ptr<Util::Logger> logger_;
  Util::Event<const std::string&, Util::Level> logEvent_;

  std::unique_ptr<MVC::Input> input_;
  std::unique_ptr<MVC::Logic> logic_;
  std::unique_ptr<MVC::Renderer> render_;

  std::vector<std::unique_ptr<MVC::GameObject>> gameobjects_;
};
} // namespace MVC
