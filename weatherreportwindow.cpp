#include "weatherreportwindow.h"
#include "ui_weatherreportwindow.h"

#include "curlrestrequester.h"
#include "openweathermapreporter.h"
#include <iostream>

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

    //QPixmap weatherPixmap("/Users/mholyoak/QtProjects/SampleWeatherReport/04d.png");
    //QIcon weatherIcon(weatherPixmap);
    locationItem.setIcon(slcWeather.GetIcon());
    locationItem.setText(slcWeather.GetCityName().c_str());
    locationItem.setBackgroundColor(QColor(220, 220, 220));
    ui->_locationListWidget->insertItem(0, &locationItem);
    locationItem2.setIcon(londonWeather.GetIcon());
    locationItem2.setText(londonWeather.GetCityName().c_str());
    locationItem2.setBackgroundColor(QColor(220, 220, 220));
    ui->_locationListWidget->insertItem(1, &locationItem2);

}

CWeatherReportWindow::~CWeatherReportWindow()
{
    delete ui;
}
