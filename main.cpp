#include "weatherreportwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CWeatherReportWindow w;
    w.show();

    return a.exec();
}
