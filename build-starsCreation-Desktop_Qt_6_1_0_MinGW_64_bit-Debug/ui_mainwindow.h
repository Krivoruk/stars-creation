/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNEW;
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLineEdit *timeText;
    QLineEdit *MomentX;
    QLineEdit *ImpulseX;
    QLineEdit *MassText;
    QLineEdit *MomentY;
    QLineEdit *ImpulseY;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(800, 600);
        actionNEW = new QAction(MainWindow);
        actionNEW->setObjectName(QString::fromUtf8("actionNEW"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(200, 10, 121, 21));
        timeText = new QLineEdit(centralwidget);
        timeText->setObjectName(QString::fromUtf8("timeText"));
        timeText->setGeometry(QRect(200, 30, 121, 21));
        MomentX = new QLineEdit(centralwidget);
        MomentX->setObjectName(QString::fromUtf8("MomentX"));
        MomentX->setGeometry(QRect(350, 10, 141, 26));
        ImpulseX = new QLineEdit(centralwidget);
        ImpulseX->setObjectName(QString::fromUtf8("ImpulseX"));
        ImpulseX->setGeometry(QRect(350, 30, 141, 26));
        MassText = new QLineEdit(centralwidget);
        MassText->setObjectName(QString::fromUtf8("MassText"));
        MassText->setGeometry(QRect(350, 50, 141, 26));
        MomentY = new QLineEdit(centralwidget);
        MomentY->setObjectName(QString::fromUtf8("MomentY"));
        MomentY->setGeometry(QRect(510, 10, 141, 26));
        ImpulseY = new QLineEdit(centralwidget);
        ImpulseY->setObjectName(QString::fromUtf8("ImpulseY"));
        ImpulseY->setGeometry(QRect(510, 30, 141, 26));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNEW->setText(QCoreApplication::translate("MainWindow", "NEW", nullptr));
#if QT_CONFIG(tooltip)
        actionNEW->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>new text</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
