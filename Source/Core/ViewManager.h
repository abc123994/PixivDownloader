#pragma once
#include "QtWidgets/qstackedwidget.h"
class Downloader;
class Login;
class HttpMethods;
class ViewManager :
	public QObject
{
	Q_OBJECT
public:
	ViewManager(QObject* parent=0);
	~ViewManager();
public slots:
	void ToDownload();
	void InitWidget();
private:
	QStackedWidget* m_mainwindow;
	Downloader* m_downloader;
	Login* m_login;
	HttpMethods* m_web;
	QThread* m_working_thread;
};

