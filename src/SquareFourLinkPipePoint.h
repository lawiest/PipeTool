#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class SquareFourLinkPipePoint :public PipePoint
{
public:
	SquareFourLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double dbWidth, double dbHeight, double dbThirdWidth, double dbthirdHeight, std::string strPointID, std::string strTypeName);
	virtual bool build();

	virtual ~SquareFourLinkPipePoint();

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

	//一圈点的个数
	double m_nPointCnt;
};

GS_SMARTER_PTR(SquareFourLinkPipePoint);

GLOBE_ENDNS

