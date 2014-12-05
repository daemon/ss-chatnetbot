#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "Common.hpp"

class ThreadPool
{
  MAKE_SINGLETON(ThreadPool)
public:
  ThreadPool(unsigned int nThreads = 2);
  ~ThreadPool();

  /* TODO: Implement later.
  template <typename FunctionT, typename PromiseT>
  auto queueFuturedTask(FunctionT&& fn, PromiseT promise) -> std::future<decltype(fn())>;
  */

  template <typename FunctionT>
  void queueSimpleTask(FunctionT&& fn)
  {
    std::lock_guard<std::mutex> lock(this->_mtx);
    this->_simpleTasks.push(std::forward<FunctionT>(fn));
    this->_cv.notify_one();
  } // TODO: Change to .tpp

private:
  void _run();

  std::atomic<bool> _running;
  std::atomic<int> _simpleTasksLen;
  std::condition_variable _cv;
  std::mutex _mtx;
  std::vector<std::thread> _threads;
  std::queue<std::function<void()>> _simpleTasks;
};

#endif