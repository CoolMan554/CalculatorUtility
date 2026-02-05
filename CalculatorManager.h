#include <iostream>
#include <string>
#include <getopt.h>

#include "nlohmann/json.hpp"

// for convenience
using json = nlohmann::json;

using namespace std;

class CalculatorManager
{
public:
    CalculatorManager();
    ~CalculatorManager() = default;
    void runner(int argc, char **argv);
    void parser(int argc, char **argv);
    void checker();
    void calculator();
    void printer() const;
    void print_help(const char *progName) const;
private:
    double first_arg = 0.0;
    std::string operation;
    double second_arg = 0.0;
    bool help_check = false;
    double result = 0.0;
    json j_parser;
    
    static constexpr option long_opts[] = {
        {"help",      no_argument,       nullptr, 'h'},        
        {"in",        required_argument, nullptr, 'i'},
    };
};