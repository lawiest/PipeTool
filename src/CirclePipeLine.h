#pragma once

#include "PipeLine.h"
#include "PipeUntility.h"

GLOBE_NS

class  CirclePipeLine :public PipeLine
{
public:
	CirclePipeLine();
	CirclePipeLine(osg::Vec3d p1, osg::Vec3d p2, std::string strPipeID, double diameter, std::string strTypeName);
	virtual ~CirclePipeLine();

	//圆管建模
	virtual bool Build();

	//计算索引
	void CalculateIndex();

	//计算法线
	void CalculateNormal();

private:
	//一圈点的个数
	double m_nPointCnt;
	//管径
	double m_radius;
};

GS_SMARTER_PTR(CirclePipeLine);

GLOBE_ENDNS