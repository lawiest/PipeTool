#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class Cuboid :public PipePoint
{
public:
	Cuboid(osg::Vec3d dir, osg::Vec3d postion, double width, double height, std::string strPointID, std::string strTypeName);
	virtual bool build();

	//��������,�ͷ���
	void Calculate(const std::vector<osg::Vec3d>& vecTempVec3Arry);

	void setExtend(double dbExtend);

	void Close(const std::vector<osg::Vec3d>& vecTempVec3Arry);

	virtual ~Cuboid();

private:

	osg::Vec3d m_dir;
	//�ܾ���
	double m_dbWidth;
	//�ܾ���
	double m_dbHeight;

	//�Ӵ�
	double m_dbBold;
	//��ͷ�ӳ�
	double m_dbExtend;
};

GS_SMARTER_PTR(Cuboid);

GLOBE_ENDNS

