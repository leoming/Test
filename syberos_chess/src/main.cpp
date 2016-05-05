/*
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
*/
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>

#include <SyberosGuiCache>
#include <cgui_application.h>
#include <cworkspace.h>
#include "chess_Workspace.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    qDebug() << "----------argc------------" << argc;
    qDebug() << "----------argv------------" << argv;
    return SYBEROS::SyberosGuiCache::qApplication(argc, argv, new Space());
}
