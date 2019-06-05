#ifndef H__QDBUSDAEMON_PROCESS__H
#define H__QDBUSDAEMON_PROCESS__H

#include <qdbusdaemon/Base.h>

#include <QProcess>
#include <QTimer>

namespace QDBusDaemon
{

class Process : public Base
{
    Q_OBJECT
public:
    Process(QObject *parent=0);
    ~Process();

    bool isStarted();
    bool isConnected();
    Q_PID pid() const;
    QString address() const;

    const QString &executable() const;
    void setExecutable(const QString &value);

    QStringList &executableParams();

    int connectTimeout() const;
    void setConnectTimeout(int value);
public Q_SLOTS:
    void start();
    void stop();
private:
    bool _started;
    bool _connected;
    int _connecttimeout;
    QProcess *_process;
    QString _executable;
    QStringList _executableParams;
    QString _address;
    QTimer _connecttimer;
private Q_SLOTS:
    void processTimeout();
    void processError(QProcess::ProcessError error);
    void processStarted();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processReadyReadStandardError();
    void processReadyReadStandardOutput();
};

}

#endif // H__QDBUSDAEMON_PROCESS__H
