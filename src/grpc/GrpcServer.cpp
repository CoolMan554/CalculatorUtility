#include <grpcpp/grpcpp.h>
#include <iostream>
#include <signal.h>
#include <thread>

#include "calculator.grpc.pb.h"

#include "Application.h"
#include "CalculationRequest.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using calculator::CalcRequest;
using calculator::CalcResponse;
using calculator::CalculatorService;

class CalculatorServiceImpl final : public CalculatorService::Service {
  public:
    CalculatorServiceImpl() {
        app_.init();
    }

    Status Compute(ServerContext *context, const CalcRequest *request,
                   CalcResponse *response) override {
        try {
            CalculationRequest req;

            req.first_argument = request->arg1();
            req.second_argument = request->arg2();

            if (request->operation().size() != 1) {
                return Status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid operation");
            }

            req.operation = request->operation()[0];

            app_.processRequest(req);

            response->set_result(req.result);

            return Status::OK;
        } catch (const std::exception &e) {
            return Status(grpc::StatusCode::INTERNAL, e.what());
        }
    }

  private:
    Application app_;
};

void signalInit() {
    sigset_t set;
    sigemptyset(&set);

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);

    pthread_sigmask(SIG_BLOCK, &set, nullptr);
}

void signalHandler(grpc::Server *server) {
    sigset_t set;
    sigemptyset(&set);

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);

    int sig;
    sigwait(&set, &sig);

    server->Shutdown();
}

void RunServer() {
    std::string address = "0.0.0.0:" + std::to_string(GRPC_SERVER_PORT);

    CalculatorServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    auto serverRun = builder.BuildAndStart();

    if (serverRun) {
        std::unique_ptr<Server> server(std::move(serverRun));

        std::thread sigThread(signalHandler, server.get());

        std::cout << "Server started on " << address << "\n";

        server->Wait();

        sigThread.join();
    } else {
        throw std::runtime_error("The server is not running");
    }
}

int main() {
    try {
        signalInit();
        RunServer();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << "\n";
    }
}