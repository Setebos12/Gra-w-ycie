// Filename: event.impl.h
//
// Implemenatation of template methods for event class
//
// Author: Piotr Pyrak

template <typename... Args>
void Util::Event<Args...>::invoke(Args... invokeArgs) {
  // iterator for loop to remove elements
  for (auto it = listeners_.begin(); it != listeners_.end();) {
      // remove elements based on return, increment only if not removed
      if (it->first(invokeArgs...))
        it = listeners_.erase(it);
      else
        ++it;
  }
}

template <typename... Args>
template <typename T, typename Method>
requires Util::ValidFunc<T, Method, Args...>
void Util::Event<Args...>::subscribe(std::weak_ptr<T> &&obj, Method listener) {
  listeners_.emplace_back(
      [obj = std::move(obj), listener](Args... invokeArgs) -> bool {
        if (auto sp = obj.lock()) {
          ((*sp).*listener)(invokeArgs...);
          return false;
        }
        return true;
      },
      obj);
}

template <typename... Args>
template <typename T, typename Method>
requires Util::ValidFunc<T, Method, Args...>
void Util::Event<Args...>::unsubscribe(std::weak_ptr<T> &&obj, Method listener) {
  listeners_.erase(
      std::remove_if(listeners_.begin(), listeners_.end(),
                     [obj = std::move(obj), listener](const auto &pair) {
                       return pair.second == obj &&
                                  pair.first.target_type() ==
                                      [&obj, listener]() -> bool { return false; };
                     }),
      listeners_.end());
}
