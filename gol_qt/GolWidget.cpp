#include "GolWidget.h"
namespace lst {
namespace gol {
void MyWidget::paintEvent(QPaintEvent *event) {
    // create a QPainter and pass a pointer to the device.
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawRect(QRect(0, 0, scale * h, scale * w));
    pg->run([this](Grid<2>::SharedGridPtr grid) { draw_gol_grid(grid); });
}

void MyWidget::draw_gol_grid(Grid<2>::SharedGridPtr grid) {
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    auto cells = grid->get_live_cells();
    for (const auto &cell : cells) {
        int x = cell[0];
        int y = cell[1];
        painter.drawRect(QRect(scale * x, scale * y, scale, scale));
    }
}

MyWidget::MyWidget() {
    {
        connect(&timer, &QTimer::timeout, this,
                QOverload<>::of(&MyWidget::update));
        timer.start(epoch);

        this->setFixedSize(w * scale, h * scale);
        pg = std::make_unique<PlayGroundT>(std::array<int, 2>{w, h},
                                           get_shared_pt<VectorGrid<2>>);
    }
}

MyWidget::~MyWidget() {
}
}
}