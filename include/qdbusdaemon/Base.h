#ifndef H__QDBUSDAEMON_BASE__H
#define H__QDBUSDAEMON_BASE__H

#include <QObject>
#include <QProcess>

namespace QDBusDaemon
{

class Base : public QObject
{
    Q_OBJECT
public:
    Base(QObject *parent) : QObject(parent) {}
    virtual ~Base() {}

    virtual bool isConnected() = 0;
    virtual QString address() const = 0;
public Q_SLOTS:
    virtual void start() = 0;
    virtual void stop() = 0;
Q_SIGNALS:
    void error(QString message);
    void restarting();
    void started();
    void connected();
    void disconnected();
    void finished();
};

}

#endif // H__QDBUSDAEMON_BASE__H
