#ifndef LOCATIONWEATHER_H
#define LOCATIONWEATHER_H

#include <string>
#include <vector>
#include <QPixmap>

class CLocationWeather
{
public:
    typedef std::string             CityName;
    typedef std::vector<CityName>   CityNameList;

    CLocationWeather();
    CLocationWeather(CityName cityName);

    CityName    GetCityName() const;
    void        SetCityName(CityName cityName);

    QPixmap     GetIcon() const;
    void        SetIcon(QPixmap icon);

    std::string GetDescription() const;
    void        SetDescription(const std::string& description);

    float       GetCurrentTemperature() const;
    void        SetCurrentTemperature(float temperature);

    float       GetHiTemperature() const;
    void        SetHiTemperature(float temperature);

    float       GetLowTemperature() const;
    void        SetLowTemperature(float temperature);

    float       GetWindSpeed() const;
    void        SetWindSpeed(float speed);

    std::string GetTemperatureString(float temperature) const;

private:
    CityName    _cityName;
    QPixmap     _icon;
    std::string _description;
    float       _currentTemperature;
    float       _hiTemperature;
    float       _lowTemperature;
    float       _windSpeed;
};

#endif // LOCATIONWEATHER_H
