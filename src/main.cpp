
#include <QApplication>
#include <QTranslator>
#include "PipeToolWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QTranslator tran;
	bool ok = tran.load("./qt_zh_CN.qm");
	app.installTranslator(&tran);

	PipeToolWindow w;
	w.show();

	return app.exec();
}