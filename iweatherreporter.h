#ifndef IWEATHERREPORTER_H
#define IWEATHERREPORTER_H

#include "locationweather.h"

class IWeatherReporter
{
public:
    virtual ~IWeatherReporter() {}

    virtual CLocationWeather GetWeather(const CLocationWeather::CityName& cityName) const = 0;
};

#endif // IWEATHERREPORTER_H
