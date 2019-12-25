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
	//管径
	double m_radius;
	//第三根管管径
	double m_thirdRadius;
	//一圈点的个数
	double m_nPointCnt;
};

GS_SMARTER_PTR(CircleFourLinkPipePoint);

GLOBE_ENDNS

