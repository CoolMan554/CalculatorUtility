#include "DBConfig.h"
#include <fstream>
#include "nlohmann/json.hpp"

DBConfig::DBConfig(const std::string& path){
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