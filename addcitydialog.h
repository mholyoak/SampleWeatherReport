#ifndef ADDCITYDIALOG_H
#define ADDCITYDIALOG_H

#include <QDialog>

namespace Ui {
class CAddCityDialog;
}

class CAddCityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAddCityDialog(QWidget *parent = nullptr);
    ~CAddCityDialog();

    void ShowDialog();

    std::string GetCityName() const;

private slots:
    void onSaveButtonClicked();
    void onFindButtonClicked();

private:
    Ui::CAddCityDialog *ui;

    std::string _cityName;
};

#endif // ADDCITYDIALOG_H
