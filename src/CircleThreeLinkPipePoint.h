#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class CircleThreeLinkPipePoint :public PipePoint
{
public:
	CircleThreeLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double diameter, double thirdDiameter, std::string strPointID, std::string strTypeName);
	virtual bool build();

	virtual ~CircleThreeLinkPipePoint();

private:

	std::vector<osg::Vec3d> m_vecDir;

	//�ܾ�
	double m_radius;
	//�������ܹܾ�
	double m_thirdRadius;
	//һȦ��ĸ���
	double m_nPointCnt;

	//�Ӵ�
	double m_dbBold;
	//��Ȧ�Ӵ�
	double m_dbOuterBold;
	//��ͷ�ӳ�
	double m_dbExtend;
};

GS_SMARTER_PTR(CircleThreeLinkPipePoint);

GLOBE_ENDNS

