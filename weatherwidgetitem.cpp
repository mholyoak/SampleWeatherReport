#include "weatherwidgetitem.h"
#include "ui_weatherwidgetitem.h"

CWeatherWidgetItem::CWeatherWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWeatherWidgetItem)
{
    ui->setupUi(this);
}

CWeatherWidgetItem::~CWeatherWidgetItem()
{
    delete ui;
}

void CWeatherWidgetItem::SetWeather(const QPixmap& icon, const std::string& city, float temp)
{
    ui->_icon->setPixmap(icon);
    ui->_city->setText(city.c_str());
    ui->_temp->setText(std::to_string(temp).c_str());
}
