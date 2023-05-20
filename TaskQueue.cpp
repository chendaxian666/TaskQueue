#include "TaskQueue.h"
#include <iostream>

void TaskQueue::Enqueue(std::shared_ptr<ITask> spTask){
    std::lock_guard<std::mutex> lock(pushmutex);
    if(queue.size())
    queue.push(spTask);
}

void TaskQueue::Start(){
    std::cout<<"TaskQueue start"<<std::endl;
    InitThread(4);
    
}

void TaskQueue::GetAndDoWork(){
    std::lock_guard<std::mutex> lock(getmutex);
    if(queue.size()>0){
        auto spTask = queue.front();
        queue.pop();
        spTask->DoTask();
    }
}

void TaskQueue::InitThread(int num){
    while(num-->0){
        std::thread *t = new std::thread(GetAndDoWork);
        threadlist.push_back(*t);
    }
}

TaskQueue::TaskQueue(int maxNum){
    maxTaskNum = maxNum;
}
