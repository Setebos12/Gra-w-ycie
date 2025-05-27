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

  void run();

  void updateHud();
  void handleBoardClicks();
  void handleSimulationStep(sf::Clock &simClock);

private:
  int simulationDelayMs_;
  bool running;
  sf::RenderWindow window;

  std::shared_ptr<Util::Logger> logger_;
  std::shared_ptr<Util::Event<const std::string&, Util::Level>> logEvent_;

  std::unique_ptr<MVC::Input> input_;
  std::unique_ptr<MVC::Logic> logic_;
  std::unique_ptr<MVC::Renderer> render_;
  std::unique_ptr<Uipanel> uipanel_;


  std::vector<std::shared_ptr<MVC::GameObject>> gameobjects_;
};
} // namespace MVC
