#ifndef REGISTERNEWDATABASE_H
#define REGISTERNEWDATABASE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class RegisterNewDatabase;
}

class RegisterNewDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterNewDatabase(QWidget *parent = nullptr);
    ~RegisterNewDatabase();

private slots:
    void on_cancel_clicked();

    void on_next_clicked();

    void on_passwordcheck_stateChanged(int arg1);

private:
    Ui::RegisterNewDatabase *ui;
};

#endif // REGISTERNEWDATABASE_H
