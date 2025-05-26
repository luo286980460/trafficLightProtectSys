#include "triggeringcondition.h"

TriggeringCondition::TriggeringCondition(QWidget *parent)
    :QPushButton(parent)
{
    init();
}

void TriggeringCondition::setId(int id)
{
    m_id = id;
}

int TriggeringCondition::getId()
{
    return m_id;
}

void TriggeringCondition::setName(QString name)
{
    m_name = name;
}

QString TriggeringCondition::getName()
{
    return m_name;
}

void TriggeringCondition::init()
{

}
