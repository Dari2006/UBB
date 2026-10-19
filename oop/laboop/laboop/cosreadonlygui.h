#pragma once
#include <QWidget>
#include <QPainter>
//#include "observer.h"
#include "planificare.h"

class CosReadOnlyGUI : public QWidget, public Observer {
private:
    Planificare& plan; 

public:
    CosReadOnlyGUI(Planificare& p) : plan(p) {
        plan.addObserver(this);
    }
 
    void update() override {
        QWidget::update(); 
    }

    void paintEvent(QPaintEvent* ev) override {
        QWidget::paintEvent(ev);
        QPainter p{ this };

        size_t nrElemente = plan.dim(); 

        for (size_t i = 0; i < nrElemente; i++) {
            int x = rand() % (width() - 40);
            int y = rand() % (height() - 40);

            p.drawRect(x, y, 30, 30);
        }
    }

    ~CosReadOnlyGUI() {
        plan.removeObserver(this);
    }
};