// Filename: event.h
//
// An event class being an impl of observer pattern
//
// Author: Piotr Pyrak

#pragma once

#include <functional>
#include <memory>
#include <algorithm>
#include <utility>
#include <any>

namespace Util {
template <typename... Args> class Event {
public:
  void invoke(Args... args);
  template <typename T>
  void subscribe(const std::weak_ptr<T> &obj, void (T::*listener)(Args...));
  template <typename T>
  void unsubscribe(const std::weak_ptr<T> &obj, void (T::*listener)(Args...));
  inline void clearListeners() { listeners_.clear(); }

private:
  // lambdas binding obj and func, returns true if should be removed
  std::vector<std::pair<std::function<bool(Args...)>, std::any>> listeners_;
};
} // namespace Util

template <typename... Args>
void Util::Event<Args...>::invoke(Args... invokeArgs) {
  //iterator for loop to remove elements
  for (auto it = listeners_.begin(); it != listeners_.end(); ++it) {
	//remove elements based on return
	if (it->first(invokeArgs...))
		listeners_.erase(it);
  }
}

template <typename... Args>
template <typename T>
void Util::Event<Args...>::subscribe(const std::weak_ptr<T> &obj,
                                     void (T::*listener)(Args...)) {
  listeners_.emplace_back([&obj, listener](Args... invokeArgs) -> bool {
    if (obj.expired())
	  return true;
    obj->listener(invokeArgs...);
	return false;
  }, obj);
}

template <typename... Args>
template <typename T>
void Util::Event<Args...>::unsubscribe(const std::weak_ptr<T> &obj,
                                       void (T::*listener)(Args...)) {
    listeners_.erase(std::remove_if(listeners_.begin(), listeners_.end(),
	[&obj, listener](const auto& pair) {
    	return pair.second == obj && pair.first.target_type() == [&obj, listener]() -> bool {};
	}),
	listeners_.end());
}
