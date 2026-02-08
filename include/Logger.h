#pragma once

#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Logger
{
public:
    static spdlog::logger& instance(){
        static auto logger = [&] {
            try {
                return spdlog::basic_logger_st("calculator_utility", "calculator_utility.log");         
            }
            catch(...)
            {
                return spdlog::stdout_color_st("calculator_utility_fallback");
            }   
        }();
        return *logger;        
    }
private:
    Logger() = default;
    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger operator=(const Logger&) = delete;
};