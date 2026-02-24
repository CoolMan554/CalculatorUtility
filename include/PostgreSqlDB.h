#pragma once

#include "IDatabase.h"
#include <string>
#include <libpq-fe.h>

class PostgreSqlDB : public IDatabase
{
public:
    PostgreSqlDB(
        const std::string& _server,
        int                _port,
        const std::string& _user,
        const std::string& _password,
        const std::string& _database);
    
    ~PostgreSqlDB();

    bool exec(const std::string& query) override;
    void initializeSchema() override;
private:
    std::string server_;
    int         port_;
    std::string user_;
    std::string password_;
    std::string database_;

    PGconn *connection_;

};