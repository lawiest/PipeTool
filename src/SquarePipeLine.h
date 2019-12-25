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

	//Բ�ܽ�ģ
	virtual bool Build();

	//��������,�ͷ���
	void Calculate(const std::vector<osg::Vec3d>& vecTempVec3Arry);

private:
	double m_dbWidth;
	double m_dbHeight;

	//���߶�ƫ�Ƶ�ѿ�������
	osg::Vec3d m_centerPostion;
};

GS_SMARTER_PTR(SquarePipeLine);

GLOBE_ENDNS