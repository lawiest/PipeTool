#include "CircleTwoLinkPipePoint.h"
#include "PipeUntility.h"
#include "CirclePipeLine.h"
#include <utility.h>
#include "Cylinder.h"

GLOBE_NS

CircleTwoLinkPipePoint::CircleTwoLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double diameter, std::string strPointID, std::string strTypeName)
									:PipePoint(postion, strPointID,strTypeName)
{
	//两个方向向量
	m_vecDir = vecDir;
	//管径
	m_radius = diameter / 2000.0;
	//一圈点个数
	m_nPointCnt = 36;
	m_originePoint = osg::Vec3d(0.0,0.0,0.0);

	m_ptrVetexArry = NULL;
	m_ptrNormal = NULL;
	m_ptrIndex = NULL;

	//加粗
	m_dbBold = 1.3;
	//两头延长
	m_dbExtend = 1.8;
	m_dbOuterExtend = 0.3;
	//外圈加粗
	m_dbOuterBold = 1.02;

	//如果管径比较粗则对应短一些和细一些
	if (m_radius > 0.8)
	{
		m_dbBold = 1.2;
		m_dbExtend = 1.6;
		//m_dbOuterExtend = 1 / 2.8;

	}
	else if (m_radius < 0.1)
	{
		//如果管子很细，两边稍微拉长一些
		m_dbExtend = 1.8;
		//m_dbOuterExtend = 1 / 2.0;
	}
}

void CircleTwoLinkPipePoint::setOuterExtend(double dbOuterExtend)
{
	m_dbOuterExtend = dbOuterExtend;
}


void CircleTwoLinkPipePoint::CalcuSectionCenterPoints(const osg::Vec3d& start, const osg::Vec3d& center, const osg::Vec3d& end)
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

bool CircleTwoLinkPipePoint::build()
{	
	if (fabs(m_radius) <= DBL_EPSILON)
	{
		//m_dbPipeSize = 0.05*1.2;
		return false;
	}

	//加粗
	m_radius *= m_dbBold;

	//偏移
	m_centerPostion -= m_originePoint;
	//首点
	osg::Vec3d startPoint = m_centerPostion + m_vecDir[0] * m_radius * m_dbExtend;
	//尾点
	osg::Vec3d endPoint = m_centerPostion + m_vecDir[1] * m_radius * m_dbExtend;
	//求得所有中心点
	CalcuSectionCenterPoints(startPoint, m_centerPostion, endPoint);

	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	std::vector<osg::Vec3d> ptrBaseVec3Arry;

	//基本圈，在XZ平面一周圆
	double dbDeltaAngle = 2 * PI / m_nPointCnt;
	for (int i = 0; i < m_nPointCnt; i++)
	{
		double x = m_radius*cos(dbDeltaAngle*i);
		double z = m_radius*sin(dbDeltaAngle*i);

		ptrBaseVec3Arry.push_back(osg::Vec3d(x, 0.0, z));
	}

	//变换
	TransformAllVetex(ptrBaseVec3Arry);

	CalculateIndex();
	CalculateNormal();

	Close(ptrBaseVec3Arry);

	return true;
}

void CircleTwoLinkPipePoint::Close(const std::vector<osg::Vec3d>& ptrBaseVec3Arry)
{
	if (m_ptrFirstSideVetexArry == NULL)
		m_ptrFirstSideVetexArry = new osg::Vec3dArray();

	//首圈
	CylinderPtr ptrCylinder = new Cylinder(m_vecDir[0], m_vCenterPoints[0] + m_centerPostion + m_originePoint, m_radius * 2000, m_strPointID, m_strTypeName);
	ptrCylinder->setExtend(m_dbOuterExtend);
	ptrCylinder->setOriginPoint(m_originePoint);
	ptrCylinder->build();

	osg::Vec3dArray* ptrVetexArray = ptrCylinder->getVetexArray();
	osg::Vec3dArray* ptrNormalArray = ptrCylinder->getNormalArray();
	osg::DrawElementsUShort* ptrIndexArray = ptrCylinder->getIndexArray();

	int nIndexCnt = m_ptrVetexArry->size();
	//合并顶点和法线
	for (int i = 0; i < ptrVetexArray->size(); i++)
	{
		m_ptrVetexArry->push_back((*ptrVetexArray)[i]);
		m_ptrNormal->push_back((*ptrNormalArray)[i]);
	}

	//合并索引
	for (int i = 0; i < ptrIndexArray->size(); i++)
	{
		m_ptrIndex->push_back((*ptrIndexArray)[i] + nIndexCnt);
	}

	//尾圈
	ptrCylinder = new Cylinder(m_vecDir[1], m_vCenterPoints[m_vCenterPoints.size() - 1] + m_centerPostion + m_originePoint, m_radius * 2000, m_strPointID,m_strTypeName);
	ptrCylinder->setExtend(m_dbOuterExtend);
	ptrCylinder->setOriginPoint(m_originePoint);
	ptrCylinder->build();

	ptrVetexArray = ptrCylinder->getVetexArray();
	ptrNormalArray = ptrCylinder->getNormalArray();
	ptrIndexArray = ptrCylinder->getIndexArray();

	nIndexCnt = m_ptrVetexArry->size();
	//合并顶点和法线
	for (int i = 0; i < ptrVetexArray->size(); i++)
	{
		m_ptrVetexArry->push_back((*ptrVetexArray)[i]);
		m_ptrNormal->push_back((*ptrNormalArray)[i]);
	}

	//合并索引
	for (int i = 0; i < ptrIndexArray->size(); i++)
	{
		m_ptrIndex->push_back((*ptrIndexArray)[i] + nIndexCnt);
	}
}

void CircleTwoLinkPipePoint::CalculateNormal()
{
	if (m_ptrVetexArry->size() <= 0)
		return;

	int nCnt = m_ptrVetexArry->size() / m_nPointCnt;

	//前面n-1个圈每个点法线,实际上中间点共六个面，有时间再优化
	for (int i = 0; i < nCnt - 1; ++i)
	{
		for (int j = 0; j < m_nPointCnt; ++j)
		{
			osg::Vec3d vec0;
			osg::Vec3d vec1;
			osg::Vec3d vec2;
			osg::Vec3d vec3;
			osg::Vec3d vec4;

			if (j == 0)
			{
				vec0 = (*m_ptrVetexArry)[m_nPointCnt*i + m_nPointCnt - 1];
				vec1 = (*m_ptrVetexArry)[m_nPointCnt*i + j];
				vec2 = (*m_ptrVetexArry)[m_nPointCnt*i + j + m_nPointCnt];
				vec3 = (*m_ptrVetexArry)[m_nPointCnt*i + j + m_nPointCnt + 1];
				vec4 = (*m_ptrVetexArry)[m_nPointCnt*i + j + 1];
			}
			else if (j == m_nPointCnt - 1)
			{
				vec0 = (*m_ptrVetexArry)[m_nPointCnt*i + j - 1];
				vec1 = (*m_ptrVetexArry)[m_nPointCnt*i + j];
				vec2 = (*m_ptrVetexArry)[m_nPointCnt*i + j + m_nPointCnt];
				vec3 = (*m_ptrVetexArry)[m_nPointCnt*i + m_nPointCnt];
				vec4 = (*m_ptrVetexArry)[m_nPointCnt*i];
			}
			else
			{
				vec0 = (*m_ptrVetexArry)[m_nPointCnt*i + j - 1];
				vec1 = (*m_ptrVetexArry)[m_nPointCnt*i + j];
				vec2 = (*m_ptrVetexArry)[m_nPointCnt*i + j + m_nPointCnt];
				vec3 = (*m_ptrVetexArry)[m_nPointCnt*i + j + m_nPointCnt + 1];
				vec4 = (*m_ptrVetexArry)[m_nPointCnt*i + j + 1];
			}

			//第一个面法向量
			osg::Vec3d normal1 = (vec2 - vec1) ^ (vec0 - vec1);
			normal1.normalize();
			//第二个面法向量
			osg::Vec3d normal2 = (vec3 - vec1) ^ (vec2 - vec1);
			normal2.normalize();
			//第一个面法向量
			osg::Vec3d normal3 = (vec4 - vec1) ^ (vec3 - vec1);
			normal3.normalize();

			osg::Vec3d normal = (normal1 + normal2 + normal3) / 3.0;
			normal.normalize();
			m_ptrNormal->push_back(normal);
		}
	}

	//最后一圈每个点法线
	int i = nCnt*m_nPointCnt - m_nPointCnt;
	for (i; i < m_nPointCnt * nCnt; ++i)
	{
		osg::Vec3d vec0;
		osg::Vec3d vec1;
		osg::Vec3d vec2;
		osg::Vec3d vec3;
		osg::Vec3d vec4;

		if (i == nCnt*m_nPointCnt - m_nPointCnt)
		{
			vec0 = (*m_ptrVetexArry)[m_nPointCnt * nCnt - 1];
			vec1 = (*m_ptrVetexArry)[i];
			vec2 = (*m_ptrVetexArry)[m_nPointCnt * nCnt - m_nPointCnt - 1];
			vec3 = (*m_ptrVetexArry)[i - m_nPointCnt];
			vec4 = (*m_ptrVetexArry)[i + 1];
		}
		else if (i == m_nPointCnt * nCnt - 1)
		{
			vec0 = (*m_ptrVetexArry)[i - 1];
			vec1 = (*m_ptrVetexArry)[i];
			vec2 = (*m_ptrVetexArry)[i - m_nPointCnt - 1];
			vec3 = (*m_ptrVetexArry)[i - m_nPointCnt];
			vec4 = (*m_ptrVetexArry)[m_nPointCnt * nCnt - m_nPointCnt];
		}
		else
		{
			vec0 = (*m_ptrVetexArry)[i - 1];
			vec1 = (*m_ptrVetexArry)[i];
			vec2 = (*m_ptrVetexArry)[i - m_nPointCnt - 1];
			vec3 = (*m_ptrVetexArry)[i - m_nPointCnt];
			vec4 = (*m_ptrVetexArry)[i + 1];
		}

		//第一个面法向量
		osg::Vec3d normal1 = (vec0 - vec1) ^ (vec2 - vec1);
		normal1.normalize();
		//第二个面法向量
		osg::Vec3d normal2 = (vec2 - vec1) ^ (vec3 - vec1);
		normal2.normalize();
		//第一个面法向量
		osg::Vec3d normal3 = (vec3 - vec1) ^ (vec4 - vec1);
		normal3.normalize();

		osg::Vec3d normal = (normal1 + normal2 + normal3) / 3.0;
		normal.normalize();
		m_ptrNormal->push_back(normal);
	}
}

void CircleTwoLinkPipePoint::CalculateIndex()
{
	int nCnt = m_ptrVetexArry->size() / m_nPointCnt;

	for (int i = 0; i < nCnt - 1; ++i)
	{
		for (int j = 0; j < m_nPointCnt; ++j)
		{
			//顺时针
			if (j == m_nPointCnt - 1)
			{ 
				m_ptrIndex->push_back(j + m_nPointCnt*i);
				m_ptrIndex->push_back(m_nPointCnt + m_nPointCnt*i);
				m_ptrIndex->push_back(j + m_nPointCnt *(i + 1));

				m_ptrIndex->push_back(j + m_nPointCnt*i);
				m_ptrIndex->push_back(m_nPointCnt*i);
				m_ptrIndex->push_back(m_nPointCnt + m_nPointCnt*i);
				break;
			}

			m_ptrIndex->push_back(j + m_nPointCnt*i);
			m_ptrIndex->push_back(j + m_nPointCnt*i + m_nPointCnt + 1);
			m_ptrIndex->push_back(j + m_nPointCnt*i + m_nPointCnt);

			m_ptrIndex->push_back(j + m_nPointCnt*i);
			m_ptrIndex->push_back(j + m_nPointCnt*i + 1);
			m_ptrIndex->push_back(j + m_nPointCnt*i + m_nPointCnt + 1);
		}
	}
}

//特殊处理最后一圈
void CircleTwoLinkPipePoint::TransformLastCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry)
{
	osg::Vec3d pos = m_vCenterPoints[m_vCenterPoints.size()-1];
	osg::Vec3d YAxis = m_vecDir[1];

	osg::Vec3d tempDir = m_vCenterPoints[m_vCenterPoints.size() - 2]-m_vCenterPoints[m_vCenterPoints.size() - 1]  ;
	tempDir.normalize();

	osg::Vec3d up(0.0, 0.0, 1.0);
	double dbAngle = acos(up*YAxis);

	//这种情况下Y轴和Z轴平行，重新选择tempDir为辅助向量
	if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON)
		up = tempDir;

	osg::Vec3d XAxis = up^YAxis;
	osg::Vec3d ZAxis = YAxis^XAxis;

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
		m_ptrVetexArry->push_back(ptrBaseVec3Arry[j] * mat);
	}
}

//特殊处理第一圈
void CircleTwoLinkPipePoint::TransformFirstCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry)
{
	osg::Vec3d pos = m_vCenterPoints[0];
	osg::Vec3d YAxis = -m_vecDir[0];

	osg::Vec3d tempDir= m_vCenterPoints[1] - m_vCenterPoints[0];
	tempDir.normalize();

	osg::Vec3d up(0.0,0.0,1.0);
	double dbAngle = acos(up*YAxis);

	//这种情况下Y轴和Z轴平行，重新选择p1为辅助向量
	if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON)
		up = tempDir;

	osg::Vec3d XAxis = up^YAxis;
	osg::Vec3d ZAxis = YAxis^XAxis;

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
		m_ptrVetexArry->push_back(ptrBaseVec3Arry[j] * mat);
	}
}

void CircleTwoLinkPipePoint::TransformAllVetex(const std::vector<osg::Vec3d>& ptrBaseVec3Arry)
{
	//首先减去自己的中心点
	for (int i = 0;i<m_vCenterPoints.size();i++)
	{
		m_vCenterPoints[i] = m_vCenterPoints[i] - m_centerPostion;
	}

	//变换第一圈
	TransformFirstCircle(ptrBaseVec3Arry);

	//变换中间插值圈
	for (int i = 1; i < m_vCenterPoints.size() - 1; ++i)
	{
		osg::Vec3d 	pos = m_vCenterPoints[i];
		osg::Vec3d	p1 = m_vCenterPoints[i];
		osg::Vec3d	p2 = m_vCenterPoints[i + 1];

		//PipeUntility::createLine(osg::Vec3(0.0, 0.0, 0.0), p1 + m_centerPostion);

		osg::Vec3d YAxis = p2 - p1;
		double dbLenght = YAxis.normalize();

		osg::Vec3d up(0.0, 0.0, 1.0);

		p1.normalize();
		p2.normalize();

		double dbAngle = acos(up*p2);

		//这种情况下Y轴和Z轴会重合,把p1点稍微朝X轴方向移一点，只要让他们叉乘不为零即可
		if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON)
			up = p1;

		osg::Vec3d XAxis = up^YAxis;
		osg::Vec3d ZAxis = YAxis^XAxis;

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
			m_ptrVetexArry->push_back(ptrBaseVec3Arry[j] * mat);
		}
	}

	//变换最后一圈圈
	TransformLastCircle(ptrBaseVec3Arry);
}

CircleTwoLinkPipePoint::~CircleTwoLinkPipePoint()
{

}

GLOBE_ENDNS