#include <QMessageBox>
#include <QCryptographicHash>
#include <QSqlError>

#include "dbmanager.h"

dbManager::dbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("DiffPass.sqlite");

    if(m_db.open())
    {
        qDebug("Otwarta");
    }
    else
    {
        qDebug("Nie otwarto");
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

    qDebug() << qry.lastError();

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
        qry.prepare("CREATE TABLE "+ username +"(id integer primary key,url CHAR(255), email CHAR(255), password CHAR)");
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
        qry.bindValue(":username", username);
        qry.bindValue(":password", password);

        while(qry.next())
            log++;
    }

}
