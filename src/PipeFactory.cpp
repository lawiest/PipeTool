#include "PipeFactory.h"

#include <utility.h>
#include <osg/Vec3d>
#include "PipeUntility.h"
#include "CircleTwoLinkPipePoint.h"
#include "CirclePipeLine.h"
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osg/MatrixTransform>
#include "CircleThreeLinkPipePoint.h"
#include "CircleFourLinkPipePoint.h"
#include "CircleStraightLinkPipePoint.h"
#include "SquarePipeLine.h"
#include "SquareTwoLinkPipePoint.h"
#include "SquareThreeLinkPipePoint.h"
#include "SquareStraightLinkPipePoint.h"
#include "SquareFourLinkPipePoint.h"
#include <QString>
#include <QFileInfo>
#include <QDir>
#include "GeoGlobleEvent.h"
#include "obj/ReaderWriterOBJ.h"

using namespace KERNEL_NAME;
using namespace UTILITY_NAME;

GLOBE_NS

PipeFactory::PipeFactory(PipeProducePara para)
{
	m_ProducePara = para;
}

std::vector<PipeLinePtr>& PipeFactory::GetPipeLines()
{
	return m_vecPipeLine;
}

std::vector<PipePointPtr>& PipeFactory::GetPipePoints()
{
	return m_vecPipePoint;
}

void PipeFactory::getLineFeature(std::string& strPipeSize,const GsFeaturePtr& ptrLineFea, MyLineFeature& lineFeature)
{
	GsGeometryPtr pGeo = ptrLineFea->Geometry();
	GsGeometryBlob* blob = pGeo->GeometryBlobPtr();
	double *pCorrd = blob->Coordinate();

	double dbStartHeight = ptrLineFea->ValueDouble(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["STARTHEIGHT"].c_str()));
	double dbEndHeight = ptrLineFea->ValueDouble(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["ENDHEIGHT"].c_str()));
	std::string strPipeID = ptrLineFea->ValueString(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["PIPEID"].c_str()));
	std::string strSPointID = ptrLineFea->ValueString(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["PIPESID"].c_str()));
	std::string strEPointID = ptrLineFea->ValueString(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["PIPEEID"].c_str()));

	lineFeature.m_spoint = osg::Vec3d(pCorrd[0], pCorrd[1], dbStartHeight);
	lineFeature.m_epoint = osg::Vec3d(pCorrd[2], pCorrd[3], dbEndHeight);
	lineFeature.m_sheight = dbStartHeight;
	lineFeature.m_eheight = dbEndHeight;
	lineFeature.m_id = strPipeID;
	lineFeature.m_spointid = strSPointID;
	lineFeature.m_epointid = strEPointID;

	strPipeSize = GsStringHelp::ToUpper(strPipeSize.c_str());
	GsVector<GsString> vecSize = GsStringHelp::Split(strPipeSize.c_str(), "X");

	//�Ͼ�����û�������ֶΣ�ͨ���ַ����ж�
	if (vecSize.size() == 1)
	{
		lineFeature.m_diameter = atof(vecSize[0]);
		lineFeature.m_type = Circle;
	}
	else if (vecSize.size() == 2)
	{
		lineFeature.m_width = atof(vecSize[0]);
		lineFeature.m_height = atof(vecSize[1]);
		lineFeature.m_type = SQuare;
	}
}

//�ҵ������
ErrorCode PipeFactory::FindRelativeLine(std::string strPointID, std::vector<MyLineFeature>& vecFeatures)
{
	ErrorCode errorCode = NoError;

	//Ѱ�����
	std::string strWhere = m_ProducePara.m_lineFieldsMap["PIPESID"] + std::string(" = '") + strPointID + "'";
	GsQueryFilterPtr ptrQuery = new GsQueryFilter(strWhere.c_str());
	GsFeatureCursorPtr ptrCursor = m_ptrLineFeatureClass->Search(ptrQuery);
	GsFeaturePtr ptrLineFea = ptrCursor->Next();

	while (true)
	{
		if (NULL == ptrLineFea)
			break;

		std::string strPipeSize = ptrLineFea->ValueString(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["PIPESIZE"].c_str()));

		//���û�йܾ��Ͳ����
		if (strPipeSize != "")
		{
			MyLineFeature lineFeature;
			getLineFeature(strPipeSize, ptrLineFea, lineFeature);
			vecFeatures.push_back(lineFeature);
		}
		else
		{
			errorCode = ZeroPipeSize;
		}

		if (ptrCursor->Next(ptrLineFea) == false)
			break;
	};

	//Ѱ���յ�
	strWhere = m_ProducePara.m_lineFieldsMap["PIPEEID"] + std::string(" = '") + strPointID + "'";
	ptrQuery->WhereClause(strWhere.c_str());
	ptrCursor = m_ptrLineFeatureClass->Search(ptrQuery);

	if (ptrLineFea == NULL)
	{
		ptrLineFea = ptrCursor->Next();
	}
	else if (ptrCursor->Next(ptrLineFea) == false)
	{
		//�����û�й�����Ҳ����û�ܾ����Ǿ���û�߸�������
		if (vecFeatures.size() == 0 && errorCode != ZeroPipeSize)
			errorCode = NoPipeLink;

		return errorCode;
	}

	while (true)
	{
		if (NULL == ptrLineFea)
			break;

		std::string strPipeSize = ptrLineFea->ValueString(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["PIPESIZE"].c_str()));

		//���û�йܾ��Ͳ����
		if (strPipeSize != "")
		{
			MyLineFeature lineFeature;
			getLineFeature(strPipeSize, ptrLineFea, lineFeature);
			vecFeatures.push_back(lineFeature);
		}
		else
		{
			errorCode = ZeroPipeSize;
		}

		if (ptrCursor->Next(ptrLineFea) == false)
			break;
	};

	//�����û�й�����Ҳ����û�ܾ����Ǿ���û�߸�������
	if (vecFeatures.size() == 0 && errorCode != ZeroPipeSize)
		errorCode = NoPipeLink;

	return errorCode;
}

bool CheckIsTwoPointEqual(const osg::Vec3d& p1, const osg::Vec3d& p2)
{
	double EPSILON = 0.00000001;
	//double dbDeltaX = fabs(p1.x() - p2.x());
	//double dbDeltaY = fabs(p1.y() - p2.y());
	//double dbDeltaZ = fabs(p1.z() - p2.z());

	if (fabs(p1.x() - p2.x())<= EPSILON && fabs(p1.y() - p2.y()) <= EPSILON && fabs(p1.z() - p2.z()) <= 0.8)
	{
		return true;
	}
	return false;
}

double GetAngle(osg::Vec3d p1, osg::Vec3d p2)
{
	p1.normalize();
	p2.normalize();

	return  acos(p1*p2);
}

PipeSizePara PipeFactory::getThreeLinkVector(const std::vector<osg::Vec3d>& vecDir, const std::vector<MyLineFeature>& vecLineFeatures, std::vector<osg::Vec3d>& vecTempDir)
{

	PipeSizePara sizePara;
	//���ҳ��Ƕ�������������
	double angle0 = GetAngle(vecDir[0], vecDir[1]);
	double angle1 = GetAngle(vecDir[1], vecDir[2]);
	double angle2 = GetAngle(vecDir[0], vecDir[2]);

	//���������ӵĴ�С
	double thirdDiameter = 0.0;
	double dbThirdWidth = 0.0, dbThirdHeight = 0.0;
	double dbMaxAngle = std::max(std::max(angle0, angle1), angle2);
	if (angle0 == dbMaxAngle)
	{
		vecTempDir.push_back(vecDir[0]);
		vecTempDir.push_back(vecDir[1]);
		vecTempDir.push_back(vecDir[2]);

		if (vecLineFeatures[2].m_type == Circle)
		{
			thirdDiameter = vecLineFeatures[2].m_diameter;
		}
		else if (vecLineFeatures[2].m_type == SQuare)
		{
			dbThirdWidth = vecLineFeatures[2].m_width;
			dbThirdHeight = vecLineFeatures[2].m_eheight;
		}
	}
	else if (angle1 == dbMaxAngle)
	{
		vecTempDir.push_back(vecDir[1]);
		vecTempDir.push_back(vecDir[2]);
		vecTempDir.push_back(vecDir[0]);

		if (vecLineFeatures[0].m_type == Circle)
		{
			thirdDiameter = vecLineFeatures[0].m_diameter;
		}
		else if (vecLineFeatures[0].m_type == SQuare)
		{
			dbThirdWidth = vecLineFeatures[0].m_width;
			dbThirdHeight = vecLineFeatures[0].m_eheight;
		}
	}
	else if (angle2 == dbMaxAngle)
	{
		vecTempDir.push_back(vecDir[0]);
		vecTempDir.push_back(vecDir[2]);
		vecTempDir.push_back(vecDir[1]);

		if (vecLineFeatures[1].m_type == Circle)
		{
			thirdDiameter = vecLineFeatures[1].m_diameter;
		}
		else if (vecLineFeatures[1].m_type == SQuare)
		{
			dbThirdWidth = vecLineFeatures[1].m_width;
			dbThirdHeight = vecLineFeatures[1].m_eheight;
		}
	}

	sizePara.thirdDiameter = thirdDiameter;
	sizePara.m_thirdWidth = dbThirdWidth;
	sizePara.m_thirdHeight = dbThirdHeight;

	return sizePara;
}

void getMaxPipeSize(const MyLineFeature& lineFeatures0, const MyLineFeature& lineFeatures1, double& maxDiameter, double& dbMaxWidth, double& dbMaxHeight)
{
	//Ŀǰֻ����ȫ���Ƿ��ܺ�Բ�������������з�������Բ��Ŀǰ��������
	if (lineFeatures0.m_type == Circle)
	{
		double size0 = lineFeatures0.m_diameter;
		double size1 = lineFeatures1.m_diameter;

		maxDiameter = std::max(size0, size1);
	}
	else if (lineFeatures0.m_type == SQuare)
	{
		double dbMaxWidth0 = lineFeatures0.m_width;
		double dbMaxHeight0 = lineFeatures0.m_height;
		double dbMaxWidth1 = lineFeatures1.m_width;
		double dbMaxHeight1 = lineFeatures1.m_height;

		if (dbMaxWidth0 > dbMaxWidth1)
		{
			dbMaxWidth = dbMaxWidth0;
			dbMaxHeight = dbMaxHeight0;
		}
		else
		{
			dbMaxWidth = dbMaxWidth1;
			dbMaxHeight = dbMaxHeight1;
		}
	}
}

PipeSizePara PipeFactory::getFourLinkVector(const std::vector<osg::Vec3d>& vecDir, const std::vector<MyLineFeature>& vecLineFeatures, std::vector<osg::Vec3d>& vecTempDir)
{
	PipeSizePara sizePara;

	//���ҳ��Ƕ�������������
	double angle0 = GetAngle(vecDir[0], vecDir[1]);
	double angle1 = GetAngle(vecDir[1], vecDir[2]);
	double angle2 = GetAngle(vecDir[2], vecDir[3]);
	double angle3 = GetAngle(vecDir[0], vecDir[2]);
	double angle4 = GetAngle(vecDir[1], vecDir[3]);
	double angle5 = GetAngle(vecDir[0], vecDir[3]);
	//���������ӵĴ�С
	double maxDiameter,thirdDiameter = 0.0;
	double dbMaxWidth = 0.0, dbMaxHeight = 0.0;
	double dbThirdWidth = 0.0, dbThirdHeight = 0.0;

	double dbMaxAngle = std::max(std::max(std::max(std::max(std::max(angle0, angle1), angle2), angle3), angle4), angle5);
	if (angle0 == dbMaxAngle)
	{
		vecTempDir.push_back(vecDir[0]);
		vecTempDir.push_back(vecDir[1]);
		//���Ƕ��������ܾ�
		getMaxPipeSize(vecLineFeatures[0], vecLineFeatures[1],maxDiameter,dbMaxWidth,dbMaxHeight);

		vecTempDir.push_back(vecDir[2]);
		vecTempDir.push_back(vecDir[3]);
		//�����������ܾ�
		getMaxPipeSize(vecLineFeatures[2], vecLineFeatures[3], thirdDiameter, dbThirdWidth, dbThirdHeight);

	}
	else if (angle1 == dbMaxAngle)
	{
		vecTempDir.push_back(vecDir[1]);
		vecTempDir.push_back(vecDir[2]);
		getMaxPipeSize(vecLineFeatures[1], vecLineFeatures[2], maxDiameter, dbMaxWidth, dbMaxHeight);

		vecTempDir.push_back(vecDir[0]);
		vecTempDir.push_back(vecDir[3]);
		getMaxPipeSize(vecLineFeatures[0], vecLineFeatures[3], thirdDiameter, dbThirdWidth, dbThirdHeight);
	}
	else if (angle2 == dbMaxAngle)
	{
		vecTempDir.push_back(vecDir[2]);
		vecTempDir.push_back(vecDir[3]);
		getMaxPipeSize(vecLineFeatures[2], vecLineFeatures[3], maxDiameter, dbMaxWidth, dbMaxHeight);

		vecTempDir.push_back(vecDir[0]);
		vecTempDir.push_back(vecDir[1]);
		getMaxPipeSize(vecLineFeatures[0], vecLineFeatures[1], thirdDiameter, dbThirdWidth, dbThirdHeight);
	}
	else if (angle3 == dbMaxAngle)
	{
		vecTempDir.push_back(vecDir[0]);
		vecTempDir.push_back(vecDir[2]);
		getMaxPipeSize(vecLineFeatures[0], vecLineFeatures[2], maxDiameter, dbMaxWidth, dbMaxHeight);

		vecTempDir.push_back(vecDir[1]);
		vecTempDir.push_back(vecDir[3]);
		getMaxPipeSize(vecLineFeatures[1], vecLineFeatures[3], thirdDiameter, dbThirdWidth, dbThirdHeight);
	}
	else if (angle4 == dbMaxAngle)
	{
		vecTempDir.push_back(vecDir[1]);
		vecTempDir.push_back(vecDir[3]);
		getMaxPipeSize(vecLineFeatures[1], vecLineFeatures[3], maxDiameter, dbMaxWidth, dbMaxHeight);

		vecTempDir.push_back(vecDir[0]);
		vecTempDir.push_back(vecDir[2]);
		getMaxPipeSize(vecLineFeatures[0], vecLineFeatures[2], thirdDiameter, dbThirdWidth, dbThirdHeight);
	}
	else if (angle5 == dbMaxAngle)
	{
		vecTempDir.push_back(vecDir[0]);
		vecTempDir.push_back(vecDir[3]);
		getMaxPipeSize(vecLineFeatures[0], vecLineFeatures[3], maxDiameter, dbMaxWidth, dbMaxHeight);

		vecTempDir.push_back(vecDir[1]);
		vecTempDir.push_back(vecDir[2]);
		getMaxPipeSize(vecLineFeatures[1], vecLineFeatures[2], thirdDiameter, dbThirdWidth, dbThirdHeight);
	}

	sizePara.m_diameter = maxDiameter;
	sizePara.thirdDiameter = thirdDiameter;
	sizePara.m_width = dbMaxWidth;
	sizePara.m_height = dbMaxHeight;
	sizePara.m_thirdWidth = dbThirdWidth;
	sizePara.m_thirdHeight = dbThirdHeight;
	
	return sizePara;
}

//�õ�����
void PipeFactory::getVector(osg::Vec3d pos,const std::vector<MyLineFeature>& vecLineFeatures, std::vector<osg::Vec3d>& vecDir, PipeSizePara& sizePara)
{
	bool bIsCircle = false;
	bool bIsSquare = false;
	bool bIsMix = false;

	double thirdDiameter = 0.0;
	double maxDiameter = 0.0;

	double dbMaxWidth = 0.0, dbMaxHeight = 0.0;
	double dbThirdWidth = 0.0, dbThirdHeight = 0.0;

	osg::Vec3d tempPos = pos;
	for (int i = 0; i < vecLineFeatures.size(); i++)
	{
		double dbStartHeight = 0.0, dbEndHeight = 0.0, diameter = 0.0;
		double dbWidth = 0.0, dbHeight = 0.0;

		dbStartHeight = vecLineFeatures[i].m_sheight;
		dbEndHeight = vecLineFeatures[i].m_eheight;

		//�Ͼ�����û�������ֶΣ�ͨ���ַ����ж�
		if (vecLineFeatures[i].m_type == Circle)
		{
			diameter = vecLineFeatures[i].m_diameter;
			//�ҵ����ܾ�
			if (diameter >= maxDiameter)
				maxDiameter = diameter;

			bIsCircle = true;
		}
		else if (vecLineFeatures[i].m_type == SQuare)
		{
			dbWidth = vecLineFeatures[i].m_width;
			dbHeight = vecLineFeatures[i].m_height;
			bIsSquare = true;

			//����ֻ�ȽϿ���֤�����ͬһ������
			if (dbWidth >= dbMaxWidth)
			{
				dbMaxWidth = dbWidth;
				dbMaxHeight = dbHeight;
			}
		}

		if (bIsCircle && bIsSquare)
		{
			bIsMix = true;
		}

		osg::Vec3d point1 = vecLineFeatures[i].m_spoint;
		osg::Vec3d point2 = vecLineFeatures[i].m_epoint;

		GsSpatialReferencePtr ptrSpatial = m_ptrPointFeatureClass->SpatialReference();
		int nEPSG = ptrSpatial->EPSG();
		//�����Ͼ�û�пռ�ο�
		nEPSG = 1234;

		if (CheckIsTwoPointEqual(pos, point1))
		{
			osg::Vec3d tempPos = pos;
			if (nEPSG == 4326)
			{
				point2 = PipeUntility::ToDKE(point2);
				tempPos = PipeUntility::ToDKE(tempPos);
			}

			osg::Vec3d dir = point2 - tempPos;
			dir.normalize();
			vecDir.push_back(dir);
		}
		else if (CheckIsTwoPointEqual(pos, point2))
		{
			osg::Vec3d tempPos = pos;
			if (nEPSG == 4326)
			{
				point1 = PipeUntility::ToDKE(point1);
				tempPos = PipeUntility::ToDKE(tempPos);
			}

			osg::Vec3d dir = point1 - tempPos;
			dir.normalize();
			vecDir.push_back(dir);
		}
	}

	//�������ͨ����ͨ�Ͱ��Ƕȴ�С�Ÿ���
	if (vecDir.size() == 3)
	{
		std::vector<osg::Vec3d> vecTempDir;

		PipeSizePara sizePara;
		sizePara = getThreeLinkVector(vecDir, vecLineFeatures,vecTempDir);

		thirdDiameter = sizePara.thirdDiameter;
		dbThirdWidth = sizePara.m_thirdWidth;
		dbThirdHeight = sizePara.m_thirdHeight;

		vecDir.clear();
		vecDir = vecTempDir;
	}
	else if(vecDir.size() == 4)
	{
		std::vector<osg::Vec3d> vecTempDir;	

		PipeSizePara sizePara;
		sizePara = getFourLinkVector(vecDir, vecLineFeatures, vecTempDir);

		maxDiameter = sizePara.m_diameter;
		thirdDiameter = sizePara.thirdDiameter;
		dbMaxWidth = sizePara.m_width;
		dbMaxHeight = sizePara.m_height;
		dbThirdWidth = sizePara.m_thirdWidth;
		dbThirdHeight = sizePara.m_thirdHeight;

		vecDir.clear();
		vecDir = vecTempDir;
	}

	sizePara.m_diameter = maxDiameter;
	sizePara.thirdDiameter = thirdDiameter;
	sizePara.m_width = dbMaxWidth;
	sizePara.m_height = dbMaxHeight;
	sizePara.m_thirdWidth = dbThirdWidth;
	sizePara.m_thirdHeight = dbThirdHeight;

	if (bIsMix)
		sizePara.m_type = Mix;
	else if(bIsSquare)
		sizePara.m_type = SQuare;
	else if (bIsCircle)
		sizePara.m_type = Circle;
}

void PipeFactory::DealWithStraightLink(const osg::Vec3d pos, std::string strPointID, const std::vector<osg::Vec3d>& vecDir, const PipeSizePara& sizePara)
{
	if (sizePara.m_type == SQuare)
	{
		std::string strMessage = "����ֱͨ: " + strPointID ;
		safeCout(strMessage);
		SquareStraightLinkPipePointPtr ptrStraight = new SquareStraightLinkPipePoint(vecDir[0], pos, sizePara.m_width,sizePara.m_height,strPointID, m_ProducePara.m_strPipeTypeName);
		ptrStraight->setOriginPoint(m_originePoint);
		ptrStraight->setBold(1.1);
		ptrStraight->setExtend(1.5);
		ptrStraight->setOuterExtend(0.1);
		bool bIsOk = ptrStraight->build();
		ptrStraight->closeFirstSide();

		if (bIsOk)
			m_vecPipePoint.push_back(ptrStraight);
	}
	else if (sizePara.m_type == Circle)
	{
		std::string strMessage = "Բ��ֱͨ: " + strPointID ;
		safeCout(strMessage);
		CircleStraightLinkPipePointPtr ptrStraight = new CircleStraightLinkPipePoint(vecDir[0], pos, sizePara.m_diameter, strPointID, m_ProducePara.m_strPipeTypeName);
		ptrStraight->setOriginPoint(m_originePoint);
		ptrStraight->setBold(1.1);
		ptrStraight->setExtend(1.5);
		ptrStraight->setOuterExtend(0.1);
		bool bIsOk = ptrStraight->build();
		ptrStraight->closeFirstSide();

		if (bIsOk)
			m_vecPipePoint.push_back(ptrStraight);
	}
}


void PipeFactory::DealWith2Link(const osg::Vec3d pos, const std::string strPointID, const std::vector<osg::Vec3d>& vecDir, const PipeSizePara& sizePara)
{
	if (vecDir.size() < 2)
	{
		std::string strMessage = "ע��!��������ͬһ����(ID:" + strPointID + ")���겻һ������ģ��ֹ! ";
		safeCout(strMessage);
		return;
	}

	PipePointPtr ptrPoint = NULL;
	if (sizePara.m_type == SQuare)
	{
		std::string strMessage = "���ܶ�ͨ: " + strPointID;
		safeCout(strMessage);
		ptrPoint = new SquareTwoLinkPipePoint(vecDir, pos, sizePara.m_width, sizePara.m_height, strPointID, m_ProducePara.m_strPipeTypeName);
	}
	else if (sizePara.m_type == Circle)
	{
		std::string strMessage = "Բ�ܶ�ͨ: " + strPointID;
		safeCout(strMessage);
		ptrPoint = new CircleTwoLinkPipePoint(vecDir, pos, sizePara.m_diameter, strPointID, m_ProducePara.m_strPipeTypeName);
	}

	if (ptrPoint == NULL)
		return;

	ptrPoint->setOriginPoint(m_originePoint);
	bool bIsOk = ptrPoint->build();

	if (bIsOk)
		m_vecPipePoint.push_back(ptrPoint);
}

void PipeFactory::DealWith3Link(const osg::Vec3d pos, const std::string strPointID, const std::vector<osg::Vec3d>& vecDir, const PipeSizePara& sizePara)
{
	if (vecDir.size() < 3)
	{
		std::string strMessage = "ע��!��������ͬһ����(ID:" + strPointID + ")���겻һ������ģ��ֹ! ";
		safeCout(strMessage);
		return;
	}

	PipePointPtr ptrPoint = NULL;
	if (sizePara.m_type == SQuare)
	{
		std::string strMessage = "������ͨ: " + strPointID;
		safeCout(strMessage);
		ptrPoint = new SquareThreeLinkPipePoint(vecDir, pos, sizePara.m_width, sizePara.m_height, sizePara.m_thirdWidth, sizePara.m_thirdHeight, strPointID, m_ProducePara.m_strPipeTypeName);
	}
	else if (sizePara.m_type == Circle)
	{
		std::string strMessage = "Բ����ͨ: " + strPointID;
		safeCout(strMessage);
		ptrPoint = new CircleThreeLinkPipePoint(vecDir, pos, sizePara.m_diameter, sizePara.thirdDiameter, strPointID, m_ProducePara.m_strPipeTypeName);
	}

	if (ptrPoint == NULL)
		return;

	ptrPoint->setOriginPoint(m_originePoint);
	bool bIsOk = ptrPoint->build();

	if (bIsOk)
		m_vecPipePoint.push_back(ptrPoint);
}

void PipeFactory::DealWith4Link(const osg::Vec3d pos, const std::string strPointID, const std::vector<osg::Vec3d>& vecDir, const PipeSizePara& sizePara)
{
	if (vecDir.size() < 4)
	{
		std::string strMessage = "ע��!��������ͬһ����(ID:" + strPointID + ")���겻һ������ģ��ֹ! ";
		safeCout(strMessage);
		return;
	}

	PipePointPtr ptrPoint = NULL;
	if (sizePara.m_type == SQuare)
	{
		std::string strMessage = "������ͨ: " + strPointID;
		safeCout(strMessage);
		ptrPoint = new SquareFourLinkPipePoint(vecDir, pos, sizePara.m_width, sizePara.m_height, sizePara.m_thirdWidth, sizePara.m_thirdHeight, strPointID, m_ProducePara.m_strPipeTypeName);
	}
	else if (sizePara.m_type == Circle)
	{
		std::string strMessage = "Բ����ͨ: " + strPointID;
		safeCout(strMessage);
		ptrPoint = new CircleFourLinkPipePoint(vecDir, pos, sizePara.m_diameter, sizePara.thirdDiameter, strPointID, m_ProducePara.m_strPipeTypeName);
	}

	if (ptrPoint == NULL)
		return;

	ptrPoint->setOriginPoint(m_originePoint);
	bool bIsOk = ptrPoint->build();

	if (bIsOk)
		m_vecPipePoint.push_back(ptrPoint);
}

void PipeFactory::safeCout(std::string strMessage)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	std::cout << strMessage << std::endl;
}

void PipeFactory::DealWithPoint(osg::Vec3d pos, std::string strPointID)
{
	std::vector<MyLineFeature> vecLineFeatures;

	//�ҵ��õ����������
	ErrorCode errordode = FindRelativeLine(strPointID, vecLineFeatures);

	if (vecLineFeatures.size() == 0 && errordode == ZeroPipeSize)
	{
		std::string strMessage = "�͹ܵ�: " + strPointID + "�������߹ܾ���Ϊ��!";
		safeCout(strMessage);
		return;
	}
	else if(vecLineFeatures.size() == 0 && errordode == NoPipeLink)
	{
		std::string strMessage = "û�ߺ͹ܵ�: " + strPointID + "����!";
		safeCout(strMessage);

		return;
	}

	std::vector<osg::Vec3d> vecDir;
	PipeSizePara sizePara;
	//��øõ����������������ܾ�
	getVector(pos, vecLineFeatures, vecDir, sizePara);

	if (vecDir.size() == 0)
	{
		std::string strMessage = "�ܵ�: " + strPointID + "�����������ȷ!";
		safeCout(strMessage);

		return;
	}

	if (strPointID == "130207.053-146683.800")
	{
		int i = 0;
		i++;
	}

	GsSpatialReferencePtr ptrSpatial = m_ptrPointFeatureClass->SpatialReference();
	int nEPSG = ptrSpatial->EPSG();
	//�����Ͼ�����û�пռ�ο�������㸶��ֵ
	nEPSG = 1234;

	osg::Vec3d tempPos = pos;
	//����Ǿ�γ�Ⱦ���ת�ѿ���
	if (nEPSG == 4326)
		tempPos = PipeUntility::ToDKE(pos);

	if (sizePara.m_type == Mix)
	{
		std::string strMessage = "�͹ܵ�: " + strPointID + "�������߼��з�������Բ��!";
		safeCout(strMessage);
	}

	if (vecLineFeatures.size() == 1)
	{
		return DealWithStraightLink(tempPos, strPointID, vecDir, sizePara);
	}
	else if (vecLineFeatures.size() == 2)
	{
		return DealWith2Link(tempPos,strPointID,vecDir,sizePara);
	}
	else if (vecLineFeatures.size() == 3)
	{
		return DealWith3Link(tempPos, strPointID, vecDir, sizePara);
	}
	else if (vecLineFeatures.size() == 4)
	{
		return DealWith4Link(tempPos, strPointID, vecDir, sizePara);
	}
	else
	{
		std::string strMessage = std::to_string(vecLineFeatures.size()) +"ͨ: " + strPointID + "��ʱû�д���";
		safeCout(strMessage);
	}
}

double PipeFactory::GetPointHeightInLine(std::string strPointID)
{
	//Ѱ�����
	std::string strWhere = m_ProducePara.m_lineFieldsMap["PIPESID"] + std::string(" = '") + strPointID + "'";
	GsQueryFilterPtr ptrQuery = new GsQueryFilter(strWhere.c_str());
	GsFeatureCursorPtr ptrCursor = m_ptrLineFeatureClass->Search(ptrQuery);
	GsFeaturePtr ptrLineFea = ptrCursor->Next();
	double pointHeight;

	while (true)
	{
		if (NULL == ptrLineFea)
			break;

		//��������ID�ҵ�һ���ߣ�ֱ��ȡ���ߵ����߳�
		pointHeight = ptrLineFea->ValueDouble(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["STARTHEIGHT"].c_str()));
		return pointHeight;

		if (ptrCursor->Next(ptrLineFea) == false)
			break;
	};

	//Ѱ���յ�
	strWhere = m_ProducePara.m_lineFieldsMap["PIPEEID"] + std::string(" = '") + strPointID + "'";
	ptrQuery->WhereClause(strWhere.c_str());
	ptrCursor = m_ptrLineFeatureClass->Search(ptrQuery);

	if (ptrLineFea == NULL)
	{
		ptrLineFea = ptrCursor->Next();
	}
	else
	{
		if (ptrCursor->Next(ptrLineFea) == false)
			return 0.0;
	}

	while (true)
	{
		if (NULL == ptrLineFea)
			break;

		//������յ�ID�ҵ�һ���ߣ�ֱ��ȡ���ߵ��յ�߳�
		pointHeight = ptrLineFea->ValueDouble(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["ENDHEIGHT"].c_str()));
		return pointHeight;

		if (ptrCursor->Next(ptrLineFea) == false)
			break;
	};

	return 0.0;
}

std::string PipeFactory::FindModelFile(std::string strModelName)
{
	for (int i = 0; i < m_ProducePara.m_vecModel.size(); ++i)
	{
		std::string strFilePath = GsEncoding::ToUtf8(m_ProducePara.m_vecModel[i].c_str()).c_str();
		GsFile file(strFilePath.c_str());
		std::string strName = file.Name(false).c_str();
		if (strName == strModelName)
			return m_ProducePara.m_vecModel[i];
	}

	return "no find!";
}

void PipeFactory::DealWithAppendant(std::string strPointName, std::string strAppendantName, osg::Vec3d pos,double dbAngle)
{
	osg::Vec3d transPoint = pos - m_originePoint;

	std::map<std::string, osg::ref_ptr<osg::Node> >::iterator it = m_mapAppendantUnique.find(strAppendantName);

	if (it != m_mapAppendantUnique.end())
	{
		osg::ref_ptr<osg::MatrixTransform> m_ptrMatrixNode = new osg::MatrixTransform();
		m_ptrMatrixNode->setName(strAppendantName);
		m_ptrMatrixNode->addChild((*it).second);
		osg::Matrixd mat = osg::Matrixd::rotate(dbAngle, osg::Vec3d(0.0, 0.0, 1.0)) *osg::Matrixd::translate(transPoint);
		m_ptrMatrixNode->setMatrix(mat);

		m_mapAppendant[strPointName] = m_ptrMatrixNode;
	}
	else
	{
		std::string strModelPath = FindModelFile(strAppendantName);

		if (strModelPath == "no find!")
			return;

		osg::ref_ptr<osg::Node> ptrNode = osgDB::readNodeFile(strModelPath);

		if (ptrNode == NULL)
			return;

		osg::ref_ptr<osg::MatrixTransform> m_ptrMatrixNode = new osg::MatrixTransform();
		m_ptrMatrixNode->setName(strAppendantName);
		m_ptrMatrixNode->addChild(ptrNode);
		osg::Matrixd mat = osg::Matrixd::rotate(dbAngle, osg::Vec3d(0.0, 0.0, 1.0))*osg::Matrixd::translate(transPoint);
		m_ptrMatrixNode->setMatrix(mat);

		if (ptrNode)
		{
			m_mapAppendant[strPointName] = m_ptrMatrixNode;
			m_mapAppendantUnique[strAppendantName] = ptrNode;
		}
	}
}

void PipeFactory::BuildPipePoint()
{
	QFileInfo file(QString::fromLocal8Bit(m_ProducePara.m_strPointPath.c_str()));

	std::string strPath = file.absolutePath().toStdString();
	std::string strName = file.baseName().toStdString();

	GsConnectProperty prop;
	prop.Server = strPath;
	prop.DataSourceType = eFile;

	GsFileGeoDatabaseFactory fac;
	GsGeoDatabasePtr ptrDB = fac.Open(prop);

	if (!ptrDB.p)
		return;

	m_ptrPointFeatureClass = ptrDB->OpenFeatureClass(strName.c_str());

	if (NULL == m_ptrLineFeatureClass)
	{
		std::string strMessage = "ʸ����ʧ��!";
		safeCout(strMessage);
		return;
	}

	GsFeatureCursorPtr ptrCur = m_ptrPointFeatureClass->Search();
	GsFeaturePtr ptrFea = ptrCur->Next();

	bool bIsFirst = true;
	while (true)
	{
		if (NULL == ptrFea)
			break;

		GsGeometryPtr pGeo = ptrFea->Geometry();
		GsGeometryBlob* blob = pGeo->GeometryBlobPtr();
		double *pCorrd = blob->Coordinate();
		int Dms = blob->CoordinateDimension();

		double dbPointHeight;
		std::string strPointID;

		strPointID = ptrFea->ValueString(m_ptrPointFeatureClass->Fields().FindField(m_ProducePara.m_pointFieldsMap["POINTID"].c_str()));

		//���û�йܵ�̣߳���Ҫ��������ȥȡ
		if (m_ProducePara.m_pointFieldsMap["POINTHEIGHT"] == "")
			dbPointHeight = GetPointHeightInLine(strPointID);
		else
			dbPointHeight = ptrFea->ValueDouble(m_ptrPointFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["POINTHEIGHT"].c_str()));

		std::string strAppendant = ptrFea->ValueString(m_ptrPointFeatureClass->Fields().FindField(m_ProducePara.m_pointFieldsMap["POINTMODEL"].c_str()));
		
		osg::Vec3d pos = osg::Vec3d(pCorrd[0], pCorrd[1], dbPointHeight);

		if (strAppendant != "")
		{
			std::string strMessage = "������:" + strPointID;
			safeCout(strMessage);
			double dbRotateAngel = ptrFea->ValueString(m_ptrPointFeatureClass->Fields().FindField(m_ProducePara.m_pointFieldsMap["ROTATEANGLE"].c_str()));
			DealWithAppendant(strPointID, strAppendant, pos, dbRotateAngel);
		}
		else
		{
			DealWithPoint(pos, strPointID);
		}

		if (ptrCur->Next(ptrFea) == false)
			break;
	}
}

int PipeFactory::EPSG()
{
	return m_nEPSG;
}

void PipeFactory::BuildPipeLine()
{
	QFileInfo file(QString::fromLocal8Bit(m_ProducePara.m_strLinePath.c_str()));

	std::string strPath = file.absolutePath().toStdString();
	std::string strName = file.baseName().toStdString();

	GsConnectProperty prop;
	prop.Server = strPath;
	prop.DataSourceType = eFile;
	GsFileGeoDatabaseFactory fac;
	GsGeoDatabasePtr ptrDB = fac.Open(prop);

	if (!ptrDB.p)
		return ;

	m_ptrLineFeatureClass = ptrDB->OpenFeatureClass(strName.c_str());

	if (NULL == m_ptrLineFeatureClass)
	{
		std::string strMessage = "ʸ����ʧ��!";
		safeCout(strMessage);
		return;
	}

	GsFeatureCursorPtr ptrCur = m_ptrLineFeatureClass->Search();
	GsSpatialReferencePtr ptrSpatial = m_ptrLineFeatureClass->SpatialReference();

	int nEPSG = ptrSpatial->EPSG();
	//�����Ͼ����ڲ�֪���ռ�ο�,����㸶��ֵ����Ȼ�ں˻�Ĭ�ϸ���4326���º���
	nEPSG = 1234;
	m_nEPSG = nEPSG;

	GsFeaturePtr ptrFea = ptrCur->Next();

	bool bIsFirst = true;
	while (true)
	{
		if (NULL == ptrFea)
			break;

		GsGeometryPtr pGeo = ptrFea->Geometry();
		GsGeometryBlob* blob = pGeo->GeometryBlobPtr();
		double *pCorrd = blob->Coordinate();
		int Dms = blob->CoordinateDimension();

		double dbStartHeight = 0.0 , dbEndHeight = 0.0, dbPipeSize = 0.0;
		double dbWidth = 0.0, dbHeight = 0.0;
		std::string strPipeID;
		bool bIsSquare = false;

		dbStartHeight = ptrFea->ValueDouble(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["STARTHEIGHT"].c_str()));
		dbEndHeight = ptrFea->ValueDouble(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["ENDHEIGHT"].c_str()));
		strPipeID = ptrFea->ValueString(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["PIPEID"].c_str()));

		std::string strPipeSize = ptrFea->ValueString(m_ptrLineFeatureClass->Fields().FindField(m_ProducePara.m_lineFieldsMap["PIPESIZE"].c_str()));

		strPipeSize = GsStringHelp::ToUpper(strPipeSize.c_str());
		GsVector<GsString> vecSize =  GsStringHelp::Split(strPipeSize.c_str(), "X");

		if (vecSize.size() == 0)
		{
			std::string strMessage = "����: " + strPipeID + "û�йܾ�!";
			safeCout(strMessage);
			if (ptrCur->Next(ptrFea) == false)
				break;

			continue;
		}

		//�Ͼ�����û�������ֶΣ�ͨ���ַ����ж�
		if (vecSize.size() == 1)
		{
			dbPipeSize = atof(vecSize[0]);
			bIsSquare = false;
		}
		else if(vecSize.size() == 2)
		{
			dbWidth = atof(vecSize[0]);
			dbHeight = atof(vecSize[1]);
			bIsSquare = true;
		}

		//����ʸ������˵����ȷ����������
		osg::Vec3d point1 = osg::Vec3d(pCorrd[0], pCorrd[1], dbStartHeight);
		osg::Vec3d point2 = osg::Vec3d(pCorrd[2], pCorrd[3], dbEndHeight);

		//��ΪԴ�㣬���е������ƫ��
		if (bIsFirst)
		{
			osg::Vec3d tempOrigine1 = point1;
			osg::Vec3d tempOrigine2 = point2;
			osg::Vec3d vecAbsolutePoint1;
			osg::Vec3d vecAbsolutePoint2;

			//����Ǿ�γ�ȣ���ת�ѿ���
			if (nEPSG == 4326)
			{
				vecAbsolutePoint1 = PipeUntility::ToDKE(tempOrigine1);
				vecAbsolutePoint2 = PipeUntility::ToDKE(tempOrigine2);
				m_origineWgs84Point = (tempOrigine1 + tempOrigine2) / 2.0;
			}
			else
			{
				vecAbsolutePoint1 = tempOrigine1;
				vecAbsolutePoint2 = tempOrigine2;
			}

			m_originePoint = (vecAbsolutePoint1 + vecAbsolutePoint2) / 2;

			bIsFirst = false;
		}

		//����Ǿ�γ�ȣ���ת�ѿ���
		if (nEPSG == 4326)
		{
			point1 = PipeUntility::ToDKE(point1);
			point2 = PipeUntility::ToDKE(point2);
		}

		std::string strMessage = "����: " + strPipeID ;
		safeCout(strMessage);

		PipeLinePtr ptrPipe = NULL;
		bool bIsOk = false;
		
		if (bIsSquare)
		{
			//����
			ptrPipe = new SquarePipeLine(point1, point2, strPipeID, dbWidth, dbHeight, m_ProducePara.m_strPipeTypeName);
		}
		else
		{
			//Բ��
			ptrPipe = new CirclePipeLine(point1, point2, strPipeID, dbPipeSize, m_ProducePara.m_strPipeTypeName);
		}

		ptrPipe->setOriginePoint(m_originePoint);
		bIsOk = ptrPipe->Build();

		if (bIsOk)
			m_vecPipeLine.push_back(ptrPipe);

		if (ptrCur->Next(ptrFea) == false)
			break;
	}
}

void PipeFactory::SaveMetaData()
{
	std::string strMetaDataPath = m_ProducePara.m_strSavePath + "/" + m_ProducePara.m_strDataSetName + "/" +
		m_ProducePara.m_strPipeTypeName + "/";

	strMetaDataPath += "metadata.xml";

	std::ofstream ofile;
	ofile.open(strMetaDataPath);

	if (!ofile.is_open())
	{
		std::string strMessage =  "���棡metadata.xml�ļ�����ʧ��! ԭ���Ǵ�ʧ��!";
		safeCout(strMessage);
		return;
	}

	std::string strMetaHead = "<?xml version = \"1.0\" encoding = \"utf-8\"?>\n"
							  "<ModelMetadata version = \"1\">";

	ofile << strMetaHead << std::endl;

	std::string strMetaSrs = "<SRS>" + std::to_string(m_nEPSG) + "</SRS>";
	ofile << strMetaSrs << std::endl;

	osg::Vec3d origin;
	if (m_nEPSG == 4326)
		origin = m_origineWgs84Point;
	else
		origin = m_originePoint;

	std::string strMetaSrsOrigin = "<SRSOrigin>" + std::to_string(origin.x()) + ","+ std::to_string(origin.y()) + "," + std::to_string(origin.z()) + "</SRSOrigin>";
	ofile << strMetaSrsOrigin << std::endl;

	std::string strMetaTextureVisible = " <Texture>\n"
										"<ColorSource>Visible</ColorSource>\n"
										"</Texture>";
	ofile << strMetaTextureVisible << std::endl;

	std::string strEndHead = "</ModelMetadata>";
	ofile << strEndHead << std::endl;

	ofile.close();
}

osg::Vec3d PipeFactory::getPipeColor()
{
	QString strLinePath = QString::fromLocal8Bit(m_ProducePara.m_strLinePath.c_str());

	QStringList qstrList = strLinePath.split("_");
	qstrList[1].toUtf8();
	
	std::string strColor = m_ProducePara.m_mapColor[qstrList[1].toLocal8Bit().data()];
	if (strColor == "")
		return osg::Vec3d(1.0, 1.0, 1.0);

	GsVector<GsString> gstrVec = GsStringHelp::Split(strColor.c_str(), ",");
	double r = atof(gstrVec[0]) / 255.0;
	double g = atof(gstrVec[1]) / 255.0;
	double b = atof(gstrVec[2]) / 255.0;

	return osg::Vec3d(r, g, b);
}

void PipeFactory::SaveMaterial(std::string strPath, osg::Vec3d color)
{
	std::string strMaterialPath = strPath + m_ProducePara.m_strPipeTypeName + ".mtl";

	std::ofstream ofileMaterial;
	ofileMaterial.open(strMaterialPath);

	if (!ofileMaterial.is_open())
		return;

	//������
	std::string strMaterialName = "newmtl " + m_ProducePara.m_strPipeTypeName + "_mtl";
	ofileMaterial << strMaterialName << std::endl;

	std::string strMaterialHead = "Ns 32.0000 \n"
		"Ni 1.5000 \n"
		"d 1.0000 \n"
		"Tr 0.0000 \n"
		"Tf 1.0000 1.0000 1.0000 \n"
		"illum 2";

	//����ͷ
	ofileMaterial << strMaterialHead << std::endl;
	//������
	ofileMaterial << "Ka 0.3451 0.3451 0.3451" << std::endl;
	//������
	std::string strdiffuse = "Kd " + std::to_string(color.x()) + " " + std::to_string(color.y()) + " " + std::to_string(color.z());
	ofileMaterial << strdiffuse << std::endl;
	//���淴��
	ofileMaterial << "Ks 0.1500 0.1500 0.1500" << std::endl;
	//������
	ofileMaterial << "Ke 0.0000 0.0000 0.0000" << std::endl;
}

void PipeFactory::SaveAndShowObj()
{
	osgDB::Options* option = new osgDB::Options(std::string("noTriStripPolygons"));

	std::string strPipePath = m_ProducePara.m_strSavePath + "/" + m_ProducePara.m_strDataSetName + "/" +
		m_ProducePara.m_strPipeTypeName + "/";

	GsString gstrFileName = GsEncoding::ToUtf8(strPipePath.c_str());
	GsDir dir(gstrFileName);
	if (!dir.Exists())
		dir.Create();

	osg::Vec3d color = getPipeColor();
	SaveMaterial(strPipePath, color);

	//�������
	for (int i = 0; i < m_vecPipeLine.size(); i++)
	{
		PipeLinePtr circlePipe = m_vecPipeLine[i];

		std::string strMessage = "�������: " + circlePipe->getPipeName() + ".obj";
		safeCout(strMessage);

		std::string strTempSavePath = strPipePath;

		circlePipe->SaveToObj(strTempSavePath);

		//strTempSavePath += circlePipe->getPipeName() + ".obj";
		//osg::Node* ptrNode = osgDB::readNodeFile(strTempSavePath, option);
		//osg::ref_ptr<GeoGlobleEventAdapter> ptrUserEvenAdapter = new GeoGlobleEventAdapter();
		//ptrUserEvenAdapter->setEventType(ADD_NODE);
		//ptrUserEvenAdapter->setData(ptrNode);
		//GLOBE_NAME::PipeUntility::getViewer()->getEventQueue()->userEvent(ptrUserEvenAdapter);
	}

	//����ܵ�
	for (int i = 0; i < m_vecPipePoint.size(); i++)
	{
		PipePointPtr point = m_vecPipePoint[i];

		std::string strMessage = "����ܵ�: " + point->getPipePointName() + ".obj";
		safeCout(strMessage);

		std::string strTempSavePath = strPipePath;
		point->SaveToObj(strTempSavePath);

		//strTempSavePath += point->getPipePointName() + ".obj";
		//osg::Node* ptrNode = osgDB::readNodeFile(strTempSavePath, option);

		//osg::ref_ptr<GeoGlobleEventAdapter> ptrUserEvenAdapter = new GeoGlobleEventAdapter();
		//ptrUserEvenAdapter->setEventType(ADD_NODE);
		//ptrUserEvenAdapter->setData(ptrNode);
		//GLOBE_NAME::PipeUntility::getViewer()->getEventQueue()->userEvent(ptrUserEvenAdapter);
	}

	//���渽����
	std::map<std::string, osg::ref_ptr<osg::Node> >::iterator it = m_mapAppendant.begin();

	ReaderWriterOBJ rwObj;
	for (it; it != m_mapAppendant.end(); it++)
	{
		std::string strPipePath = m_ProducePara.m_strSavePath + "/" + m_ProducePara.m_strDataSetName + "/" +
									m_ProducePara.m_strPipeTypeName + "/";

		strPipePath += (*it).first + ".obj";

		std::string strMessage = "���渽����: " + (*it).first + ".obj";
		safeCout(strMessage);

		rwObj.writeNode(*(*it).second, strPipePath);
		//osgDB::writeNodeFile(*(*it).second,strPipePath);

		CopyTexture();
		
		//osg::Node* ptrNode = osgDB::readNodeFile(strPipePath, option);
		//osg::ref_ptr<GeoGlobleEventAdapter> ptrUserEvenAdapter = new GeoGlobleEventAdapter();
		//ptrUserEvenAdapter->setEventType(ADD_NODE);
		//ptrUserEvenAdapter->setData(ptrNode);
		//GLOBE_NAME::PipeUntility::getViewer()->getEventQueue()->userEvent(ptrUserEvenAdapter);
	}

	SaveMetaData();
}

void PipeFactory::traverseAllTexture(QString qstrFileName)
{
	QDir dir(qstrFileName);

	if (!dir.exists())
		return;

	std::string strPipePath = m_ProducePara.m_strSavePath + "/" + m_ProducePara.m_strDataSetName + "/" +
		m_ProducePara.m_strPipeTypeName + "/";

	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

	QFileInfoList fileList = dir.entryInfoList();

	int fileCount = fileList.count();
	for (int i = 0; i < fileCount; i++)
	{
		QFileInfo fileInfo = fileList[i];

		if (fileInfo.isFile())
		{
			QString suffix = fileInfo.suffix();

			if (QString::compare(suffix, QString("jpg"), Qt::CaseInsensitive) == 0
				|| QString::compare(suffix, QString("png"), Qt::CaseInsensitive) == 0
				|| QString::compare(suffix, QString("bmp"), Qt::CaseInsensitive) == 0)

			{
				/*��ȡ�ļ�����·����ȫ·��*/
				QString filePath = fileInfo.absoluteFilePath();

				QFile file(filePath);
				QString qstrSave = QString::fromLocal8Bit(strPipePath.c_str()) + fileInfo.fileName().toLocal8Bit();
				bool b = file.copy(qstrSave);
			}
		}
	}
}

void PipeFactory::CopyTexture()
{
	std::map<std::string, osg::ref_ptr<osg::Node> >::iterator it = m_mapAppendantUnique.begin();

	for (it; it != m_mapAppendantUnique.end(); it++)
	{
		std::string strModelPath = FindModelFile((*it).first);
		QString qstrModel = QString::fromLocal8Bit(strModelPath.c_str());
		QFileInfo fileInfo(qstrModel);

		traverseAllTexture(fileInfo.absolutePath());
	}
}

PipeFactory::~PipeFactory()
{

}

GLOBE_ENDNS