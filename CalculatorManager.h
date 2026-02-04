#include <iostream>
#include <string>
#include <getopt.h>

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

    static void print_help(const char *progName) {
        cout << "Calculator CLI Utility — Help\n\n";
        cout << "Usage:\n";
        cout << "  " << progName << " -a20 -o/ -b30\n";
        cout << "  " << progName << " --arg1=20 --operation=/ --arg2=30\n";
        cout << "  " << progName << " --arg1=20 --operation=! \n";
        cout << "  " << progName << " --help | -h\n\n";

        cout << "Description:\n";
        cout << "  A simple command-line calculator that performs:\n";
        cout << "    +   addition\n";
        cout << "    -   subtraction\n";
        cout << "    *   multiplication\n";
        cout << "    /   division (checks for divide by zero)\n";
        cout << "    ^   power (iterative implementation)\n";
        cout << "    !   factorial (recursive implementation)\n\n";

        cout << "Examples:\n";
        cout << "  " << progName << " \t--arg1=3 \t--operation=+ \t--arg2=5       \t-> Result: 8\n";
        cout << "  " << progName << " \t--arg1=8 \t--operation=- \t--arg2=3       \t-> Result: 5\n";
        cout << "  " << progName << " \t--arg1=20 \t--operation=* \t--arg2=2      \t-> Result: 40\n";
        cout << "  " << progName << " \t--arg1=10 \t--operation=/ \t--arg2=2      \t-> Result: 5\n";
        cout << "  " << progName << " \t--arg1=2 \t--operation=^ \t--arg2=8       \t-> Result: 256\n";
        cout << "  " << progName << " \t--arg1=5 \t--operation=!                  \t-> Result: 120\n\n";

        cout << "Options:\n";
        cout << "  -h, --help    Show this help message and exit\n";
    }
private:
    std::string first_arg;
    std::string operation;
    std::string second_arg;
    bool help_check = false;
    double result = 0.0;
    
    static constexpr option long_opts[] = {
        {"help",      no_argument,       nullptr, 'h'},
        {"arg1",      required_argument, nullptr, 'a'},
        {"arg2",      optional_argument, nullptr, 'b'},
        {"operation", required_argument, nullptr, 'o'},
        {nullptr,     0,                 nullptr,  0}
    };
};