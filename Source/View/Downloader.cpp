#include "../stdafx.h"
#include "Downloader.h"



Downloader::Downloader()
{
	m_ui = new Ui::pixivDownloader;
	m_ui->setupUi(this);
	m_ui->calendarWidget->setMaximumDate(QDate::currentDate().addDays(-1));;
	m_ui->calendarWidget->setSelectedDate(QDate::currentDate().addDays(-1));
	m_ui->tabWidget->setCurrentIndex(0);
	m_filedialog.setAttribute(Qt::WidgetAttribute::WA_QuitOnClose, false);
}


Downloader::~Downloader()
{
}
void Downloader::on_btn_download_user_clicked()
{
	
	this->m_ui->tabWidget->setEnabled(false);
	m_filedialog.setDirectory(QDir::current());
	m_filedialog.setFileMode(QFileDialog::FileMode::DirectoryOnly);
	m_filedialog.setOption(QFileDialog::ShowDirsOnly, false);
	if (m_filedialog.exec() == QDialog::Accepted) {

		qDebug() << m_filedialog.directory().absolutePath();
		StartDownLoadUser(this->m_ui->edit_userid->text().trimmed(), m_filedialog.directory().absolutePath());
		qDebug() << "download start...";
	}
	
	
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
	m_filedialog.setDirectory(QDir::current());
	m_filedialog.setFileMode(QFileDialog::FileMode::DirectoryOnly);
	m_filedialog.setOption(QFileDialog::ShowDirsOnly, false);

	if (m_filedialog.exec() == QDialog::Accepted) {
		StartDownLoadPic(this->m_ui->edit_illustid->text().trimmed(), m_filedialog.directory().absolutePath());
		this->m_ui->tabWidget->setEnabled(false);
	}
}
void Downloader::on_btn_download_daily_clicked()
{
	m_filedialog.setDirectory(QDir::current());
	m_filedialog.setFileMode(QFileDialog::FileMode::DirectoryOnly);
	m_filedialog.setOption(QFileDialog::ShowDirsOnly, false);
	if (m_filedialog.exec() == QDialog::Accepted) {

		qDebug() << m_ui->calendarWidget->selectedDate().toString("yyyyMMdd");
		StartDownLoadDaily(m_ui->calendarWidget->selectedDate().toString("yyyyMMdd"), m_filedialog.directory().absolutePath());
		qDebug() << "on btn daily download...";
		this->m_ui->tabWidget->setEnabled(false);
	}
}
#include "Downloader.moc"