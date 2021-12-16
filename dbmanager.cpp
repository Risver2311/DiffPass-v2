#include <QMessageBox>

#include "dbmanager.h"


dbManager::dbManager()
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
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
    QString password = pass;

    QSqlQuery qry;

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
        qry.prepare("CREATE TABLE "+ username +"(website_address CHAR(255), username CHAR(255), password CHAR(255))");
        qry.exec();

        qry.prepare("INSERT INTO users (username, password)" "VALUES (:username, :password)");
        qry.bindValue(":username", username);
        qry.bindValue(":password", password);

        if(qry.exec())
            reg = 2;
    }
}
