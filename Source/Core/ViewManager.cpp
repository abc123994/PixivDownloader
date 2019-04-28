#include "../stdafx.h"
#include "ViewManager.h"
#include "../View/DownLoader.h"
#include "../View/Login.h"
#include "../Network/HttpMethods.h"
enum pages
{
	pg_login = 0,
	pg_download = 1,
};
ViewManager::ViewManager(QObject* p)
{
	m_working_thread = new QThread(this);
	m_web = new HttpMethods();
	m_web->moveToThread(m_working_thread);
	InitWidget();
	connect(m_login, SIGNAL(StartLogin(QString, QString)),m_web, SLOT(OnLogin(QString, QString)));
	connect(m_downloader, SIGNAL(StartDownLoadUser(QString)), m_web, SLOT(OnDownloadByUser(QString)),Qt::QueuedConnection);
	connect(m_downloader, SIGNAL(StartDownLoadPic(QString)), m_web, SLOT(OnDownloadByPic(QString)), Qt::QueuedConnection);
	connect(m_web, SIGNAL(current_proc(QString)), m_downloader, SLOT(ShowSatus(QString)));
	connect(m_web, SIGNAL(proc_done()), m_downloader, SLOT(Reset()));
	connect(m_web, SIGNAL(login_ok()), this,SLOT(ToDownload()));
	m_working_thread->start();
	m_mainwindow->show();
}


ViewManager::~ViewManager()
{
	m_working_thread->terminate();
	m_working_thread->deleteLater();
}
void ViewManager::ToDownload()
{
	m_mainwindow->setCurrentIndex(pages::pg_download);
	m_mainwindow->setCurrentWidget(m_downloader);
}
void ViewManager::InitWidget()
{
	m_mainwindow = new QStackedWidget;
	m_mainwindow->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
	m_downloader = new Downloader();
	m_login = new Login();
	m_mainwindow->addWidget(m_login);
	m_mainwindow->addWidget(m_downloader);
	m_mainwindow->setGeometry(0, 0, 400, 300);
	m_mainwindow->setCurrentIndex(pages::pg_login);
	m_mainwindow->setCurrentWidget(m_login);
}
#include "ViewManager.moc"