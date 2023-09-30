#ifndef TASK
#define TASK
#include <functional>

class Task
{
public:
    template <typename Func, typename... Args>
    Task(Func &&f, Args &&...args)
        : func_(std::function<void()>(std::bind(std::forward<Func>(f), std::forward<Args>(args)...))) {} // bind拷贝了局部变量，存储在function中

    void operator()()
    {
        func_();
    }

private:
    std::function<void()> func_;
};
#endif
