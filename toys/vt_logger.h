#pragma once
#include <iostream>
#include <string_view>
#include <type_traits>
#include "pretty_type.h"

namespace cxxcoll::toy {
class Logger {
   public:
    template <class... Args>
    static void Log(const char* msg, Args&&... args) {
        std::string str_msg{msg};
        auto a = {(VarReplace(str_msg, std::forward<decltype(args)>(args)), 0)...};
        std::cout << str_msg << std::endl;
    }

   private:
    template <class T>
    static void VarReplace(std::string& msg, T&& var) {
        std::cout << std::is_same_v<std::decay<T>, std::string> << std::endl;
        if constexpr (std::is_arithmetic_v<std::decay_t<T>>) {
            DigitReplace(msg, std::forward<T>(var));
        } else if constexpr (std::is_same_v<std::decay<T>, std::string> ||
                             std::is_same_v<std::decay<T>, char*>) {
            StrReplace(msg, std::forward<T>(var));
        }
    }

    template <class T>
    static void DigitReplace(std::string& msg, T&& digit) {
        auto pos = msg.find("{}");
        if (pos != std::string::npos) {
            msg.erase(pos, 2).insert(pos, std::to_string(digit));
        }
    }

    template <class T>
    static void StrReplace(std::string& msg, T&& str) {
        auto pos = msg.find("{}");
        if (pos != std::string::npos) {
            msg.erase(pos, 2).insert(pos, str);
        }
    }
};
}  // namespace cxxcoll::toy
