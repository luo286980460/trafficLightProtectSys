#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>

class QNetworkAccessManager;

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
    bool executeTaskIsDone(e_screenExecuteTask executeTask, QStringList args);      // 执行结果为真

private:
    void init();
    void post2Screen(QString url, QString jsonData);
    void post(QString url);
    void executeTask0(QString content);
    void executeTask1();
    void executeTask2();
    void executeTask3();
    void executeTask4();
    void executeTask5();


signals:



private:
    QNetworkAccessManager* m_manager;
    int m_id = 1;
    QString m_ip;
    int m_port;
};

#endif // SCREEN_H
