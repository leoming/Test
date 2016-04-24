#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include "chessgame.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<CChessGame>("ChessGame",1,0,"ChessGame");
    qRegisterMetaType<BYTE>();
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
