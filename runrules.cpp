#include "runrules.h"
#include "qglobal.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QFile>

#define RULES_JSON  "/rules.json"

runRules::runRules(QObject *parent)
    : QObject{parent}
{
    initRules();
    initTimer();
}

void runRules::runRule()
{
    for(int i=0; i<m_ruleList.count(); i++){
        if(allConitionIsTrue(&(m_ruleList.at(i)->conditionList))){
            allexecuteTaskIsDone(&(m_ruleList.at(i)->executeTaskList));
            showMsg(m_ruleList.at(i)->name + ":    所有条件为真");
        }else{
            showMsg(m_ruleList.at(i)->name + ":    有条件为假");
        }
    }
}

void runRules::initRules()
{
    // CFG_JSON配置文件是否存在
    QString iniPath = QCoreApplication::applicationDirPath() + RULES_JSON;

    if(!QFileInfo::exists(iniPath)){
        qCritical() << ("****** cfg.json 配置文件丢失 ******");
    }

    // 打开配置文件
    QFile file(iniPath);
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << ("****** " + iniPath + " 配置文件打开失败 ******");
    }

    // 读取配置文件
    m_localRulesData = file.readAll();

    setRules(QString::fromUtf8(m_localRulesData));
}

void runRules::writewRules2RulesFile(QString rulesData)
{
    // CFG_JSON配置文件是否存在
    QString iniPath = QCoreApplication::applicationDirPath() + RULES_JSON;

    if(!QFileInfo::exists(iniPath)){
        qCritical() << ("****** cfg.json 配置文件丢失 ******");
    }

    // 打开配置文件
    QFile file(iniPath);
    if(!file.open(QIODevice::WriteOnly)){
        qCritical() << ("****** " + iniPath + " 配置文件打开失败 ******");
    }

    // 写入文件
    file.write(rulesData.toUtf8());
}

TrafficLight *runRules::getLight(int deviceId)
{
    for(int i=0; i<m_trafficLightList->count(); i++){
        if(m_trafficLightList->at(i)->getId() == deviceId){
            return m_trafficLightList->at(i);
        }
    }
    return nullptr;
}

bool runRules::conittionIsTrue(s_condition condition)
{
    switch (condition.deviceType) {
    case e_deviceType::LIGHT:
        if(!getLight(condition.deviceId)->conitionIsTrue((e_lightCondition)(condition.condition), condition.args)){
            return false;
        }
        break;
    case e_deviceType::SCREEN:

        break;
    default:
        break;
    }
    return true;
}

bool runRules::allConitionIsTrue(QList<s_condition> *conditionList)
{
    for(int i=0; i<conditionList->count(); i++){
        if(!conittionIsTrue(conditionList->at(i))){
            return false;
        }
    }
    return true;
}

bool runRules::executeTaskIsDone(s_executeTask condition)
{
    return true;
}

bool runRules::allexecuteTaskIsDone(QList<s_executeTask> *executeTaskList)
{
    for(int i=0; i<executeTaskList->count(); i++){
        if(!executeTaskIsDone(executeTaskList->at(i))){
            return false;
        }
    }
    return true;
}

void runRules::test()
{
    QByteArray data = "\
{\
    \"rules\": [\
        {\
            \"name\":\"规则1\",\
            \"conditionList\":[\
                {     \
                    \"deviceType\":0,\
                    \"deviceId\":1,\
                    \"condition\":0,\
                    \"args\":[\"1\"]\
                }\
            ],\
            \"executeTaskList\":[\
                {     \
                    \"deviceType\":0,\
                    \"deviceId\":1,\
                    \"executeTask\":0,\
                    \"args\":[\"安全驾驶\"]\
                }\
            ]\
        }\
    ]\
}";

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    setRules(data);


    //qDebug() << jsonDoc.object();

    // s_rule* ruleTest = new s_rule;
    // s_condition condition;
    // s_executeTask executeTask;

    // condition.id = 1;
    // condition.e_conditionList << e_condition::CONDITTION0;
    // executeTask.deviceId = 1;
    // executeTask.e_executeTaskList << e_executeTask::TASK0;
    // ruleTest->s_conditionList << condition;
    // ruleTest->s_executeTaskList << executeTask;


    // ruleTest->name = "规则1";
    // m_rules << ruleTest;


    // s_rule* ruleTest2 = new s_rule;
    // s_condition condition2;
    // s_executeTask executeTask2;
    // condition2.id = 1;
    // condition2.e_conditionList.clear();
    // condition2.e_conditionList << e_condition::CONDITTION1;
    // executeTask2.deviceId = 1;
    // executeTask2.e_executeTaskList.clear();
    // executeTask2.e_executeTaskList << e_executeTask::TASK1;

    // ruleTest2->s_conditionList << condition2;
    // ruleTest2->s_executeTaskList << executeTask2;
    // ruleTest2->name = "规则2";
    // m_rules << ruleTest2;



    // s_rule* ruleTest3 = new s_rule;
    // s_condition condition3;
    // s_executeTask executeTask3;
    // condition3.id = 2;
    // condition3.e_conditionList.clear();
    // condition3.e_conditionList << e_condition::CONDITTION0;
    // executeTask3.deviceId = 2;
    // executeTask3.e_executeTaskList.clear();
    // executeTask3.e_executeTaskList << e_executeTask::TASK0;

    // ruleTest3->s_conditionList << condition3;
    // ruleTest3->s_executeTaskList << executeTask3;
    // ruleTest3->name = "规则3";
    // m_rules << ruleTest3;


    // s_rule* ruleTest4 = new s_rule;
    // s_condition condition4;
    // s_executeTask executeTask4;
    // condition4.id = 2;
    // condition4.e_conditionList.clear();
    // condition4.e_conditionList << e_condition::CONDITTION1;
    // executeTask4.deviceId = 2;
    // executeTask4.e_executeTaskList.clear();
    // executeTask4.e_executeTaskList << e_executeTask::TASK1;

    // ruleTest4->s_conditionList << condition4;
    // ruleTest4->s_executeTaskList << executeTask4;
    // ruleTest4->name = "规则4";
    // m_rules << ruleTest4;


    // s_rule* ruleTest5 = new s_rule;
    // s_condition condition5;
    // s_executeTask executeTask5;
    // condition5.id = 3;
    // condition5.e_conditionList.clear();
    // condition5.e_conditionList << e_condition::CONDITTION0;
    // executeTask5.deviceId =3;
    // executeTask5.e_executeTaskList.clear();
    // executeTask5.e_executeTaskList << e_executeTask::TASK0;

    // ruleTest5->s_conditionList << condition5;
    // ruleTest5->s_executeTaskList << executeTask5;
    // ruleTest5->name = "规则5";
    // m_rules << ruleTest5;

    // s_rule* ruleTest6 = new s_rule;
    // s_condition condition6;
    // s_executeTask executeTask6;
    // condition6.id = 3;
    // condition6.e_conditionList.clear();
    // condition6.e_conditionList << e_condition::CONDITTION1;
    // executeTask6.deviceId =3;
    // executeTask6.e_executeTaskList.clear();
    // executeTask6.e_executeTaskList << e_executeTask::TASK1;

    // ruleTest6->s_conditionList << condition6;
    // ruleTest6->s_executeTaskList << executeTask6;
    // ruleTest6->name = "规则6";
    // m_rules << ruleTest6;
}

s_rule* runRules::at(int index)
{
    if(index < 0 || index >= m_ruleList.size() ){
        return nullptr;
    }

    return m_ruleList.at(index);
}

int runRules::count()
{
    return m_ruleList.count();
}

QString runRules::e_condition2String(e_condition condition)
{
    QString str;
    switch(condition){
    case e_condition::CONDITTION0:
        str = "灯为红色时";
        break;
    case e_condition::CONDITTION1:
        str = "灯为绿色时";
        break;
    case e_condition::CONDITTION2:
        str = "灯为黄色时";
        break;
    case e_condition::CONDITTION3:
        str = "CONDITTION3";
        break;
    case e_condition::CONDITTION4:
        str = "CONDITTION4";
        break;
    case e_condition::CONDITTION5:
        str = "CONDITTION5";
        break;
    default:
        break;
    }
    return str;
}

QString runRules::e_executeTask2String(e_lightExecuteTask executeTask)
{
    QString str;
    switch(executeTask){
    case e_lightExecuteTask::TASK0:
        str = "执行任务 0 ";
        break;
    case e_lightExecuteTask::TASK1:
        str = "执行任务 1 ";
        break;
    case e_lightExecuteTask::TASK2:
        str = "执行任务 2 ";
        break;
    case e_lightExecuteTask::TASK3:
        str = "执行任务 3 ";
        break;
    case e_lightExecuteTask::TASK4:
        str = "执行任务 4 ";
        break;
    case e_lightExecuteTask::TASK5:
        str = "执行任务 5 ";
        break;
    default:
        break;
    }
    return str;
}

void runRules::setTrafficLightList(QList<TrafficLight *> *trafficLightList)
{
    m_trafficLightList = trafficLightList;
}

void runRules::setRules(QString ruleData)
{
    clearRules();
    m_rulesList.clear();

    QJsonDocument rulesJsonDoc = QJsonDocument::fromJson(ruleData.toUtf8());
    QJsonObject rulesJsonObj = rulesJsonDoc.object();

    foreach (QJsonValue ruleValue, rulesJsonObj.value("rules").toArray()) {
        QJsonObject ruleJson = ruleValue.toObject();

        m_rulesList << QJsonDocument(ruleJson).toJson();

        s_rule* rule = new s_rule;
        rule->name = ruleJson.value("name").toString();
        m_ruleList << rule;

        QJsonArray conditionsArray = ruleJson.value("conditionList").toArray();
        foreach (QJsonValue conditionValue, conditionsArray){
            QJsonObject conditionJson = conditionValue.toObject();
            s_condition condition;
            QJsonArray args = conditionJson.value("args").toArray();

            condition.deviceType = (e_deviceType)conditionJson.value("deviceType").toInt();
            condition.deviceId = conditionJson.value("deviceId").toInt();
            condition.condition = conditionJson.value("condition").toInt();

            foreach (QJsonValue value, args) {
                condition.args << value.toString();
            }
            rule->conditionList << condition;
        }

        QJsonArray executeArray = ruleJson.value("executeTasks").toArray();
        foreach (QJsonValue executeTaskValue, executeArray){
            QJsonObject executeTaskJson = executeTaskValue.toObject();
            s_executeTask executeTask;
            QJsonArray args = executeTaskJson.value("args").toArray();

            executeTask.deviceType = (e_deviceType)executeTaskJson.value("deviceType").toInt();
            executeTask.deviceId = executeTaskJson.value("deviceId").toInt();
            executeTask.executeTask = executeTaskJson.value("condition").toInt();

            foreach (QJsonValue value, args) {
                executeTask.args << value.toString();
            }
            rule->executeTaskList << executeTask;
        }
    }

    // clearRules();
    // m_rulesList.clear();
    // QJsonDocument rulesJsonDoc = QJsonDocument::fromJson(ruleData.toUtf8());
    // QJsonObject rulesJsonObj = rulesJsonDoc.object();

    // foreach (QJsonValue ruleValue, rulesJsonObj.value("rules").toArray()) {
    //     QJsonObject ruleJson = ruleValue.toObject();

    //     m_rulesList << QJsonDocument(ruleJson).toJson();

    //     s_rule* rule = new s_rule;
    //     rule->name = ruleJson.value("name").toString();
    //     m_ruleList << rule;

    //     QJsonArray conditionsArray = ruleJson.value("conditions").toArray();
    //     foreach (QJsonValue conditionValue, conditionsArray){
    //         QJsonObject conditionJson = conditionValue.toObject();
    //         s_condition condition;
    //         condition.deviceId = conditionJson.value("id").toInt();

    //         QJsonArray conditionlistArray = conditionJson.value("conditions").toArray();
    //         foreach(QJsonValue conditionValue, conditionlistArray){
    //             condition.e_conditionList << (e_condition)conditionValue.toInt();
    //         }
    //         rule->s_conditionList << condition;
    //     }

    //     QJsonArray executeArray = ruleJson.value("executeTasks").toArray();
    //     foreach (QJsonValue executeTaskValue, executeArray){
    //         QJsonObject executeTaskJson = executeTaskValue.toObject();
    //         s_executeTask executeTask;
    //         executeTask.deviceId = executeTaskJson.value("deviceId").toInt();

    //         QJsonArray conditionlistArray = executeTaskJson.value("executeTasks").toArray();
    //         foreach(QJsonValue executeTaskValue, conditionlistArray){
    //             executeTask.e_executeTaskList << (e_lightExecuteTask)executeTaskValue.toInt();
    //         }
    //         rule->s_executeTaskList << executeTask;
    //     }
    // }
}

void runRules::clearRules()
{
    foreach(s_rule* rule, m_ruleList){
        if(rule){
            delete rule;
        }
    }
    m_ruleList.clear();
}

QStringList runRules::getRulesList()
{
    return m_rulesList;
}

void runRules::initTimer()
{
    m_runRulesTimer = new QTimer;
    connect(m_runRulesTimer, &QTimer::timeout, this, [this]{
        if(!m_ruleList.isEmpty() && m_trafficLightList->size() > 0){
            // startRunRules();

            runRule();
        }
    });

    m_runRulesTimer->setInterval(1000);
    m_runRulesTimer->start();
}

void runRules::packRulesData()
{
    QJsonObject json;

    m_rulesData = QJsonDocument(json).toJson();
}

void runRules::slotUpdateRulesInfo(QString ruleData)
{
    setRules(ruleData);
}
