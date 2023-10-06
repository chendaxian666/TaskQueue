#include "TaskQueue.h"
#include <iostream>
#include <functional>


void TaskQueue::Start()
{
    std::cout << "TaskQueue start" << std::endl;
    InitThread(threadNum);
}

void TaskQueue::GetAndDoWork()
{
    try
    {
        while (true)
        {
            if (stop)
                break;
            std::unique_lock<std::mutex> lock(mutex);
            if(tasks.empty())
            {
                con.wait(lock);
            }
            if (stop)
                break;
            if(!tasks.empty()){
                auto task = tasks.front();
                tasks.pop();
                lock.unlock();
                task();
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void TaskQueue::InitThread(int num)
{
    auto func = std::bind(&TaskQueue::GetAndDoWork, this);
    while (num-- > 0)
    {
        spthreadlist.emplace_back(std::make_shared<std::thread>(func));
    }
    for (const auto &thread : spthreadlist)
    {
        thread->join();
    }
}

TaskQueue::TaskQueue(int maxNum, int threadnum)
{
    this->maxTaskNum = maxNum;
    this->threadNum = threadnum;
    stop = false;
}

void TaskQueue::Exit()
{ 
    stop = true;
    con.notify_all();
}
