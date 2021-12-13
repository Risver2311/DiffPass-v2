#include "addnewdatabase.h"

addnewdatabase::addnewdatabase(QByteArray password, QByteArray passwordcorrect)
{
    QCryptographicHash *hash = new QCryptographicHash(QCryptographicHash::Md5);
    QByteArray key = generator().Generate().toUtf8();
    hash -> addData(key);
    key = hash -> result().toHex();

    QByteArray masterkey = password+key;
    hash -> addData(masterkey);
    masterkey = hash -> result().toHex();

    QFile file("key.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << key;
    file.close();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("remotemysql.com");
    db.setUserName("F5fMShnnbI");
    db.setPassword("EL9RqMWWwr");
    db.setDatabaseName("F5fMShnnbI");
    db.setPort(3306);
    db.open();

    QSqlQuery query;
    query.prepare("INSERT INTO users (userkey)" "VALUE (:userkey)");
    query.bindValue(":userkey", masterkey);
    query.exec();
        //emit closewindow(1);
}

