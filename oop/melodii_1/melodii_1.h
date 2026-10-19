#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_melodii_1.h"

class melodii_1 : public QMainWindow
{
    Q_OBJECT

public:
    melodii_1(QWidget *parent = nullptr);
    ~melodii_1();

private:
    Ui::melodii_1Class ui;
};

