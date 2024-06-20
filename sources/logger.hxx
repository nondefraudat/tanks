#pragma once

#include <iostream>

class logger {
public:
    template <typename ...args_t>
    static void log(args_t &&...args) noexcept {
        (std::cout << ... << args) << std::endl;
    }
};
