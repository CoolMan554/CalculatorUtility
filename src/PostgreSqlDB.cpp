#include "PostgreSqlDB.h"
#include "Logger.h"

#include <stdexcept>

PostgreSqlDB::PostgreSqlDB(const std::string& server,
        int                port,
        const std::string& user,
        const std::string& password,
        const std::string& database) : server_(server), port_(port), user_(user), password_(password), database_(database)
{

    if (port_ == 0)
        port_ = 5432;

    std::string params = "host=" + server_
                       + " port=" + std::to_string(port)
                       + " user=" + user
                       + " password=" + password
                       + " dbname=" + database;

    connection_ = PQconnectdb(params.c_str());

    if (PQstatus(connection_) != CONNECTION_OK)
    {
        std::string error_msg = PQerrorMessage(connection_);
        throw std::runtime_error("Connection to database failed: " + error_msg);
    }
}

PostgreSqlDB::~PostgreSqlDB()
{
    PQfinish(connection_);
}

bool PostgreSqlDB::exec(const std::string& query)
{
    PGresult* res = PQexec(connection_, query.c_str());

    if (PQstatus(connection_) == CONNECTION_BAD)
    {
        PQreset(connection_);

        if (PQstatus(connection_) == CONNECTION_BAD )
        {
            PQclear(res);
            throw std::runtime_error("Lost connection to DB, unable to reconnect");            
        }
        else
        {
            Logger::instance().info("Succesfully reconnected to DB");

            // Re-execute the query
            PQclear(res);
            res = PQexec(connection_, query.c_str());
        }
    }

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        std::string error_msg = PQerrorMessage(connection_);
        Logger::instance().error("Command failed: " + error_msg);
        PQclear(res);
        return false;
    }

    PQclear(res);
    return true;
}

void PostgreSqlDB::initializeSchema()
{
    std::string query {"CREATE TABLE IF NOT EXISTS operations ("
        "id SERIAL PRIMARY KEY, "
        "operation_type VARCHAR(10) NOT NULL, "
        "arg1 DOUBLE PRECISION NOT NULL, "
        "arg2 DOUBLE PRECISION, "
        "result DOUBLE PRECISION NOT NULL, "
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ");"};

    if (!exec(query))
    {
        throw std::runtime_error("Schema initialization failed");
    }
}
