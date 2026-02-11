#include "gtest/gtest.h"

#include "JsonInputParser.h"

TEST(JsonInputParser, Json_Parsing_Is_Successful) {
    JsonInputParser jsP;
    auto req = jsP.parse(R"({ "arg1": 10, "operation": "+", "arg2": 10 })");
    EXPECT_EQ(10, req.first_argument);
    EXPECT_EQ(10, req.second_argument);
    EXPECT_EQ('+', req.operation);
}

TEST(JsonInputParser, No_Arg1_Throw) {
    JsonInputParser jsP;
    EXPECT_THROW(jsP.parse(R"({ "operation": "!" })"), std::runtime_error);
}

TEST(JsonInputParser, No_Operation_Throw) {
    JsonInputParser jsP;
    EXPECT_THROW(jsP.parse(R"({" arg1": 10, "arg2": 10 })"), std::runtime_error);
}

TEST(JsonInputParser, No_Arg2_Throw) {
    JsonInputParser jsP;
    EXPECT_THROW(jsP.parse(R"({" arg1": 10, "operation": "!" })"), std::runtime_error);
}

TEST(JsonInputParser, Error_JSON_Parse_Throw) {
    JsonInputParser jsP;
    EXPECT_THROW(jsP.parse(R"({" arg1": 10, "operation:"/", "arg2: 0 })"), std::exception);
}