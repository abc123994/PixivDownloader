#include "../stdafx.h"

#include "HttpMethods.h"
#include "curlpp/cURLpp.hpp"
#include "curlpp/Options.hpp"
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <regex>
#include<sstream>
#include <iostream>
#include <sstream>
#include <fstream>
#ifndef CURL_MAX_HTTP_HEADER
// workaround for older cURL versions
#define CURL_MAX_HTTP_HEADER CURL_MAX_WRITE_SIZE
#endif
//enum CURL_MAX_HTTP_HEADER = 102400;
// CURLOPT_COOKIEFILE request
// CURLOPT_COOKIEJAR response
using namespace std;
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
	if (userp)
	{
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if (os.write(static_cast<char*>(buf), len))
			return len;
	}

	return 0;
}
CURLcode curl_read(const std::string& url, std::ostream& os, long timeout, CURL* curl)
{
	CURLcode code(CURLE_FAILED_INIT);


	if (curl)
	{
		if (CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, data_write))
			&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L))
			&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt"))
			&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt"))
			&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
			&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
			&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
			&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())))
		{

			code = curl_easy_perform(curl);


		}
		else
		{
			printf("res = %d curl_easy_perform() failed: %s\n", code, curl_easy_strerror(code));
		}

	}
	return code;
}
void HttpMethods::ResetCURL()
{
	//;
	m_headers = NULL;
	curl_global_init(CURL_GLOBAL_ALL);
	m_curl = curl_easy_init();
	m_headers = curl_slist_append(m_headers, "Origin: https://accounts.pixiv.net");
	m_headers = curl_slist_append(m_headers,
		"User-Agent: Mozilla/5.0(Windows NT 10.0;Win64; x64)AppleWebKit/537.36 (KHTML,like Gecko)Chrome/73.0.3683.103Safari/37.36");
	m_headers = curl_slist_append(m_headers, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
	m_headers = curl_slist_append(m_headers, "Referer: https://accounts.pixiv.net/login?lang=zh&source=pc&view_type=page&ref=wwwtop_accounts_index");
	m_headers = curl_slist_append(m_headers, "X-Requested-With: XMLHttpRequest");
	curlpp::Cleanup myCleanup;
}





HttpMethods::HttpMethods(QObject* parent)
{
	
	connect(this, SIGNAL(ok()), this, SLOT(HandleDownLoad()), Qt::QueuedConnection);
	

}
void HttpMethods::OnStart(QString userid)
{
	this->ResetCURL();
	qDebug() << "OnStart...";
	m_userid = userid.toInt();
	GetAllIllust((char*)QString("https://www.pixiv.net/ajax/user/%1/profile/all").arg(QString::number(m_userid)).toStdString().c_str());
}
std::string HttpMethods::GetPostKey()
{
	std::regex reg("name=\"post_key\".?value=(.*?).\"");
	std::smatch m;
	std::ifstream infile("test.txt");
	std::string line;
	std::ssub_match sm, smk;
	std::string key;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		if (regex_search(line, m, reg)) {

			for (auto &match : m) {
				sm = match;
				key += sm.str() + " ";
			}
		}
	}

	auto i = QString::fromStdString(key).split(" ").at(1).split("=").at(1).toStdString();
	cout << "pixiv post key:" << i;
	return i;
}
void HttpMethods::OnLogin(QString usr,QString psw)
{
	this->ResetCURL();
	std::string file = "test.txt";
	std::ofstream ofs(file, std::ostream::binary);
	std::string url_init = "https://accounts.pixiv.net/login";
	std::string url_login = "https://accounts.pixiv.net/login?lang=en";
	qDebug() << "get post key";
	Initail(ofs, (char*)url_init.c_str());
	qDebug() << "login";
	char postfile[1024];

	std::ostringstream output;
	//curl_easy_setopt(m_curl, CURLOPT_PROXY, "10.99.60.201:8080");// 代理
	curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers);
	curl_easy_setopt(m_curl, CURLOPT_URL, (char*)url_login.c_str());
	curl_easy_setopt(m_curl, CURLOPT_COOKIEFILE, "cookies.txt");
	curl_easy_setopt(m_curl, CURLOPT_COOKIEJAR, "cookies.txt");
	curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, data_write);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &output);
	sprintf_s(postfile, sizeof(postfile), "captcha=&g_recaptcha_response=&password=%s&pixiv_id=%s&post_key=%s&source=pc&ref=wwwtop_accounts_index&return_to=https://www.pixiv.net/"
		, psw.toStdString().c_str()
		,usr.toStdString().c_str()
		, QString::fromStdString(GetPostKey()).remove("\"").toStdString().c_str());
	cout << "post file:\t" << postfile << endl;;
	curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, postfile);
	m_res = curl_easy_perform(m_curl);
	cout << output.str() << endl;
	curl_easy_cleanup(m_curl);
	qDebug() << "login done";
	emit login_ok();
	
}


void HttpMethods::GetAllIllust(char* url)
{


	std::ostringstream ofs;
	curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers);
	curl_easy_setopt(m_curl, CURLOPT_URL, url);
	curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(m_curl, CURLOPT_COOKIEFILE, "cookies.txt");
	curl_easy_setopt(m_curl, CURLOPT_COOKIEJAR, "cookies.txt");
	curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &ofs);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &ofs);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, data_write);
	curl_easy_perform(m_curl);
	cout << ofs.str() << endl;
	QJsonDocument doc = QJsonDocument::fromJson(QString::fromStdString(ofs.str()).split("\r\n\r\n").at(1).toUtf8());
	QJsonObject obj = doc.object();
	QJsonObject body = obj.value("body").toObject();
	QJsonObject illust = body.value("illusts").toObject();
	cout << ofs.str() << endl;
	qDebug() << illust.keys();
	for (auto i : illust.keys())
		m_download_list.append(i);
	this->HandleDownLoad();

}
void HttpMethods::HandleDownLoad()
{
	std::string file = "test.txt";
	std::ofstream ofs(file, std::ostream::binary);

	if (!m_download_list.isEmpty())
	{
		std::string tmp = m_page_url + m_download_list.dequeue().toStdString();
		Initail(ofs, (char*)tmp.c_str());
		DownLoadPic(GetDownLoadUrl());
	}
	else
	{
		emit current_proc("done...");
		emit proc_done();
		curl_easy_cleanup(m_curl);
	}
}
bool HttpMethods::Initail(std::ofstream& os, char* url)
{
	//crawl info you want you want
	if (m_curl)
	{
		try {

			curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers);
			curl_easy_setopt(m_curl, CURLOPT_URL, url);
			curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 0L);
			curl_easy_setopt(m_curl, CURLOPT_COOKIEFILE, "cookies.txt");
			curl_easy_setopt(m_curl, CURLOPT_COOKIEJAR, "cookies.txt");
			curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &os);
			curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &os);
			curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, data_write);

			m_res = curl_easy_perform(m_curl);

			if (m_res != 0) {

				cout << curl_easy_strerror(m_res);
				curl_easy_cleanup(m_curl);
			}
			else
			{

			}

			return true;
		}
		catch (exception e)
		{

		}
	}
}
std::string HttpMethods::GetDownLoadUrl()
{
	std::regex reg("\"original\":\"(.*?)\"");
	std::smatch m;
	std::ifstream infile("test.txt");
	std::string line;
	std::ssub_match sm, smk;
	std::string key;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		//cout << "compair.." << line << "\t"  << endl;
		if (regex_search(line, m, reg)) {

			for (auto &match : m) {
				cout << match.str() << endl;
				if (QString::fromStdString(match.str()).contains("\"original\"") == false)
				{

					qDebug() << "get img url:" << QString::fromStdString(match.str()).replace("\"", "");
					return QString::fromStdString(match.str()).replace("\\", "").toStdString();
				}
			}
		}
	}
	return "";
}
void HttpMethods::DownLoadPic(std::string str)
{
	QStringList tmp = QString::fromStdString(str).split("/");
	if (!QDir(QString("C:/Users/User/Pictures/%1/").arg(QString::number(m_userid))).exists());
	QDir().mkdir(QString("C:/Users/User/Pictures/%1/").arg(QString::number(m_userid)));
	std::ostringstream os1;
	QString path = QString("C:/Users/User/Pictures/%1/%2").arg(QString::number(m_userid)).arg(tmp.last());
	std::string picurl = str;
	std::ofstream ofs(path.toStdString(), std::ostream::binary);
	emit current_proc(tmp.last()+"\tRemains:"+QString::number(m_download_list.size())+"files");
	if (CURLE_OK == curl_read((str), ofs, 30, m_curl))
	{
		qDebug() << QString::fromStdString(picurl) << "\tpic get";
		emit ok();
	}
	else
	{

		qDebug() << "ERROR:" << path;
		emit current_proc("Error...");
		emit proc_done();
	}
}
HttpMethods::~HttpMethods()
{

}

#include "HttpMethods.moc"
