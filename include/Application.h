#pragma once

#include "CacheManager.h"
#include "Calculator.h"
#include "Checker.h"
#include "CliParser.h"
#include "IDatabase.h"
#include "JsonInputParser.h"

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
    CacheManager cache_m;
    std::unique_ptr<IDatabase> database_;
};