#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopWidget>
#include <QMainWindow>
#include <QMessageBox>

#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Quit_Bt_clicked();

    void on_dial_valueChanged(int value);

    void on_dial_sliderMoved(int position);

    void on_XAxis_Bt_clicked();

    void on_YAxis_Bt_clicked();

    void on_Cursor_Bt_clicked();

    void on_pushButton_2_clicked();

    void on_Tracer_Bt_clicked();

private:
    Ui::MainWindow *ui;

    float HC;

    QCPItemTracer *cursor;
};

#endif // MAINWINDOW_H
