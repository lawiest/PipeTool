#include "PipeToolWindow.h"
#include <QFileDialog>
#include <QDir>
#include <QCheckBox>
#include <QComboBox>
#include <QStandardItemModel> 
#include <utility.h>
#include <geodatabase.h>
#include "ShowPipeWindow.h"
#include "GsGeospace3DQt.h"
#include "PipeUntility.h"
#include <osgDB/ReadFile>
#include <osgDB/Options>
#include <QColorDialog>
#include "ThreadObject.h"
#include <QPointer>

using namespace KERNEL_NAME;
using namespace UTILITY_NAME;
using namespace GLOBE_NAME;

PipeToolWindow::PipeToolWindow()
{
	ui.setupUi(this);
	m_nCurrentPage = 0;

	connect(ui.okPushButton,SIGNAL(clicked()),this,SLOT(finish()));
	connect(ui.nextPushButton,SIGNAL(clicked()),this,SLOT(nextStep()));
	connect(ui.prePushButton, SIGNAL(clicked()), this, SLOT(preStep()));

	connect(ui.choosePipeDataBtn, SIGNAL(clicked()), this, SLOT(choosePipeData()));
	connect(ui.chooseSaveBtn, SIGNAL(clicked()), this, SLOT(chooseSavePath()));
	connect(ui.chooseFolderModelBtn, SIGNAL(clicked()), this, SLOT(chooseModelPath()));
	connect(ui.chooseSingleModelBtn, SIGNAL(clicked()), this, SLOT(chooseSingleModel()));
	connect(ui.selectAllModelBtn, SIGNAL(clicked()), this, SLOT(selectAllModel()));
	connect(ui.deleteModelBtn, SIGNAL(clicked()), this, SLOT(deleteSelectedModel()));
	connect(ui.colorTableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(colorCellClick(int, int)));
	connect(ui.addColorBtn, SIGNAL(clicked()), this, SLOT(addColorClick()));
	connect(ui.deleteColor, SIGNAL(clicked()), this, SLOT(deleteColorClick()));
	connect(ui.seleAllColorBtn, SIGNAL(clicked()), this, SLOT(selectAllColorClick()));
	connect(ui.defaultColor, SIGNAL(clicked()), this, SLOT(defaultColorClick()));

	ui.page1->hide();
	ui.page2->hide();
	ui.page3->hide();

	ui.prePushButton->setEnabled(false);
	ui.okPushButton->setEnabled(false);

	ui.modelListWidget->setSelectionMode(QAbstractItemView::MultiSelection);

	//设置第一列宽度
	ui.colorTableWidget->setColumnWidth(0, 40);

	m_ptrShowPipe = new ShowPipeWindow();
	m_ptrShowPipe->show();

	InitFieldsBridge();

	m_threadPool = new ThreadPool();

}

void PipeToolWindow::colorCellClick(int row, int column)
{
	if (column == 5)
	{
		QColor color = QColorDialog::getColor();

		if (!color.isValid())
			return;
		
		QTableWidgetItem* ptrItem = ui.colorTableWidget->item(row,column);
		ptrItem->setBackgroundColor(QColor(color.red(), color.green(), color.blue()));
	}
}

void PipeToolWindow::InitFieldsBridge()
{
	m_mapLineBridgeFields[0] = "PIPEID";
	m_mapLineBridgeFields[1] = "PIPESID";
	m_mapLineBridgeFields[2] = "PIPEEID";
	m_mapLineBridgeFields[3] = "STARTHEIGHT";
	m_mapLineBridgeFields[4] = "ENDHEIGHT";
	m_mapLineBridgeFields[5] = "STARTDEEP";
	m_mapLineBridgeFields[6] = "ENDDEEP";
	m_mapLineBridgeFields[7] = "PIPESIZE";
	m_mapLineBridgeFields[8] = "PIPETYPE";
	m_mapLineDesBridgeFields["PIPEID"] = "管线编号";
	m_mapLineDesBridgeFields["PIPESID"] = "管线起点编号";
	m_mapLineDesBridgeFields["PIPEEID"] = "管线终点编号";
	m_mapLineDesBridgeFields["STARTHEIGHT"] = "管线起点高程";
	m_mapLineDesBridgeFields["ENDHEIGHT"] = "管线终点高程";
	m_mapLineDesBridgeFields["STARTDEEP"] = "管线起点埋深";
	m_mapLineDesBridgeFields["ENDDEEP"] = "管线终点埋深";
	m_mapLineDesBridgeFields["PIPESIZE"] = "管径";
	m_mapLineDesBridgeFields["PIPETYPE"] = "管线类型";

	m_mapPointBridgeFields[0] = "POINTID";
	m_mapPointBridgeFields[1] = "FEATUREPOINT";
	m_mapPointBridgeFields[2] = "POINTMODEL";
	m_mapPointBridgeFields[3] = "POINTDEEP" ;
	m_mapPointBridgeFields[4] = "GROUNDELEV";
	m_mapPointBridgeFields[5] = "POINTHEIGHT";
	m_mapPointBridgeFields[6] = "ROTATEANGLE";
	m_mapPointDesBridgeFields["POINTID"] = "物探点号";
	m_mapPointDesBridgeFields["FEATUREPOINT"] = "特征点";
	m_mapPointDesBridgeFields["POINTMODEL"] = "附属物";
	m_mapPointDesBridgeFields["POINTDEEP"] = "管点埋深";
	m_mapPointDesBridgeFields["GROUNDELEV"] = "地面高程";
	m_mapPointDesBridgeFields["POINTHEIGHT"] = "管点高程";
	m_mapPointDesBridgeFields["ROTATEANGLE"] = "旋转角";

}

void PipeToolWindow::traverseAllModel(QString qstrFileName)
{
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
		else if(fileInfo.isFile())
		{
			QString suffix = fileInfo.suffix();

			if (QString::compare(suffix, QString(tr("x")), Qt::CaseInsensitive) == 0 
				|| QString::compare(suffix, QString(tr("obj")), Qt::CaseInsensitive) == 0)
			{
				/*获取文件绝对路径即全路径*/
				QString filePath = fileInfo.absoluteFilePath();
				m_vecModel.push_back(filePath.toLocal8Bit().data());

				QListWidgetItem* ptrItem = new QListWidgetItem(filePath);

				ui.modelListWidget->addItem(ptrItem);
			}
		}
	}
}

void PipeToolWindow::chooseModelPath()
{
	QString qstrFileName = QFileDialog::getExistingDirectory(this);

	if (qstrFileName.isEmpty())
		return;

	traverseAllModel(qstrFileName);
}

bool PipeToolWindow::checkHasSelected()
{
	int nCnt = ui.modelListWidget->count();

	for (int i = 0; i < nCnt; i++)
	{
		QListWidgetItem* ptrItem = ui.modelListWidget->item(i);
		if (ptrItem->isSelected())
		{
			return true;
		}
	}

	return false;
}

void PipeToolWindow::deleteSelectedModel()
{
	int nCnt = ui.modelListWidget->count();

	int i = 0;
	while (checkHasSelected())
	{
		QListWidgetItem* ptrItem = ui.modelListWidget->item(i);
		if (ptrItem->isSelected())
		{
			std::string strText = ptrItem->text().toLocal8Bit();
			ui.modelListWidget->removeItemWidget(ptrItem);

			std::vector<std::string>::iterator it = std::find(m_vecModel.begin(), m_vecModel.end(), strText);
			if (it != m_vecModel.end())
				m_vecModel.erase(it);

			delete ptrItem;
		}

		if (++i >= ui.modelListWidget->count())
			i = 0;
	}
}

void PipeToolWindow::selectAllModel()
{
	int nCnt = ui.modelListWidget->count();

	for (int i = 0; i < nCnt; i++)
	{
		bool bSele = ui.modelListWidget->item(i)->isSelected();
		ui.modelListWidget->item(i)->setSelected(!bSele);
	}
	ui.modelListWidget->setFocus();
}

void PipeToolWindow::chooseSingleModel()
{
	QStringList qstrList = QFileDialog::getOpenFileNames(this,"选择模型文件",".", "Model Files(*.x *.obj)");

	if (qstrList.isEmpty())
		return;

	for (int i = 0; i < qstrList.size(); ++i)
	{
		std::string strFile = qstrList[i].toLocal8Bit().data();
		std::vector<std::string>::iterator it = std::find(m_vecModel.begin(), m_vecModel.end(), strFile);
		if (it == m_vecModel.end())
		{
			m_vecModel.push_back(strFile);
			QListWidgetItem* ptrItem = new QListWidgetItem(GsEncoding::ToUtf8(strFile.c_str()).c_str());
			ui.modelListWidget->addItem(ptrItem);
		}
	}
}

void PipeToolWindow::chooseSavePath()
{
	QString qstrFileName = QFileDialog::getExistingDirectory(this);

	if (qstrFileName.isEmpty())
		return;

	QDir dir(qstrFileName);

	if (!dir.exists())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("导出路径为空为空！"), QString::fromLocal8Bit("确定"));
		return;
	}

	ui.savePathLineEdit->setText(qstrFileName);
}

void PipeToolWindow::traverseAllVector(QString qstrFileName)
{
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
			traverseAllVector(strAbsolutePath);
		}
		else if (fileInfo.isFile())
		{
			QString suffix = fileInfo.suffix();

			if (QString::compare(suffix, QString(tr("shp")), Qt::CaseInsensitive) == 0
				|| QString::compare(suffix, QString(tr("fcs")), Qt::CaseInsensitive) == 0)
			{
				QString filePath = fileInfo.absoluteFilePath();/*获取文件绝对路径即全路径*/
				QString fileName = fileInfo.baseName();
				QStringList list = fileName.split('_');

				if (QString::compare(list[list.size()-1],"Line", Qt::CaseInsensitive)==0
					|| QString::compare(list[list.size() - 1], "L", Qt::CaseInsensitive) == 0)
				{
					m_vecLineVector.push_back(filePath.toLocal8Bit().data());
				}
				else if (QString::compare(list[list.size() - 1], "Point", Qt::CaseInsensitive) == 0
					|| QString::compare(list[list.size() - 1], "P", Qt::CaseInsensitive) == 0)
				{
					m_vecPointVector.push_back(filePath.toLocal8Bit().data());
				}
			}
		}
	}
}

void PipeToolWindow::choosePipeData()
{
	QString qstrFileName = QFileDialog::getExistingDirectory(this);

	if (qstrFileName.isEmpty())
		return;

	QDir dir(qstrFileName);

	if (!dir.exists())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("管线数据为空！"));
		return;
	}

	ui.vectorDataEdit->setText(qstrFileName);

	traverseAllVector(qstrFileName);
}

void PipeToolWindow::finish()
{
	//先解析字段映射并保存到配置文件
	ParseSavePipeLineMapping();

	for (int i = 0; i < m_vecLineVector.size(); ++i)
	{
		QString strLinePath = QString::fromLocal8Bit(m_vecLineVector[i].c_str());

		QFileInfo fileinfo(strLinePath);
		std::string strName = fileinfo.baseName().toLocal8Bit();
		size_t pos = strName.rfind("_");
		strName = strName.substr(0, pos);

		PipeProducePara para;
		para.m_strLinePath = m_vecLineVector[i].c_str();
		para.m_strPointPath = m_vecPointVector[i].c_str();
		para.m_strSavePath = ui.savePathLineEdit->text().toLocal8Bit().data();
		para.m_vecModel = m_vecModel;
		para.m_strDataSetName = ui.datasetEdit->text().toLocal8Bit().data();
		para.m_strPipeTypeName = strName;
		para.m_lineFieldsMap = m_mapLineFields;
		para.m_pointFieldsMap = m_mapPointFields;
		para.m_mapColor = m_mapColor;

		m_threadPool->addParameter(para);
	}

	m_threadPool->start();
}

void PipeToolWindow::preStep()
{
	if (m_nCurrentPage == 0)
	{
		ui.page0->show();
		ui.page1->hide();
		ui.page2->hide();
		ui.page3->hide();

		ui.prePushButton->setEnabled(false);
		ui.nextPushButton->setEnabled(true);
		ui.okPushButton->setEnabled(false);
	}
	else if (m_nCurrentPage == 1)
	{
		ui.page0->show();
		ui.page1->hide();
		ui.page2->hide();
		ui.page3->hide();

		ui.prePushButton->setEnabled(false);
		ui.nextPushButton->setEnabled(true);
		ui.okPushButton->setEnabled(false);
		m_nCurrentPage--;
	}
	else if (m_nCurrentPage == 2)
	{
		ui.page0->hide();
		ui.page1->show();
		ui.page2->hide();
		ui.page3->hide();

		ui.prePushButton->setEnabled(true);
		ui.nextPushButton->setEnabled(true);
		ui.okPushButton->setEnabled(false);
		m_nCurrentPage--;
	}
	else if (m_nCurrentPage == 3)
	{
		ui.page0->hide();
		ui.page1->hide();
		ui.page2->show();
		ui.page3->hide();

		ui.prePushButton->setEnabled(true);
		ui.nextPushButton->setEnabled(true);
		ui.okPushButton->setEnabled(false);
		m_nCurrentPage--;
	}
}

void PipeToolWindow::MessageBox(QString qstrtext,QMessageBox::Icon icon)
{
	QMessageBox box(icon,QString::fromLocal8Bit("提示"), qstrtext, QMessageBox::NoButton,this);
	box.setStandardButtons(QMessageBox::Ok);
	box.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
	box.exec();
}

void PipeToolWindow::LoadColorMapping()
{
	ui.colorTableWidget->clearContents();
	ui.colorTableWidget->setRowCount(0);

	UTILITY_NAME::GsConfig colorConfig("./config/PipeColorConfig.xml");
	//矢量路径
	GsVector<GsConfig> vecConfig = colorConfig["ColorMapping"].Children();
	for (int i = 0; i < vecConfig.size(); ++i)
	{
		GsVector<GsConfig> vecChirld = vecConfig[i].Children();

		int iRow = ui.colorTableWidget->rowCount();
		ui.colorTableWidget->setRowCount(iRow + vecChirld.size());//总行数增加

		for (int j = 0; j < vecChirld.size(); ++j)
		{
			std::string strColor = vecChirld[j].Value();
			GsVector<GsString> gstrVec = GsStringHelp::Split(strColor.c_str(), ",");
			int r = atoi(gstrVec[0]);
			int g = atoi(gstrVec[1]);
			int b = atoi(gstrVec[2]);

			//QCheckBox* ptrCheckBox = new QCheckBox();
			//ptrCheckBox->setChecked(true);


			QTableWidgetItem* ptrCheckBox = new QTableWidgetItem();
			ptrCheckBox->setCheckState(Qt::Checked);
			ptrCheckBox->setFlags(ptrCheckBox->flags() &  (~Qt::ItemIsEditable & ~Qt::ItemIsSelectable));

			ui.colorTableWidget->setItem(iRow+j,0, ptrCheckBox);
			ui.colorTableWidget->setItem(iRow + j, 1, new QTableWidgetItem(vecConfig[i].Name().c_str()));
			ui.colorTableWidget->setItem(iRow + j, 2, new QTableWidgetItem(vecConfig[i].Description().c_str()));
			ui.colorTableWidget->setItem(iRow + j, 3, new QTableWidgetItem(vecChirld[j].Name().c_str()));
			ui.colorTableWidget->setItem(iRow + j, 4, new QTableWidgetItem(vecChirld[j].Description().c_str()));
			QTableWidgetItem* ptrItem = new QTableWidgetItem();
			ptrItem->setBackgroundColor(QColor(r,g,b));
			ui.colorTableWidget->setItem(iRow + j, 5, ptrItem);

			ptrItem->setFlags(ptrItem->flags() & (~Qt::ItemIsEditable & ~Qt::ItemIsSelectable));

		}
	}
}

void PipeToolWindow::defaultColorClick()
{
	LoadColorMapping();
}

void PipeToolWindow::selectAllColorClick()
{
	int iRow = ui.colorTableWidget->rowCount();

	for (int i = 0; i < iRow; i++)
	{
		QTableWidgetItem* item = ui.colorTableWidget->item(i, 0);
		Qt::CheckState state = item->checkState();
		if (state == Qt::Checked)
		{
			item->setCheckState(Qt::Unchecked);
		}
		else if(state == Qt::Unchecked)
		{
			item->setCheckState(Qt::Checked);
		}
	}
}

int PipeToolWindow::CheckColorChecked(int start)
{
	int iRow = ui.colorTableWidget->rowCount();

	for (int i = start; i < iRow; ++i)
	{
		QTableWidgetItem* item = ui.colorTableWidget->item(i, 0);
		Qt::CheckState state = item->checkState();
		if (state == Qt::Checked)
		{
			return i;
		}
	}

	return -1;
}

void PipeToolWindow::deleteColorClick()
{
	int iRow = ui.colorTableWidget->rowCount();
	int pos = 0;

	while (pos != -1)
	{
		pos = CheckColorChecked(pos);
		if (pos >= 0)
			ui.colorTableWidget->removeRow(pos);
	}
}


void PipeToolWindow::addColorClick()
{
	int iRow = ui.colorTableWidget->rowCount();
	ui.colorTableWidget->setRowCount(iRow + 1);

	//QCheckBox* ptrCheckBox = new QCheckBox();
	//ptrCheckBox->setChecked(true);

	QTableWidgetItem* ptrCheckBox = new QTableWidgetItem();
	ptrCheckBox->setCheckState(Qt::Checked);
	ptrCheckBox->setFlags(ptrCheckBox->flags() &  (~Qt::ItemIsEditable & ~Qt::ItemIsSelectable));

	ui.colorTableWidget->setItem(iRow, 0, ptrCheckBox);
	ui.colorTableWidget->setItem(iRow, 1, new QTableWidgetItem());
	ui.colorTableWidget->setItem(iRow, 2, new QTableWidgetItem());
	ui.colorTableWidget->setItem(iRow, 3, new QTableWidgetItem());
	ui.colorTableWidget->setItem(iRow, 4, new QTableWidgetItem());
	QTableWidgetItem* ptrItem = new QTableWidgetItem();
	ui.colorTableWidget->setItem(iRow, 5, ptrItem);
	ptrItem->setFlags(ptrItem->flags() & (~Qt::ItemIsEditable & ~Qt::ItemIsSelectable));

	ui.colorTableWidget->scrollToBottom();
}

void PipeToolWindow::SaveColorToConfig()
{
	m_mapColor.clear();

	std::string strSavePath = GsFileSystem::Combine(GsFileSystem::WorkingFolder(), "./config/PipeColorConfig.xml");

	GsConfig config;
	GsConfig colorRoot = config.Child("ColorMapping");
	colorRoot.Type("String");

	std::string strParentType;
	std::string strParentDes;
	std::string strChildType;
	std::string strChildDes;

	int nRowCnt = ui.colorTableWidget->rowCount();
	for (int i = 0; i < nRowCnt; ++i)
	{
		QTableWidgetItem* ptrItem;
		//父类型
		ptrItem = ui.colorTableWidget->item(i, 1);
		strParentType = ptrItem->text().toLocal8Bit();
		//父描述
		ptrItem = ui.colorTableWidget->item(i, 2);
		strParentDes = ptrItem->text().toLocal8Bit();
		//子类型
		ptrItem = ui.colorTableWidget->item(i, 3);
		strChildType = ptrItem->text().toLocal8Bit();
		//子描述
		ptrItem = ui.colorTableWidget->item(i, 4);
		strChildDes = ptrItem->text().toLocal8Bit();
		//颜色
		ptrItem = ui.colorTableWidget->item(i, 5);
		QColor color = ptrItem->backgroundColor();
		std::string strColor = std::to_string(color.red()) + ","+ std::to_string(color.green())+","+ std::to_string(color.blue());

		GsConfig pareConfig = colorRoot.Child(strParentType);
		pareConfig.Description(GsEncoding::ToUtf8(strParentDes.c_str()));
		pareConfig.Type("String");

		GsConfig childConfig = pareConfig.Child(strChildType);
		childConfig.Description(GsEncoding::ToUtf8(strChildDes.c_str()));
		childConfig.Type("String");
		childConfig.Value(strColor);

		m_mapColor[strChildType] = strColor;
	}

	config.Save(strSavePath.c_str());
}

void PipeToolWindow::LoadPipeLineMapping()
{
	ui.lineTableWidget->setRowCount(9);

	std::vector<QComboBox*> vecCombo;

	ui.lineTableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("管线编号")));
	QComboBox* ptrCom0 = new QComboBox();
	vecCombo.push_back(ptrCom0);
	ui.lineTableWidget->setCellWidget(0, 1, ptrCom0);

	ui.lineTableWidget->setItem(1, 0, new QTableWidgetItem(QString::fromLocal8Bit("起点管点号")));
	QComboBox* ptrCom1 = new QComboBox();
	vecCombo.push_back(ptrCom1);
	ui.lineTableWidget->setCellWidget(1, 1, ptrCom1);

	ui.lineTableWidget->setItem(2, 0, new QTableWidgetItem(QString::fromLocal8Bit("终点管点号")));
	QComboBox* ptrCom2 = new QComboBox();
	vecCombo.push_back(ptrCom2);
	ui.lineTableWidget->setCellWidget(2, 1, ptrCom2);

	ui.lineTableWidget->setItem(3, 0, new QTableWidgetItem(QString::fromLocal8Bit("起点高程")));
	QComboBox* ptrCom3 = new QComboBox();
	vecCombo.push_back(ptrCom3);
	ui.lineTableWidget->setCellWidget(3, 1, ptrCom3);

	ui.lineTableWidget->setItem(4, 0, new QTableWidgetItem(QString::fromLocal8Bit("终点高程")));
	QComboBox* ptrCom4 = new QComboBox();
	vecCombo.push_back(ptrCom4);
	ui.lineTableWidget->setCellWidget(4, 1, ptrCom4);

	ui.lineTableWidget->setItem(5, 0, new QTableWidgetItem(QString::fromLocal8Bit("起点埋深")));
	QComboBox* ptrCom5 = new QComboBox();
	vecCombo.push_back(ptrCom5);
	ui.lineTableWidget->setCellWidget(5, 1, ptrCom5);

	ui.lineTableWidget->setItem(6, 0, new QTableWidgetItem(QString::fromLocal8Bit("终点埋深")));
	QComboBox* ptrCom6 = new QComboBox();
	vecCombo.push_back(ptrCom6);
	ui.lineTableWidget->setCellWidget(6, 1, ptrCom6);

	ui.lineTableWidget->setItem(7, 0, new QTableWidgetItem(QString::fromLocal8Bit("断面尺寸")));
	QComboBox* ptrCom7 = new QComboBox();
	vecCombo.push_back(ptrCom7);
	ui.lineTableWidget->setCellWidget(7, 1, ptrCom7);

	ui.lineTableWidget->setItem(8, 0, new QTableWidgetItem(QString::fromLocal8Bit("管线类型")));
	QComboBox* ptrCom8 = new QComboBox();
	vecCombo.push_back(ptrCom8);
	ui.lineTableWidget->setCellWidget(8, 1, ptrCom8);

	OpenVectorFilds(m_vecLineVector[0].c_str(),vecCombo);

	for (int i = 0; i < vecCombo.size(); ++i)
	{
		vecCombo[i]->setCurrentIndex(-1);
	}
}

void PipeToolWindow::OpenVectorFilds(std::string strFile,std::vector<QComboBox*>& vecCombo)
{

	QFileInfo file(QString::fromLocal8Bit(strFile.c_str()));

	std::string strPath = file.absolutePath().toStdString();
	std::string strName = file.baseName().toStdString();

	GsConnectProperty prop;
	prop.Server = strPath;
	prop.DataSourceType = eFile;
	GsFileGeoDatabaseFactory fac;
	GsGeoDatabasePtr ptrDB = fac.Open(prop);

	if (!ptrDB.p)
		return;

	GsFeatureClassPtr ptrLineFeatureClass = ptrDB->OpenFeatureClass(strName.c_str());

	GsFeatureCursorPtr ptrCur = ptrLineFeatureClass->Search();
	GsFeaturePtr ptrFea = ptrCur->Next();

	if (ptrFea == NULL)
		return;

	UTILITY_NAME::GsVector<GsField> fields = ptrLineFeatureClass->Fields().Fields;
	QStringList strList;

	for (int i = 0; i < fields.size(); ++i)
	{
		std::string strName = fields[i].Name;
		strList.push_back(strName.c_str());
	}

	for (int j = 0; j < vecCombo.size(); ++j)
	{
		vecCombo[j]->addItems(strList);
	}
}

void PipeToolWindow::LoadPipePointMapping()
{
	ui.pointTableWidget->setRowCount(7);

	std::vector<QComboBox*> vecCombo;

	ui.pointTableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("管点编号")));
	QComboBox* ptrCom0 = new QComboBox();
	vecCombo.push_back(ptrCom0);
	ui.pointTableWidget->setCellWidget(0, 1, ptrCom0);

	ui.pointTableWidget->setItem(1, 0, new QTableWidgetItem(QString::fromLocal8Bit("特征点")));
	QComboBox* ptrCom1 = new QComboBox();
	vecCombo.push_back(ptrCom1);
	ui.pointTableWidget->setCellWidget(1, 1, ptrCom1);

	ui.pointTableWidget->setItem(2, 0, new QTableWidgetItem(QString::fromLocal8Bit("附属物")));
	QComboBox* ptrCom2 = new QComboBox();
	vecCombo.push_back(ptrCom2);
	ui.pointTableWidget->setCellWidget(2, 1, ptrCom2);

	ui.pointTableWidget->setItem(3, 0, new QTableWidgetItem(QString::fromLocal8Bit("管点埋深")));
	QComboBox* ptrCom3 = new QComboBox();
	vecCombo.push_back(ptrCom3);
	ui.pointTableWidget->setCellWidget(3, 1, ptrCom3);

	ui.pointTableWidget->setItem(4, 0, new QTableWidgetItem(QString::fromLocal8Bit("地面高程")));
	QComboBox* ptrCom4 = new QComboBox();
	vecCombo.push_back(ptrCom4);
	ui.pointTableWidget->setCellWidget(4, 1, ptrCom4);

	ui.pointTableWidget->setItem(5, 0, new QTableWidgetItem(QString::fromLocal8Bit("管点高程")));
	QComboBox* ptrCom5 = new QComboBox();
	vecCombo.push_back(ptrCom5);
	ui.pointTableWidget->setCellWidget(5, 1, ptrCom5);

	ui.pointTableWidget->setItem(6, 0, new QTableWidgetItem(QString::fromLocal8Bit("旋转角")));
	QComboBox* ptrCom6 = new QComboBox();
	vecCombo.push_back(ptrCom6);
	ui.pointTableWidget->setCellWidget(6, 1, ptrCom6);

	OpenVectorFilds(m_vecPointVector[0].c_str(), vecCombo);

	for (int i = 0; i < vecCombo.size(); ++i)
	{
		vecCombo[i]->setCurrentIndex(-1);
	}
}

void PipeToolWindow::nextStep()
{
	if (m_nCurrentPage == 0)
	{
		if (m_vecLineVector.size() <= 0 || 
			m_vecPointVector.size() <= 0 ||
			m_vecModel.size() <=0 || 
			ui.datasetEdit->text() == "" ||
			ui.savePathLineEdit->text() == "")
		{
			MessageBox(QString::fromLocal8Bit("信息不完整！或者没实质数据"));
			return;
		}

		ui.page0->hide();
		ui.page1->show();
		ui.page2->hide();
		ui.page3->hide();

		LoadColorMapping();

		ui.prePushButton->setEnabled(true);
		m_nCurrentPage++;
	}
	else if(m_nCurrentPage == 1)
	{
		ui.page0->hide();
		ui.page1->hide();
		ui.page2->show();
		ui.page3->hide();
		m_nCurrentPage++;

		//把颜色存到配置文件
		SaveColorToConfig();

		//首先将字段填到复选框
		LoadPipeLineMapping();
		//读之前存的配置
		std::string strPath = GsFileSystem::Combine(GsFileSystem::WorkingFolder(), "./config/PipeLineFieldsMapping.xml");
		LoadFieldsFromConfig(0, strPath);
	}
	else if (m_nCurrentPage == 2)
	{
		ui.page0->hide();
		ui.page1->hide();
		ui.page2->hide();
		ui.page3->show();
		m_nCurrentPage++;

		ui.prePushButton->setEnabled(true);
		ui.okPushButton->setEnabled(true);
		ui.nextPushButton->setEnabled(false);

		//首先将字段填到复选框
		LoadPipePointMapping();
		//读之前存的配置
		std::string strPath = GsFileSystem::Combine(GsFileSystem::WorkingFolder(), "./config/PipePointFieldsMapping.xml");
		LoadFieldsFromConfig(1, strPath);
	}
}

void PipeToolWindow::LoadFieldsFromConfig(int type, std::string strPath)
{
	QTableWidget* ptrTable = NULL;
	std::map<int, std::string> mapBridgeFields;
	if (type == 0)
	{
		ptrTable = ui.lineTableWidget;
		mapBridgeFields = m_mapLineBridgeFields;
	}
	else
	{
		ptrTable = ui.pointTableWidget;
		mapBridgeFields = m_mapPointBridgeFields;
	}

	GsConfig config(strPath.c_str());
	GsVector<GsConfig> child = config["FieldsMapping"].Children();

	int nRowCnt = ptrTable->rowCount();
	for (int i = 0; i < nRowCnt; ++i)
	{
		//拿到表格里的复选框
		QComboBox* ptrCheckBox = dynamic_cast<QComboBox*>(ptrTable->cellWidget(i, 1));
		std::string strName = mapBridgeFields[i];

		//在子里面找到对应的实际字段
		for (int j = 0; j < child.size(); ++j)
		{
			if (child[j].Name().c_str() == strName)
			{
				std::string strValue = child[j].Value();
				int nIndex = ptrCheckBox->findText(strValue.c_str());
				ptrCheckBox->setCurrentIndex(nIndex);
			}
		}
	}
}

void PipeToolWindow::SaveFieldsToConfig(int type, std::string strPath)
{
	std::map<std::string, std::string> mapFields;
	std::map<std::string, std::string> mapDesBridgeFields;

	if (type == 0)
	{
		mapFields = m_mapLineFields;
		mapDesBridgeFields = m_mapLineDesBridgeFields;
	}
	else if(type == 1)
	{
		mapFields = m_mapPointFields;
		mapDesBridgeFields = m_mapPointDesBridgeFields;
	}

	GsConfig config;
	GsConfig lineRoot = config.Child("FieldsMapping");
	lineRoot.Type("String");
	lineRoot.Description(GsEncoding::ToUtf8("管线字段映射"));

	std::map<std::string, std::string>::iterator it = mapFields.begin();
	for (it; it != mapFields.end(); ++it)
	{
		GsConfig child = lineRoot.Child((*it).first.c_str());
		child.Type("String");
		child.Value((*it).second);
		child.Description(GsEncoding::ToUtf8(mapDesBridgeFields[(*it).first.c_str()].c_str()));
	}

	bool b = config.Save(strPath.c_str());
}

void PipeToolWindow::ParseSavePipeLineMapping()
{
	m_mapLineFields.clear();
	m_mapPointFields.clear();

	int nLRowCnt = ui.lineTableWidget->rowCount();

	for (int i = 0; i < nLRowCnt; ++i)
	{
		QComboBox* ptrCheckBox = dynamic_cast<QComboBox*>(ui.lineTableWidget->cellWidget(i, 1));
		m_mapLineFields[m_mapLineBridgeFields[i]] = ptrCheckBox->currentText().toLocal8Bit().data();
	}

	std::string strSavePath = GsFileSystem::Combine(GsFileSystem::WorkingFolder(), "./config/PipeLineFieldsMapping.xml");
	SaveFieldsToConfig(0,strSavePath);

	int nPRowCnt = ui.pointTableWidget->rowCount();

	for (int i = 0; i < nPRowCnt; ++i)
	{
		QComboBox* ptrCheckBox = dynamic_cast<QComboBox*>(ui.pointTableWidget->cellWidget(i, 1));
		m_mapPointFields[m_mapPointBridgeFields[i]] = ptrCheckBox->currentText().toLocal8Bit().data();
	}

	strSavePath = GsFileSystem::Combine(GsFileSystem::WorkingFolder(), "./config/PipePointFieldsMapping.xml");
	SaveFieldsToConfig(1, strSavePath);
}

PipeToolWindow::~PipeToolWindow()
{
	if (m_threadPool)
	{
		m_threadPool->stop();
	}
	m_threadPool->wait();
}