#ifndef PASSMAN_H
#define PASSMAN_H

#include <QObject>

class passman : public QObject
{
    Q_OBJECT
public:
    explicit passman(QObject *parent = nullptr);

signals:
};

#endif // PASSMAN_H
