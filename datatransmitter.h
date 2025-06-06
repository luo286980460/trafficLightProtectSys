#ifndef DATATRANSMITTER_H
#define DATATRANSMITTER_H

#include <QObject>

class QTimer;

enum class e_dataTransmitterExecuteTask{   // 可执行的任务
    TASK0,      // 给指定接口发送数据
    TASK1,
    TASK2,
    TASK3,
    TASK4,
    TASK5,
    };

class DataTransmitter : public QObject
{
    Q_OBJECT
public:
    explicit DataTransmitter(QObject *parent = nullptr);
    bool executeTaskIsDone(e_dataTransmitterExecuteTask executeTask, QStringList args);      // 执行结果为真

    void post(QString url, QByteArray dataJson);

private:
    void initTimer();
    void executeTask0(QString url);    // 给指定接口发送数据
    void executeTask1();
    void executeTask2();
    void executeTask3();
    void executeTask4();
    void executeTask5();



signals:

private:
    QTimer* m_updataTimer;  // 向后台更新数据的计时器
    QString m_url;          // 需要发送到后台的数据
    QByteArray m_data;      // 需要发送到后台的数据
};

#endif // DATATRANSMITTER_H
