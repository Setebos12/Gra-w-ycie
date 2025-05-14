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
  Renderer(std::unique_ptr<Render::Drawer> &&drawer)
      : drawer_(std::move(drawer)) {}
  Renderer(const std::string &name, const sf::Vector2u &size)
      : drawer_(std::make_unique<Render::Drawer>(name, size, 60)) {}
  template <typename T>
  void draw(const std::vector<std::unique_ptr<T>> &all_objects)
    requires std::is_base_of_v<Render::IRenderObject, T>;

private:
  std::unique_ptr<Render::Drawer> drawer_;
};
} // namespace MVC
#include "renderer.impl.h"
