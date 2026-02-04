#include "CalculatorManager.h"

int main(int argc, char **argv) 
{
    try
    {
        CalculatorManager info;
        info.runner(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}