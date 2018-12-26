#include "openweathermapreporter.h"

#include <sstream>
#include <string>
#include <json/reader.h>

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
        std::string jsonResponse = restResponse.GetStringBody();
        locationWeather = ParseWeatherJson(jsonResponse);

    }

    return locationWeather;
}

CLocationWeather COpenWeatherMapReporter::ParseWeatherJson(const std::string& weatherResponseJson) const
{
    CLocationWeather locationWeather;

    Json::CharReaderBuilder builder;
    Json::CharReader * jsonReader = builder.newCharReader();
    Json::Value weatherJson;
    std::string errors;

    auto result = jsonReader->parse(weatherResponseJson.c_str(), weatherResponseJson.c_str() + weatherResponseJson.size(), &weatherJson, &errors);

    // BUGBUG need try catch
    locationWeather.SetCityName(weatherJson["name"].asString());
    locationWeather.SetCurrentTemperature(weatherJson["main"]["temp"].asFloat());
    locationWeather.SetDescription(weatherJson["weather"][0]["description"].asString());
    std::string iconName = weatherJson["weather"][0]["icon"].asString();

    locationWeather.SetIcon(CreateWeatherIcon(iconName));

    return locationWeather;
}

#include <fstream>

QIcon COpenWeatherMapReporter::CreateWeatherIcon(const std::string& iconName) const
{
    QIcon weatherIcon;
    QPixmap weatherPixmap;

    auto pngIcon = DownloadWeatherPng(iconName);

    weatherPixmap.loadFromData(pngIcon.data(), pngIcon.size());

    weatherIcon.addPixmap(weatherPixmap);

    return weatherIcon;
}

CRestResponse::BinaryData COpenWeatherMapReporter::DownloadWeatherPng(const std::string& iconName) const
{
    CRestResponse iconResponse = CallIconRestAPI(iconName);
    if (iconResponse.Success())
    {
        return iconResponse.GetBinaryBody();
    }

    return CRestResponse::BinaryData();
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

CRestResponse COpenWeatherMapReporter::CallIconRestAPI(const std::string& iconName) const
{
    // http://openweathermap.org/img/w/09d.png?APPID=da65fafb6cb9242168b7724fb5ab75e7
    const char* iconNameFmt = "ICONNAME";
    std::string iconWeatherUrl("/img/w/ICONNAME.png?APPID=da65fafb6cb9242168b7724fb5ab75e7");

    ReplaceSubString(iconWeatherUrl, iconNameFmt, iconName);

    std::ostringstream urlStrStream;
    urlStrStream << sProtocall << sDomainName << iconWeatherUrl;
    std::string weatherUrl = urlStrStream.str();

    auto restResponse = _restRequester->GetBinaryRequest(weatherUrl);

    return restResponse;
}

