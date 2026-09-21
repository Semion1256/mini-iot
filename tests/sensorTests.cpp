#include <gtest/gtest.h>
#include "Sensor.h"
#include "Measurement.h"
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