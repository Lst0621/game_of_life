#include "GolWidget.h"
namespace lst {
namespace gol {
void MyWidget::paintEvent(QPaintEvent* event) {
    LOG(INFO) << "Paint Event starts";

    // create a QPainter and pass a pointer to the device.
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.drawRect(QRect(0, 0, scale * h, scale * w));

    int run_no_show = 20;
    for (int i = 0; i < run_no_show; i++) {
        pg->run();
    }
    pg->run([this](Grid<3>::SharedGridPtr grid) { draw_gol_grid(grid); });
    LOG(INFO) << "Paint Event ends";
}

void MyWidget::draw_gol_grid(Grid<3>::SharedGridPtr grid) {
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    auto cells = grid->get_live_cells();
    std::vector<std::vector<int>> m_xy(w, std::vector<int>(w));
    std::vector<std::vector<int>> m_yz(w, std::vector<int>(w));
    std::vector<std::vector<int>> m_xz(w, std::vector<int>(w));
    // std::map<std::array<int,2>,int> m_yz;
    // std::map<std::array<int,2>,int> m_xz;
    int max_cnt = 1;
    for (const auto& cell : cells) {
        int x = cell[0];
        int y = cell[1];
        int z = cell[2];
        int& xy_cnt = m_xy[x][y];
        int& yz_cnt = m_yz[y][z];
        int& xz_cnt = m_xz[x][z];
        xy_cnt++;
        yz_cnt++;
        xz_cnt++;
        max_cnt = std::max({max_cnt, xy_cnt, yz_cnt, xz_cnt});
        // painter.drawRect(QRect(scale * x, scale * y, scale, scale));
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < h; j++) {
            int xy = m_xy[i][j];
            int yz = m_yz[i][j];
            int xz = m_xz[i][j];
            auto get_color_fac = [=](int cnt) {
                float ratio = cnt / float(max_cnt);
                float curve = 1;
                return 1 - pow(1 - ratio, curve);
            };
            /**
            auto color =
                QColor(255 * get_color_fac(xy), 255 * get_color_fac(yz),
                       255 * get_color_fac(xz));
                       **/
            auto color = QColor(255 * get_color_fac(xy), 0, 0);
            painter.setBrush(QBrush(color, Qt::SolidPattern));
            painter.drawRect(QRect(scale * i, scale * j, scale, scale));
        }
    }
}

MyWidget::MyWidget() {
    {
        connect(&timer, &QTimer::timeout, this,
                QOverload<>::of(&MyWidget::update));
        timer.start(epoch);

        this->setFixedSize(w * scale, h * scale);
        pg = std::make_unique<PlayGroundT>(std::array<int, 3>{w, w, w},
                                           get_shared_pt<VectorGrid<3>>);
    }
}

MyWidget::~MyWidget() {
}
}
}