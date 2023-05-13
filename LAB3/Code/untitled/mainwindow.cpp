#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <unistd.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Mybutton1_clicked()
{
    if(ui->LED1->isChecked() == true)
    {
        ui->label_1->setEnabled(true);
    }
    else
    {
        ui->label_1->setEnabled(false);
    }
    if(ui->LED2->isChecked() == true)
    {
        ui->label_2->setEnabled(true);
    }
    else
    {
        ui->label_2->setEnabled(false);
    }
    if(ui->LED3->isChecked() == true)
    {
        ui->label_3->setEnabled(true);
    }
    else
    {
        ui->label_3->setEnabled(false);
    }
    if(ui->LED4->isChecked() == true)
    {
        ui->label_4->setEnabled(true);
    }
    else
    {
        ui->label_4->setEnabled(false);
    }
}
int Rcount = 0;
int Times = 0;
QTimer *timer;
void MainWindow::on_LED_Switching_clicked()
{
    Rcount = 0;
    Times = (ui->TIme_count_text->toPlainText()).toInt();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(switchingLED()));
    timer->start(1000);
}

void MainWindow::switchingLED()
{
    if (Rcount == Times * 2 - 1)
    {
        timer->stop();
    }
    ui->label_1 ->setEnabled(!ui->label_1->isEnabled());
    ui->LED1->setChecked(!ui->LED1->isChecked());
    ui->label_2->setEnabled(!ui->label_2->isEnabled());
    ui->LED2->setChecked(!ui->LED2->isChecked());
    ui->label_3->setEnabled(!ui->label_3->isEnabled());
    ui->LED3->setChecked(!ui->LED3->isChecked());
    ui->label_4->setEnabled(!ui->label_4->isEnabled());
    ui->LED4->setChecked(!ui->LED4->isChecked());
    Rcount +=1;

}

void MainWindow::on_TIme_count_text_destroyed()
{
}
