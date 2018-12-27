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

CLocationWeather::CityNameList COpenWeatherMapReporter::FindCity(const std::string& findCity) const
{
    CLocationWeather::CityNameList cityNameList;

    auto restResponse = CallFindCityRestApi(findCity);
    if (restResponse.RequestSuccess())
    {
        cityNameList = ParseFindCityJson(restResponse.GetStringBody());
    }

    return cityNameList;
}

CLocationWeather COpenWeatherMapReporter::ParseWeatherJson(const std::string& weatherResponseJson) const
{
    CLocationWeather locationWeather;

    Json::CharReaderBuilder builder;
    Json::CharReader * jsonReader = builder.newCharReader();
    Json::Value weatherJson;
    std::string errors;

    auto success = jsonReader->parse(weatherResponseJson.c_str(), weatherResponseJson.c_str() + weatherResponseJson.size(), &weatherJson, &errors);
    if (success)
    {
        locationWeather.SetCityName(weatherJson["name"].asString());
        locationWeather.SetCurrentTemperature(weatherJson["main"]["temp"].asFloat());
        locationWeather.SetDescription(weatherJson["weather"][0]["description"].asString());
        locationWeather.SetHiTemperature(weatherJson["main"]["temp_max"].asFloat());
        locationWeather.SetLowTemperature(weatherJson["main"]["temp_min"].asFloat());
        locationWeather.SetWindSpeed(weatherJson["wind"]["speed"].asFloat());
        // BUGBUG should be a loop
        std::string iconName = weatherJson["weather"][0]["icon"].asString();

        locationWeather.SetIcon(CreateWeatherIcon(iconName));
    }

    return locationWeather;
}

QPixmap COpenWeatherMapReporter::CreateWeatherIcon(const std::string& iconName) const
{
    QPixmap weatherPixmap;

    auto pngIcon = DownloadWeatherPng(iconName);

    weatherPixmap.loadFromData(pngIcon.data(), pngIcon.size());

    return weatherPixmap;
}

CRestResponse::BinaryData COpenWeatherMapReporter::DownloadWeatherPng(const std::string& iconName) const
{
    CRestResponse iconResponse = CallIconRestApi(iconName);
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

CRestResponse COpenWeatherMapReporter::CallIconRestApi(const std::string& iconName) const
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

CLocationWeather::CityNameList COpenWeatherMapReporter::ParseFindCityJson(const std::string& findCityResponseJson) const
{
    CLocationWeather::CityNameList cityNameList;

    Json::CharReaderBuilder builder;
    Json::CharReader * jsonReader = builder.newCharReader();
    Json::Value findCityJson;
    std::string errors;

    auto success = jsonReader->parse(findCityResponseJson.c_str(), findCityResponseJson.c_str() + findCityResponseJson.size(), &findCityJson, &errors);
    if (success)
    {
        auto cityListJson = findCityJson["list"];

        for (auto cityJson = cityListJson.begin(); cityJson != cityListJson.end(); ++cityJson)
        {
            cityNameList.push_back((*cityJson)["name"].asString() + ", " + (*cityJson)["sys"]["country"].asString());
        }
    }

    return cityNameList;
}

CRestResponse COpenWeatherMapReporter::CallFindCityRestApi(const std::string& findCity) const
{
    // https://api.openweathermap.org/data/2.5/find?q=London&type=like&appid=da65fafb6cb9242168b7724fb5ab75e7
    const char* cityNameFmt = "CITYNAME";
    std::string cityWeatherUrl("/data/2.5/find?q=CITYNAME&APPID=da65fafb6cb9242168b7724fb5ab75e7");

    ReplaceSubString(cityWeatherUrl, cityNameFmt, findCity);
    ReplaceSubString(cityWeatherUrl, " ", "%20");

    std::ostringstream urlStrStream;
    urlStrStream << sProtocall << sDomainName << cityWeatherUrl;
    std::string weatherUrl = urlStrStream.str();

    auto restResponse = _restRequester->GetRequest(weatherUrl);

    return restResponse;
}


