#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simulare_telefdoane.h"

class simulare_telefdoane : public QMainWindow
{
    Q_OBJECT

public:
    simulare_telefdoane(QWidget *parent = nullptr);
    ~simulare_telefdoane();

private:
    Ui::simulare_telefdoaneClass ui;
};

