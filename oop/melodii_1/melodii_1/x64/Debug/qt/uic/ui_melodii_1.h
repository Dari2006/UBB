/********************************************************************************
** Form generated from reading UI file 'melodii_1.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MELODII_1_H
#define UI_MELODII_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_melodii_1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *melodii_1Class)
    {
        if (melodii_1Class->objectName().isEmpty())
            melodii_1Class->setObjectName("melodii_1Class");
        melodii_1Class->resize(600, 400);
        menuBar = new QMenuBar(melodii_1Class);
        menuBar->setObjectName("menuBar");
        melodii_1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(melodii_1Class);
        mainToolBar->setObjectName("mainToolBar");
        melodii_1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(melodii_1Class);
        centralWidget->setObjectName("centralWidget");
        melodii_1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(melodii_1Class);
        statusBar->setObjectName("statusBar");
        melodii_1Class->setStatusBar(statusBar);

        retranslateUi(melodii_1Class);

        QMetaObject::connectSlotsByName(melodii_1Class);
    } // setupUi

    void retranslateUi(QMainWindow *melodii_1Class)
    {
        melodii_1Class->setWindowTitle(QCoreApplication::translate("melodii_1Class", "melodii_1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class melodii_1Class: public Ui_melodii_1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MELODII_1_H
