#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QMap>

class MainThread : public QObject
{
    private:
        Q_OBJECT

    public:
        MainThread(QObject *parent = nullptr);
        ~MainThread();

    public slots:
        void prepareStart();
        void prepareFinished();

    signals:
        void prepareMsg(const QString &message);
        void prepareErrMsg(const QString &error);

    private:
        QMap<QString, QThread *> threads;
};

#endif // MAIN_THREAD_H
