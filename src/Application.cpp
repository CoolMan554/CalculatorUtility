#include "Application.h"
#include "Calculator.h"
#include "Checker.h"
#include "CliParser.h"
#include "JsonInputParser.h"
#include "Printer.h"
#include "PostgreSqlDB.h"

void Application::init()
{
    database_ = std::make_unique<PostgreSqlDB>("localhost", 5432, "postgres", "909671Dima", "test1");

    database_->initializeSchema();
}

void Application::run(int argc, char **argv) {

    cli_.parse_arguments(argc, argv);

    if (cli_.get_status_help()) {        
        return;
    }

    auto req = json_parser_.parse(cli_.get_input_data());

    check_.validate_input(req);

    req.result = calc_.calculate(req);

    Printer::print(req);
}