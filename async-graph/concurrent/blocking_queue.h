#pragma once

#include <condition_variable>
#include <list>
#include <mutex>
#include <optional>

template <typename T>
class BlockingQueue {
   public:
    BlockingQueue() = default;
    ~BlockingQueue() = default;
    BlockingQueue(const BlockingQueue &) = delete;
    BlockingQueue &operator=(const BlockingQueue &) = delete;

    void Add(const T &element) {
        {
            std::unique_lock<std::mutex> guard(mu_);
            queue_.push_back(element);
        }
        cond_.notify_one();
    }

    std::optional<T> Take() {
        std::unique_lock<std::mutex> guard(mu_);
        cond_.wait(guard, [this] { return !queue_.empty() || closed_; });
        if (queue_.empty() && closed_) {
            return std::nullopt;
        }
        auto element = queue_.front();
        queue_.pop_front();
        return element;
    }

    bool Empty() const {
        std::lock_guard<std::mutex> lock(mu_);
        return queue_.empty();
    }

    size_t Size() const {
        std::lock_guard<std::mutex> lock(mu_);
        return queue_.size();
    }

    void Close() {
        closed_ = true;
        cond_.notify_all();
    }

   private:
    mutable std::mutex mu_;
    std::condition_variable cond_;
    std::list<T> queue_;
    bool closed_ = false;
};