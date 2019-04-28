#include "../stdafx.h"
#include "Login.h"

#include "ui_Login.h"

Login::Login()
{
	m_ui = new Ui::Login;
	m_ui->setupUi(this);

}


Login::~Login()
{
}
void Login::on_btn_login_clicked()
{
	qDebug() << "login...";
	this->m_ui->btn_login->setEnabled(false);
	emit StartLogin(this->m_ui->edit_user->text(), this->m_ui->edit_psw->text());

}
void Login::showEvent(QShowEvent *event)
{
	qDebug() << "on login show...";
	this->m_ui->btn_login->setEnabled(true);
}

#include "Login.moc"