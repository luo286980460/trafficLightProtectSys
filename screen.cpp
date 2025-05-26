#include "screen.h"
#include "qjsonobject.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

Screen::Screen(QString ip, int port,QObject *parent)
    : QObject{parent}
{
    init();
    m_url = QString("http://%1:%2/screenOn/Text")
                .arg(ip).arg(port);
}


void Screen::post(QString jsonData)
{

    QNetworkRequest request(m_url);
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

void Screen::executeAllTasks(QList<e_screenExecuteTask> *e_executeTaskList)
{
    for(int i=0; i<e_executeTaskList->size(); i++){
        e_screenExecuteTask executeTask =  e_executeTaskList->at(i);
        switch (executeTask) {
        case e_screenExecuteTask::TASK0:
            executeTask0();
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
            break;
        default:
            break;
        }
    }
}

void Screen::init()
{
    m_manager = new QNetworkAccessManager();
}


void Screen::executeTask0()
{
    QJsonObject json;

    json.insert("FontSize", 30);
    json.insert("Content", "屏幕任务 0");
    json.insert("AudioTimes", 1);
    json.insert("AudioContent", "1");
    json.insert("AudioSwitch", 0);
    json.insert("Audiovolume", 9);

    post(QJsonDocument(json).toJson());

    emit showMsg("屏幕任务 0");
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

    post(QJsonDocument(json).toJson());

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

    post(QJsonDocument(json).toJson());

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

    post(QJsonDocument(json).toJson());

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

    post(QJsonDocument(json).toJson());

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

    post(QJsonDocument(json).toJson());

    emit showMsg("屏幕任务 5");;
}

void Screen::tmpScreenExecuteTasks(QStringList taskList)
{


    QList<e_screenExecuteTask> taskList_e;
    foreach(QString task, taskList){
        e_screenExecuteTask task_e = (e_screenExecuteTask)task.toInt();


        switch(task_e){
        case e_screenExecuteTask::TASK0:
            executeTask0();
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
    }


}

