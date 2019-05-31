#include "MainWindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>

MainWindow::MainWindow() : QMainWindow()
{
    _dbprocess = new QDBusDaemon::Process(this);

    connect(_dbprocess, SIGNAL(error(QString)), this, SLOT(error(QString)));
    connect(_dbprocess, SIGNAL(started()), this, SLOT(started()));
    connect(_dbprocess, SIGNAL(connected()), this, SLOT(connected()));
    connect(_dbprocess, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_dbprocess, SIGNAL(finished()), this, SLOT(finished()));
    connect(_dbprocess, SIGNAL(restarting()), this, SLOT(restarting()));

    _list = new QListWidget(this);
    setCentralWidget(_list);

	QMenu* actmenu = menuBar()->addMenu("&Actions");

	QAction *startmenu = actmenu->addAction("&Start");
	connect(startmenu, SIGNAL(triggered(bool)), this, SLOT(menuStart(bool)));

	QAction *stopmenu = actmenu->addAction("S&top");
	connect(stopmenu, SIGNAL(triggered(bool)), this, SLOT(menuStop(bool)));
}

void MainWindow::menuStart(bool)
{
    _dbprocess->start();
}

void MainWindow::menuStop(bool)
{
    _dbprocess->stop();
}

void MainWindow::error(QString message)
{
    new QListWidgetItem(QString("ERROR: %1").arg(message), _list);
}

void MainWindow::started()
{
    new QListWidgetItem("STARTED", _list);
}

void MainWindow::connected()
{
    new QListWidgetItem(QString("CONNECTED: %1").arg(_dbprocess->address()), _list);
}

void MainWindow::disconnected()
{
    new QListWidgetItem("DISCONNECTED", _list);
}

void MainWindow::finished()
{
    new QListWidgetItem("FINISHED", _list);
}

void MainWindow::restarting()
{
    new QListWidgetItem("RESTARTING", _list);
}
