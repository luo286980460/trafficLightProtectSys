#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class MyTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpClient(QObject *parent = nullptr);
    void connectToHost(QString ip, int port);

signals:
    void signalUpdateLightsInfoDataParse(QString data);


private slots:
    void readPendingDatagrams();// 读取接收到的数据

private:
    QTcpSocket* m_tcpSocket = nullptr;
};

#endif // MYTCPCLIENT_H
