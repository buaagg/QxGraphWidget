#include "mainwindow.h"
#include <QApplication>
#include <QStatusBar>
#include "qxgraphwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.statusBar()->hide();

    w.setCentralWidget( new QxGraphWidget() );

    w.show();
    return a.exec();
}
