#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_laboop.h"

class laboop : public QMainWindow
{
    Q_OBJECT

public:
    laboop(QWidget *parent = nullptr);
    ~laboop();

private:
    Ui::laboopClass ui;
};

