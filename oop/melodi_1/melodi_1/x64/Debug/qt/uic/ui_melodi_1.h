/********************************************************************************
** Form generated from reading UI file 'melodi_1.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MELODI_1_H
#define UI_MELODI_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_melodi_1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *melodi_1Class)
    {
        if (melodi_1Class->objectName().isEmpty())
            melodi_1Class->setObjectName("melodi_1Class");
        melodi_1Class->resize(600, 400);
        menuBar = new QMenuBar(melodi_1Class);
        menuBar->setObjectName("menuBar");
        melodi_1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(melodi_1Class);
        mainToolBar->setObjectName("mainToolBar");
        melodi_1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(melodi_1Class);
        centralWidget->setObjectName("centralWidget");
        melodi_1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(melodi_1Class);
        statusBar->setObjectName("statusBar");
        melodi_1Class->setStatusBar(statusBar);

        retranslateUi(melodi_1Class);

        QMetaObject::connectSlotsByName(melodi_1Class);
    } // setupUi

    void retranslateUi(QMainWindow *melodi_1Class)
    {
        melodi_1Class->setWindowTitle(QCoreApplication::translate("melodi_1Class", "melodi_1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class melodi_1Class: public Ui_melodi_1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MELODI_1_H
