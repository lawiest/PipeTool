#include "GsGeospace3DQt.h"
#include <osg/ref_ptr>
#include <QtWidgets/QGridLayout>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgQt/GraphicsWindowQt>
#include <osgGA/TrackballManipulator>
#include <osgGA/TerrainManipulator>

#include <osgDB/ReadFile>
#include <osgGA/StateSetManipulator>
#include <osg/Image>
#include <osgDB/WriteFile>
#include "PipeUntility.h"

GLOBE_NS

osgViewer::GraphicsWindowEmbedded* createGraphicsWindow1(int x, int y, int w, int h, const std::string& name, bool windowDecoration)
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = 8/*ds->getNumMultiSamples()*/;

	return new osgViewer::GraphicsWindowEmbedded(traits.get());
}

GsGeospace3DQt::GsGeospace3DQt(QWidget* parent,Qt::WindowFlags f) : QWidget(parent, f)
{
	//setThreadingModel(threadingModel);

	// disable the default setting of viewer.done() by pressing Escape.
	//setKeyEventSetsDone(0);

	QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 100, 100));
	QGridLayout* grid = new QGridLayout;
	grid->addWidget(widget1, 0, 0);
	//grid->addWidget(widget2, 0, 1);
	//grid->addWidget(widget3, 1, 0);
	//grid->addWidget(widget4, 1, 1);
	grid->setSpacing(0);
	grid->setContentsMargins(0, 0, 1, 0);
	setLayout(grid);
	connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
	_timer.start(17);
}

void GsGeospace3DQt::Test(std::string strUrl)
{

}

QWidget* GsGeospace3DQt::addViewWidget(osgQt::GraphicsWindowQt* gw)
{

	m_ptrViewer = PipeUntility::getViewer();

	m_ptrViewer->setCameraManipulator(new osgGA::TrackballManipulator());

	m_ptrViewer->setThreadingModel(osgViewer::ViewerBase::ThreadingModel::SingleThreaded);
	m_ptrViewer->setKeyEventSetsDone(0);

	m_ptrViewer->addEventHandler(new osgViewer::StatsHandler());
	m_ptrViewer->addEventHandler(new osgViewer::WindowSizeHandler());
	m_ptrViewer->addEventHandler(new osgViewer::LODScaleHandler());
	m_ptrViewer->addEventHandler(new osgGA::StateSetManipulator(m_ptrViewer->getCamera()->getOrCreateStateSet()));
	m_ptrViewer->addEventHandler(new osgViewer::ThreadingHandler);
	m_ptrViewer->addEventHandler(new osgViewer::HelpHandler);
	m_ptrViewer->getCamera()->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//m_ptrViewer->getCamera()->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.2f, 1.0f));
	//view->getCamera()->setProjectionMatrixAsPerspective(45.0f, static_cast<double>(this->width()) / static_cast<double>(this->height()), 1.0, 1000.0);

	osg::Group* ptrRoot = PipeUntility::getRoot();

	PipeUntility::createAxis();

	m_ptrViewer->setSceneData(ptrRoot);

	osg::Camera* camera = m_ptrViewer->getCamera();
	camera->setGraphicsContext(gw);

	const osg::GraphicsContext::Traits* traits = gw->getTraits();

	//camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	camera->setProjectionMatrixAsPerspective(45.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 0.1f, 10000.0f);

	gw->setTouchEventsEnabled(true);
	return gw->getGLWidget();
}

osgQt::GraphicsWindowQt* GsGeospace3DQt::createGraphicsWindow(int x, int y, int w, int h, const std::string& name, bool windowDecoration)
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = 8/*ds->getNumMultiSamples()*/;

	return new osgQt::GraphicsWindowQt(traits.get());
}

void GsGeospace3DQt::paintEvent(QPaintEvent* event)
{
	m_ptrViewer->frame();
}

GLOBE_ENDNS