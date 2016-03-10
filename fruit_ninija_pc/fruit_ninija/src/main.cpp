#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/qml/main.qml"));

   return app.exec();
}

/*
int main(int argc, char **argv)
{
    QQuickView *view;
    QGuiApplication *application;
    QGuiApplication stackApp(argc, argv);
    QQuickView stackView;
    application = &stackApp;
    view = &stackView;
	view->setTitle("cmos-message");
    view->create();
    QPlatformNativeInterface *native = QGuiApplication::platformNativeInterface();
    native->setWindowProperty(view->handle(), "statusBarVisable", "true");
   	native->setWindowProperty(view->handle(), "statusBarStyle", "transblack");

    qmlRegisterType<ConversationTime>("ConversationTime",1,0,"ConversationTime");
    qmlRegisterType<MsgHandler>("MsgHandler",1,0,"MsgHandler");
    qmlRegisterType<MsgUtils>("MsgUtils",1,0,"MsgUtils");

    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->requestActivate();       
    view->raise();
    //view->showFullScreen();
	
    return application->exec();
}
*/
