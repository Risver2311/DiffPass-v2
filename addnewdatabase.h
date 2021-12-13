#ifndef ADDNEWDATABASE_H
#define ADDNEWDATABASE_H

#include <QObject>
#include <QCryptographicHash>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

#include "mainwindow.h"

class addnewdatabase : public QObject
{
    Q_OBJECT

public:
    addnewdatabase(QByteArray password, QByteArray passwordcorrect);
};

#endif // ADDNEWDATABASE_H
