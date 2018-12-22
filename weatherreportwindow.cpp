#include "weatherreportwindow.h"
#include "ui_weatherreportwindow.h"

CWeatherReportWindow::CWeatherReportWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CWeatherReportWindow)
{
    ui->setupUi(this);

    QPixmap weatherPixmap("/Users/mholyoak/QtProjects/SampleWeatherReport/04d.png");
    QIcon weatherIcon(weatherPixmap);
    locationItem.setIcon(weatherIcon);
    locationItem.setText("Salt Lake City\t37°");
    locationItem.setBackgroundColor(QColor(240, 240, 240));
    ui->_locationListWidget->insertItem(0, &locationItem);
    locationItem2.setIcon(weatherIcon);
    locationItem2.setText("London\t37°");
    locationItem2.setBackgroundColor(QColor(240, 240, 240));
    ui->_locationListWidget->insertItem(1, &locationItem2);
}

CWeatherReportWindow::~CWeatherReportWindow()
{
    delete ui;
}
