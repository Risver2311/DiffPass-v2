#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

#include "signup.h"
#include "login.h"
#include "dbmanager.h"
#include "generator.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void nextWindow(QString);

private slots:
    void on_login_clicked();
    void on_signup_clicked();

    void on_remove_clicked();
    void on_add_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_settings_clicked();
    void on_generator_clicked();

    void on_back_clicked();
    void on_imageButton_clicked();
    void on_changePassword_clicked();

private:
    Ui::MainWindow *ui;
    login * m_logWindow{nullptr};
    signup * m_regWindow{nullptr};
    generator * m_genWindow{nullptr};

    QString Bufferbase;
    QSqlDatabase m_db;
    QSqlTableModel * table;

    QByteArray encrypt(QByteArray plainText);
    QByteArray decrypt(QByteArray encryptedText);

    void refresh();
    void decodedLine();
    void changePassword(QByteArray ch_password);
};

#endif // MAINWINDOW_H
