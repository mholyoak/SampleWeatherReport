#ifndef IWEATHERREPORTER_H
#define IWEATHERREPORTER_H

#include "locationweather.h"

// Weather Reporter Interface so we could use different weather services
class IWeatherReporter
{
public:
    virtual ~IWeatherReporter() = default;

    // Return the weather object for a city
    virtual CLocationWeather GetWeather(const CLocationWeather::CityName& cityName,
                                        const CLocationWeather::CountryName& countryName) const = 0;
    // Search for a city and return list of matches
    virtual CLocationWeather::CityNameList FindCity(const std::string& findCity) const = 0;
};

#endif // IWEATHERREPORTER_H
