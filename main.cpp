#include "weatherreportwindow.h"
#include <QApplication>

#include <iostream>

#include "curlrestrequester.h"
#include "openweathermapreporter.h"

int main(int argc, char *argv[])
{
    /*
    CCurlRestRequester restRequester;

    auto restResponese = restRequester.GetRequest("https://api.openweathermap.org/data/2.5/weather?q=Salt%20Lake%20City&units=imperial&APPID=da65fafb6cb9242168b7724fb5ab75e7");

    std::cout << "Response: " << restResponese.GetBody() << std::endl;
    */
    std::shared_ptr<IRestRequester> restRequester = std::make_shared<CCurlRestRequester>();
    COpenWeatherMapReporter weatherReporter(restRequester);

    auto slcWeather = weatherReporter.GetWeather("Salt Lake City");
    std::cout << "Response: " << slcWeather.GetCityName() << " " << slcWeather.GetDescription() << std::endl;

    QApplication a(argc, argv);
    CWeatherReportWindow w;
    w.show();

    return a.exec();
}
