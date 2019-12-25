#include "Cylinder.h"
#include "CirclePipeLine.h"
#include <utility.h>

GLOBE_NS

Cylinder::Cylinder(osg::Vec3d dir, osg::Vec3d postion, double radius, std::string strPointID, std::string strTypeName)
					:PipePoint(postion, strPointID,strTypeName)
{
	m_dir = dir;

	m_radius = radius / 2000.0;
	m_nPointCnt = 36;

	//�Ӵ�
	m_dbBold = 1.3;
	//��ͷ�ӳ�
	m_dbExtend = 1/2.5;
	//��Ȧ�Ӵ�
	m_dbOuterBold = 1.06;

	//����ܾ��Ƚϴ����Ӧ��һЩ��ϸһЩ
	if (m_radius > 0.8)
	{
		m_dbBold = 1.2;
		m_dbExtend = 1 / 2.8;
	}
	else if (m_radius < 0.1)
	{
		//������Ӻ�ϸ��������΢����һЩ
		m_dbExtend = 1 / 2.0;
	}
}

void Cylinder::setExtend(double dbExtend)
{
	m_dbExtend = dbExtend;
}

void Cylinder::TranslateSideVetex(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& vecTempVetex)
{
	osg::Vec3d pos = m_centerPostion;
	pos.normalize();
	osg::Vec3d YAxis = m_dir;
	m_dir.normalize();

	double dbAngle = acos(pos*m_dir);

	//���������Y���Z����غ�,��p1����΢��X�᷽����һ�㣬ֻҪ�����ǲ�˲�Ϊ�㼴��
	if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON)
	{
		pos.x() += 0.1;
		pos.normalize();
	}

	osg::Vec3d XAxis = pos^YAxis;
	osg::Vec3d ZAxis = YAxis^XAxis;

	XAxis.normalize();
	ZAxis.normalize();

	osg::Matrixd mat;
	mat.set(XAxis.x()*m_dbOuterBold, XAxis.y()*m_dbOuterBold, XAxis.z()*m_dbOuterBold, 0.0,
		YAxis.x(), YAxis.y(), YAxis.z(), 0.0,
		ZAxis.x()*m_dbOuterBold, ZAxis.y()*m_dbOuterBold, ZAxis.z()*m_dbOuterBold, 0.0,
		m_centerPostion.x(), m_centerPostion.y(), m_centerPostion.z(), 1.0);

	//�任
	for (int j = 0; j < ptrBaseVec3Arry.size(); ++j)
	{
		vecTempVetex.push_back(ptrBaseVec3Arry[j] * mat);
	}
}

void Cylinder::CloseTwoSideFace()
{
	//�ȴ�һ�¸���
	int nIndexCnt = m_ptrVetexArry->size();

	osg::Vec3d normal0 = ((*m_ptrVetexArry)[0] - (*m_ptrVetexArry)[1]) ^ ((*m_ptrVetexArry)[2] - (*m_ptrVetexArry)[1]);
	osg::Vec3d normal1 = ((*m_ptrVetexArry)[m_nPointCnt + 2] - (*m_ptrVetexArry)[m_nPointCnt + 1]) ^ ((*m_ptrVetexArry)[m_nPointCnt + 0] - (*m_ptrVetexArry)[m_nPointCnt + 1]);
	normal0.normalize();
	normal1.normalize();

	for (int i = 0; i < nIndexCnt; ++i)
	{
		m_ptrVetexArry->push_back((*m_ptrVetexArry)[i]);

		if (i > (nIndexCnt / 2 - 1))
			m_ptrNormal->push_back(normal1);
		else
			m_ptrNormal->push_back(normal0);
	}

	std::vector<unsigned short> vecIndex;
	//������������
	for (int k = 0; k < 2; ++k)
	{
		bool bClockwise = true;
		//������Ҫ��ʱ��
		if (k == 1)
			bClockwise = false;

		for (int i = 0; i < m_nPointCnt - 1; ++i)
		{
			if (i == m_nPointCnt - 2)
			{
				if (bClockwise)
				{
					//˳ʱ��
					vecIndex.push_back(m_nPointCnt*k + 0);
					vecIndex.push_back(m_nPointCnt*k + m_nPointCnt - 1);
					vecIndex.push_back(m_nPointCnt*k + m_nPointCnt - 2);
				}
				else
				{
					//��ʱ��
					vecIndex.push_back(m_nPointCnt*k + 0);
					vecIndex.push_back(m_nPointCnt*k + m_nPointCnt - 2);
					vecIndex.push_back(m_nPointCnt*k + m_nPointCnt - 1);
				}
				break;
			}

			if (bClockwise)
			{
				//˳ʱ��
				vecIndex.push_back(m_nPointCnt*k + 0);
				vecIndex.push_back(m_nPointCnt*k + i + 2);
				vecIndex.push_back(m_nPointCnt*k + i + 1);
			}
			else
			{
				//��ʱ��
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

void Cylinder::CalculateIndex()
{
	//Բ������
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
void Cylinder::CalculateNormal()
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

bool Cylinder::build()
{	
	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	m_centerPostion -= m_originePoint;

	std::vector<osg::Vec3d> ptrBaseVec3Arry;

	//����Ȧ����XZƽ��һ��Բ
	double dbDeltaAngle = 2 * PI / m_nPointCnt;
	for (int i = 0; i < m_nPointCnt; i++)
	{
		double x = m_radius*cos(dbDeltaAngle*i);
		double z = m_radius*sin(dbDeltaAngle*i);

		ptrBaseVec3Arry.push_back(osg::Vec3d(x, 0.0, z));
	}

	std::vector<osg::Vec3d> vecTempVetex;
	TranslateSideVetex(ptrBaseVec3Arry, vecTempVetex);

	//βȦ
	for (int i = 0; i < m_nPointCnt; ++i)
	{
		osg::Vec3d point = vecTempVetex[i] - m_dir*m_radius * m_dbExtend;
		m_ptrVetexArry->push_back(point);
	}
	//��Ȧ
	for (int i = 0; i < m_nPointCnt; ++i)
	{
		osg::Vec3d point = vecTempVetex[i] + m_dir*m_radius * m_dbExtend;
		m_ptrVetexArry->push_back(point);
	}

	//��������
	CalculateIndex();
	//���㷨��
	CalculateNormal();
	//�����
	CloseTwoSideFace();

	return true;
}

Cylinder::~Cylinder()
{

}

GLOBE_ENDNS