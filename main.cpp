#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if (QCoreApplication::arguments().contains("--test-play")) {
        w.setTestMode(true);
    }
    w.show();
    return a.exec();
}
