#ifndef MYUDPSERVER_H
#define MYUDPSERVER_H

#include <QObject>
#include <QTcpSocket>

class MyUdpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyUdpServer(QObject *parent = nullptr);
    void connectToHost(QString ip, int port);

signals:
    void showMsg(QString msg);
    void signalUpdateLightsInfoDataParse(QString data);


private slots:
    void readPendingDatagrams();// 读取接收到的数据

private:
    QTcpSocket* m_tcpSocket = nullptr;
};

#endif // MYUDPSERVER_H
