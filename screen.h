#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>

enum class e_screenCondition{   // 条件列表
    CONDITTION0,        // 灯为红色时
    CONDITTION1,        // 灯为绿色时
    CONDITTION2,        // 灯为黄色时
    CONDITTION3,
    CONDITTION4,
    CONDITTION5,
};

enum class e_screenExecuteTask{   // 可执行的任务
    TASK0,
    TASK1,
    TASK2,
    TASK3,
    TASK4,
    TASK5,
};


class Screen : public QObject
{
    Q_OBJECT
public:
    explicit Screen(QObject *parent = nullptr);
    int getId();

signals:

private:
    int m_id = 1;
};

#endif // SCREEN_H
