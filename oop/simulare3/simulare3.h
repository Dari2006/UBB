#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simulare3.h"

class simulare3 : public QMainWindow
{
    Q_OBJECT

public:
    simulare3(QWidget *parent = nullptr);
    ~simulare3();

private:
    Ui::simulare3Class ui;
};

