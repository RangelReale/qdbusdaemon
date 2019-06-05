#include <qdbusdaemon/Static.h>

#include <QMetaObject>

namespace QDBusDaemon
{

Static::Static(QObject *parent) :
    Base(parent), _started(false), _connected(false), _pid(-1)
{

}

Static::~Static()
{
}

bool Static::isStarted()
{
    return _started;
}

bool Static::isConnected()
{
    return _connected;
}

Q_PID Static::pid() const
{
    if (_started)
    {
        return _pid;
    }
    return 0;
}

QString Static::address() const
{
    return _address;
}

void Static::start()
{
    if (!_started)
    {
        QMetaObject::invokeMethod(this, "error", Qt::QueuedConnection, Q_ARG(QString, "DBus daemon not started"));
    }
}

void Static::stop()
{
}

void Static::setStarted(bool is_started, Q_PID pid)
{
    bool last_started = _started;
    _started = is_started;
    _pid = pid;
    if (!is_started)
    {
        setConnected(false);
    }
    if (is_started && !last_started)
    {
        emit started();
    }
    else if (!is_started && last_started)
    {
        emit finished();
    }
}

void Static::setConnected(bool is_connected, const QString &address)
{
    bool last_connected = _connected;
    _connected = is_connected;
    _address = address;
    if (is_connected && !last_connected)
    {
        emit connected();
    }
    else if (!is_connected && last_connected)
    {
        emit disconnected();
    }
}

void Static::setError(const QString &errorMessage)
{
    emit error(errorMessage);
}

}
