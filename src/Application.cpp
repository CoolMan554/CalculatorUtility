#include "Application.h"
#include "Calculator.h"
#include "Checker.h"
#include "CliParser.h"
#include "JsonInputParser.h"
#include "PostgreSqlDB.h"
#include "Printer.h"
#include "DBConfig.h"

void Application::init() {

    DBConfig conf("config/config_db.json");

    database_ = std::make_unique<PostgreSqlDB>(conf);

    database_->initializeSchema();

    cache_m.loadInCache(database_);
}

void Application::run(int argc, char **argv) {

    cli_.parse_arguments(argc, argv);

    if (cli_.get_status_help()) {
        return;
    }

    auto req = json_parser_.parse(cli_.get_input_data());

    if (cache_m.findInCache(req, req.result)) {
        check_.validate_input(req);
        Printer::print(req);
    } else {
        std::string opStr(1, req.operation);

        database_->insert(database_->TABLE_DATABASE, {"operation_type", "arg1", "arg2", "result"},
                          {opStr, std::to_string(req.first_argument),
                           std::to_string(req.second_argument), std::to_string(req.result)});

        check_.validate_input(req);

        req.result = calc_.calculate(req);

        cache_m.addToCache(req, req.result);

        Printer::print(req);
    }
}