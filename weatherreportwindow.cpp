#include "weatherreportwindow.h"
#include "ui_weatherreportwindow.h"

#include "curlrestrequester.h"
#include "openweathermapreporter.h"
#include <iostream>
#include <iomanip>
#include <sstream>

CWeatherReportWindow::CWeatherReportWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CWeatherReportWindow)
{
    ui->setupUi(this);

    std::shared_ptr<IRestRequester> restRequester = std::make_shared<CCurlRestRequester>();
    COpenWeatherMapReporter weatherReporter(restRequester);

    auto slcWeather = weatherReporter.GetWeather("Salt Lake City");
    std::cout << "Response: " << slcWeather.GetCityName() << " " << slcWeather.GetDescription() << std::endl;

    auto londonWeather = weatherReporter.GetWeather("London");
    std::cout << "Response: " << slcWeather.GetCityName() << " " << slcWeather.GetDescription() << std::endl;

    ui->_locationListWidget->setIconSize(QSize(100, 100));
    locationItem.setIcon(slcWeather.GetIcon());
    std::stringstream cityTempStr;
    cityTempStr << slcWeather.GetCityName() << "\t" << std::fixed << std::setprecision(1) << slcWeather.GetCurrentTemperature() << "°";
    locationItem.setText(cityTempStr.str().c_str());
    locationItem.setBackgroundColor(QColor(220, 220, 220));
    ui->_locationListWidget->insertItem(0, &locationItem);

    locationItem2.setIcon(londonWeather.GetIcon());
    //cityTempStr = londonWeather.GetCityName() + "\t" + std::to_string(londonWeather.GetCurrentTemperature());
    //locationItem2.setText(cityTempStr.c_str());
    locationItem2.setBackgroundColor(QColor(220, 220, 220));
    ui->_locationListWidget->insertItem(1, &locationItem2);
}

CWeatherReportWindow::~CWeatherReportWindow()
{
    delete ui;
}
