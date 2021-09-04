#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QList<QObject*> ol = engine.rootObjects();

    Client client;
    client.setQmlobj(ol.first());
    QObject::connect(ol.first(), SIGNAL(qmlSignalConnect(QString)),
                         &client, SLOT(handleConnect(QString)));
    QObject::connect(ol.first(), SIGNAL(qmlSignalDisconnect(QString)),
                         &client, SLOT(handleDisconnect(QString)));
    QObject::connect(ol.first(), SIGNAL(qmlSignalSend(QString)),
                         &client, SLOT(sendRequest(QString)));

    return app.exec();
}
