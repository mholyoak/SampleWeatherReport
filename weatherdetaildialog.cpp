#include "weatherdetaildialog.h"
#include "ui_weatherdetaildialog.h"

#include <QPainter>

#include <iostream>
#include <iomanip>
#include <sstream>

CWeatherDetailDialog::CWeatherDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::make_shared<Ui::CWeatherDetailDialog>())
{
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setParent(nullptr); // Create TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    // If removed paintEvent method this makes background 100% transparent
    //setAttribute(Qt::WA_TranslucentBackground, true);
    ui->setupUi(this);
}

CWeatherDetailDialog::~CWeatherDetailDialog()
{
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

void CWeatherDetailDialog::paintEvent(QPaintEvent* /*event*/)
{
    //QColor backgroundColor = palette().light().color();
    QColor backgroundColor(214, 226, 255);
    backgroundColor.setAlpha(150);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}
