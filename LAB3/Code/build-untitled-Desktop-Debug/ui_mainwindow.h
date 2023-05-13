/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *Mybutton1;
    QCheckBox *LED3;
    QCheckBox *LED4;
    QCheckBox *LED1;
    QCheckBox *LED2;
    QLabel *Time_count;
    QPushButton *LED_Switching;
    QTextEdit *TIme_count_text;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(615, 386);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Mybutton1 = new QPushButton(centralWidget);
        Mybutton1->setObjectName(QStringLiteral("Mybutton1"));
        Mybutton1->setGeometry(QRect(160, 220, 101, 25));
        LED3 = new QCheckBox(centralWidget);
        LED3->setObjectName(QStringLiteral("LED3"));
        LED3->setGeometry(QRect(160, 130, 92, 23));
        LED3->setChecked(false);
        LED4 = new QCheckBox(centralWidget);
        LED4->setObjectName(QStringLiteral("LED4"));
        LED4->setGeometry(QRect(160, 190, 92, 23));
        LED4->setChecked(false);
        LED1 = new QCheckBox(centralWidget);
        LED1->setObjectName(QStringLiteral("LED1"));
        LED1->setGeometry(QRect(160, 10, 92, 23));
        LED1->setChecked(false);
        LED2 = new QCheckBox(centralWidget);
        LED2->setObjectName(QStringLiteral("LED2"));
        LED2->setGeometry(QRect(160, 70, 92, 23));
        LED2->setChecked(false);
        Time_count = new QLabel(centralWidget);
        Time_count->setObjectName(QStringLiteral("Time_count"));
        Time_count->setGeometry(QRect(290, 120, 67, 17));
        LED_Switching = new QPushButton(centralWidget);
        LED_Switching->setObjectName(QStringLiteral("LED_Switching"));
        LED_Switching->setGeometry(QRect(290, 190, 131, 25));
        TIme_count_text = new QTextEdit(centralWidget);
        TIme_count_text->setObjectName(QStringLiteral("TIme_count_text"));
        TIme_count_text->setGeometry(QRect(290, 150, 141, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        label->setGeometry(QRect(40, 10, 101, 51));
        label->setPixmap(QPixmap(QString::fromUtf8("../LED.bmp")));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(false);
        label_2->setGeometry(QRect(40, 70, 101, 41));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../LED.bmp")));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(false);
        label_3->setGeometry(QRect(40, 120, 101, 51));
        label_3->setPixmap(QPixmap(QString::fromUtf8("../LED.bmp")));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setEnabled(false);
        label_4->setGeometry(QRect(40, 180, 101, 51));
        label_4->setPixmap(QPixmap(QString::fromUtf8("../LED.bmp")));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 615, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Mybutton1->setText(QApplication::translate("MainWindow", "LED Shining", Q_NULLPTR));
        LED3->setText(QApplication::translate("MainWindow", "LED3", Q_NULLPTR));
        LED4->setText(QApplication::translate("MainWindow", "LED4", Q_NULLPTR));
        LED1->setText(QApplication::translate("MainWindow", "LED1", Q_NULLPTR));
        LED2->setText(QApplication::translate("MainWindow", "LED2", Q_NULLPTR));
        Time_count->setText(QApplication::translate("MainWindow", "Times", Q_NULLPTR));
        LED_Switching->setText(QApplication::translate("MainWindow", "LED Switching", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
