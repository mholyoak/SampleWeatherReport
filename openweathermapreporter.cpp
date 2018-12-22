#include "openweathermapreporter.h"

#include <sstream>

static const char* sDomainName = "api.openweathermap.org";
static const char* sProtocall = "https://";

COpenWeatherMapReporter::COpenWeatherMapReporter(std::shared_ptr<IRestRequester> &restRequester) :
    _restRequester(restRequester)
{

}

COpenWeatherMapReporter::~COpenWeatherMapReporter()
{

}

CLocationWeather COpenWeatherMapReporter::GetWeather(const CLocationWeather::CityName& cityName) const
{

    CLocationWeather locationWeather;



    locationWeather.SetCityName(cityName);

    return locationWeather;
}


CRestResponse COpenWeatherMapReporter::CallCityRestApi(const CLocationWeather::CityName& cityName) const
{
    // https://api.openweathermap.org/data/2.5/weather?q=Salt%20Lake%20City&units=imperial&APPID=da65fafb6cb9242168b7724fb5ab75e7
    const char* cityNameFmt = "CITYNAME";
    std::string cityWeatherUrl("/data/2.5/weather?q=CITYNAME&units=imperial&APPID=da65fafb6cb9242168b7724fb5ab75e7");

    auto index = cityWeatherUrl.find(cityNameFmt, 0);
    if (index == std::string::npos)
    {
        return CRestResponse(1, 0, "");
    }

    // Make the replacement.
    cityWeatherUrl.replace(index, cityName.size(), cityName);

    std::ostringstream urlStrStream;
    urlStrStream << sProtocall << sDomainName << cityWeatherUrl;
    std::string weatherUrl = urlStrStream.str();

    auto restResponse = _restRequester->GetRequest(weatherUrl);

    return restResponse;
}
