#ifndef WEATHERDETAILDIALOG_H
#define WEATHERDETAILDIALOG_H

#include "locationweather.h"

#include <QDialog>

namespace Ui {
class CWeatherDetailDialog;
}

// Dialog to show weather details for a city
class CWeatherDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CWeatherDetailDialog(QWidget *parent = nullptr);
    ~CWeatherDetailDialog();

    // Displays the dialog with weather details
    void ShowDetail(const CLocationWeather& locationWeather);
protected:
      void paintEvent(QPaintEvent* event) override;

private:
    std::shared_ptr<Ui::CWeatherDetailDialog> ui;
};

#endif // WEATHERDETAILDIALOG_H
