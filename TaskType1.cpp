#include "TaskTyep1.h"
#include <iostream>
#include <unistd.h>


void TaskType1::DoTask(){

    std::cout<<"this task is "<<taskID<<std::endl;\
    if(func!=nullptr){
        func();
    }
    sleep(1);
    std::cout<<"task "<<taskID<<"over"<<std::endl;

}

TaskType1::TaskType1(int taskid,std::function<void(void)> func){
    this->func = func;
    this->taskID = taskid;
    // std::cout<<"ctor"<<std::endl;
}