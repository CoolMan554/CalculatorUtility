#include "gtest/gtest.h"

#include "Application.h"
#include <vector>

class ApplicationTest : public testing::Test {
  protected:
    Application app;
    std::string parametr{"--in"};

    void run(const std::string &json_str) {
        std::vector<std::string> args = {"progName", parametr, json_str};

        std::vector<char *> argv;
        argv.reserve(args.size());

        for (auto &arg : args) {
            argv.emplace_back(arg.data());
        }

        app.run(static_cast<int>(argv.size()), argv.data());
    }
};

TEST_F(ApplicationTest, Addition_Operation) {
    run(R"({ "arg1": 10, "operation": "+", "arg2": 10 })");
    EXPECT_EQ(20, calc.result());
}

TEST_F(ApplicationTest, Subtraction_Operation) {
    run(R"({ "arg1": 10, "operation": "-", "arg2": 10 })");
    EXPECT_EQ(0, calc.result());
}

TEST_F(ApplicationTest, Division_Operation) {
    run(R"({ "arg1": 10, "operation": "/", "arg2": 10 })");
    EXPECT_EQ(1, calc.result());
}

TEST_F(ApplicationTest, Multiplication_Operation) {
    run(R"({ "arg1": 10, "operation": "*", "arg2": 10 })");
    EXPECT_EQ(100, calc.result());
}

TEST_F(ApplicationTest, Exponentiation_Operation) {
    run(R"({ "arg1": 5, "operation": "^", "arg2": 5 })");
    EXPECT_EQ(15625, calc.result());
}

TEST_F(ApplicationTest, Factorial_Operation) {
    run(R"({ "arg1": 5, "operation": "!" })");
    EXPECT_EQ(120, calc.result());
}

TEST_F(ApplicationTest, Print_Help) {
    parametr = {"--help"};
    run("");
    EXPECT_EQ(true, calc.get_help_check());
}

TEST_F(ApplicationTest, NoInput_JSON_Throw) {
    parametr = {""};
    EXPECT_THROW(run(""), std::runtime_error);
}

TEST_F(ApplicationTest, Operation_Value_Missing_Throw) {
    EXPECT_THROW(run(R"({ "arg1": 5, "operation": "#" })"), std::runtime_error);
}

TEST_F(ApplicationTest, No_Such_Operation_Throw) {
    parametr = {"--out"};
    EXPECT_THROW(run(R"({ "arg1": 5, "operation": "!" })"), std::runtime_error);
}

TEST_F(ApplicationTest, No_Arg1_Throw) {
    EXPECT_THROW(run(R"({ "operation": "!" })"), std::runtime_error);
}

TEST_F(ApplicationTest, No_Operation_Throw) {
    EXPECT_THROW(run(R"({" arg1": 10, "arg2": 10 })"), std::runtime_error);
}

TEST_F(ApplicationTest, No_Arg2_Throw) {
    EXPECT_THROW(run(R"({" arg1": 10, "operation": "!" })"), std::runtime_error);
}

TEST_F(ApplicationTest, Divide_By_Zero_Throw) {
    EXPECT_THROW(run(R"({" arg1": 10, "operation": "/", "arg2": 0 })"), std::runtime_error);
}

TEST_F(ApplicationTest, Error_JSON_Parse_Throw) {
    EXPECT_THROW(run(R"({" arg1": 10, "operation:"/", "arg2: 0 })"), std::exception);
}