#pragma once
#include <QApplication>
#include <QGridLayout>
#include <QtCore>
#include <QtGui>

#include <QWidget>
#include <QtGui>
#include <memory>

#include "Grid.h"
#include "Playground.h"
#include "VectorGrid.h"

namespace lst {
namespace gol {
class MyWidget : public QWidget {
   public:
    MyWidget();
    virtual ~MyWidget();

   protected:
    void paintEvent(QPaintEvent *event);

   private:
    using PlayGroundT = PlayGround<2>;
    std::unique_ptr<PlayGroundT> pg;

    void draw_gol_grid(Grid<2>::SharedGridPtr grid);

    int h = 200;
    int w = 200;
    int scale = 4;
    int epoch = 100;
    QTimer timer = QTimer(this);
};
}
}
