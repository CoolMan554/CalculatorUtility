#include "gtest/gtest.h"

#include "Calculator.h"

TEST(Calculator, Addition_Operation) {
    Calculator calc;
    double result = calc.calculate({10, 20, '+'});
    EXPECT_EQ(30, result);
}

TEST(Calculator, Subtraction_Operation) {
    Calculator calc;
    double result = calc.calculate({10, 10, '-'});
    EXPECT_EQ(0, result);
}

TEST(Calculator, Division_Operation) {
    Calculator calc;
    double result = calc.calculate({10, 10, '/'});
    EXPECT_EQ(1, result);
}

TEST(Calculator, Multiplication_Operation) {
    Calculator calc;
    double result = calc.calculate({10, 10, '*'});
    EXPECT_EQ(100, result);
}

TEST(Calculator, Exponentiation_Operation) {
    Calculator calc;
    double result = calc.calculate({5, 5, '^'});
    EXPECT_EQ(15625, result);
}

TEST(Calculator, Factorial_Operation) {
    Calculator calc;
    double result = calc.calculate({5, 5, '!'});
    EXPECT_EQ(120, result);
}

TEST(Calculator, Operation_Error_Throw) {
    Calculator calc;
    EXPECT_THROW(calc.calculate({5, 5, '$'}), std::runtime_error);
}