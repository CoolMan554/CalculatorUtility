#pragma once

#include "CalculationRequest.h"
#include "IDatabase.h"

#include <memory>
#include <unordered_map>

class CacheManager {
  public:
    void addToCache(const CalculationRequest &req, double result);
    bool findInCache(const CalculationRequest &key, double &res);
    void loadInCache(const std::unique_ptr<IDatabase> &database_);

  private:
    static inline std::unordered_map<CalculationRequest, double, CalculationKeyHash> cache_{};
};