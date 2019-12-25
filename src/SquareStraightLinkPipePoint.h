#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class SquareStraightLinkPipePoint :public PipePoint
{
public:
	SquareStraightLinkPipePoint(osg::Vec3d dir, osg::Vec3d postion, double dbWidth, double dbHeight, std::string strPointID, std::string strTypeName);
	virtual bool build();

	void setBold(double dbBold);
	void setExtend(double dbExtend);
	void setOuterExtend(double dbOuterExtend);

	void closeFirstSide();

	virtual ~SquareStraightLinkPipePoint();

private:

	osg::Vec3d m_dir;

	//管径宽
	double m_dbWidth;
	//管径高
	double m_dbHeight;

	//加粗
	double m_dbBold;
	//外圈加粗
	double m_dbOuterBold;
	//两头延长
	double m_dbExtend;
	//外圈两头延长
	double m_dbOuterExtend;
};

GS_SMARTER_PTR(SquareStraightLinkPipePoint);

GLOBE_ENDNS

