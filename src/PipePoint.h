#pragma once
#include <utility.h>
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class PipePoint :public GeoStar::Utility::GsRefObject
{
public:
	PipePoint(osg::Vec3d postion, std::string strPointID, std::string strTypeName);
	virtual ~PipePoint();

	osg::Vec3dArray* getVetexArray();
	osg::Vec3dArray* getNormalArray();
	osg::DrawElementsUShort* getIndexArray();

	//���浽Obj
	virtual void SaveToObj(std::string strPath);
	virtual bool build() { return false; };
	virtual std::string getPipePointName();

	void setOriginPoint(const osg::Vec3d& originPoint);

protected:

	//����
	osg::ref_ptr<osg::Vec3dArray> m_ptrVetexArry;
	//����
	osg::ref_ptr<osg::Vec3dArray> m_ptrNormal;
	//����
	osg::ref_ptr<osg::DrawElementsUShort> m_ptrIndex;

	//�ܵ������ƫ�Ƶ�ѿ�������
	osg::Vec3d m_centerPostion;
	//ƫ�Ƶ�
	osg::Vec3d m_originePoint;
	//ID
	std::string m_strPointID;
	std::string m_strTypeName;
};

GS_SMARTER_PTR(PipePoint);

GLOBE_ENDNS

