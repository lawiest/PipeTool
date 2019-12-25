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

	//����������ĵ�
	void CalcuSectionCenterPoints(const osg::Vec3d& start, const osg::Vec3d& center, const osg::Vec3d& end);

	void TransformAllVetex(const std::vector<osg::Vec3d>& ptrBaseVec3Arry);
	//���⴦���һȦ
	void TransformFirstCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry);
	//���⴦�����Ȧ
	void TransformLastCircle(const std::vector<osg::Vec3d>& ptrBaseVec3Arry);

	//��ͷ���
	void Close(const std::vector<osg::Vec3d>& ptrBaseVec3Arry);

	//��������
	void CalculateIndex();
	//���㷨��
	void CalculateNormal();

	void setOuterExtend(double dbOuterExtend);

	virtual ~CircleTwoLinkPipePoint();

private:

	osg::ref_ptr<osg::Vec3dArray> m_ptrFirstSideVetexArry;
	osg::ref_ptr<osg::Vec3dArray> m_ptrEndSideVetexArry;

	std::vector<osg::Vec3d> m_vecDir;

	//�ܾ�
	double m_radius;
	//һȦ��ĸ���
	double m_nPointCnt;

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

GS_SMARTER_PTR(CircleTwoLinkPipePoint);

GLOBE_ENDNS

