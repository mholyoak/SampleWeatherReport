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

private:
    Ui::CAddCityDialog *ui;
};

#endif // ADDCITYDIALOG_H
