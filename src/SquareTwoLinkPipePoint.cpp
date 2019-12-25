#include "SquareTwoLinkPipePoint.h"
#include "PipeUntility.h"
#include <utility.h>
#include "Cuboid.h"

GLOBE_NS

SquareTwoLinkPipePoint::SquareTwoLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double dbWidth, double dbHeight, std::string strPointID, std::string strTypeName)
									:PipePoint(postion, strPointID, strTypeName)
{
	//两个方向向量
	m_vecDir = vecDir;
	//管径宽
	m_dbWidth = dbWidth / 1000.0;
	//管径高
	m_dbHeight = dbHeight / 1000.0;

	m_originePoint = osg::Vec3d(0.0,0.0,0.0);

	m_ptrVetexArry = NULL;
	m_ptrNormal = NULL;
	m_ptrIndex = NULL;

	//加粗
	m_dbBold = 1.2;
	//两头延长
	m_dbExtend = 1.1;
	m_dbOuterExtend = 0.3;
	//外圈加粗
	m_dbOuterBold = 1.06;
}

void SquareTwoLinkPipePoint::setOuterExtend(double dbOuterExtend)
{
	m_dbOuterExtend = dbOuterExtend;
}

void SquareTwoLinkPipePoint::setExtend(double dbExtend)
{
	m_dbExtend = dbExtend;
}

void SquareTwoLinkPipePoint::CalcuSectionCenterPoints(const osg::Vec3d& start, const osg::Vec3d& center, const osg::Vec3d& end)
{
	const int nStack = 8;
	m_vCenterPoints.clear();
	m_vCenterPoints.push_back(start);

	bool bIsInterpolate = true;

	//这种情况下不需要插值
	double dbAngle = acos(m_vecDir[0]* m_vecDir[1]);
	if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON)
		bIsInterpolate = false;

	if (bIsInterpolate)
	{
		for (int i = 1; i < nStack - 1; i++)
		{
			double delta = static_cast<float>(i) / (nStack - 1);
			osg::Vec3d interpolatPt = PipeUntility::BSpline2Ex(delta, start, center, end);
			m_vCenterPoints.push_back(interpolatPt);
		}
	}

	m_vCenterPoints.push_back(end);
}

bool SquareTwoLinkPipePoint::build()
{	
	if (fabs(m_dbWidth) <= DBL_EPSILON || fabs(m_dbHeight) <= DBL_EPSILON)
	{
		//m_dbPipeSize = 0.05*1.2;
		return false;
	}

	//加粗
	m_dbWidth *= m_dbBold;
	m_dbHeight *= m_dbBold;

	double dbAvgPipeSize = (m_dbWidth + m_dbHeight)*0.8 / 2.0;

	//偏移
	m_centerPostion -= m_originePoint;
	//首点
	osg::Vec3d startPoint = m_centerPostion + m_vecDir[0] * dbAvgPipeSize * m_dbExtend;
	//尾点
	osg::Vec3d endPoint = m_centerPostion + m_vecDir[1] * dbAvgPipeSize * m_dbExtend;
	//求得所有中心点
	CalcuSectionCenterPoints(startPoint, m_centerPostion, endPoint);

	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	//在X-Z平面标准矩形四个点
	std::vector<osg::Vec3d> ptrBaseVec3Arry;
	osg::Vec3d righttop = osg::Vec3d(m_dbHeight / 2.0, 0.0, m_dbWidth / 2.0);
	osg::Vec3d rightbottom = osg::Vec3d(m_dbHeight / 2.0, 0.0, -m_dbWidth / 2.0);
	osg::Vec3d leftbottom = osg::Vec3d(-m_dbHeight / 2.0, 0.0, -m_dbWidth / 2.0);
	osg::Vec3d lefttop = osg::Vec3d(-m_dbHeight / 2.0, 0.0, m_dbWidth / 2.0);
	ptrBaseVec3Arry.push_back(righttop);
	ptrBaseVec3Arry.push_back(lefttop);
	ptrBaseVec3Arry.push_back(leftbottom);
	ptrBaseVec3Arry.push_back(rightbottom);

	std::vector<osg::Vec3d> tempVec3Arry;
	//变换
	TransformAllVetex(ptrBaseVec3Arry, tempVec3Arry);

	Calculate(tempVec3Arry);

	Close();

	return true;
}


void SquareTwoLinkPipePoint::Close()
{
	//建一个长方体
	osg::Vec3d absolutPos = m_vCenterPoints[0] + m_centerPostion + m_originePoint;
	Cuboid cubiod(m_vecDir[0], absolutPos, m_dbWidth * 1000, m_dbHeight * 1000, m_strPointID,m_strTypeName);
	cubiod.setOriginPoint(m_originePoint);
	cubiod.build();

	osg::Vec3dArray* ptrVetex = cubiod.getVetexArray();
	osg::Vec3dArray* ptrNormal = cubiod.getNormalArray();
	osg::DrawElementsUShort* ptrIndex = cubiod.getIndexArray();

	//合并顶点和法线
	int nCnt = m_ptrVetexArry->size();
	for (int i = 0; i < ptrVetex->size(); ++i)
	{
		m_ptrVetexArry->push_back((*ptrVetex)[i]);
		m_ptrNormal->push_back((*ptrNormal)[i]);
	}
	//合并索引
	for (int j = 0; j < ptrIndex->size(); ++j)
	{
		m_ptrIndex->push_back((*ptrIndex)[j] + nCnt);
	}

	//再建一个长方体
	absolutPos = m_vCenterPoints[m_vCenterPoints.size()-1] + m_centerPostion + m_originePoint;
	Cuboid cubiod2(m_vecDir[1], absolutPos, m_dbWidth * 1000, m_dbHeight * 1000, m_strPointID,m_strTypeName);
	cubiod2.setOriginPoint(m_originePoint);
	cubiod2.build();

	ptrVetex = cubiod2.getVetexArray();
	ptrNormal = cubiod2.getNormalArray();
	ptrIndex = cubiod2.getIndexArray();

	//合并顶点和法线
	nCnt = m_ptrVetexArry->size();
	for (int i = 0; i < ptrVetex->size(); ++i)
	{
		m_ptrVetexArry->push_back((*ptrVetex)[i]);
		m_ptrNormal->push_back((*ptrNormal)[i]);
	}
	//合并索引
	for (int j = 0; j < ptrIndex->size(); ++j)
	{
		m_ptrIndex->push_back((*ptrIndex)[j] + nCnt);
	}
}

//计算
void SquareTwoLinkPipePoint::Calculate(const std::vector<osg::Vec3d>& ptrTempVec3Arry)
{
	int nCnt = 4;
	int nLoop = ptrTempVec3Arry.size() / nCnt;

	for (int j = 0; j < nLoop - 1; j++)
	{	
		for (int i = 0; i < nCnt; ++i)
		{
			int nSize = m_ptrVetexArry->size();
			if (i == nCnt - 1)
			{
				m_ptrVetexArry->push_back(ptrTempVec3Arry[nCnt*j + i]);
				m_ptrVetexArry->push_back(ptrTempVec3Arry[nCnt*j + nCnt + i]);
				m_ptrVetexArry->push_back(ptrTempVec3Arry[nCnt*j + nCnt]);
				m_ptrVetexArry->push_back(ptrTempVec3Arry[nCnt*j]);

				osg::Vec3d normal = (ptrTempVec3Arry[nCnt*j] - ptrTempVec3Arry[nCnt*j + i]) ^ (ptrTempVec3Arry[nCnt*j + nCnt + i] - ptrTempVec3Arry[nCnt*j + i]);
				normal.normalize();
				m_ptrNormal->push_back(normal);
				m_ptrNormal->push_back(normal);
				m_ptrNormal->push_back(normal);
				m_ptrNormal->push_back(normal);

				m_ptrIndex->push_back(nSize + 0);
				m_ptrIndex->push_back(nSize + 2);
				m_ptrIndex->push_back(nSize + 1);

				m_ptrIndex->push_back(nSize + 0);
				m_ptrIndex->push_back(nSize + 3);
				m_ptrIndex->push_back(nSize + 2);

				break;
			}

			m_ptrVetexArry->push_back(ptrTempVec3Arry[nCnt*j + i]);
			m_ptrVetexArry->push_back(ptrTempVec3Arry[nCnt*j + i + nCnt]);
			m_ptrVetexArry->push_back(ptrTempVec3Arry[nCnt*j + i + nCnt + 1]);
			m_ptrVetexArry->push_back(ptrTempVec3Arry[nCnt*j + i + 1]);

			osg::Vec3d normal = (ptrTempVec3Arry[nCnt*j + i + 1] - ptrTempVec3Arry[nCnt*j + i]) ^ (ptrTempVec3Arry[nCnt*j + i + nCnt] - ptrTempVec3Arry[nCnt*j + i]);
			normal.normalize();
			m_ptrNormal->push_back(normal);
			m_ptrNormal->push_back(normal);
			m_ptrNormal->push_back(normal);
			m_ptrNormal->push_back(normal);

			m_ptrIndex->push_back(nSize + 0);
			m_ptrIndex->push_back(nSize + 2);
			m_ptrIndex->push_back(nSize + 1);

			m_ptrIndex->push_back(nSize + 0);
			m_ptrIndex->push_back(nSize + 3);
			m_ptrIndex->push_back(nSize + 2);
		}
	}
}

//特殊处理最后一圈
void SquareTwoLinkPipePoint::TransformLastCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& tempVec3Arry)
{
	osg::Vec3d pos = m_vCenterPoints[m_vCenterPoints.size() - 1];
	osg::Vec3d YAxis = m_vecDir[1];
	osg::Vec3d up = osg::Vec3d(0.0, 0.0, 1.0);

	double dbAngle = acos(up*YAxis);

	//这种情况下这根管子和Z轴平行,把P1作为辅助向量
	if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON || fabs(dbAngle - 3.141592) <= 0.0001)
		up = pos;

	osg::Vec3d ZAxis = up^YAxis;
	osg::Vec3d XAxis = ZAxis^YAxis;

	//PipeUntility::createLine(osg::Vec3(0.0, 0.0, 0.0), pos + m_centerPostion);

	XAxis.normalize();
	ZAxis.normalize();

	osg::Matrixd mat;
	mat.set(XAxis.x(), XAxis.y(), XAxis.z(), 0.0,
		YAxis.x(), YAxis.y(), YAxis.z(), 0.0,
		ZAxis.x(), ZAxis.y(), ZAxis.z(), 0.0,
		pos.x() + m_centerPostion.x(), pos.y() + m_centerPostion.y(), pos.z() + m_centerPostion.z(), 1.0);

	//PipeUntility::createAxis(XAxis, YAxis, ZAxis, pos + m_centerPostion, 5);

	//变换
	for (int j = 0; j < ptrBaseVec3Arry.size(); ++j)
	{
		tempVec3Arry.push_back(ptrBaseVec3Arry[j] * mat);
	}
}

void SquareTwoLinkPipePoint::TransformAllVetex(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& tempVec3Arry)
{
	//首先减去自己的中心点
	for (int i = 0;i<m_vCenterPoints.size();i++)
	{
		m_vCenterPoints[i] = m_vCenterPoints[i] - m_centerPostion;
	}

	//变换第一圈
	TransformFirstCircle(ptrBaseVec3Arry, tempVec3Arry);

	//变换中间插值圈
	for (int i = 1; i < m_vCenterPoints.size() - 1; ++i)
	{
		osg::Vec3d 	pos = m_vCenterPoints[i];
		osg::Vec3d	p1 = m_vCenterPoints[i];
		osg::Vec3d	p2 = m_vCenterPoints[i + 1];

		//PipeUntility::createLine(osg::Vec3(0.0, 0.0, 0.0), p1 + m_centerPostion);

		osg::Vec3d up(0.0, 0.0, 1.0);

		osg::Vec3d YAxis = p2 - p1;
		double dbLenght = YAxis.normalize();

		p1.normalize();
		p2.normalize();

		double dbAngle = acos(up*p2);

		//这种情况下这根管子和Z轴平行,把P1作为辅助向量
		if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON || fabs(dbAngle - 3.141592) <= 0.0001)
			up = p1;

		osg::Vec3d ZAxis  = up^YAxis;
		osg::Vec3d XAxis = ZAxis^YAxis;

		XAxis.normalize();
		ZAxis.normalize();
		
		osg::Matrixd mat;
		mat.set(XAxis.x(), XAxis.y(), XAxis.z(), 0.0,
			YAxis.x(), YAxis.y(), YAxis.z(), 0.0,
			ZAxis.x(), ZAxis.y(), ZAxis.z(), 0.0,
			pos.x() + m_centerPostion.x() , pos.y() + m_centerPostion.y(), pos.z() + m_centerPostion.z(), 1.0);

		//PipeUntility::createAxis(XAxis, YAxis, ZAxis, pos+m_centerPostion, dbLenght);

		//变换
		for (int j = 0; j < ptrBaseVec3Arry.size(); ++j)
		{
			tempVec3Arry.push_back(ptrBaseVec3Arry[j] * mat);
		}
	}

	//变换最后一圈圈
	TransformLastCircle(ptrBaseVec3Arry, tempVec3Arry);
}

//特殊处理第一圈
void SquareTwoLinkPipePoint::TransformFirstCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& tempVec3Arry)
{
	osg::Vec3d pos = m_vCenterPoints[0];
	osg::Vec3d YAxis = -m_vecDir[0];

	osg::Vec3d up = osg::Vec3d(0.0,0.0,1.0);

	double dbAngle = acos(up*YAxis);

	//这种情况下这根管子和Z轴平行,把P1作为辅助向量
	if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON || fabs(dbAngle - 3.141592) <= 0.0001)
		up = pos;

	osg::Vec3d ZAxis = up^YAxis;
	osg::Vec3d XAxis = ZAxis^YAxis;

	//PipeUntility::createLine(osg::Vec3(0.0, 0.0, 0.0), pos + m_centerPostion);

	XAxis.normalize();
	ZAxis.normalize();

	osg::Matrixd mat;
	mat.set(XAxis.x(), XAxis.y(), XAxis.z(), 0.0,
		YAxis.x(), YAxis.y(), YAxis.z(), 0.0,
		ZAxis.x(), ZAxis.y(), ZAxis.z(), 0.0,
		pos.x() + m_centerPostion.x(), pos.y() + m_centerPostion.y(), pos.z() + m_centerPostion.z(), 1.0);

	//PipeUntility::createAxis(XAxis, YAxis, ZAxis, pos + m_centerPostion, 5);

	//变换
	for (int j = 0; j < ptrBaseVec3Arry.size(); ++j)
	{
		tempVec3Arry.push_back(ptrBaseVec3Arry[j] * mat);
	}
}

SquareTwoLinkPipePoint::~SquareTwoLinkPipePoint()
{

}

GLOBE_ENDNS