#include "trafficlight.h"

#include <QDebug>

#define LIGHT_RED_PATH ":/src/trafficLight/circle/red.png"
#define LIGHT_GREEN_PATH ":/src/trafficLight/circle/green.png"
#define LIGHT_YELLOW_PATH ":/src/trafficLight/circle/yellow.png"
#define LIGHT_BLACK_PATH ":/src/trafficLight/circle/black.png"

#define LIGHT_RED_GO_STRAIGHT_PATH ":/src/trafficLight/arrows/forward/red.png"
#define LIGHT_GREEN_GO_STRAIGHT_PATH ":/src/trafficLight/arrows/forward/green.png"
#define LIGHT_YELLOW_GO_STRAIGHT_PATH ":/src/trafficLight/arrows/forward/yellow.png"
#define LIGHT_BLACK_GO_STRAIGHT_PATH ":/src/trafficLight/arrows/forward/black.png"

#define LIGHT_RED_TURN_LEFT_PATH ":/src/trafficLight/arrows/left/red.png"
#define LIGHT_GREEN_TURN_LEFT_PATH ":/src/trafficLight/arrows/left/green.png"
#define LIGHT_YELLOW_TURN_LEFT_PATH ":/src/trafficLight/arrows/left/yellow.png"
#define LIGHT_BLACK_TURN_LEFT_PATH ":/src/trafficLight/arrows/left/black.png"

#define LIGHT_RED_TURN_RIGHT_PATH ":/src/trafficLight/arrows/right/red.png"
#define LIGHT_GREEN_TURN_RIGHT_PATH ":/src/trafficLight/arrows/right/green.png"
#define LIGHT_YELLOW_TURN_RIGHT_PATH ":/src/trafficLight/arrows/right/yellow.png"
#define LIGHT_BLACK_TURN_RIGHT_PATH ":/src/trafficLight/arrows/right/black.png"

#define LIGHT_RED_TURN_BACK_PATH ":/src/trafficLight/arrows/back/red.png"
#define LIGHT_GREEN_TURN_BACK_PATH ":/src/trafficLight/arrows/back/green.png"
#define LIGHT_YELLOW_TURN_BACK_PATH ":/src/trafficLight/arrows/back/yellow.png"
#define LIGHT_BLACK_TURN_BACK_PATH ":/src/trafficLight/arrows/back/black.png"

#define LIGHT_RED_UNKNOWN_PATH ":/src/trafficLight/unknown/red.png"
#define LIGHT_GREEN_UNKNOWN_PATH ":/src/trafficLight/unknown/green.png"
#define LIGHT_YELLOW_UNKNOWN_PATH ":/src/trafficLight/unknown/yellow.png"
#define LIGHT_BLACK_UNKNOWN_PATH ":/src/trafficLight/unknown/black.png"

TrafficLight::TrafficLight(e_trafficLightColor color,
                           int id, QWidget *parent)
    : QPushButton{parent}
    , m_color(color)
    , m_id(id)
{

}

QString TrafficLight::getImgPath()
{
    switch(m_color){
    case e_trafficLightColor::RED:
        switch(m_direction){
        case e_direction::CIRCLE:
            return LIGHT_RED_PATH;
            break;
        case e_direction::GO_STRAIGHT:
            return LIGHT_RED_GO_STRAIGHT_PATH;
            break;
        case e_direction::TURN_LEFT:
            return LIGHT_RED_TURN_LEFT_PATH;
            break;
        case e_direction::TURN_RIGHT:
            return LIGHT_RED_TURN_RIGHT_PATH;
            break;
        case e_direction::TURN_BACK:
            return LIGHT_RED_TURN_BACK_PATH;
            break;
        default:
            return LIGHT_RED_UNKNOWN_PATH;
            break;
        }
        break;
    case e_trafficLightColor::GREEN:
        switch(m_direction){
        case e_direction::CIRCLE:
            return LIGHT_GREEN_PATH;
            break;
        case e_direction::GO_STRAIGHT:
            return LIGHT_GREEN_GO_STRAIGHT_PATH;
            break;
        case e_direction::TURN_LEFT:
            return LIGHT_GREEN_TURN_LEFT_PATH;
            break;
        case e_direction::TURN_RIGHT:
            return LIGHT_GREEN_TURN_RIGHT_PATH;
            break;
        case e_direction::TURN_BACK:
            return LIGHT_GREEN_TURN_BACK_PATH;
            break;
        default:
            return LIGHT_GREEN_UNKNOWN_PATH;
            break;
        }
    case e_trafficLightColor::YELLOW:
        switch(m_direction){
        case e_direction::CIRCLE:
            return LIGHT_YELLOW_PATH;
            break;
        case e_direction::GO_STRAIGHT:
            return LIGHT_YELLOW_GO_STRAIGHT_PATH;
            break;
        case e_direction::TURN_LEFT:
            return LIGHT_YELLOW_TURN_LEFT_PATH;
            break;
        case e_direction::TURN_RIGHT:
            return LIGHT_YELLOW_TURN_RIGHT_PATH;
            break;
        case e_direction::TURN_BACK:
            return LIGHT_YELLOW_TURN_BACK_PATH;
            break;
        default:
            return LIGHT_YELLOW_UNKNOWN_PATH;
            break;
        }
        break;
    case e_trafficLightColor::BLACK:
        switch(m_direction){
        case e_direction::CIRCLE:
            return LIGHT_BLACK_PATH;
            break;
        case e_direction::GO_STRAIGHT:
            return LIGHT_BLACK_GO_STRAIGHT_PATH;
            break;
        case e_direction::TURN_LEFT:
            return LIGHT_BLACK_TURN_LEFT_PATH;
            break;
        case e_direction::TURN_RIGHT:
            return LIGHT_BLACK_TURN_RIGHT_PATH;
            break;
        case e_direction::TURN_BACK:
            return LIGHT_BLACK_TURN_BACK_PATH;
            break;
        default:
            return LIGHT_BLACK_UNKNOWN_PATH;
            break;
        }
        break;
    default:
        break;

    }
}

int TrafficLight::getId()
{
    return m_id;
}

QString TrafficLight::getColor()
{
    switch (m_color) {
    case e_trafficLightColor::RED:
        return "红色";
        break;
    case e_trafficLightColor::GREEN:
        return "绿色";
        break;
    case e_trafficLightColor::YELLOW:
        return "黄色";
        break;
    case e_trafficLightColor::BLACK:
        return "黑色";
        break;
    default:
        return "未知";
        break;
    }
}

void TrafficLight::setLightColor(e_trafficLightColor color)
{
    if(m_color == color){
        m_lightSec++;
        return;
    }

    m_lightSec = 0;
    m_color = color;

}

void TrafficLight::setLightDirection(e_direction direction)
{
    m_direction = direction;
}

void TrafficLight::setLightLane(e_lane lane)
{
    m_lane = lane;
}

QString TrafficLight::getLightDirection()
{

    switch (m_direction) {
    case e_direction::CIRCLE:
        return "圆灯";
        break;
    case e_direction::TURN_LEFT:
        return "左转箭头";
        break;
    case e_direction::GO_STRAIGHT:
        return "直行箭头";
        break;
    case e_direction::TURN_RIGHT:
        return "右转箭头";
        break;
    case e_direction::TURN_BACK:
        return "掉头";
        break;
    default:
        return "未知";
        break;
    }
}

e_lane TrafficLight::getLightLane()
{
    return m_lane;
}

e_direction TrafficLight::getLightDirectionE()
{
    return m_direction;
}

int TrafficLight::getLightSec()
{
    return m_lightSec/10;
}

void TrafficLight::updateLightSec(e_trafficLightColor color)
{
    if(color == e_trafficLightColor::BLACK && m_lightSec >= 999){
        m_lightSec = 999;
    }
    if(color == m_color){
        m_lightSec++;
    }else{
        m_lightSec = 0;
    }
}

void TrafficLight::updateStytle()
{
    QString stytle = QString("border-image: url(%1);").arg(getImgPath());
    setStyleSheet(stytle);
    resize(60, 60);
}

QString TrafficLight::getStytle()
{
    return QString("border-image: url(%1);").arg(getImgPath());
}

bool TrafficLight::CONDITTION0IsTrue(e_trafficLightColor color)
{
    qDebug() << "color: " << "    " << (int)color;
    qDebug() << "m_color: " << "    " << (int)m_color;
    if(m_color == color){
        return true;
    }
    return false;
}

bool TrafficLight::CONDITTION1IsTrue(int sec)
{
    if(m_lightSec/10 >= sec){
        return true;
    }
    return false;
}

bool TrafficLight::CONDITTION2IsTrue()
{

    return false;
}

bool TrafficLight::CONDITTION3IsTrue()
{
    return false;
}

bool TrafficLight::CONDITTION4IsTrue()
{
    return false;
}

bool TrafficLight::CONDITTION5IsTrue()
{
    return false;
}

void TrafficLight::executeAllTasks(QList<e_lightExecuteTask> *e_executeTaskList)
{

    QStringList taskList;


    for(int i=0; i<e_executeTaskList->size(); i++){

        taskList << QString::number(((int)(e_executeTaskList->at(i))));

    }

    emit tmpScreenExecuteTasks(taskList);

    // for(int i=0; i<e_executeTaskList->size(); i++){
    //     e_lightExecuteTask executeTask =  e_executeTaskList->at(i);
    //     switch (executeTask) {
    //     case e_lightExecuteTask::TASK0:
    //         executeTask0();
    //         break;
    //     case e_lightExecuteTask::TASK1:
    //         executeTask1();
    //         break;
    //     case e_lightExecuteTask::TASK2:
    //         executeTask2();
    //         break;
    //     case e_lightExecuteTask::TASK3:
    //         executeTask3();
    //         break;
    //     case e_lightExecuteTask::TASK4:
    //         executeTask4();
    //         break;
    //     case e_lightExecuteTask::TASK5:
    //         executeTask5();
    //         break;
    //         break;
    //     default:
    //         break;
    //     }
    // }
}

QString TrafficLight::executeTask0()
{
    QString msg = "执行任务 0 ";

    // switch (m_direction) {
    // case e_direction::TURN_LEFT:
    //     msg = "禁止左转";
    //     break;
    // case e_direction::GO_STRAIGHT:
    //     msg = "禁止直行";
    //     break;
    // case e_direction::TURN_RIGHT:
    //     msg = "禁止右转";
    //     break;
    // case e_direction::TURN_BACK:
    //     msg = "禁止掉头";
    //     break;
    // default:
    //     msg = "禁止通行";
    //     break;
    // }

    emit showMsg(msg);
    return msg;
}

QString TrafficLight::executeTask1()
{
    QString msg = "执行任务 1";

    // switch (m_direction) {
    // case e_direction::TURN_LEFT:
    //     msg = "可以左转";
    //     break;
    // case e_direction::GO_STRAIGHT:
    //     msg = "可以直行";
    //     break;
    // case e_direction::TURN_RIGHT:
    //     msg = "可以右转";
    //     break;
    // case e_direction::TURN_BACK:
    //     msg = "可以掉头";
    //     break;
    // default:
    //     msg = "可以通行";
    //     break;
    // }

    emit showMsg(msg);

    return msg;
}

QString TrafficLight::executeTask2()
{
    QString msg = "执行任务 2";

    emit showMsg(msg);

    return msg;
}

QString TrafficLight::executeTask3()
{
    QString msg = "执行任务 3";

    emit showMsg(msg);

    return msg;
}

QString TrafficLight::executeTask4()
{
    QString msg = "执行任务 4";

    emit showMsg(msg);

    return msg;
}

QString TrafficLight::executeTask5()
{
    QString msg = "执行任务 5";

    emit showMsg(msg);

    return msg;
}

bool TrafficLight::conitionIsTrue(e_lightCondition condition, QStringList args)
{
    switch (condition) {
    case e_lightCondition::CONDITTION0:
        if(CONDITTION0IsTrue((e_trafficLightColor)args.at(0).toInt()))return true;
        break;
    case e_lightCondition::CONDITTION1:
        if(CONDITTION1IsTrue(args.at(0).toInt()))return true;
        break;
    case e_lightCondition::CONDITTION2:
        if(CONDITTION2IsTrue())return true;
        break;
    case e_lightCondition::CONDITTION3:
        if(CONDITTION3IsTrue())return true;
        break;
    case e_lightCondition::CONDITTION4:
        if(CONDITTION4IsTrue())return true;
        break;
    default:
        break;
    }
    return false;
}
