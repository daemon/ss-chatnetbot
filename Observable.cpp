#include <algorithm>
#include <utility>
#include "Observer.hpp"
#include "Observable.hpp"

// T - Observer type
// U - Message type

template <typename T, typename U>
void common::Observable<T, U>::notifyAll(U &&message)
{
  for (auto observer : this->_observers)
    observer->notify(*this, std::forward<U>(message));
}

template <typename T, typename U>
void common::Observable<T, U>::addObserver(T *observer)
{
  static_assert(is_observer<T>::value, "Not an observer.");
  this->_observers.push_back(observer);
}

template <typename T, typename U>
void common::Observable<T, U>::removeObserver(T *observer)
{
  static_assert(is_observer<T>::value, "Not an observer.");
  std::remove(this->_observers.begin(), this->_observers.end(), observer);
}

////////////////////////////
// shared_ptr specialization
////////////////////////////
template <typename T, typename U>
void common::Observable<std::shared_ptr<T>, U>::notifyAll(U &&message)
{
  for (auto observer : this->_observers)
    observer->notify(*this, std::forward<U>(message));
}

template <typename T, typename U>
void common::Observable<std::shared_ptr<T>, U>::addObserver(std::shared_ptr<T> observer)
{
  static_assert(is_observer<T>::value, "Not an observer.");
  this->_observers.push_back(observer);
}

template <typename T, typename U>
void common::Observable<std::shared_ptr<T>, U>::removeObserver(std::shared_ptr<T> observer)
{
  static_assert(is_observer<T>::value, "Not an observer.");
  std::remove(this->_observers.begin(), this->_observers.end(), observer);
}