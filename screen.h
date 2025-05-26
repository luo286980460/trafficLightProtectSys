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
    explicit Screen(QString ip, int port, QObject *parent = nullptr);
    void post(QString jsonData);

    void executeAllTasks(QList<e_screenExecuteTask> *e_executeTaskList);

private:
    void init();

    void executeTask0();
    void executeTask1();
    void executeTask2();
    void executeTask3();
    void executeTask4();
    void executeTask5();

signals:
    void showMsg(QString msg);

public slots:
    void tmpScreenExecuteTasks(QStringList taskList);   // 临时方法,屏幕执行任务

private:
    QNetworkAccessManager* m_manager;
    QString m_url;
};

#endif // SCREEN_H
