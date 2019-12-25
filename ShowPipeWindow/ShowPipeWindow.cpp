#include "ShowPipeWindow.h"
#include "GsGeospace3DQt.h"
#include <QDir>
#include <QMessageBox>
#include <QMimeData>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <QLayout>
#include "PipeUntility.h"

ShowPipeWindow::ShowPipeWindow()
{
	ui.setupUi(this);

	GLOBE_NAME::GsGeospace3DQt* ptrGeospace3d = new GLOBE_NAME::GsGeospace3DQt(/*this*/);

	QHBoxLayout* ptrHLayout = new QHBoxLayout();
	ptrHLayout->addWidget(ptrGeospace3d);
	setLayout(ptrHLayout);

	//setCentralWidget(ptrGeospace3d);

	setAcceptDrops(true);
}

ShowPipeWindow::~ShowPipeWindow()
{

}

void ShowPipeWindow::traverseAllModel(QString qstrFileName)
{
	QFileInfo modelfileInfo(qstrFileName);
	if (modelfileInfo.isFile())
	{
		QString suffix = modelfileInfo.suffix();
		if (QString::compare(suffix, QString(tr("obj")), Qt::CaseInsensitive) == 0)
		{
			/*获取文件绝对路径即全路径*/
			QString filePath = modelfileInfo.absoluteFilePath();

			osgDB::Options* option = new osgDB::Options(std::string("noTriStripPolygons"));

			osg::Node* ptrNode = osgDB::readNodeFile(filePath.toLocal8Bit().data(), option);
			GLOBE_NAME::PipeUntility::getRoot()->addChild(ptrNode);
		}

		return;
	}


	QDir dir(qstrFileName);

	if (!dir.exists())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("导出路径为空为空！"), QString::fromLocal8Bit("确定"));
		return;
	}

	dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

	QFileInfoList fileList = dir.entryInfoList();

	int fileCount = fileList.count();
	for (int i = 0; i < fileCount; i++)
	{
		QFileInfo fileInfo = fileList[i];

		if (fileInfo.isDir())
		{
			QString strAbsolutePath = fileInfo.filePath();
			traverseAllModel(strAbsolutePath);
		}
		else if (fileInfo.isFile())
		{
			QString suffix = fileInfo.suffix();

			if (QString::compare(suffix, QString(tr("obj")), Qt::CaseInsensitive) == 0)
			{
				/*获取文件绝对路径即全路径*/
				QString filePath = fileInfo.absoluteFilePath();

				osgDB::Options* option = new osgDB::Options(std::string("noTriStripPolygons"));

				osg::Node* ptrNode = osgDB::readNodeFile(filePath.toLocal8Bit().data(), option);
				GLOBE_NAME::PipeUntility::getRoot()->addChild(ptrNode);
				//m_vecModel.push_back(filePath.toLocal8Bit().data());
				//QListWidgetItem* ptrItem = new QListWidgetItem(filePath);
				//ui.modelListWidget->addItem(ptrItem);
			}
		}
	}
}

void ShowPipeWindow::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;

	QString name;

	foreach(QUrl url, urls)
	{
		name = url.toLocalFile();
		QFileInfo fileinfo(name);
		traverseAllModel(name);
	}

	// optimize the scene graph, remove redundant nodes and state etc.
	osgUtil::Optimizer optimizer;
	optimizer.optimize(GLOBE_NAME::PipeUntility::getRoot());

	event->acceptProposedAction();
}


void ShowPipeWindow::dragEnterEvent(QDragEnterEvent *event)
{
	event->acceptProposedAction();
}