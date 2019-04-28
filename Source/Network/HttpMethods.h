#pragma once
#include <curl/curl.h>
#include "../stdafx.h"

class CURLCode;
class HttpMethods : public QObject {
  Q_OBJECT

 public:
  HttpMethods(QObject* parent = 0);
  ~HttpMethods();

  struct curl_slist* m_headers = NULL;
  CURL* m_curl;
  CURLcode m_res;
  int m_userid;
 signals:
  void ok();
  void current_proc(QString);
  void login_ok();
  void proc_done();
 private slots:
  void HandleDownLoad();
public slots:
  void OnDownloadByUser(QString userid);
  void OnDownloadByPic(QString picid);
  void OnLogin(QString, QString);
 private:
  void CleanCookie();
  void ResetCURL();
  std::string GetPostKey();
 

  void GetAllIllust(char* url);
  bool Initail(std::ofstream&, char*);
  std::string HandlePageUrl();  // set userid and return download url
  
  void DownLoadPic(std::string);

  // std::string m_og_url = "https://embed.pixiv.net/decorate.php?illust_id=";
  // useless
  std::string m_page_url =
      "https://www.pixiv.net/member_illust.php?mode=medium&illust_id=";

  QQueue<QString> m_download_list;
};
