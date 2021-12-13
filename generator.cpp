#include "generator.h"
#include <QDebug>

QVector<QChar> lowercase  { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
QVector<QChar> uppercase  { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K','L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V','W', 'X', 'Y', 'Z'};
QVector<QChar> numbers  { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
QVector<QChar> specialchars  { '&', '~', '#', '-', '_', '$', '%', '*', '!', '?' };

generator::generator()
{

}

QString generator::Generate()
{
    QVector<QChar> Symbols;
    int length = 20;

    Symbols = lowercase+uppercase+numbers+specialchars;
    QVector<QChar> password(length);
    QRandomGenerator *rng = QRandomGenerator::global();

    for (int i = 0 ; i < length ; ++i)
    {
        int index = rng->bounded(Symbols.length());
        password[i] = Symbols[index];
    }

    QString pass;
    for(int i=0; i < password.size(); i++)
    {
        pass += password[i];
    }

    return pass;
}

