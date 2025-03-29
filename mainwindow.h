#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<udpclient.h>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SendButton_clicked();

    void on_ClearButton_clicked();

    void on_SendClearButton_clicked();

    void on_captureButton_clicked();
    void on_pushButton_clicked();
    void tslots();
    void isslot(const QByteArray &data);
    void onTimeout();

signals:
    void starcapture();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

   UDPClient* client;
    int pixcnt;
   int udpsize;
};
#endif // MAINWINDOW_H
