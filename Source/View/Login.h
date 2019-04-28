#pragma once
#include "ui_Login.h"
class UI_Login;
class Login :
	public QWidget
{
	Q_OBJECT
public:
	Login();
	~Login();
	Ui::Login* m_ui;
signals:
	void StartLogin(QString user_id,QString psw);
public slots:
	void on_btn_login_clicked();
protected:
	virtual void showEvent(QShowEvent *event);
}

;