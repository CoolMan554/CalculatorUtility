#include "math.h"

namespace library_math
{
    double sum(double num1, double num2)
    {
        return num1 + num2;
    }

    double minus(double num1, double num2)
    {
        return num1 - num2;
    }

    double multiplication(double num1, double num2)
    {
        return num1 * num2;
    }

    double division(double num1, double num2)
    {
        return num1 / num2;
    }

    int exponentiation(int num, int degree)
    {
        if(degree == 0)
            return 1;

        int res = num;     
        for(int i = 0; i < degree; i++)
        {
            res *= num;
        }
        return res;
    }

    int factorial(int num)
    {
        if(num == 0)
            return 1;

        return num * factorial(num - 1);
    }
}