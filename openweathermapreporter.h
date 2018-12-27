#ifndef OPENWEATHERMAPREPORTER_H
#define OPENWEATHERMAPREPORTER_H

#include "iweatherreporter.h"

#include "irestrequester.h"

#include <memory>

class COpenWeatherMapReporter :public IWeatherReporter
{
public:
    COpenWeatherMapReporter(std::shared_ptr<IRestRequester>& restRequester);
    virtual ~COpenWeatherMapReporter() override;

    CLocationWeather GetWeather(const CLocationWeather::CityName& cityName) const override;

    CLocationWeather::CityNameList FindCity(const std::string& findCity) const override;

private:
    std::shared_ptr<IRestRequester> _restRequester;

    CLocationWeather                ParseWeatherJson(const std::string& weatherResponseJson) const;
    QPixmap                         CreateWeatherIcon(const std::string& iconName) const;
    CRestResponse::BinaryData       DownloadWeatherPng(const std::string& iconName) const;
    CLocationWeather::CityNameList  ParseFindCityJson(const std::string& findCityResponseJson) const;

    CRestResponse                   CallCityRestApi(const CLocationWeather::CityName& cityName) const;
    CRestResponse                   CallIconRestApi(const std::string& iconName) const;
    CRestResponse                   CallFindCityRestApi(const std::string& findCity) const;
};

#endif // OPENWEATHERMAPREPORTER_H
