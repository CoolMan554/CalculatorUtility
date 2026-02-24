#pragma once

#include <iostream>
#include <string>

#include "CalculationRequest.h"

class Printer {
  public:
    /**
     * @brief Prints calculation result to stdout.
     */
    static void print(const OperationKey &req);

    /**
     * @brief Prints help message.
     *
     * @param program_name Name of executable
     */
    static void print_help(const std::string &progName);
};