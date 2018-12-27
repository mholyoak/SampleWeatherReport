#ifndef WEATHERWIDGETITEM_H
#define WEATHERWIDGETITEM_H

#include <QWidget>

namespace Ui {
class CWeatherWidgetItem;
}

class CWeatherWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit CWeatherWidgetItem(QWidget *parent = nullptr);
    ~CWeatherWidgetItem();

    void SetWeather(const QPixmap& icon, const std::string& city, float temp);

private:
    Ui::CWeatherWidgetItem *ui;
};

#endif // WEATHERWIDGETITEM_H
