#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class CircleStraightLinkPipePoint :public PipePoint
{
public:
	CircleStraightLinkPipePoint(osg::Vec3d dir, osg::Vec3d postion, double diameter, std::string strPointID, std::string strTypeName);
	virtual bool build();

	void setBold(double dbBold);
	void setExtend(double dbExtend);
	void setOuterExtend(double dbOuterExtend);

	void closeFirstSide();

	virtual ~CircleStraightLinkPipePoint();

private:

	osg::Vec3d m_dir;
	//管径
	double m_radius;
	//一圈点的个数
	double m_nPointCnt;

	//加粗
	double m_dbBold;
	//外圈加粗
	double m_dbOuterBold;
	//两头延长
	double m_dbExtend;
	//外圈两头延长
	double m_dbOuterExtend;
};

GS_SMARTER_PTR(CircleStraightLinkPipePoint);

GLOBE_ENDNS

