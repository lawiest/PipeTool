
#include "GeoGlobleEvent.h"
#include "PipeUntility.h"

GeoGlobleEventAdapter::GeoGlobleEventAdapter()
{
}

void GeoGlobleEventAdapter::setEventType(GeoEventType eventType)
{
	m_EventType = eventType;
}

GeoEventType GeoGlobleEventAdapter::EventType()
{
	return m_EventType;
}

void GeoGlobleEventAdapter::setData( osg::Node* ptrData)
{
	m_ptrData = ptrData;
}

osg::Node* GeoGlobleEventAdapter::getData()
{
	return m_ptrData;
}

GeoGlobleEventHandler::GeoGlobleEventHandler()
{

}

GeoGlobleEventHandler::~GeoGlobleEventHandler()
{

}

bool GeoGlobleEventHandler::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
{
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::FRAME:
		{
			
		}break;
	case osgGA::GUIEventAdapter::USER:
		{
			GeoGlobleEventAdapter* ptrGeoEventAdapter = (GeoGlobleEventAdapter*)dynamic_cast<const GeoGlobleEventAdapter*>(ea.getUserData());

			if(ptrGeoEventAdapter==NULL)
				break;

			switch (ptrGeoEventAdapter->EventType())
			{
				case ADD_NODE:
				{
					GLOBE_NAME::PipeUntility::getRoot()->addChild(ptrGeoEventAdapter->getData());
				}break;
				case REMOVE_NODE:
				{
					GLOBE_NAME::PipeUntility::getRoot()->removeChild(ptrGeoEventAdapter->getData());
				}break;
			}

		}break;
	default:
		break;
	}
	
	return false;
}
