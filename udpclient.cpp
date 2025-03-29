// UDPClient.cpp
#include "udpclient.h"
#include <QHostAddress>
#include<QScreen>
#include<QPixmap>
#include<QBuffer>
#include<QTimer>
using namespace std;
QTimer *timer;
UDPClient::UDPClient(QObject *parent) : QObject(parent), udpSocket(new QUdpSocket(this)) {
    connect(udpSocket, &QUdpSocket::readyRead, this, &UDPClient::onReadyRead);

}

void UDPClient::connectToServer(const QHostAddress &address, quint16 port) {
    //绑定端口号
    udpSocket->connectToHost(address, port);
    this->ip=address;
    this->port=port;
    thread=new QThread;
    pixthread=new QThread;
    //绑定线程
    this->moveToThread(thread);
    connect(thread,&QThread::started,this,&UDPClient::sendMessage);
    thread->start();

    mutex=new QMutex;
}
#include<QApplication>
void UDPClient::sendMessage() {
    while(1)
    {

            for(int i=1;i<=5;i++)imageque.emplace_back(QApplication::primaryScreen()->grabWindow(0).toImage());



            while(!imageque.empty()){

                QByteArray scaledByteArray;
                QBuffer scaledBuffer(&scaledByteArray);
                scaledBuffer.open(QIODevice::WriteOnly);

                //改变尺寸并且保存
                imageque.head().scaled(1920/3,1080/3,Qt::KeepAspectRatio, Qt::SmoothTransformation).save(&scaledBuffer, "PNG");

                int totalSize = scaledByteArray.size();//总数据长度
                qDebug() << totalSize;
                int packetSize = 400;//步长

                // 计算包的数量，确保向上取整
                int numberOfPackets = (totalSize + packetSize - 1) / packetSize;

                //QByteArray packet;
                qDebug()<<"包的总数8到10为正常，既是12w到13.9w"<<numberOfPackets;
                for (int i = 0; i <numberOfPackets; ++i) {
                    int start = i * packetSize;
                    int end=0;
                    if(start+packetSize!=totalSize)end=start+packetSize;
                    else end=totalSize-1;
                    // 发送数据报
                    udpSocket->writeDatagram(scaledByteArray.mid(start, end-start), QHostAddress(this->ip), port);
                    //qDebug()<<scaledByteArray.mid(start, end-start).size();

                    // 每发送一个包，打印一些调试信息以便排查问题
                    // qDebug() << "Sent packet " << i << " of size " << packet.size();
                }
                QThread::msleep(100);
                // 定义结束标志
                QByteArray endPacket = "\r\n";

                imageque.pop_front();
                // 发送方在发送完所有数据包后发送结束标志
                udpSocket->writeDatagram(endPacket, QHostAddress(this->ip), this->port);

                emit ts();
                //QThread::msleep(1000);
            }
    }
}

void UDPClient::onReadyRead()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        emit messageReceived(QString(datagram));
    }
}
#include<QApplication>
void UDPClient::getpix()
{


    // 将缩放后的图片转换为字节数组
    while(1){
        imageque.emplace_back(QApplication::primaryScreen()->grabWindow(0).toImage());
        qDebug()<<"图片\n";
        //emit ts();
    }

}

