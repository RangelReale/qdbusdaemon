#ifndef H_MAINWINDOW_H
#define H_MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

#include <qdbusdaemon/Process.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
public Q_SLOTS:
    void error(QString message);
    void started();
    void connected();
    void disconnected();
    void finished();
    void restarting();

    void menuStart(bool);
    void menuStop(bool);
private:
    QDBusDaemon::Process* _dbprocess;
    QListWidget *_list;
};

#endif // H_MAINWINDOW_H
