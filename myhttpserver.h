#ifndef MYHTTPSERVER_H
#define MYHTTPSERVER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include "include/libhv/HttpServer.h"

using namespace hv;


class MyHttpServer : public QObject
{
    Q_OBJECT

public:
    MyHttpServer(int port, QObject *parent = nullptr);
    ~MyHttpServer();

    void stop();
    void initTestJsonRules();
    void setRulesJsonArayData(QByteArray jsonData);

private:
    void createHttpserver(int port);                // 开启httpserver
    bool ipAddrIsOK(const QString & ip);            // 判断字符串是否为合法 ip 地址
    QString qstr2Hex(QString instr);                // 汉字 转 16进制

    void add_file_handler(HttpServer& server, const QString& basepath, const QString& path);
    void add_directory_handlers(HttpServer& server, const QString& basepath, const QString& path = "");
    QByteArray crypt_Aes128_ECB_PKCS7_HEX(QByteArray plaintext, QByteArray key);
    QByteArray decrypt_Aes128_ECB_PKCS7_HEX(QByteArray plaintext, QByteArray key);

    bool updateLightsInfoDataIsLegal(QJsonObject& json);    // 协议数据是否合法

signals:
    void signalRestartApplication();
    void signalUpdateLightsInfoDataParse(QString data);
    void signalUpdateRulesInfo(QString ruleData);

public slots:

public:
    hv::HttpServer* m_httpServer;
    HttpService* m_router;

private:
    QByteArray m_aesKey = "Utis00000000LsCb";
    QJsonObject m_rulesJson;
};


#endif // MYHTTPSERVER_H
