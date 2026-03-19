#include "Application.h"
#include "Calculator.h"
#include "Checker.h"
#include "CliParser.h"
#include "DBConfig.h"
#include "JsonInputParser.h"
#include "PostgreSqlDB.h"
#include "Printer.h"

#include <signal.h>

void Application::init() {

    DBConfig conf(DBConfig::findConfig());

    database_ = std::make_unique<PostgreSqlDB>(conf);

    database_->initializeSchema();

    cache_m.loadInCache(database_);
}

void Application::run(int argc, char **argv) {

    while (running_) {
        cli_.parse_arguments(argc, argv);

        if (cli_.get_status_help()) {
            return;
        }

        auto req = json_parser_.parse(cli_.get_input_data());

        processRequest(req);
    }
}

void Application::signalLoop() {
    sigset_t set;
    sigemptyset(&set);

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);

    int sig;
    sigwait(&set, &sig);

    running_ = false;
}

void Application::processRequest(CalculationRequest &req) {
    if (cache_m.findInCache(req, req.result)) {
        check_.validate_input(req);
        Printer::print(req);
    } else {
        std::string opStr(1, req.operation);

        if (!check_.validate_input(req)) {
            database_->insert(database_->TABLE_DATABASE,
                              {"operation_type", "arg1", "arg2", "result"},
                              {opStr, std::to_string(req.first_argument),
                               std::to_string(req.second_argument), std::to_string(req.result)});

            cache_m.addToCache(req, 0.0);

            throw std::runtime_error("Function validate_input: You can't divided by zero!");
        }

        req.result = calc_.calculate(req);

        database_->insert(database_->TABLE_DATABASE, {"operation_type", "arg1", "arg2", "result"},
                          {opStr, std::to_string(req.first_argument),
                           std::to_string(req.second_argument), std::to_string(req.result)});

        cache_m.addToCache(req, req.result);

        Printer::print(req);
    }
}