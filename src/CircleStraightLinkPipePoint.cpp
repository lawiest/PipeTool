#include "CircleStraightLinkPipePoint.h"
#include "PipeUntility.h"
#include "CirclePipeLine.h"
#include <utility.h>
#include "Cylinder.h"

GLOBE_NS

CircleStraightLinkPipePoint::CircleStraightLinkPipePoint(osg::Vec3d dir, osg::Vec3d postion, double diameter, std::string strPointID, std::string strTypeName)
											:PipePoint(postion, strPointID,strTypeName)
{
	m_dir = dir;
	m_radius = diameter / 2000.0;
	m_nPointCnt = 36;

	//加粗
	m_dbBold = 1.3;
	//两头延长
	m_dbExtend = 2;
	//外圈两头延长
	m_dbOuterExtend = 0.3;
	//外圈加粗
	m_dbOuterBold = 1.06;

	//如果管径比较粗则对应短一些和细一些
	if (m_radius > 0.8)
	{
		m_dbBold = 1.2;
		m_dbExtend = 1.8;
		m_dbOuterExtend = 0.4;
	}
	else if (m_radius < 0.1)
	{
		//如果管子很细，两边稍微拉长一些
		m_dbExtend = 2.3;
		m_dbOuterExtend = 0.2;
	}
}

void CircleStraightLinkPipePoint::setBold(double dbBold)
{
	m_dbBold = dbBold;
}

void CircleStraightLinkPipePoint::setExtend(double dbExtend)
{
	m_dbExtend = dbExtend;
}

void CircleStraightLinkPipePoint::setOuterExtend(double dbOuterExtend)
{
	m_dbOuterExtend = dbOuterExtend;
}

bool CircleStraightLinkPipePoint::build()
{	
	if (fabs(m_radius) <= DBL_EPSILON)
	{
		//m_dbPipeSize = 0.05*1.2;
		return false;
	}

	m_radius *= m_dbBold;

	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	//由于这里是建一个直通
	osg::Vec3d endPoint = m_centerPostion + m_dir * m_radius * m_dbExtend;
	CirclePipeLinePtr ptrCircle = new CirclePipeLine(m_centerPostion, endPoint, m_strPointID, m_radius * 2000,m_strTypeName);
	ptrCircle->setMinus(false);
	ptrCircle->setOriginePoint(m_originePoint);

	bool bIsOk = ptrCircle->Build();

	m_ptrVetexArry = ptrCircle->getVetexArray();
	m_ptrNormal = ptrCircle->getNormalArray();
	m_ptrIndex = ptrCircle->getIndexArray();

	CylinderPtr ptrCylinder = new Cylinder(m_dir, endPoint, m_radius * 2000,m_strPointID,m_strTypeName);
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

	return bIsOk;
}

void CircleStraightLinkPipePoint::closeFirstSide()
{
	if (m_ptrVetexArry == NULL)
		return;

	//先存一下个数
	int nIndexCnt = m_ptrVetexArry->size();

	osg::Vec3d normal0 = ((*m_ptrVetexArry)[0] - (*m_ptrVetexArry)[1]) ^ ((*m_ptrVetexArry)[2] - (*m_ptrVetexArry)[1]);
	normal0.normalize();

	//把第一圈连起来封闭，顶点和法线
	for (int i = 0; i < m_nPointCnt; ++i)
	{
		m_ptrVetexArry->push_back((*m_ptrVetexArry)[i]);
		m_ptrNormal->push_back(normal0);
	}

	std::vector<unsigned short> vecIndex;
	//两个侧面索引
	for (int k = 0; k < 1; ++k)
	{
		bool bClockwise = true;

		for (int i = 0; i < m_nPointCnt - 1; ++i)
		{
			if (i == m_nPointCnt - 2)
			{
				if (bClockwise)
				{
					//顺时针
					vecIndex.push_back(m_nPointCnt*k + 0);
					vecIndex.push_back(m_nPointCnt*k + m_nPointCnt - 1);
					vecIndex.push_back(m_nPointCnt*k + m_nPointCnt - 2);
				}
				else
				{
					//逆时针
					vecIndex.push_back(m_nPointCnt*k + 0);
					vecIndex.push_back(m_nPointCnt*k + m_nPointCnt - 2);
					vecIndex.push_back(m_nPointCnt*k + m_nPointCnt - 1);
				}
				break;
			}

			if (bClockwise)
			{
				//顺时针
				vecIndex.push_back(m_nPointCnt*k + 0);
				vecIndex.push_back(m_nPointCnt*k + i + 2);
				vecIndex.push_back(m_nPointCnt*k + i + 1);
			}
			else
			{
				//逆时针
				vecIndex.push_back(m_nPointCnt*k + 0);
				vecIndex.push_back(m_nPointCnt*k + i + 1);
				vecIndex.push_back(m_nPointCnt*k + i + 2);
			}
		}
	}

	for (int j = 0; j < vecIndex.size(); j++)
	{
		m_ptrIndex->push_back(vecIndex[j] + nIndexCnt);
	}
}

CircleStraightLinkPipePoint::~CircleStraightLinkPipePoint()
{

}

GLOBE_ENDNS