#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class SquareThreeLinkPipePoint :public PipePoint
{
public:
	SquareThreeLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double dbWidth, double dbHeight, double dbThirdWidth, double dbthirdHeight, std::string strPointID, std::string strTypeName);

	virtual bool build();

	void setOuterExtend(double dbOuterExtend);

	virtual ~SquareThreeLinkPipePoint();

private:

	std::vector<osg::Vec3d> m_vecDir;

	//管径宽
	double m_dbWidth;
	//管径高
	double m_dbHeight;

	//第三根管径宽
	double m_dbThirdWidth;
	//第三根管径高
	double m_dbthirdHeight;

	//加粗
	double m_dbBold;
	//外圈加粗
	double m_dbOuterBold;
	//两头延长
	double m_dbExtend;
	//外圈两头延长
	double m_dbOuterExtend;
};

GS_SMARTER_PTR(SquareThreeLinkPipePoint);

GLOBE_ENDNS

