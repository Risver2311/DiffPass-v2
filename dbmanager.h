#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>

#include "ui_signup.h"


class dbManager
{
public:
    dbManager();

    void Registration(QString, QString);
    int reg = 0;

private:
    bool check = true;
};

#endif // DBMANAGER_H
