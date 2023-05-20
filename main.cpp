#include <iostream>
#include "TaskTyep1.h"
#include <thread>
#include "TaskQueue.h"
int main(){

    TaskQueue taskQueue;

    std::thread taskThread(
        [&](){
            taskQueue.Start();
        }
    );

    for(int i =0;i<10;i++){
        auto f = [](){
            std::cout<<"work work~"<<std::endl;
        };
        std::shared_ptr<ITask> ptask = std::make_shared<TaskType1>(i,f);
        taskQueue.Enqueue(ptask);
    }
    taskThread.join();
    return 0;
}