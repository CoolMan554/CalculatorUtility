#pragma once

#include <iostream>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

class Logger {
  public:
    static Logger &instance();

    Logger();
    ~Logger() = default;

    Logger(const Logger &) = delete;
    Logger operator=(const Logger &) = delete;

    Logger(Logger &&) noexcept = delete;
    Logger operator=(Logger &&) noexcept = delete;

    void error(const std::string &message);
    void critical(const std::string &message);
    void warn(const std::string &message);
    void info(const std::string &message);
    void debug(const std::string &message);

  private:
    void log(spdlog::level::level_enum lvl, const std::string &message);
    std::shared_ptr<spdlog::logger> logger{nullptr};
};