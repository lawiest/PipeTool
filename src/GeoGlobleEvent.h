#pragma once
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>

enum GeoEventType
{
	ADD_NODE,
	REMOVE_NODE,
	ADD_OVERLAYNODE,
	ADD_LAYER,
	ADD_ELEMENT
};

class GeoGlobleEventAdapter : public osg::Referenced
{
public:
	GeoGlobleEventAdapter();

	void setEventType(GeoEventType eventType);
	void setData(osg::Node* ptrData);
	osg::Node* getData();


	GeoEventType EventType();

	virtual ~GeoGlobleEventAdapter() {};

private:
	osg::ref_ptr<osg::Node> m_ptrData;
	GeoEventType m_EventType;
};

class GeoGlobleEventHandler :public osgGA::GUIEventHandler
{
public:
	GeoGlobleEventHandler();

	virtual ~GeoGlobleEventHandler();
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

private:

};

