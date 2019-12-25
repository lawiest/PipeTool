#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class Cylinder :public PipePoint
{
public:
	Cylinder(osg::Vec3d dir, osg::Vec3d postion, double radius, std::string strPointID, std::string strTypeName);
	virtual bool build();

	void setExtend(double dbExtend);

	void TranslateSideVetex(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& vecTempVetex);

	void CalculateIndex();
	void CalculateNormal();
	void CloseTwoSideFace();

	virtual ~Cylinder();

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
};

GS_SMARTER_PTR(Cylinder);

GLOBE_ENDNS

