#ifndef TASKTYPE1
#define TASKTYPE1
#include "ITask.h"
#include <functional>


class TaskType1:public ITask
{
private:
    int taskID;
    std::function<void(void)> func;
public:
    virtual void DoTask();
    TaskType1(int taskid,std::function<void(void)> func);
};
#endif