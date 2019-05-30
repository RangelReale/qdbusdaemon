#include <qdbusdaemon/Process.h>

namespace QDBusDaemon
{

Process::Process() : _process(NULL), _executable("dbus-daemon"), _executableParams()
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

const QString &Process::executable() const
{
    return _executable;
}

void Process::setExecutable(const QString &value)
{
    _executable = value;
}

QStringList &Process::executableParams()
{
    return _executableParams;
}

void Process::start()
{
    _process = new QProcess();

    connect(_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));

    QStringList params;
    params << "--session" << "--nofork" << "--print-address";
    params.append(_executableParams);

    _process->start(_executable, params);
}

void Process::stop()
{

}

void Process::processError(QProcess::ProcessError error)
{
}

void Process::processStarted()
{

}

void Process::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{

}

void Process::processReadyReadStandardError()
{

}

void Process::processReadyReadStandardOutput()
{

}

}
