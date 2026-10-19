/********************************************************************************
** Form generated from reading UI file 'practicOOP.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRACTICOOP_H
#define UI_PRACTICOOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_practicOOPClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *practicOOPClass)
    {
        if (practicOOPClass->objectName().isEmpty())
            practicOOPClass->setObjectName("practicOOPClass");
        practicOOPClass->resize(600, 400);
        menuBar = new QMenuBar(practicOOPClass);
        menuBar->setObjectName("menuBar");
        practicOOPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(practicOOPClass);
        mainToolBar->setObjectName("mainToolBar");
        practicOOPClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(practicOOPClass);
        centralWidget->setObjectName("centralWidget");
        practicOOPClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(practicOOPClass);
        statusBar->setObjectName("statusBar");
        practicOOPClass->setStatusBar(statusBar);

        retranslateUi(practicOOPClass);

        QMetaObject::connectSlotsByName(practicOOPClass);
    } // setupUi

    void retranslateUi(QMainWindow *practicOOPClass)
    {
        practicOOPClass->setWindowTitle(QCoreApplication::translate("practicOOPClass", "practicOOP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class practicOOPClass: public Ui_practicOOPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRACTICOOP_H
