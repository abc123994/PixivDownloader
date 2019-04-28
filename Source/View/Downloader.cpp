#include "../stdafx.h"
#include "Downloader.h"



Downloader::Downloader()
{
	m_ui = new Ui::pixivDownloader;
	m_ui->setupUi(this);
	
}


Downloader::~Downloader()
{
}
void Downloader::on_btn_download_user_clicked()
{
	StartDownLoadUser(this->m_ui->edit_userid->text().trimmed());
	qDebug() << "download start...";
	this->m_ui->tabWidget->setEnabled(false);
}
void Downloader::ShowSatus(QString str)
{
	this->m_ui->lbl_status->setText(str);
}
void Downloader::Reset()
{
	qDebug() << "enable btn";
	this->m_ui->tabWidget->setEnabled(true);
	this->m_ui->edit_illustid->setText("");
	this->m_ui->edit_userid->setText("");
}
void Downloader::on_btn_download_pic_clicked()
{
	StartDownLoadPic(this->m_ui->edit_illustid->text().trimmed());
	this->m_ui->tabWidget->setEnabled(false);
}
#include "Downloader.moc"