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

    auto restResponse = CallCityRestApi(cityName);

    if (restResponse.RequestSuccess())
    {
        locationWeather.SetCityName(cityName);

        locationWeather.SetDescription(restResponse.GetBody());
    }

    return locationWeather;
}

void ReplaceSubString(std::string& updateString, std::string strToReplace, std::string replacementStr)
{
    size_t index = 0;
    while (index != std::string::npos)
    {
         // Locate the substring to replace
         index = updateString.find(strToReplace, index);
         if (index != std::string::npos)
         {
             /* Make the replacement. */
             updateString.replace(index, strToReplace.size(), replacementStr);

             /* Advance index forward so the next iteration doesn't pick it up as well. */
             index += strToReplace.size();
         }
    }
}

CRestResponse COpenWeatherMapReporter::CallCityRestApi(const CLocationWeather::CityName& cityName) const
{
    // https://api.openweathermap.org/data/2.5/weather?q=Salt%20Lake%20City&units=imperial&APPID=da65fafb6cb9242168b7724fb5ab75e7
    const char* cityNameFmt = "CITYNAME";
    std::string cityWeatherUrl("/data/2.5/weather?q=CITYNAME&units=imperial&APPID=da65fafb6cb9242168b7724fb5ab75e7");

    ReplaceSubString(cityWeatherUrl, cityNameFmt, cityName);
    ReplaceSubString(cityWeatherUrl, " ", "%20");

    std::ostringstream urlStrStream;
    urlStrStream << sProtocall << sDomainName << cityWeatherUrl;
    std::string weatherUrl = urlStrStream.str();

    auto restResponse = _restRequester->GetRequest(weatherUrl);

    return restResponse;
}
