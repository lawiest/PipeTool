#pragma once
#include <utility.h>
#include "PipePoint.h"
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class CircleTwoLinkPipePoint :public PipePoint
{
public:
	CircleTwoLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double diameter, std::string strPointID, std::string strTypeName);

	virtual bool build();

	//算出所有中心点
	void CalcuSectionCenterPoints(const osg::Vec3d& start, const osg::Vec3d& center, const osg::Vec3d& end);

	void TransformAllVetex(const std::vector<osg::Vec3d>& ptrBaseVec3Arry);
	//特殊处理第一圈
	void TransformFirstCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry);
	//特殊处理最后圈
	void TransformLastCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry);

	//两头封闭
	void Close(const std::vector<osg::Vec3d>& ptrBaseVec3Arry);

	//计算索引
	void CalculateIndex();
	//计算法线
	void CalculateNormal();

	void setOuterExtend(double dbOuterExtend);

	virtual ~CircleTwoLinkPipePoint();

private:

	osg::ref_ptr<osg::Vec3dArray> m_ptrFirstSideVetexArry;
	osg::ref_ptr<osg::Vec3dArray> m_ptrEndSideVetexArry;

	std::vector<osg::Vec3d> m_vecDir;

	//管径
	double m_radius;
	//一圈点的个数
	double m_nPointCnt;

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

GS_SMARTER_PTR(CircleTwoLinkPipePoint);

GLOBE_ENDNS

