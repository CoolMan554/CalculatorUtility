#include "Application.h"
#include "Logger.h"

int main(int argc, char **argv) {
    try {
        Application app;
        app.run(argc, argv);
    } catch (const std::exception &ex) {
        Logger::instance().critical(ex.what());
        std::cout << ex.what() << "\n";
    }
}