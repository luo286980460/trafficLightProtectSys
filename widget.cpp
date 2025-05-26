#include "widget.h"
#include "myhttpserver.h"
#include "myudpserver.h"
#include "runrules.h"
#include "ui_widget.h"

#include "trafficlight.h"
#include "triggeringcondition.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QGroupBox>
#include <QDebug>
#include <Screen.h>

#define CFG_NAME "/cfg.json";

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initMyHttpserver();
    ui->propertyGroupBox->hide();
    ui->ConditionGroupBox->hide();
    ui->conditionShowWidget->setReadOnly(true);
    setFixedSize(1240, 830);
    ui->updateBtn->hide();


    initCfg();

    initUdpServer();
    initRunRules();
    updateRulesList();

    connect(m_myHttpserver, &MyHttpServer::signalUpdateRulesInfo, m_runRules, &runRules::slotUpdateRulesInfo);

    initScreen();
    connect(this, &Widget::tmpScreenExecuteTasks, m_screen, &Screen::tmpScreenExecuteTasks);
}

Widget::~Widget()
{
    delete ui;
}

QWidget *Widget::getUi()
{
    return ui->TrafficLightShowWidget;
}

void Widget::initCfg()
{
    QString cfgPath = QCoreApplication::applicationDirPath() + CFG_NAME;
    QFile file(cfgPath);

    if(!file.exists()){
        showMsg("配置文件不存在");
    }

    if(!file.open(QIODevice::ReadOnly)){
        showMsg("配置文件读取失败");
    }

    m_cfgJson = QJsonDocument::fromJson(file.readAll()).object();
}

void Widget::initMyHttpserver()
{
    m_myHttpserver = new MyHttpServer(23334, this);
    connect(m_myHttpserver, &MyHttpServer::showMsg, this, &Widget::showMsg);
    connect(m_myHttpserver, &MyHttpServer::signalUpdateLightsInfoDataParse, this, &Widget::slotUpdateLightsInfoDataParse);
    m_myHttpserver->setTrafficLightListPtr(&m_trafficLightList);
}

void Widget::showMsg(QString msg)
{
    ui->history->appendPlainText(msg);
}

void Widget::addLight2List(int id, e_trafficLightColor color)
{
    TrafficLight* light = new TrafficLight(color, id, ui->TrafficLightShowWidget);
    connect(light, &TrafficLight::showMsg, this, &Widget::showMsg);
    connect(light, &TrafficLight::tmpScreenExecuteTasks, this, &Widget::tmpScreenExecuteTasks);
    m_trafficLightList << light;
    light->setText(QString::number(id));
    connect(light, &QPushButton::clicked, this, [this, light]{

        if(ui->propertyGroupBox->isHidden() || m_currentCheckLabel+1 !=  light->getId()){
            ui->propertyGroupBox->move(light->x() + light->width(), light->y() + light->height());
            ui->propertyGroupBox->show();
            ui->propertyGroupBox->raise();
            ui->imgLabel->setStyleSheet(light->getStytle());
            ui->idLabel->setText(QString::number(light->getId()));
            ui->colorLabel->setText("当前颜色: " + light->getColor());
            ui->lightSecLabel->setText("已亮时长: " + QString::number(light->getLightSec()));
            ui->directionComboBox->setCurrentIndex((int)light->getLightDirectionE());
            ui->laneComboBox->setCurrentIndex((int)light->getLightLane());
        }else{
            ui->propertyGroupBox->hide();
        }

        m_currentCheckLabel = light->getId()-1;
    });

    showLights();
}

bool Widget::modifyLightColorById(int id, e_trafficLightColor color)
{
    for(int i=0; i<m_trafficLightList.size(); i++){
        if(id == m_trafficLightList.at(i)->getId()){
            m_trafficLightList.at(i)->setLightColor(color);
            showLights();
            return true;
        }
    }
    return false;
}

void Widget::showLights()
{
    for(int i=0; i<m_trafficLightList.size(); i++){
        m_trafficLightList.at(i)->updateStytle();
        m_trafficLightList.at(i)->show();
        m_trafficLightList.at(i)->raise();
        m_trafficLightList.at(i)->move((i*10) + i*m_trafficLightList.at(i)->width(), 5);
    }

    if(m_currentCheckLabel < m_trafficLightList.size() && m_currentCheckLabel >= 0){
        ui->imgLabel->setStyleSheet(m_trafficLightList.at(m_currentCheckLabel)->getStytle());
        ui->idLabel->setText(QString::number(m_trafficLightList.at(m_currentCheckLabel)->getId()));
        ui->colorLabel->setText("当前颜色: " + m_trafficLightList.at(m_currentCheckLabel)->getColor());
        ui->lightSecLabel->setText("已亮时长: " + QString::number(m_trafficLightList.at(m_currentCheckLabel)->getLightSec()));
    }
}

e_trafficLightColor Widget::colorString2Enum(QString color)
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

TrafficLight *Widget::getLightFromList(int id)
{
    for(int i=0; i<m_trafficLightList.size(); i++){
        if(id == m_trafficLightList.at(i)->getId()){
            return m_trafficLightList.at(i);
        }
    }
    return nullptr;
}

void Widget::showConditions()
{
    for(int i=0,index=0; index <  m_triggeringConditionList.size(); i++){
        int x = 0;
        int y = 0;

        for(int j=0; j<4 && index <  m_triggeringConditionList.size();j++){
            m_triggeringConditionList.at(index)->adjustSize();
            m_triggeringConditionList.at(index)->move(x + (j*5 + j*m_triggeringConditionList.at(index)->width()), y + (i*5 + i*m_triggeringConditionList.at(index)->height()));
            m_triggeringConditionList.at(index)->show();
            index++;
        }
    }
}

void Widget::updateRulesList()
{
    on_updateRulesBtn_clicked();
}

void Widget::getRules()
{
    ui->rulesListComBox->clear();

    if(m_runRules){
        QStringList ruleList = m_runRules->getRulesList();

        for(int i=0; i<m_runRules->count(); i++){
            ui->rulesListComBox->addItem(m_runRules->at(i)->name, ruleList.at(i));
        }
    }
}

void Widget::setRules()
{
    QJsonObject json;
    QJsonArray ruleArray;

    for (int i=0; i<ui->rulesListComBox->count(); i++) {
        ruleArray << QJsonDocument::fromJson(ui->rulesListComBox->itemData(i).toByteArray()).object();
    }

    json.insert("rules", ruleArray);
    m_runRules->setRules(QJsonDocument(json).toJson());
    m_runRules->writewRules2RulesFile(QJsonDocument(json).toJson());

    getRules();
}

void Widget::on_clsBtn_clicked()
{
    ui->history->clear();
}

void Widget::on_clsBtn_3_clicked()
{
    foreach (TrafficLight* light, m_trafficLightList) {
        if(light){
            light->deleteLater();
        }
    }

    m_trafficLightList.clear();
}

void Widget::slotUpdateLightsInfoDataParse(QString data)
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
}

void Widget::on_updateBtn_clicked()
{
    TrafficLight* light = getLightFromList(ui->idLabel->text().toInt());
    if(light){
        light->setLightDirection((e_direction)ui->directionComboBox->currentIndex());
        light->setLightLane((e_lane)ui->laneComboBox->currentIndex());
        light->updateStytle();
        ui->imgLabel->setStyleSheet(light->getStytle());
    }
}


void Widget::on_conditionGroupBoxCloseBtn_clicked()
{
    ui->ConditionGroupBox->hide();
}

void Widget::initUdpServer()
{
    m_myUdpServer = new MyUdpServer;
    connect(m_myUdpServer, &MyUdpServer::showMsg, this, &Widget::showMsg);
    connect(m_myUdpServer, &MyUdpServer::signalUpdateLightsInfoDataParse, this, &Widget::slotUpdateLightsInfoDataParse);
}

void Widget::initRunRules()
{
    m_runRules = new runRules;
    connect(m_runRules, &runRules::showMsg, this, &Widget::showMsg);
    m_runRules->setTrafficLightList(&m_trafficLightList);
}

void Widget::initScreen()
{
    QString ip = m_cfgJson.value("screen").toObject().value("ip").toString();
    int port = m_cfgJson.value("screen").toObject().value("port").toInt();
    m_screen = new Screen(ip, port);
    connect(m_screen, &Screen::showMsg, this, &Widget::showMsg);

}


void Widget::on_propertyGroupBoxCloseBtn_clicked()
{
    ui->propertyGroupBox->hide();
}


void Widget::on_conditionGroupBoxUpdateBtn_clicked()
{
    m_currClickCon->setId(idCombox->currentText().toInt());
}


void Widget::on_pushButton_2_clicked()
{
    QString ip = ui->lineEdit->text().split(":", Qt::SkipEmptyParts).at(0);
    int port = ui->lineEdit->text().split(":", Qt::SkipEmptyParts).at(1).toInt();


    m_myUdpServer->connectToHost(ip, port);
}

void Widget::on_updateRulesBtn_clicked()
{
    getRules();
}


void Widget::on_rulesListComBox_currentIndexChanged(int index)
{
    if(index == -1) return;

    ui->conditionShowWidget->setReadOnly(true);
    ui->editRuleBtn->setText("编辑规则");
    ui->conditionShowWidget->clear();
    ui->conditionShowWidget->appendPlainText(ui->rulesListComBox->itemData(index).toString());

    // 将指针地址转换为整型
    // s_rule* rule = reinterpret_cast<s_rule*>(ui->rulesListComBox->itemData(index).toULongLong());

    // for(int i=0; i<rule->s_conditionList.size(); i++){
    //     ui->idComBox->addItem(QString::number(rule->s_conditionList.at(i).id), reinterpret_cast<uintptr_t>(&(rule->s_conditionList.at(i))));
    // }

    //********
}

void Widget::on_editRuleBtn_clicked()
{
    if(ui->conditionShowWidget->toPlainText().isEmpty()){
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(ui->conditionShowWidget->toPlainText().toUtf8());
    if(jsonDoc.isEmpty()){
        emit showMsg("非法 json 请检查格式");
        return;
    }


    if(ui->conditionShowWidget->isReadOnly()){
        ui->conditionShowWidget->setReadOnly(false);
        ui->editRuleBtn->setText("保存规则");
    }else{
        ui->conditionShowWidget->setReadOnly(true);
        ui->editRuleBtn->setText("编辑规则");


        ui->rulesListComBox->setItemData(ui->rulesListComBox->currentIndex(), ui->conditionShowWidget->toPlainText());


        setRules();
    }
}


void Widget::on_deleteRulesBtn_clicked()
{
    ui->conditionShowWidget->clear();
    ui->rulesListComBox->removeItem(ui->rulesListComBox->currentIndex());
    setRules();
}


void Widget::on_addRulesBtn_clicked()
{
    ui->rulesListComBox->addItem("新规则");
    ui->rulesListComBox->setCurrentIndex(ui->rulesListComBox->count()-1);
    ui->conditionShowWidget->setReadOnly(false);
    ui->editRuleBtn->setText("保存规则");
}


void Widget::on_directionComboBox_currentIndexChanged(int index)
{
    ui->updateBtn->click();
}


void Widget::on_laneComboBox_currentIndexChanged(int index)
{
    ui->updateBtn->click();
}

