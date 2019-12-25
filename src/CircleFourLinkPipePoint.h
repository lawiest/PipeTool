#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class CircleFourLinkPipePoint :public PipePoint
{
public:
	CircleFourLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double diameter, double thirdDiameter, std::string strPointID, std::string strTypeName);
	virtual bool build();

	virtual ~CircleFourLinkPipePoint();

private:

	std::vector<osg::Vec3d> m_vecDir;
	//�ܾ�
	double m_radius;
	//�������ܹܾ�
	double m_thirdRadius;
	//һȦ��ĸ���
	double m_nPointCnt;
};

GS_SMARTER_PTR(CircleFourLinkPipePoint);

GLOBE_ENDNS

