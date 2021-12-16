#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPoint>
#include <QMouseEvent>

#include "loginform.h"


namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_exit_clicked();

    void on_pushButton_clicked();

private:
    Ui::login *ui;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};

#endif // LOGIN_H
