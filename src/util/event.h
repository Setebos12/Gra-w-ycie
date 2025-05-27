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
#include <type_traits>

namespace Util {
template <typename T, typename Method, typename... Args>
concept ValidFunc =
	std::is_same_v<Method, void (T::*)(Args...) const> ||
	std::is_same_v<Method, void (T::*)(Args...)>;

template <typename... Args> class Event {
public:
  Event() = default;

  void invoke(Args... args);

  template <typename T, typename Method>
  requires ValidFunc<T, Method, Args...>
  void subscribe(std::weak_ptr<T> &&obj, Method listener);

  template <typename T, typename Method>
  requires ValidFunc<T, Method, Args...>
  void unsubscribe(std::weak_ptr<T> &&obj, Method listener);

  inline void clearListeners() { listeners_.clear(); }

private:
  // lambdas binding obj and func, returns true if should be removed
  std::vector<std::pair<std::function<bool(Args...)>, std::any>> listeners_; //for unsub have a struct
};
} // namespace Util
#include "event.impl.h"
