#ifndef WEATHERREPORTWINDOW_H
#define WEATHERREPORTWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "locationweather.h"

#include <vector>

namespace Ui {
class CWeatherReportWindow;
}

// Main weather window with list of city weather summaries
class CWeatherReportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CWeatherReportWindow(QWidget *parent = nullptr);
    ~CWeatherReportWindow();

private slots:
    // Event handlers
    void onDetailButtonclicked();
    void onAddButtonclicked();
    void onRemoveButtonclicked();
    void onListSelectionChanged();

private:
    Ui::CWeatherReportWindow *ui;

    std::vector<CLocationWeather>   _cityNameList;

    void UpdateWeatherList();
};

#endif // WEATHERREPORTWINDOW_H
