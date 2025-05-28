#ifndef WIDGET_H
#define WIDGET_H

#include "qjsonobject.h"
#include "runrules.h"
#include "trafficlight.h"
#include <QWidget>
#include <QComboBox>

class TrafficLight;
class MyHttpServer;
class TriggeringCondition;
class MyUdpServer;
class MyWidget;
class runRules;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QWidget* getUi();

private:
    void initCfg();
    void initMyHttpserver();

    void addLight2List(int id, e_trafficLightColor color);
    bool modifyLightColorById(int id, e_trafficLightColor color);
    void showLights();
    e_trafficLightColor colorString2Enum(QString color);
    TrafficLight* getLightFromList(int id);


    void showConditions();
    void updateRulesList();
    void getRules();
    void setRules();

signals:
    void tmpScreenExecuteTasks(QStringList taskList);   // 临时方法,让屏幕执行任务

private slots:
    void showMsg(QString msg);
    void on_clsBtn_clicked();
    void on_clsBtn_3_clicked();
    void slotUpdateLightsInfoDataParse(QString data);      // 解析协议数据
    void on_updateBtn_clicked();
    void on_conditionGroupBoxCloseBtn_clicked();
    void on_propertyGroupBoxCloseBtn_clicked();
    void on_conditionGroupBoxUpdateBtn_clicked();
    void on_pushButton_2_clicked();
    void on_updateRulesBtn_clicked();
    void on_rulesListComBox_currentIndexChanged(int index);
    void on_editRuleBtn_clicked();
    void on_deleteRulesBtn_clicked();


    void on_addRulesBtn_clicked();

    void on_directionComboBox_currentIndexChanged(int index);

    void on_laneComboBox_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
    QJsonObject m_cfgJson;

    QList<TrafficLight*> m_trafficLightList;
    MyHttpServer* m_myHttpserver;
    int m_currentCheckLabel;


    QList<TriggeringCondition*> m_triggeringConditionList;    // 条件集列表

    MyUdpServer* m_myUdpServer;
    void initUdpServer();
    TriggeringCondition* m_currClickCon;
    QComboBox* idCombox;
    QComboBox* ConditionCombox;

    // 添加规则窗口
    MyWidget* m_myWidget;
    runRules* m_runRules;
    QList<s_rule> *m_rules;
    void initRunRules();
    s_rule m_currentRule;


};
#endif // WIDGET_H
