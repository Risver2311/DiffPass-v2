QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QTPLUGIN += qsqlite


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbmanager.cpp \
    generator.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    qaesencryption.cpp \
    signup.cpp

HEADERS += \
    dbmanager.h \
    generator.h \
    login.h \
    mainwindow.h \
    qaesencryption.h \
    signup.h

FORMS += \
    generator.ui \
    login.ui \
    mainwindow.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
