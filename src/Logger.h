#pragma once
#include <fstream>
class Measurement;
class Logger
{
public:
    Logger();
    ~Logger();
    void log(const Measurement& measurement);
private:
    std::ofstream m_file;

};


