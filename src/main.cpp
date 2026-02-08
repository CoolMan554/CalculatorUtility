#include "CalculatorManager.h"
#include "Logger.h"

int main(int argc, char **argv) 
{
    try
    {
        CalculatorManager info;
        info.runner(argc, argv);
    }
    catch(const std::exception& ex)
    {
        Logger::instance().critical(ex.what());
        std::cout << ex.what() << "\n";
    }
}