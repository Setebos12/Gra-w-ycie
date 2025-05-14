// Filename: gameobject.h
//
// All objects that need to interact with the game loop will inherit this class,
// requires implementation of draw and update functions.
//
// Author: Piotr Pyrak

#pragma once

#include "../render/irenderobj.h"
#include <string>
#include <ostream>
#include <istream>

namespace MVC {
class GameObject : public Render::IRenderObject {
public:
  GameObject(const std::string &name) : name_(name) {}
  virtual ~GameObject() = default;

  // recivers renderer object where it will be able to call drawing methods
  virtual void draw(const Render::Drawer &drawer) override = 0;
  virtual void update() = 0;

  const auto &getName() { return name_; }
  void setName(const std::string &name) { name_ = name; }

  virtual std::string printString() const = 0;
  virtual void readString(const std::string& read) = 0;

protected:
  friend std::ostream &operator<<(std::ostream &write, const GameObject& gameObj);
  friend std::istream &operator>>(std::istream &read, GameObject& gameObj);

private:
  std::string name_;
};
} // namespace MVC
