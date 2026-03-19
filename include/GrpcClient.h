#pragma once

#include "calculator.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>

using calculator::CalcRequest;
using calculator::CalcResponse;
using calculator::CalculatorService;

class CalculatorClient {
  public:
    explicit CalculatorClient(std::shared_ptr<grpc::Channel> channel);
    double Compute(double arg1, const std::string &op, double arg2 = 0.0);

  private:
    std::unique_ptr<CalculatorService::Stub> stub_;
};