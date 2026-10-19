#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicOOP.h"

class practicOOP : public QMainWindow
{
    Q_OBJECT

public:
    practicOOP(QWidget *parent = nullptr);
    ~practicOOP();

private:
    Ui::practicOOPClass ui;
};

