#pragma once
#include "scenegraph.h"   

#ifdef _WIN32
#include <atlbase.h>
#include <atlcom.h>
#include <atlwin.h>

GLOBE_NS

/// \brief 基于Windows实现的三维场景插件
template<class T>
class GsWindowsSceneGraph :public T,public CWindowImpl< GsWindowsSceneGraph<T> >
{
	HWND m_WinHwnd;
	const unsigned int m_TimerID;
public:
	GsWindowsSceneGraph(HWND hwnd, int nMaxFPS = 100):m_TimerID(147286)
	{
		SubclassWindow(hwnd);
		m_WinHwnd = hwnd;

		SetTimer(m_TimerID, 1000.0 / nMaxFPS);
	}
	~GsWindowsSceneGraph()
	{
		UnsubclassWindow();
	}
	virtual void* WindowHandle()
	{
		return m_WinHwnd;
	}

	BEGIN_MSG_MAP(GsWindowsSceneGraph)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnMouseLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnMouseLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_SIZE, OnReSize)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnMouseRButtonDown)
		MESSAGE_HANDLER(WM_MBUTTONDOWN, OnMouseMButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONUP, OnMouseRButtonUp)
		MESSAGE_HANDLER(WM_MBUTTONUP, OnMouseMButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnMouseLButtonDoubleClick)
		MESSAGE_HANDLER(WM_RBUTTONDBLCLK, OnMouseRButtonDoubleClick)
		MESSAGE_HANDLER(WM_MBUTTONDBLCLK, OnMouseMButtonDoubleClick)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	END_MSG_MAP()

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (wParam != m_TimerID)
			return S_OK;

		T::OnRender();
		return S_OK;
	}

	virtual void Close()
	{
		KillTimer(m_TimerID);
		T::Close();
	}

	LRESULT OnMouseLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		int button = 0;
		button |= eLeftButton;
		T::OnMouseDown((GsButton)button, x, y);
		return S_OK;
	}

	LRESULT OnMouseRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		int button = 0;
		button |= eRightButton;
		T::OnMouseDown((GsButton)button, x, y);
		return S_OK;
	}

	LRESULT OnMouseMButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		int button = 0;
		button |= eMiddleButton;
		T::OnMouseDown((GsButton)button, x, y);
		return S_OK;
	}

	LRESULT OnMouseLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		int button = 0;
		button |= eLeftButton;
		T::OnMouseUp((GsButton)button, x, y);
		return S_OK;
	}

	LRESULT OnMouseRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		int button = 0;
		button |= eRightButton;
		T::OnMouseUp((GsButton)button, x, y);
		return S_OK;
	}

	LRESULT OnMouseMButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		int button = 0;
		button |= eMiddleButton;
		T::OnMouseUp((GsButton)button, x, y);
		return S_OK;
	}

	LRESULT OnMouseLButtonDoubleClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		int button = 0;
		button |= eLeftButton;
		T::OnMouseDoubleClick((GsButton)button, x, y);
		return S_OK;
	}

	LRESULT OnMouseRButtonDoubleClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		int button = 0;
		button |= eRightButton;
		T::OnMouseDoubleClick((GsButton)button, x, y);
		return S_OK;
	}

	LRESULT OnMouseMButtonDoubleClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		int button = 0;
		button |= eMiddleButton;
		T::OnMouseDoubleClick((GsButton)button, x, y);
		return S_OK;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		GetMousePosition(lParam, x, y);

		T::OnMouseMove(x, y);
		return S_OK;
	}

	LRESULT OnReSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int nWidth = LOWORD(lParam);
		int nHeight = HIWORD(lParam);

		T::ResizeWindow(nWidth, nHeight);
		return S_OK;
	}

	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		int x = 0;
		int y = 0;
		int nDelta = (short)HIWORD(wParam);
		GetMousePosition(lParam, x, y);

		T::OnMouseWheel(nDelta, x, y);
		return S_OK;
	}

	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		T::OnKeyDown((GsKey)TransKey(wParam));
		return S_OK;
	}

	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		T::OnKeyUp((GsKey)TransKey(wParam));
		return S_OK;
	}

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		T::OnFocus();
		return S_OK;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc(uMsg, wParam, lParam);

		T::OnFocusOut();
		return S_OK;
	}

private:
	void GetMousePosition(LPARAM lParam, int &x, int &y)
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
	}

	//asc2表转换成引擎自定义
	int TransKey(unsigned int key)
	{
		switch (key)
		{
		case 32://空格
			return eKeySpace;

		case 27://esc
			return 256;
		}

		return key;
	}
};
GLOBE_ENDNS

#endif //_WIN32
