#include "screen.h"
#include "qjsonobject.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCoreApplication>
#include <QFile>

#define CFG_NAME "/cfg.json"
#define SCREEN_SEND_TEXT "http://%1:%2/screenOn/Text"

Screen::Screen(QObject *parent)
    : QObject{parent}
{
    init();
}


void Screen::post(QString url, QString jsonData)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = m_manager->post(request, jsonData.toUtf8());
    // 连接信号，处理响应
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            qDebug() << "Response:" << response;
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();  // 释放内存
    });
}

bool Screen::executeTaskIsDone(e_screenExecuteTask executeTask, QStringList args)
{
    switch (executeTask) {
    case e_screenExecuteTask::TASK0:
        executeTask0(args.at(0));
        break;
    case e_screenExecuteTask::TASK1:
        executeTask1();
        break;
    case e_screenExecuteTask::TASK2:
        executeTask2();
        break;
    case e_screenExecuteTask::TASK3:
        executeTask3();
        break;
    case e_screenExecuteTask::TASK4:
        executeTask4();
        break;
    case e_screenExecuteTask::TASK5:
        executeTask5();
        break;
    default:
        break;
    }
    return true;
}

void Screen::init()
{
    m_manager = new QNetworkAccessManager();

    QString cfgPath = QCoreApplication::applicationDirPath() + CFG_NAME;
    QFile file(cfgPath);

    if(!file.exists()){
        showMsg("配置文件不存在");
    }

    if(!file.open(QIODevice::ReadOnly)){
        showMsg("配置文件读取失败");
    }

    QJsonObject cfgJson = QJsonDocument::fromJson(file.readAll()).object();
    m_ip = cfgJson.value("screen").toObject().value("ip").toString();
    m_port = cfgJson.value("screen").toObject().value("port").toInt();
}


void Screen::executeTask0(QString content)
{
    QJsonObject json;

    json.insert("FontSize", 30);
    json.insert("Content", content);
    json.insert("AudioTimes", 1);
    json.insert("AudioContent", "1");
    json.insert("AudioSwitch", 0);
    json.insert("Audiovolume", 9);

    post(QString(SCREEN_SEND_TEXT).arg(m_ip).arg(m_port),
         QJsonDocument(json).toJson());

    emit showMsg("屏幕任务显示:  " + content);
}

void Screen::executeTask1()
{
    QJsonObject json;

    json.insert("FontSize", 30);
    json.insert("Content", "屏幕任务 1");
    json.insert("AudioTimes", 1);
    json.insert("AudioContent", "1");
    json.insert("AudioSwitch", 0);
    json.insert("Audiovolume", 9);

    post(QString(SCREEN_SEND_TEXT).arg(m_ip).arg(m_port),
         QJsonDocument(json).toJson());

    emit showMsg("屏幕任务 1");

}

void Screen::executeTask2()
{

    QJsonObject json;

    json.insert("FontSize", 30);
    json.insert("Content", "屏幕任务 2");
    json.insert("AudioTimes", 1);
    json.insert("AudioContent", "1");
    json.insert("AudioSwitch", 0);
    json.insert("Audiovolume", 9);

    post(QString(SCREEN_SEND_TEXT).arg(m_ip).arg(m_port),
         QJsonDocument(json).toJson());

    emit showMsg("屏幕任务 2");

}

void Screen::executeTask3()
{

    QJsonObject json;

    json.insert("FontSize", 30);
    json.insert("Content", "屏幕任务 3");
    json.insert("AudioTimes", 1);
    json.insert("AudioContent", "1");
    json.insert("AudioSwitch", 0);
    json.insert("Audiovolume", 9);

    post(QString(SCREEN_SEND_TEXT).arg(m_ip).arg(m_port),
         QJsonDocument(json).toJson());

    emit showMsg("屏幕任务 3");

}

void Screen::executeTask4()
{

    QJsonObject json;

    json.insert("FontSize", 30);
    json.insert("Content", "屏幕任务 4");
    json.insert("AudioTimes", 1);
    json.insert("AudioContent", "1");
    json.insert("AudioSwitch", 0);
    json.insert("Audiovolume", 9);

    post(QString(SCREEN_SEND_TEXT).arg(m_ip).arg(m_port),
         QJsonDocument(json).toJson());

    emit showMsg("屏幕任务 4");

}

void Screen::executeTask5()
{

    QJsonObject json;

    json.insert("FontSize", 30);
    json.insert("Content", "屏幕任务 5");
    json.insert("AudioTimes", 1);
    json.insert("AudioContent", "1");
    json.insert("AudioSwitch", 0);
    json.insert("Audiovolume", 9);

    post(QString(SCREEN_SEND_TEXT).arg(m_ip).arg(m_port),
         QJsonDocument(json).toJson());

    emit showMsg("屏幕任务 5");;
}
