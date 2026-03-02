#pragma once

#include <string>

struct DBConfig{
    DBConfig(const std::string& path);

    std::string getHost() const{
        return host;
    }

    int getPort() const{
        return port;
    }

    std::string getUser() const{
        return user;
    }

    std::string getPassword() const{
        return password;
    }

    std::string getDBName() const{
        return dbname;
    }
    
private:
    std::string host;    
    int port = 0;
    std::string user;
    std::string password;
    std::string dbname;
};