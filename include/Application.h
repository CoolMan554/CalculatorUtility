#pragma once

#include "Calculator.h"
#include "Checker.h"
#include "CliParser.h"
#include "JsonInputParser.h"
#include "IDatabase.h"
#include "OperationRepository.h"

#include <memory>
#include <unordered_map>

class Application {
  public:
    Application() = default;
    ~Application() = default;

    Application(const Application &) = default;
    Application &operator=(const Application &) = default;

    Application(Application &&) noexcept = default;
    Application &operator=(Application &&) noexcept = default;

    void init();

    void run(int argc, char **argv);

  private:
    CliParser cli_;
    JsonInputParser json_parser_;
    Checker check_;
    Calculator calc_;
    std::unique_ptr<IDatabase> database_;
    static inline std::unordered_map<OperationKey, double, OperationKeyHash> cache_{};    

    void addToCache(const CalculationRequest& req, double result);
    bool findInCache(const OperationKey& key, double& res);
    void loadInCache();
};