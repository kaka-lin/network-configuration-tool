#include <QFile>
#include <QFileInfo>
#include <QDirIterator>

#include "prepare_thread.h"

PrepareThread::PrepareThread()
{
    myProcess = new QProcess(this);
}

int PrepareThread::copyFile(QString origin_file, QString copied_script)
{
    int ret;

    if (QFile::exists(copied_script)) {
        emit prepareMsg("File exists!");
        return 1;
    }

    ret = QFile::copy(origin_file, copied_script);
    if(!ret) {
        emit prepareErrMsg("Load file failed!");
        return -1;
    }

    copied_script.prepend("chmod +x ");
    copied_script.append("\n");
    ret = myProcess->write(copied_script.toUtf8());
    if (ret == -1) {
        emit prepareErrMsg("Change file permission failed!");
        return -1;
    }

    return 1;
}

void PrepareThread::prepareStart()
{
    int ret = 0;
    QByteArray cmd;
    QString address;
    QString program = "/bin/bash";
    bool isError = false;

    myProcess->start(program, QIODevice::ReadWrite);
    if (!myProcess->waitForStarted()) {
        emit prepareErrMsg("Not start!");
        emit prepareFinished();
        return;
    }

    QDirIterator it(":/scripts/", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        origin_script = it.next();
        copied_script = "/tmp/" + it.fileName();
        //qDebug() << origin_script << copied_script;

        ret = copyFile(origin_script, copied_script);
        if (!ret) {
            emit prepareErrMsg("File open failed!");

            closeShell();
            myProcess->kill();
            emit prepareFinished();
            return;
        }
    }

    if (!QFile::exists(prepare_script)) {
        emit prepareErrMsg("File not exists!");
        return;
    }

    // Start command -> (mount and cd)
    prepare_script.append("\n");
    cmd = prepare_script.toUtf8();
    ret = myProcess->write(cmd);
    if (ret == -1) {
        emit prepareErrMsg("Command failed!");

        closeShell();
        myProcess->kill();
        emit prepareFinished();
        return;
    }

    qDebug() << "---------- Start bash shell! ----------";
    while(true) {
        if (isError)
            break;

        ret = myProcess->waitForReadyRead(3000); //msecs
        if(!ret) {
            break;
        }

        while (myProcess->canReadLine()) {
            address = myProcess->readLine();
            emit prepareMsg(address);
        }

        break;
    }

    closeShell();
    myProcess->kill();

    emit prepareFinished();
}

void PrepareThread::closeShell()
{
    myProcess->write("exit\n");
    if (!myProcess->waitForFinished()) {
        emit prepareMsg("Bash shell not Finished!");
    }
}
