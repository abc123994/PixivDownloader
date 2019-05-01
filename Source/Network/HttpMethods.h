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
  void OnDownloadByUser(QString userid,QString path);
  void OnDownloadByPic(QString picid,QString path);
  void OnDownloadByDaily(QString date,QString path);
  void OnLogin(QString, QString);
 private:
  void CleanCookie();
  void ResetCURL();

  std::string GetPostKey();
 

  void GetAllIllust(char* url);
  void GetDailyIllust(QString,char* url);

  bool Initial(std::ofstream&, char*);
  bool Initial(std::ostringstream& ,char*);
  
  void DownLoadPic(std::string);

  
  //daily top 50
  std::string m_daily_illust_url= "https://www.pixiv.net/ranking.php?mode=daily&content=illust&date=%1&p=1&format=json";
  //get user illust all
  std::string m_user_illust_all = "https://www.pixiv.net/ajax/user/%1/profile/all";
  // get liiust series
  std::string m_illust_id_pic_all = "https://www.pixiv.net/ajax/illust/%1/pages";
  //illustid_url
  std::string m_page_url = "https://www.pixiv.net/member_illust.php?mode=medium&illust_id=";

  QQueue<QString> m_download_list;
  std::string m_downloaded_path;
};
