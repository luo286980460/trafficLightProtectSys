#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>
#include <QJsonObject>

class MyHttpServer;
class MyTcpClient;
class MyTcpClient;
class Rule;

class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = nullptr);


private:
    void init();
    bool initCfgJson();
    bool initHttpserver();
    bool initTcpClient();
    bool initRule();

signals:
    void signalUpdateLightsInfoDataParse(QString data);
    void signalUpdateRulesInfo(QString ruleData);

public slots:

private:
    QJsonObject m_cfgJson;
    MyHttpServer* m_myHttpServer;
    MyTcpClient* m_myTcpclient;
    Rule* m_rule;
};

#endif // MAINCLASS_H
