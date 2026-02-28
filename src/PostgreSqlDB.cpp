#include "PostgreSqlDB.h"
#include "Logger.h"

#include <stdexcept>

PostgreSqlDB::PostgreSqlDB(const std::string &server, int port, const std::string &user,
                           const std::string &password, const std::string &database)
    : server_(server), port_(port), user_(user), password_(password), database_(database) {

    if (port_ == 0)
        port_ = 5432;

    std::string params = "host=" + server_ + " port=" + std::to_string(port) + " user=" + user +
                         " password=" + password + " dbname=" + database;

    connection_ = PQconnectdb(params.c_str());

    if (PQstatus(connection_) != CONNECTION_OK) {
        std::string error_msg = PQerrorMessage(connection_);
        throw std::runtime_error("Connection to database failed: " + error_msg);
    }
}

PostgreSqlDB::~PostgreSqlDB() {
    PQfinish(connection_);
}

PGresult *PostgreSqlDB::executeQuery(PGconn *conn, const std::string &query) {
    return PQexec(conn, query.c_str());
}

PGresult *PostgreSqlDB::executeQueryParams(PGconn *conn, const std::string &query,
                                           const std::vector<std::string> &values) {
    std::vector<const char *> c_values;
    c_values.reserve(values.size());

    for (const auto &value : values)
        c_values.emplace_back(value.c_str());

    return PQexecParams(conn, query.c_str(), values.size(), nullptr, c_values.data(), nullptr,
                        nullptr, 0);
}

bool PostgreSqlDB::isConnectionBad(PGconn *conn) {
    return PQstatus(conn) == CONNECTION_BAD;
}

void PostgreSqlDB::tryReconnect(PGconn *conn) {
    PQreset(conn);
}

bool PostgreSqlDB::checkAndHandleReconnect(PGconn *conn, PGresult *&res,
                                           const std::function<PGresult *()> &executor) {
    if (!isConnectionBad(conn))
        return true;

    tryReconnect(conn);

    if (isConnectionBad(conn)) {
        PQclear(res);
        throw std::runtime_error("Lost connection to DB, unable to reconnect");
    }

    Logger::instance().info("Succesfully reconnected to DB");

    PQclear(res);
    res = executor();

    return true;
}

bool PostgreSqlDB::checkCommandResult(PGconn *conn, PGresult *res) {
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::string error_msg = PQerrorMessage(conn);
        Logger::instance().error("Command failed: " + error_msg);
        return false;
    }

    return true;
}

bool PostgreSqlDB::checkSelectResult(PGconn *conn, PGresult *res) {
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::string error_msg = PQerrorMessage(conn);
        Logger::instance().error("Command failed: " + error_msg);
        return false;
    }

    return true;
}

bool PostgreSqlDB::exec(const std::string &query) {
    PGresult *res = executeQuery(connection_, query);

    checkAndHandleReconnect(connection_, res, [&]() { return executeQuery(connection_, query); });

    if (!checkCommandResult(connection_, res)) {
        PQclear(res);
        return false;
    }

    PQclear(res);
    return true;
}

bool PostgreSqlDB::exec_params(const std::string &query, const std::vector<std::string> &values) {
    std::vector<const char *> c_values;
    for (const auto &value : values)
        c_values.push_back(value.c_str());

    PGresult *res = executeQueryParams(connection_, query, values);

    checkAndHandleReconnect(connection_, res, [&]() { return executeQuery(connection_, query); });

    if (!checkCommandResult(connection_, res)) {
        PQclear(res);
        return false;
    }

    PQclear(res);
    return true;
}

std::vector<CalculationRequest> PostgreSqlDB::exec_sel(const std::string &query) {
    std::vector<CalculationRequest> records;

    PGresult *res = executeQuery(connection_, query);

    checkAndHandleReconnect(connection_, res, [&]() { return executeQuery(connection_, query); });

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::string error_msg = PQerrorMessage(connection_);
        Logger::instance().error("Command failed: " + error_msg);
        PQclear(res);
        return records;
    }

    if (!checkSelectResult(connection_, res)) {
        PQclear(res);
        return records;
    }

    int rows = PQntuples(res);

    for (int i = 0; i < rows; ++i) {
        CalculationRequest req;

        req.operation = PQgetvalue(res, i, 0)[0];
        req.first_argument = std::stod(PQgetvalue(res, i, 1));
        req.second_argument = std::stod(PQgetvalue(res, i, 2));
        req.result = std::stod(PQgetvalue(res, i, 3));

        records.emplace_back(req);
    }

    PQclear(res);

    return records;
}

void PostgreSqlDB::initializeSchema() {
    std::string query{"CREATE TABLE IF NOT EXISTS operations ("
                      "id SERIAL PRIMARY KEY, "
                      "operation_type CHAR(1) NOT NULL, "
                      "arg1 DOUBLE PRECISION NOT NULL, "
                      "arg2 DOUBLE PRECISION, "
                      "result DOUBLE PRECISION NOT NULL, "
                      "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
                      ");"};

    if (!exec(query)) {
        throw std::runtime_error("Schema initialization failed");
    }
}

void PostgreSqlDB::insert(const std::string &table, const std::vector<std::string> &columns,
                          const std::vector<std::string> &values) {
    std::string query = "INSERT INTO " + table + " (" + join(columns, ",") + ") VALUES (" +
                        buildPlaceholders(values.size()) + ")";

    if (!exec_params(query, values)) {
        throw std::runtime_error("Insert data");
    }
}

void PostgreSqlDB::select(const std::string &table, const std::string &columns,
                          std::vector<CalculationRequest> &res) {
    std::string query = "SELECT " + columns + " FROM " + table + ";";

    res = exec_sel(query);
}

std::string PostgreSqlDB::buildPlaceholders(std::size_t count) {
    std::string result;
    for (size_t i = 0; i < count; ++i) {
        result += "$" + std::to_string(i + 1);
        if (i != count - 1)
            result += ", ";
    }
    return result;
}
std::string PostgreSqlDB::join(const std::vector<std::string> &items, const std::string delimiter) {
    std::string result;
    for (size_t i = 0; i < items.size(); ++i) {
        result += items[i];
        if (i != items.size() - 1)
            result += delimiter;
    }
    return result;
}
