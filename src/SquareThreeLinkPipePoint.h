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

	//�ܾ���
	double m_dbWidth;
	//�ܾ���
	double m_dbHeight;

	//�������ܾ���
	double m_dbThirdWidth;
	//�������ܾ���
	double m_dbthirdHeight;

	//�Ӵ�
	double m_dbBold;
	//��Ȧ�Ӵ�
	double m_dbOuterBold;
	//��ͷ�ӳ�
	double m_dbExtend;
	//��Ȧ��ͷ�ӳ�
	double m_dbOuterExtend;
};

GS_SMARTER_PTR(SquareThreeLinkPipePoint);

GLOBE_ENDNS

