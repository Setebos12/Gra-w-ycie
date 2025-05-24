#pragma once

#include "../input/Input.h"
#include "../logic/logic.h"
#include <memory>
#include "../render/renderer.h"
#include "../ui/hud.h"
namespace MVC {
class Simulation {
public:
  Simulation();

  void run();

  void updateHud();
  void handleInput(sf::RenderWindow& window);
  void handleBoardClicks();
  void handleSimulationStep(sf::Clock& simClock);

private:
	int simulationDelayMs_;
	bool running;
  sf::RenderWindow window;

  std::unique_ptr<Input> input_;
  std::unique_ptr<MVC::Logic> logic_;
  std::unique_ptr<MVC::Renderer> render_;

  std::vector<std::unique_ptr<MVC::GameObject>> gameobjects_;
};
} // namespace MVC
