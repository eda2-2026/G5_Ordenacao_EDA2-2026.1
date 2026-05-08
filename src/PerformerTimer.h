#pragma once
#include <chrono>
 
class PerformerTimer {
public:
 
    void start() {
        _inicio = std::chrono::high_resolution_clock::now();
    }
 
    void stop() {
        _fim = std::chrono::high_resolution_clock::now();
    }
 
    double get_time_ms() {
        return std::chrono::duration<double, std::milli>(_fim - _inicio).count();
    }
 
private:
    std::chrono::high_resolution_clock::time_point _inicio;
    std::chrono::high_resolution_clock::time_point _fim;
};
