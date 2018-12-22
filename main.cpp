#include "weatherreportwindow.h"
#include <QApplication>

#include <iostream>

#include "curlrestrequester.h"

int main(int argc, char *argv[])
{
    CCurlRestRequester restRequester;

    auto restResponese = restRequester.GetRequest("https://api.openweathermap.org/data/2.5/weather?q=Salt%20Lake%20City&units=imperial&APPID=da65fafb6cb9242168b7724fb5ab75e7");

    std::cout << "Response: " << restResponese.GetBody() << std::endl;

    QApplication a(argc, argv);
    CWeatherReportWindow w;
    w.show();

    return a.exec();
}
