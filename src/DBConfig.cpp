#include "DBConfig.h"
#include "nlohmann/json.hpp"
#include <fstream>

DBConfig::DBConfig(const std::string &path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open config file");
    }

    nlohmann::json j;
    file >> j;

    host = j["database"]["host"];
    port = j["database"]["port"];
    user = j["database"]["user"];
    password = j["database"]["password"];
    dbname = j["database"]["dbname"];
}

std::string DBConfig::findConfig() {
    if (std::filesystem::exists("./config/config_db.json"))
        return "./config/config_db.json";

    if (std::filesystem::exists("/etc/calculator_utility/config_db.json"))
        return "/etc/calculator_utility/config_db.json";

    throw std::runtime_error("Config file not found");
}