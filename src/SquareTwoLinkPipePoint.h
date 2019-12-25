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

	//����������ĵ�
	void CalcuSectionCenterPoints(const osg::Vec3d& start, const osg::Vec3d& center, const osg::Vec3d& end);

	void TransformAllVetex(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& tempVec3Arry);
	//���⴦���һȦ
	void TransformFirstCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& tempVec3Arry);
	//���⴦�����Ȧ
	void TransformLastCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry, std::vector<osg::Vec3d>& tempVec3Arry);

	//��������,�ͷ���
	void Calculate(const std::vector<osg::Vec3d>& ptrTempVec3Arry);

	void Close();

	void setOuterExtend(double dbOuterExtend);
	void setExtend(double dbExtend);


	virtual ~SquareTwoLinkPipePoint();

private:

	std::vector<osg::Vec3d> m_vecDir;

	//�ܾ���
	double m_dbWidth;
	//�ܾ���
	double m_dbHeight;

	std::vector<osg::Vec3d> m_vCenterPoints;

	//�Ӵ�
	double m_dbBold;
	//��Ȧ�Ӵ�
	double m_dbOuterBold;
	//��ͷ�ӳ�
	double m_dbExtend;
	//��Ȧ��ͷ�ӳ�
	double m_dbOuterExtend;
};

GS_SMARTER_PTR(SquareTwoLinkPipePoint);

GLOBE_ENDNS

