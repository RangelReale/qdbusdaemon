#include <qdbusdaemon/Process.h>

namespace QDBusDaemon
{

Process::Process() : _process()
{

}

Process::~Process()
{

}

bool Process::isConnected()
{
    return false;
}

QString Process::address() const
{
    return QString();
}

void Process::start()
{

}

void Process::stop()
{

}

}
