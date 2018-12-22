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

QIcon       CLocationWeather::GetIcon() const
{
    return _icon;
}

void CLocationWeather::SetIcon(QIcon icon)
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
