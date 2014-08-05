#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTranslator>
#include "appglobal.h"

void test();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // load stylesheet
    QFile file(":/stylesheet.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());

    // load translate
    QTranslator qtTranslator;
    qtTranslator.load("app_trans_ch.qm");
    a.installTranslator(&qtTranslator);


    MainWindow w;
    w.show();

	//for git test

    //test();
    return a.exec();
}
