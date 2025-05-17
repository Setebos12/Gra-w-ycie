// Filename: event.h
//
// An event class being an impl of observer pattern
//
// Author: Piotr Pyrak

#pragma once

#include <algorithm>
#include <any>
#include <functional>
#include <memory>
#include <utility>

namespace Util {
template <typename... Args> class Event {
public:
  Event() = default;

  void invoke(Args... args);
  template <typename T>
  void subscribe(std::weak_ptr<T> &&obj, void (T::*listener)(Args...));
  template <typename T>
  void unsubscribe(std::weak_ptr<T> &&obj, void (T::*listener)(Args...));
  inline void clearListeners() { listeners_.clear(); }

private:
  // lambdas binding obj and func, returns true if should be removed
  std::vector<std::pair<std::function<bool(Args...)>, std::any>> listeners_;
};
} // namespace Util
#include "event.impl.h"
