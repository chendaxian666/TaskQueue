#ifndef TASKQUEUE
#define TASKQUEUE
#include <queue>
#include "Task.h"
#include <thread>
#include <mutex>
#include <condition_variable>

class TaskQueue
{
private:
    /* data */
    std::queue<Task> tasks;
    std::mutex mutex;
    std::condition_variable con;
    std::vector<std::shared_ptr<std::thread>> spthreadlist;
    int maxTaskNum;
    int threadNum;
    bool stop;

    void InitThread(int num);
    void GetAndDoWork();
public:
    template <typename Func, typename... Args>
    void Enqueue(Func &&f, Args &&...args);
    /// @brief 初始化任务队列
    /// @param tasknum  最大任务数量
    /// @param threadnum  线程数
    TaskQueue(int tasknum,int threadnum);
    void Start();
    void Exit();
};

template <typename Func, typename... Args>
void TaskQueue::Enqueue(Func &&f, Args &&...args)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (tasks.size() < maxTaskNum)
    {
        tasks.emplace(std::forward<Func>(f), std::forward<Args>(args)...);
        con.notify_one();
    }
}
#endif