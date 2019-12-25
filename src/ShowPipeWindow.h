#ifndef _SHOW_PIPE_WINDOW
#define _SHOW_PIPE_WINDOW

#include <QWidget>
#include <QThread>

#include "../GeneratedFiles/ui_ShowPipeWindow.h"

class ShowPipeWindow :public QWidget
{
	Q_OBJECT

public:
	ShowPipeWindow();
	~ShowPipeWindow();

	void traverseAllModel(QString qstrFileName);

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);

public Q_SLOTS:

private:
	Ui::showPipeWindow ui;

};

#endif