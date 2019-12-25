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
	//�ܾ�
	double m_radius;
	//һȦ��ĸ���
	double m_nPointCnt;

	//�Ӵ�
	double m_dbBold;
	//��Ȧ�Ӵ�
	double m_dbOuterBold;
	//��ͷ�ӳ�
	double m_dbExtend;
	//��Ȧ��ͷ�ӳ�
	double m_dbOuterExtend;
};

GS_SMARTER_PTR(CircleStraightLinkPipePoint);

GLOBE_ENDNS

