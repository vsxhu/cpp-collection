#pragma once

#include <any>
#include <future>
#include <vector>

class KernelContext {
   public:
    using ValueType = std::any;
    template <class T>
    void AddInput(T&& val) {
        inputs_.emplace_back(std::forward<T>(val));
    }

    template <class T>
    T GetInput(int idx) {
        return std::any_cast<T>(inputs_[idx]);
    }

    template <class T>
    void AddOutput(T&& val) {
        results_.emplace_back(std::forward<T>(val));
    }

    template <class T>
    T GetOutput(int idx) {
        return std::any_cast<T>(results_[idx]);
    }


    std::any GetOutput(int idx) {
        return results_[idx];
    }
    unsigned int GetInputSize() { return inputs_.size(); }

    unsigned int GetOutputSize() { return results_.size(); }

   private:
    std::vector<ValueType> inputs_;
    std::vector<ValueType> results_;
};
