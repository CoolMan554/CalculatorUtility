#pragma once

#include <string>

class IDatabase {
public:
    virtual bool exec(const std::string& query) = 0;
    virtual void initializeSchema() = 0;
    virtual ~IDatabase() = default;
};