#include "weatherdetaildialog.h"
#include "ui_weatherdetaildialog.h"

#include <iostream>
#include <iomanip>
#include <sstream>

CWeatherDetailDialog::CWeatherDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CWeatherDetailDialog)
{
    ui->setupUi(this);
}

CWeatherDetailDialog::~CWeatherDetailDialog()
{
    delete ui;
}

void CWeatherDetailDialog::ShowDetail(const CLocationWeather& locationWeather)
{
    // Populate controls
    ui->_icon->setPixmap(locationWeather.GetIcon());
    ui->_cityName->setText(locationWeather.GetCityName().c_str());
    ui->_countryName->setText(locationWeather.GetCountryName().c_str());
    ui->_description->setText(locationWeather.GetDescription().c_str());
    ui->_currentTemperature->setText(
                locationWeather.GetTemperatureString(locationWeather.GetCurrentTemperature()).c_str());
    ui->_hiTemperature->setText(
                locationWeather.GetTemperatureString(locationWeather.GetHiTemperature()).c_str());
    ui->_lowTemperature->setText(
                locationWeather.GetTemperatureString(locationWeather.GetLowTemperature()).c_str());

    std::stringstream windSpeedStr;
    windSpeedStr << std::fixed << std::setprecision(1) << locationWeather.GetWindSpeed() << " mph";
    ui->_windSpeed->setText(windSpeedStr.str().c_str());

    // Display Dialog
    exec();
}
