#include "gtest/gtest.h"

#include "CliParser.h"

class CliParserTest : public testing::Test {
  protected:
    CliParser cliParser;
    std::string parametr{"--in"};

    void run(const std::string &json_str) {
        std::vector<std::string> args = {"progName", parametr, json_str};

        std::vector<char *> argv;
        argv.reserve(args.size());

        for (auto &arg : args) {
            argv.emplace_back(arg.data());
        }

        cliParser.parse_arguments(static_cast<int>(argv.size()), argv.data());
    }
};

TEST_F(CliParserTest, Parses_In_Option) {
    run(R"({ "arg1": 10, "operation": "+", "arg2": 10 })");
    EXPECT_EQ(cliParser.get_input_data(), R"({ "arg1": 10, "operation": "+", "arg2": 10 })");
}

TEST_F(CliParserTest, Parses_In_Option_Help) {
    parametr = "--help";
    run("");
    EXPECT_EQ(cliParser.get_status_help(), true);
}

TEST_F(CliParserTest, Parses_Without_An_Argument) {
    parametr = "--out";
    EXPECT_THROW(run(R"({ "arg1": 10, "operation": "+", "arg2": 10 })"), std::runtime_error);
}
