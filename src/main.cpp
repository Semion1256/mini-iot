#include <vector>
#include <iostream>
#include <thread>
#include <nlohmann/json.hpp>
#include <mutex>
#include <condition_variable>
#include "Sensor.h"
#include "Measurement.h"
#include "MeasurementProcessor.h"
#include "SensorManager.h"
#include "Logger.h"
#include "MeasurementPrinter.h"
#include "UdpServer.h"
#include "UdpClient.h"
using nlohmann::json;
bool serverReady = false;
bool serverFailed = false;
std::condition_variable serverCv;
std::mutex serverMutex;
int main()
{

    Sensor sens1(1);
    Sensor sens2(2);
    Sensor sens3(3);
    Sensor sens4(4);
    std::vector<Sensor> sensors = {sens1, sens2, sens3, sens4};
    SensorManager manager(sensors);
    Sensor sens5(5);
    manager.addSensor(sens5);
    Logger logger;
    MeasurementProcessor measurementProcessor;
    MeasurementPrinter printer;
    const std::vector<Sensor> &sensorsGet = manager.getSensors();
    UdpServer server;
    UdpClient client;

    std::thread serverThread(&UdpServer::start,
                             &server, 1,
                             std::ref(serverReady),
                             std::ref(serverCv),
                             std::ref(serverMutex),
                             std::ref(serverFailed));

    {
        std::unique_lock lock(serverMutex);
        serverCv.wait(lock, [&]
                      { return serverReady || serverFailed; });
    }
    if (serverFailed)
    {
        serverThread.join();
        return 1;
    }
    for (int i = 0; i < 1; ++i)
    {
        Measurement measurement = sensorsGet[i].read();

        if (measurementProcessor.isValid(measurement))
        {

            logger.log(measurement);
            printer.printMeasurement(measurement);
            json data = {
                {"sensorId", measurement.sensorId},
                {"temperature", measurement.temperature},
                {"humidity", measurement.humidity}};
            std::string message = data.dump();

            // client.start(message);
            std::string badMessage = R"({"sensorId":1,"temperature":"wrong"})";
            std::string goodMessage = R"({"sensorId":2,"temperature":25.5,"humidity":30.2})";

            client.start(badMessage);
            client.start(goodMessage);
        }
        else
        {
            std::cout << "Invalid measurement" << std::endl;
        }
    }
    serverThread.join();
    std::cout << "Program finished successfully" << std::endl;
}