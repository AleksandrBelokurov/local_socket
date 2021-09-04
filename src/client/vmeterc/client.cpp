#include <QtWidgets>
#include <QtNetwork>
#include "client.h"

Client::Client(QObject *parent)
    : QObject(parent),
      socket(new QLocalSocket(this))
{
    connect(socket, &QLocalSocket::readyRead, this, &Client::readResponse);
    connect(socket, &QLocalSocket::errorOccurred, this, &Client::displayError);
    connect(socket, &QLocalSocket::stateChanged, this, &Client::handleStateChanged);
}

void Client::setQmlobj(QObject *obj)
{
    qmlobj_ = obj;
}

void Client::handleConnect(const QString &msg)
{
    if (socket->isOpen())
        return;
    QObject *label = qmlobj_->findChild<QObject*>("lConnectStatus");
    if (label)
        label->setProperty("text", msg);
    QObject *textInput = qmlobj_->findChild<QObject*>("SocketPath");
    if (textInput)
        socket->connectToServer(textInput->property("text").toString());
}

void Client::handleDisconnect(const QString &msg)
{
    if (!socket->isOpen())
        return;
    QObject *label = qmlobj_->findChild<QObject*>("lConnectStatus");
    if (label)
        label->setProperty("text", msg);
    socket->close();
}

void Client::sendRequest(const QString &msg)
{
    if (socket->isOpen()) {
        socket->write(msg.toLatin1());
    } else {
        QObject *label = qmlobj_->findChild<QObject*>("tResponse");
        if (label) {
            label->setProperty("text", "server is not connected\n"
                               "unable answer");
            label->setProperty("color", "black");
        }
    }
}

void Client::handleStateChanged(int state)
{
    QObject *label = qmlobj_->findChild<QObject*>("lConnectStatus");
    if (!label)
        return;
    if (state == QLocalSocket::UnconnectedState) {
        socket->close();
        label->setProperty("text", "Unconnected");
        label->setProperty("color", "red");
    }
    else if (state == QLocalSocket::ConnectedState) {
        label->setProperty("text", "Connected");
        label->setProperty("color", "dark green");
    }
}

void Client::readResponse()
{
//    qDebug() << socket->bytesAvailable();
    QString answer(socket->readAll());
    QObject *label = qmlobj_->findChild<QObject*>("tResponse");
    if (!label)
        return;
    std::string stdstr = answer.toStdString();
    int tt = stdstr.find("ok");
    if (tt >= 0) {
        label->setProperty("color", "dark green");
    } else label->setProperty("color", "black");
    label->setProperty("text", answer);
}

void Client::displayError(QLocalSocket::LocalSocketError socketError)
{
    QObject *label = qmlobj_->findChild<QObject*>("tResponse");
    if (!label)
        return;
    label->setProperty("color", "black");
    switch (socketError) {
    case QLocalSocket::ServerNotFoundError:
        label->setProperty("text", tr("The host was not found. Please make sure\n"
                                      "that the server is running and that the\n"
                                      "server path is correct."));
        break;
    case QLocalSocket::ConnectionRefusedError:
        label->setProperty("text", tr("The connection was refused by the peer.\n"
                                      "Make sure the server is running,\n"
                                      "and check that the path "
                                      "is correct."));
        break;
    case QLocalSocket::PeerClosedError:
        break;
    default:
        label->setProperty("text", tr("The following error occurred:\n%1.")
                           .arg(socket->errorString()));
        break;
    }
}

