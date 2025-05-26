#ifndef RUNRULES_H
#define RUNRULES_H

#include "trafficlight.h"
#include <QObject>
#include <QTimer>


enum class e_deviceType{    // 设备类型
    LIGHT,
    SCREEN
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
class runRules : public QObject
{
    Q_OBJECT
public:
    explicit runRules(QObject *parent = nullptr);


    void runRule();
    void initRules();   // 加载本地规则
    void writewRules2RulesFile(QString rulesData);   // 写入规则到文件
    TrafficLight* getLight(int deviceId);
    bool conittionIsTrue(s_condition condition);      // 条件为真
    bool allConitionIsTrue(QList<s_condition>* conditionList);
    bool executeTaskIsDone(s_executeTask condition);      // 执行结果为真
    bool allexecuteTaskIsDone(QList<s_executeTask>* executeTaskList);

    void test();
    s_rule* at(int index);
    int count();

    QString e_condition2String(e_condition condition);
    QString e_executeTask2String(e_lightExecuteTask executeTask);
    void setTrafficLightList(QList<TrafficLight*>* trafficLightList);

    void setRules(QString ruleData);
    void clearRules();
    QStringList getRulesList();

private:
    void initTimer();
    void packRulesData();

signals:
    void showMsg(QString msg);

public slots:
    void slotUpdateRulesInfo(QString ruleData);

private:
    QTimer* m_runRulesTimer;
    QList<s_rule*> m_ruleList;      // 需要执行的规则列表
    QStringList m_rulesList;      // 需要执行的规则列表(str)
    QString m_rulesData;
    QList<TrafficLight*>* m_trafficLightList;
    QByteArray m_localRulesData;
};

#endif // RUNRULES_H
