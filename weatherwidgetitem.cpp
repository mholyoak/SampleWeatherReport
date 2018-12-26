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
