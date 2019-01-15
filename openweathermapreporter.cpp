#include "openweathermapreporter.h"

#include <sstream>
#include <string>
#include <json/reader.h>

static const char* sDomainName = "api.openweathermap.org";
static const char* sProtocall = "https://";
// The APP ID should probably be saved in a config file so that it isn't saved with the code
static const char* sAppId = "da65fafb6cb9242168b7724fb5ab75e7";

COpenWeatherMapReporter::COpenWeatherMapReporter(std::shared_ptr<IRestRequester> restRequester) :
    _restRequester(restRequester)
{

}

COpenWeatherMapReporter::~COpenWeatherMapReporter()
{

}

CLocationWeather COpenWeatherMapReporter::GetWeather(const CLocationWeather::CityName& cityName,
                                                     const CLocationWeather::CountryName& countryName) const
{
    CLocationWeather locationWeather;

    auto restResponse = CallCityRestApi(cityName, countryName);

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

// Handle parsing json and setting weather location info
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
        locationWeather.SetCountryName(weatherJson["sys"]["country"].asString());
        locationWeather.SetCurrentTemperature(weatherJson["main"]["temp"].asFloat());
        locationWeather.SetDescription(weatherJson["weather"][0]["description"].asString());
        locationWeather.SetHiTemperature(weatherJson["main"]["temp_max"].asFloat());
        locationWeather.SetLowTemperature(weatherJson["main"]["temp_min"].asFloat());
        locationWeather.SetWindSpeed(weatherJson["wind"]["speed"].asFloat());
        // TODO This should probably be a loop but its not clear what multiple icons would be used for
        std::string iconName = weatherJson["weather"][0]["icon"].asString();

        locationWeather.SetIcon(CreateWeatherIcon(iconName));
    }

    return locationWeather;
}

// handle creating a icon from binary data from REST call
QPixmap COpenWeatherMapReporter::CreateWeatherIcon(const std::string& iconName) const
{
    QPixmap weatherPixmap;

    auto pngIcon = DownloadWeatherPng(iconName);

    weatherPixmap.loadFromData(pngIcon.data(), uint(pngIcon.size()));

    return weatherPixmap;
}

// handle downloading the PNG file
CRestResponse::BinaryData COpenWeatherMapReporter::DownloadWeatherPng(const std::string& iconName) const
{
    CRestResponse iconResponse = CallIconRestApi(iconName);
    if (iconResponse.Success())
    {
        return iconResponse.GetBinaryBody();
    }

    return CRestResponse::BinaryData();
}

// Replace a sub string - TODO this should be moved to a utilities module
void ReplaceSubString(std::string& updateString, std::string strToReplace, std::string replacementStr)
{
    size_t index = 0;
    while (index != std::string::npos)
    {
         // Locate the substring to replace
         index = updateString.find(strToReplace, index);
         if (index != std::string::npos)
         {
             updateString.replace(index, strToReplace.size(), replacementStr);

             index += strToReplace.size();
         }
    }
}

// Call city REST API to get weather JSON
CRestResponse COpenWeatherMapReporter::CallCityRestApi(const CLocationWeather::CityName& cityName,
                                                       const CLocationWeather::CountryName& countryName) const
{
    // https://api.openweathermap.org/data/2.5/weather?q=Salt%20Lake%20City&units=imperial&APPID=da65fafb6cb9242168b7724fb5ab75e7
    const char* cityNameFmt = "CITYNAME";
    const char* countryNameFmt = "COUNTRYNAME";
    const char* appIdFmt = "APIIDFMT";
    std::string cityWeatherUrl("/data/2.5/weather?q=CITYNAME,COUNTRYNAME&units=imperial&APPID=APIIDFMT");

    ReplaceSubString(cityWeatherUrl, cityNameFmt, cityName);
    ReplaceSubString(cityWeatherUrl, countryNameFmt, countryName);
    ReplaceSubString(cityWeatherUrl, appIdFmt, sAppId);
    ReplaceSubString(cityWeatherUrl, " ", "%20");

    std::ostringstream urlStrStream;
    urlStrStream << sProtocall << sDomainName << cityWeatherUrl;
    std::string weatherUrl = urlStrStream.str();

    auto restResponse = _restRequester->GetRequest(weatherUrl);

    return restResponse;
}

// Call icon REST API to get png binary image
CRestResponse COpenWeatherMapReporter::CallIconRestApi(const std::string& iconName) const
{
    // http://openweathermap.org/img/w/09d.png?APPID=da65fafb6cb9242168b7724fb5ab75e7
    const char* iconNameFmt = "ICONNAME";
    const char* appIdFmt = "APIIDFMT";
    std::string iconWeatherUrl("/img/w/ICONNAME.png?APPID=APIIDFMT");

    ReplaceSubString(iconWeatherUrl, iconNameFmt, iconName);
    ReplaceSubString(iconWeatherUrl, appIdFmt, sAppId);

    std::ostringstream urlStrStream;
    urlStrStream << sProtocall << sDomainName << iconWeatherUrl;
    std::string weatherUrl = urlStrStream.str();

    auto restResponse = _restRequester->GetBinaryRequest(weatherUrl);

    return restResponse;
}

// Parse the find city JSON and create list of City Names
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

// Call REST API to find list of matching cities
CRestResponse COpenWeatherMapReporter::CallFindCityRestApi(const std::string& findCity) const
{
    // https://api.openweathermap.org/data/2.5/find?q=London&type=like&appid=da65fafb6cb9242168b7724fb5ab75e7
    const char* cityNameFmt = "CITYNAME";
    const char* appIdFmt = "APIIDFMT";
    std::string cityWeatherUrl("/data/2.5/find?q=CITYNAME&APPID=APIIDFMT");

    ReplaceSubString(cityWeatherUrl, cityNameFmt, findCity);
    ReplaceSubString(cityWeatherUrl, appIdFmt, sAppId);
    ReplaceSubString(cityWeatherUrl, " ", "%20");

    std::ostringstream urlStrStream;
    urlStrStream << sProtocall << sDomainName << cityWeatherUrl;
    std::string weatherUrl = urlStrStream.str();

    auto restResponse = _restRequester->GetRequest(weatherUrl);

    return restResponse;
}


