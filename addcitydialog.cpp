#include "addcitydialog.h"
#include "ui_addcitydialog.h"

#include "openweathermapreporter.h"
#include "curlrestrequester.h"

CAddCityDialog::CAddCityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddCityDialog)
{
    ui->setupUi(this);

    auto connected = QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onSaveButtonClicked()));
    assert(connected);
    connected = QObject::connect(ui->_findButton, SIGNAL(clicked()), this, SLOT(onFindButtonClicked()));
    assert(connected);
}

CAddCityDialog::~CAddCityDialog()
{
    delete ui;
}

void CAddCityDialog::ShowDialog()
{
    exec();
}

std::string CAddCityDialog::GetCityName() const
{
    return _cityName;
}

void CAddCityDialog::onSaveButtonClicked()
{
    _cityName = ui->_findCityEdit->text().toUtf8().constData();
}

void CAddCityDialog::onFindButtonClicked()
{
    std::string findCity = ui->_findCityEdit->text().toUtf8().constData();
    if (!findCity.empty())
    {
        std::shared_ptr<IRestRequester> restRequester = std::make_shared<CCurlRestRequester>();
        COpenWeatherMapReporter weatherReporter(restRequester);

        auto cityList = weatherReporter.FindCity(findCity);

        for (auto city : cityList)
        {
            ui->_cityList->addItem(city.c_str());
        }
    }
}
