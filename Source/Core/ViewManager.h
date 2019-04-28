#pragma once
#include "QtWidgets/qstackedwidget.h"
class Downloader;
class Login;
class HttpMethods;
class ViewManager :
	public QObject
{
public:
	ViewManager(QObject* parent=0);
	~ViewManager();
private:
	QStackedWidget* m_mainwindow;
	Downloader* m_downloader;
	Login* m_login;
	HttpMethods* m_web;
};

