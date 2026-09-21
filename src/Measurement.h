#include <chrono>
struct Measurement
{
    int sensorId;
    double temperature;
    double humidity;
    std::chrono::system_clock::time_point timestamp;
};