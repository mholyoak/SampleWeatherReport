#include "locationweather.h"

#include <iostream>
#include <iomanip>
#include <sstream>

CLocationWeather::CLocationWeather()
{

}

CLocationWeather::CLocationWeather(CityName cityName, CountryName countryName) :
    _cityName(cityName),
    _countryName(countryName),
    _description(""),
    _currentTemperature(0.0),
    _hiTemperature(0.0),
    _lowTemperature(0.0),
    _windSpeed(0.0)
{

}

CLocationWeather::CityName CLocationWeather::GetCityName() const
{
    return _cityName;
}

void CLocationWeather::SetCityName(CityName cityName)
{
    _cityName = cityName;
}

CLocationWeather::CountryName CLocationWeather::GetCountryName() const
{
    return _countryName;
}

void CLocationWeather::SetCountryName(CountryName countryName)
{
    _countryName = countryName;
}



QPixmap CLocationWeather::GetIcon() const
{
    return _icon;
}

void CLocationWeather::SetIcon(QPixmap icon)
{
    _icon = icon;
}

std::string CLocationWeather::GetDescription() const
{
    return _description;
}

void CLocationWeather::SetDescription(const std::string& description)
{
    _description = description;
}

float CLocationWeather::GetCurrentTemperature() const
{
    return _currentTemperature;
}

void CLocationWeather::SetCurrentTemperature(float temperature)
{
    _currentTemperature = temperature;
}

float CLocationWeather::GetHiTemperature() const
{
    return _hiTemperature;
}

void CLocationWeather::SetHiTemperature(float temperature)
{
    _hiTemperature = temperature;
}

float CLocationWeather::GetLowTemperature() const
{
    return _lowTemperature;
}

void CLocationWeather::SetLowTemperature(float temperature)
{
    _lowTemperature = temperature;
}

float CLocationWeather::GetWindSpeed() const
{
    return _windSpeed;
}

void CLocationWeather::SetWindSpeed(float speed)
{
    _windSpeed = speed;
}

// Helper function to print temperature string could move to a utility module
std::string CLocationWeather::GetTemperatureString(float temperature) const
{
    std::stringstream cityTempStr;
    cityTempStr << std::fixed << std::setprecision(1) << temperature << "°";
    return cityTempStr.str();
}
