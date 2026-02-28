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

    loadInCache();
}

void Application::run(int argc, char **argv) {

    cli_.parse_arguments(argc, argv);

    if (cli_.get_status_help()) {        
        return;
    }

    auto req = json_parser_.parse(cli_.get_input_data());

    check_.validate_input(req);

    if (findInCache(OperationKey::makeKey(req), req.result))
    {
        Printer::print(req);
    }
    else 
    {
        req.result = calc_.calculate(req);

        std::string opStr(1, req.operation);
        database_->insert(database_->TABLE_DATABASE, {"operation_type", "arg1", "arg2", "result"},
            {opStr, std::to_string(req.first_argument), std::to_string(req.second_argument), std::to_string(req.result)});
        
        addToCache(req, req.result);

        Printer::print(req);
    }
}

void Application::addToCache(const CalculationRequest& op, double result)
{
    cache_[OperationKey::makeKey(op)] = result;
}

bool Application::findInCache(const OperationKey& key, double& res)
{
    auto it = cache_.find(key);
    if (it != cache_.end())
    {
        res = it->second;
        return true;
    }

    return false;
}

void Application::loadInCache()
{
    std::vector<CalculationRequest> history;
    database_->select("operations", "operation_type, arg1, arg2, result", history);

    for (const auto& record : history)
    {
        cache_[OperationKey::makeKey(record)] = record.result;
    }
}