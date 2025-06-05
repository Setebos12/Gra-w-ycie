// Filename: renderer.h
//
// During a game loop this class is given control and is responsible for drawing
// objects.
//
// Author: Piotr Pyrak

#pragma once

#include "drawer.h"
#include "irenderobj.h"
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

namespace MVC {
class Renderer {
public:
  Renderer(std::shared_ptr<sf::RenderWindow> window, const std::shared_ptr<Util::Event<const std::string&, Util::Level>>& logEvent)
      : drawer_(std::make_unique<Render::Drawer>(window, logEvent)), logEvent_(logEvent) {}
  template <typename T>
  void draw(const std::vector<std::shared_ptr<T>> &all_objects)
    requires std::is_base_of_v<Render::IRenderObject, T>;

private:
  std::unique_ptr<Render::Drawer> drawer_;
  std::shared_ptr<Util::Event<const std::string&, Util::Level>> logEvent_;
};
} // namespace MVC
#include "renderer.impl.h"
