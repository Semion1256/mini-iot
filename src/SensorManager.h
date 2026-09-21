#pragma once
#include <vector>
#include "Sensor.h"
class SensorManager
{
public:
    SensorManager();
    SensorManager(const Sensor& sensor);
    SensorManager(const std::vector<Sensor>&  sensors);
    void addSensor(const Sensor& sensor);
    const std::vector<Sensor>& getSensors() const;
private:
    std::vector<Sensor> m_sensors;
};