#include <QPixmap>

#include "mainwindow.h"
#include "welcomewindow.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint );
    QPixmap pic("icon.png");
    ui->logo->setPixmap(pic);

    ui->label->setStyleSheet("QWidget{color: #005500;}");
}

Register::~Register()
{
    delete ui;
}

void Register::on_next_clicked()
{
    RegisterNewDatabase newdatabase;

    if(ui->newbase->isChecked())
    {
        newdatabase.setModal(true);
        newdatabase.exec();
    }
}
