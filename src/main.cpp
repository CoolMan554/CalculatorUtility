#include "CalculatorManager.h"

int main(int argc, char **argv) 
{
    try
    {
        CalculatorManager info;
        info.runner(argc, argv);
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << '\n';
    }
}