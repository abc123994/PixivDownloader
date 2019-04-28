#include "stdafx.h"
#include "Network/HttpMethods.h"

#include "Core/ViewManager.h"
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	//
	QDir::setCurrent(QApplication::applicationDirPath());
	QFile("cookies.txt").remove();
	ViewManager mgr;
	//HttpMethods methods;
	app.exec();
}