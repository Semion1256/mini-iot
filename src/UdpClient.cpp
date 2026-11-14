#include "UdpClient.h"
#include <sys/socket.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <nlohmann/json.hpp>

using nlohmann::json;
void UdpClient::start(const std::string &message)
{

    int clientFd = socket(AF_INET, SOCK_DGRAM, 0);

    if (clientFd == -1)
    {
        std::cerr << "client socket error\n"
                  << strerror(errno);

        return;
    }
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    timeval tv{};
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    if (setsockopt(clientFd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == -1)
    {
        std::cerr << "setsockopt error: " << strerror(errno) << '\n';
        close(clientFd);
        return;
    }

    ssize_t bytesSent = sendto(clientFd, message.data(), message.size(), 0, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr));

    if (bytesSent == message.size())
    {
        char tmp[1024];
        std::string buffer;
        sockaddr_in fromAddr{};
        socklen_t fromLen = sizeof(fromAddr);

        ssize_t bytesReceived = recvfrom(clientFd, tmp, sizeof(tmp), 0, reinterpret_cast<sockaddr *>(&fromAddr), &fromLen);

        if (bytesReceived > 0)
        {
            buffer.append(tmp, bytesReceived);
            if (buffer == "OK")
            {
                std::cout << "Server acknowledged message" << std::endl;
            }
            else
            {
                std::cout << "unexpected answer" << std::endl;
            }
        }
        else if (bytesReceived == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                std::cerr << "client timeout\n";
            }
            else
            {
                std::cerr << "recvfrom error: "
                          << strerror(errno) << '\n';
            }
            close(clientFd);
            return;
        }
        else
        {
            std::cout << "пришла пустая датаграмма\n";
            close(clientFd);
            return;
        }
    }
    else if (bytesSent == -1)
    {
        std::cerr << "sent error\n"
                  << strerror(errno);
        close(clientFd);
        return;
    }
    else
    {
        std::cout << "размер байтов не равен сообщению";
        close(clientFd);
        return;
    }
    close(clientFd);
}