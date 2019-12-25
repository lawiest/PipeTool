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

	//�ܾ���
	double m_dbWidth;
	//�ܾ���
	double m_dbHeight;

	//�������ܾ���
	double m_dbThirdWidth;
	//�������ܾ���
	double m_dbthirdHeight;

	//һȦ��ĸ���
	double m_nPointCnt;
};

GS_SMARTER_PTR(SquareFourLinkPipePoint);

GLOBE_ENDNS

