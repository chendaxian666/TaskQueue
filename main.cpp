#include <iostream>
#include "TaskTyep1.h"
#include <thread>
#include "TaskQueue.h"
#include <unistd.h>
int main(){

    TaskQueue taskQueue(7,4);

    std::thread taskThread(   //这个线程用来启动消费者
        [&](){
            taskQueue.Start();
        }
    );

    auto f = [](){
        std::cout<<"work work~"<<std::endl;
    };
    for(int i =0;i<10;i++){
        sleep(0.5);
        std::shared_ptr<ITask> ptask = std::make_shared<TaskType1>(i,f);
        taskQueue.Enqueue(ptask);
    }

    sleep(10);//等一阵，让消费者都陷于阻塞，然后重新开始生产
    for(int i =0;i<20;i++){  //差不多4,5秒队列就满了，其他的就丢了
        sleep(0.5);
        std::shared_ptr<ITask> ptask = std::make_shared<TaskType1>(i,f);
        taskQueue.Enqueue(ptask);
    }
    taskQueue.Exit();
    taskThread.join();
    return 0;
}