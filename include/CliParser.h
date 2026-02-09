#pragma once

#include <getopt.h>
#include <string>

class CliParser {
public:
    CliParser() = default;
    ~CliParser() = default;

    /**
     * @brief Parses command-line arguments.
     *
     * @throws std::runtime_error if arguments are invalid
     */
    void parse_arguments(int argc, char **argv);

    bool get_status_help() const {
        return show_help;
    }
    std::string get_input_data() const {
        return input_data;
    }
private:
    bool show_help{false};
    std::string input_data;
};