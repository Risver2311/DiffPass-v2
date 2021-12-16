#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QPoint>
#include <QMouseEvent>

#include "signupform.h"


namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_exit_clicked();

    void on_pushButton_clicked();

private:
    Ui::signup *ui;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};

#endif // SIGNUP_H
