#include "weatherdetaildialog.h"
#include "ui_weatherdetaildialog.h"

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
    ui->_icon->setPixmap(locationWeather.GetIcon());
    ui->_cityName->setText(locationWeather.GetCityName().c_str());
    ui->_description->setText(locationWeather.GetDescription().c_str());
    ui->_currentTemperature->setText(
                locationWeather.GetTemperatureString(locationWeather.GetCurrentTemperature()).c_str());
    ui->_hiTemperature->setText(
                locationWeather.GetTemperatureString(locationWeather.GetHiTemperature()).c_str());
    ui->_lowTemperature->setText(
                locationWeather.GetTemperatureString(locationWeather.GetLowTemperature()).c_str());

    exec();
}
