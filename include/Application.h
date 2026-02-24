#pragma once

#include "Calculator.h"
#include "Checker.h"
#include "CliParser.h"
#include "JsonInputParser.h"
#include "IDatabase.h"

#include <memory>

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
};