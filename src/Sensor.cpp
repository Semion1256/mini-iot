#include "Sensor.h"
#include "Measurement.h"
#include <random>
#include <iostream>

Sensor::Sensor(int id):m_id(id){
    
}

int Sensor::id() const{
    return m_id;
}

Measurement Sensor::read() const{
    int sensId = id();
    double temp = getRandomNumber();
    double humidity = getRandomNumber();
    auto now = std::chrono::system_clock::now();
    Measurement measurement {
        sensorId:sensId,
        temperature:temp,
        humidity:humidity,
        timestamp:now


    };
    return measurement;

    
}

double Sensor::getRandomNumber() const{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(1.0, 40.0);

    return dist(gen);
}