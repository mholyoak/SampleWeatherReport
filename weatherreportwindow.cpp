#include "weatherreportwindow.h"
#include "ui_weatherreportwindow.h"

#include "curlrestrequester.h"
#include "openweathermapreporter.h"
#include "weatherdetaildialog.h"
#include "addcitydialog.h"

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
    const char* sanFranciscoName = "San Francisco";
    const char* newYorkName = "New York";
    const char* usName = "US";
    _cityNameList.push_back(CLocationWeather(saltLakeName, usName));
    _cityNameList.push_back(CLocationWeather(sanFranciscoName, usName));
    _cityNameList.push_back(CLocationWeather(newYorkName, usName));

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
    // Set Wait cursor
    auto saveCursor = this->cursor();
    this->setCursor(Qt::WaitCursor);

    std::shared_ptr<IRestRequester> restRequester = std::make_shared<CCurlRestRequester>();
    COpenWeatherMapReporter weatherReporter(restRequester);

    ui->_locationListWidget->clear();

    // create City weather summary list items
    for (auto& cityWeather : _cityNameList)
    {
        cityWeather = weatherReporter.GetWeather(cityWeather.GetCityName(), cityWeather.GetCountryName());

        QListWidgetItem* cityWidgetItem = new QListWidgetItem();
        cityWidgetItem->setIcon(cityWeather.GetIcon());
        std::string cityTempStr;
        cityTempStr = cityWeather.GetCityName() + ", " + cityWeather.GetCountryName() + " - " +
                cityWeather.GetTemperatureString(cityWeather.GetCurrentTemperature());
        cityWidgetItem->setText(cityTempStr.c_str());
        cityWidgetItem->setBackgroundColor(QColor(220, 220, 220));
        ui->_locationListWidget->addItem(cityWidgetItem);
    }

    onListSelectionChanged();

    this->setCursor(saveCursor);
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
    CAddCityDialog addCityDialog(this);

    addCityDialog.ShowDialog();

    auto cityName = addCityDialog.GetCityName();
    auto countryName = addCityDialog.GetCountryName();
    if (!cityName.empty() && !countryName.empty())
    {
        _cityNameList.push_back(CLocationWeather(cityName, countryName));

        UpdateWeatherList();
    }
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
