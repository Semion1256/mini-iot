#pragma once
class Measurement;
class Sensor
{
public:
    Sensor(int id);
    int id() const;

    Measurement read() const;

private:
    double getRandomNumber() const;

private:
    int m_id;
};