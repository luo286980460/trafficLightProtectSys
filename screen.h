#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>

class QNetworkAccessManager;

enum class e_screenExecuteTask{   // 屏幕的可执行任务
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
    void post(QString url, QString jsonData);

    bool executeTaskIsDone(e_screenExecuteTask executeTask, QStringList args);      // 执行结果为真

private:
    void init();

    void executeTask0(QString content);
    void executeTask1();
    void executeTask2();
    void executeTask3();
    void executeTask4();
    void executeTask5();

signals:
    void showMsg(QString msg);

public slots:

private:
    QNetworkAccessManager* m_manager;
    QString m_ip;
    int m_port;
};

#endif // SCREEN_H
