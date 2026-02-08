#pragma once

#include <array>
#include <getopt.h>
#include <string>

#include "nlohmann/json.hpp"

// for convenience
using json = nlohmann::json;

/**
 * @class CalculatorManager
 * @brief Manages command-line parsing, validation, calculation and output.
 */
class CalculatorManager {
  public:
    CalculatorManager() = default;
    ~CalculatorManager() = default;

    /**
     * @brief Entry point for program execution.
     *
     * @param argc Argument count
     * @param argv Argument values
     */
    void run(int argc, char **argv);

    /**
     * @brief Returns whether help option was requested.
     */
    [[nodiscard]] bool get_help_check() const {
        return help_check_;
    }

    /**
     * @brief Returns calculation result.
     */
    [[nodiscard]] double result() const {
        return result_;
    }

  private:
    /**
     * @brief Parses command-line arguments.
     *
     * @throws std::runtime_error if arguments are invalid
     */
    void parse_arguments(int argc, char **argv);

    /**
     * @brief Validates parsed input data.
     *
     * @throws std::runtime_error if validation fails
     */
    void validate_input();

    /**
     * @brief Performs calculation based on parsed input.
     */
    void calculate();

    /**
     * @brief Prints calculation result to stdout.
     */
    void print_result() const;

    /**
     * @brief Prints help message.
     *
     * @param program_name Name of executable
     */
    void print_help(const char *program_name) const;

    double first_argument_{0.0};
    double second_argument_{0.0};

    std::string operation_;

    bool help_check_{false};
    double result_{0.0};

    json input_json_;

    // ===== CLI options =====
    static constexpr std::array<option, 3> long_opts = {{{"help", no_argument, nullptr, 'h'},
                                                         {"in", required_argument, nullptr, 'i'},
                                                         {nullptr, 0, nullptr, 0}}};
};