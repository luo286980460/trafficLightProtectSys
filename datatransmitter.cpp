#include "datatransmitter.h"
#include "qnetworkaccessmanager.h"
#include "qnetworkreply.h"
#include "qtimer.h"

DataTransmitter::DataTransmitter(QObject *parent)
    : QObject{parent}
{

}

bool DataTransmitter::executeTaskIsDone(e_dataTransmitterExecuteTask executeTask, QStringList args)
{
    switch (executeTask) {
    case e_dataTransmitterExecuteTask::TASK0:
        executeTask0(args.at(0));
        break;
    case e_dataTransmitterExecuteTask::TASK1:
        executeTask1();
        break;
    case e_dataTransmitterExecuteTask::TASK2:
        executeTask2();
        break;
    case e_dataTransmitterExecuteTask::TASK3:
        executeTask3();
        break;
    case e_dataTransmitterExecuteTask::TASK4:
        executeTask4();
        break;
    case e_dataTransmitterExecuteTask::TASK5:
        executeTask5();
        break;
    default:
        break;
    }
    return true;
    return true;
}

void DataTransmitter::post(QString url, QByteArray dataJson)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // 设置请求URL
    //QUrl url(url);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    // 发送POST请求
    QNetworkReply *reply = manager->post(request, dataJson);

    // 异步处理响应
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Response:" << reply->readAll();
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}

void DataTransmitter::initTimer()
{
    m_updataTimer = new QTimer;
    m_updataTimer->setInterval(1000);
    connect(m_updataTimer, &QTimer::timeout, this, [=](){
        post(m_url, m_data);
    });
    m_updataTimer->start();
}

void DataTransmitter::executeTask0(QString url)
{
    post(url, m_data);
}

void DataTransmitter::executeTask1()
{

}

void DataTransmitter::executeTask2()
{

}

void DataTransmitter::executeTask3()
{

}

void DataTransmitter::executeTask4()
{

}

void DataTransmitter::executeTask5()
{

}
