#pragma once
#include "scenegraph.h"   
#include <QWidget>
#include <QMouseEvent>
#include <QtWidgets/QApplication>
GLOBE_NS 

/// \brief 基于QT实现的三维场景插件
template<class T>
class GsQTSceneGraph:public T, public QWidget
{
	int m_timer_update;
	int m_timer_network;
public:
	GsQTSceneGraph(int nMaxFPS = 100,QWidget* parent = Q_NULLPTR,
		Qt::WindowFlags f = Qt::WindowFlags()):QWidget(parent,f)
	{
		if (nMaxFPS <= 0) nMaxFPS = 100;
#ifdef _WIN32
		setAttribute(Qt::WA_PaintOnScreen);
#endif
		setAttribute(Qt::WA_NoSystemBackground);
		setFocusPolicy(Qt::StrongFocus);
		setMouseTracking(true);
		m_timer_update = startTimer(1000.0 / nMaxFPS);
		//设定网络消息处理速度是渲染的2倍
		m_timer_network = startTimer(1000.0 / (nMaxFPS * 2));
	}

	/// \brief 返回窗体对象
	virtual void* WindowHandle()
	{
		return (void*)QWidget::winId();
	}
public:

	/// \brief 关闭场景
	virtual void Close()
	{
		killTimer(0);
		T::Close();
	}
	/// \brief 定时器触发事件
	virtual void timerEvent(QTimerEvent *event)
	{
		if (event->timerId() == m_timer_update)
		{
			T::OnRender();

			QWidget::update();
		}
		if (event->timerId() == m_timer_network)
		{
			OnHandleNetWork();
		}
		QWidget::timerEvent(event);
	}

	/// \brief 重绘事件
	virtual QPaintEngine *paintEngine() const
	{
		return NULL;
	}

	/// \brief 调整窗体Size事件
	virtual void resizeEvent(QResizeEvent *event)
	{
		int width = size().width();
		int height = size().height();
		T::ResizeWindow(width, height);

		QWidget::resizeEvent(event);
	}

	/// \brief 鼠标单击按下事件
	virtual void mousePressEvent(QMouseEvent *event)
	{
		int button = 0;
		if (event->button() & Qt::LeftButton)
			button |= eLeftButton;
		if (event->button() & Qt::RightButton)
			button |= eRightButton;
		if (event->button() & Qt::MidButton)
			button |= eMiddleButton;
		T::OnMouseDown((GsButton)button, event->pos().x(), event->pos().y());

		QWidget::mousePressEvent(event);
	}

	/// \brief 鼠标单击弹起事件
	virtual void mouseReleaseEvent(QMouseEvent *event)
	{
		int button = 0;
		if (event->button() & Qt::LeftButton)
			button |= eLeftButton;
		if (event->button() & Qt::RightButton)
			button |= eRightButton;
		if (event->button() & Qt::MidButton)
			button |= eMiddleButton;
		T::OnMouseUp((GsButton)button, event->pos().x(), event->pos().y());

		QWidget::mouseReleaseEvent(event);
	}

	/// \brief 鼠标双击事件
	virtual void mouseDoubleClickEvent(QMouseEvent *event)
	{
		int button = 0;
		if (event->button() & Qt::LeftButton)
			button |= eLeftButton;
		if (event->button() & Qt::RightButton)
			button |= eRightButton;
		if (event->button() & Qt::MidButton)
			button |= eMiddleButton;
		T::OnMouseDoubleClick((GsButton)button, event->pos().x(), event->pos().y());

		QWidget::mouseDoubleClickEvent(event);
	}

	/// \brief 鼠标移动事件
	virtual void mouseMoveEvent(QMouseEvent *event)
	{
		QPoint pos = mapFromGlobal(event->globalPos());
		T::OnMouseMove(pos.x(), pos.y());
		QWidget::mouseMoveEvent(event);
	}

	/// \brief 鼠标滚轮滚动事件
	virtual void wheelEvent(QWheelEvent *event)
	{
		T::OnMouseWheel(event->delta(), event->pos().x(), event->pos().y());
		QWidget::wheelEvent(event);
	}

	/// \brief 按键按下事件
	virtual void keyPressEvent(QKeyEvent *event)
	{
		T::OnKeyDown((GsKey)TransKey((GsKey)event->key()));
		QWidget::keyPressEvent(event);
	}

	/// \brief 按键弹起事件
	virtual void keyReleaseEvent(QKeyEvent *event)
	{
		T::OnKeyUp((GsKey)event->key());
		QWidget::keyReleaseEvent(event);
	}

	/// \breif 插件获取焦点事件
	virtual void focusInEvent(QFocusEvent *event)
	{
		T::OnFocus();
		QWidget::focusInEvent(event);
	}

	/// \breif 插件失去焦点事件
	virtual void focusOutEvent(QFocusEvent *event)
	{
		T::OnFocusOut();
		QWidget::focusOutEvent(event);
	}

protected:
	int TransKey(GsKey key)
	{
		switch (key)
		{
		case eKeyEscape:
			return 256;
		}

		return key;
	}

	virtual void OnHandleNetWork() {}
};
GLOBE_ENDNS