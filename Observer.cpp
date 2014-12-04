#include <utility>

#include "Observable.hpp"
#include "Observer.hpp"

// T - observertype
// U - messagetype
template <typename T, typename U>
void common::Observer<T, U>::notify(T &notifier, U &&message)
{
  this->_notify(notifier, std::forward<U>(message));
}

////////////////////////////////////////////
// template specialization for shared_ptr 
////////////////////////////////////////////
template <typename T, typename U>
void common::Observer<std::shared_ptr<T>, U>::notify(T &notifier, U &&message)
{
  this->_notify(notifier, std::forward<U>(message));
}