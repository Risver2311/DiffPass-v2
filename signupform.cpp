#include <QMessageBox>

#include "signupform.h"
#include "signup.h"
#include "dbmanager.h"


signupForm::signupForm(Ui::signup* ui)
{
    dbManager db;
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString password2 = ui->lineEdit_3->text();

    if(username.length() < 6 || password.length() < 6)
    {
        QMessageBox::about(QDialog::find(0), "error", "Your login or password is too short");
    }

    else if(password != password2)
    {
        QMessageBox::about(QDialog::find(0), "error", "Password and confirm password does not match");
    }

    else if(username.length() >= 6 && password.length() >= 6 && password == password2)
    {
        db.Registration(username, password);
        switch(db.reg)
        {
            case 1:
                QMessageBox::about(QDialog::find(0), "Username", "Username Already Exist!");
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                break;
            case 2:
                qDebug("przechodze dalej");
                break;
        }

    }
}
