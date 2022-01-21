#include <QMessageBox>
#include <QCryptographicHash>
#include <QSqlError>

#include "dbmanager.h"

dbManager::dbManager()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setUserName("root");
    m_db.setPassword("");
    m_db.setDatabaseName("DiffPass");

    if(m_db.open())
    {
        qDebug("Otwarta");
    }
    else
    {
        qDebug("Nie otwarto");
        qDebug() << m_db.lastError();
    }
}

void dbManager::Registration(QString usr, QString pass)
{
    QString username = usr;
    QByteArray password = pass.toUtf8();

    QCryptographicHash *hash = new QCryptographicHash(QCryptographicHash::Md5);
    hash->addData(password);
    password = hash->result().toHex();

    QSqlQuery qry(m_db);

    qry.prepare("SELECT username FROM users WHERE username = :username");
    qry.bindValue(":username", username);
    qry.exec();

    while(qry.next())
    {
        QString usernameDB = qry.value("username").toString();

        if(username == usernameDB)
        {
            check = false;
            reg = 1;
            break;
        }
    }

    if(check)
    {
        qry.prepare("CREATE TABLE "+ username +"(id INTEGER AUTO_INCREMENT PRIMARY KEY, url CHAR(255), email CHAR(255), password CHAR(255))");
        qry.exec();

        qry.prepare("INSERT INTO users (username, password)" "VALUES (:username, :password)");
        qry.bindValue(":username", username);
        qry.bindValue(":password", password);

        if(qry.exec())
            reg = 2;
    }
}

void dbManager::Login(QString usr, QString pass)
{
    QString username = usr;
    QByteArray password = pass.toUtf8();

    QCryptographicHash *hash = new QCryptographicHash(QCryptographicHash::Md5);
    hash->addData(password);
    password = hash->result().toHex();

    QSqlQuery qry(m_db);

    qry.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    qry.bindValue(":username", username);
    qry.bindValue(":password", password);

    if(qry.exec())
    {
        while(qry.next())
            log++;
    }

}
