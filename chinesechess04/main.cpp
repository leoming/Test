#include<QGuiApplication>
#include<QtGui>
#include"topwidget.h"
#include<QTextCodec>


int main(int argc,char**argv)
{
    QApplication app(argc,argv);
    topwidget * w = new topwidget;
    w->show();

    return app.exec();
}
