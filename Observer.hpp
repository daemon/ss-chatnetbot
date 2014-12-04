#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <memory>
#include <type_traits>
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

template <typename ObservedType, typename ReturnType>
class Observer
{
public:
  void notify(ObservedType &notifier, ReturnType &&message);

  static constexpr bool is_observer = true;

private:
  virtual void _notify(ObservedType*, ReturnType) = 0;
};

// Partial specialization for shared_ptr
template <typename ObservedType, typename ReturnType>
class Observer<std::shared_ptr<ObservedType>, ReturnType>
{
public:
  void notify(ObservedType &notifier, ReturnType &&message);

  static constexpr bool is_observer = true;

private:
  virtual void _notify(std::shared_ptr<ObservedType>, ReturnType) = 0;
};

}

#endif