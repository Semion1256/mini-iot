#include "Logger.h"
#include "Measurement.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
Logger::Logger()
{
}

Logger::~Logger()
{
    if (m_file.is_open()){
        m_file.close();
    }
}

void Logger::log(const Measurement& measurement){
    std::chrono::system_clock::time_point timestamp = measurement.timestamp;
    std::time_t now = std::chrono::system_clock::to_time_t(timestamp);
    std::tm* localTime = std::localtime(&now);
    m_file.open("measurements.log", std::ios::app);
    if (!m_file.is_open()){
        std::cerr<<"не удалось открыть файл";
    }
    m_file<<"Sensor: "<<measurement.sensorId<<" Temperature: "<<measurement.temperature<<
        " Humidity: "<<measurement.humidity<<" Created: "<<std::put_time(localTime, "%H:%M:%S");
}