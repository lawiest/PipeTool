#pragma once
#include "utility.h"
#include "kernel.h"
#include "element.h"
  
GLOBE_NS
// 轨迹类型
enum GsTrackerType
{
	eTrackerDefault = 0,// 自定义类型
	eTrackerMeasure=1,	// 量算轨迹类型
	eTrackerPlot=2,		// 标绘轨迹类型
	//...
	eTrackerCustom = 5	//自定义轨迹类型
};

/// \brief 轨迹要素类
class GS_API GsTrackerElement : public Gs3DElement
{
protected:
	// 轨迹类型
	int m_nTrackerType;

	// 显示符号
	KERNEL_NAME::GsSymbolPtr m_ptrSymbol;

	// 几何对象
	KERNEL_NAME::GsGeometryPtr m_ptrGeometry;
public:
	GsTrackerElement(bool bSurface);
	virtual ~GsTrackerElement();

	virtual void Destory();

	/// \brief 绘制画布
	virtual bool Draw(KERNEL_NAME::GsCanvas* pCanvas, KERNEL_NAME::GsDisplayTransformation *pDT) = 0;

	/// \brief 显示符号
	virtual void Symbol(GsSymbol* pSymbol, bool bClone = false) {}
	virtual GsSymbol* Symbol() { return m_ptrSymbol; }

	/// \brief 几何对象
	virtual void Geometry(GsGeometry* pGeo) {}
	virtual GsGeometry* Geometry() { return m_ptrGeometry; }

	/// \brief 是否是地表要素
	virtual void Element3D(bool b3DElement) { m_b3DElement = b3DElement; }
	virtual bool Element3D() { return m_b3DElement; }

	/// \brief 轨迹类型
	virtual void TrackerType(int nTrackerType) { m_nTrackerType = nTrackerType; }
	virtual int TrackerType() { return m_nTrackerType; }

};
GS_SMARTER_PTR(GsTrackerElement);

class GS_API GsTrackerElementMgr : public UTILITY_NAME::GsRefObject
{
	int m_nTrackerType;
protected:
	GsTrackerElementMgr(int nTrackerType);
	virtual ~GsTrackerElementMgr(){}
public:
	int TrackerType();

	/// \brief 新增轨迹要素
	virtual void AddTrackerElement(GLOBE_NAME::GsTrackerElement* pEle, bool bRedraw = true) = 0;

	/// \brief 删除轨迹要素
	virtual bool DeleteTrackerElement(GLOBE_NAME::GsTrackerElement* pEle, bool bRedraw = true) = 0;

	/// \brief 删除所有轨迹要素对象
	virtual void Clear() = 0;
};

/// \biref 轨迹工具基类
class GS_API GsTracker : public UTILITY_NAME::GsRefObject
{
	friend class GsTrackerRenderer;
	// 激活状态
	bool m_bActivate;
protected:
	// 轨迹本身元素
	GsTrackerElementPtr m_ptrElement;
	// 轨迹刷新元素
	GsTrackerElementPtr m_ptrRefreshElement;
	// 是否显示计算结果
	bool m_bShowResult;
	// 开启深度测试
	int m_nTrackerType;
	// 是否开启深度测试
	bool m_bDepthTest;
	GsTracker();
public:
	virtual ~GsTracker() {}
	/// \brief 工具激活
	virtual bool Activate(bool b);
	virtual bool Activate();

	/// \brief 是否处于工作状态
	virtual bool IsWorking() { return false; }

	/// \brief 元素本身的符号
	virtual void ElementSymbol(KERNEL_NAME::GsSymbol *pSymbol);
	KERNEL_NAME::GsSymbol* ElementSymbol();

	/// \brief 刷新元素的符号
	void RefreshElementSymbol(KERNEL_NAME::GsSymbol *pSymbol);
	KERNEL_NAME::GsSymbol* RefreshElementSymbol();

	/// \brief 是否绘制地表轨迹
	virtual void SurfaceElement(bool bIsSurface);
	virtual bool SurfaceElement();

	/// \brief 设置轨迹类型
	virtual void TrackerType(int nTrackerType);
	virtual int TrackerType();

	/// \brief 深度测试
	virtual void DepthTest(bool b) { m_bDepthTest = b; }
	virtual bool DepthTest() { return m_bDepthTest; }

	/// \brief 是否显示计算结果
	void ShowResult(bool bShow) { m_bShowResult = bShow; }

	/// \brief 取消操作
	virtual void Cancel() = 0;

	/// \brief 增加点操作（屏幕坐标）
	virtual bool AddPoint(int x, int y, bool bComplete) = 0;
	/// \brief 增加点操作（地理坐标）
	//virtual bool AddPoint(const KERNEL_NAME::GsRawPoint3D& pt, bool bComplete) = 0;

	/// \brief 更新尾节点操作（屏幕坐标）
	virtual bool UpdatePoint(int x, int y) = 0;
	/// \brief 更新尾节点操作（地理坐标）
	//virtual bool UpdatePoint(const KERNEL_NAME::GsRawPoint3D& pt) = 0;

	/// \brief 返回测量结果事件
	UTILITY_NAME::GsDelegate<void(double)> ShowResultEventHandler;

	/// \brief 操作完成事件
	/// \param GsTrackerElement* 当前绘制的轨迹要素对象
	/// \param GsTracker* 当前绘制的轨迹工具
	/// \param int 返回的错误代码，默认为0-成功，非0-错误代码（1图形自相交...）
	UTILITY_NAME::GsDelegate<void(GsTrackerElement*, GsTracker*, unsigned int)> CompleteEventHandler;

protected:
	/// \brief 刷新当前空间要素
	virtual void RefreshSpaceElement();

	/// \brief 绘制当前地表要素
	bool DrawSurfaceElement(KERNEL_NAME::GsCanvas* pCanvas, KERNEL_NAME::GsDisplayTransformation *pDT);	

	/// \brief 修改更新状态
	void UpdateState(bool bUpdate);
	bool UpdateState();

	// 是否是有效的加点操作
	bool IsValidAddPointOperator(bool bComplete);
};
GS_SMARTER_PTR(GsTracker);

/// \breif 轨迹创建工厂类
class GS_API GsTrackerFactory
{
public:
	static GsTrackerFactory& Instance();

	/// \brief 获取轨迹要素管理对象
	GsTrackerElementMgr* GetTrackerElementMgr(int nTrackerType = eTrackerDefault);

	/// \breif 创建点轨迹对象
	GsTrackerPtr CreatePointTracker(int nTrackerType = eTrackerDefault);

	/// \breif 创建线轨迹对象
	GsTrackerPtr CreateLengthTracker(int nTrackerType = eTrackerDefault);

	/// \breif 创建面轨迹对象
	GsTrackerPtr CreateAreaTracker(int nTrackerType = eTrackerDefault);

	/// \breif 创建高度轨迹对象
	GsTrackerPtr CreateAltitudeTracker(int nTrackerType = eTrackerDefault);
private:
	UTILITY_NAME::GsVector<GsTrackerPtr> m_vtTrackerKit;

	// 当前的Tracker
	GsTrackerPtr m_ptrCurTracker;
};

GLOBE_ENDNS