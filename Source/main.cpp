#include "stdafx.h"

#include "Core/ViewManager.h"
int main(int argc, char* argv[])
{
	
	QApplication app(argc, argv);
	
	QDir::setCurrent(QApplication::applicationDirPath());
	
	ViewManager mgr;
	app.exec();
}