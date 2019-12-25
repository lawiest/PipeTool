#ifndef _THREAD_OBJECT_
#define _THREAD_OBJECT_

#include <QThread>
#include <QMutex>
#include <QPointer>
#include "PipeFactory.h"

class ThreadObject : public QThread
{
    Q_OBJECT

public:
	ThreadObject(GLOBE_NAME::PipeProducePara para,QObject* parent = NULL);
	ThreadObject(QObject* parent = NULL);

	void setPipePara(GLOBE_NAME::PipeProducePara para);

    ~ThreadObject();
	virtual void run();

    void stop();

private:
	GLOBE_NAME::PipeProducePara m_Para;

    bool m_isStop;
    QMutex m_stopMutex;
};

typedef QPointer<ThreadObject> ThreadObjectPtr;

#endif