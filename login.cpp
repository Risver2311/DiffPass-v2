#include "login.h"
#include "ui_login.h"
#include "dbmanager.h"
#include "passman.h"

#include <QMessageBox>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

login::~login()
{
    delete ui;
}

void login::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->position().x();
    m_nMouseClick_Y_Coordinate = event->position().y();
}

void login::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().x() - m_nMouseClick_X_Coordinate, event->globalPosition().y() - m_nMouseClick_Y_Coordinate);
}

void login::on_exit_clicked()
{
    this->close();
}

void login::on_pushButton_clicked()
{
    dbManager db;

    QString username = ui->username->text();
    QString password = ui->password->text();

    db.Login(username, password);
    if(db.log < 1)
        QMessageBox::about(this, "error", "Your login or password is not correct");
    if(db.log == 1)
    {
        emit LoginSuccess(username);
        this->close();
    }
}

