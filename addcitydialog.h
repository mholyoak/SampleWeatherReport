#ifndef ADDCITYDIALOG_H
#define ADDCITYDIALOG_H

#include <QDialog>

namespace Ui {
class CAddCityDialog;
}

// Dialog to add a new city to get weather info
class CAddCityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAddCityDialog(QWidget *parent = nullptr);
    ~CAddCityDialog();

    void ShowDialog();

    // city selected by use empty if none selected
    std::string GetCityName() const;
    // country selected by use empty if none selected
    std::string GetCountryName() const;

private slots:
    void onSaveButtonClicked();
    void onFindButtonClicked();
    void onListSelectionChanged();

private:
    Ui::CAddCityDialog *ui;

    std::string _cityName;
    std::string _countryName;
};

#endif // ADDCITYDIALOG_H
