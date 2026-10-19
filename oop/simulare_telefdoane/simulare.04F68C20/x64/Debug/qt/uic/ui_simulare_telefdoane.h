/********************************************************************************
** Form generated from reading UI file 'simulare_telefdoane.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE_TELEFDOANE_H
#define UI_SIMULARE_TELEFDOANE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simulare_telefdoaneClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *simulare_telefdoaneClass)
    {
        if (simulare_telefdoaneClass->objectName().isEmpty())
            simulare_telefdoaneClass->setObjectName("simulare_telefdoaneClass");
        simulare_telefdoaneClass->resize(600, 400);
        menuBar = new QMenuBar(simulare_telefdoaneClass);
        menuBar->setObjectName("menuBar");
        simulare_telefdoaneClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(simulare_telefdoaneClass);
        mainToolBar->setObjectName("mainToolBar");
        simulare_telefdoaneClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(simulare_telefdoaneClass);
        centralWidget->setObjectName("centralWidget");
        simulare_telefdoaneClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(simulare_telefdoaneClass);
        statusBar->setObjectName("statusBar");
        simulare_telefdoaneClass->setStatusBar(statusBar);

        retranslateUi(simulare_telefdoaneClass);

        QMetaObject::connectSlotsByName(simulare_telefdoaneClass);
    } // setupUi

    void retranslateUi(QMainWindow *simulare_telefdoaneClass)
    {
        simulare_telefdoaneClass->setWindowTitle(QCoreApplication::translate("simulare_telefdoaneClass", "simulare_telefdoane", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simulare_telefdoaneClass: public Ui_simulare_telefdoaneClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE_TELEFDOANE_H
