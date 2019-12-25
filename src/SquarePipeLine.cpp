#include "SquarePipeLine.h"
#include <utility.h>
#include <geodatabase.h>

using namespace KERNEL_NAME;
using namespace UTILITY_NAME;

GLOBE_NS

SquarePipeLine::SquarePipeLine(osg::Vec3d p1, osg::Vec3d p2, std::string strPipeID, double dbWidth, double dbHeight, std::string strTypeName)
								:PipeLine(p1, p2, strPipeID,strTypeName)
{
	m_dbWidth = dbWidth;
	m_dbHeight = dbHeight;
}

SquarePipeLine::~SquarePipeLine()
{

}

bool SquarePipeLine::Build()
{
	//算成米
	m_dbWidth /= 1000;
	m_dbHeight /= 1000;

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

	osg::Vec3d p1 = m_p1;
	osg::Vec3d p2 = m_p2;

	osg::Vec3d center = (p1 + p2) / 2;

	m_centerPostion = center - m_originePoint;

	osg::Matrixd matTrans = osg::Matrixd::translate(m_centerPostion);

	osg::Vec3d YAxis = p2 - p1;
	double dbLenght = YAxis.normalize();

	//这种情况下管子两头就不缩
	if (dbLenght / 2.0 <= (m_dbWidth + m_dbHeight) / 2.0)
		m_bIsMinus = false;

	osg::Vec3d up(0.0, 0.0, 1.0);

	p1.normalize();
	p2.normalize();

	double dbAngle = acos(up*p2);

	//这种情况下这根管子和Z轴平行,把P1作为辅助向量
	if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON || fabs(dbAngle - 3.141592) <= 0.0001)
		up = p1;

	osg::Vec3d ZAxis = up^YAxis;
	osg::Vec3d XAxis = ZAxis^YAxis;

	XAxis.normalize();
	ZAxis.normalize();

	osg::Matrixd mat;
	mat.set(XAxis.x(), XAxis.y(), XAxis.z(), 0.0,
		YAxis.x(), YAxis.y(), YAxis.z(), 0.0,
		ZAxis.x(), ZAxis.y(), ZAxis.z(), 0.0,
		0.0, 0.0, 0.0, 1.0);

	//PipeUntility::createAxis(XAxis, YAxis, ZAxis, m_p1 - m_originePoint, 1);

	//PipeUntility::createLine(osg::Vec3d(0.0, 0.0, 0.0), m_p1 - m_originePoint);

	std::vector<osg::Vec3d> vecTempVec3Arry;

	//变换
	for (int i = 0; i < ptrBaseVec3Arry.size(); ++i)
	{
		ptrBaseVec3Arry[i] = ptrBaseVec3Arry[i] * mat;
	}

	//首圈
	for (int i = 0; i < ptrBaseVec3Arry.size(); ++i)
	{
		//管子两头要稍微缩一点，不然建管头时会破出来
		osg::Vec3 lenght = YAxis*dbLenght / 2;
		double minus = (m_dbWidth + m_dbHeight) / 2.0;

		if (m_bIsMinus)
			lenght -= YAxis*minus*0.8;

		vecTempVec3Arry.push_back(ptrBaseVec3Arry[i] - lenght);
	}

	//尾圈,管子两头要稍微缩一点，不然建管头时会破出来
	for (int i = 0; i < ptrBaseVec3Arry.size(); ++i)
	{
		//管子两头要稍微缩一点，不然建管头时会破出来
		osg::Vec3 lenght = YAxis*dbLenght / 2;
		double minus = (m_dbWidth + m_dbHeight) / 2.0;

		if (m_bIsMinus)
			lenght -= YAxis*minus*0.8;

		vecTempVec3Arry.push_back(ptrBaseVec3Arry[i] + lenght);
	}

	//偏移，这个应该在obj中存个矩阵的，现在不知道咋存，先放这
	for (int i = 0; i < vecTempVec3Arry.size(); ++i)
	{
		vecTempVec3Arry[i] += m_centerPostion;
	}

	Calculate(vecTempVec3Arry);

	return true;
}

//计算
void SquarePipeLine::Calculate(const std::vector<osg::Vec3d>& vecTempVec3Arry)
{
	int nCnt = 4;
	for (int i = 0; i < nCnt; ++i)
	{
		int nSize = m_ptrVetexArry->size();
		if (i == nCnt - 1)
		{
			m_ptrVetexArry->push_back(vecTempVec3Arry[i]);
			m_ptrVetexArry->push_back(vecTempVec3Arry[nCnt + i]);
			m_ptrVetexArry->push_back(vecTempVec3Arry[nCnt]);
			m_ptrVetexArry->push_back(vecTempVec3Arry[0]);

			osg::Vec3d normal = (vecTempVec3Arry[0] - vecTempVec3Arry[i]) ^ (vecTempVec3Arry[nCnt + i] - vecTempVec3Arry[i]);
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

		m_ptrVetexArry->push_back(vecTempVec3Arry[i]);
		m_ptrVetexArry->push_back(vecTempVec3Arry[nCnt + i]);
		m_ptrVetexArry->push_back(vecTempVec3Arry[nCnt + i + 1]);
		m_ptrVetexArry->push_back(vecTempVec3Arry[i+1]);

		osg::Vec3d normal = (vecTempVec3Arry[i + 1] - vecTempVec3Arry[i]) ^ (vecTempVec3Arry[nCnt + i] - vecTempVec3Arry[i]);
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

GLOBE_ENDNS