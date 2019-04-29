#pragma once
#include "ui_Downloader.h"
#include "QtWidgets/qfiledialog.h"
class Downloader :
	public QWidget
{
	Q_OBJECT
public:
	Downloader();
	~Downloader();
	Ui::pixivDownloader* m_ui;
signals:
	void StartDownLoadUser(QString user_id,QString path);
	void StartDownLoadPic(QString pic_id,QString path);
	void StartDownLoadDaily(QString date, QString path);
public slots:
	void on_btn_download_user_clicked();
	void on_btn_download_pic_clicked();
	void on_btn_download_daily_clicked();
	void ShowSatus(QString status);
	void Reset();
private:
	QFileDialog m_filedialog;
};

