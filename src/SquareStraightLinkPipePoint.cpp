#include "SquareStraightLinkPipePoint.h"
#include "PipeUntility.h"
#include "SquarePipeLine.h"
#include <utility.h>
#include "Cuboid.h"

GLOBE_NS

SquareStraightLinkPipePoint::SquareStraightLinkPipePoint(osg::Vec3d dir, osg::Vec3d postion, double dbWidth, double dbHeight, std::string strPointID, std::string strTypeName)
											:PipePoint(postion, strPointID,strTypeName)
{
	m_dir = dir;

	//管径宽
	m_dbWidth = dbWidth / 1000.0;
	//管径高
	m_dbHeight = dbHeight / 1000.0;

	//加粗
	m_dbBold = 1.3;
	//两头延长
	m_dbExtend = 2;
	//外圈两头延长
	m_dbOuterExtend = 0.3;
	//外圈加粗
	m_dbOuterBold = 1.06;

	//如果管径比较粗则对应短一些和细一些
	if (m_dbWidth > 0.8)
	{
		m_dbBold = 1.2;
		m_dbExtend = 1.8;
		m_dbOuterExtend = 0.4;
	}
	else if (m_dbWidth < 0.1)
	{
		//如果管子很细，两边稍微拉长一些
		m_dbExtend = 2.3;
		m_dbOuterExtend = 0.2;
	}
}

void SquareStraightLinkPipePoint::setBold(double dbBold)
{
	m_dbBold = dbBold;
}

void SquareStraightLinkPipePoint::setExtend(double dbExtend)
{
	m_dbExtend = dbExtend;
}

void SquareStraightLinkPipePoint::setOuterExtend(double dbOuterExtend)
{
	m_dbOuterExtend = dbOuterExtend;
}

bool SquareStraightLinkPipePoint::build()
{	
	if (fabs(m_dbWidth) <= DBL_EPSILON)
		return false;

	m_dbWidth *= m_dbBold;
	m_dbHeight *= m_dbBold;

	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	double dbAvgPipeSize = (m_dbWidth + m_dbHeight)*0.8 / 2.0;

	//由于这里是建一个直通
	osg::Vec3d endPoint = m_centerPostion + m_dir * dbAvgPipeSize * m_dbExtend;
	SquarePipeLinePtr ptrCircle = new SquarePipeLine(m_centerPostion, endPoint, m_strPointID, m_dbWidth * 1000, m_dbHeight * 1000,m_strTypeName);
	ptrCircle->setOriginePoint(m_originePoint);
	ptrCircle->setMinus(false);
	bool bIsOk = ptrCircle->Build();

	m_ptrVetexArry = ptrCircle->getVetexArray();
	m_ptrNormal = ptrCircle->getNormalArray();
	m_ptrIndex = ptrCircle->getIndexArray();

	CuboidPtr ptrCuboid = new Cuboid(m_dir, endPoint, m_dbWidth * 1000, m_dbHeight * 1000,m_strPointID, m_strTypeName);
	//ptrCuboid->setExtend(m_dbOuterExtend);
	ptrCuboid->setOriginPoint(m_originePoint);
	ptrCuboid->build();

	osg::Vec3dArray* ptrVetexArray = ptrCuboid->getVetexArray();
	osg::Vec3dArray* ptrNormalArray = ptrCuboid->getNormalArray();
	osg::DrawElementsUShort* ptrIndexArray = ptrCuboid->getIndexArray();

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

void SquareStraightLinkPipePoint::closeFirstSide()
{
	size_t nCnt = m_ptrVetexArry->size();
	m_ptrVetexArry->push_back((*m_ptrVetexArry)[0 * 4]);
	m_ptrVetexArry->push_back((*m_ptrVetexArry)[1 * 4]);
	m_ptrVetexArry->push_back((*m_ptrVetexArry)[2 * 4]);
	m_ptrVetexArry->push_back((*m_ptrVetexArry)[3 * 4]);

	osg::Vec3d normal = ((*m_ptrVetexArry)[0 * 4] - (*m_ptrVetexArry)[1 * 4]) ^ ((*m_ptrVetexArry)[2 * 4] - (*m_ptrVetexArry)[1 * 4]) ;
	normal.normalize();
	m_ptrNormal->push_back(normal);
	m_ptrNormal->push_back(normal);
	m_ptrNormal->push_back(normal);
	m_ptrNormal->push_back(normal);

	m_ptrIndex->push_back(0 + nCnt);
	m_ptrIndex->push_back(2 + nCnt);
	m_ptrIndex->push_back(1 + nCnt);

	m_ptrIndex->push_back(0 + nCnt);
	m_ptrIndex->push_back(3 + nCnt);
	m_ptrIndex->push_back(2 + nCnt);

}


SquareStraightLinkPipePoint::~SquareStraightLinkPipePoint()
{

}

GLOBE_ENDNS