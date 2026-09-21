#include "SensorManager.h"
#include "Sensor.h"

SensorManager::SensorManager(){

}

SensorManager::SensorManager(const Sensor& sensor){
    m_sensors.push_back(sensor);
}

SensorManager::SensorManager(const std::vector<Sensor>&  sensors):m_sensors(sensors){
    
}
void SensorManager::addSensor(const Sensor& sensor){
    m_sensors.push_back(sensor);
}

const std::vector<Sensor>& SensorManager::getSensors() const{
    return m_sensors;
}