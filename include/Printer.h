#pragma once

#include <string>
#include <iostream>

class Printer {
public:
    /**
     * @brief Prints calculation result to stdout.
     */
    template<typename T>
    static void print(T result) {
        std::cout << result << "\n";
    }

    /**
     * @brief Prints help message.
     *
     * @param program_name Name of executable
     */
    static void print_help(const std::string& progName);
};