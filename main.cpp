#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon("./icon.png"));

    Register reg;
    reg.show();
    return a.exec();
}
