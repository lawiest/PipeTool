#pragma once
#include <utility.h>
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/PrimitiveSet>

GLOBE_NS

class PipeLine :public GeoStar::Utility::GsRefObject
{
public:
	PipeLine();
	PipeLine(osg::Vec3d p1, osg::Vec3d p2, std::string strPipeID, std::string strTypeName);
	virtual ~PipeLine();

	virtual bool Build() { return true; };

	void setOriginePoint(osg::Vec3d point);
	bool IsSetOriginePoint();

	osg::Vec3dArray* getVetexArray();
	void setVetexArray(const osg::Vec3dArray* ptrVetexArray);

	osg::Vec3dArray* getNormalArray();
	osg::DrawElementsUShort* getIndexArray();

	void setMinus(bool isMinus);

	//保存到Obj
	virtual void SaveToObj(std::string strPath);

	virtual std::string getPipeName();

protected:
	//顶点
	osg::ref_ptr<osg::Vec3dArray> m_ptrVetexArry;
	//法线
	osg::ref_ptr<osg::Vec3dArray> m_ptrNormal;
	//索引
	osg::ref_ptr<osg::DrawElementsUShort> m_ptrIndex;

	//管线唯一名称/ID
	std::string m_strPipeName;
	std::string m_strTypeName;

	//是否已经设置偏移点
	bool m_IsSetOriginPoint;

	bool m_bIsMinus;

	//起点
	osg::Vec3d m_p1;
	//终点
	osg::Vec3d m_p2;

	//偏移点
	osg::Vec3d m_originePoint;
};

GS_SMARTER_PTR(PipeLine);

GLOBE_ENDNS

