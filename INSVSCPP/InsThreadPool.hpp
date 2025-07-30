#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
using namespace std;

class ThreadPool {
public:
    ThreadPool(size_t);
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> future<typename result_of<F(Args...)>::type>;
    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    vector<thread> workers;
    // the task queue
    queue<function<void()>> tasks;

    // synchronization
    mutex queue_mutex;
    condition_variable condition;
    bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
    : stop(false) // 构造函数前初始化stop，更高效
{
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back(
            [this]
            {
                for (;;)
                {
                    function<void()> task; // 定义任意可调用目标

                    { // 上锁后的作用域
                        unique_lock<mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            }
    );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
-> future<typename result_of<F(Args...)>::type>
{
    using return_type = typename result_of<F(Args...)>::type;

    /*
    * bind将用户函数f和参数args封装成无参的可调用对象
    * packaged_task封装任务，将任务结果与future关联
    * shared_ptr管理封装任务的生命周期
    */ 
    auto task = make_shared<packaged_task<return_type()>>(
        bind(forward<F>(f), forward<Args>(args)...)
    );

    future<return_type> res = task->get_future();
    {
        unique_lock<mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if (stop)
            throw runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one(); // 唤醒一个等待在条件变量上的线程
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        unique_lock<mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (thread& worker : workers)
        worker.join();
}

#endif