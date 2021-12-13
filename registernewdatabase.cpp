#include "registernewdatabase.h"
#include "ui_registernewdatabase.h"

RegisterNewDatabase::RegisterNewDatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterNewDatabase)
{
    ui->setupUi(this);

    ui->label_3->setStyleSheet(
    "QWidget:disabled{color: #FFFFFF;}"
    "QWidget{color: red;}");
    //ui->label_3->hide();
}

RegisterNewDatabase::~RegisterNewDatabase()
{
    delete ui;
}

void RegisterNewDatabase::on_next_clicked()
{
    QByteArray password = ui -> password -> text().toUtf8();
    QByteArray passwordcorrect = ui -> passwordcorrect -> text().toUtf8();
    int length = ui->password->text().length();

    if(password == passwordcorrect)
    {
        ui ->label_3->setEnabled(false);
        if(length >= 6)
            addnewdatabase(password, passwordcorrect);
        this -> close();

    }
    else
    {
        ui ->label_3->setEnabled(true);
    }
}

void RegisterNewDatabase::on_cancel_clicked()
{
    this -> close();
}



void RegisterNewDatabase::on_passwordcheck_stateChanged(int arg1)
{
    if(arg1)
    {
        ui ->password -> setEchoMode(QLineEdit::Normal);
        ui ->passwordcorrect -> setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui ->password -> setEchoMode(QLineEdit::Password);
        ui ->passwordcorrect -> setEchoMode(QLineEdit::Password);
    }
}
