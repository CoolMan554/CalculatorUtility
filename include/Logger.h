#pragma once

#include <iostream>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

class Logger {
  public:
    static spdlog::logger &instance() {
        static auto logger = [&] {
            try {
                return spdlog::basic_logger_st("calculator_utility", "calculator_utility.log");
            } catch (...) {
                return spdlog::stdout_color_st("calculator_utility_fallback");
            }
        }();
        return *logger;
    }

    Logger(const Logger &) = delete;
    Logger operator=(const Logger &) = delete;

  private:
    Logger() = default;
    ~Logger() = default;
};