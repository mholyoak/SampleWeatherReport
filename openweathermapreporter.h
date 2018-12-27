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

private:
    std::shared_ptr<IRestRequester> _restRequester;

    CLocationWeather            ParseWeatherJson(const std::string& weatherResponseJson) const;
    QPixmap                     CreateWeatherIcon(const std::string& iconName) const;
    CRestResponse::BinaryData   DownloadWeatherPng(const std::string& iconName) const;


    CRestResponse               CallCityRestApi(const CLocationWeather::CityName& cityName) const;
    CRestResponse               CallIconRestAPI(const std::string& iconName) const;
};

#endif // OPENWEATHERMAPREPORTER_H
