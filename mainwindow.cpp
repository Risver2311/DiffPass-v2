#include <QMessageBox>
#include <QtGui>
#include <QCryptographicHash>
#include <openssl/aes.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"


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
};

MainWindow::~MainWindow()
{
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

//Manager
void MainWindow::nextWindow(QString base)
{
    ui->stackedWidget->setCurrentIndex(1);
    Bufferbase = base;

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setUserName("root");
    m_db.setPassword("");
    m_db.setDatabaseName("DiffPass");

    if(!m_db.open())
        qDebug() << m_db.lastError();

    decodedLine();
}

void MainWindow::on_remove_clicked()
{
    if (ui->tableWidget->selectionModel()->hasSelection())
    {
        table = new QSqlTableModel(this, m_db);
        table->setTable(Bufferbase);
        table->select();
        int addressId = ui->tableWidget->selectionModel()->currentIndex().row();
        table->removeRows(addressId, 1);
        table->submitAll();
        ui->tableWidget->removeRow(addressId);
        refresh();
    }
}

void MainWindow::on_add_clicked()
{
    QString url = ui->recordUrl->text();
    QString email = ui->recordMail->text();
    QByteArray password = ui->recordPass->text().toUtf8();
    password = encrypt(password).toBase64();

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
    }

    else
    {
        qDebug() << qry.lastError();
    }

    refresh();
}

void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    int row = index.row();
    int column = index.column();
    QString text = index.sibling(row, column).data().toString();
    auto clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);
}

QByteArray MainWindow::encrypt(QByteArray plainText)
{
    QByteArray passphrase = QByteArray::fromBase64("pE4B5J5u18U55BTJho//Fioy2bEURa5W/o7HrO1O7/s=");
    QByteArray myiv = QByteArray::fromBase64("Gi9kSb/a5f0h7Mb+sRWQdQ==");

    unsigned char* Key = (unsigned char*) passphrase.data();
    unsigned char* IV = (unsigned char*) myiv.data();

    AES_KEY* AesKey = new AES_KEY();
    AES_set_encrypt_key(Key, 256, AesKey);

    int UserDataSize = (int)plainText.size();
    int RequiredPadding = (AES_BLOCK_SIZE - (UserDataSize % AES_BLOCK_SIZE));
    for(int i=0; i < RequiredPadding; i++) {
        plainText.push_back('\0');
    }

    unsigned char * UserData = (unsigned char*) plainText.data();
    int UserDataSizePadded = (int)plainText.size();

    unsigned char EncryptedData[UserDataSizePadded];
    memset(EncryptedData, 0, UserDataSizePadded*sizeof(unsigned char));
    AES_cbc_encrypt(UserData, EncryptedData, UserDataSizePadded, (const AES_KEY*)AesKey, IV, AES_ENCRYPT);

    QByteArray encrypted = QByteArray(reinterpret_cast<char*>(EncryptedData), UserDataSizePadded);

    return encrypted;
}

QByteArray MainWindow::decrypt(QByteArray encryptedText)
{
    QByteArray passphrase = QByteArray::fromBase64("pE4B5J5u18U55BTJho//Fioy2bEURa5W/o7HrO1O7/s=");
    QByteArray myiv = QByteArray::fromBase64("Gi9kSb/a5f0h7Mb+sRWQdQ==");

    unsigned char* Key = (unsigned char*) passphrase.data();
    unsigned char* IV = (unsigned char*) myiv.data();

    AES_KEY* AesDecryptKey = new AES_KEY();
    AES_set_decrypt_key(Key, 256, AesDecryptKey);

    unsigned char DecryptedData[encryptedText.size()];
    memset(DecryptedData, 0, encryptedText.size()*sizeof(unsigned char));
    AES_cbc_encrypt((unsigned char*) encryptedText.data(), DecryptedData, encryptedText.size(), (const AES_KEY*)AesDecryptKey, IV, AES_DECRYPT);

    QByteArray decrypted = QByteArray(reinterpret_cast<char*>(DecryptedData), encryptedText.size());

    return decrypted;
}

void MainWindow::refresh()
{
    QSqlQuery qry(m_db);
    QString sBuffer = "SELECT url, email, password FROM "+Bufferbase;

    int rowCount = ui->tableWidget->rowCount();

    for(int row = 0; row < rowCount; row++)
    {
        int row1 = 0;
        ui->tableWidget->removeRow(row1);
        row1++;
    }

    if(qry.exec(sBuffer))
    {
        int rowCount = 0;
        while(qry.next())
        {
            QTableWidgetItem * url = new QTableWidgetItem;
            QTableWidgetItem * email = new QTableWidgetItem;
            QTableWidgetItem * password = new QTableWidgetItem;

            url->setText(qry.value(0).toString());
            email->setText(qry.value(1).toString());
            QByteArray pass = qry.value(2).toString().toUtf8();
            pass = QByteArray::fromBase64(pass);
            QString passdecoded = decrypt(pass);
            password->setText(passdecoded);

            ui->tableWidget->insertRow(rowCount);
            ui->tableWidget->setItem(rowCount, 0, url);
            ui->tableWidget->setItem(rowCount, 1, email);
            ui->tableWidget->setItem(rowCount, 2, password);

            rowCount++;
        }
    }

    qry.clear();
}

void MainWindow::decodedLine()
{
    QSqlQuery qry(m_db);
    QString sBuffer = "SELECT url, email, password FROM "+Bufferbase;

    ui->tableWidget->setColumnCount(3);
    QStringList labels;
    labels << "Url" << "E-mail" << "Password";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    if(qry.exec(sBuffer))
    {
        int rowCount = 0;
        while(qry.next())
        {
            QTableWidgetItem * url = new QTableWidgetItem;
            QTableWidgetItem * email = new QTableWidgetItem;
            QTableWidgetItem * password = new QTableWidgetItem;

            url->setText(qry.value(0).toString());
            email->setText(qry.value(1).toString());
            QByteArray pass = qry.value(2).toString().toUtf8();
            pass = QByteArray::fromBase64(pass);
            QString passdecoded = decrypt(pass);
            password->setText(passdecoded);

            ui->tableWidget->insertRow(rowCount);
            ui->tableWidget->setItem(rowCount, 0, url);
            ui->tableWidget->setItem(rowCount, 1, email);
            ui->tableWidget->setItem(rowCount, 2, password);

            rowCount++;
        }
    }
    qry.clear();
}

void MainWindow::on_generator_clicked()
{
     m_genWindow->show();
}

void MainWindow::on_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->hello->setText("Hi "+Bufferbase+" !");
}

//User Panel
void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_imageButton_clicked()
{
    //QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
}


void MainWindow::on_changePassword_clicked()
{
    QByteArray ch_password = ui->ch_password->text().toUtf8();
    QByteArray ch_password_2 = ui->ch_password_2->text().toUtf8();

    if(ch_password == ch_password_2)
    {
        changePassword(ch_password);
        ui->ch_password->clear();
        ui->ch_password_2->clear();
    }

    else
    {
        QMessageBox::about(this, "error", "Password and confirm password does not match");
    }
}

void MainWindow::changePassword(QByteArray ch_password)
{
    QCryptographicHash * hash = new QCryptographicHash(QCryptographicHash::Md5);
    hash->addData(ch_password);
    ch_password = hash->result().toHex();

    QSqlQuery qry(m_db);

    qDebug() << qry.lastError();

    qry.prepare("UPDATE users SET password =:password WHERE username=:username");
    qry.bindValue(":password", ch_password);
    qry.bindValue(":username", Bufferbase);
    qry.exec();
}
