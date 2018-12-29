#include "addcitydialog.h"
#include "ui_addcitydialog.h"

#include "openweathermapreporter.h"
#include "curlrestrequester.h"

CAddCityDialog::CAddCityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddCityDialog)
{
    ui->setupUi(this);

    auto connected = QObject::connect(ui->_buttonBox, SIGNAL(accepted()), this, SLOT(onSaveButtonClicked()));
    assert(connected);
    connected = QObject::connect(ui->_findButton, SIGNAL(clicked()), this, SLOT(onFindButtonClicked()));
    assert(connected);
    connected = QObject::connect(ui->_cityList, SIGNAL(itemSelectionChanged()), this, SLOT(onListSelectionChanged()));
    assert(connected);

    onListSelectionChanged();
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

std::string CAddCityDialog::GetCountryName() const
{
    return _countryName;
}

void CAddCityDialog::onSaveButtonClicked()
{
    _cityName = ui->_findCityEdit->text().toUtf8().constData();
    auto currentItem = ui->_cityList->currentItem();
    if (currentItem)
    {
        std::string cityCountry = currentItem->text().toUtf8().constData();

        // Parse city and country
        std::string delimiter(", ");
        auto delimitePos = cityCountry.find(delimiter);
        if (delimitePos != std::string::npos)
        {
            _cityName = cityCountry.substr(0, delimitePos);
            _countryName = cityCountry.substr(delimitePos + delimiter.size());
        }
    }
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


void CAddCityDialog::onListSelectionChanged()
{
    auto selectedRow = ui->_cityList->currentRow();
    ui->_buttonBox->button( QDialogButtonBox::Save )->setEnabled(selectedRow >= 0);
}
