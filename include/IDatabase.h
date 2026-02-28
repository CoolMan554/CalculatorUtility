#pragma once

#include "CalculationRequest.h"

#include <string>
#include <vector>

class IDatabase {
public:
    virtual bool exec(const std::string& query) = 0;
    virtual bool exec_params(const std::string& query, const std::vector<std::string>& values) = 0;
    virtual void initializeSchema() = 0;
    virtual void insert(const std::string& table, const std::vector<std::string>& columns, const std::vector<std::string>& values) = 0;
    virtual void select(const std::string& table, const std::string& columns, std::vector<CalculationRequest>& res) = 0;
    virtual ~IDatabase() = default;
    const std::string TABLE_DATABASE = "operations";
};