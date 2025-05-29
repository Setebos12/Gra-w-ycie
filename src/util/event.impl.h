// Filename: event.impl.h
//
// Implemenatation of template methods for event class
//
// Author: Piotr Pyrak

template <typename... Args>
void Util::Event<Args...>::invoke(Args... invokeArgs) {
  // iterator for loop to remove elements
  for (auto it = listeners_.begin(); it != listeners_.end();) {
      // remove if returns false, increment only if not removed
      if (!((**it)(invokeArgs...)))
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
      std::make_unique<Listener<T, Method>>(std::move(obj), listener));
}

template <typename... Args>
template <typename T, typename Method>
requires Util::ValidFunc<T, Method, Args...>
void Util::Event<Args...>::unsubscribe(std::weak_ptr<T> &&obj, Method listener) {
  listeners_.erase(
      std::remove_if(listeners_.begin(), listeners_.end(),
                     [&listener, obj = std::move(obj)](const auto &listenerPtr) {
                        return *listenerPtr == Listener<T, Method>(std::move(obj), listener);
                     }),
      listeners_.end());
}

template <typename... Args>
template <typename T, typename Method>
requires Util::ValidFunc<T, Method, Args...>
bool Util::Event<Args...>::Listener<T, Method>::operator()(Args... invokeArgs) {
    if (auto lp = obj_.lock()) {
        ((*lp).*method_)(invokeArgs...);
        return true;
    }
    return false;
}

template <typename... Args>
template <typename T, typename Method>
requires Util::ValidFunc<T, Method, Args...>
bool Util::Event<Args...>::Listener<T, Method>::operator==(const IListener& other) const {
    if (!std::is_convertible<IListener, Listener<T, Method>>())
        return false;
    const Listener<T, Method>& convert = dynamic_cast<const Listener<T, Method>&>(other);
    if (auto lp = obj_.lock()) {
        if (auto otherLp = convert.obj_.lock()) {
            return lp == otherLp && method_ == convert.method_;
        }
    }
    return false;
}
