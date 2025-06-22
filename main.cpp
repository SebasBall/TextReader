#include "mainwindow.h"
#include <csignal>
#include <QApplication>

void handleSigTerm(int)
{
    QCoreApplication::quit();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::signal(SIGTERM, handleSigTerm);

    MainWindow w;
    if (QCoreApplication::arguments().contains("--test-play")) {
        w.setTestMode(true);
    }
    w.show();
    return a.exec();
}
