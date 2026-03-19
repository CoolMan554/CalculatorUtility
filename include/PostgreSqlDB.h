#pragma once

#include "CalculationRequest.h"
#include "DBConfig.h"
#include "IDatabase.h"

#include <functional>
#include <libpq-fe.h>
#include <memory>
#include <string>

using PGconnPtr = std::unique_ptr<PGconn, decltype(&PQfinish)>;

class PostgreSqlDB : public IDatabase {
  public:
    PostgreSqlDB(const DBConfig &cfg);
    ~PostgreSqlDB() = default;

    PostgreSqlDB(const PostgreSqlDB &) = default;
    PostgreSqlDB &operator=(const PostgreSqlDB &) = default;

    PostgreSqlDB(PostgreSqlDB &&) noexcept = default;
    PostgreSqlDB &operator=(PostgreSqlDB &&) noexcept = default;

    bool exec(const std::string &query) override;
    bool exec_params(const std::string &query, const std::vector<std::string> &values) override;
    std::vector<CalculationRequest> exec_sel(const std::string &query);

    void initializeSchema() override;

    void insert(const std::string &table, const std::vector<std::string> &columns,
                const std::vector<std::string> &values) override;
    void select(const std::string &table, const std::string &columns,
                std::vector<CalculationRequest> &res) override;

    std::string buildPlaceholders(std::size_t count);
    std::string join(const std::vector<std::string> &items, const std::string delimiter);

  private:
    std::string server_;
    int port_;
    std::string user_;
    std::string password_;
    std::string database_;
    std::string params_;

    PGconnPtr connection_;
    PGresult *executeQuery(PGconn *conn, const std::string &query);
    PGresult *executeQueryParams(PGconn *conn, const std::string &query,
                                 const std::vector<std::string> &values);
    bool isConnectionBad(PGconn *conn);
    void tryReconnect(PGconn *conn);
    bool checkAndHandleReconnect(PGconn *conn, PGresult *res,
                                 const std::function<PGresult *()> &executor);
    bool checkCommandResult(PGconn *conn, PGresult *res);
    bool checkSelectResult(PGconn *conn, PGresult *res);
};