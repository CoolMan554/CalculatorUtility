#include "GrpcClient.h"

#include "Printer.h"


CalculatorClient::CalculatorClient(std::shared_ptr<grpc::Channel> channel) : stub_(CalculatorService::NewStub(channel)) 
{

}

double CalculatorClient::Compute(const double arg1, const std::string& operation, const double arg2) {
    CalcRequest req;
    req.set_arg1(arg1);
    req.set_arg2(arg2);
    req.set_operation(operation);

    CalcResponse res;
    grpc::ClientContext context;

    auto status = stub_->Compute(&context, req, &res);

    if (!status.ok()) {
        throw std::runtime_error(status.error_message());
    }

    return res.result();
}