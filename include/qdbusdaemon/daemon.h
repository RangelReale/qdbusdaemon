#ifndef H__QDBUSDAEMON_DAEMON__H
#define H__QDBUSDAEMON_DAEMON__H

#include <qdbusdaemon/qdbusdaemon.h>

#include <QProcess>

namespace QDBusDaemon
{

class Daemon : public QDBusDaemon
{
    Q_OBJECT
public:
    Daemon();
    ~Daemon();

    bool isConnected();
    QString address() const;
public Q_SLOTS:
    void start();
    void stop();
private:
    QProcess *_process;
};

}

#endif // H__QDBUSDAEMON_DAEMON__H
