/********************************************************************************
** Form generated from reading UI file 'simulare3.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE3_H
#define UI_SIMULARE3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simulare3Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *simulare3Class)
    {
        if (simulare3Class->objectName().isEmpty())
            simulare3Class->setObjectName("simulare3Class");
        simulare3Class->resize(600, 400);
        menuBar = new QMenuBar(simulare3Class);
        menuBar->setObjectName("menuBar");
        simulare3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(simulare3Class);
        mainToolBar->setObjectName("mainToolBar");
        simulare3Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(simulare3Class);
        centralWidget->setObjectName("centralWidget");
        simulare3Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(simulare3Class);
        statusBar->setObjectName("statusBar");
        simulare3Class->setStatusBar(statusBar);

        retranslateUi(simulare3Class);

        QMetaObject::connectSlotsByName(simulare3Class);
    } // setupUi

    void retranslateUi(QMainWindow *simulare3Class)
    {
        simulare3Class->setWindowTitle(QCoreApplication::translate("simulare3Class", "simulare3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simulare3Class: public Ui_simulare3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE3_H
