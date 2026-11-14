#include <gtest/gtest.h>
#include "Sensor.h"
#include "Measurement.h"
#include "MeasurementProcessor.h"
TEST(sensorTests, sensorIdCorrect){
    Sensor sensor(42);
    Measurement meas = sensor.read();
    EXPECT_EQ(meas.sensorId, 42);
     
}

TEST(sensorTests, temperatureInRange){
    Sensor sensor(42);
    Measurement meas = sensor.read();
    EXPECT_GE(meas.temperature, 1);
    EXPECT_LE(meas.temperature, 40);
    

}

TEST(sensorTests, humidityInRange){
    Sensor sensor(42);
    Measurement meas = sensor.read();
    EXPECT_GE(meas.humidity, 1);
    EXPECT_LE(meas.humidity, 40);
}

TEST(sensorTests, timestampCorrect){
    Sensor sensor(42);
    auto before = std::chrono::system_clock::now();
    Measurement meas = sensor.read();
    auto after = std::chrono::system_clock::now();
    EXPECT_GE(meas.timestamp, before);
    EXPECT_LE(meas.timestamp, after);
}

TEST(MeasurementTest, temperatureOutRange){
    MeasurementProcessor measurementProcessor;
    bool temperatureAboveRange = measurementProcessor.isTemperatureValid(41);
    bool temperatureBelowRange = measurementProcessor.isTemperatureValid(0);
    EXPECT_EQ(temperatureAboveRange, false);
    EXPECT_EQ(temperatureBelowRange, false);
    
}

TEST(MeasurementTest, temperatureInRange){
    MeasurementProcessor measurementProcessor;
    bool temperatureInMinRange =measurementProcessor.isTemperatureValid(1);
    bool temperatureInMaxRange = measurementProcessor.isTemperatureValid(40);
    EXPECT_EQ(temperatureInMinRange, true);
    EXPECT_EQ(temperatureInMaxRange, true);
}

TEST(MeasurementTests, humidityOutRange){
    MeasurementProcessor measurementProcessor;
    bool humidityAboveRange = measurementProcessor.isHumidityValid(41);
    bool humidityBelowRange = measurementProcessor.isHumidityValid(0);
    EXPECT_EQ(humidityAboveRange, false);
    EXPECT_EQ(humidityBelowRange, false);
    
}

TEST(MeasurementTests, humidityInRange){
    MeasurementProcessor measurementProcessor;
    bool humidityMinRange = measurementProcessor.isHumidityValid(1);
    bool humidityMaxRange = measurementProcessor.isHumidityValid(40);
    EXPECT_EQ(humidityMinRange, true);
    EXPECT_EQ(humidityMaxRange, true);
    
}

TEST(MeasurementTests, isInvalidTemperatureisInValidHumidity){
    MeasurementProcessor measurementProcessor;
    Measurement measurement{
        .temperature = 41,
        .humidity = 41
    };
    EXPECT_FALSE(measurementProcessor.isValid(measurement));
    
}

TEST(MeasurementTests, isInvalidTemperatureisValidHumidity){
    MeasurementProcessor measurementProcessor;
    Measurement measurement{
        .temperature = 41,
        .humidity = 20
    };
    EXPECT_FALSE(measurementProcessor.isValid(measurement));
    
}

TEST(MeasurementTests, isValidTemperatureisInValidHumidity){
    MeasurementProcessor measurementProcessor;
    Measurement measurement{
        .temperature = 20,
        .humidity = 41
    };
    EXPECT_FALSE(measurementProcessor.isValid(measurement));
    
}

TEST(MeasurementTests, isValidTemperatureisValidHumidity){
    MeasurementProcessor measurementProcessor;
    Measurement measurement{
        .temperature = 20,
        .humidity = 20
    };
    EXPECT_TRUE(measurementProcessor.isValid(measurement));
    
}

