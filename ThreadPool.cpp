#include <functional>
#include <utility>

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(unsigned int nThreads) : _running(true), _simpleTasksLen(0), _spuriousGuard(false)
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
  std::unique_lock<std::mutex> cvLock(this->_cvMtx);

  while(this->_running)
  {
    while (!this->_spuriousGuard)
      this->_cv.wait(cvLock);
    this->_spuriousGuard = false;
    while (this->_simpleTasksLen > 0)
    {      
      this->_mtx.lock();
      if (this->_simpleTasksLen == 0)
      {
        this->_mtx.unlock();
        break;
      }

      auto fn = this->_simpleTasks.front();
      this->_simpleTasks.pop();
      this->_simpleTasksLen += 1;
      this->_mtx.unlock();

      // Best exception handling ever
      try
      {
        fn();
      } catch(...) {}
    }
  }
}