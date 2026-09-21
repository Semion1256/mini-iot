#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
#include "Sensor.h"
#include "Measurement.h"
#include "SensorManager.h"
#include "Logger.h"
int main(){
   
    Sensor sens1(1);
    Sensor sens2(2);
    Sensor sens3(3);
    Sensor sens4(4);
    std::vector<Sensor> sensors = {sens1, sens2, sens3, sens4};
    SensorManager manager(sensors);
    Sensor sens5(5);
    manager.addSensor(sens5);
    Logger logger;
    const std::vector<Sensor>& sensorsGet= manager.getSensors();
    for (int i = 0; i<sensorsGet.size(); ++i){
        Measurement measurement = sensorsGet[i].read();
        logger.log(measurement);

        std::chrono::system_clock::time_point timestamp = measurement.timestamp;
        std::time_t now = std::chrono::system_clock::to_time_t(timestamp);
        std::tm* localTime = std::localtime(&now);

        std::cout<<"Sensor: "<<measurement.sensorId
        <<"\n Temperature: "<<measurement.temperature
        <<"\n Humidity: "<<measurement.humidity
        <<"\n Created: "<<std::put_time(localTime, "%H:%M:%S")<<std::endl;
    }
}