#ifndef RULE_H
#define RULE_H

#include "trafficlight.h"
#include <QObject>
#include <QTimer>

class NovaController;
class DataTransmitter;

enum class e_deviceType{    // 设备类型
    LIGHT,              // 灯
    SCREEN,             // 屏
    DATA_TRANSMITTER    // 数据发送
};

typedef struct {        // 条件结构体
    e_deviceType deviceType;
    int deviceId;
    int condition;
    QStringList args;
}s_condition;

typedef struct {        // 任务结构体
    e_deviceType deviceType;
    int deviceId;
    int executeTask;
    QStringList args;
}s_executeTask;

typedef struct {    // 规则(多条件皆为true时, 执行所有任务)
    QString name;   // 规则名
    QList<s_condition> conditionList;
    QList<s_executeTask> executeTaskList;
}s_rule;

class Rule : public QObject
{
    Q_OBJECT
public:
    explicit Rule(QObject *parent = nullptr);

    void runRule();

    void testShowLights();
    void testShowRules();

private:
    void initTimer();
    void initRules();   // 加载本地规则
    void initScreen();
    void initDataTransmitter();
    void writewRules2RulesFile(QString rulesData);   // 写入规则到文件
    bool conittionIsTrue(s_condition condition);      // 条件为真
    bool allConitionIsTrue(QList<s_condition>* conditionList);
    bool executeTaskIsDone(s_executeTask executeTask);      // 执行结果为真
    bool allexecuteTaskIsDone(QList<s_executeTask>* executeTaskList);
    bool modifyLightColorById(int id, e_trafficLightColor color);
    e_trafficLightColor colorString2Enum(QString color);
    QString enum2ColorString(e_trafficLightColor color);

    void addLight2List(int id, e_trafficLightColor color);
    void setRules(QString ruleData);
    void clearRules();

    TrafficLight* getLight(int deviceId);
    NovaController* getScreen(int deviceId);
    DataTransmitter* getDataTransmitter(int deviceId);

signals:

public slots:
    void slotUpdateLightsInfoDataParse(QString data);      // 解析协议数据
    void slotUpdateRulesInfo(QString ruleData);

private:
    QTimer* m_runRulesTimer;
    QList<s_rule*> m_ruleList;
    QList<TrafficLight*> m_trafficLightList;
    QList<NovaController*> m_screenList;
    QByteArray m_localRulesData;
    NovaController* m_screen;
    DataTransmitter* m_dataTransmitter;
};

#endif // RULE_H
