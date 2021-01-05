#include <glog/logging.h>
#include <QtWidgets/QApplication>
#include <iostream>

#include "GolWidget.h"

using namespace lst::gol;

int main(int argc, char *argv[]) {
    google::InstallFailureSignalHandler();
    std::cout << "Game of Life" << std::endl;
    QApplication app(argc, argv);
    MyWidget2 myWidget;
    myWidget.show();
    return app.exec();
}
