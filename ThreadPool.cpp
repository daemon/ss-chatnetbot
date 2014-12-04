#include <functional>
#include <utility>

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(unsigned int nThreads = 2) : _running(true), _simpleTasksLen(0)
{
  auto fn = std::bind(&ThreadPool::_run, this); 

  while (nThreads--)
    this->_threads.push_back(std::thread(fn));
}

ThreadPool::~ThreadPool()
{
  this->_running = false;
  this->_cv.notify_all();
}

template <typename FunctionT>
void ThreadPool::queueSimpleTask(FunctionT&& fn)
{
  std::lock_guard<std::mutex> lock(this->_mtx);
  this->_simpleTasks.push(std::forward<FunctionT>(fn));
  this->_cv.notify_one();
}

void ThreadPool::_run()
{
  std::mutex cvMtx;
  std::unique_lock<std::mutex> cvLock(cvMtx);

  while(this->_running)
  {
    this->_cv.wait(cvLock);
    std::lock_guard<std::mutex> lock(this->_mtx);
    while (_simpleTasksLen > 0)
    {      
      auto fn = this->_simpleTasks.pop();
      --_simpleTasksLen;
      lock.unlock();

      // Best exception handling ever
      try
      {
        fn();
      } catch(...) {}
    }
    // Lock released here...
  }
}