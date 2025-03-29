#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QAudioInput>
#include <QAudioFormat>
//#include <QAudioDeviceInfo>
#include <QIODevice>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);






    MainWindow w;
    w.show();
    return a.exec();
}
