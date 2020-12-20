#ifndef PREPARE_THREAD_H
#define PREPARE_THREAD_H

#include <QObject>
#include <QDebug>
#include <QProcess>

class PrepareThread : public QObject
{
    private:
        Q_OBJECT

    public:
        explicit PrepareThread();
        ~PrepareThread() {};

        int copyFile(QString origin_file, QString copied_script);
        void closeShell();

    public slots:
        void prepareStart();

    signals:
        void prepareMsg(const QString &message);
        void prepareErrMsg(const QString &error);
        void prepareFinished();

    private:
        QString origin_script = "";
        QString copied_script = "";
        QString prepare_script = "/tmp/get_ip.sh";
        QProcess *myProcess;
};

#endif // PREPARE_THREAD_H

