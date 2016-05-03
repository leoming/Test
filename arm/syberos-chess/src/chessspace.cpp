#include <QtQml>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QUrl>
#include <QString>
#include <QRegExp>
#include <SyberosGuiCache>
#include <QDebug>
#include "chessgame.h"
#include "chessspace.h"

Space::Space(QObject *parent)
    : CWorkspace(parent)
{
}

Space::~Space()
{

}

void Space::onLaunchComplete(SYBEROS::CWorkspace::Option option, const QStringList &params)
{
    qDebug() << "--------------Params-------------" << params;
    switch (option)
    {
        case HOME:
        {
            break;
        }
        case URL:
        {
            break;
        }
        default:
            break;
    }

    qmlRegisterType<CChessGame>("ChessGame",1,0,"ChessGame");
    qRegisterMetaType<BYTE>();
    QQuickView *view = SYBEROS::SyberosGuiCache::qQuickView();
    view->create();
    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->requestActivate();       
    view->raise();
    view->showFullScreen();
    CWorkspace::onLaunchComplete(option, params);
}

