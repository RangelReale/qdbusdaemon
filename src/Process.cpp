#include <qdbusdaemon/Process.h>

namespace QDBusDaemon
{

Process::Process(QObject *parent) :
    Base(parent), _started(false), _connected(false), _process(NULL),
    _executable("dbus-daemon"), _executableParams()
{

}

Process::~Process()
{

}

bool Process::isConnected()
{
    return _connected;
}

QString Process::address() const
{
    return _address;
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
    if (!_started)
    {
        _address.clear();

        if (_process) delete _process;
        _process = new QProcess();

        connect(_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));
        connect(_process, SIGNAL(started()), this, SLOT(processStarted()));
        connect(_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));
        connect(_process, SIGNAL(readyReadStandardError()), this, SLOT(processReadyReadStandardError()));
        connect(_process, SIGNAL(readyReadStandardOutput()), this, SLOT(processReadyReadStandardOutput()));

        QStringList params;
        params << "--session" << "--nofork" << "--print-address";
        params.append(_executableParams);

        _started = true;
        _process->start(_executable, params);
    }
}

void Process::stop()
{
    if (_started)
    {
        _started = false;
        _process->terminate();
    }
}

void Process::processError(QProcess::ProcessError err)
{
    QString errorMessage("Process error");
    switch (err) {
    case QProcess::ProcessError::FailedToStart: errorMessage += ": Failed to start"; break;
    case QProcess::ProcessError::Crashed: errorMessage += ": Crashed"; break;
    case QProcess::ProcessError::Timedout: errorMessage += ": Timed out"; break;
    case QProcess::ProcessError::ReadError: errorMessage += ": Read error"; break;
    case QProcess::ProcessError::WriteError: errorMessage += ": Write error"; break;
    default: break;
    }

    emit error(errorMessage);
}

void Process::processStarted()
{
    if (_started)
    {
        emit started();
    }
}

void Process::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (_connected)
    {
        _connected = false;
        emit disconnected();
    }

    _process->deleteLater();
    _process = NULL;

    if (_started)
    {
        emit restarting();

        // restart
        _started = false;
        emit start();
    }
    else
    {
        emit finished();
    }
}

void Process::processReadyReadStandardError()
{
    if (_started)
    {
        emit error(QString("Error output: %1").arg(QString::fromLocal8Bit(_process->readAll())));
    }
}

void Process::processReadyReadStandardOutput()
{
    if (_started)
    {
        if (_address.isEmpty())
        {
            _address = QString::fromLocal8Bit(_process->readAll().trimmed());
            emit connected();
        }
    }
}

}
