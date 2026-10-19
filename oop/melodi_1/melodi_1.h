#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_melodi_1.h"

class melodi_1 : public QMainWindow
{
    Q_OBJECT

public:
    melodi_1(QWidget *parent = nullptr);
    ~melodi_1();

private:
    Ui::melodi_1Class ui;
};

