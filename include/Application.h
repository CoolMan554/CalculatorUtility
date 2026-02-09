#pragma once

class Application {
public:
    Application() = default;
    ~Application() = default;
    void run(int argc, char** argv);
    double get_result const {
        return save_result;
    }
    bool get_result const {
        return save_result;
    }
private:
    double save_result{0.0};
};