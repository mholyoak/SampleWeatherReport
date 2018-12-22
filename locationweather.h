#ifndef LOCATIONWEATHER_H
#define LOCATIONWEATHER_H

#include <string>
#include <list>
#include <QIcon>

class CLocationWeather
{
public:
    typedef std::string         CityName;
    typedef std::list<CityName> CityNameList;

    CLocationWeather();

    CityName    GetCityName() const;
    void        SetCityName(CityName cityName);

    QIcon       GetIcon() const;
    void        SetIcon(QIcon icon);

    float       GetCurrentTemperature() const;
    void        SetCurrentTemperature(float temperature);

    std::string GetDescription() const;
    void        SetDescription(const std::string& description);

private:
    CityName    _cityName;
    QIcon       _icon;
    float       _currentTemperature;
    std::string _description;
};

#endif // LOCATIONWEATHER_H
