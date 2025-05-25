// Filename: gameobject.h
//
// All objects that need to interact with the game loop will inherit this class,
// requires implementation of draw and update functions.
//
// Author: Piotr Pyrak

#pragma once

#include "../render/irenderobj.h"
#include "../util/event.h"
#include "../util/logger.h"
#include <istream>
#include <optional>
#include <ostream>
#include <string>

namespace MVC {
class GameObject : public Render::IRenderObject {
public:
  GameObject(const std::string &name,
             std::optional<
                 std::shared_ptr<Util::Event<const std::string &, Util::Level>>>
                 logEvent = std::nullopt)
      : name_(name), logEvent_(logEvent) {}
  virtual ~GameObject() = default;

  // recivers renderer object where it will be able to call drawing methods
  virtual void draw(Render::Drawer &drawer) override = 0;
  virtual void update() = 0;

  const auto &getName() { return name_; }
  void setName(const std::string &name) { name_ = name; }

  virtual std::string printString() const = 0;
  virtual void readString(const std::string &read) = 0;

protected:
  friend std::ostream &operator<<(std::ostream &write,
                                  const GameObject &gameObj);
  friend std::istream &operator>>(std::istream &read, GameObject &gameObj);

  std::optional<std::shared_ptr<Util::Event<const std::string &, Util::Level>>>
      logEvent_;
private:
  std::string name_;
};
} // namespace MVC
