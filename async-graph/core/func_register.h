#pragma once

#include <functional>
#include <string>

#include "kernel_frame.h"

using KernelFunc = std::function<void(KernelContext*)>;

class FuncRegister {
   public:
    void AddFunc(const std::string& func_name, KernelFunc&& func) {
        func_map_.insert(std::make_pair(func_name, func));
    }

    KernelFunc GetFunc(const std::string& func_name) { return func_map_[func_name]; }

    void RemoveFunc(const std::string& func_name) { func_map_.erase(func_name); }

   private:
    std::unordered_map<std::string, KernelFunc> func_map_;
};

void RegisterKernelFunc(KernelFunc&& func) {}
