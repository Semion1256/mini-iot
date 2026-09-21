#include <iostream>
#include <ctime>
#include <iomanip>
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
    const std::vector<Sensor>& sensorsGet= manager.getSensors();
    for (int i = 0; i<sensorsGet.size(); ++i){
        Measurement meas1 = sensorsGet[i].read();
        Logger logger;
        logger.log(meas1);
        
        
    }
    
    
    
    

    

    // std::cout<<"Sensor "<<sens2.id()<<" "<<sens2.read()<<std::endl;
}