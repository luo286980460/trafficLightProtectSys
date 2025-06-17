#include "mainclass.h"
#include "myhttpserver.h"
#include "mytcpclient.h"
#include "qjsonarray.h"
#include "rule.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QJsonDocument>
#include <QProcess>

#define CFG_JSON        "/cfg.json"


MainClass::MainClass(QObject *parent)
    : QObject{parent}
{
    init();
}

void MainClass::init()
{
    if(!initCfgJson()) return;  // 先读取配置， 往下的函数会使用配置信息
    if(!initTcpClient()) return;
    if(!initRule()) return;
    if(!initHttpserver()) return;
}

bool MainClass::initCfgJson()
{
    // CFG_JSON配置文件是否存在
    QString iniPath = QCoreApplication::applicationDirPath() + CFG_JSON;

    if(!QFileInfo::exists(iniPath)){
        qCritical() << ("****** cfg.json 配置文件丢失 ******");
        return false;
    }

    // 打开配置文件
    QFile file(iniPath);
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << ("****** " + iniPath + " 配置文件打开失败 ******");
        return false;
    }

    // 读取配置文件
    QJsonParseError error;
    m_cfgJson = QJsonDocument::fromJson(file.readAll(), &error)
                    .object();
                    // .value("utisDeviceServer")
                    // .toObject();

    if(error.error != QJsonParseError::NoError){
        qCritical() << "error cfgJson: " + error.errorString();
        return false;
    }
    return true;
}

bool MainClass::initHttpserver()
{
    int port = m_cfgJson.value("httpServerPort").toInt();

    if(port < 1) {
        qCritical() << " error UtisDeviceServer Port = " + QString::number(port);
        return false;
    }

    m_myHttpServer = new MyHttpServer(port, this);
    connect(m_myHttpServer, &MyHttpServer::signalUpdateLightsInfoDataParse, this, &MainClass::signalUpdateLightsInfoDataParse);
    connect(m_myHttpServer, &MyHttpServer::signalUpdateRulesInfo, this, &MainClass::signalUpdateRulesInfo);

    if(m_rule){
        m_myHttpServer->setRulesJsonArayData(m_rule->getRulesJsonArayData());
    }

    return true;
}

bool MainClass::initTcpClient()
{
    m_myTcpclient = new MyTcpClient();
    connect(m_myTcpclient, &MyTcpClient::signalUpdateLightsInfoDataParse, this, &MainClass::signalUpdateLightsInfoDataParse);
    m_myTcpclient->connectToHost(m_cfgJson.value("camera").toObject().value("ip").toString(),
                                 m_cfgJson.value("camera").toObject().value("port").toInt());
    return true;
}

bool MainClass::initRule()
{
    m_rule = new Rule();
    connect(this, &MainClass::signalUpdateLightsInfoDataParse, m_rule, &Rule::slotUpdateLightsInfoDataParse);
    connect(this, &MainClass::signalUpdateRulesInfo, m_rule, &Rule::slotUpdateRulesInfo);
    return true;
}
