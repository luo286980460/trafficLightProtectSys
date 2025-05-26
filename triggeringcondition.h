#ifndef TRIGGERINGCONDITION_H
#define TRIGGERINGCONDITION_H

#include <QObject>
#include <QPushButton>

class TriggeringCondition : public QPushButton
{
    Q_OBJECT
public:
    TriggeringCondition(QWidget *parent = nullptr);
    // id
    void setId(int id);
    int getId();

    // name
    void setName(QString name);
    QString getName();

private:
    void init();

private:
    int m_id = 1;
    QString m_name;
};

#endif // TRIGGERINGCONDITION_H
