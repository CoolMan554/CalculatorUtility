#include "gtest/gtest.h"

#include "CalculatorManager.h"
#include <vector>

class CalculatorManagerTest : public testing::Test {
  protected:
    CalculatorManager calc;
    std::string parametr{"--in"};

    void run(const std::string &json_str) {
        std::vector<std::string> args = {"progName", parametr, json_str};

        std::vector<char *> argv;
        argv.reserve(args.size());

        for (auto &arg : args) {
            argv.emplace_back(arg.data());
        }

        calc.run(static_cast<int>(argv.size()), argv.data());
    }
};

TEST_F(CalculatorManagerTest, Addition_Operation) {
    run(R"({ "arg1": 10, "operation": "+", "arg2": 10 })");
    EXPECT_EQ(20, calc.result());
}

TEST_F(CalculatorManagerTest, Subtraction_Operation) {
    run(R"({ "arg1": 10, "operation": "-", "arg2": 10 })");
    EXPECT_EQ(0, calc.result());
}

TEST_F(CalculatorManagerTest, Division_Operation) {
    run(R"({ "arg1": 10, "operation": "/", "arg2": 10 })");
    EXPECT_EQ(1, calc.result());
}

TEST_F(CalculatorManagerTest, Multiplication_Operation) {
    run(R"({ "arg1": 10, "operation": "*", "arg2": 10 })");
    EXPECT_EQ(100, calc.result());
}

TEST_F(CalculatorManagerTest, Exponentiation_Operation) {
    run(R"({ "arg1": 5, "operation": "^", "arg2": 5 })");
    EXPECT_EQ(15625, calc.result());
}

TEST_F(CalculatorManagerTest, Factorial_Operation) {
    run(R"({ "arg1": 5, "operation": "!" })");
    EXPECT_EQ(120, calc.result());
}

TEST_F(CalculatorManagerTest, Print_Help) {
    parametr = {"--help"};
    run("");
    EXPECT_EQ(true, calc.get_help_check());
}

TEST_F(CalculatorManagerTest, NoInput_JSON_Throw) {
    parametr = {""};
    EXPECT_THROW(run(""), std::runtime_error);
}

TEST_F(CalculatorManagerTest, Operation_Value_Missing_Throw) {
    EXPECT_THROW(run(R"({ "arg1": 5, "operation": "#" })"), std::runtime_error);
}

TEST_F(CalculatorManagerTest, No_Such_Operation_Throw) {
    parametr = {"--out"};
    EXPECT_THROW(run(R"({ "arg1": 5, "operation": "!" })"), std::runtime_error);
}

TEST_F(CalculatorManagerTest, No_Arg1_Throw) {
    EXPECT_THROW(run(R"({ "operation": "!" })"), std::runtime_error);
}

TEST_F(CalculatorManagerTest, No_Operation_Throw) {
    EXPECT_THROW(run(R"({" arg1": 10, "arg2": 10 })"), std::runtime_error);
}

TEST_F(CalculatorManagerTest, No_Arg2_Throw) {
    EXPECT_THROW(run(R"({" arg1": 10, "operation": "!" })"), std::runtime_error);
}

TEST_F(CalculatorManagerTest, Divide_By_Zero_Throw) {
    EXPECT_THROW(run(R"({" arg1": 10, "operation": "/", "arg2": 0 })"), std::runtime_error);
}

TEST_F(CalculatorManagerTest, Error_JSON_Parse_Throw) {
    EXPECT_THROW(run(R"({" arg1": 10, "operation:"/", "arg2: 0 })"), std::exception);
}