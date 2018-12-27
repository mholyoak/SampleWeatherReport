#ifndef WEATHERREPORTWINDOW_H
#define WEATHERREPORTWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include <list>

namespace Ui {
class CWeatherReportWindow;
}

class CWeatherReportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CWeatherReportWindow(QWidget *parent = nullptr);
    ~CWeatherReportWindow();

private:
    Ui::CWeatherReportWindow *ui;

    QListWidgetItem locationItem;
    QListWidgetItem locationItem2;
};

#endif // WEATHERREPORTWINDOW_H
