#ifndef TASKQUEUE
#define TASKQUEUE
#include <queue>
#include "ITask.h"
#include <thread>
#include <mutex>
#include <condition_variable>

class TaskQueue
{
private:
    /* data */
    std::queue<std::shared_ptr<ITask>> queue;
    std::mutex mutex;
    std::condition_variable con;
    std::vector<std::shared_ptr<std::thread>> spthreadlist;
    int maxTaskNum;
    int threadNum;
    bool stop;

    void InitThread(int num);
    void GetAndDoWork();
public:
    void Enqueue(std::shared_ptr<ITask>);
    TaskQueue(int tasknum,int threadnum);
    void Start();
    void Exit();
};
#endif