#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QPushButton>

enum class e_lane{  // 车道
    CAR,
    BICYCLE,
    WALKER,
    UNKNOWN
};

enum class e_trafficLightColor{  // 红绿灯颜色
    UNKNOWN,
    RED,
    GREEN,
    YELLOW,
    BLACK
};

enum class e_direction{     // 信号灯方向
    CIRCLE,                 // 无方向
    TURN_LEFT,              // 左转
    GO_STRAIGHT,            // 直行
    TURN_RIGHT,             // 右转
    TURN_BACK,              // 掉头,
    UNKNOWN
};


enum class e_condition{   // 条件列表
    CONDITTION0,        // 灯为红色时
    CONDITTION1,        // 灯为绿色时
    CONDITTION2,        // 灯为黄色时
    CONDITTION3,        // 灯为黑色时
    CONDITTION4,
    CONDITTION5,
};

enum class e_lightCondition{   // 条件列表
    CONDITTION0,        // 灯为红色时
    CONDITTION1,        // 灯为绿色时
    CONDITTION2,        // 灯为黄色时
    CONDITTION3,        // 灯亮的时间 >= 多少s
    CONDITTION4,
    CONDITTION5,
};

enum class e_lightExecuteTask{   // 任务列表
    TASK0,              // 禁止通行
    TASK1,              // 可以通行
    TASK2,
    TASK3,
    TASK4,
    TASK5,
    };

class TrafficLight : public QPushButton
{
    Q_OBJECT
public:
    explicit TrafficLight(e_trafficLightColor color,
                          int id, QWidget *parent = nullptr);

    QString getImgPath();
    int getId();
    QString getColor();
    QString getLightDirection();
    e_lane getLightLane();
    e_direction getLightDirectionE();
    int getLightSec();
    void updateLightSec(e_trafficLightColor color);
    void updateBorderImg(e_trafficLightColor color);


    void setLightColor(e_trafficLightColor color);
    void setLightDirection(e_direction direction);
    void setLightLane(e_lane lane);

    void updateStytle();
    QString getStytle();

    bool CONDITTION0IsTrue(e_trafficLightColor color);   // 颜色为 color 时
    bool CONDITTION1IsTrue(int sec);                     // 亮灯时间 >= sec
    bool CONDITTION2IsTrue();
    bool CONDITTION3IsTrue();
    bool CONDITTION4IsTrue();
    bool CONDITTION5IsTrue();

    void executeAllTasks(QList<e_lightExecuteTask> *e_executeTaskList);
    QString executeTask0();
    QString executeTask1();
    QString executeTask2();
    QString executeTask3();
    QString executeTask4();
    QString executeTask5();

    bool conitionIsTrue(e_lightCondition condition, QStringList args);

signals:
    void showMsg(QString msg);
    void tmpScreenExecuteTasks(QStringList taskList);   // 临时方法,让屏幕执行任务

protected:
    e_trafficLightColor m_color = e_trafficLightColor::UNKNOWN;;
    e_direction m_direction = e_direction::UNKNOWN;;
    e_lane m_lane = e_lane::UNKNOWN;
    int m_id;
    int m_lightSec = 0;
};

#endif // TRAFFICLIGHT_H
