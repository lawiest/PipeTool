#pragma once
#include <utility.h>
#include <osg/Vec3d>
#include <osg/Group>
#include <osgViewer/Viewer>

GLOBE_NS

const double EarthRadiu = 6371393.0;
const double PI = 3.14159265358979323846;

class PipeUntility :public GeoStar::Utility::GsRefObject
{
public:
	PipeUntility();

	static osg::Group* getRoot();
	static osgViewer::Viewer* getViewer();

	static osg::Vec3d ToDKE(const osg::Vec3d&  pt);
	//2次B样条
	static osg::Vec3d BSpline2(double delta, const osg::Vec3d & p0, const osg::Vec3d & p1, const osg::Vec3d & p2);
	static osg::Vec3d BSpline2Ex(double delta, const osg::Vec3d & p0, const osg::Vec3d & p1, const osg::Vec3d & p2);
	static void createLine(osg::Vec3Array* vertices);
	static void createLine(osg::Vec3d p1, osg::Vec3d p2);
	static void createAxis(osg::Vec3d XAxis, osg::Vec3d YAxis, osg::Vec3d ZAxis, osg::Vec3d trans, double dbLenght);
	//创建X、Y、Z三个轴好观察
	static void createAxis();

	virtual ~PipeUntility();

private:
	static osg::ref_ptr<osg::Group> m_ptrRoot;
	static osg::ref_ptr<osgViewer::Viewer> m_ptrViewer;
};

GS_SMARTER_PTR(PipeUntility);

GLOBE_ENDNS

