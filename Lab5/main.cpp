#include <QtWidgets>
#include <iostream>
#include <fstream>

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSqlDatabase>

#include "mainwindow.h"
using namespace std;

int main(int argc, char *argv[])
{
    //qDebug() << QSqlDatabase::drivers();
    QApplication app(argc, argv);

    MainWindow mainWin;

    mainWin.show();
    return app.exec();













    return 0;
}
