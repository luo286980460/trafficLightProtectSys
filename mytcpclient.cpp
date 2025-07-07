#include "mytcpclient.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

MyTcpClient::MyTcpClient(QObject *parent)
    : QObject{parent}
{

    m_tcpSocket = new QTcpSocket(this);
    // 连接 readyRead 信号到槽函数
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &MyTcpClient::readPendingDatagrams);
    connect(m_tcpSocket, &QTcpSocket::stateChanged, this, [](QAbstractSocket::SocketState state){
        switch (state) {
        case QAbstractSocket::UnconnectedState:
            qDebug() << ("camera UnconnectedState");
            break;
        case QAbstractSocket::HostLookupState:
            qDebug() << ("camera HostLookupState");
            break;
        case QAbstractSocket::ConnectingState:
            qDebug() << ("camera ConnectingState");
            break;
        case QAbstractSocket::ConnectedState:
            qDebug() << ("camera ConnectedState");
            break;
        case QAbstractSocket::BoundState:
            qDebug() << ("camera BoundState");
            break;
        case QAbstractSocket::ListeningState:
            qDebug() << ("camera ListeningState");
            break;
        case QAbstractSocket::ClosingState:
            qDebug() << ("camera ClosingState");
            break;
        default:
            break;
        }
    });

}

void MyTcpClient::connectToHost(QString ip, int port)
{
    // 绑定到指定端口
    m_tcpSocket->connectToHost(ip, port);
    // if () {
    //     qDebug() << "UDP Server started on port 7878";
    // } else {
    //     qDebug() << "Failed to bind UDP socket";
    // }



}

void MyTcpClient::readPendingDatagrams()
{
    QByteArray utfdata = m_tcpSocket->readAll();
    QJsonObject json;
    QJsonArray idArray;

    while(!utfdata.isEmpty()){
        if(utfdata.size() < 2){
            break;
        }

        QJsonObject light;
        int id = utfdata.at(0);
        int colorInt =  utfdata.at(1);
        QString color;

        switch(colorInt){
        case 0:
            color = "black";
            break;
        case 1:
            color = "red";
            break;
        case 2:
            color = "yellow";
            break;
        case 3:
            color = "green";
            break;
        case 4:
            color = "black";
            break;
        default:
            color = "black";
            break;
        }

        light.insert("id", id);
        light.insert("color", color);
        idArray << light;
        utfdata.remove(0,1);
        utfdata.remove(0,1);
    }

    json.insert("trafficlight_status", idArray);

    // qDebug() << json;

    emit signalUpdateLightsInfoDataParse(QJsonDocument(json).toJson());
}
