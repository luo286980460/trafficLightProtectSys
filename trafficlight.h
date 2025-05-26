#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QObject>

enum class e_lightCondition{   // 条件列表
    CONDITTION0,        // 灯为红色时
    CONDITTION1,        // 灯为绿色时
    CONDITTION2,        // 灯为黄色时
    CONDITTION3,        // 灯亮的时间 >= 多少s
    CONDITTION4,
    CONDITTION5,
};

enum class e_lightExecuteTask{   // 可执行的任务
    TASK0,
    TASK1,
    TASK2,
    TASK3,
    TASK4,
    TASK5,
};

enum class e_trafficLightColor{  // 红绿灯颜色
    UNKNOWN,
    RED,
    GREEN,
    YELLOW,
    BLACK
};

class TrafficLight : public QObject
{
    Q_OBJECT
public:
    explicit TrafficLight(e_trafficLightColor color, int id, QObject *parent = nullptr);

    int getId();
    e_trafficLightColor getColor();
    void setLightColor(e_trafficLightColor color);
    bool conitionIsTrue(e_lightCondition condition, QStringList args);

private:
    bool CONDITTION0IsTrue(e_trafficLightColor color);   // 颜色为 color 时
    bool CONDITTION1IsTrue(int sec);                     // 亮灯时间 >= sec
    bool CONDITTION2IsTrue();
    bool CONDITTION3IsTrue();
    bool CONDITTION4IsTrue();

signals:

private:
    e_trafficLightColor m_color = e_trafficLightColor::UNKNOWN;
    int m_id;
    int m_lightSec = 0;
};

#endif // TRAFFICLIGHT_H
