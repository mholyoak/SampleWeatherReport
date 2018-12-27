#include "weatherreportwindow.h"
#include "ui_weatherreportwindow.h"

#include "curlrestrequester.h"
#include "openweathermapreporter.h"
#include "weatherdetaildialog.h"

#include <iostream>
#include <iomanip>
#include <sstream>

CWeatherReportWindow::CWeatherReportWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CWeatherReportWindow)
{
    ui->setupUi(this);

    // Setup button handlers
    auto connected = QObject::connect(ui->_detailBtn, SIGNAL(clicked()), this, SLOT(onDetailButtonclicked()));
    assert(connected);
    connected = QObject::connect(ui->_addBtn, SIGNAL(clicked()), this, SLOT(onAddButtonclicked()));
    assert(connected);
    connected = QObject::connect(ui->_removeBtn, SIGNAL(clicked()), this, SLOT(onRemoveButtonclicked()));
    assert(connected);
    connected = QObject::connect(ui->_locationListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(onListSelectionChanged()));
    assert(connected);

    const char* saltLakeName = "Salt Lake City";
    const char* londonName = "London";
    const char* newYorkName = "New York";
    _cityNameList.push_back(CLocationWeather(saltLakeName));
    _cityNameList.push_back(CLocationWeather(londonName));
    _cityNameList.push_back(CLocationWeather(newYorkName));

    ui->_locationListWidget->setIconSize(QSize(100, 100));

    UpdateWeatherList();

    onListSelectionChanged();
}

CWeatherReportWindow::~CWeatherReportWindow()
{
    delete ui;
}

void CWeatherReportWindow::UpdateWeatherList()
{
    std::shared_ptr<IRestRequester> restRequester = std::make_shared<CCurlRestRequester>();
    COpenWeatherMapReporter weatherReporter(restRequester);

    ui->_locationListWidget->clear();

    for (auto& cityWeather : _cityNameList)
    {
        cityWeather = weatherReporter.GetWeather(cityWeather.GetCityName());

        QListWidgetItem* cityWidgetItem = new QListWidgetItem();
        cityWidgetItem->setIcon(cityWeather.GetIcon());
        std::string cityTempStr;
        cityTempStr = cityWeather.GetCityName() + " - " + cityWeather.GetTemperatureString(cityWeather.GetCurrentTemperature());
        cityWidgetItem->setText(cityTempStr.c_str());
        cityWidgetItem->setBackgroundColor(QColor(220, 220, 220));
        ui->_locationListWidget->addItem(cityWidgetItem);
    }
}


void CWeatherReportWindow::onDetailButtonclicked()
{
    CWeatherDetailDialog detailDialog(this);

    auto selectedRow = ui->_locationListWidget->currentRow();
    if (selectedRow >= 0)
    {
        detailDialog.ShowDetail(_cityNameList[uint32_t(selectedRow)]);
    }
}

void CWeatherReportWindow::onAddButtonclicked()
{

}

void CWeatherReportWindow::onRemoveButtonclicked()
{
    auto selectedRow = ui->_locationListWidget->currentRow();
    if (selectedRow >= 0)
    {
        _cityNameList.erase(_cityNameList.begin() + selectedRow);

        UpdateWeatherList();
    }
}

void CWeatherReportWindow::onListSelectionChanged()
{
    auto selectedRow = ui->_locationListWidget->currentRow();
    ui->_detailBtn->setEnabled(selectedRow >= 0);
    ui->_removeBtn->setEnabled(selectedRow >= 0);
}
