#ifndef OPENWEATHERMAPREPORTER_H
#define OPENWEATHERMAPREPORTER_H

#include "iweatherreporter.h"

#include "irestrequester.h"

#include <memory>

// Open Weather Map implementation of Weather report interface
class COpenWeatherMapReporter :public IWeatherReporter
{
public:
    COpenWeatherMapReporter(std::shared_ptr<IRestRequester>& restRequester);
    virtual ~COpenWeatherMapReporter() override;

    // Get weather info for a city
    CLocationWeather GetWeather(const CLocationWeather::CityName& cityName,
                                const CLocationWeather::CountryName& countryName) const override;
    // Get list of city matching find city
    CLocationWeather::CityNameList FindCity(const std::string& findCity) const override;

private:
    std::shared_ptr<IRestRequester> _restRequester;

    CLocationWeather                ParseWeatherJson(const std::string& weatherResponseJson) const;
    QPixmap                         CreateWeatherIcon(const std::string& iconName) const;
    CRestResponse::BinaryData       DownloadWeatherPng(const std::string& iconName) const;
    CLocationWeather::CityNameList  ParseFindCityJson(const std::string& findCityResponseJson) const;

    CRestResponse                   CallCityRestApi(const CLocationWeather::CityName& cityName,
                                                    const CLocationWeather::CountryName& countryName) const;
    CRestResponse                   CallIconRestApi(const std::string& iconName) const;
    CRestResponse                   CallFindCityRestApi(const std::string& findCity) const;
};

#endif // OPENWEATHERMAPREPORTER_H
