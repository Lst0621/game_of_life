#pragma once
#include <QApplication>
#include <QGridLayout>
#include <QGuiApplication>
#include <QtCore>
#include <QtGui>

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

#include <QWidget>
#include <QtGui>
#include <memory>

#include "Grid.h"
#include "Playground.h"
#include "VectorGrid.h"

namespace lst {
namespace gol {
extern template class lst::gol::VectorGrid<3>;
extern template class lst::gol::PlayGround<3>;

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

class MyWidget2 : public QWidget {
   public:
    MyWidget2();
    virtual ~MyWidget2();

   protected:
    void paintEvent(QPaintEvent *event);

   private:
    using PlayGroundT = PlayGround<3>;
    std::unique_ptr<PlayGroundT> pg;
    void draw_gol_grid(Grid<3>::SharedGridPtr grid);
    std::map<Grid<3>::CoorType, Qt3DCore::QEntity *> cubes;

    int w = 8;
    int epoch = 70;
    QTimer timer = QTimer(this);
};
}  // namespace gol

}  // namespace lst
