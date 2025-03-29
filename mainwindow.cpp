#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include<QPixmap>
#include<QBuffer>
#include <QImageReader>
#include <QThreadPool>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << QThreadPool::globalInstance()->maxThreadCount();
    ui->setupUi(this);
    timer=new QTimer(this);
    udpsize=10;
    client =new UDPClient[udpsize];

    for(int i=0;i<udpsize;i++)
    {
        client[i].connectToServer(QHostAddress("192.168.198.1"), 12345+i);
       connect(&client[i],&UDPClient::ts,this,&MainWindow::tslots);
    }
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);
    timer->start(1000);
    pixcnt = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SendButton_clicked()
{
    // 发送消息
    QString messageToSend = ui->SendEdit->text();
    //client.sendMessage(messageToSend);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);
    //ui->RecieveEdit->append("\n客户端："+messageToSend);
}


void MainWindow::on_ClearButton_clicked()
{
    ui->RecieveEdit->clear();
}


void MainWindow::on_SendClearButton_clicked()
{
    ui->SendEdit->clear();
}


void MainWindow::on_captureButton_clicked()
{
    //emit starcapture();
}


void MainWindow::on_pushButton_clicked()
{
   // static int cnt = 0;
    // 截取屏幕内容
    // QScreen *screen = QGuiApplication::primaryScreen();
    // if(!screen){
    //     qDebug() << "无法获取屏幕内容";
    //     return;
    // }
    // QPixmap screenshot = screen->grabWindow(0);


    // ui->screenshot->setPixmap(screenshot);
    // ui->screenshot->resize(screenshot.size());

    // //cnt++;
    // ui->fankui->setText(QString::number(cnt));
}

void MainWindow::tslots()
{
   //ui->RecieveEdit->append("客户端发送一张图片\n");
    pixcnt+=1;
    // if(pixcnt%60==0)
    //     ui->RecieveEdit->append(QString::number(pixcnt)+"发送图片\n");
}
void MainWindow::isslot(const QByteArray &data){
    Q_UNUSED(data);
    // QByteArray  byteArray=data;

    // QBuffer buffer(&byteArray);
    // buffer.open(QIODevice::ReadOnly);

    // QImageReader imageReader(&buffer);
    // QImage image = imageReader.read();
    // ui->RecieveEdit->append("123\n");
    // if (!image.isNull())
    // {
    //     // 将QImage转换为QPixmap
    //     QPixmap pixmap = QPixmap::fromImage(image);
    //     // 设置QLabel的Pixmap
    //     ui->screenshot->clear();
    //     ui->screenshot->setPixmap(pixmap);
    // }
}

void MainWindow::onTimeout()
{
    //QString messageToSend = ui->SendEdit->text();
    // for(int i=0;i<udpsize;i++)
    //     client[i].sendMessage();

    ui->RecieveEdit->append("fps:" + QString::number(pixcnt));
    pixcnt = 0;

}
