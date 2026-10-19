#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simulare2.h"

class simulare2 : public QMainWindow
{
    Q_OBJECT

public:
    simulare2(QWidget *parent = nullptr);
    ~simulare2();

private:
    Ui::simulare2Class ui;
};

