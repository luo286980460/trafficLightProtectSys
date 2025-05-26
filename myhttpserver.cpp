#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>
#include <QFile>
#include <QCoreApplication>
#include <QDir>

#include "myhttpserver.h"
#include "include/libhv/hthread.h"    // import hv_gettid
#include "include/libhv/hasync.h"     // import hv::async
#include "qaesencryption.h"
#include "trafficlight.h"

#define LOGIN_PATH "/src/dist/index.html"
#define SRC_PATH "/src"
#define ACCOUNT_INFO_PATH "/aip.ls"


MyHttpServer::MyHttpServer(int port, QWidget* lightWidget, QObject *parent)
    : QObject(parent)
    , m_lightWidget(lightWidget)
{
    createHttpserver(port);
}

MyHttpServer::~MyHttpServer()
{
    m_httpServer->stop();
    hv::async::cleanup();
}

void MyHttpServer::stop()
{
    m_httpServer->stop();
    hv::async::cleanup();
}

void MyHttpServer::createHttpserver(int port)
{
    HV_MEMCHECK;

    m_router = new HttpService;

    /* Static file service */
    // curl -v http://ip:port/
    m_router->Static("/", "./html");

    /* Forward proxy service */
    m_router->EnableForwardProxy();
    // curl -v http://httpbin.org/get --proxy http://127.0.0.1:8080
    m_router->AddTrustProxy("*httpbin.org");

    /* Reverse proxy service */
    // curl -v http://ip:port/httpbin/get
    m_router->Proxy("/httpbin/", "http://httpbin.org/");


    // 首页 login.html  /UtisWebCfgServer
    m_router->GET("/", [](HttpRequest* req, HttpResponse* resp) {

        Q_UNUSED(req);
        QString path = QCoreApplication::applicationDirPath() + LOGIN_PATH;

        return resp->File(path.toStdString().c_str());
    });

    // login
    m_router->POST("/login", [this](HttpRequest* req, HttpResponse* resp) {

        // const char* Token;  = "session_id=Y3VybF91c2VyOjEyMw==; Max-Age=7200; Path=/; Domain=.example.com; Secure; HttpOnly; SameSite=Lax";
        //  resp->SetHeader("Set-Cookie", Token);

        QJsonObject backJson;
        backJson.insert("token", "");
        backJson.insert("code", 200);
        backJson.insert("msg", "ok");

        QString body = QString::fromStdString(req->body);
        QString contentType = QString::fromStdString(req->GetHeader("ConTent-Type")).trimmed().replace(" ", "");

        if("application/json" != contentType){
            backJson["code"] = 400;
            backJson["msg"] = "非法请求头";


            resp->content_type = APPLICATION_JSON;
            resp->body = QJsonDocument(backJson).toJson().toStdString();
            // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
            return 200;

            //return resp->String(QJsonDocument(backJson).toJson().toStdString());
        }

        // 获取json数据包
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(req->body).toUtf8());
        QJsonObject jsonObj = jsonDoc.object();

        QString username = jsonObj.value("username").toString();
        QString password =  jsonObj.value("password").toString();
        QString token;


        //  使用数据库保存账号密码的模块
        // 验证账号密码
        // if(!m_myDataBase->useramePwdIsOK(username, password, backJson)){
        //     return resp->String(QJsonDocument(backJson).toJson().toStdString());
        // }

        // // 生成token并更新
        // token = generateToken(username, password);
        // if(!m_myDataBase->updataToken(username, token, backJson)){
        //     resp->content_type = TEXT_PLAIN;
        //     resp->body = QJsonDocument(backJson).toJson().toStdString();
        //     return 400;

        //     //return resp->String(QJsonDocument(backJson).toJson().toStdString());
        // }
        // backJson["token"] = token;

        // // 获取设备数据
        // QJsonArray deviceArray;
        // if(!m_myDataBase->getDeviceData(username, deviceArray, backJson)){

        //     resp->content_type = TEXT_PLAIN;
        //     resp->body = QJsonDocument(backJson).toJson().toStdString();
        //     return 400;
        //     // return resp->String(QJsonDocument(backJson).toJson().toStdString());
        // }

        // backJson.insert("devices", deviceArray);
        // m_myDataBase->closeDataBase(); // 关闭连接

        // return resp->String(QJsonDocument(backJson).toJson().toStdString());



        // 使用文件保存账号密码的模块
        QString accountInfoFilePath = QCoreApplication::applicationDirPath() + ACCOUNT_INFO_PATH;
        QFile accountInfoFile(accountInfoFilePath);

        if(!accountInfoFile.open(QIODevice::ReadOnly)){
            backJson["code"] = 400;
            backJson["msg"] = "account cfg missing";

            resp->content_type = APPLICATION_JSON;
            resp->body = QJsonDocument(backJson).toJson().toStdString();
            //resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
            return 200;
        }

        bool isOk = false;

        //qDebug() << QJsonDocument::fromJson(decrypt_Aes128_ECB_PKCS7_HEX(QByteArray::fromHex(accountInfoFile.readAll()), m_aesKey).trimmed());

        QByteArray res = decrypt_Aes128_ECB_PKCS7_HEX(QByteArray::fromHex(accountInfoFile.readAll()), m_aesKey);
        res.chop(res.at(res.size() - 1));

        QJsonObject usrInfo = QJsonDocument::fromJson(res).object();


        if(usrInfo.find(username) == usrInfo.end()){
            backJson["code"] = 400;
            backJson["msg"] = "用户错误";

            resp->content_type = APPLICATION_JSON;
            resp->body = QJsonDocument(backJson).toJson().toStdString();
            return 200;
        }else if(usrInfo.value(username).toString() != password){
            backJson["code"] = 400;
            backJson["msg"] = "密码错误";

            resp->content_type = APPLICATION_JSON;
            resp->body = QJsonDocument(backJson).toJson().toStdString();
            return 200;
        }

        // QString lineData = accountInfoFile.readLine();

        // while(!lineData.isEmpty()){
        //     QList usrPwdList = lineData.split(":");
        //     if(usrPwdList.size() != 2){
        //         lineData = accountInfoFile.readLine();
        //         continue;
        //     }
        //     QString usr = usrPwdList.at(0).trimmed();
        //     QString pwd = usrPwdList.at(1).trimmed();

        //     if(username == usr && password == pwd){
        //         isOk = true;
        //         break;
        //     }

        //     lineData = accountInfoFile.readLine();
        // }

        // if(!isOk){
        //     backJson["code"] = 400;
        //     backJson["msg"] = "用户或者密码错误";

        //     resp->content_type = APPLICATION_JSON;
        //     resp->body = QJsonDocument(backJson).toJson().toStdString();
        //     //resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
        //     return 200;
        // }

        backJson["code"] = 200;
        backJson["msg"] = "success";
        backJson["token"] = "1";
        resp->content_type = APPLICATION_JSON;
        resp->body = QString(QJsonDocument(backJson).toJson()).toStdString();
        // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
        return 200;

    });

    /*          POST            */
    // curl -v http://ip:port/echo -d "hello,world!"
    m_router->POST("/echo", [](const HttpContextPtr& ctx) {
        return ctx->send(ctx->body(), ctx->type());
    });

    //
    m_router->POST("/trafficLight/updateLightsInfo", [this](HttpRequest* req, HttpResponse* resp) {
        QJsonObject backJson;
        backJson.insert("token", "");
        backJson.insert("code", 200);
        backJson.insert("msg", "ok");

        QString body = QString::fromStdString(req->body);
        QString contentType = QString::fromStdString(req->GetHeader("ConTent-Type")).trimmed().replace(" ", "");


        emit showMsg(body);

        if("application/json" != contentType){
            backJson["code"] = 400;
            backJson["msg"] = "非法请求头";


            resp->content_type = APPLICATION_JSON;
            resp->body = QJsonDocument(backJson).toJson().toStdString();
            // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
            return 200;

            //return resp->String(QJsonDocument(backJson).toJson().toStdString());
        }

        // 获取json数据包
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(req->body).toUtf8());
        QJsonObject jsonObj = jsonDoc.object();

        if(!updateLightsInfoDataIsLegal(jsonObj)){
            backJson["code"] = 200;
            backJson["msg"] = "updateLightsInfo协议数据不合法";
            resp->content_type = APPLICATION_JSON;
            resp->body = QString(QJsonDocument(backJson).toJson()).toStdString();
            // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
            return 200;
        }

        emit signalUpdateLightsInfoDataParse(QString::fromStdString(req->body).toUtf8());

        backJson["code"] = 200;
        backJson["msg"] = "success";
        backJson["token"] = "1";
        resp->content_type = APPLICATION_JSON;
        resp->body = QString(QJsonDocument(backJson).toJson()).toStdString();
        // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
        return 200;
    });

    m_router->POST("/trafficLight/updateRulesInfo", [this](HttpRequest* req, HttpResponse* resp) {
        QJsonObject backJson;
        backJson.insert("token", "");
        backJson.insert("code", 200);
        backJson.insert("msg", "ok");

        QString body = QString::fromStdString(req->body);
        QString contentType = QString::fromStdString(req->GetHeader("ConTent-Type")).trimmed().replace(" ", "");


        emit showMsg(body);

        if("application/json" != contentType){
            backJson["code"] = 400;
            backJson["msg"] = "非法请求头";


            resp->content_type = APPLICATION_JSON;
            resp->body = QJsonDocument(backJson).toJson().toStdString();
            // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
            return 200;

            //return resp->String(QJsonDocument(backJson).toJson().toStdString());
        }

        // 获取json数据包
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(req->body).toUtf8());
        QJsonObject jsonObj = jsonDoc.object();


        if(!updateLightsInfoDataIsLegal(jsonObj)){
            backJson["code"] = 200;
            backJson["msg"] = "updateLightsInfo协议数据不合法";
            resp->content_type = APPLICATION_JSON;
            resp->body = QString(QJsonDocument(backJson).toJson()).toStdString();
            // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
            return 200;
        }

        emit signalUpdateRulesInfo(jsonDoc.toJson());

        backJson["code"] = 200;
        backJson["msg"] = "success";
        backJson["token"] = "1";
        resp->content_type = APPLICATION_JSON;
        resp->body = QString(QJsonDocument(backJson).toJson()).toStdString();
        // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson().data(), m_aesKey).toStdString();
        return 200;
    });

    // web前端获取所有红绿灯选项接口
    m_router->GET("/trafficLight/getAllLightOptions", [this](HttpRequest* req, HttpResponse* resp) {

        QJsonObject backJson;


        QJsonObject light1;
        QJsonObject light2;
        QJsonArray lightArray;

        QJsonObject option0;
        QJsonObject option1;
        QJsonObject option2;
        QJsonArray optionArray;
        option0.insert("index", "0");
        option1.insert("index", "1");
        option2.insert("index", "2");
        option0.insert("text", "灯为红色时");
        option1.insert("text", "灯为绿色时");
        option2.insert("text", "灯为黄色时");
        optionArray << option0 << option1 << option2;

        light1.insert("id", "1");
        light2.insert("id", "2");
        light1.insert("options", optionArray);
        light2.insert("options", optionArray);


        lightArray << light1 << light2;
        backJson.insert("data", lightArray);

        resp->content_type = APPLICATION_JSON;
        resp->body = QJsonDocument(backJson).toJson().toStdString();


        // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson(), m_aesKey).toStdString();
         return 200;
    });


    /*          GET            */
    /* API handlers */
    // curl -v http://ip:port/ping
    m_router->GET("/ping", [](HttpRequest* req, HttpResponse* resp) {
        Q_UNUSED(req);
        Json ex3 =  {
            {"time", "最后更新时间：2025年05月12日"},
            {"Name", "信号灯守护神系统UI"},
            {"Version", "0.1"},
            {"Msg", ""}
        };

        QJsonObject backJson;
        backJson.insert("time", "最后更新时间：2025年05月12日");
        backJson.insert("Name", "信号灯守护神系统UI");
        backJson.insert("Version", "0.1");
        backJson.insert("Msg", "");

        resp->content_type = APPLICATION_JSON;
        resp->body = QJsonDocument(backJson).toJson().toStdString();


        // resp->body = aes128_ECB_PKCS7_HEX(QJsonDocument(backJson).toJson(), m_aesKey).toStdString();
        return 200;
        // return resp->Json(ex3);
    });

    // curl -v http://ip:port/paths
    m_router->GET("/paths", [this](HttpRequest* req, HttpResponse* resp) {
        Q_UNUSED(req);
        return resp->Json(m_router->Paths());
    });

    // curl -v http://ip:port/get?env=1
    m_router->GET("/get", [](const HttpContextPtr& ctx) {
        hv::Json resp;
        resp["origin"] = ctx->ip();
        resp["url"] = ctx->url();
        resp["args"] = ctx->params();
        resp["headers"] = ctx->headers();
        return ctx->send(resp.dump(2));
    });

    // curl -v http://ip:port/user/123
    m_router->GET("/user/{id}", [](const HttpContextPtr& ctx) {
        hv::Json resp;
        resp["id"] = ctx->param("id");
        return ctx->send(resp.dump(2));
    });

    // curl -v http://ip:port/async
    m_router->GET("/async", [](const HttpRequestPtr& req, const HttpResponseWriterPtr& writer) {
        Q_UNUSED(req);
        writer->Begin();
        writer->WriteHeader("X-Response-tid", hv_gettid());
        writer->WriteHeader("Content-Type", "text/plain");
        writer->WriteBody("This is an async response.\n");
        writer->End();
    });

    // web 模块
    m_httpServer = new HttpServer;

    add_directory_handlers(*m_httpServer, QCoreApplication::applicationDirPath() + SRC_PATH);

    m_httpServer->service = m_router;
    m_httpServer->port = port;

#if TEST_HTTPS
    server.https_port = 8443;
    hssl_ctx_opt_t param;
    memset(&param, 0, sizeof(param));
    param.crt_file = "cert/server.crt";
    param.key_file = "cert/server.key";
    param.endpoint = HSSL_SERVER;
    if (server.newSslCtx(&param) != 0) {
        fprintf(stderr, "new SSL_CTX failed!\n");
        return -20;
    }
#endif

    // uncomment to test multi-processes
    // server.setProcessNum(4);
    // uncomment to test multi-threads
    // server.setThreadNum(4);


    m_httpServer->start();
}

bool MyHttpServer::ipAddrIsOK(const QString &ip)
{
    if (ip.isEmpty())
    {
        return false;
    }

    QStringList list = ip.split('.');
    if (list.size() != 4)
    {
        return false;
    }

    for (const auto& num : list)
    {
        bool ok = false;
        int temp = num.toInt(&ok);
        if (!ok || temp < 0 || temp > 255)
        {
            return false;
        }
    }

    return true;
}

QString MyHttpServer::qstr2Hex(QString instr)
{
    if(instr.isEmpty()) return instr;

    QTextCodec *codec = QTextCodec::codecForName("GB2312");  //set char code
    QByteArray encodedString = codec->fromUnicode(instr);//convert to unicode
    instr = encodedString.toHex(QChar::Space); //hex add space example:FFAC21 convert to FF AC 21
    return instr.toUpper();
}

void MyHttpServer::add_file_handler(HttpServer &server, const QString &basepath, const QString &path)
{
    QString filepath = basepath + "/" + path;
    QFileInfo fileInfo(filepath);
    if (fileInfo.isFile()) {
        m_router->GET(("/"+path).toStdString().c_str(), [filepath](HttpRequest* req, HttpResponse* resp) {

            return resp->File(filepath.toStdString().c_str());
        });
    }
}

void MyHttpServer::add_directory_handlers(HttpServer &server, const QString &basepath, const QString &path)
{
    QDir dir(basepath + "/" + path);
    if (dir.exists()) {
        for (const QString& entry : dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries)) {
            QString subpath = path.isEmpty() ? entry : path + "/" + entry;
            if (QFileInfo(dir, entry).isDir()) {
                add_directory_handlers(server, basepath, subpath);
            } else {
                add_file_handler(server, basepath, subpath);
            }
        }
    }
}

QByteArray MyHttpServer::crypt_Aes128_ECB_PKCS7_HEX(QByteArray plaintext, QByteArray key)
{
    return QAESEncryption::Crypt(QAESEncryption::AES_128, QAESEncryption::ECB, plaintext, key, "", QAESEncryption::PKCS7).toHex();
}

QByteArray MyHttpServer::decrypt_Aes128_ECB_PKCS7_HEX(QByteArray plaintext, QByteArray key)
{
    return QAESEncryption::Decrypt(QAESEncryption::AES_128, QAESEncryption::ECB, plaintext, key, "", QAESEncryption::PKCS7);
}

bool MyHttpServer::updateLightsInfoDataIsLegal(QJsonObject &json)
{
    return true;
}

void MyHttpServer::setTrafficLightListPtr(QList<TrafficLight *> *trafficLightList)
{
    m_trafficLightList = trafficLightList;
}
