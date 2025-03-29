// UDPClient.h
#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include<QThread>
#include<QMutex>
#include<QQueue>
class UDPClient : public QObject
{
    Q_OBJECT

public:
    explicit UDPClient(QObject *parent = nullptr);

public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void sendMessage();
    void onReadyRead();
    void getpix();


signals:
    void messageReceived(const QString &message);
    void ts();
    void is(const QByteArray &data);
private:
    QUdpSocket *udpSocket;
    QByteArray testdata;
    QThread* thread;
    QThread*pixthread;
    QMutex*mutex;
    QHostAddress ip;
    quint16 port;
    QQueue<QImage>imageque;

};

#endif // UDPCLIENT_H
