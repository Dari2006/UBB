/********************************************************************************
** Form generated from reading UI file 'simulare2.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE2_H
#define UI_SIMULARE2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simulare2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *simulare2Class)
    {
        if (simulare2Class->objectName().isEmpty())
            simulare2Class->setObjectName("simulare2Class");
        simulare2Class->resize(600, 400);
        menuBar = new QMenuBar(simulare2Class);
        menuBar->setObjectName("menuBar");
        simulare2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(simulare2Class);
        mainToolBar->setObjectName("mainToolBar");
        simulare2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(simulare2Class);
        centralWidget->setObjectName("centralWidget");
        simulare2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(simulare2Class);
        statusBar->setObjectName("statusBar");
        simulare2Class->setStatusBar(statusBar);

        retranslateUi(simulare2Class);

        QMetaObject::connectSlotsByName(simulare2Class);
    } // setupUi

    void retranslateUi(QMainWindow *simulare2Class)
    {
        simulare2Class->setWindowTitle(QCoreApplication::translate("simulare2Class", "simulare2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simulare2Class: public Ui_simulare2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE2_H
