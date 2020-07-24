#include "mainwindow.h"
#include<QCoreApplication>
#include <QApplication>
#include<QSplashScreen>
#include<QTimer>
#include <QDebug>
#include<opencv2/opencv.hpp>
#include<QtGui>
#include<QStyleFactory>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    qApp->setStyle(QStyleFactory::create("fusion"));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(15,15,15));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
    palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(palette);
    */

    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

   // qApp->setPalette(darkPalette);

    /*
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(142,45,197));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    qApp->setPalette(p);
    */

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/icons/splashScreen3.png"));
    splash->show();
    Qt::Alignment bottomCenter = Qt::AlignCenter | Qt::AlignBottom;
    splash->showMessage(QObject::tr("Loading modules..."),bottomCenter, Qt::black);
    splash->setFont(QFont("Time New Roman",14,QFont::Bold));
/*

        Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
            splash->showMessage(QObject::tr("Setting up the main window..."),
                                   topRight, Qt::white);
            splash->showMessage(QObject::tr("Loading modules..."),
                                       topRight, Qt::white);
            splash->showMessage(QObject::tr("Establishing connections..."),
                                       topRight, Qt::white);

*/
    MainWindow w;
    QTimer::singleShot(5000,splash,SLOT(close()));
    QTimer::singleShot(5000,&w,SLOT(show()));
    QTimer::singleShot(5000,splash,SLOT(delete));
    //w.show();

   //splash->finish(&w);
   //delete splash;

    return a.exec();
}
