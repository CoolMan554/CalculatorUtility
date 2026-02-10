#include "CliParser.h"
#include "Logger.h"
#include "Printer.h"

#include <array>

void CliParser::parse_arguments(int argc, char **argv) {

    // Resetting the counter
    optind = 1;
    opterr = 1;

    int opt;

    // ===== CLI options =====
    static constexpr std::array<option, 3> long_opts = {{{"help", no_argument, nullptr, 'h'},
                                                         {"in", required_argument, nullptr, 'i'},
                                                         {nullptr, 0, nullptr, 0}}};

    while ((opt = getopt_long(argc, argv, "hi:", long_opts.data(), nullptr)) != -1) {
        switch (opt) {
        case 'h':
            show_help = true;
            break;
        case 'i':
            if (optarg != nullptr) {
                input_data = optarg;
            }
            break;
        case '?':
            throw std::runtime_error("Function parse_arguments: The argument value is missing!");
            break;
        default:
            throw std::runtime_error("Function parse_arguments: There is no such operation!");
        }
    }

    Logger::instance().info("The argument parsing was successful");
}