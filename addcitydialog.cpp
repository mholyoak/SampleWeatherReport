#include "addcitydialog.h"
#include "ui_addcitydialog.h"

CAddCityDialog::CAddCityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddCityDialog)
{
    ui->setupUi(this);
}

CAddCityDialog::~CAddCityDialog()
{
    delete ui;
}
