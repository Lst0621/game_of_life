#pragma once
#include <QApplication>
#include <QGridLayout>
#include <QtCore>
#include <QtGui>

#include <QWidget>
#include <QtGui>
#include <memory>

#include "Playground.h"

namespace lst {
namespace gol {
class MyWidget : public QWidget {
   public:
    MyWidget();
    virtual ~MyWidget();

   protected:
    void paintEvent(QPaintEvent *event);

   private:
    std::unique_ptr<PlayGround> pg;

    void draw_gol_grid(const Grid &grid);

    int h = 90;
    int w = 90;
    int scale = 10;
    int epoch = 100;
    QTimer timer = QTimer(this);
};
}
}
