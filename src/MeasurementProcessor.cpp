#include "MeasurementProcessor.h"
#include "Measurement.h"


bool MeasurementProcessor::isValid(const Measurement& measurement) const{
    if (!isTemperatureValid(measurement.temperature) || !isHumidityValid(measurement.humidity)){
        return false;
    }
    return true;
}   
bool MeasurementProcessor::isTemperatureValid(double temperature) const{
    return temperature>=1 &&temperature<=40;
      
}   
bool MeasurementProcessor::isHumidityValid(double humidity) const{
    return humidity>=1 &&humidity<=40;
      
    
}   