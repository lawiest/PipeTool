#ifndef _LOAD_OGC_SERVICE_WINDOW
#define _LOAD_OGC_SERVICE_WINDOW

#include <QWidget>
#include <QMessageBox>
#include "../GeneratedFiles/ui_PipeToolWindow.h"
#include <QThread>
#include "ThreadObject.h"
#include "PipeFactory.h"

class ShowPipeWindow;

class ThreadPool :public QThread
{
public:
	ThreadPool()
	{
		m_isStop = false;
		m_vecThread[0] = new ThreadObject();
		m_vecThread[1] = new ThreadObject();
		m_vecThread[2] = new ThreadObject();

	}

	~ThreadPool()
	{

	}

	virtual void run()
	{
		while (true)
		{
			if (m_isStop || m_quePipePara.size() == 0)
				break;

			sleep(1);

			for (int i = 0; i < sizeof(m_vecThread)/sizeof(ThreadObjectPtr); ++i)
			{
				if (m_isStop || m_quePipePara.size() == 0)
					break;

				if (m_vecThread[i]->isRunning())
				{
					std::cout << "线程" << m_vecThread[i]->currentThreadId()<<"正在运行中"<<std::endl;
				}
				else
				{
					GLOBE_NAME::PipeProducePara para = m_quePipePara.front();
					m_quePipePara.pop();

					m_vecThread[i]->setPipePara(para);
					m_vecThread[i]->start();
				}

				sleep(1);
			}
		}

		std::cout << "生产完成！" << std::endl;
	}

	void stop()
	{
		QMutexLocker locker(&m_stopMutex);
		m_isStop = true;

		//std::vector<ThreadObjectPtr>::iterator it = m_vecThread.begin();
		//for (it; it < m_vecThread.end(); it++)
		//{
		//	(*it)->stop();
		//}
	}

	void addParameter(GLOBE_NAME::PipeProducePara para)
	{
		m_quePipePara.push(para);
	}

private:
	ThreadObjectPtr m_vecThread[3];

	std::queue<GLOBE_NAME::PipeProducePara> m_quePipePara;
	QMutex m_stopMutex;

	int m_nCnt = 0;
	bool m_isStop;
};

class PipeToolWindow :public QWidget
{
	Q_OBJECT

public:
	PipeToolWindow();
	~PipeToolWindow();

	void traverseAllModel(QString qstrFileName);

	void MessageBox(QString qstrtext, QMessageBox::Icon icon = QMessageBox::Warning);

	void LoadColorMapping();

	void OpenVectorFilds(std::string strFile, std::vector<QComboBox*>& vecCombo);

	void LoadPipeLineMapping();
	void LoadPipePointMapping();

	void ParseSavePipeLineMapping();

	void InitFieldsBridge();

	void SaveFieldsToConfig(int type,std::string strPath);
	void LoadFieldsFromConfig(int type, std::string strPath);

	void SaveColorToConfig();
	int CheckColorChecked(int start);

public Q_SLOTS:
	void nextStep();
	void preStep();
	void finish();

	void choosePipeData();
	void traverseAllVector(QString qstrFileName);
	void chooseSavePath();
	void chooseModelPath();

	void colorCellClick(int row, int column);
	void addColorClick();
	void deleteColorClick();
	void selectAllColorClick();
	void defaultColorClick();

	void chooseSingleModel();
	void selectAllModel();

	bool checkHasSelected();
	void deleteSelectedModel();

private:
	Ui::pipeToolWindow ui;
	int m_nCurrentPage;

	ThreadPool* m_threadPool;

	std::vector<std::string> m_vecModel;
	std::vector<std::string> m_vecLineVector;
	std::vector<std::string> m_vecPointVector;

	std::map <std::string, std::string> m_mapColor;

	std::map <int, std::string> m_mapLineBridgeFields;
	std::map <std::string, std::string> m_mapLineDesBridgeFields;
	std::map <std::string, std::string> m_mapLineFields;

	std::map <int, std::string> m_mapPointBridgeFields;
	std::map <std::string, std::string> m_mapPointDesBridgeFields;
	std::map <std::string, std::string> m_mapPointFields;

	ShowPipeWindow* m_ptrShowPipe;
};

#endif