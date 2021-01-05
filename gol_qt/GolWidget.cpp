#include "GolWidget.h"
#include <QGuiApplication>

#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qcameralens.h>

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qtexture.h>

#include <Qt3DCore/qaspectengine.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DRender/qrenderaspect.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
namespace lst {
namespace gol {

Qt3DCore::QEntity *add_cube(Qt3DCore::QEntity *rootEntity, float scale,
                            std::array<float, 3> translation) {
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();

    // CuboidMesh Transform
    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(scale);
    cuboidTransform->setTranslation(
        QVector3D(translation[0], translation[1], translation[2]));

    Qt3DExtras::QPhongMaterial *cuboidMaterial =
        new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setDiffuse(QColor(QRgb(0x66542)));
    //cuboidMaterial->setDiffuse(Qt::blue);

    // Cuboid
    Qt3DCore::QEntity *cuboidEntity = new Qt3DCore::QEntity(rootEntity);
    cuboidEntity->addComponent(cuboid);
    cuboidEntity->addComponent(cuboidMaterial);
    cuboidEntity->addComponent(cuboidTransform);
    cuboidEntity->setEnabled(false);
    return cuboidEntity;
}

void MyWidget::paintEvent(QPaintEvent *event) {
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
    for (const auto &cell : cells) {
        int x = cell[0];
        int y = cell[1];
        int z = cell[2];
        int &xy_cnt = m_xy[x][y];
        int &yz_cnt = m_yz[y][z];
        int &xz_cnt = m_xz[x][z];
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
                                           Grid<3>::get_shared_pt<VectorGrid>);
    }
}
MyWidget::~MyWidget() {
}

MyWidget2::~MyWidget2() {
}

void MyWidget2::paintEvent(QPaintEvent *event) {
    LOG(INFO) << "Paint Event starts";

    // create a QPainter and pass a pointer to the device.

    pg->run([this](Grid<3>::SharedGridPtr grid) { draw_gol_grid(grid); });
    LOG(INFO) << "Paint Event ends";
}

void MyWidget2::draw_gol_grid(Grid<3>::SharedGridPtr grid) {
    auto cells = grid->get_live_cells();

    for (const auto kv : cubes) {
        kv.second->setEnabled(false);
    }

    for (const auto &cell : cells) {
        if (cubes.count(cell)) {
            cubes.at(cell)->setEnabled(true);
        }
    }
}

MyWidget2::MyWidget2() {
    {
        connect(&timer, &QTimer::timeout, this,
                QOverload<>::of(&MyWidget::update));
        timer.start(epoch);

        // this->setFixedSize(w * scale, h * scale);
        pg = std::make_unique<PlayGroundT>(std::array<int, 3>{w, w, w},
                                           Grid<3>::get_shared_pt<VectorGrid>);

        Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
        view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
        QWidget *container = QWidget::createWindowContainer(view);
        QSize screenSize = view->screen()->size();
        container->setMinimumSize(QSize(200, 100));
        container->setMaximumSize(screenSize);

        QWidget *widget = this;
        QHBoxLayout *hLayout = new QHBoxLayout(widget);
        QVBoxLayout *vLayout = new QVBoxLayout();
        vLayout->setAlignment(Qt::AlignTop);
        hLayout->addWidget(container, 1);
        hLayout->addLayout(vLayout);

        widget->setWindowTitle(QStringLiteral("Basic shapes"));

        Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
        view->registerAspect(input);

        // Root entity
        Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

        // Camera
        Qt3DRender::QCamera *cameraEntity = view->camera();

        cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f,
                                                       0.1f, 1000.0f);
        cameraEntity->setPosition(QVector3D(-30, -30, -30));
        cameraEntity->setUpVector(QVector3D(0, 1, 0));
        cameraEntity->setViewCenter(QVector3D(0, 0, 0));

        Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
        Qt3DRender::QPointLight *light =
            new Qt3DRender::QPointLight(lightEntity);
        light->setColor("white");
        light->setIntensity(1);
        lightEntity->addComponent(light);
        Qt3DCore::QTransform *lightTransform =
            new Qt3DCore::QTransform(lightEntity);
        lightTransform->setTranslation(cameraEntity->position());
        lightEntity->addComponent(lightTransform);

        // For camera controls
        Qt3DExtras::QFirstPersonCameraController *camController =
            new Qt3DExtras::QFirstPersonCameraController(rootEntity);
        camController->setCamera(cameraEntity);

        // Set root object of the scene
        view->setRootEntity(rootEntity);
        int s = w;
        for (int i = 0; i < s; i++) {
            for (int j = 0; j < s; j++) {
                for (int k = 0; k < s; k++) {
                    auto ptr =
                        add_cube(rootEntity, 1.6,
                                 {float(i * 2), float(j * 2), float(k * 2)});
                    cubes[{i, j, k}] = ptr;
                }
            }
        }

        widget->show();
        widget->resize(1200, 800);
    }
}

}  // namespace gol
}  // namespace lst