#pragma once
#include <utility.h>
#include <geometry.h>
#include <QtWidgets/QWidget>
#include <QtCore/QTimer>

namespace osgQt
{
	class GraphicsWindowQt;
}

namespace osgViewer
{
	class Viewer;
}

GLOBE_NS

class GS_API GsGeospace3DQt : public QWidget, public GeoStar::Utility::GsRefObject
{
public:
	GsGeospace3DQt(QWidget* parent = 0, Qt::WindowFlags f = 0);

	QWidget* addViewWidget(osgQt::GraphicsWindowQt* gw);

	osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false);

	void Test(std::string strUrl);

	virtual void paintEvent(QPaintEvent* event);

protected:

	QTimer _timer;
	osgViewer::Viewer* m_ptrViewer;
};

GS_SMARTER_PTR(GsGeospace3DQt);

GLOBE_ENDNS

