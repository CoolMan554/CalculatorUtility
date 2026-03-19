#include "gtest/gtest.h"

#include "Checker.h"

TEST(Checker, Check_Result_No_Throw) {
    Checker check;
    EXPECT_NO_THROW(check.validate_input({10, '+', 20}));
}

TEST(Checker, Check_Devided_By_Zero_Throw) {
    Checker check;
    EXPECT_FALSE(check.validate_input({10, '/', 0}));
}