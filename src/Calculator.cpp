#include "Calculator.h"
#include "Logger.h"
#include "library_math.h"

double Calculator::calculate(const CalculationRequest &req) const {

    double result{0.0};

    switch (req.operation[0]) {
    case '+':
        result = Library_Math::sum(req.first_argument, req.second_argument);
        break;
    case '-':
        result = Library_Math::minus(req.first_argument, req.second_argument);
        break;
    case '*':
        result = Library_Math::multiplication(req.first_argument, req.second_argument);
        break;
    case '/':
        result = Library_Math::division(req.first_argument, req.second_argument);
        break;
    case '^':
        result = Library_Math::exponentiation(req.first_argument, req.second_argument);
        break;
    case '!':
        result = Library_Math::factorial(static_cast<int>(req.first_argument));
        break;
    default:
        throw std::runtime_error(
            "Function calculate: There is no such operation. Select another operation!");
    }

    Logger::instance().info("The calculation was successful");

    return result;
}