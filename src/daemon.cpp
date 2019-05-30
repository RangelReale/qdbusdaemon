#include <qdbusdaemon/daemon.h>

namespace QDBusDaemon
{

Daemon::Daemon() : _process()
{

}

Daemon::~Daemon()
{

}

bool Daemon::isConnected()
{
    return false;
}

QString Daemon::address() const
{
    return QString();
}

void Daemon::start()
{

}

void Daemon::stop()
{

}

}
