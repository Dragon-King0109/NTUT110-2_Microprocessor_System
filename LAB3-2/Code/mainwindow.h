#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    void on_Mybutton1_clicked();

    void on_Switching_On_clicked();

    void on_Switching_Off_clicked();

    void switchingLED();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QString getCountString;
};

#endif // MAINWINDOW_H
