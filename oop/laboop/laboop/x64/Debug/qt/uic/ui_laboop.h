/********************************************************************************
** Form generated from reading UI file 'laboop.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABOOP_H
#define UI_LABOOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_laboopClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *laboopClass)
    {
        if (laboopClass->objectName().isEmpty())
            laboopClass->setObjectName("laboopClass");
        laboopClass->resize(600, 400);
        menuBar = new QMenuBar(laboopClass);
        menuBar->setObjectName("menuBar");
        laboopClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(laboopClass);
        mainToolBar->setObjectName("mainToolBar");
        laboopClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(laboopClass);
        centralWidget->setObjectName("centralWidget");
        laboopClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(laboopClass);
        statusBar->setObjectName("statusBar");
        laboopClass->setStatusBar(statusBar);

        retranslateUi(laboopClass);

        QMetaObject::connectSlotsByName(laboopClass);
    } // setupUi

    void retranslateUi(QMainWindow *laboopClass)
    {
        laboopClass->setWindowTitle(QCoreApplication::translate("laboopClass", "laboop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class laboopClass: public Ui_laboopClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABOOP_H
