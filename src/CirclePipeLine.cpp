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

	//����ܾ�Ϊ0���˴�Ϊ�˵��Ը�������ֵ
	if (dbSize == 0.0)
	{
		std::cout << "���棡���߱��Ϊ:" + m_strPipeName + "�Ĺܾ�Ϊ��! ��ģֹͣ!" << std::endl;
		return false;
		//dbSize = 0.05;
	}

	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	std::vector<osg::Vec3d> ptrBaseVec3Arry;

	//����Ȧ����XZƽ��һ��Բ
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
	//��������¹�����ͷ�Ͳ���
	if (dbLenght / 2.0 <= m_radius)
		m_bIsMinus = false;

	p1.normalize();
	p2.normalize();

	double dbAngle = acos(up*p2);

	//���������Y���Z��ƽ�У�����ѡ��p1Ϊ��������
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

	//�任
	for (int i = 0; i < ptrBaseVec3Arry.size(); ++i)
	{
		ptrBaseVec3Arry[i] = ptrBaseVec3Arry[i] * mat;
	}

	//��Ȧ
	for (int i = 0; i < ptrBaseVec3Arry.size(); ++i)
	{
		//������ͷҪ��΢��һ�㣬��Ȼ����ͷʱ���Ƴ���
		osg::Vec3 lenght = YAxis*dbLenght / 2;
		double minus = (m_radius)/**1.2*/;

		if (m_bIsMinus)
			lenght -= YAxis*minus;

		m_ptrVetexArry->push_back(ptrBaseVec3Arry[i] - lenght);
	}

	//βȦ,������ͷҪ��΢��һ�㣬��Ȼ����ͷʱ���Ƴ���
	for (int i = 0; i < ptrBaseVec3Arry.size(); ++i)
	{
		//������ͷҪ��΢��һ�㣬��Ȼ����ͷʱ���Ƴ���
		osg::Vec3 lenght = YAxis*dbLenght / 2;
		double minus = (m_radius) /**1.2*/;

		if (m_bIsMinus)
			lenght -= YAxis*minus;

		m_ptrVetexArry->push_back(ptrBaseVec3Arry[i] + lenght);
	}

	//ƫ�ƣ����Ӧ����obj�д������ģ����ڲ�֪��զ�棬�ȷ���
	for (int i = 0; i < m_ptrVetexArry->size(); ++i)
	{
		(*m_ptrVetexArry)[i] += transform;
	}

	CalculateIndex();
	CalculateNormal();

	return true;
}

//��������
void CirclePipeLine::CalculateIndex()
{
	for (int i = 0; i < m_nPointCnt; ++i)
	{
		//˳ʱ��
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

//���㷨��,��õ���ÿ���㹲�������ƽ��������
void CirclePipeLine::CalculateNormal()
{
	if (m_ptrNormal == NULL)
		m_ptrNormal = new osg::Vec3dArray();

	if (m_ptrVetexArry->size() <= 0)
		return;

	//��Ȧÿ���㷨��
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

		//��һ���淨����
		osg::Vec3d normal1 = (vec2 - vec1) ^ (vec0 - vec1);
		normal1.normalize();
		//�ڶ����淨����
		osg::Vec3d normal2 = (vec3 - vec1) ^ (vec2 - vec1);
		normal2.normalize();
		//��һ���淨����
		osg::Vec3d normal3 = (vec4 - vec1) ^ (vec3 - vec1);
		normal3.normalize();

		osg::Vec3d normal = (normal1 + normal2 + normal3) / 3.0;
		normal.normalize();
		m_ptrNormal->push_back(normal);
	}

	//��βȦÿ���㷨��
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

		//��һ���淨����
		osg::Vec3d normal1 = (vec0 - vec1) ^ (vec2 - vec1);
		normal1.normalize();
		//�ڶ����淨����
		osg::Vec3d normal2 = (vec2 - vec1) ^ (vec3 - vec1);
		normal2.normalize();
		//��һ���淨����
		osg::Vec3d normal3 = (vec3 - vec1) ^ (vec4 - vec1);
		normal3.normalize();

		osg::Vec3d normal = (normal1 + normal2 + normal3) / 3.0;
		normal.normalize();
		m_ptrNormal->push_back(normal);
	}
}


GLOBE_ENDNS