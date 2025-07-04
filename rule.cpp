#include "rule.h"
#include "datatransmitter.h"
#include "novacontroller.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "trafficlight.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QFile>

#define RULES_JSON  "/rules.json"
#define CFG_NAME "/cfg.json"

Rule::Rule(QObject *parent)
    : QObject{parent}
{
    initRules();
    initTimer();
    initScreen();
}

void Rule::runRule()
{
    for(int i=0; i<m_ruleList.count(); i++){
        if(allConitionIsTrue(&(m_ruleList.at(i)->conditionList))){
            allexecuteTaskIsDone(&(m_ruleList.at(i)->executeTaskList));
            qDebug() << m_ruleList.at(i)->name << ":    true";
            //qDebug() << m_ruleList.at(i)->name << ":    所有条件为真";
        }else{
            qDebug() << m_ruleList.at(i)->name << ":    false";
           //qDebug() << m_ruleList.at(i)->name << ":    有条件为假";
        }
    }
}

void Rule::testShowLights()
{
    QString msg;
    for(int i=0; i<m_trafficLightList.count(); i++){
        msg += QString::number(m_trafficLightList.at(i)->getId());
        msg += ": ";
        msg += enum2ColorString(m_trafficLightList.at(i)->getColor());
        msg += "    ";
    }
    qDebug() << msg;
}

void Rule::testShowRules()
{
    for(int i=0; i<m_ruleList.count(); i++){
        qDebug() << m_ruleList.at(i)->name;
    }
}

QByteArray Rule::getRulesJsonArayData()
{
    return m_localRulesData;
}

void Rule::initTimer()
{
    m_runRulesTimer = new QTimer;
    connect(m_runRulesTimer, &QTimer::timeout, this, [this]{
        if(!m_ruleList.isEmpty() && m_trafficLightList.size() > 0){
            runRule();
        }
    });

    m_runRulesTimer->setInterval(1000);
    m_runRulesTimer->start();
}

void Rule::initRules()
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

void Rule::initScreen()
{
    QString cfgPath = QCoreApplication::applicationDirPath() + CFG_NAME;
    QFile file(cfgPath);

    if(!file.exists()){
        qDebug() <<("配置文件不存在");
    }

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() <<("配置文件读取失败");
    }

    QString ip;
    int Back2DefaultProgram;
    QJsonObject cfgJson = QJsonDocument::fromJson(file.readAll()).object();

    ip = cfgJson.value("screen").toObject().value("ip").toString();
    Back2DefaultProgram = cfgJson.value("screen").toObject().value("Back2DefaultProgram").toInt();
    m_screen = new NovaController(ip, Back2DefaultProgram);
    m_screenList << m_screen;

    m_screen->start();
}

void Rule::initDataTransmitter()
{
    m_dataTransmitter = new DataTransmitter;
}

void Rule::writewRules2RulesFile(QString rulesData)
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

    // 读取配置文件
    file.write(rulesData.toUtf8());
}

bool Rule::conittionIsTrue(s_condition condition)
{
    TrafficLight* light = nullptr;
    switch (condition.deviceType) {
    case e_deviceType::LIGHT:
        light = getLight(condition.deviceId);
        if(!light){
            qDebug() << "lightID: " << condition.deviceId << "不存在";
            return false;
        }

        if(!light->conitionIsTrue((e_lightCondition)(condition.condition), condition.args)){
            return false;
        }

        break;
    case e_deviceType::SCREEN:
        qCritical() << "****** 屏幕未添加条件判断 ******";
        return false;
        break;
    case e_deviceType::DATA_TRANSMITTER:
        qCritical() << "****** 屏幕数据发送未添加条件判断 ******";
        return false;
        break;
    default:
        break;
    }
    return true;
}

bool Rule::allConitionIsTrue(QList<s_condition>* conditionList)
{
    for(int i=0; i<conditionList->count(); i++){
        if(!conittionIsTrue(conditionList->at(i))){
            return false;
        }
    }

    return true;
}

bool Rule::executeTaskIsDone(s_executeTask executeTask)
{
    switch (executeTask.deviceType) {
    case e_deviceType::LIGHT:
        qDebug() << "灯执行任务暂未启用";
        return false;
        break;
    case e_deviceType::SCREEN:
        if(!getScreen(executeTask.deviceId)->executeTaskIsDone((e_screenExecuteTask)(executeTask.executeTask), executeTask.args)){
            return false;
        }
        break;
    case e_deviceType::DATA_TRANSMITTER:
        if(!getDataTransmitter(executeTask.deviceId)->executeTaskIsDone((e_dataTransmitterExecuteTask)(executeTask.executeTask), executeTask.args)){
            return false;
        }
        break;
    default:
        break;
    }

    return true;
}

bool Rule::allexecuteTaskIsDone(QList<s_executeTask>* executeTaskList)
{
    for(int i=0; i<executeTaskList->count(); i++){
        if(!executeTaskIsDone(executeTaskList->at(i))){
            return false;
        }
    }
    return true;
}

bool Rule::modifyLightColorById(int id, e_trafficLightColor color)
{

    for(int i=0; i<m_trafficLightList.size(); i++){
        if(id == m_trafficLightList.at(i)->getId()){
            m_trafficLightList.at(i)->setLightColor(color);
            return true;
        }
    }
    return false;
}

e_trafficLightColor Rule::colorString2Enum(QString color)
{
    if(color.toUpper() == "RED"){
        return e_trafficLightColor::RED;
    }else if(color.toUpper() == "GREEN"){
        return e_trafficLightColor::GREEN;
    }else if(color.toUpper() == "YELLOW"){
        return e_trafficLightColor::YELLOW;
    }else if(color.toUpper() == "BLACK"){
        return e_trafficLightColor::BLACK;
    }else{
        return e_trafficLightColor::UNKNOWN;
    }
}

QString Rule::enum2ColorString(e_trafficLightColor color)
{
    switch(color){
    case e_trafficLightColor::BLACK:
        return "黑";
        break;
    case e_trafficLightColor::RED:
        return "红";
        break;
    case e_trafficLightColor::GREEN:
        return "绿";
        break;
    case e_trafficLightColor::YELLOW:
        return "黄";
        break;
    case e_trafficLightColor::UNKNOWN:
        return "未知";
        break;
    default:
        break;
    }
    return "未知";
}

void Rule::addLight2List(int id, e_trafficLightColor color)
{
    TrafficLight* light = new TrafficLight(color, id, this);
    m_trafficLightList << light;

}

void Rule::setRules(QString ruleData)
{
    clearRules();
    m_ruleList.clear();

    QJsonDocument rulesJsonDoc = QJsonDocument::fromJson(ruleData.toUtf8());
    QJsonObject rulesJsonObj = rulesJsonDoc.object();

    foreach (QJsonValue ruleValue, rulesJsonObj.value("rules").toArray()) {
        qDebug() << "/***********************************************/";
        QJsonObject ruleJson = ruleValue.toObject();

        s_rule* rule = new s_rule;
        rule->name = ruleJson.value("name").toString();
        qDebug() << "规则: " << rule->name;
        m_ruleList << rule;

        QJsonArray conditionsArray = ruleJson.value("conditionList").toArray();
        foreach (QJsonValue conditionValue, conditionsArray){

            qDebug() << "**条件: ";
            QJsonObject conditionJson = conditionValue.toObject();
            s_condition condition;
            QJsonArray args = conditionJson.value("args").toArray();
            qDebug() << conditionJson;

            condition.deviceType = (e_deviceType)conditionJson.value("deviceType").toInt();
            condition.deviceId = conditionJson.value("deviceId").toInt();
            condition.condition = conditionJson.value("condition").toInt();

            foreach (QJsonValue value, args) {
                condition.args << value.toObject().value("name").toString();
            }
            rule->conditionList << condition;

            qDebug() << "****设备类型: " << (int)condition.deviceType;
            qDebug() << "****设备编号: " << (int)condition.deviceId;
            qDebug() << "****满足条件: " << (int)condition.condition;
            qDebug() << "****参数列表: " << condition.args;
        }

        QJsonArray executeArray = ruleJson.value("executeTaskList").toArray();
        foreach (QJsonValue executeTaskValue, executeArray){

            qDebug() << "**执行: ";
            QJsonObject executeTaskJson = executeTaskValue.toObject();
            s_executeTask executeTask;
            QJsonArray args = executeTaskJson.value("args").toArray();

            qDebug() << executeTaskJson;

            executeTask.deviceType = (e_deviceType)executeTaskJson.value("deviceType").toInt();
            executeTask.deviceId = executeTaskJson.value("deviceId").toInt();
            executeTask.executeTask = executeTaskJson.value("condition").toInt();

            foreach (QJsonValue value, args) {
                executeTask.args << value.toObject().value("name").toString();
            }
            rule->executeTaskList << executeTask;
            qDebug() << "****设备类型: " << (int)executeTask.deviceType;
            qDebug() << "****设备编号: " << (int)executeTask.deviceId;
            qDebug() << "****满足条件: " << (int)executeTask.executeTask;
            qDebug() << "****参数列表: " << executeTask.args;
        }
    }
}

void Rule::clearRules()
{
    for(int i=0; i<m_ruleList.count(); i++){
        s_rule* rule = m_ruleList.at(i);
        if(rule){
            delete rule;
        }
    }
    m_ruleList.clear();
}

TrafficLight *Rule::getLight(int deviceId)
{
    Q_UNUSED(deviceId);
    for(int i=0; i<m_trafficLightList.count(); i++){
        if(m_trafficLightList.at(i)->getId() == deviceId){
            return m_trafficLightList.at(i);
        }
    }
    return nullptr;
}

NovaController *Rule::getScreen(int deviceId)
{
    for(int i=0; i<m_screenList.count(); i++){
        if(m_screenList.at(i)->getId() == deviceId){
            return m_screenList.at(i);
        }
    }
    return nullptr;
}

DataTransmitter *Rule::getDataTransmitter(int deviceId)
{
    Q_UNUSED(deviceId);
    if(m_dataTransmitter) return m_dataTransmitter;
    return nullptr;
}

void Rule::slotUpdateLightsInfoDataParse(QString data)
{
    QJsonObject json = QJsonDocument::fromJson(data.toLatin1()).object();
    QJsonArray lightArray = json.value("trafficlight_status").toArray();

    for(int i=0; i<lightArray.size(); i++){
        QJsonObject light = lightArray.at(i).toObject();
        int id = light.value("id").toInt();
        e_trafficLightColor color = colorString2Enum(light.value("color").toString());

        if(modifyLightColorById(id, color)){
            continue;
        }else{
            addLight2List(id, color);
        }
    }
    // testShowLights();
}

void Rule::slotUpdateRulesInfo(QString ruleData)
{
    setRules(ruleData);
    writewRules2RulesFile(ruleData);
    testShowRules();
}
