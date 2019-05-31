#ifndef H__QDBUSDAEMON_PROCESS__H
#define H__QDBUSDAEMON_PROCESS__H

#include <qdbusdaemon/Base.h>

#include <QProcess>

namespace QDBusDaemon
{

class Process : public Base
{
    Q_OBJECT
public:
    Process(QObject *parent=0);
    ~Process();

    bool isConnected();
    QString address() const;

    const QString &executable() const;
    void setExecutable(const QString &value);

    QStringList &executableParams();
public Q_SLOTS:
    void start();
    void stop();
private:
    bool _started;
    bool _connected;
    QProcess *_process;
    QString _executable;
    QStringList _executableParams;
    QString _address;
private Q_SLOTS:
    void processError(QProcess::ProcessError error);
    void processStarted();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processReadyReadStandardError();
    void processReadyReadStandardOutput();
};

}

#endif // H__QDBUSDAEMON_PROCESS__H
