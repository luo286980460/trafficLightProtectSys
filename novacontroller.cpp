#include "novacontroller.h"
#include "novacontrollerworker.h"
#include "qjsonobject.h"

NovaController::NovaController(QString ip, int Back2DefaultProgram, QObject *parent)
    : QObject{parent}
{
    m_work = new NovaControllerWorker(ip, Back2DefaultProgram);
    m_work->moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::finished, m_work, &QObject::deleteLater);

    connect(this, &NovaController::signalInitWorker, m_work,&NovaControllerWorker::slotInit);
    connect(this, &NovaController::signalPlayProgram1, m_work,&NovaControllerWorker::slotPlayProgram1);
    connect(this, &NovaController::signalPlayProgram2, m_work,&NovaControllerWorker::slotPlayProgram2);
    connect(this, &NovaController::signalPlayProgram3, m_work,&NovaControllerWorker::slotPlayProgram3);
    connect(this, &NovaController::signalSetDefaultTxt, m_work,&NovaControllerWorker::slotSetDefaultTxt);
    connect(this, &NovaController::signalSetDefaultPic, m_work,&NovaControllerWorker::slotSetDefaultPic);
    connect(this, &NovaController::signalSetCurrentDefaultProgram, m_work,&NovaControllerWorker::slotSetCurrentDefaultProgram);
    connect(this, &NovaController::signalPlayPicProgramByPicName, m_work,&NovaControllerWorker::slotPlayPicProgramByPicName);
}

NovaController::~NovaController()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

void NovaController::start()
{
    m_workerThread.start();
    emit signalInitWorker();
}

void NovaController::stop()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

int NovaController::getId()
{
    return m_id;
}

bool NovaController::executeTaskIsDone(e_screenExecuteTask executeTask, QStringList args)
{
    switch (executeTask) {
    case e_screenExecuteTask::TASK0:
        executeTask0(args.at(0));
        break;
    case e_screenExecuteTask::TASK1:
        executeTask1();
        break;
    case e_screenExecuteTask::TASK2:
        executeTask2();
        break;
    case e_screenExecuteTask::TASK3:
        executeTask3();
        break;
    case e_screenExecuteTask::TASK4:
        executeTask4();
        break;
    case e_screenExecuteTask::TASK5:
        executeTask5();
        break;
    default:
        break;
    }
    return true;
}
void NovaController::executeTask0(QString content)
{
    emit signalPlayPicProgramByPicName(content);
    return;
}

void NovaController::executeTask1()
{

}

void NovaController::executeTask2()
{

}
void NovaController::executeTask3()
{

}
void NovaController::executeTask4()
{

}
void NovaController::executeTask5()
{

}

