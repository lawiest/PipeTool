#pragma once

#include "PipeLine.h"
#include <osg/Array>
#include <osg/PrimitiveSet>
#include "PipeUntility.h"

GLOBE_NS

class SquarePipeLine :public PipeLine
{
public:
	SquarePipeLine(osg::Vec3d p1, osg::Vec3d p2, std::string strPipeID, double dbWidth, double dbHeight, std::string strTypeName);
	virtual ~SquarePipeLine();

	//圆管建模
	virtual bool Build();

	//计算索引,和法线
	void Calculate(const std::vector<osg::Vec3d>& vecTempVec3Arry);

private:
	double m_dbWidth;
	double m_dbHeight;

	//管线对偏移点笛卡尔坐标
	osg::Vec3d m_centerPostion;
};

GS_SMARTER_PTR(SquarePipeLine);

GLOBE_ENDNS