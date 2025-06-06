#ifndef NOVACONTROLLER_H
#define NOVACONTROLLER_H

#include <QObject>
#include <QThread>

class NovaControllerWorker;

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

class NovaController : public QObject
{
    Q_OBJECT
public:
    explicit NovaController(QString ip, int Back2DefaultProgram, QObject *parent = nullptr);
    ~NovaController();

    void start();
    void stop();
    int getId();
    bool executeTaskIsDone(e_screenExecuteTask executeTask, QStringList args);      // 执行结果为真

private:
    void executeTask0(QString content);
    void executeTask1();
    void executeTask2();
    void executeTask3();
    void executeTask4();
    void executeTask5();


signals:
    void signalInitWorker();
    void signalPlayProgram1(int fontSize, QString content, int audioTimes, QString voiceContent, int audioSwitch, int audiovolume);
    void signalPlayProgram2(QString base64);
    void signalPlayProgram3(int fontSize, QString content, int audioTimes, QString voiceContent,
                            int audioSwitch, int audiovolume , QString base64);
    void signalSetDefaultTxt(QString content, int size);    // 设置默认节目的内容
    void signalSetDefaultPic(QString base64);     // 设置默认节目的图片
    void signalSetCurrentDefaultProgram(int currentProgram);    // 设置当前默认节目的图片编号
    void signalPlayPicProgramByPicName(QString picName);    // 用文件名来播放图片节目(图片已经预制到屏幕内存)


private:
    QThread m_workerThread;                         // 作线程
    NovaControllerWorker *m_work = nullptr;         // 工作类
    int m_id = 1;
};

#endif // NOVACONTROLLER_H
