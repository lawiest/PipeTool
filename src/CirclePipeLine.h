#pragma once

#include "PipeLine.h"
#include "PipeUntility.h"

GLOBE_NS

class  CirclePipeLine :public PipeLine
{
public:
	CirclePipeLine();
	CirclePipeLine(osg::Vec3d p1, osg::Vec3d p2, std::string strPipeID, double diameter, std::string strTypeName);
	virtual ~CirclePipeLine();

	//Բ�ܽ�ģ
	virtual bool Build();

	//��������
	void CalculateIndex();

	//���㷨��
	void CalculateNormal();

private:
	//һȦ��ĸ���
	double m_nPointCnt;
	//�ܾ�
	double m_radius;
};

GS_SMARTER_PTR(CirclePipeLine);

GLOBE_ENDNS