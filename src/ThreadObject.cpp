#include "ThreadObject.h"
#include <QThread>
#include <QDebug>
#include <QMutexLocker>
#include <QElapsedTimer>
#include <limits>

ThreadObject::ThreadObject(GLOBE_NAME::PipeProducePara para,QObject *parent):QThread(parent)
{
	m_Para = para;
	m_isStop = false;
}

ThreadObject::ThreadObject(QObject *parent) : QThread(parent)
{
	m_isStop = false;
}

void ThreadObject::setPipePara(GLOBE_NAME::PipeProducePara para)
{
	m_Para = para;
}

ThreadObject::~ThreadObject()
{

}

void ThreadObject::run()
{
	GLOBE_NAME::PipeFactory pipeFac(m_Para);
	pipeFac.BuildPipeLine();
	pipeFac.BuildPipePoint();
	pipeFac.SaveAndShowObj();
}

void ThreadObject::stop()
{
    QMutexLocker locker(&m_stopMutex);
    m_isStop = true;
}
