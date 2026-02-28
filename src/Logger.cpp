#include "Logger.h"

Logger &Logger::instance() {
    static Logger logger;
    return logger;
}

Logger::Logger() {
    logger = spdlog::basic_logger_st("calculator_utility", "calculator_utility.log");
}

void Logger::log(spdlog::level::level_enum lvl, const std::string &message) {
    if (logger) {
        logger->log(lvl, message);
    }
}

void Logger::error(const std::string &message) {
    log(spdlog::level::level_enum::err, message);
}

void Logger::critical(const std::string &message) {
    log(spdlog::level::level_enum::critical, message);
}

void Logger::warn(const std::string &message) {
    log(spdlog::level::level_enum::warn, message);
}

void Logger::info(const std::string &message) {
    log(spdlog::level::level_enum::info, message);
}

void Logger::debug(const std::string &message) {
    log(spdlog::level::level_enum::debug, message);
}