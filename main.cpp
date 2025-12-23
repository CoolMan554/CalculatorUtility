#include <iostream>

int main()
{
    int number1 = 0, number2 = 0, operation = 0, result = 0;
    bool replay = false;
    std::cout << "Enter the first number: " << std::endl;
    std::cin >> number1;
    std::cout << "Enter the second number: " << std::endl;
    std::cin >> number2;

    while(replay)
    {
        std::cout << "Select an operation: \n0 - addition, \n1 - subtraction, \n2 - division, \n3 - multiplication" << std::endl;
        std::cin >> operation;

        if(operation == 2 && number2 == 0)
        {
            std::cout << "You can't divide by zero!" << std::endl;
            replay = true;
            continue;
        }

        switch(operation)
        {
            case 0:
                result = 0;
                replay = false;
            break;
            case 1:
                result = 0;
                replay = false;
            break;
            case 2:                
                result = 0;
                replay = false;
            break;
            case 3:
                result = 0;
            break;
            default:
                std::cout << "There is no such operation. Select another operation!" << std::endl;
                replay = true;
                continue;
        }
    }

    std::cout << "Result: " << result << std::endl;
}