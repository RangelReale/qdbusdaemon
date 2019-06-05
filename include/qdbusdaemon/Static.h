#ifndef H__QDBUSDAEMON_STATIC__H
#define H__QDBUSDAEMON_STATIC__H

#include <qdbusdaemon/Base.h>

namespace QDBusDaemon
{

class Static : public Base
{
    Q_OBJECT
public:
    Static(QObject *parent=0);
    ~Static();

    bool isStarted();
    bool isConnected();
    Q_PID pid() const;
    QString address() const;

    void setStarted(bool started, Q_PID pid = -1);
    void setConnected(bool connected, const QString &address = QString());
    void setError(const QString &errorMessage);
public Q_SLOTS:
    void start();
    void stop();
private:
    bool _started, _connected;
    Q_PID _pid;
    QString _address;
};

}

#endif // H__QDBUSDAEMON_STATIC__H
