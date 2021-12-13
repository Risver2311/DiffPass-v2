#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QClipboard>
#include <QVector>
#include <QString>
#include <QRandomGenerator>
#include <vector>

#include "mainwindow.h"

class generator : public QObject
{
    Q_OBJECT

public:
    generator();
    QString Generate();
};

#endif // GENERATOR_H
