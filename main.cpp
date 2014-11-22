#include "View/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View::MainWindow w;
    w.showMaximized();

    return a.exec();
}
