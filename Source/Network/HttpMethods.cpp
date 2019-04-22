#include "../stdafx.h"

#include "HttpMethods.h"
#include "curlpp/cURLpp.hpp"
#include "curlpp/Options.hpp"
#include <iostream>
#include <sstream>
using namespace std;



HttpMethods::HttpMethods(QObject* parent)
{
	

	/* ERR_load_crypto_strings(); */
	//CURL 
	//std::ostringstream os;
	//std::ostringstream foo;
	//CURL *curl = curl_easy_init();
	//if (curl)
	//{
	//	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	//	curl_easy_setopt(curl, CURLOPT_URL, "https://google.com/");
	//	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	//	curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");
	//	CURLcode res = curl_easy_perform(curl);
	//	if (res != CURLE_OK)
	//		printf("res = %d curl_easy_perform() failed: %s\n", res, curl_easy_strerror(res));
	//	curl_easy_cleanup(curl);
	//}
	//curl_global_cleanup();



	curlpp::Cleanup myCleanup;
	std::ostringstream os;
	os << curlpp::options::Url(std::string("https://www.pixiv.net"));
	QTextCodec* tc = QTextCodec::codecForName("UTF8");
	
	qDebug()<< tc->toUnicode(os.str().c_str());
	
	
}


HttpMethods::~HttpMethods()
{
}
