#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include <memory>
#include <vector>
#include <type_traits>
#include "Observer.hpp"

template <typename T, typename = void>
struct is_observable
{
  static constexpr bool value = false;
};

template <typename T>
struct is_observable<T, typename std::enable_if<T::is_observable>::type>
{
  static constexpr bool value = true;
};

namespace common
{

template <typename ObserverType, typename MessageType>
class Observable
{
public:
  template <typename SelfType>
  void notifyAll(SelfType *self, MessageType message)
  {
    static_assert(is_observer<ObserverType>::value, "Not an observer.");
    for (ObserverType* observer : this->_observers)
      observer->update(self, message);
  }

  void addObserver(ObserverType* observer)
  {
    this->_observers.push_back(observer);
  }

  static constexpr bool is_observable = true;
private:
  std::vector<ObserverType*> _observers;
};

// Change to .tpp
}
#endif