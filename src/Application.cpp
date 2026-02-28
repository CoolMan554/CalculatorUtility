#include "Application.h"
#include "Calculator.h"
#include "Checker.h"
#include "CliParser.h"
#include "JsonInputParser.h"
#include "PostgreSqlDB.h"
#include "Printer.h"

void Application::init() {
    database_ =
        std::make_unique<PostgreSqlDB>("localhost", 5432, "postgres", "909671Dima", "test1");

    database_->initializeSchema();

    cache_m.loadInCache(database_);
}

void Application::run(int argc, char **argv) {

    cli_.parse_arguments(argc, argv);

    if (cli_.get_status_help()) {
        return;
    }

    auto req = json_parser_.parse(cli_.get_input_data());

    check_.validate_input(req);

    if (cache_m.findInCache(req, req.result)) {
        Printer::print(req);
    } else {
        req.result = calc_.calculate(req);

        std::string opStr(1, req.operation);
        database_->insert(database_->TABLE_DATABASE, {"operation_type", "arg1", "arg2", "result"},
                          {opStr, std::to_string(req.first_argument),
                           std::to_string(req.second_argument), std::to_string(req.result)});

        cache_m.addToCache(req, req.result);

        Printer::print(req);
    }
}