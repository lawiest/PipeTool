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

	//�ܾ���
	double m_dbWidth;
	//�ܾ���
	double m_dbHeight;

	//�Ӵ�
	double m_dbBold;
	//��Ȧ�Ӵ�
	double m_dbOuterBold;
	//��ͷ�ӳ�
	double m_dbExtend;
	//��Ȧ��ͷ�ӳ�
	double m_dbOuterExtend;
};

GS_SMARTER_PTR(SquareStraightLinkPipePoint);

GLOBE_ENDNS

