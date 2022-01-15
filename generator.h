#ifndef GENERATOR_H
#define GENERATOR_H

#include <QDialog>
#include <QPoint>
#include <QMouseEvent>

namespace Ui {
class generator;
}

class generator : public QDialog
{
    Q_OBJECT

public:
    explicit generator(QWidget *parent = nullptr);
    ~generator();

private slots:
    void on_exit_clicked();

    void on_genpass_clicked();

    void on_copy_clicked();

private:
    Ui::generator *ui;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

    QVector<QChar> Generate(int length);
};

#endif // GENERATOR_H
