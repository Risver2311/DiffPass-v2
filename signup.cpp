#include "signup.h"
#include "ui_signup.h"
#include "dbmanager.h"

#include <QMessageBox>

class signup;

signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

signup::~signup()
{
    delete ui;
}

void signup::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->position().x();
    m_nMouseClick_Y_Coordinate = event->position().y();
}

void signup::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().x() - m_nMouseClick_X_Coordinate, event->globalPosition().y() - m_nMouseClick_Y_Coordinate);
}


void signup::on_exit_clicked()
{
    this->close();
}


void signup::on_pushButton_clicked()
{
    dbManager db;
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString password2 = ui->lineEdit_3->text();

    if(username.length() < 6 || password.length() < 6)
    {
        QMessageBox::about(this, "error", "Your login or password is too short");
    }

    else if(password != password2)
    {
        QMessageBox::about(this, "error", "Password and confirm password does not match");
    }

    else if(username.length() >= 6 && password.length() >= 6 && password == password2)
    {
        db.Registration(username, password);
        switch(db.reg)
        {
            case 1:
                QMessageBox::about(this, "Username", "Username Already Exist!");
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                break;
            case 2:
                QMessageBox::about(this, "Registration", "Registration successful");
                this->close();
                break;
        }

    }
}

