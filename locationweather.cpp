#include "locationweather.h"

CLocationWeather::CLocationWeather()
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

QPixmap CLocationWeather::GetIcon() const
{
    return _icon;
}

void CLocationWeather::SetIcon(QPixmap icon)
{
    _icon = icon;
}

float CLocationWeather::GetCurrentTemperature() const
{
    return _currentTemperature;
}

void CLocationWeather::SetCurrentTemperature(float temperature)
{
    _currentTemperature = temperature;
}

std::string CLocationWeather::GetDescription() const
{
    return _description;
}

void CLocationWeather::SetDescription(const std::string& description)
{
    _description = description;
}

