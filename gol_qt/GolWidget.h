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
    using PlayGroundT = PlayGround<3>;
    std::unique_ptr<PlayGroundT> pg;

    void draw_gol_grid(Grid<3>::SharedGridPtr grid);

    int h = 15;
    int w = 15;
    int scale = 40;
    int epoch = 50;
    QTimer timer = QTimer(this);
};
}
}
