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
  class IListener {
  public:
  	virtual ~IListener() = default;
    //true if obj is dead and listener should be removed
  	virtual bool operator()(Args... args) = 0;
  	virtual bool operator==(const IListener& other) const = 0;
  };
  
  template <typename T, typename Method>
  requires ValidFunc<T, Method, Args...>
  class Listener : public IListener {
  public:
      Listener(std::weak_ptr<T> &&obj, Method method) : obj_(std::move(obj)), method_(method) {}
      bool operator()(Args... args) override;
      bool operator==(const IListener& other) const override;
  private:
      std::weak_ptr<T> obj_;
      Method method_;
  };

  std::vector<std::unique_ptr<IListener>> listeners_;
};
} // namespace Util
#include "event.impl.h"