class Measurement;
class MeasurementProcessor
{

public:
    bool isValid(const Measurement& measurement) const;
    bool isTemperatureValid(double temperature) const;
    bool isHumidityValid(double humidity) const;
};

