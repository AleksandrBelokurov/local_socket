#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDataStream>
#include <QLocalSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    void setQmlobj(QObject* obj);

public slots:
    void handleConnect(const QString &msg);
    void handleDisconnect(const QString &msg);
    void sendRequest(const QString &msg);

private slots:
    void handleStateChanged(int state);
    void readResponse();
    void displayError(QLocalSocket::LocalSocketError socketError);

private:
    QLocalSocket *socket;
    QObject* qmlobj_;

};

#endif // CLIENT_H
