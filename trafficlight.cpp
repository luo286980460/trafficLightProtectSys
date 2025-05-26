#include "trafficlight.h"
#include "qdebug.h"

TrafficLight::TrafficLight(e_trafficLightColor color, int id, QObject *parent)
    : QObject{parent}
    , m_color(color)
    , m_id(id)
{

}


int TrafficLight::getId()
{
    return m_id;
}

e_trafficLightColor TrafficLight::getColor()
{
    return m_color;
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

bool TrafficLight::CONDITTION0IsTrue(e_trafficLightColor color)
{
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
