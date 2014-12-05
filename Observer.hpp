#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T, typename = void>
struct is_observer
{
  static constexpr bool value = false;
};

template <typename T>
struct is_observer<T, typename std::enable_if<T::is_observer>::type>
{
  static constexpr bool value = true;
};

namespace common
{

template <typename ObservedType, typename MessageType>
class Observer
{
public:
  void update(ObservedType* notifier, MessageType message)
  {
    this->_notify(notifier, message);
  }

  static constexpr bool is_observer = true;

private:
  virtual void _notify(ObservedType*, MessageType) = 0;
};

}

#endif