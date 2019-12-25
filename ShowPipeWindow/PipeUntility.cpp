#include "PipeUntility.h"
#include <osg/Geometry>
#include <osg/Array>
#include <osg/LineWidth>
#include <osg/Geode>

GLOBE_NS

osg::ref_ptr<osg::Group> PipeUntility::m_ptrRoot = NULL;
osg::ref_ptr<osgViewer::Viewer> PipeUntility::m_ptrViewer = NULL;

PipeUntility::PipeUntility()
{

}

osg::Group* PipeUntility::getRoot()
{
	if (m_ptrRoot == NULL)
		m_ptrRoot = new osg::Group();

	return m_ptrRoot;
}

osgViewer::Viewer* PipeUntility::getViewer()
{
	if (m_ptrViewer == NULL)
		m_ptrViewer = new osgViewer::Viewer();

	return m_ptrViewer;
}

osg::Vec3d PipeUntility::ToDKE(const osg::Vec3d&  pt)
{
	osg::Vec3d tempPos = pt;

	osg::Vec3d  ptRet;
	//实际的高程加上地球的半径
	tempPos.z() += EarthRadiu;
	//X和Y弧度。
	tempPos.y() *= osg::PI / 180.0;
	tempPos.x() *= osg::PI / 180.0;

	//Z坐标
	ptRet.z() = tempPos.z() * sin(tempPos.y());

	//由维度值计算出坐标点所在Z平面上的长度。
	double dblZLen = tempPos.z() * cos(tempPos.y());

	//计算出x和y
	ptRet.x() = dblZLen * cos(tempPos.x());
	ptRet.y() = dblZLen * sin(tempPos.x());
	return ptRet;
}

osg::Vec3d PipeUntility::BSpline2(double delta, const osg::Vec3d & p0, const osg::Vec3d & p1, const osg::Vec3d & p2)
{
	double t = delta;
	double f02 = 0.5 * (t - 1) * (t - 1);
	double f12 = -1 * t * t + t + 0.5;
	double f22 = 0.5 * t * t;

	return osg::Vec3d(f02 * p0.x() + f12 * p1.x() + f22 * p2.x(), f02 * p0.y() + f12 * p1.y() + f22 * p2.y(), f02 * p0.z() + f12 * p1.z() + f22 * p2.z());
}

osg::Vec3d PipeUntility::BSpline2Ex(double delta, const osg::Vec3d & p0, const osg::Vec3d & p1, const osg::Vec3d & p2)
{
	double t = delta;
	double f02 = (1 - t) * (1 - t);
	double f12 = 2 * t * (1 - t);
	double f22 = t * t;

	return osg::Vec3d(f02 * p0.x() + f12 * p1.x() + f22 * p2.x(), f02 * p0.y() + f12 * p1.y() + f22 * p2.y(), f02 * p0.z() + f12 * p1.z() + f22 * p2.z());
}

void PipeUntility::createLine(osg::Vec3Array* vertices)
{
	osg::Geometry* linesGeom = new osg::Geometry();

	linesGeom->setVertexArray(vertices);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	linesGeom->setColorArray(colors, osg::Array::BIND_OVERALL);

	// set the normal in the same way color.
	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	linesGeom->setNormalArray(normals, osg::Array::BIND_OVERALL);

	linesGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices->size()));

	osg::ref_ptr<osg::LineWidth> ptrLineWidth = new osg::LineWidth(1);

	osg::Geode* ptrGeode = new osg::Geode();

	// add the points geometry to the geode.
	ptrGeode->addDrawable(linesGeom);

	ptrGeode->getOrCreateStateSet()->setAttribute(ptrLineWidth);
	ptrGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	PipeUntility::getRoot()->addChild(ptrGeode);
}


void PipeUntility::createLine(osg::Vec3d p1, osg::Vec3d p2)
{
	osg::Geometry* linesGeom = new osg::Geometry();

	osg::Vec3Array* vertices = new osg::Vec3Array(2);
	(*vertices)[0].set(p1);
	(*vertices)[1].set(p2);

	linesGeom->setVertexArray(vertices);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	linesGeom->setColorArray(colors, osg::Array::BIND_OVERALL);

	// set the normal in the same way color.
	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	linesGeom->setNormalArray(normals, osg::Array::BIND_OVERALL);

	linesGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));

	osg::ref_ptr<osg::LineWidth> ptrLineWidth = new osg::LineWidth(2);

	osg::Geode* ptrGeode = new osg::Geode();

	// add the points geometry to the geode.
	ptrGeode->addDrawable(linesGeom);
	//ptrGeode->getOrCreateStateSet()->setAttribute(ptrLineWidth);
	ptrGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	PipeUntility::getRoot()->addChild(ptrGeode);
}


void PipeUntility::createAxis(osg::Vec3d XAxis, osg::Vec3d YAxis, osg::Vec3d ZAxis, osg::Vec3d trans, double dbLenght)
{
	osg::Geometry* linesGeom = new osg::Geometry();
	osg::Geometry* linesGeomY = new osg::Geometry();
	osg::Geometry* linesGeomZ = new osg::Geometry();

	osg::Vec3Array* vertices = new osg::Vec3Array(2);
	(*vertices)[0].set(osg::Vec3(0.0f, 0.0f, 0.0f) + trans);
	(*vertices)[1].set(XAxis * 2 + trans);

	osg::Vec3Array* verticesY = new osg::Vec3Array(2);
	(*verticesY)[0].set(osg::Vec3(0.0f, 0.0f, 0.0f) + trans);
	(*verticesY)[1].set(YAxis * dbLenght + trans);

	osg::Vec3Array* verticesZ = new osg::Vec3Array(2);
	(*verticesZ)[0].set(osg::Vec3(0.0f, 0.0f, 0.0f) + trans);
	(*verticesZ)[1].set(ZAxis * 2 + trans);

	linesGeom->setVertexArray(vertices);
	linesGeomY->setVertexArray(verticesY);
	linesGeomZ->setVertexArray(verticesZ);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	linesGeom->setColorArray(colors, osg::Array::BIND_OVERALL);

	osg::Vec4Array* colorsY = new osg::Vec4Array;
	colorsY->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	linesGeomY->setColorArray(colorsY, osg::Array::BIND_OVERALL);

	osg::Vec4Array* colorsZ = new osg::Vec4Array;
	colorsZ->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	linesGeomZ->setColorArray(colorsZ, osg::Array::BIND_OVERALL);

	// set the normal in the same way color.
	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	linesGeom->setNormalArray(normals, osg::Array::BIND_OVERALL);
	linesGeomY->setNormalArray(normals, osg::Array::BIND_OVERALL);
	linesGeomZ->setNormalArray(normals, osg::Array::BIND_OVERALL);

	linesGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));
	linesGeomY->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));
	linesGeomZ->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));

	osg::ref_ptr<osg::LineWidth> ptrLineWidth = new osg::LineWidth(3);

	osg::Geode* ptrGeode = new osg::Geode();

	// add the points geometry to the geode.
	ptrGeode->addDrawable(linesGeom);
	ptrGeode->addDrawable(linesGeomY);
	ptrGeode->addDrawable(linesGeomZ);
	//ptrGeode->getOrCreateStateSet()->setAttribute(ptrLineWidth);
	ptrGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	PipeUntility::getRoot()->addChild(ptrGeode);
}


//创建X、Y、Z三个轴好观察
void PipeUntility::createAxis()
{
	osg::Geometry* linesGeom = new osg::Geometry();
	osg::Geometry* linesGeomY = new osg::Geometry();
	osg::Geometry* linesGeomZ = new osg::Geometry();

	osg::Vec3Array* vertices = new osg::Vec3Array(2);
	(*vertices)[0].set(0.0f, 0.0f, 0.0f);
	(*vertices)[1].set(50.0, 0.0f, 0.0f);

	osg::Vec3Array* verticesY = new osg::Vec3Array(2);
	(*verticesY)[0].set(0.0f, 0.0f, 0.0f);
	(*verticesY)[1].set(0.0, 50.0f, 0.0f);

	osg::Vec3Array* verticesZ = new osg::Vec3Array(2);
	(*verticesZ)[0].set(0.0f, 0.0f, 0.0f);
	(*verticesZ)[1].set(0.0, 0.0f, 50.0f);

	linesGeom->setVertexArray(vertices);
	linesGeomY->setVertexArray(verticesY);
	linesGeomZ->setVertexArray(verticesZ);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	linesGeom->setColorArray(colors, osg::Array::BIND_OVERALL);

	osg::Vec4Array* colorsY = new osg::Vec4Array;
	colorsY->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	linesGeomY->setColorArray(colorsY, osg::Array::BIND_OVERALL);


	osg::Vec4Array* colorsZ = new osg::Vec4Array;
	colorsZ->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 0.0f));
	linesGeomZ->setColorArray(colorsZ, osg::Array::BIND_OVERALL);

	// set the normal in the same way color.
	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	linesGeom->setNormalArray(normals, osg::Array::BIND_OVERALL);
	linesGeomY->setNormalArray(normals, osg::Array::BIND_OVERALL);
	linesGeomZ->setNormalArray(normals, osg::Array::BIND_OVERALL);

	linesGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));
	linesGeomY->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));
	linesGeomZ->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));

	osg::ref_ptr<osg::LineWidth> ptrLineWidth = new osg::LineWidth(5);

	osg::Geode* ptrGeode = new osg::Geode();

	// add the points geometry to the geode.
	ptrGeode->addDrawable(linesGeom);
	ptrGeode->addDrawable(linesGeomY);
	ptrGeode->addDrawable(linesGeomZ);
	ptrGeode->getOrCreateStateSet()->setAttribute(ptrLineWidth);
	ptrGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	m_ptrRoot->addChild(ptrGeode);
}


PipeUntility::~PipeUntility()
{

}

GLOBE_ENDNS