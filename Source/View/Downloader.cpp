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
void Downloader::on_btn_download_clicked()
{
	StartDownLoad(this->m_ui->edit_userid->text().trimmed());
	qDebug() << "download start...";
	m_ui->btn_download->setEnabled(false);
}
void Downloader::ShowSatus(QString str)
{
	this->m_ui->lbl_status->setText(str);
}
void Downloader::Reset()
{
	qDebug() << "enable btn";
	this->m_ui->btn_download->setEnabled(true);
}
#include "Downloader.moc"