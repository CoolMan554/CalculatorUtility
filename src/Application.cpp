#include "Application.h"
#include "CliParser.h"
#include "JsonInputParser.h"
#include "Checker.h"
#include "Calculator.h"
#include "Printer.h"

void Application::run(int argc, char** argv) {
    CliParser cli;

    cli.parse_arguments(argc, argv);

    if (cli.get_status_help()) {
        Printer::print_help(argv[0]);
        return;
    }

    JsonInputParser json_parser;
    const auto req = json_parser.parse(cli.get_input_data());

    Checker check;
    check.validate_input(req);

    Calculator calc;
    auto result = calc.calculate(req);

    Printer::print(result);
}