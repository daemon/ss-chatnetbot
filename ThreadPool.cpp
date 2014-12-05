#include <functional>
#include <utility>

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(unsigned int nThreads) : _running(true), _simpleTasksLen(0)
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

void ThreadPool::_run()
{
  std::mutex cvMtx;
  std::unique_lock<std::mutex> cvLock(cvMtx);

  while(this->_running)
  {
    this->_cv.wait(cvLock);
    this->_mtx.lock();
    while (_simpleTasksLen > 0)
    {      
      auto fn = this->_simpleTasks.front();
      this->_simpleTasks.pop();
      --_simpleTasksLen;
      this->_mtx.unlock();

      // Best exception handling ever
      try
      {
        fn();
      } catch(...) {}
    }
    // Lock released here...
  }
}