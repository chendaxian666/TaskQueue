#include "TaskQueue.h"
#include <iostream>
#include <functional>

void TaskQueue::Enqueue(std::shared_ptr<ITask> spTask){
    std::lock_guard<std::mutex> lock(mutex);
    if(queue.size()<maxTaskNum){
        queue.push(spTask);
        con.notify_one();
    }
}

void TaskQueue::Start(){
    std::cout<<"TaskQueue start"<<std::endl;
    InitThread(threadNum);
}

void TaskQueue::GetAndDoWork(){
    try
    {
        while(true){
            if(stop) break;
            std::unique_lock<std::mutex> lock(mutex);
            if(queue.size()==0){
                con.wait(lock);
            }
            if(stop) break;
            auto spTask = queue.front();
            queue.pop();
            lock.unlock();
            spTask->DoTask();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void TaskQueue::InitThread(int num){
    auto func = std::bind(&TaskQueue::GetAndDoWork,this);
    while(num-->0){
        auto sp_thread = std::make_shared<std::thread>(func);
        spthreadlist.push_back(sp_thread);
    }
    for(const auto& thread:spthreadlist){
        thread->join();
    }
    
}

TaskQueue::TaskQueue(int maxNum,int threadnum){
    this->maxTaskNum = maxNum;
    this->threadNum = threadnum;
    stop = false;
}

void TaskQueue::Exit(){    //有些问题，结束的时候，队列还很多任务，直接退出了
    stop = true;
    con.notify_all();
}
