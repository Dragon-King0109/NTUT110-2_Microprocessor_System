#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_TIme_count_text_destroyed();

    void on_LED_Switching_clicked();

    void switchingLED();

private:
    Ui::MainWindow *ui;
    QString getCountString;
};

#endif // MAINWINDOW_H
