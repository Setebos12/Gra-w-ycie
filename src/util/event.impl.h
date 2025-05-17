//Filename: event.impl.h
//
//Implemenatation of template methods for event class
//
//Author: Piotr Pyrak

template <typename... Args>
void Util::Event<Args...>::invoke(Args... invokeArgs) {
  // iterator for loop to remove elements
  for (auto it = listeners_.begin(); it != listeners_.end(); ++it) {
    // remove elements based on return
    if (it->first(invokeArgs...))
      listeners_.erase(it);
  }
}

template <typename... Args>
template <typename T>
void Util::Event<Args...>::subscribe(std::weak_ptr<T> &&obj,
                                     void (T::*listener)(Args...)) {
  listeners_.emplace_back(
      [obj = std::move(obj), listener](Args... invokeArgs) -> bool {
        if (obj.expired())
          return true;
        obj->listener(invokeArgs...);
        return false;
      },
      obj);
}

template <typename... Args>
template <typename T>
void Util::Event<Args...>::unsubscribe(std::weak_ptr<T> &&obj,
                                       void (T::*listener)(Args...)) {
  listeners_.erase(
      std::remove_if(listeners_.begin(), listeners_.end(),
                     [obj = std::move(obj), listener](const auto &pair) {
                       return pair.second == obj &&
                                  pair.first.target_type() ==
                                      [&obj, listener]() -> bool {};
                     }),
      listeners_.end());
}
