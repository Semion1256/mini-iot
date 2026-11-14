#include "MeasurementPrinter.h"
#include "Measurement.h"
#include <iostream>
#include <iomanip>
#include <ctime>
void MeasurementPrinter::printMeasurement(const Measurement& measurement) const{
    std::chrono::system_clock::time_point timestamp = measurement.timestamp;
    std::time_t now = std::chrono::system_clock::to_time_t(timestamp);
    std::tm* localTime = std::localtime(&now);

    std::cout<<"Sensor: "<<measurement.sensorId
    <<"\n Temperature: "<<measurement.temperature
    <<"\n Humidity: "<<measurement.humidity
    <<"\n Created: "<<std::put_time(localTime, "%H:%M:%S")<<std::endl;
}