#include "gtest/gtest.h"

#include "GrpcClient.h"

class GrpcClientTest : public testing::Test {
protected:
    void SetUp() override {
        ASSERT_TRUE(waitForServer());
    }

    bool waitForServer()
    {
        auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

        auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(3);

        return channel->WaitForConnected(deadline);
    }
};

TEST_F(GrpcClientTest, Addition) {
    CalculatorClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    double result = client.Compute(10, "+", 20);
    EXPECT_EQ(30, result);
}

TEST_F(GrpcClientTest, Subtraction) {
    CalculatorClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    double result = client.Compute(10, "-", 10);
    EXPECT_EQ(0, result);
}

TEST_F(GrpcClientTest, Division) {
    CalculatorClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    double result = client.Compute(10, "/", 10);
    EXPECT_EQ(1, result);
}

TEST_F(GrpcClientTest, Multiplication) {
    CalculatorClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    double result = client.Compute(10, "*", 10);
    EXPECT_EQ(100, result);
}

TEST_F(GrpcClientTest, Exponentiation) {
    CalculatorClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    double result = client.Compute(5, "^", 5);
    EXPECT_EQ(15625, result);
}

TEST_F(GrpcClientTest, Factorial) {
    CalculatorClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    double result = client.Compute(5, "!");
    EXPECT_EQ(120, result);
}

TEST_F(GrpcClientTest, Operation_Error_Throw) {
    CalculatorClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    EXPECT_THROW(client.Compute(5, "$", 5), std::runtime_error);
}