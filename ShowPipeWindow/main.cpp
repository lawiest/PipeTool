
#include <QApplication>
#include <QTranslator>
#include "ShowPipeWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QTranslator tran;
	bool ok = tran.load("./qt_zh_CN.qm");
	app.installTranslator(&tran);

	ShowPipeWindow* w = new ShowPipeWindow();
	w->show();

	return app.exec();
}