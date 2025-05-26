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
    connect(m_tcpSocket, &QTcpSocket::stateChanged, this, [this](QAbstractSocket::SocketState state){
        switch (state) {
        case QAbstractSocket::UnconnectedState:
            emit showMsg("UnconnectedState");
            break;
        case QAbstractSocket::HostLookupState:
            emit showMsg("HostLookupState");
            break;
        case QAbstractSocket::ConnectingState:
            emit showMsg("ConnectingState");
            break;
        case QAbstractSocket::ConnectedState:
            emit showMsg("ConnectedState");
            break;
        case QAbstractSocket::BoundState:
            emit showMsg("BoundState");
            break;
        case QAbstractSocket::ListeningState:
            emit showMsg("ListeningState");
            break;
        case QAbstractSocket::ClosingState:
            emit showMsg("ClosingState");
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

    emit signalUpdateLightsInfoDataParse(QJsonDocument(json).toJson());
}
