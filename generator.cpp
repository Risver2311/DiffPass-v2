#include <QClipboard>
#include <QVector>
#include <QString>
#include <QRandomGenerator>
#include <vector>

#include "generator.h"
#include "ui_generator.h"

QVector<QChar> lowercase  { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
QVector<QChar> uppercase  { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K','L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V','W', 'X', 'Y', 'Z'};
QVector<QChar> numbers  { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
QVector<QChar> specialchars  { '&', '~', '#', '-', '_', '$', '%', '*', '!', '?' };

generator::generator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::generator)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

generator::~generator()
{
    delete ui;
}

void generator::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->position().x();
    m_nMouseClick_Y_Coordinate = event->position().y();
}

void generator::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().x() - m_nMouseClick_X_Coordinate, event->globalPosition().y() - m_nMouseClick_Y_Coordinate);
}

void generator::on_exit_clicked()
{
    this->close();
}

void generator::on_genpass_clicked()
{
    QVector<QChar> password = Generate(ui->spinBox->value());
    QString pass;

    for(int i=0; i < password.size(); i++)
    {
        pass += password[i];
    }

    ui->lineEdit->setText(pass);
}

QVector<QChar> generator::Generate(int length)
{
    QVector<QChar> password(length);
    QVector<QChar> Symbols;

    if(ui->lowcase->isChecked() || ui->uppcase->isChecked() || ui->numbers->isChecked() || ui->symbols->isChecked())
    {
        if(ui->lowcase->isChecked())
        {
            Symbols += lowercase;
        }

        if(ui->uppcase->isChecked())
        {
            Symbols += uppercase;
        }

        if(ui->numbers->isChecked())
        {
            Symbols += numbers;
        }

        if(ui->symbols->isChecked())
        {
            Symbols += specialchars;
        }

        QRandomGenerator *rng = QRandomGenerator::global();

            for (int i = 0 ; i < length ; ++i)
            {
                int index = rng->bounded(Symbols.length());
                password[i] = Symbols[index];
            }
        ui->label_6->setText("");
    }

    else
    {
        ui->label_6->setText("select at least one option.");
    }

    return password;
}

void generator::on_copy_clicked()
{
    auto clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->lineEdit->text());
     ui->label_6->setText("copied");
}

