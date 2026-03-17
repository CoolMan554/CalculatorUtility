#include "Application.h"
#include "Logger.h"
#include "nlohmann/json.hpp"

#include <thread>
#include <signal.h>

using json = nlohmann::json;

void signalInit()
{
    sigset_t set;
    sigemptyset(&set);

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);

    pthread_sigmask(SIG_BLOCK, &set, nullptr);
}

int main(int argc, char **argv) {

    signalInit();

    try {
        Application app;

        app.init();

        std::thread signal_thread([&app](){
            try {
                app.signalLoop();
            }
            catch (const std::exception &ex){
                std::cerr << ex.what() << "\n";
            }
        });
        
        std::thread worker_thread([&](){
            try{
                app.run(argc, argv);
            }
            catch (const json::parse_error &e) {
                std::ostringstream error_msg;
                error_msg << "JSON parsing Error: " << "message: " << e.what() << '\n'
                        << "exception id: " << e.id << '\n'
                        << "byte position of error: " << e.byte << "\n";

                std::cerr << error_msg.str() << "\n";
            } 
            catch (const std::exception &ex) {
                std::cerr << ex.what() << "\n";
            }
        });

        signal_thread.join();
        worker_thread.join();
    
    }
    catch (const std::exception &ex) {
        std::cerr << ex.what() << "\n";
    }
}