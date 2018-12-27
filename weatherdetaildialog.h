#ifndef WEATHERDETAILDIALOG_H
#define WEATHERDETAILDIALOG_H

#include "locationweather.h"

#include <QDialog>

namespace Ui {
class CWeatherDetailDialog;
}

class CWeatherDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CWeatherDetailDialog(QWidget *parent = nullptr);
    ~CWeatherDetailDialog();

    void ShowDetail(const CLocationWeather& locationWeather);

private:
    Ui::CWeatherDetailDialog *ui;
};

#endif // WEATHERDETAILDIALOG_H
