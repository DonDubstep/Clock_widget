#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/src/icon.ico")); // Укажите путь к иконке

    w.show();
    return a.exec();
}
