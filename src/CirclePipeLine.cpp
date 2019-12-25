#include "CirclePipeLine.h"
#include <utility.h>
#include <geodatabase.h>

using namespace KERNEL_NAME;
using namespace UTILITY_NAME;

GLOBE_NS

CirclePipeLine::CirclePipeLine(osg::Vec3d p1, osg::Vec3d p2, std::string strPipeID, double diameter, std::string strTypeName)
							:PipeLine(p1,p2,strPipeID,strTypeName)
{
	m_radius = diameter / 2000.0;
	m_nPointCnt = 36;
}

CirclePipeLine::CirclePipeLine()
{
	m_nPointCnt = 36;
}


CirclePipeLine::~CirclePipeLine()
{

}

bool CirclePipeLine::Build()
{
	double dbSize = m_radius;

	//如果管径为0，此处为了调试给他赋个值
	if (dbSize == 0.0)
	{
		std::cout << "警告！管线编号为:" + m_strPipeName + "的管径为零! 建模停止!" << std::endl;
		return false;
		//dbSize = 0.05;
	}

	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	std::vector<osg::Vec3d> ptrBaseVec3Arry;

	//基本圈，在XZ平面一周圆
	double dbDeltaAngle = 2 * PI / m_nPointCnt;
	for (int i = 0; i < m_nPointCnt; i++)
	{
		double x = dbSize*cos(dbDeltaAngle*i);
		double z = dbSize*sin(dbDeltaAngle*i);

		ptrBaseVec3Arry.push_back(osg::Vec3d(x, 0.0, z));
	}

	osg::Vec3d p1 = m_p1;
	osg::Vec3d p2 = m_p2;

	osg::Vec3d transform = (p1 + p2) / 2 - m_originePoint;
	osg::Matrixd matTrans = osg::Matrixd::translate(transform);

	osg::Vec3d YAxis = p2 - p1;
	double dbLenght = YAxis.normalize();

	osg::Vec3d up(0.0,0.0,1.0);
	//这种情况下管子两头就不缩
	if (dbLenght / 2.0 <= m_radius)
		m_bIsMinus = false;

	p1.normalize();
	p2.normalize();

	double dbAngle = acos(up*p2);

	//这种情况下Y轴和Z轴平行，重新选择p1为辅助向量
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
			0.0, 0.0, 0.0, 1.0);

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
		double minus = (m_radius)/**1.2*/;

		if (m_bIsMinus)
			lenght -= YAxis*minus;

		m_ptrVetexArry->push_back(ptrBaseVec3Arry[i] - lenght);
	}

	//尾圈,管子两头要稍微缩一点，不然建管头时会破出来
	for (int i = 0; i < ptrBaseVec3Arry.size(); ++i)
	{
		//管子两头要稍微缩一点，不然建管头时会破出来
		osg::Vec3 lenght = YAxis*dbLenght / 2;
		double minus = (m_radius) /**1.2*/;

		if (m_bIsMinus)
			lenght -= YAxis*minus;

		m_ptrVetexArry->push_back(ptrBaseVec3Arry[i] + lenght);
	}

	//偏移，这个应该在obj中存个矩阵的，现在不知道咋存，先放这
	for (int i = 0; i < m_ptrVetexArry->size(); ++i)
	{
		(*m_ptrVetexArry)[i] += transform;
	}

	CalculateIndex();
	CalculateNormal();

	return true;
}

//计算索引
void CirclePipeLine::CalculateIndex()
{
	for (int i = 0; i < m_nPointCnt; ++i)
	{
		//顺时针
		if (i == m_nPointCnt - 1)
		{
			m_ptrIndex->push_back(i);
			m_ptrIndex->push_back(m_nPointCnt);
			m_ptrIndex->push_back(m_nPointCnt * 2 - 1);

			m_ptrIndex->push_back(i);
			m_ptrIndex->push_back(0);
			m_ptrIndex->push_back(m_nPointCnt);
			break;
		}

		m_ptrIndex->push_back(i);
		m_ptrIndex->push_back(i + m_nPointCnt + 1);
		m_ptrIndex->push_back(i + m_nPointCnt);

		m_ptrIndex->push_back(i);
		m_ptrIndex->push_back(i + 1);
		m_ptrIndex->push_back(i + m_nPointCnt + 1);
	}
}

//计算法线,求得得是每个点共三个面的平均法向量
void CirclePipeLine::CalculateNormal()
{
	if (m_ptrNormal == NULL)
		m_ptrNormal = new osg::Vec3dArray();

	if (m_ptrVetexArry->size() <= 0)
		return;

	//首圈每个点法线
	for (int i = 0; i < m_nPointCnt; ++i)
	{
		osg::Vec3d vec0;
		osg::Vec3d vec1;
		osg::Vec3d vec2;
		osg::Vec3d vec3;
		osg::Vec3d vec4;

		if (i == 0)
		{
			vec0 = (*m_ptrVetexArry)[m_nPointCnt - 1];
			vec1 = (*m_ptrVetexArry)[i];
			vec2 = (*m_ptrVetexArry)[i + m_nPointCnt];
			vec3 = (*m_ptrVetexArry)[i + m_nPointCnt + 1];
			vec4 = (*m_ptrVetexArry)[i + 1];
		}
		else if (i == m_nPointCnt - 1)
		{
			vec0 = (*m_ptrVetexArry)[i - 1];
			vec1 = (*m_ptrVetexArry)[i];
			vec2 = (*m_ptrVetexArry)[i + m_nPointCnt];
			vec3 = (*m_ptrVetexArry)[m_nPointCnt];
			vec4 = (*m_ptrVetexArry)[0];
		}
		else
		{
			vec0 = (*m_ptrVetexArry)[i - 1];
			vec1 = (*m_ptrVetexArry)[i];
			vec2 = (*m_ptrVetexArry)[i + m_nPointCnt];
			vec3 = (*m_ptrVetexArry)[i + m_nPointCnt + 1];
			vec4 = (*m_ptrVetexArry)[i + 1];
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

	//第尾圈每个点法线
	for (int i = m_nPointCnt; i < m_nPointCnt * 2; ++i)
	{
		osg::Vec3d vec0;
		osg::Vec3d vec1;
		osg::Vec3d vec2;
		osg::Vec3d vec3;
		osg::Vec3d vec4;

		if (i == m_nPointCnt)
		{
			vec0 = (*m_ptrVetexArry)[m_nPointCnt * 2 - 1];
			vec1 = (*m_ptrVetexArry)[i];
			vec2 = (*m_ptrVetexArry)[m_nPointCnt - 1];
			vec3 = (*m_ptrVetexArry)[i - m_nPointCnt];
			vec4 = (*m_ptrVetexArry)[i + 1];
		}
		else if (i == m_nPointCnt * 2 - 1)
		{
			vec0 = (*m_ptrVetexArry)[i - 1];
			vec1 = (*m_ptrVetexArry)[i];
			vec2 = (*m_ptrVetexArry)[i - m_nPointCnt - 1];
			vec3 = (*m_ptrVetexArry)[i - m_nPointCnt];
			vec4 = (*m_ptrVetexArry)[m_nPointCnt];
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


GLOBE_ENDNS