#include <qdbusdaemon/Base.h>

#include <QProcessEnvironment>

namespace QDBusDaemon
{

QStringList Base::environmentVariables()
{
    QProcessEnvironment env;
    env.insert("DBUS_SESSION_BUS_PID", QString("%1").arg(pid()));
    env.insert("DBUS_SESSION_BUS_ADDRESS", address());
    return env.toStringList();
}

}

