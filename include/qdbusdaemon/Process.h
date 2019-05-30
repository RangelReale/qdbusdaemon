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
    Process();
    ~Process();

    bool isConnected();
    QString address() const;
public Q_SLOTS:
    void start();
    void stop();
private:
    QProcess *_process;
};

}

#endif // H__QDBUSDAEMON_PROCESS__H
