/********************************************************************************
** Form generated from reading UI file 'sim.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIM_H
#define UI_SIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *simClass)
    {
        if (simClass->objectName().isEmpty())
            simClass->setObjectName("simClass");
        simClass->resize(600, 400);
        menuBar = new QMenuBar(simClass);
        menuBar->setObjectName("menuBar");
        simClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(simClass);
        mainToolBar->setObjectName("mainToolBar");
        simClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(simClass);
        centralWidget->setObjectName("centralWidget");
        simClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(simClass);
        statusBar->setObjectName("statusBar");
        simClass->setStatusBar(statusBar);

        retranslateUi(simClass);

        QMetaObject::connectSlotsByName(simClass);
    } // setupUi

    void retranslateUi(QMainWindow *simClass)
    {
        simClass->setWindowTitle(QCoreApplication::translate("simClass", "sim", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simClass: public Ui_simClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIM_H
