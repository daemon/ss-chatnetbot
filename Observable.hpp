#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include <memory>
#include <vector>

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
  void notifyAll(MessageType &&message);
  void addObserver(ObserverType *observer);
  void removeObserver(ObserverType *observer);

  std::vector<ObserverType *> getObservers() const;

  static constexpr bool is_observable = true;
private:
  std::vector<ObserverType *> _observers;
};

template <typename ObserverType, typename MessageType>
class Observable<typename std::shared_ptr<ObserverType>, MessageType>
{
public:
  void notifyAll(MessageType &&message);
  void addObserver(std::shared_ptr<ObserverType> observer);
  void removeObserver(std::shared_ptr<ObserverType> observer);
  
  std::vector<std::shared_ptr<ObserverType>> getObservers() const;

  static constexpr bool is_observable = true;
private:
  std::vector<std::shared_ptr<ObserverType>> _observers;
};

}
#endif