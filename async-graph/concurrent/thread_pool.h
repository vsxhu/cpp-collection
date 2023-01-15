#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "blocking_queue.h"

class ThreadPool {
   public:
    explicit ThreadPool(size_t size) : stopped_(false) {
        for (int i = 0; i < size; ++i)
        {
            workers_.emplace_back([this] {
                while (true)
                {
                    if (stopped_ && tasks_.Empty())
                    { return; }
                    auto cur_task = tasks_.Take();
                    if (cur_task == std::nullopt)
                    { break; }
                    cur_task.value()();
                }
            });
        }
    };

    ~ThreadPool() {
        stopped_ = true;
        tasks_.Close();
        for (auto& worker : workers_)
        { worker.join(); }
    }

    template <class F, class... Args>
    std::future<typename std::result_of<F(Args...)>::type> Enqueue(F&& f, Args&&... args) {
        using ReturnType = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<ReturnType> res = task->get_future();
        tasks_.Add([task]() { (*task)(); });
        return res;
    }

   private:
    std::vector<std::thread> workers_;
    BlockingQueue<std::function<void(void)>> tasks_;

    std::atomic<bool> stopped_;
};