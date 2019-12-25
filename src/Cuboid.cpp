#include "Cuboid.h"
#include <utility.h>

GLOBE_NS

Cuboid::Cuboid(osg::Vec3d dir, osg::Vec3d postion, double width, double height, std::string strPointID, std::string strTypeName)
					:PipePoint(postion, strPointID,strTypeName)
{
	m_dir = dir;

	//�ܾ���
	m_dbWidth = width / 1000.0;
	//�ܾ���
	m_dbHeight = height / 1000.0;

	//�Ӵ�
	m_dbBold = 1.06;
	//��ͷ�ӳ�
	m_dbExtend = 1 / 10.0;

	//����ܾ��Ƚϴ����Ӧ��һЩ��ϸһЩ
	if (m_dbWidth > 0.8)
	{
		m_dbBold = 1.2;
		m_dbExtend = 1 / 8.0;
	}
	else if (m_dbWidth < 0.1)
	{
		//������Ӻ�ϸ��������΢����һЩ
		m_dbExtend = 1 / 4.0;
	}
}

void Cuboid::setExtend(double dbExtend)
{
	m_dbExtend = dbExtend;
}

bool Cuboid::build()
{	
	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	m_dbWidth *= m_dbBold;
	m_dbHeight *= m_dbBold;

	//��X-Zƽ���׼�����ĸ���
	std::vector<osg::Vec3d> ptrBaseVec3Arry;
	osg::Vec3d righttop = osg::Vec3d(m_dbHeight / 2.0, 0.0, m_dbWidth / 2.0);
	osg::Vec3d rightbottom = osg::Vec3d(m_dbHeight / 2.0, 0.0, -m_dbWidth / 2.0);
	osg::Vec3d leftbottom = osg::Vec3d(-m_dbHeight / 2.0, 0.0, -m_dbWidth / 2.0);
	osg::Vec3d lefttop = osg::Vec3d(-m_dbHeight / 2.0, 0.0, m_dbWidth / 2.0);
	ptrBaseVec3Arry.push_back(righttop);
	ptrBaseVec3Arry.push_back(lefttop);
	ptrBaseVec3Arry.push_back(leftbottom);
	ptrBaseVec3Arry.push_back(rightbottom);

	m_centerPostion = m_centerPostion - m_originePoint;

	osg::Matrixd matTrans = osg::Matrixd::translate(m_centerPostion);

	osg::Vec3d YAxis = m_dir;
	double dbLenght = YAxis.normalize();

	osg::Vec3d up(0.0, 0.0, 1.0);

	double dbAngle = acos(up*YAxis);

	//���������������Ӻ�Z��ƽ��,��P1��Ϊ��������
	if (isnan(dbAngle) || fabs(dbAngle - 0.0) <= DBL_EPSILON || fabs(dbAngle - 3.141592) <= 0.0001)
	{
		up = m_centerPostion;
		up.normalize();
	}

	osg::Vec3d ZAxis = up^YAxis;
	osg::Vec3d XAxis = ZAxis^YAxis;

	XAxis.normalize();
	ZAxis.normalize();

	osg::Matrixd mat;
	mat.set(XAxis.x(), XAxis.y(), XAxis.z(), 0.0,
		YAxis.x(), YAxis.y(), YAxis.z(), 0.0,
		ZAxis.x(), ZAxis.y(), ZAxis.z(), 0.0,
		m_centerPostion.x(), m_centerPostion.y(), m_centerPostion.z(), 1.0);

	std::vector<osg::Vec3d> vecTempVec3Arry;

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
		double extend = (m_dbWidth + m_dbHeight) / 2.0;
		vecTempVec3Arry.push_back(ptrBaseVec3Arry[i] - m_dir*extend * m_dbExtend);
	}

	//βȦ,������ͷҪ��΢��һ�㣬��Ȼ����ͷʱ���Ƴ���
	for (int i = 0; i < ptrBaseVec3Arry.size(); ++i)
	{
		//������ͷҪ��΢��һ�㣬��Ȼ����ͷʱ���Ƴ���
		osg::Vec3 lenght = YAxis*dbLenght / 2;
		double extend = (m_dbWidth + m_dbHeight) / 2.0;
		vecTempVec3Arry.push_back(ptrBaseVec3Arry[i] + m_dir*extend * m_dbExtend);
	}

	//���㷨������
	Calculate(vecTempVec3Arry);
	//������
	Close(vecTempVec3Arry);

	return true;
}

//����ͷ
void Cuboid::Close(const std::vector<osg::Vec3d>& vecTempVec3Arry)
{
	size_t nSize = m_ptrVetexArry->size();
	m_ptrVetexArry->push_back(vecTempVec3Arry[0]);
	m_ptrVetexArry->push_back(vecTempVec3Arry[1]);
	m_ptrVetexArry->push_back(vecTempVec3Arry[2]);
	m_ptrVetexArry->push_back(vecTempVec3Arry[3]);

	osg::Vec3d normal = (vecTempVec3Arry[3] - vecTempVec3Arry[0]) ^ (vecTempVec3Arry[1] - vecTempVec3Arry[0]);
	normal.normalize();
	m_ptrNormal->push_back(normal);
	m_ptrNormal->push_back(normal);
	m_ptrNormal->push_back(normal);
	m_ptrNormal->push_back(normal);

	m_ptrIndex->push_back(0 + nSize);
	m_ptrIndex->push_back(3 + nSize);
	m_ptrIndex->push_back(2 + nSize);
	m_ptrIndex->push_back(0 + nSize);
	m_ptrIndex->push_back(2 + nSize);
	m_ptrIndex->push_back(1 + nSize);


	nSize = m_ptrVetexArry->size();
	m_ptrVetexArry->push_back(vecTempVec3Arry[4]);
	m_ptrVetexArry->push_back(vecTempVec3Arry[5]);
	m_ptrVetexArry->push_back(vecTempVec3Arry[6]);
	m_ptrVetexArry->push_back(vecTempVec3Arry[7]);

	normal = (vecTempVec3Arry[5] - vecTempVec3Arry[4]) ^ (vecTempVec3Arry[7] - vecTempVec3Arry[4]) ;
	normal.normalize();
	m_ptrNormal->push_back(normal);
	m_ptrNormal->push_back(normal);
	m_ptrNormal->push_back(normal);
	m_ptrNormal->push_back(normal);

	m_ptrIndex->push_back(0 + nSize);
	m_ptrIndex->push_back(2 + nSize);
	m_ptrIndex->push_back(3 + nSize);

	m_ptrIndex->push_back(0 + nSize);
	m_ptrIndex->push_back(1 + nSize);
	m_ptrIndex->push_back(2 + nSize);

}

//����
void Cuboid::Calculate(const std::vector<osg::Vec3d>& vecTempVec3Arry)
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
		m_ptrVetexArry->push_back(vecTempVec3Arry[i + 1]);

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

Cuboid::~Cuboid()
{

}

GLOBE_ENDNS