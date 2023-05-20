#ifndef TASKQUEUE
#define TASKQUEUE
#include <queue>
#include "ITask.h"
#include <thread>
#include <mutex>

class TaskQueue
{
private:
    /* data */
    std::queue<std::shared_ptr<ITask>> queue;
    std::mutex pushmutex;
    std::mutex getmutex;
    std::vector<std::thread> threadlist;
    int maxTaskNum;

    void InitThread(int num);
    void GetAndDoWork();
public:
    void Enqueue(std::shared_ptr<ITask>);
    TaskQueue(int num);
    void Start();
    void Exit();
};
#endif