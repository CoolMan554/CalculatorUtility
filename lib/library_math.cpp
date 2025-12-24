#include "math.h"

namespace library_math {
double sum(double num1, double num2) {
    return num1 + num2;
}

double minus(double num1, double num2) {
    return num1 - num2;
}

double multiplication(double num1, double num2) {
    return num1 * num2;
}

double division(double num1, double num2) {
    return num1 / num2;
}

double exponentiation(double num, double degree) {
    if (degree == 0)
        return 1;

    double res = num;
    for (int i = 0; i < degree; i++) {
        res *= num;
    }
    return res;
}

double factorial(double num) {
    if (num == 0)
        return 1;

    return num * factorial(num - 1);
}
} // namespace library_math