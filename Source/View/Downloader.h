#pragma once
#include "ui_Downloader.h"

class Downloader :
	public QWidget
{
	Q_OBJECT
public:
	Downloader();
	~Downloader();
	Ui::pixivDownloader* m_ui;
signals:
	void StartDownLoadUser(QString user_id);
	void StartDownLoadPic(QString user_id);
public slots:
	void on_btn_download_user_clicked();
	void on_btn_download_pic_clicked();
	void ShowSatus(QString status);
	void Reset();
};

