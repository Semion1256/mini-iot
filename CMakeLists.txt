cmake_minimum_required(VERSION 3.10)

project(MySensor)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(/usr/src/googletest googletest-build)
add_executable(sensor
    src/main.cpp
    src/Sensor.cpp
    src/SensorManager.cpp
    src/Logger.cpp
    src/MeasurementProcessor.cpp
    src/MeasurementPrinter.cpp
    src/UdpServer.cpp
    src/UdpClient.cpp
    
)

add_executable(sensorTest
    tests/sensorTests.cpp
    src/Sensor.cpp
    src/MeasurementProcessor.cpp
    
)

target_include_directories(sensor PRIVATE src)
target_include_directories(sensorTest PRIVATE src)

target_link_libraries(sensorTest PRIVATE gtest_main)