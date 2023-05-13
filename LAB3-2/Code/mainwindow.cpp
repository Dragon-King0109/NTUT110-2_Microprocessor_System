#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
// 7:6 15:14 19:20 23:25
using namespace std;

int gpio_export(unsigned int gpio);
int gpio_unexport(unsigned int gpio);

int gpio_set_value(unsigned int gpio, int value);
int gpio_set_dir(unsigned int gpio, string dirStatus);

QTimer *timer;
int speed;
bool timer_isTrigger;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gpio_export(396);
    gpio_export(255);
    gpio_export(429);
    gpio_export(427);
    gpio_set_dir(396, "out");
    gpio_set_dir(255, "out");
    gpio_set_dir(429, "out");
    gpio_set_dir(427, "out");
    ui->label_1->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    timer_isTrigger = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    gpio_unexport(396);
    gpio_unexport(255);
    gpio_unexport(429);
    gpio_unexport(427);
}

void MainWindow::on_Mybutton1_clicked()
{
    if (ui->LED1->isChecked() == true)
    {
        ui->label_1->setVisible(true);
        gpio_set_value(396, 1);
    }
    else
    {
        ui->label_1->setVisible(false);
        gpio_set_value(396, 0);
    }
    if (ui->LED2->isChecked() == true)
    {
        ui->label_2->setVisible(true);
        gpio_set_value(255, 1);
    }
    else
    {
        ui->label_2->setVisible(false);
        gpio_set_value(255, 0);
    }
    if (ui->LED3->isChecked() == true)
    {
        ui->label_3->setVisible(true);
        gpio_set_value(429, 1);
    }
    else
    {
        ui->label_3->setVisible(false);
        gpio_set_value(429, 0);
    }
    if (ui->LED4->isChecked() == true)
    {
        ui->label_4->setVisible(true);
        gpio_set_value(427, 1);
    }
    else
    {
        ui->label_4->setVisible(false);
        gpio_set_value(427, 0);
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    speed = 1500 - arg1 * 10;
}

void MainWindow::on_Switching_On_clicked()
{
    if(!timer_isTrigger){
        if(ui->LED1->isChecked()) ui->label_1->setVisible(true);
        else ui->label_1->setVisible(false);
        if(ui->LED2->isChecked()) ui->label_2->setVisible(true);
        else ui->label_2->setVisible(false);
        if(ui->LED3->isChecked()) ui->label_3->setVisible(true);
        else ui->label_3->setVisible(false);
        if(ui->LED4->isChecked()) ui->label_4->setVisible(true);
        else ui->label_4->setVisible(false);
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(switchingLED()));
        timer->start(speed);
        timer_isTrigger = true;
    }
}

void MainWindow::on_Switching_Off_clicked()
{
    if(timer_isTrigger){
        timer->stop();
        ui->label_1->setVisible(false);
        ui->LED1->setChecked(false);
        gpio_set_value(396, 0);
        ui->label_2->setVisible(false);
        ui->LED2->setChecked(false);
        gpio_set_value(255, 0);
        ui->label_3->setVisible(false);
        ui->LED3->setChecked(false);
        gpio_set_value(429, 0);
        ui->label_4->setVisible(false);
        ui->LED4->setChecked(false);
        gpio_set_value(427, 0);
        timer_isTrigger = false;
    }
}

void MainWindow::switchingLED()
{
    ui->label_1->setVisible(!ui->label_1->isVisible());
    ui->LED1->setChecked(!ui->LED1->isChecked());
    ui->label_2->setVisible(!ui->label_2->isVisible());
    ui->LED2->setChecked(!ui->LED2->isChecked());
    ui->label_3->setVisible(!ui->label_3->isVisible());
    ui->LED3->setChecked(!ui->LED3->isChecked());
    ui->label_4->setVisible(!ui->label_4->isVisible());
    ui->LED4->setChecked(!ui->LED4->isChecked());
    if (ui->LED1->isChecked() == true) gpio_set_value(396, 1);
    else gpio_set_value(396, 0);
    if (ui->LED2->isChecked() == true) gpio_set_value(255, 1);
    else gpio_set_value(255, 0);
    if (ui->LED3->isChecked() == true) gpio_set_value(429, 1);
    else gpio_set_value(429, 0);
    if (ui->LED4->isChecked() == true) gpio_set_value(427, 1);
    else gpio_set_value(427, 0);
    timer->start(speed);
}

int gpio_export(unsigned int gpio)
{
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;
}

int gpio_unexport(unsigned int gpio)
{
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;
}

int gpio_set_value(unsigned int gpio, int value)
{
    int fd;
    char buf[64];
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/value");
        return fd;
    }
    if (value == 0)
        write(fd, "0", 2);
    if (value == 1)
        write(fd, "1", 2);
    close(fd);
    return 0;
}

int gpio_set_dir(unsigned int gpio, string dirStatus)
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/direction");
        return fd;
    }

    if (dirStatus == "out")
        write(fd, "out", 4);
    else
        write(fd, "in", 3);

    close(fd);
    return 0;
}
