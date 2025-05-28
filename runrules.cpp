#include "runrules.h"
#include "qglobal.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "screen.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QFile>

#define RULES_JSON  "/rules.json"

runRules::runRules(QObject *parent)
    : QObject{parent}
{
    initRules();
    initTimer();
    initScreen();
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

Screen *runRules::getScreen(int deviceId)
{
    return m_screen;
}

bool runRules::conditionIsTrue(s_condition condition)
{
    switch (condition.deviceType) {
    case e_deviceType::LIGHT:
        if(!getLight(condition.deviceId)->conitionIsTrue((e_lightCondition)(condition.condition), condition.args)){
            return false;
        }
        break;
    case e_deviceType::SCREEN:
        qDebug() << "屏幕条件判断暂未启用";
        showMsg("屏幕条件判断暂未启用");
        return false;
        break;
    default:
        break;
    }
    return true;
}

bool runRules::allConitionIsTrue(QList<s_condition> *conditionList)
{
    for(int i=0; i<conditionList->count(); i++){
        if(!conditionIsTrue(conditionList->at(i))){
            return false;
        }
    }
    return true;
}

bool runRules::executeTaskIsDone(s_executeTask executeTask)
{
    switch (executeTask.deviceType) {
    case e_deviceType::LIGHT:
        qDebug() << "灯执行任务暂未启用";
        showMsg("灯执行任务暂未启用");
        return false;
        break;
    case e_deviceType::SCREEN:
        if(!getScreen(executeTask.deviceId)->executeTaskIsDone((e_screenExecuteTask)(executeTask.executeTask), executeTask.args)){
            return false;
        }
        break;
    default:
        break;
    }

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

        QJsonArray executeArray = ruleJson.value("executeTaskList").toArray();
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

void runRules::initScreen()
{
    m_screen = new Screen;
    connect(m_screen, &Screen::showMsg, this, &runRules::showMsg);
}

void runRules::slotUpdateRulesInfo(QString ruleData)
{
    setRules(ruleData);
}
