#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtGui>
#include <QAbstractItemModel>
#include <QCryptographicHash>
#include "qaesencryption.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    m_logWindow = new login(this);
    m_regWindow = new signup(this);
    m_genWindow = new generator(this);

    connect(m_logWindow,&login::LoginSuccess, this, &MainWindow::nextWindow);

}

MainWindow::~MainWindow()
{
    encodedLine();
    delete ui;
}

void MainWindow::on_login_clicked()
{
    m_logWindow->show();
}

void MainWindow::on_signup_clicked()
{
    m_regWindow->show();
}

void MainWindow::nextWindow(QString base)
{
    ui->stackedWidget->setCurrentIndex(1);
    Bufferbase = base;

    m_db.setDatabaseName("DiffPass.sqlite");
    table = new QSqlTableModel(this, m_db);

    table->setTable(Bufferbase);
    table->select();
    ui->tableView->setModel(table);
    ui->tableView->setColumnHidden (0,true);
    decodedLine();
}

void MainWindow::on_remove_clicked()
{
    if (ui->tableView->selectionModel()->hasSelection())
    {
        int addressId = ui->tableView->selectionModel()->currentIndex().row();
        table->removeRows(addressId, 1);
        table->submitAll();
        refresh();
    }
}

void MainWindow::on_add_clicked()
{
    QString url = ui->recordUrl->text();
    QString email = ui->recordMail->text();
    QString password = ui->recordPass->text();

    QSqlQuery qry(m_db);

    qry.prepare("INSERT INTO "+Bufferbase+"(url, email, password)" "VALUES(:url, :email, :password)");
    qry.bindValue(":url", url);
    qry.bindValue(":email", email);
    qry.bindValue(":password", password);

    if(qry.exec())
    {
        ui->recordUrl->clear();
        ui->recordMail->clear();
        ui->recordPass->clear();
        table->submitAll();
        refresh();
    }

    else
    {
        qDebug() << qry.lastError();
    }
}

QByteArray MainWindow::encoding(QByteArray inputStr)
{
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QString key = "test";
    QString iv("test");

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray encodedText = encryption.encode(inputStr, hashKey, hashIV);

    return encodedText;
}

QString MainWindow::decoding(QByteArray inputStr)
{
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QString key = "test";
    QString iv("test");

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray decodedText = encryption.decode(inputStr, hashKey, hashIV);
    QString decodedString = QString(encryption.removePadding(decodedText));

    return decodedString;
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    int column = index.column();
    QString text = index.sibling(row, column).data().toString();
    auto clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);
}

void MainWindow::decodedLine()
{
    for(int row = 0; row < table->rowCount(); row++)
    {
        QByteArray pass = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString().toUtf8();
        pass = QByteArray::fromBase64(pass);
        QString passdecoded = decoding(pass);
        ui->tableView->model()->setData(ui->tableView->model()->index(row, 3), passdecoded);
        table->submitAll();
    }
}

void MainWindow::refresh()
{
    table->setTable(Bufferbase);
    table->select();
    ui->tableView->setModel(table);
    ui->tableView->setColumnHidden (0,true);
}

void MainWindow::encodedLine()
{
    for(int row = 0; row < table->rowCount(); row++)
    {
        QByteArray pass = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString().toUtf8();
        QByteArray passencoded = encoding(pass).toBase64();
        ui->tableView->model()->setData(ui->tableView->model()->index(row, 3), passencoded);
        table->submitAll();
    }
}

void MainWindow::on_generator_clicked()
{
     m_genWindow->show();
}

