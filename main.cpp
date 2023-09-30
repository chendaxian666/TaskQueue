#include <iostream>
#include <thread>
#include "TaskQueue.h"
int main()
{

    TaskQueue taskQueue(5, 4); // 任务队列长度为5，有4个工作线程

    auto consume = [&]()
    {
        taskQueue.Start();        //消费者线程
    };
    std::thread thread(consume);

    auto f = [](int id)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "task " << id << " work work~" << std::endl;
    };

    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        taskQueue.Enqueue(f, i);
    }

    std::this_thread::sleep_for(std::chrono::seconds(5)); // 等一阵，让消费者都陷于阻塞，然后重新开始生产
    for (int i = 0; i < 20; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        taskQueue.Enqueue(f,i);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2)); //过两秒后退出任务队列
    taskQueue.Exit();
    std::cout<<"over";

    thread.join();

    return 0;
}