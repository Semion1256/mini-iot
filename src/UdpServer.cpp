#include "UdpServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>

using nlohmann::json;
void UdpServer::start(ssize_t expectedMessages, bool &serverReady, std::condition_variable &serverCv, std::mutex &serverMutex, bool &serverFailed)
{
    std::cout<<expectedMessages<<"смотрим"<<std::endl;
    int serverFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverFd == -1)
    {
        std::cerr << "server fd error\n"
                  << strerror(errno);
        {
            std::lock_guard<std::mutex> lock(serverMutex);
            serverFailed = true;
        }

        serverCv.notify_one();

        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int bindResult = bind(serverFd, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr));
    if (bindResult == -1)
    {

        std::cerr << "bind error\n"
                  << strerror(errno);
        close(serverFd);
        {
            std::lock_guard<std::mutex> lock(serverMutex);
            serverFailed = true;
        }
        serverCv.notify_one();
        return;
    }

    sockaddr_in clientAddr{};
    timeval tv{};
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    if (setsockopt(serverFd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == -1)
    {
        std::cerr << "setsockopt error: " << strerror(errno) << '\n';
        close(serverFd);
        {
            std::lock_guard<std::mutex> lock(serverMutex);
            serverFailed = true;
        }
        serverCv.notify_one();
        return;
    }
    {
        std::lock_guard<std::mutex> lock(serverMutex);
        serverReady = true;
    }
    serverCv.notify_one();
    for (ssize_t i = 0; i < expectedMessages; ++i)
    {
        bool receiveFailed = false;
        int timeoutCount = 0;
        bool succes = false;
        char tmp[1024];
        std::string buffer;

        while (timeoutCount != 3 && !succes && !receiveFailed)
        {
            socklen_t clientLen = sizeof(clientAddr);
            ssize_t bytesReceived = recvfrom(serverFd, tmp, sizeof(tmp), 0, reinterpret_cast<sockaddr *>(&clientAddr), &clientLen);
            if (bytesReceived > 0)
            {
                buffer.clear();
                buffer.append(tmp, bytesReceived);

                try
                {
                    json data = json::parse(buffer);
                    int id = data["sensorId"].get<int>();
                    double temperature = data["temperature"].get<double>();
                    double humidity = data["humidity"].get<double>();
                    std::cout << "Sensor ID: " << id
                              << " Temperature: " << temperature
                              << " Humidity: " << humidity << '\n';
                    const char *message = "OK";
                    ssize_t bytesSent = sendto(serverFd, message, strlen(message), 0, reinterpret_cast<sockaddr *>(&clientAddr), sizeof(clientAddr));
                    if (bytesSent == strlen(message))
                    {
                        std::cout << "ACK sent successfully" << std::endl;
                    }
                    else
                    {
                        std::cerr << "sendto error: " << strerror(errno) << '\n';
                        break;
                    }
                    succes = true;
                    timeoutCount = 0;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            else if (bytesReceived == 0)
            {
                std::cout << "Получена пустая датаграмма\n";
                continue;
            }
            else
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                {
                    std::cerr << "Server timeout\n";
                    timeoutCount++;
                }
                else
                {
                    std::cerr << "recvfrom error: "
                              << strerror(errno) << '\n';
                    receiveFailed = true;
                }
            }
        }
        if (!succes)
        {
            break;
        }
    }
    close(serverFd);
}
