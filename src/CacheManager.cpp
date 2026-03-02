#include "CacheManager.h"
#include <vector>

void CacheManager::addToCache(const CalculationRequest &op, double result) {
    cache_[op] = result;
}

bool CacheManager::findInCache(const CalculationRequest &key, double &res) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
        res = it->second;
        return true;
    }

    return false;
}

void CacheManager::loadInCache(const std::unique_ptr<IDatabase> &database_) {
    std::vector<CalculationRequest> history;
    database_->select("operations", "operation_type, arg1, arg2, result", history);

    for (const auto &record : history) {
        cache_[record] = record.result;
    }
}