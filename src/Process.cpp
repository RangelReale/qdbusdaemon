#include <qdbusdaemon/Process.h>

namespace QDBusDaemon
{

Process::Process(QObject *parent) :
    Base(parent), _started(false), _connected(false), _connecttimeout(2000), _process(NULL),
    _executable("dbus-daemon"), _executableParams()
{
    _connecttimer.setInterval(_connecttimeout);
    _connecttimer.setSingleShot(true);
    connect(&_connecttimer, SIGNAL(timeout()), this, SLOT(processTimeout()));
}

Process::~Process()
{
    if (_process)
    {
        stop();
        _process->waitForFinished();
    }
}

bool Process::isStarted()
{
    return _started;
}

bool Process::isConnected()
{
    return _connected;
}

Q_PID Process::pid() const
{
    if (_process)
    {
        return _process->pid();
    }
    return 0;
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

int Process::connectTimeout() const
{
    return _connecttimeout;
}

void Process::setConnectTimeout(int value)
{
    _connecttimeout = value;
    _connecttimer.setInterval(value);
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
        params
            << "--session"
            << "--nofork"
            << "--print-address";
        params.append(_executableParams);

        _started = true;

        if (_connecttimeout > 0)
        {
            _connecttimer.start();
        }
        _process->start(_executable, params);
    }
}

void Process::stop()
{
    if (_started)
    {
        _connecttimer.stop();
        _started = false;
        _process->terminate();
    }
}

void Process::processError(QProcess::ProcessError err)
{
    _connecttimer.stop();

    QString errorMessage("DBD process error");
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
    _connecttimer.stop();
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
        emit error(QString("DBus daemon error output: %1").arg(QString::fromLocal8Bit(_process->readAllStandardError())));
    }
}

void Process::processReadyReadStandardOutput()
{
    if (_started)
    {
        if (_address.isEmpty())
        {
            _address = QString::fromLocal8Bit(_process->readAllStandardOutput().trimmed());
            _connected = true;
            _connecttimer.stop();
            emit connected();
        }
    }
}

void Process::processTimeout()
{
    if (_process)
    {
        emit error(QString("Process connect timeout"));
        _process->kill();
    }
}

}
