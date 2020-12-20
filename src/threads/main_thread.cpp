#include "main_thread.h"
#include "prepare_thread.h"

MainThread::MainThread(QObject *parent) : QObject(parent)
{
}

MainThread::~MainThread()
{
}

void MainThread::prepareStart()
{
    QThread *thread = new QThread(0);
    qDebug() << ">>> Prepare Thread Start <<<";
    PrepareThread *worker = new PrepareThread();
    threads["prepare"] = thread;
    worker->moveToThread(thread);

    connect(worker, &PrepareThread::prepareMsg, this, &MainThread::prepareMsg);
    connect(worker, &PrepareThread::prepareErrMsg, this, &MainThread::prepareErrMsg);
    connect(worker, &PrepareThread::prepareFinished, this, &MainThread::prepareFinished);

    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::started, worker, &PrepareThread::prepareStart);

    thread->start();
}

void MainThread::prepareFinished()
{
    QThread *thread;
    if (threads.contains("prepare")) {
        thread = threads.value("prepare");
        thread->quit();
        thread->wait();
        qDebug() << ">>> Prepare Thread Finish <<<";
    }
}
