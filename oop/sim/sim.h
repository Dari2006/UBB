#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim.h"

class sim : public QMainWindow
{
    Q_OBJECT

public:
    sim(QWidget *parent = nullptr);
    ~sim();

private:
    Ui::simClass ui;
};

