#include "Application.h"
#include "Logger.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char **argv) {
    try {
        Application app;
        app.run(argc, argv);
    } catch (const json::parse_error &e) {
        std::ostringstream error_msg;
        error_msg << "JSON parsing Error: " << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n'
                  << "byte position of error: " << e.byte << "\n";

        Logger::instance().critical(error_msg.str());
        std::cerr << error_msg.str() << "\n";
    } catch (const std::exception &ex) {
        Logger::instance().critical(ex.what());
        std::cerr << ex.what() << "\n";
    }
}