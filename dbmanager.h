#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>

#include "mainwindow.h"

class dbManager : public QObject
{

public:
    dbManager();

    void Registration(QString, QString);
    void Login(QString, QString);
    int reg = 0;
    int log = 0;

private:
    bool check = true;
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
