#pragma once
#include <sys/types.h>
#include <condition_variable>
#include <mutex>
class UdpServer
{
private:
    /* data */
public:
    void start(ssize_t expectedMessages, bool &serverReady, std::condition_variable &serverCv, std::mutex &serverMutex, bool& serverFailed);
};


