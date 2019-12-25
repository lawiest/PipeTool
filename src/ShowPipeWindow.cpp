#include "ShowPipeWindow.h"
#include "GsGeospace3DQt.h"
#include <QDropEvent>
#include "PipeUntility.h"
#include <QDir>
#include <QMessageBox>
#include <QMimeData>
#include <QThread>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include "GeoGlobleEvent.h"

template<class T> class Delegate;
template<typename R, typename T, typename P>
class Delegate<R(T::*)(P)> : public QThread
{
public:
	typedef R(T::* pFun)(P);

	Delegate() {}
	virtual ~Delegate() {}

	R operator()(P para)
	{
		m_para = para;
		start();
	}

	void Add(pFun p, T* pObject)
	{
		m_list[pObject] = p;
	}

	virtual void run()
	{
		std::map<T*, pFun >::iterator it = m_list.begin();
		for (it; it != m_list.end(); ++it)
		{
			((*it).first->*(*it).second)(m_para);
		}
	}

	P m_para;
	std::map<T*, pFun > m_list;
};

int Sum(int n)
{
	return n + 10;
}

void ShowPipeWindow::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;

	QString name;

	//Delegate<int(int)> addDelegate;
	//addDelegate.Add(&Sum);
	//int result= addDelegate(10);

	Delegate<void (ShowPipeWindow::*)(QString)>* thread = new Delegate<void(ShowPipeWindow::*)(QString)>();
	thread->Add(&ShowPipeWindow::traverseAllModel, this);
	//thread(name);

	foreach(QUrl url, urls)
	{
		name = url.toLocalFile();
		QFileInfo fileinfo(name);
		(*thread)(name);

		//traverseAllModel(name);
	}

	// optimize the scene graph, remove redundant nodes and state etc.
	//osgUtil::Optimizer optimizer;
	//optimizer.optimize(GLOBE_NAME::PipeUntility::getRoot());

	event->acceptProposedAction();
}

ShowPipeWindow::ShowPipeWindow()
{
	ui.setupUi(this);

	GLOBE_NAME::GsGeospace3DQt* ptrGeospace3d = new GLOBE_NAME::GsGeospace3DQt();
	ui.verticalLayout->addWidget(ptrGeospace3d);

	setAcceptDrops(true);
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

			osg::ref_ptr<GeoGlobleEventAdapter> ptrUserEvenAdapter = new GeoGlobleEventAdapter();
			ptrUserEvenAdapter->setEventType(ADD_NODE);
			ptrUserEvenAdapter->setData(ptrNode);
			GLOBE_NAME::PipeUntility::getViewer()->getEventQueue()->userEvent(ptrUserEvenAdapter);
			//GLOBE_NAME::PipeUntility::getRoot()->addChild(ptrNode);
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
				osg::ref_ptr<GeoGlobleEventAdapter> ptrUserEvenAdapter = new GeoGlobleEventAdapter();
				ptrUserEvenAdapter->setEventType(ADD_NODE);
				ptrUserEvenAdapter->setData(ptrNode);
				GLOBE_NAME::PipeUntility::getViewer()->getEventQueue()->userEvent(ptrUserEvenAdapter);
				//GLOBE_NAME::PipeUntility::getRoot()->addChild(ptrNode);
				//m_vecModel.push_back(filePath.toLocal8Bit().data());
				//QListWidgetItem* ptrItem = new QListWidgetItem(filePath);
				//ui.modelListWidget->addItem(ptrItem);
			}
		}
	}
}

void ShowPipeWindow::dragEnterEvent(QDragEnterEvent *event)
{
	event->acceptProposedAction();
}

ShowPipeWindow::~ShowPipeWindow()
{

}