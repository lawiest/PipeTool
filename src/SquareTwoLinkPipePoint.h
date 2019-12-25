#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class SquareTwoLinkPipePoint :public PipePoint
{
public:
	SquareTwoLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double dbWidth, double dbHeight, std::string strPointID, std::string strTypeName);

	virtual bool build();

	//算出所有中心点
	void CalcuSectionCenterPoints(const osg::Vec3d& start, const osg::Vec3d& center, const osg::Vec3d& end);

	void TransformAllVetex(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& tempVec3Arry);
	//特殊处理第一圈
	void TransformFirstCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& tempVec3Arry);
	//特殊处理最后圈
	void TransformLastCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& tempVec3Arry);

	//计算索引,和法线
	void Calculate(const std::vector<osg::Vec3d>& ptrTempVec3Arry);

	void Close();

	void setOuterExtend(double dbOuterExtend);
	void setExtend(double dbExtend);


	virtual ~SquareTwoLinkPipePoint();

private:

	std::vector<osg::Vec3d> m_vecDir;

	//管径宽
	double m_dbWidth;
	//管径高
	double m_dbHeight;

	std::vector<osg::Vec3d> m_vCenterPoints;

	//加粗
	double m_dbBold;
	//外圈加粗
	double m_dbOuterBold;
	//两头延长
	double m_dbExtend;
	//外圈两头延长
	double m_dbOuterExtend;
};

GS_SMARTER_PTR(SquareTwoLinkPipePoint);

GLOBE_ENDNS

