﻿#pragma once
#include "../utility/preconfig.h"
#include <memory> 
#include <object.h> 
#include <geometry.h>
#include <geodatabase.h>
#include <rasterprocess.h>
#include <paintdevice.h>
#include <label.h>
#include <memorymanager.h>
#include <workthread.h>
#include <symbol.h>
#include <pointsymbol.h>
#include <linesymbol.h>
#include <fillsymbol.h>
#include <spatialreference.h>
#include <model.h>
#include <mbvectortile.h>
#include <expression.h>
#include <whereclauseparser.h>
class LayerDrawStyle;


KERNEL_NS
/// \brief 绘制的阶段
enum GsDrawPhase
{
	/// \brief 通用绘制
	eDrawNormal = 1,

	/// \brief Graphic 绘制
	eDrawGraphic = 2,

	/// \brief 绘制选择集
	eDrawSelectionSet = 4,

	/// \brief 绘制自动标注
	eDrawAutoLabel = 8,

	/// \brief 绘制动态数据
	eDrawDynamic = 128,
};


/// \brief 显示对象
/// \details 代表地图的显示设备
class GS_API GsDisplay:public Utility::GsRefObject
{
protected:

	/// \brief 是否调用了StartDrawing
	bool						m_bDrawing;
	/// \brief 背景颜色
	Utility::GsColor						m_BackGroundColor;
	/// \brief 显示坐标转换
	GsDisplayTransformationPtr	m_ptrDT;
	/// \brief 绘制的画布
	GsCanvasPtr					m_ptrCanvas; 

	/// \brief 标注避让容器
	GsLabelContainerPtr			m_ptrLabelContainer;
	/// \brief 几何简化器
	GsGeometrySimplifierPtr	m_ptrSimplifier; 
	/// \brief 屏幕过滤显示
	GsGeometryPtr m_ptrClipGeometry;
protected:
	/// \brief 激发OnAfterStartDrawing事件
	virtual void FireAfterStartDrawing();
	/// \brief 激发OnBeforeEndDrawing事件
	virtual void FireBeforeEndDrawing();
	/// \brief 激发OnAfterEndDrawing事件
	virtual void FireAfterEndDrawing();
	/// \brief 缺省构造
	GsDisplay(); 
public:
	/// \brief 事件，在Display的StartDrawing方法之后激发
	/// \details 参数1 
	Utility::GsDelegate<void(GsDisplay*)> OnAfterStartDrawing;
	/// \brief 在Display结束之前激发
	/// \details 响应此事件向Display上绘制数据不会记录到Cache中
	/// \details 参数1 
	Utility::GsDelegate<void(GsDisplay*)> OnBeforeEndDrawing;
	/// \brief 在Display结束之前激发
	/// \details 响应此事件向Display上绘制数据不会记录到Cache中
	/// \details 参数1 
	Utility::GsDelegate<void(GsDisplay*)> OnAfterEndDrawing;

	/// \brief 事件，当刷新屏幕之前发生
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<void(GsDisplay*, GsCanvas*)> OnBeforeFlush;
	/// \brief 事件，当刷新屏幕之后发生
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<void(GsDisplay*, GsCanvas*)> OnAfterFlush;

public:
	/// \brief 
	/// \param pCanvas 
	/// \param pDT 
	GsDisplay(GsCanvas* pCanvas,GsDisplayTransformation* pDT);
	virtual ~GsDisplay(); 

	/// \brief 几何简化器
	/// \return 
	GsGeometrySimplifier* Simplifier();

	/// \brief 几何简化器
	/// \param p 
	void Simplifier(GsGeometrySimplifier* p);

	/// \brief 获取自动标注避让容器
	/// \return 
	GsLabelContainer* LabelContainer();
	/// \brief 获取自动标注避让容器
	/// \param con 
	void LabelContainer(GsLabelContainer* con);

	/// \brief 当前显示的地理范围
	/// \return 返回显示地物范围的Box 
	virtual GsBox ClipEnvelope();

	/// \brief 获取绘制的背景颜色
	/// \return 返回背景颜色
	virtual Utility::GsColor  BackColor();

	/// \brief 设置绘制的背景颜色
	/// \param c 背景颜色
	virtual void BackColor(const Utility::GsColor& c);

	/// \brief 开始绘制
	virtual void StartDrawing();
	
	/// \brief 是否已经调用了StartDrawing
	/// \return 
	virtual bool IsDrawing();

	/// \brief 结束绘制
	/// \param bFlush 
	virtual void EndDrawing(bool bFlush = true); 

	/// \brief 提交绘制内容
	virtual void Flush();
	
	/// \brief 获取绘制用的画布
	/// \return 
	virtual GsCanvas* Canvas();
	
	/// \brief 获取坐标转换对象
	/// \return 返回坐标转换对象指针
	virtual GsDisplayTransformation* DisplayTransformation(); 

	/// \brief 显示裁切范围
	/// \param pClipGeo 
	virtual void ClipGeometry(GsGeometry* pClipGeo);
	/// \brief 显示裁切范围
	/// \return 
	virtual GsGeometry* ClipGeometry();
};
/// \brief GsDisplayPtr
GS_SMARTER_PTR(GsDisplay);


/// \brief 取消追踪
class GS_API GsTrackCancel:public Utility::GsRefObject
{
	volatile long long m_Tick,m_StartTick;
	volatile unsigned int m_nInterval ;
	volatile bool m_bCanced;
	Utility::GsString m_strName;
	Utility::GsRWLock m_Lock;
public:
	/// \brief 缺省构造
	GsTrackCancel();
	virtual ~GsTrackCancel();

	/// \brief 线程锁,启动写锁定以阻塞所有绘制动作
	/// \return 
	Utility::GsRWLock& Lock();

	/// \brief 获取名称
	/// \return 
	Utility::GsString  Name();
	/// \brief 设置名称
	/// \param strName 
	void Name(const char* strName);

	/// \brief 开始计时
	/// \param nMilliseconds 计时周期，单位毫秒，缺省200毫秒
	virtual void StartTimer(unsigned int nMilliseconds = 200);
	
	/// \brief 结束计时
	/// \return 
	virtual long long FinishTimer();
	/// \brief 是否到达一个计时周期
	/// \return 
	virtual bool TimerFired();
	/// \brief 重置取消状态
	virtual void Reset();
	/// \brief 取消
	virtual void Cancel();

	/// \brief 可否继续
	/// \details 是否调用Cancel进行取消
	/// \return 返回是否处于取消状态
	virtual bool Continue();

	/// \brief 导致计时器立刻被激发
	virtual void FireTimer();
	
public:
	/// \brief 事件，当外部调用Cancel方法时发生
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<void(GsTrackCancel*,const char*)> OnCancel;
	
	/// \brief 事件，当调用StartTimer时发生
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<void(GsTrackCancel*,const char*)> OnStartTimer;
	/// \brief 事件，FinishTimer时发生
	/// \details 参数1 
	/// \details 参数2 
	/// \details 参数3 
	Utility::GsDelegate<void(GsTrackCancel*,const char*,long long)> OnFinishTimer;

};
/// \brief GsTrackCancelPtr
GS_SMARTER_PTR(GsTrackCancel);


/// \brief 屏幕内存缓存
class GS_API GsScreenCache:public Utility::GsRefObject
{
	int m_Order;
	GsImageCanvasPtr m_ptrCanvas;
	volatile bool m_Finished;
	volatile unsigned long long m_FlushTick;

	/// \brief 图层透明度
	volatile float m_fTransparency;
public:
	/// \brief 构造
	/// \param nOrder 
	/// \param imgCanvas 
	GsScreenCache(int nOrder, GsImageCanvas* imgCanvas);
	~GsScreenCache();

	/// \brief 透明度，0-1,0表示完全不透明，1表示完全透明
	/// \return 
	float Transparency();
	/// \brief 透明度，0-1,0表示完全不透明，1表示完全透明
	/// \param v 
	void Transparency(float v);

	/// \brief 提交数据，如果超过指定间隔，单位毫秒
	/// \param nInterval 
	void Flush(int nInterval);

	/// \brief 缓存的顺序
	/// \return 
	int Order();

	/// \brief 获取画布
	/// \return 
	GsImageCanvas* Canvas();

	/// \brief 是否绘制完成
	/// \return 
	bool Finished();

	/// \brief 标识缓存绘制完成
	void FinishCache();

	/// \brief 将其他的缓存位图合并到当前缓存
	/// \param other 
	/// \return 
	bool Merge(GsScreenCache* other);
};
/// \brief GsScreenCachePtr
GS_SMARTER_PTR(GsScreenCache);

/// \brief 屏幕缓存管理
class GS_API GsScreenCacheManager :public Utility::GsRefObject
{
	GsPaintDevicePtr m_ptrPaintDevice;
	Utility::GsSize m_Size;
	int				m_nMaxCache;
	Utility::GsSafeObject<Utility::GsList<GsScreenCachePtr> > m_CacheList;
	Utility::GsList<GsImageCanvasPtr>		m_CanvasCache;

	/// \brief 
	/// \param it 
	void RecoveryOne(Utility::GsList<GsScreenCachePtr>::iterator it);
	/// \brief 
	/// \param it 
	void Recovery(Utility::GsList<GsScreenCachePtr>::iterator it);
public:
	GsScreenCacheManager();
	~GsScreenCacheManager();

	/// \brief 清空所有缓存和状态
	void Reset();

	/// \brief 屏幕大小
	/// \return 
	Utility::GsSize ScreenSize();
	/// \brief 屏幕大小
	/// \param size 
	void ScreenSize(const Utility::GsSize& size);

	/// \brief 屏幕绘制设备
	/// \param pDevice 
	void PaintDevcie(GsPaintDevice* pDevice);
	/// \brief 屏幕绘制设备
	/// \return 
	GsPaintDevice* PaintDevcie();

	/// \brief 创建缓存
	/// \param order 
	/// \return 
	GsScreenCache* CreateCache(int order);
	/// \brief 根据Order寻找缓存
	/// \param order 
	/// \return 
	GsScreenCache* Find(int order);

	/// \brief 最后即最新的缓存
	/// \return 
	GsScreenCache* Back();

	/// \brief 第一个缓存
	/// \return 
	GsScreenCache* Front();

	/// \brief 缓存的数量
	/// \return 
	int Count();

	/// \brief 根据索引获取一个缓存
	/// \param index 
	/// \return 
	GsScreenCache* Cache(int index);

	/// \brief 执行塌陷
	/// \details 已经完成的缓存位图合并为单个位图
	void Collapse();

	/// \brief 将所有的缓存内容绘制到画布上
	/// \param pCanvas 
	/// \param offset 
	void DrawTo(GsCanvas* pCanvas,const Utility::GsPT& offset = Utility::GsPT());

	/// \brief 强制提交所有缓存
	void Flush();

};

/// \brief GsScreenCacheManagerPtr
GS_SMARTER_PTR(GsScreenCacheManager);

/// \brief 屏幕显示对象
/// \details 将可绘制设备封装成为屏幕绘制显示对象
class GS_API GsScreenDisplay:public GsDisplay
{
	GsCanvasPtr m_ptrWindowCanvas;
	GsPaintDevicePtr m_ptrDevice; 
	
	/// \brief 是否处于记录状态
	volatile bool m_bRecording;
	/// \brief 是否处于漫游状态
	volatile bool m_bPaning;

	/// \brief 漫游的开始位置和正在漫游的位置。
	GsRawPoint m_PanStart,m_PanMove;
	Utility::GsLock m_Lock;
	/// \brief 漫游的开始位置和正在漫游的位置。
	Utility::GsPT	m_PanStartPt,m_PanMovePt; 
	
	GsScreenCacheManagerPtr  m_RecordingQueue; 
public:
	/// \brief 根据可绘制设备以及坐标转换对象构造
	/// \param pDevice 可绘制对象
	/// \param pDT 设备坐标转换对象
	GsScreenDisplay(GsPaintDevice* pDevice,GsDisplayTransformation* pDT);
	/// \brief 
	/// \param pDT 
	GsScreenDisplay(GsDisplayTransformation* pDT);
	GsScreenDisplay();

	virtual ~GsScreenDisplay();
	
	/// \brief 绑定设备，返回旧设备
	/// \param pDevice 
	/// \return 
	GsPaintDevicePtr BindDevice(GsPaintDevice* pDevice);

	/// \brief 获取Display绑定的设备
	/// \return 
	GsPaintDevice* PaintDevice();

	/// \brief 开始记录
	/// \param order 
	/// \return 
	GsImageCanvas* BeginRecording(int order);
	
	/// \brief 最后用于记录的画布
	/// \return 
	GsImageCanvas* RecordingCanvas();
	 

	/// \brief 结束记录
	void EndRecording();

	/// \brief 清空记录缓存
	void ClearRecordingCache();

	/// \brief 提交记录缓存
	void FlushRecordingCache();

	/// \brief 从地理坐标开始漫游
	/// \param x 地理x坐标
	/// \param y 地理y坐标
	virtual void PanStart(double x,double y);

	/// \brief 漫游到地理坐标
	/// \param x 地理x坐标
	/// \param y 地理y坐标
	virtual void PanMoveTo(double x,double y);

	/// \brief 停止漫游
	/// \return 返回漫游结束时应该实现的地理范围
	virtual GsBox PanStop();

	/// \brief 
	/// \return 
	virtual bool HasStartPan();
	
	/// \brief 将缓存的内容绘制到设备上
	/// \param pt 绘制偏移的像素坐标
	virtual void Paint(const Utility::GsPT& pt = Utility::GsPT());

	/// \brief 当绘制设备发生变化时
	virtual void OnSizeChanged();
	/// \brief 开始绘制
	virtual void StartDrawing();
	/// \brief 结束绘制
	/// \param bFlush 
	virtual void EndDrawing(bool bFlush = true);
	/// \brief 提交绘制结果到屏幕
	virtual void Flush();

};
/// \brief GsScreenDisplayPtr
GS_SMARTER_PTR(GsScreenDisplay);


/// \brief 跟新消息代理器。
class GS_API GsUpdateAgent: public Utility::GsRefObject
{
	/// \brief 记录发送了多少次更新请求
	Utility::GsAtomic<int> m_UpdateRef;
	int			m_UpdatePeriod;
	Utility::GsStopWatch m_Watch;
	Utility::GsRWLock m_Lock;
	GsBox		m_Extent;
	double		m_Res;
public:
	/// \brief 构造函数
	/// \param nUpdatePeriodMS 间隔多久发送更新消息，单位毫秒
	GsUpdateAgent(int nUpdatePeriodMS = 40);
	
	virtual ~GsUpdateAgent();

	/// \brief 判断是否需要更新
	/// \param bClearFlag 
	/// \param extent 
	/// \return 
	bool NeedUpdate(bool bClearFlag = true,GsBox* extent = NULL);

	/// \brief 清空更新标识
	void ClearUpdateFlag();

	/// \brief 需要刷新是调用,不会立刻导致刷新
	/// \param host GsUpdateAgent对象自身
	/// \param nReason 更新理由，保留参数
	/// \param extent 更新范围
	/// \param res 分辨率
	/// \param param 保留扩展参数
	void FireNeedUpdate(GsRefObject* host, int nReason, const GsBox& extent, double res, void* param);


	/// \brief 当需要更新是发生
	/// \details 参数1， GsUpdateAgent对象自身
	/// \details 参数2， 更新理由，保留参数
	/// \details 参数3， 更新范围
	/// \details 参数4， 分辨率
	/// \details 参数5， 保留扩展参数
	/// \details 返回值， 返回true则清除更新标识
	Utility::GsDelegate<bool(GsRefObject*,int,const GsBox& ,double,void*)> OnNeedUpdate;
};
/// \brief GsUpdateAgentPtr
GS_SMARTER_PTR(GsUpdateAgent);

/// \brief 图形的抽象基类
class GS_API GsLayer:public Utility::GsRefObject
{
protected:
	/// \brief 更新代理
	GsUpdateAgentPtr m_ptrUpdateAgent;
	/// \brief 图层的名称
	Utility::GsString m_strName;
	
	/// \brief 图层的别名
	Utility::GsString m_strAliasName;

	/// \brief 图层是否可见
	volatile bool m_bVisible;
	/// \brief 最小可见比例尺
	volatile double m_dblMinScale;
	/// \brief 最大可见比例尺
	volatile double m_dblMaxScale;
	
	/// \brief 参考比例尺
	volatile double m_dblReferenceScale;

	/// \brief 用户附加数据。
	Utility::GsAny m_Tag;

	GsGeometryPtr m_ptrClipGeometry;

	/// \brief 图层透明度
	volatile float m_fTransparency;
	/// \brief 内部绘制入口
	/// \details 子类通过覆盖此函数实现绘制。
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \return 
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);

	/// \brief 激发需要刷新时间
	/// \param extent 
	/// \param res 
	void FireOnNeedUpdate(const GsBox& extent,double res);

	GsLayer();
public:
	
	virtual ~GsLayer();
	/// \brief 图层的名称
	/// \return 
	virtual Utility::GsString Name();
	/// \brief 设置图层的名称
	/// \param strName 
	virtual void Name(const char* strName);

	/// \brief 图层的别名
	/// \return 
	virtual Utility::GsString AliasName();
	/// \brief 设置图层的别名
	/// \param strName 
	virtual void AliasName(const char* strName);

	/// \brief 图层是否可见
	/// \return 
	virtual bool Visible();
	/// \brief 设置图层是否可见
	/// \param bVisible 
	virtual void Visible(bool bVisible);

	/// \brief 参考比例尺
	/// \return 
	virtual double ReferenceScale();
	/// \brief 参考比例尺
	/// \param dblScale 
	virtual void ReferenceScale(double dblScale);

	/// \brief 图层最小可见比例尺
	/// \return 
	virtual double MinScale();
	/// \brief 设置图层最小可见比例尺
	/// \param dblScale 
	virtual void MinScale(double dblScale);

	/// \brief 图层最大可见比例尺
	/// \return 
	virtual double MaxScale();
	/// \brief 设置图层最大可见比例尺
	/// \param dblScale 
	virtual void MaxScale(double dblScale);
	
	/// \brief 图层的名称
	/// \return 
	virtual Utility::GsAny Tag();
	/// \brief 设置图层的名称
	/// \param any 
	virtual void Tag(const Utility::GsAny& any);

	/// \brief 是否有效
	/// \return 
	virtual bool IsValid();

	/// \brief 图层的最大范围,以图层的空间参考显示
	/// \param pTargetSR 
	/// \return 
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0) = 0;
	
	/// \brief 图层是否存在选择集
	/// \return 
	virtual bool HasSelection() = 0;

	/// \brief 图层的空间参考
	/// \return 
	virtual GsSpatialReference* SpatialReference();

	/// \brief 图形绘制入口
	/// \param pDisplay 绘制对象
	/// \param pCancel 绘制取消对象
	/// \param eDrawPhase 绘制方式
	/// \return 
	virtual bool Draw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);

	/// \brief 判断图层是否需要绘制
	/// \param pDisplay 
	/// \param eDrawPhase 
	/// \return 
	virtual bool NeedDraw(GsDisplay* pDisplay, GsDrawPhase eDrawPhase);

	/// \brief 克隆图层
	/// \return 
	virtual Utility::GsSmarterPtr<GsLayer> Clone() = 0;

	/// \brief 显示裁切范围
	/// \param pClipGeo 
	virtual void ClipGeometry(GsGeometry* pClipGeo);
	/// \brief 显示裁切范围
	/// \return 
	virtual GsGeometry* ClipGeometry(); 

	/// \brief 更新代理
	/// \return 
	GsUpdateAgent* UpdateAgent();

	/// \brief 设置更新代理
	/// \details 设置更新代理允许图层主动对外发送需要刷新的消息
	/// \param agent 
	void UpdateAgent(GsUpdateAgent* agent);
	/// \brief 透明度，0-1,0表示完全透明，1表示完全不透明
	/// \param dblTrans 
	void Transparency(float dblTrans);
	/// \brief 透明度，0-1,0表示完全透明，1表示完全不透明
	/// \return 
	float Transparency();
};
/// \brief GsLayerPtr
GS_SMARTER_PTR(GsLayer);

  

/// \brief 排序图层组符号分级
struct GS_API GsSymbolLevel
{
	/// \brief 符号图层索引
	int LayerIndex;
	/// \brief 符号索引
	int SymbolIndex;
	/// \brief 分级索引
	int ID;
	/// \brief 初始化
	/// \param nLyrIndex 
	/// \param nSymIndex 
	/// \param nID 
	GsSymbolLevel(int nLyrIndex, int nSymIndex , int nID);
};
 



/// \brief 简化类型
enum GsSimplifyType
{
	/// \brief 不执行简化
	eDoNotSimplify,
	/// \brief 保拓扑简化
	eTopologyPreservingSimplify
};

class GS_API GsActiveView :public Utility::GsRefObject
{
protected:
	/// \brief 屏幕显示对象
	GsScreenDisplayPtr m_ptrDisplay;
	/// \brief 绘制取消对象
	GsTrackCancelPtr m_TrackCancel;

	GsActiveView();
public:
	virtual ~GsActiveView() {}


	/// \brief 取消对象指针
	/// \return 
	virtual GsTrackCancel* TrackCancel();

	/// \brief 获取屏幕显示对象
	/// \return 
	virtual GsScreenDisplay* ScreenDisplay();

	/// \brief 强制刷新地图
	/// \details 使地图失效，强制刷新
	virtual void Update() = 0;
	/// \brief 绘制地图
	/// \details 如果地图数据未失效，则直接绘制缓冲的位图，反之则重新绘制
	/// \param eReason 
	virtual void Paint(GsDrawPhase eReason = eDrawNormal) = 0;

	/// \brief 使地图失效
	virtual void Invalidate() = 0;

	/// \brief 判断是否是否已经失效
	/// \return 
	virtual bool IsValid() = 0;

	/// \brief 将地图数据绘制到输入的Display上。
	/// \details 调用者需要在外部输入启动Display的StartDraw，并在输出结束后调用EndDraw。
	/// \param pDisp 需要输出数据的Display
	/// \param pCancel 取消对象
	/// \return 
	virtual bool Output(GsDisplay* pDisp, GsTrackCancel* pCancel) = 0;

	/// \brief 全图范围
	/// \details 所有图层的范围合并的范围
	/// \return 
	virtual GsBox FullExtent() = 0;

	/// \brief 设置当前显示范围
	/// \details 会取消当前地图绘制，同时使得地图失效，但不会立刻刷新地图，需要额外调用Paint或者Update刷新地图
	/// \param extent 
	virtual void ViewExtent(const GsBox& extent);

	/// \brief 获取当前显示范围
	/// \details 相当于调用方法Display()->DisplayTransformation()->MapExtent();
	/// \return 
	virtual GsBox ViewExtent();

};
/// \brief GsActiveViewPtr
GS_SMARTER_PTR(GsActiveView);

/// \brief 图层集合
class GS_API GsLayerCollection:public Utility::GsRefObject
{
protected:
	/// \brief 图形列表
	UTILITY_NAME::GsVector<GsLayerPtr > m_lstLayers;
	UTILITY_NAME::GsRWLock m_Lock;
protected:
	
	/// \brief 当图层数量、顺序发生变化时发生。
	virtual void FireOnLayerChanged();
	/// \brief 当增加图层后发生
	/// \param lyr 
	/// \param index 
	virtual void FireOnAddLayer(GsLayer* lyr,int index);
	/// \brief 当移除图层后发生
	/// \param lyr 
	virtual void FireOnRemoveLayer(GsLayer* lyr);
	 
public:
	/// \brief 当图层数量、顺序发生变化时发生。
	/// \details 参数1 
	Utility::GsDelegate<void(GsLayerCollection*)> OnLayerChanged;
	/// \brief 当增加图层后发生
	/// \details 参数1 
	/// \details 参数2 
	/// \details 参数3 
	Utility::GsDelegate<void(GsLayerCollection*,GsLayer*,int)> OnAddLayer;
	/// \brief 当移除图层后发生
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<void(GsLayerCollection*, GsLayer*)> OnRemoveLayer;

public:
	GsLayerCollection();
	virtual ~GsLayerCollection();

	/// \brief 图层的数量
	/// \return 
	int Count();

	/// \brief 根据索引获得图层对象
	/// \param i 
	/// \return 
	GsLayer* Layer(int i);

	/// \brief 添加一个图层到图层末尾
	/// \param lyr 
	/// \return 
	bool Add(GsLayer* lyr);


	/// \brief 在特定为位置插入一个图层
	/// \param i 
	/// \param lyr 
	/// \return 
	bool Insert(int i,GsLayer* lyr);

	/// \brief 清除图层
	void Clear();

	/// \brief 删除指定的图层
	/// \param i 
	/// \return 
	bool Remove(int i);

	/// \brief 删除指定的图层
	/// \param lyr 
	/// \return 
	bool Remove(GsLayer* lyr);

	/// \brief 将图层移动到特定的位置
	/// \param lyr 
	/// \param i 
	/// \return 
	bool Move(GsLayer* lyr, int i);

	/// \brief 获取图层指针在集合中的索引
	/// \param lyr 
	/// \return 
	int IndexOf(GsLayer* lyr);


	/// \brief 克隆图层集合
	/// \return 
	Utility::GsSmarterPtr<GsLayerCollection> Clone();

	/// \brief 获取图层数组
	/// \return 
	UTILITY_NAME::GsVector<GsLayerPtr>* Layers();
	

};
/// \brief GsLayerCollectionPtr
GS_SMARTER_PTR(GsLayerCollection);


/// \brief 复合图层
class GS_API GsMultiLayer :public GsLayer
{

protected:
	GsLayerCollectionPtr m_Layers;

	/// \brief 内部绘制入口
	/// \details 子类通过覆盖此函数实现绘制。
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \return 
	virtual bool InnerDraw(GsDisplay* pDisplay, GsTrackCancel* pCancel, GsDrawPhase eDrawPhase);
public:
	GsMultiLayer();
	virtual ~GsMultiLayer();
	/// \brief 获取图层列表对象指针
	/// \return 
	UTILITY_NAME::GsVector<GsLayerPtr >* Layers();
	/// \brief 获取图层列表对象指针
	/// \return 
	GsLayerCollection* LayerCollection();

	/// \brief 图层的最大范围
	/// \param pTargetSR 
	/// \return 
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0);
	/// \brief 图层是否存在选择集
	/// \return 
	virtual bool HasSelection();
	/// \brief 图层的空间参考
	/// \return 
	virtual GsSpatialReference* SpatialReference();

	/// \brief 是否有效
	/// \return 
	virtual bool IsValid();

	/// \brief 克隆图层
	/// \return 
	virtual GsLayerPtr Clone();

};
/// \brief GsMultiLayerPtr
GS_SMARTER_PTR(GsMultiLayer);


/// \brief 排序图层组符号分级
class GS_API GsReorderLayer : public GsMultiLayer
{
	UTILITY_NAME::GsVector<GsSymbolLevel> m_LayerSymIndexs;
	bool m_EnableReorder;
protected:
	/// \brief 内部绘制入口
	/// \details 子类通过覆盖此函数实现绘制。
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \return 
	virtual bool InnerDraw(GsDisplay* pDisplay, GsTrackCancel* pCancel, GsDrawPhase eDrawPhase);
public:
	GsReorderLayer();
	virtual ~GsReorderLayer();
	/// \brief 清除排序图层组符号分级设置,默认和mutillayer 一样绘制
	void ClearOrder();
	/// \brief 添加一个分级
	/// \param level 分级描述
	void AddOrder(const GsSymbolLevel & level);
	/// \brief 设置某一位置的索引
	/// \param nIndex 位置索引
	/// \param level 分级描述
	void Order(int nIndex, const GsSymbolLevel & level);
	/// \brief 取GsSymbolLevel个数
	/// \return 
	int OrderCount();
	/// \brief 通过索引获取GsSymbolLevel
	/// \param nIndex 位置索引
	/// \return 返回值，GsSymbolLevel 分级描述
	GsSymbolLevel& Order(int nIndex);
	/// \brief 获取GsSymbolLevel 位置索引
	/// \param nIndex 分级描述
	/// \return 返回值，int 索引值
	int Order(const GsSymbolLevel& nIndex);
	/// \brief 通过索引移除GsSymbolLevel 
	/// \param nIndex 索引值
	void RemoveSymbolLevel(int nIndex);
	/// \brief 
	/// \return 
	bool EnableReorder();
	/// \brief 设置是否开启排序绘制
	/// \param bVal 
	void EnableReorder(bool bVal);
	/// \brief 克隆图层
	/// \return 
	virtual GsLayerPtr Clone();
};

/// \brief GsReorderLayerPtr
GS_SMARTER_PTR(GsReorderLayer);

/// \brief 单个瓦片缓存
class GsTileCacheContext :public UTILITY_NAME::GsRefObject
{
	Utility::GsLock m_Lock;
	KERNEL_NAME::GsTileClassPtr m_ptrTileClass;
	KERNEL_NAME::GsTilePtr m_ptrTile;
	int m_Commit;
	/// \brief 
	/// \return 
	KERNEL_NAME::GsTile* CreateTile();
	/// \brief 
	void StoreTile();

public:
	/// \brief 
	/// \param pTileClass 
	GsTileCacheContext(KERNEL_NAME::GsTileClass* pTileClass);
	~GsTileCacheContext();

	/// \brief 查询瓦片数据
	/// \param key 
	/// \param buffer 
	/// \return 
	bool QueryTile(const Utility::GsQuadKey& key, Utility::GsByteBuffer* buffer);
	/// \brief 保存瓦片
	/// \param key 
	/// \param data 
	/// \param nLen 
	void SaveTile(const Utility::GsQuadKey& key, const unsigned char* data, int nLen);
	
	/// \brief 判断瓦片是否存在
	/// \param key 
	/// \return 
	bool Exists(const Utility::GsQuadKey& key);


};
/// \brief GsTileCacheContextPtr
GS_SMARTER_PTR(GsTileCacheContext);

/// \brief 文件瓦片缓存
class GS_API GsFileTileCache:public Utility::GsRefObject
{
	KERNEL_NAME::GsGeoDatabasePtr m_ptrGDB;
	UTILITY_NAME::GsSafeObject<Utility::GsStlMap<unsigned long long, GsTileCacheContextPtr > > m_mapCacheTileCache;
	/// \brief 
	/// \return 
	KERNEL_NAME::GsGeoDatabase* GDB();
	/// \brief 
	/// \param dataHash 
	/// \return 
	KERNEL_NAME::GsTileClassPtr TileClass(unsigned long long dataHash);
	/// \brief 
	/// \param hash 
	/// \param bEnsure 
	/// \return 
	GsTileCacheContextPtr TileContext(unsigned long long hash,bool bEnsure= true);
	UTILITY_NAME::GsAtomic<int> m_BaseMapRef;

	Utility::GsSimpleLRUCache<unsigned long long, Utility::GsCachedImagePtr> m_ImageTileCache;
public:
	GsFileTileCache();
	/// \brief 全局的瓦片文件缓存
	/// \return 
	static GsFileTileCache* Singleton();

	/// \brief 是否存在
	/// \param nDSHash 
	/// \param key 
	/// \return 
	bool Exists(unsigned long long nDSHash, const Utility::GsQuadKey& key);

	/// \brief 查询一个瓦片
	/// \param nDSHash 
	/// \param key 
	/// \param buffer 
	/// \return 
	bool QueryTile(unsigned long long nDSHash, const Utility::GsQuadKey& key,Utility::GsByteBuffer* buffer);

	/// \brief 查询一个影像类型瓦片
	/// \param nDSHash 
	/// \param key 
	/// \return 
	Utility::GsCachedImagePtr  QueryTile(unsigned long long nDSHash, const Utility::GsQuadKey& key);

	/// \brief 保存一个瓦片
	/// \param hDSHash 
	/// \param key 
	/// \param data 
	/// \param nLen 
	void SaveTile(unsigned long long hDSHash, const Utility::GsQuadKey& key, const unsigned char* data, int nLen);
	
	/// \brief 增加一个引用
	void AddReference();
	/// \brief 减少一个引用
	void ReleaseReference();

};
/// \brief GsFileTileCachePtr
GS_SMARTER_PTR(GsFileTileCache);

/// \brief 底图图层，以挖片化的方式显示
class GS_API GsBaseMapLayer :public GsMultiLayer
{
protected:
	bool				m_EnableBaseMap;
	unsigned long long m_DataHash; 
	GsPyramidPtr m_ptrPyramid;
	GsPyramidPtr m_ptrPyramidTemp;
	Utility::GsWorkThread* m_BackgroundWorker;

	/// \brief 
	/// \param pDisplay 
	/// \return 
	GsPyramid*  EnsurePyramid(GsDisplay* pDisplay);
	
	/// \brief 内部绘制入口
	/// \details 子类通过覆盖此函数实现绘制。
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \return 
	virtual bool InnerDraw(GsDisplay* pDisplay, GsTrackCancel* pCancel, GsDrawPhase eDrawPhase);
public:
	/// \brief 
	/// \param pPyramid 
	GsBaseMapLayer(GsPyramid* pPyramid = NULL);
	~GsBaseMapLayer();
	
	/// \brief 获取数据内容哈希
	/// \return 
	unsigned long long DataHash();
	/// \brief 设置数据内容哈希
	/// \param hash 
	void DataHash(unsigned long long hash);

	/// \brief 是否作为底图,如果不作为底图，那么绘制行为和MultiLayer保持一致
	/// \return 
	bool EnableBaseMap();
	/// \brief 是否作为底图,如果不作为底图，那么绘制行为和MultiLayer保持一致
	/// \param b 
	void EnableBaseMap(bool b);

	/// \brief 克隆图层
	/// \return 
	virtual GsLayerPtr Clone();
};
/// \brief GsBaseMapLayerPtr
GS_SMARTER_PTR(GsBaseMapLayer);

/// \brief 代表一个图层的的渲染相关信息
struct GS_API GsLayerRenderItem
{
	/// \brief 图层渲染的顺序
	int Order;

	/// \brief 要渲染的图层
	GsLayerPtr Layer;

	/// \brief 渲染的透明度
	float  Transparency;

	GsLayerRenderItem();
	/// \brief 
	/// \param item 
	GsLayerRenderItem(const GsLayerRenderItem& item);
	/// \brief 
	/// \param o 
	/// \param lyr 
	/// \param trans 
	GsLayerRenderItem(int o, GsLayer* lyr, float trans=1);

};

/// \brief 图层渲染器，提供多种模式渲染地图图层
class GS_API GsLayerRenderer:public Utility::GsRefObject
{
protected:
	GsDisplayPtr m_ptrDisplay;
	GsTrackCancelPtr m_ptrTrack;
	GsDrawPhase m_eDrawReason;
	GsScreenCacheManagerPtr  m_RecordingQueue;
	GsLayerRenderer();
	/// \brief 执行渲染
	/// \param eDrawReason 
	/// \param lyrColl 
	virtual void OnExecuteRender(GsDrawPhase eDrawReason, GsLayerCollection* lyrColl) = 0;

public:
	~GsLayerRenderer();
	
	/// \brief 执行渲染
	/// \param pDisplay 
	/// \param pTrack 
	/// \param eDrawReason 
	/// \param lyrColl 
	virtual void ExecuteRender(GsDisplay* pDisplay, GsTrackCancel* pTrack, GsDrawPhase eDrawReason,GsLayerCollection* lyrColl);
};
/// \brief GsLayerRendererPtr
GS_SMARTER_PTR(GsLayerRenderer);


/// \brief 并行化图层渲染器
class GS_API GsParalleLayerRenderer :public GsLayerRenderer
{
	Utility::GsAtomic<int>		m_FinishCounter;
	Utility::GsBackgroundPtr m_ptrBackground;
	Utility::GsList<Utility::GsBackgroundTaskPtr> m_ListTask;
	Utility::GsSafeObject<Utility::GsList<GsLayerRenderItem > > m_LayerList;
protected:
	
	/// \brief 执行渲染
	/// \param eDrawReason 
	/// \param lyrColl 
	virtual void OnExecuteRender(GsDrawPhase eDrawReason, GsLayerCollection* lyrColl);
public:
	GsParalleLayerRenderer();

};
/// \brief GsParalleLayerRendererPtr
GS_SMARTER_PTR(GsParalleLayerRenderer);

/// \brief 顺序图层渲染器
class GS_API GsSequentialLayerRenderer :public GsLayerRenderer
{
	GsDisplayPtr m_ptrProxyDiplay;
protected:
	/// \brief 执行渲染
	/// \param eDrawReason 
	/// \param lyrColl 
	virtual void OnExecuteRender(GsDrawPhase eDrawReason, GsLayerCollection* lyrColl);

};
/// \brief GsSequentialLayerRendererPtr
GS_SMARTER_PTR(GsSequentialLayerRenderer);




/// \brief 地图对象
/// \details 多个图层绘制
class GS_API GsMap:public GsActiveView,private Utility::GsWorkThread
{
	volatile bool m_bIsValid; 
	Utility::GsSignaler m_FinishSignaler;
	volatile bool m_bDrawing;	
	GsSimplifyType m_SimplifyType;
	volatile GsDrawPhase m_ePaintReason;
	GsLayerRendererPtr m_ptrLayerRenderer;
private:

	/// \brief 在Display结束之前激发
	/// \details 响应此事件向Display上绘制数据不会记录到Cache中
	/// \param disp 
	void OnDrawDyanmic(GsDisplay* disp) ;

	/// \brief 
	/// \return 
	virtual bool Execute();
protected:
	/// \brief 图形列表
	GsLayerCollectionPtr    m_baseMapLayers;

	/// \brief 处于动态图层和普通图层之间的图层或者图层组,此图层不暴露在Layer集合中,由二次开发者根据业务实现
	GsLayerCollectionPtr	m_GraphicLayers;

	/// \brief 热点图层列表
	GsLayerCollectionPtr	m_DynamicLayers;
	
public:
	/// \brief 根据屏幕显示对象构造
	GsMap();

	/// \brief 根据屏幕显示对象构造
	/// \param pDisplay 
	GsMap(GsScreenDisplay* pDisplay);
	virtual ~GsMap();

	/// \brief 图层渲染器,实现具体的图层渲染过程
	/// \return 
	GsLayerRenderer* LayerRenderer();
	/// \brief 图层渲染器,实现具体的图层渲染过程
	/// \param render 
	void LayerRenderer(GsLayerRenderer* render);


	/// \brief 简化类型
	/// \return 
	GsSimplifyType SimplifyType();
	/// \brief 简化类型
	/// \param eType 
	void SimplifyType(GsSimplifyType eType);

	
	/// \brief 取消当前绘制
	virtual void Cancel();
	/// \brief 地图是否处于绘制状态
	/// \return 
	virtual bool IsDrawing();

	/// \brief 获取底图图层列表
	/// \return 
	UTILITY_NAME::GsVector<GsLayerPtr >* Layers();

	/// \brief 动态图层列表
	/// \return 
	UTILITY_NAME::GsVector<GsLayerPtr>* DynamicLayers();
	/// \brief Graphics图层列表
	/// \return 
	UTILITY_NAME::GsVector<GsLayerPtr>* GraphicsLayers();

	/// \brief 获取底图图层列表
	/// \return 
	GsLayerCollection * LayerCollection();

	/// \brief 动态图层列表
	/// \return 
	GsLayerCollection* DynamicLayerCollection();

	/// \brief 处于动态图层和普通图层之间的图层或者图层组,此图层不暴露在Layer集合中,由二次开发者根据业务实现
	/// \return 
	GsLayerCollection* GraphicsLayerCollection();

	/// \brief 强制刷新地图
	/// \details 使地图失效，强制刷新
	virtual void Update();
	/// \brief 绘制地图
	/// \details 如果地图数据未失效，则直接绘制缓冲的位图，反之则重新绘制
	/// \param eReason 
	virtual void Paint(GsDrawPhase eReason = eDrawNormal);

	/// \brief 使地图失效
	virtual void Invalidate();

	/// \brief 判断是否是否已经失效
	/// \return 
	virtual bool IsValid();

	/// \brief 全图范围
	/// \details 所有图层的范围合并的范围
	/// \return 
	virtual GsBox FullExtent();
	
	/// \brief 设置当前显示范围
	/// \details 会取消当前地图绘制，同时使得地图失效，但不会立刻刷新地图，需要额外调用Paint或者Update刷新地图
	/// \param extent 
	virtual void ViewExtent(const GsBox& extent);

	/// \brief 获取当前显示范围
	/// \details 相当于调用方法Display()->DisplayTransformation()->MapExtent();
	/// \return 
	virtual GsBox ViewExtent();

	
	/// \brief 将地图数据绘制到输入的Display上。
	/// \details 调用者需要在外部输入启动Display的StartDraw，并在输出结束后调用EndDraw。
	/// \param pDisp 需要输出数据的Display
	/// \param pCancel 取消对象
	/// \return 
	virtual bool Output(GsDisplay* pDisp,GsTrackCancel* pCancel);

	
	/// \brief 克隆地图对象为新的对象
	/// \return 
	Utility::GsSmarterPtr<GsMap> Clone();

	/// \brief 获取当前绘制内容类型
	/// \return 
	GsDrawPhase DrawPhase();



	
public:
	/// \brief 当完成地图绘制后发生。
	/// \details 参数1 
	Utility::GsDelegate<void(GsMap*)> OnFinishDrawing;

private:
	/// \brief 初始化标注避让数据
	void InitLabelAvoidData();
};
/// \brief GsMapPtr
GS_SMARTER_PTR(GsMap);


/// \brief 渲染器，实现数据的渲染
class GS_API GsRendition:public Utility::GsRefObject
{
protected:
	GsRendition();
	GsDisplayPtr m_ptrDisplay;

	/// \brief 名称
	Utility::GsString m_strName;
	/// \brief 属性过滤条件
	Utility::GsString m_strWhere;
	/// \brief 标注是否可见
	bool m_bVisible;
	/// \brief 标注最小可见比例尺
	volatile double m_dblTextMinScale;
	/// \brief 标注最大可见比例尺
	volatile double m_dblTextMaxScale;
	/// \brief 过滤表达式
	GsExpressionPtr m_ptrWhereExpression;

	GsRowAttributeVisitor m_RowVistor;
public:
	virtual ~GsRendition();
	/// \brief 开始渲染
	/// \param pDisplay 
	virtual void Begin(GsDisplay* pDisplay);
	
	/// \brief 结束渲染
	virtual void End();

public:
	/// \brief 名称
	/// \param strName 
	void Name(const char* strName);
	/// \brief 名称
	/// \return 
	Utility::GsString Name();

	/// \brief 条件查询语句
	/// \param strWhere 
	void WhereClause(const char* strWhere);
	/// \brief 条件查询语句
	/// \return 
	Utility::GsString WhereClause();

	/// \brief 标注是否可见
	/// \param bVisible 
	void Visible(bool bVisible);
	/// \brief 标注是否可见
	/// \return 
	bool Visible();

	/// \brief 设置/读取标注显示最小比例尺
	/// \param dblScale 
	void TextMinScale(double dblScale);
	/// \brief 
	/// \return 
	double TextMinScale();

	/// \brief 设置/读取标注显示最大比例尺
	/// \param dblScale 
	void TextMaxScale(double dblScale);
	/// \brief 
	/// \return 
	double TextMaxScale();
};
/// \brief GsRenditionPtr
GS_SMARTER_PTR(GsRendition);
/// \brief 矢量数据渲染器
class GS_API GsFeatureRendition:public GsRendition
{
protected:
	GsFeatureRendition();
public:
	virtual ~GsFeatureRendition();
	/// \brief 渲染一个地物
	/// \param pFea 
	/// \param pSym 
	/// \return 
	virtual bool Render(GsFeature* pFea,GsSymbol* pSym);
};

/// \brief GsFeatureRenditionPtr
GS_SMARTER_PTR(GsFeatureRendition);



/// \brief 标注渲染器
class GS_API GsLabelRendition :public GsFeatureRendition
{
	GsLabelPropertyPtr m_ptrLabelProperty;
	GsWhereClauserParser m_WhereParser;
protected:
	GsLabelRendition();

	/// \brief 
	/// \param pFea 
	void InitWhereParser(GsFeature* pFea);
public:
	/// \brief 
	/// \param pLabelProperty 
	GsLabelRendition(GsLabelProperty* pLabelProperty);
	virtual ~GsLabelRendition();
	/// \brief 开始渲染
	/// \param pDisplay 
	virtual void Begin(GsDisplay* pDisplay);
	/// \brief 结束渲染
	virtual void End();
	/// \brief 渲染一个地物
	/// \param pFea 
	/// \param pSym 
	/// \return 
	virtual bool Render(GsFeature* pFea, GsSymbol* pSym);

	/// \brief 返回 LabelProperty
	/// \return 
	virtual GsLabelProperty* LabelProperty();

	/// \brief 设置 LabelProperty
	/// \param pLabelProperty 
	virtual void LabelProperty(GsLabelProperty* pLabelProperty);
};
/// \brief GsLabelRenditionPtr
GS_SMARTER_PTR(GsLabelRendition);


/// \brief 多标注渲染器
/// \brief 根据多个GsLabelProperty计算位置
class GS_API GsMultiLabelRendition : public GsLabelRendition
{
	Utility::GsVector<GsLabelPropertyPtr> m_ptrLabelPropertys;
public:
	GsMultiLabelRendition();
	virtual ~GsMultiLabelRendition();
	/// \brief 开始渲染
	/// \param pDisplay 
	virtual void Begin(GsDisplay* pDisplay);
	/// \brief 结束渲染
	virtual void End();
	/// \brief 渲染一个地物
	/// \param pFea 
	/// \param pSym 
	/// \return 
	virtual bool Render(GsFeature* pFea, GsSymbol* pSym);
	/// \brief 返回 LabelProperty
	/// \param nIndex 
	/// \return 
	virtual GsLabelProperty* LabelProperty(int nIndex);
	/// \brief 设置 LabelProperty
	/// \param nIndex 
	/// \param pLabelProperty 
	virtual void LabelProperty(int nIndex,GsLabelProperty* pLabelProperty);
	/// \brief 设置 移除一个LabelProperty
	/// \param nIndex 
	virtual void Remove(int nIndex);
	/// \brief 清空所有LabelProperty
	/// \param nIndex 
	virtual void Clear(int nIndex);
};
/// \brief GsLabelRenditionPtr
GS_SMARTER_PTR(GsMultiLabelRendition);
/// \brief 渲染器方式
enum GsRenditionMode
{
	/// \brief 单渲染器
	eSingleRendition,
	/// \brief 多渲染器
	eMultiRendition,
};



enum GsLegendItemStyle
{
	/// \brief 水平
	Horizontal,
	/// \brief 水平并成一个bar,label 和 descrition
	HorizontalBar,
	/// \brief 嵌套
	Nested,
	/// 垂直排列
	Vertical,
};

enum GsRectanglePosition
{
	eTopSide = 1,
	eBottomSide = 2,
	eLeftSide = 3,
	eRightSide = 4
};

/// \brief 单个图例信息样式,
/// \details 每个图例组GsLegendGroup 有多个GsLegendClass,
/// \details GsLegendClassFormat 为GsLegendClass的样式
class GS_API GsLegendClassFormat :public Utility::GsRefObject
{
private:
	/// \brief 描述信息所用的文本符号 
	GsTextSymbolPtr m_ptrDescriptionSymbol;
	/// \brief 标签所用的文本符号 
	GsTextSymbolPtr m_ptrLabelSymbol;
	/// \brief 单个图例图块符号 
	GsSymbolPtr m_ptrPatchSymbol;

public:
	GsLegendClassFormat();
	virtual ~GsLegendClassFormat();

	/// \brief 得到描述信息所用的文本符号
	/// \return 
	GsTextSymbol* DescriptionSymbol();
	/// \brief 设置描述信息所用的文本符号
	/// \param pTextSymbol 
	void DescriptionSymbol(GsTextSymbol *pTextSymbol);

	/// \brief 得到标签所用的文本符号 
	/// \return 
	GsTextSymbol* LabelSymbol();
	/// \brief 设置标签所用的文本符号 
	/// \param pTextSymbol 
	void LabelSymbol(GsTextSymbol *pTextSymbol);

	/// \brief 得到图块符号
	/// \return 
	GsSymbol* PatchSymbol();
	/// \brief 设置图块符号
	/// \param pSym 
	void PatchSymbol(GsSymbol* pSym);

};
GS_SMARTER_PTR(GsLegendClassFormat);

/// \brief 单个图例信息,
/// \details 每个图例组GsLegendGroup 有多个GsLegendClass,
class GS_API GsLegendClass :public Utility::GsRefObject
{
private:
	/// \brief 图例信息样式
	GsLegendClassFormatPtr m_ptrLegendClassFormat;
	/// \brief 描述文本内容
	Utility::GsString m_strDescription;
	/// \brief 标签文本内容
	Utility::GsString m_strLabel;
	/// \brief 使用同一符号的feature个数
	int m_iFeatureCount;

public:
	GsLegendClass();
	~GsLegendClass();

	/// \brief 得到描述文本内容
	/// \return 
	Utility::GsString Description();
	/// \brief 设置描述文本内容
	/// \param strDescription 
	void Description(const char *strDescription);

	/// \brief 得到标签文本内容
	/// \return 
	Utility::GsString Label();
	/// \brief 设置标签文本内容
	/// \param strLabel 
	void Label(const char *strLabel);

	/// \brief 得到图例信息样式
	/// \return 
	GsLegendClassFormat* Format();
	/// \brief 设置图例信息样式
	/// \param pFormat 
	void Format(GsLegendClassFormat* pFormat);

	/// \brief 
	/// \param nCount 
	void FeatureCount(int nCount);
	/// \brief 
	/// \return 
	int FeatureCount();
};
GS_SMARTER_PTR(GsLegendClass);


/// \brief 多个图例信息组成一个GsLegendGroup
/// \details 每个图层有一个GsLegendGroup, 有多个GsLegendClass
class GS_API GsLegendGroup :public Utility::GsRefObject
{
private:
	Utility::GsVector<GsLegendClassPtr > m_lstLegendClasses;

	/// \brief 图例Heading名字
	Utility::GsString m_strHeading;
	/// \brief 图例图层layer名字
	Utility::GsString m_strLayerName;
	/// \brief 图例显示默认符号的名字
	Utility::GsString m_strDefautSymName;
	/// \brief 图例图层是否显示
	bool m_bVisible;
	/// \brief 样式是否与指定的层兼容
	bool m_bCanDisplay;
	/// \brief 当前LegendGroup的列数
	int m_iColumns;
	/// \brief 显示的图例组的索引
	int m_iGroupIndex;
	/// \brief 图例Heading符号
	GsTextSymbolPtr m_ptrHeadingSymbol;
	/// \brief 图例layer符号
	GsTextSymbolPtr m_ptrLayerNameSymbol;
	/// \brief 图例组默认格式信息
	GsLegendClassFormatPtr m_ptrLegendClassFormat;
	/// \brief 获取是否全部GroupClass是否显示为一列
	bool m_bKeepTogether;

	/// \brief 是否在图例中启动新列
	bool m_bNewColumn;
	/// \brief 描述信息是否可见的
	bool m_bShowDescriptions;
	/// \brief Heading是否可见的
	bool m_bShowHeading;
	/// \brief Labels是否可见的
	bool m_bShowLabels;
	/// \brief LayerName是否可见的
	bool m_bShowLayerName;
	/// \brief 图例组样式
	GsLegendItemStyle m_eLegendItemStyle;


public:
	GsLegendGroup();
	~GsLegendGroup();

	/// \brief GsLegendClass个数
	/// \return 
	int Count();

	/// \brief Index位置的GsLegendClass
	/// \param Index 索引
	/// \return 
	GsLegendClass* Legend(int Index);

	/// \brief 插入
	/// \param LegendClass 
	void Add(GsLegendClass* LegendClass);

	/// \brief 清空
	void Clear();

	/// \brief 图例Heading名字
	/// \return 
	GeoStar::Utility::GsString Heading();
	/// \brief 
	/// \param strHeading 
	void Heading(const char* strHeading);
	
	/// \brief 图例图层layer名字
	/// \return 
	GeoStar::Utility::GsString LayerName();
	/// \brief 
	/// \param strHeading 
	void LayerName(const char* strHeading);
	
	/// \brief 图例显示默认符号的名字
	/// \return 
	GeoStar::Utility::GsString DefautSymName();
	/// \brief 
	/// \param strHeading 
	void DefautSymName(const char* strHeading);

	/// \brief 图例图层是否显示
	/// \return 
	bool Visible();
	/// \brief 
	/// \param bVisible 
	void Visible(bool bVisible);

	/// \brief 指示样式是否与指定的层兼容
	/// \return 
	bool CanDisplay();
	/// \brief 图例项中的列数
	/// \return 
	int Columns();
	/// \brief 
	/// \param nCols 
	void Columns(int nCols);
	/// \brief 这个项目所显示的图例组的零基索引。使用-1来显示使用这个项目的所有图例组
	/// \return 
	int GroupIndex();
	/// \brief 
	/// \param nGroupIndex 
	void GroupIndex(int nGroupIndex);
	/// \brief Heading文本符号
	/// \return 
	GsTextSymbol* HeadingSymbol();
	/// \brief 
	/// \param pTextSymbol 
	void HeadingSymbol(GsTextSymbol* pTextSymbol);
	/// \brief LayerName文本符号
	/// \return 
	GsTextSymbol* LayerNameSymbol();
	/// \brief 
	/// \param pTextSymbol 
	void LayerNameSymbol(GsTextSymbol* pTextSymbol);

	/// \brief 图例类的默认格式信息。渲染器可以重写。
	/// \return 
	GsLegendClassFormat* LegendClassFormat();
	/// \brief 
	/// \param pLegendClassFormat 
	void LegendClassFormat(GsLegendClassFormat* pLegendClassFormat);

	/// \brief 获取是否全部GroupClass是否显示为一列
	/// \return 返回bool
	bool KeepTogether();

	/// \brief 设置是否全部GroupClass显示在一起
	/// \param bool bkeepTogether 是否显示为一列
	/// \param bkeepTogether 
	void KeepTogether(bool bkeepTogether);

	/// \brief 指示项目是否在图例中启动新列
	/// \return 
	bool NewColumn();
	/// \brief 
	/// \param bNewColum 
	void NewColumn(bool bNewColum);

	/// \brief 描述信息是否可见的
	/// \return 
	bool ShowDescriptions();
	/// \brief 
	/// \param bNewColum 
	void ShowDescriptions(bool bNewColum);
	/// \brief Heading是否可见的
	/// \return 
	bool ShowHeading();
	/// \brief 
	/// \param bNewColum 
	void ShowHeading(bool bNewColum);
	/// \brief Labels是否可见的
	/// \return 
	bool ShowLabels();
	/// \brief 
	/// \param bNewColum 
	void ShowLabels(bool bNewColum);
	/// \brief LayerName是否可见的
	/// \return 
	bool ShowLayerName();
	/// \brief 
	/// \param bNewColum 
	void ShowLayerName(bool bNewColum);

	/// \brief 样式
	/// \return 
	GsLegendItemStyle Style();
	/// \brief 
	/// \param eStyle 
	void Style(GsLegendItemStyle eStyle);

	/// \brief 在m_lstLegendClasses找看有无pSym，若有则增加计数，若没有，则NEW新的放入列表中
	/// \param strName 
	/// \param pSym 
	void AddLegendClassBySymbol(const char* strName, GsSymbol* pSym);

protected:
	/// \brief 
	/// \param pSym 
	/// \return 
	GsLegendClass* FindLegendClassBySymbol(GsSymbol* pSym);

};
GS_SMARTER_PTR(GsLegendGroup);

/// \brief 图例信息,
/// \details 每个render都有自带一个LegendInfo
/// \details 如果是动态图例 需要统计当前map绘制得数据量
class GS_API GsLegends :public Utility::GsRefObject
{
	GsLegendGroupPtr m_ptrLegendGroup;
public:
	GsLegends();
	~GsLegends();
	/// \brief 获取一组图例,一般为一个图层的所有图例
	/// \param nIndex 
	/// \return 
	GsLegendGroup* LegendGroup(int nIndex);
	/// \brief 获取组图例个数
	/// \return 
	int LegendGroupCount();

};
GS_SMARTER_PTR(GsLegends);

class GS_API GsFeatureLegendClass : public GsLegendClass
{
public:
	GsFeatureLegendClass();
	~GsFeatureLegendClass();
};
GS_SMARTER_PTR(GsFeatureLegendClass);

class GS_API GsVectorTileLegendClass : public GsLegendClass
{
public:
	GsVectorTileLegendClass();
	~GsVectorTileLegendClass();
};
GS_SMARTER_PTR(GsVectorTileLegendClass);

class GS_API GsRasterLegendClass : public GsLegendClass
{
public:
	GsRasterLegendClass();
	~GsRasterLegendClass();
};
GS_SMARTER_PTR(GsRasterLegendClass);


class GS_API GsRenderer :public Utility::GsRefObject
{
protected:
	GsLegendsPtr m_ptrLegends;
	GsRenderer();
public:
	~GsRenderer();

	/// \brief
	/// \return 
	GsLegends* Legends();

	/// \brief 初始化LegendGroup信息, Layer 调用draw之前触发初始化
	/// \param pLayer 
	virtual void InitLegendsInfo(GsLayer* pLayer);
};
GS_SMARTER_PTR(GsRenderer);

/// \brief 地物渲染动态绑定器
/// \details 在绘制之前根据特定规则或表达式做符号或者数据的修改,以便达到动态效果
/// \details 每个render只能绑定一个,重载Binding方法可实现不同绑定效果
class GS_API  GsParameterDynamicBinder :public Utility::GsRefObject
{
protected:
	/// \brief 
	GsParameterDynamicBinder() {}
public:
	/// \brief 根据GsFeature 绑定GsSymbol
	/// \param pFea 绘制的 Feature
	/// \param pSym 绘制使用的符号
	virtual void Binding(GsFeature *pFea, GsSymbol* pSym) = 0;

	/// \brief 克隆
	/// \return 
	virtual Utility::GsSmarterPtr<GsParameterDynamicBinder> Clone() = 0;
};
GS_SMARTER_PTR(GsParameterDynamicBinder);
/// \brief 浮点数字段动态绑定
class GS_API GsFloatFieldParameterDynamicBinder :public GsParameterDynamicBinder
{	
	//字段索引
	int m_nIndex;
	//字段或者表达式
	Utility::GsString m_strField;
	//字段信息
	GsField m_Field;
public:
	/// \brief 初始化
	/// \param strField 字段名称
	GsFloatFieldParameterDynamicBinder(const char* strField);
	/// \brief 根据GsFeature 绑定GsSymbol
	/// \param pFea 绘制的 Feature
	/// \param pSym 绘制使用的符号
	virtual void Binding(GsFeature *pFea, GsSymbol* pSym);

	/// \brief 获取绑定的字段名
	/// \return 
	const char* FieldName();

	/// \brief 克隆
	/// \return 
	virtual Utility::GsSmarterPtr<GsParameterDynamicBinder> Clone();
};
GS_SMARTER_PTR(GsFloatFieldParameterDynamicBinder);

class GS_API GsExpressionContext2;
GS_SMARTER_PTR(GsExpressionContext2);
/// \brief 地物渲染器抽象基类
class GS_API GsFeatureRenderer:public GsRenderer
{
	/// \brief 渲染器结束绘制时发生。
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	bool EndDrawCursor(GsFeatureCursor* pFeaCursor, GsDisplay* pDisplay);
protected:
	/// \brief 显示对象
	GsDisplayPtr m_ptrDisplay;
	/// \brief 当前会绘制的游标
	GsFeatureCursorPtr m_ptrFeaCursor;
	
	/// \brief 坐标变换对象
	GsCoordinateTransformationPtr m_ptrTrans;
	
	/// \brief 渲染器类型
	GsRenditionMode m_eMode;
	/// \brief 渲染器
	Utility::GsVector<GsFeatureRenditionPtr> m_vecRendition;
	/// \brief 当前使用的渲染器对象
	GsFeatureRendition *m_pCurrentRendition;
	/// \brief 当前图层的图例组对象
	GsLegendGroupPtr m_ptrLegendGroup;
	/// \brief 当前渲染器的索引
	int m_nCurrentRenditionIndex;
	/// \brief 动态绑定器
	GsParameterDynamicBinderPtr m_ptrDynamicBinder;
	///\brief 表达式上下文
	GsExpressionContext2Ptr m_ptrExpressionContext;
protected:
	/// \brief 渲染器开始绘制游标时发生
	/// \param pFeaFirst 
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	/// \param pFea 
	/// \param pDisplay 
	/// \return 
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 子类如果需要实现克隆接口，父类的属性首先Assign(克隆)一次。
	/// \param pFea 
	virtual void Assign(GsFeatureRenderer* pFea);
public:
	GsFeatureRenderer();
	~GsFeatureRenderer(); 

	/// \brief 渲染器模式
	/// \param eMode 
	void RenditionMode(GsRenditionMode eMode);
	/// \brief 渲染器模式
	/// \return 
	GsRenditionMode RenditionMode();

	/// \brief 渲染器数量
	/// \return 
	int RenditionCount();
	/// \brief 获取渲染器
	/// \param nIndex 
	/// \return 
	GsFeatureRendition* Rendition(int nIndex=0);
	/// \brief 新增渲染器
	/// \param pRen 
	void AddRendition(GsFeatureRendition* pRen);

	/// \brief 删除一个Rendition
	/// \param nIndex 
	/// \return 
	bool RemoveRendition(int nIndex);
	/// \brief 清除所有Rendition
	void RemoveAllRendition();

	/// \brief 绘制一个地物游标中的数据
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \param pCancel 
	virtual void DrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay,GsTrackCancel* pCancel);

	/// \brief 获取坐标转换对象
	/// \return 
	GsCoordinateTransformation* CoordinateTransformation();
	/// \brief 设置坐标转换对象
	/// \param trans 
	void CoordinateTransformation(GsCoordinateTransformation* trans);

	/// \brief 设置当前渲染器
	/// \param nIndex 
	void CurrentRendition(int nIndex = 0);

	/// \brief 克隆
	/// \return 
	virtual Utility::GsSmarterPtr<GsFeatureRenderer> Clone() ;

	/// \brief
	/// \param index 
	/// \return 
	GsLegendGroup* LegendGroup(int index = 0);

	/// \brief 初始化LegendGroup信息
	/// \param pLayer 
	virtual void InitLegendGroupInfo(GsLayer* pLayer);

	/// \brief 设置动态绑定器
	/// \param pDynamicBinder 
	void ParameterDynamicBinder(GsParameterDynamicBinder* pDynamicBinder);
	/// \brief 获取动态绑定器
	/// \return 
	GsParameterDynamicBinder* ParameterDynamicBinder();
	/// \brief 设置表达式上下文
	/// \param 上下文
	void ExpressionContext(GsExpressionContext2* pExpcontext);
	/// \brief 获取表达式上下文
	/// \return 上下文
	GsExpressionContext2* ExpressionContext();
public:
	/// \brief 事件,当开始绘制的时候发生
	/// \details 参数1 
	/// \details 参数2 
	/// \details 参数3 
	Utility::GsDelegate<void(GsFeature*,GsFeatureCursor*,GsDisplay*)> OnBegin;
	/// \brief 
	/// \details 参数1 
	/// \details 参数2 
	/// \details 参数3 
	Utility::GsDelegate<void(GsFeature*,GsDisplay*,bool*)> OnFeature;
	/// \brief 
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<void(GsFeatureCursor*,GsDisplay*)> OnEnd;
protected:
	/// \brief 当开始Render Label的时候发生,取所有render Label的公共实现
	/// \param pFea 
	/// \param pDisplay 
	/// \param pSymbol 
	/// \return 
	bool OnRenditionRender(GsFeature * pFea, GsDisplay * pDisplay, GsSymbol* pSymbol);
};
/// \brief GsFeatureRendererPtr
GS_SMARTER_PTR(GsFeatureRenderer);
 
/// \brief 将任意的颜色转换为RGBA32位位图。
/// \details RasterRenderer的二次开发可以扩展一个ColorToRGBA子类；或者直接重写GsRasterRenderer::DrawCursor，以获得更大的灵活性
class GS_API GsColorToRGBA
{
protected:
	/// \brief 透明度
	double m_dblTrans;
	GsTrackCancelPtr m_ptrCancel;
public:
	GsColorToRGBA();
	virtual ~GsColorToRGBA();
	
	/// \brief 根据RasterClass生成颜色转换器
	/// \param pRasterClass 栅格数据集
	/// \param pCancel 取消对象
	/// \return 
	static GsColorToRGBA* CreateColorToRGBA(GsRasterClass* pRasterClass, GsTrackCancel* pCancel);

	/// \brief 转换数据到Image
	/// \param pRaster 
	/// \param pImg 
	/// \return 
	virtual bool Translate(GsRaster* pRaster,Utility::GsImage* pImg);
	/// \brief 将Image中的指定颜色c转换为透明
	/// \param pImg 传入的图片对象指针
	/// \param c 需要修改的颜色
	/// \return 是否修改成功
	virtual bool Translate(Utility::GsImage* pImg, Utility::GsColor c);
	/// \brief 
	/// \param pImg 
	/// \param useAlphaBand 
	/// \param useRedBand 
	/// \param useGreenBand 
	/// \param useBlueBand 
	/// \return 
	virtual bool Translate(Utility::GsImage* pImg, bool useAlphaBand, bool useRedBand, bool useGreenBand, bool useBlueBand);
	//virtual bool Translate(GsRaster* sRaster, GsRaster* tRaster);
	/// \brief 转换数据到Image
	/// \param pRaster 
	/// \param pImg 
	/// \param offset 
	/// \return 
	virtual bool Translate(GsRaster* pRaster, Utility::GsImage* pImg,Utility::GsPT &offset);
	/// \brief 设置透明度，取值从0到1
	/// \param dblTrans 
	void Transparency(double dblTrans);
	/// \brief 获取透明度，取值从0到1
	/// \return 
	double Transparency();
	/// \brief 获取中断器
	/// \return 
	GsTrackCancel* TrackCancel();
	/// \brief 设置中断器
	/// \param cancel 
	void TrackCancel(GsTrackCancel* cancel);

	/// \brief 设置nodata的值，一般情况下可以认为小于nodata的像素值认为是无效的。
	/// \param nodata 设置的nodata的值
	virtual void NoDataValue(double nodata);

	/// \brief 获取nodata的值。
	/// \return 返回nodata的值
	virtual double NoDataValue();
};
enum GS_API GsStrectchType
{
	/// \brief 局部标准差
	eStandardDeviations,
	/// \brief 最大最小值
	eMininumMaxinum,
	/// \brief 常规
	eCustom,
	/// \brief 直方图均衡化
	eHistogramEqualize,
	/// \brief 直方图定制化
	eHistogramSpecification,
	/// \brief 百分比剪切
	ePercentClip
};

/// \brief 栅格数据渲染器抽象基类
class GS_API GsRasterRenderer:public GsRenderer
{
protected:
	/// \brief 用于绘制的位图对象
	Utility::GsSimpleBitmapPtr m_ptrImage;
	/// \brief 像素转换
	Utility::GsSharedPtr<GsColorToRGBA> m_ptrTrans;
	/// \brief 透明度
	double m_dblTrans; 

	/// \brief 无效色
	Utility::GsColor m_InvalidColor;
	/// \brief 对m_ptrImage做转换，如无效色等处理
	/// \return 
	virtual bool Translation();

	/// \brief 栅格波段的数据类型
	GsRasterDataType m_DataType;
	GsRasterRenderer();
public:
	virtual ~GsRasterRenderer();

	/// \brief 绘制一个地物游标中的数据
	/// \param pRasterCursor 
	/// \param pDisplay 
	/// \param pCancel 
	virtual void DrawCursor(GsRasterCursor* pRasterCursor,GsDisplay* pDisplay,GsTrackCancel* pCancel);

	/// \brief 设置透明度，取值从0到1
	/// \param dblTrans 
	void Transparency(double dblTrans);
	
	/// \brief 设置无效色，使得某个颜色变为无效色(变透明色)
	/// \param c 颜色
	void InvalidColor(Utility::GsColor c);

	/// \brief 获取设置的无效色
	/// \return 颜色
	Utility::GsColor InvalidColor();
	
	/// \brief 克隆RasterRenderer
	/// \return 
	virtual Utility::GsSmarterPtr<GsRasterRenderer> Clone() = 0;

	/// \brief 
	/// \return 
	double Transparency();

	//void Strectch(double deviations);
	virtual void Strectch(double min,double max);

	/// \brief 创建颜色绘制对象
	/// \param pRaster 
	/// \param pCancel 
	virtual void CreateColorTrans(GsRasterClass* pRaster, GsTrackCancel* pCancel);
};
/// \brief GsRasterRendererPtr
GS_SMARTER_PTR(GsRasterRenderer);

/// \brief RGBA渲染器
/// \details 游标中所有的像素统一使用RGBA值进行绘制
class GS_API GsRGBARasterRenderer:public GsRasterRenderer
{
	int m_nRed;
    int m_nGreen;
    int m_nBlue;
    int m_nAlpha;
	/// \brief 是否使用红色波段
	bool m_useRedBand;
	/// \brief 是否使用绿色波段
	bool m_useGreenBand;
	/// \brief 是否使用蓝色波段
	bool m_useBlueBand;
	/// \brief 是否使用透明波段
	bool m_useAlphaBand;

	Utility::GsPair<int, int>  m_BandRange[4];
	/// \brief 覆盖基类函数，对图像进行转换
	/// \return 
	virtual bool Translation();
public:
	/// \brief 从RGBA的通道序列构造，无透明通道时，a设为-1
	/// \param r 
	/// \param g 
	/// \param b 
	/// \param a 
	GsRGBARasterRenderer(int r, int g, int b, int a=3);
	GsRGBARasterRenderer();
	~GsRGBARasterRenderer();

	/// \brief 获取波段的范围信息，波段顺序对应R(0),G(1),B(2),A(3)
	/// \param nBand 
	/// \return 
	Utility::GsPair<int, int>& BandRange(int nBand);

	/// \brief 创建颜色绘制对象
	/// \param pRaster 
	/// \param pCancel 
	virtual void CreateColorTrans(GsRasterClass* pRaster, GsTrackCancel* pCancel);

	/// \brief Red通道序号
	/// \return 
	int Red();
	/// \brief 
	/// \param r 
	void Red(int r);

	/// \brief Green通道序号
	/// \return 
	int Green();
	/// \brief 
	/// \param g 
	void Green(int g);

	/// \brief Blue通道序号
	/// \return 
	int Blue();
	/// \brief 
	/// \param b 
	void Blue(int b);

	/// \brief Alpha通道序号
	/// \return 
	int Alpha();
	/// \brief 
	/// \param a 
	void Alpha(int a);

	/// \brief 是否使用透明波段
	/// \param uAlpha 
	void UseAlphaBand(bool uAlpha);
	/// \brief 
	/// \return 
	bool UseAlphaBand();

	/// \brief 是否使用红色波段
	/// \param uRed 
	void UseRedBand(bool uRed);
	/// \brief 
	/// \return 
	bool UseRedBand();

	/// \brief 是否使用绿色波段
	/// \param uGreen 
	void UseGreenBand(bool uGreen);
	/// \brief 
	/// \return 
	bool UseGreenBand();

	/// \brief 是否使用蓝色波段
	/// \param uBlue 
	void UseBlueBand(bool uBlue);
	/// \brief 
	/// \return 
	bool UseBlueBand();

	/// \brief 获取RGB通道序号
	/// \param redIndex 
	/// \param greenIndex 
	/// \param blueIndex 
	void QueryBandIndices(int &redIndex,int &greenIndex,int &blueIndex);
	/// \brief 设置RGB通道序号
	/// \param redIndex 
	/// \param greenIndex 
	/// \param blueIndex 
	void SetBandIndices(int redIndex, int greenIndex, int blueIndex);

	/// \brief 克隆RasterRenderer
	/// \return 
	virtual GsRasterRendererPtr Clone();
};
/// \brief GsRGBARasterRenderer
GS_SMARTER_PTR(GsRGBARasterRenderer);



/// \brief DEM地形渲染器
class GS_API GsTerrainRenderer : public GsRasterRenderer
{
	/// \brief 山体阴影参数
	GsHillshadeData m_Data;
	/// \brief 渐变色
	Utility::GsGradsColorPtr m_GradColor;
	/// \brief 颜色数量
	int m_nCount;

	bool m_useHillShade;

	template<class T>
	void CreatColorTrans(GsRasterClass* pRasterClass);

public:
	/// \brief 构造函数，默认灰度渲染
	GsTerrainRenderer();
	/// \brief 从渐变色和颜色数量构造
	/// \param pGradColor 渐变色
	/// \param nCount 所需生成颜色的数量
	GsTerrainRenderer(Utility::GsGradsColor* pGradColor, int nCount);

	/// \brief 析构函数
	~GsTerrainRenderer();

	/// \brief 是否使用阴影
	void UseHillShade(bool hillshade);
	bool UseHillShade();

	/// \brief 设置山体阴影参数
	/// \param alt 太阳高度角，单位角度
	/// \param az 太阳方位角，单位角度
	/// \param pGeoTranform 几何变换参数
	/// \param factor 设置高程的缩放系数(夸大系数)
	/// \param scale 水平像素单位和高程单位的换算系数
	void HillShadeData(double alt, double az, double* pGeoTranform = NULL, double factor = 1, double scale = 1);
	/// \brief 设置山体阴影参数
	/// \param data 山体阴影参数结构体 
	void HillShadeData(const GsHillshadeData& data);
	/// \brief 获取山体阴影参数
	GsHillshadeData HillShadeData();

	void GradsColor(Utility::GsGradsColor* pGradColor, int nCount);
	Utility::GsGradsColor* GradsColor();
	/// \brief 创建颜色绘制对象
	/// \param pRaster 
	/// \param pCancel 
	virtual void CreateColorTrans(GsRasterClass* pRaster, GsTrackCancel* pCancel);

	/// \brief 克隆RasterRenderer 
	virtual GsRasterRendererPtr Clone();
};
/// \brief GsTerrainRendererPtr
GS_SMARTER_PTR(GsTerrainRenderer);

/// \brief 灰度影像渲染器
class GS_API GsGrayIndexRasterRenderer : public GsRasterRenderer
{
	double m_sMin;
	double m_sMax;
	double m_sNoData;
	bool  m_bSwap;
	bool  m_bUseNoData;
protected:

public:
	/// \brief 
	/// \param minVal 
	/// \param maxVal 
	/// \param nNoData 
	GsGrayIndexRasterRenderer(double minVal,double maxVal,double nNoData);
	~GsGrayIndexRasterRenderer(){}

	/// \brief 交换黑色和白色
	/// \param bSwap 
	void SwapWhiteBlack(bool bSwap);

	/// \brief 是否使用无效值
	/// \param bUse 
	void UseNoDataValue(bool bUse);
	/// \brief 
	/// \return 
	bool UseNoDataValue();

	/// \brief 无效值
	/// \return 
	double NoDataValue();
	/// \brief 
	/// \param nNoData 
	void NoDataValue(double nNoData);

	void Strectch(double min, double max);
	/// \brief 克隆RasterRenderer
	/// \return 
	virtual GsRasterRendererPtr Clone();

	/// \brief 创建颜色绘制对象
	/// \param pRaster 
	/// \param pCancel 
	virtual void CreateColorTrans(GsRasterClass* pRaster, GsTrackCancel* pCancel);
};
/// \brief GsGrayIndexRasterRenderer
GS_SMARTER_PTR(GsGrayIndexRasterRenderer);

/// \brief 调色板真彩色渲染器
class GS_API GsPaletteRasterRenderer : public GsRasterRenderer
{
	GsColorTable m_cTable;

public:
	/// \brief 
	/// \param table 
	GsPaletteRasterRenderer(const GsColorTable &table);
	~GsPaletteRasterRenderer();


	/// \brief 返回调色板
	/// \return 
	GsColorTable &ColorTable();
	/// \brief 克隆RasterRenderer
	/// \return 
	virtual GsRasterRendererPtr Clone();


	/// \brief 创建颜色绘制对象
	/// \param pRaster 
	/// \param pCancel 
	virtual void CreateColorTrans(GsRasterClass* pRaster, GsTrackCancel* pCancel);
};
/// \brief GsPaletteRasterRenderer
GS_SMARTER_PTR(GsPaletteRasterRenderer);

/// \brief 简单地物渲染器
/// \details 游标中所有的地物统一使用一种符号进行绘制
class GS_API GsSimpleFeatureRenderer:public GsFeatureRenderer
{
	GsSymbolizeFeaturePtr m_ptrSymbolizeFea;
	Utility::GsStlMap<long long,GsSymbolPtr> m_CacheSymbol;
	
	/// \brief 
	/// \param pFea 
	/// \param pDisplay 
	/// \return 
	bool DrawSymbolizeFeature(GsFeature* pFea,GsDisplay* pDisplay);
protected:
	/// \brief 渲染的符号
	GsSymbolPtr m_ptrSymbol;
protected:
	/// \brief 渲染器开始绘制游标时发生
	/// \param pFeaFirst 
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	/// \param pFea 
	/// \param pDisplay 
	/// \return 
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
public:
	/// \brief 缺省构造
	GsSimpleFeatureRenderer();
	/// \brief 根据符号构造
	/// \param pSym 
	GsSimpleFeatureRenderer(GsSymbol* pSym);
	virtual ~GsSimpleFeatureRenderer();

	/// \brief 设置渲染的符号
	/// \param pSym 
	virtual void Symbol(GsSymbol* pSym);
	/// \brief 获取渲染的符号指针
	/// \return 
	virtual GsSymbol* Symbol();
	/// \brief 克隆
	/// \return 
	virtual GsFeatureRendererPtr Clone();
	/// \brief 初始化LegendGroup信息
	/// \param pLayer 
	virtual void InitLegendGroupInfo(GsLayer* pLayer);

};
/// \brief GsSimpleFeatureRendererPtr
GS_SMARTER_PTR(GsSimpleFeatureRenderer);

/// \brief 质底填充渲染器
/// \details 游标中根据指定的属性值，过滤出各个地物，使用不同符号进行绘制
class GS_API GsUniqueValueRenderer:public GsFeatureRenderer
{
protected:
	/// \brief 默认渲染符号
	GsSymbolPtr m_ptrDefaultSymbol;
	
	/// \brief 要过滤的字段名
	Utility::GsString m_strFieldName;
	/// \brief 要过滤的字段名的位置
	int m_nFieldPos;

	/// \brief 记录是否使用默认符号进行绘制
	bool m_bUseDefaultSymbol;

	/// \brief 绘制时描述Feature字段值，声明为成员减少构造次数
	Utility::GsAny m_anyEachFeature;

	/// \brief 渲染符号容器
	Utility::GsStlMap<unsigned long long, GsSymbolPtr> m_mapSymbols;	
	Utility::GsVector<Utility::GsPair<unsigned long long,GsSymbolPtr>> m_vecHahSymbol;
	Utility::GsVector<Utility::GsPair<Utility::GsAny, GsSymbolPtr>> m_Symbols;

	/// \brief 参考值容器
	Utility::GsStlMap< unsigned long long, Utility::GsVector<Utility::GsAny>>  m_mapRefValue;
	/// \brief 标注容器
	Utility::GsStlMap< unsigned long long, Utility::GsAny>  m_mapLabelValue;

protected:
	/// \brief 渲染器开始绘制游标时发生
	/// \param pFeaFirst 
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	/// \param pFea 
	/// \param pDisplay 
	/// \return 
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);

public:
	/// \brief 缺省构造
	GsUniqueValueRenderer();
	/// \brief 根据默认符号构造
	/// \param pDefaultSym 
	GsUniqueValueRenderer(GsSymbol* pDefaultSym);
	virtual ~GsUniqueValueRenderer();

	/// \brief 设置默认符号
	/// \param pSym 
	void DefaultSymbol(GsSymbol* pSym);
	/// \brief 获取默认符号
	/// \return 
	GsSymbol *DefaultSymbol();

	/// \brief 设置过滤字段名
	/// \param strFieldName 
	void FieldName(const char* strFieldName);
	/// \brief 获取过滤字段
	/// \return 
	Utility::GsString FieldName();

	/// \brief 根据双精度型属性值设置符号，放到容器的最后
	/// \param dblValue 
	/// \param pSym 
	void Symbol(double dblValue, GsSymbol* pSym);
	/// \brief 根据单精度型属性值设置符号，放到容器的最后
	/// \param fValue 
	/// \param pSym 
	void Symbol(float fValue, GsSymbol* pSym);
	/// \brief 根据整型属性值设置符号，放到容器的最后
	/// \param nValue 
	/// \param pSym 
	void Symbol(int nValue, GsSymbol* pSym);
	/// \brief 根据字符串型属性值设置符号，放到容器的最后
	/// \param strValue 
	/// \param pSym 
	void Symbol(const char* strValue, GsSymbol* pSym);

	/// \brief 根据双精度型属性值设置符号，插入容器中index位置
	/// \param dblValue 
	/// \param pSym 
	/// \param index 
	/// \return 
	bool Symbol(double dblValue, GsSymbol* pSym, int index);
	/// \brief 根据单精度型属性值设置符号，插入容器中index位置
	/// \param fValue 
	/// \param pSym 
	/// \param index 
	/// \return 
	bool Symbol(float fValue, GsSymbol* pSym, int index);
	/// \brief 根据整型属性值设置符号，插入容器中index位置
	/// \param nValue 
	/// \param pSym 
	/// \param index 
	/// \return 
	bool Symbol(int nValue, GsSymbol* pSym, int index);
	/// \brief 根据字符串型属性值设置符号，插入容器中index位置
	/// \param strValue 
	/// \param pSym 
	/// \param index 
	/// \return 
	bool Symbol(const char* strValue, GsSymbol* pSym, int index);
	/// \brief 分类对应的符号集合
	/// \return 
	const Utility::GsVector<Utility::GsPair<Utility::GsAny, GsSymbolPtr>>& Symbols();
	/// \brief 根据双精度型属性值获取符号
	/// \param dblValue 
	/// \return 
	GsSymbol* Symbol(double dblValue);
	/// \brief 根据单精度型属性值获取符号
	/// \param fValue 
	/// \return 
	GsSymbol* Symbol(float fValue);
	/// \brief 根据整型属性值获取符号
	/// \param nValue 
	/// \return 
	GsSymbol* Symbol(int nValue);
	/// \brief 根据字符串型属性值获取符号
	/// \param value 
	/// \return 
	GsSymbol* Symbol(const char* value);

	/// \brief 添加属性值的参考值
	/// \param Value 
	/// \param refValue 
	void AddReferenceValue(Utility::GsAny& Value, Utility::GsAny& refValue);
	/// \brief 
	/// \param Value 
	/// \param refValues 
	void AddReferenceValue(Utility::GsAny& Value, Utility::GsVector<Utility::GsAny>& refValues);
	/// \brief 通过属性值Key获取所有的参考值
	/// \param Value 
	/// \return 
	Utility::GsVector<Utility::GsAny>& ReferenceValue(Utility::GsAny& Value);

	/// \brief 获取属性值的标注
	/// \param Value 
	/// \return 
	Utility::GsAny Label(Utility::GsAny& Value);
	/// \brief 设置属性值的标注
	/// \param Value 
	/// \param Label 
	void Label(Utility::GsAny& Value, Utility::GsAny& Label);

	/// \brief 设置是否使用默认符号进行绘制
	/// \param bUse 
	void IsUseDefaultSymbol(bool bUse);
	/// \brief 返回是否使用默认符号进行绘制
	/// \return 
	bool IsUseDefaultSymbol();

	/// \brief 根据指定值删除符号
	/// \param anyValue 
	void RemoveSymbol(const Utility::GsAny& anyValue);
	/// \brief 删除所有的符号
	void RemoveAllSymbol();

	/// \brief 克隆
	/// \return 
	virtual GsFeatureRendererPtr Clone();

	/// \brief 初始化LegendGroup信息
	/// \param pLayer 
	virtual void InitLegendGroupInfo(GsLayer* pLayer);

protected:
	/// \brief 所有符号准备绘制
	/// \param pDisplay 
	void AllSymbolsBeginDraw(GsDisplay* pDisplay);
	/// \brief 所有符号结束绘制
	void AllSymbolsEndDraw();
	/// \brief 根据key值查找符号，没有找到返回空指针
	/// \param nKey 
	/// \return 
	GsSymbol *FindSymbolByKey(unsigned long long nKey);

};
/// \brief GsSimpleFeatureRendererPtr
GS_SMARTER_PTR(GsUniqueValueRenderer);

/// \brief 用于渲染注记地物
class GS_API GsTextFeatureRenderer:public GsFeatureRenderer
{
protected:
	/// \brief 是否统一使用一种符号(m_ptrTextSymbol)渲染。
	bool m_bUnified;
	/// \brief 接口变量，外部可设置获取。
	GsTextSymbolPtr m_ptrTextSymbol;
	/// \brief 实际绘制时的文字符号。
	GsTextSymbolPtr m_ptrRenderSymbol;
	GsSymbolizeFeaturePtr m_ptrSymbolizeFea;
	int m_nTextFieldPos;
	Utility::GsStlMap<long long,GsTextSymbolPtr> m_CacheSymbol;
	
	/// \brief 
	/// \param pFea 
	/// \param pDisplay 
	/// \return 
	bool DrawSymbolizeFeature(GsFeature* pFea,GsDisplay* pDisplay);
protected:
	/// \brief 设置文字符号的属性
	/// \param GsFeature* pFea：每个地物，里面记录的属性可能会不一样
	/// \param pFea 
	virtual void TextSymbolProperty(GsFeature* pFea);
	/// \brief 渲染器开始绘制游标时发生
	/// \param pFeaFirst 
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	/// \param pFea 
	/// \param pDisplay 
	/// \return 
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 注记属性转为textSymbol
	/// \param pFea 
	/// \param pTxtSym 
	/// \return 
	virtual bool PutFieldPropSymbol(GsFeature *pFea,GsTextSymbol *pTxtSym);
public:
	/// \brief 缺省构造,会设置m_bUnified为false
	GsTextFeatureRenderer();
	/// \brief 根据符号构造
	/// \param pSym 统一绘制时用到的绘制符号，默认统一绘制m_bUnified为false
	GsTextFeatureRenderer(GsTextSymbol* pSym);
	virtual ~GsTextFeatureRenderer();

	/// \brief 设置渲染的符号，仅仅会修改符号，并不会修改m_bUnified
	/// \param pSym 
	virtual void Symbol(GsTextSymbol* pSym);
	/// \brief 获取渲染的符号指针
	/// \return 
	virtual GsTextSymbol* Symbol();

	/// \brief 是否统一使用一种符号渲染
	/// \return 
	bool Unified();
	/// \brief 是否统一使用一种符号渲染
	/// \param b 
	void Unified(bool b);

	/// \brief 
	/// \return 
	virtual GsFeatureRendererPtr Clone();
};
/// \brief GsTextFeatureRendererPtr
GS_SMARTER_PTR(GsTextFeatureRenderer);

/// \brief 用于做选择绘制时，避免因为分别绘制时将注记地物的文字颜色设置给文字符号
class GS_API GsSelectionTextFeatureRenderer :public GsTextFeatureRenderer
{
protected:
	/// \brief 设置文字符号的属性
	/// \param pFea 每个地物，里面记录的属性可能会不一样
	virtual void TextSymbolProperty(GsFeature* pFea);
public:
	/// \brief 
	/// \param pSym 
	GsSelectionTextFeatureRenderer(GsTextSymbol* pSym);
	GsSelectionTextFeatureRenderer();
	virtual ~GsSelectionTextFeatureRenderer();
	/// \brief 
	/// \return 
	virtual GsFeatureRendererPtr Clone();
};
GS_SMARTER_PTR(GsSelectionTextFeatureRenderer);

/// \brief 用于分级渲染
class GS_API GsGraduatedRenderer:public GsFeatureRenderer
{
	/// \brief 默认渲染符号
	GsSymbolPtr m_ptrDefaultSymbol;
	/// \brief 是否用缺省符号
	bool m_bIsUseDefaultSymbol; 
	/// \brief 分级符号
	UTILITY_NAME::GsVector<GsSymbolPtr> m_vSymbols;
	
	/// \brief 是否为分级颜色
	bool m_bIsGradeColor;

	/// \brief 分级点
	UTILITY_NAME::GsVector<double> m_vBreakValues;
	/// \brief 级别数
	int m_nBreakCount;
	
	/// \brief 字段索引号
	int	 m_nFieldPos;	
	/// \brief 字段名
	Utility::GsString m_strFieldName;
	/// \brief 正规化字段索引号
	int	 m_nNormFieldPos; 
	/// \brief 正规化字段名
	Utility::GsString m_strNormFieldName;

protected:
	/// \brief 渲染器开始绘制游标时发生
	/// \param pFeaFirst 
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	/// \param pFea 
	/// \param pDisplay 
	/// \return 
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);


	/// \brief 获取字段值
	/// \param pFea 
	/// \param pos 
	/// \param dValue 
	/// \return 
	bool FieldValue(GsFeature* pFea, int pos, double &dValue);
	/// \brief 计算字段值的分级
	/// \param pFea 
	/// \return 
	int FieldGrade(GsFeature* pFea);

public:
	/// \brief 缺省构造
	GsGraduatedRenderer();
	virtual ~GsGraduatedRenderer();

	/// \brief 设置符号
	/// \param pSymbol 
	void Symbol(GsSymbol* pSymbol);

	/// \brief 设置符号到指定位置
	/// \param pSymbol 需要插入的符号
	/// \param left 设置插入符号对应的左边界值
	/// \param right 设置插入符号对应的右边界值,右边界值需要大于等于左边界值
	/// \param nIndex 插入符号的位置
	/// \return 返回是否插入成功 
	bool Symbol(GsSymbol* pSymbol, double left, double right, int nIndex);

	/// \brief 根据级别值获取符号, 参数的最小值为0
	/// \param nIndex 
	/// \return 
	GsSymbol* Symbol(int nIndex);

	/// \brief 设置默认符号
	/// \param pSymbol 
	void DefaultSymbol(GsSymbol* pSymbol);
	/// \brief 获取默认符号
	/// \return 
	GsSymbol* DefaultSymbol();

	/// \brief 设置是否使用默认符号
	/// \param bIsUseDefaultSymbol 
	void IsUseDefaultSymbol(bool bIsUseDefaultSymbol);
	/// \brief 获取是否使用默认符号
	/// \return 
	bool IsUseDefaultSymbol();


	/// \brief 判断是否分级颜色
	/// \return 
	bool GradeTypeColor();
	/// \brief 设置是否分级颜色
	/// \param bIsGradeColor 
	void GradeTypeColor(bool bIsGradeColor);

	/// \brief 设置字段位置
	/// \param nPos 
	void FieldPos(int nPos);
	/// \brief 返回字段位置
	/// \return 
	int FieldPos();

	/// \brief 
	/// \param strFieldName 
	void FieldName(const char* strFieldName);
	/// \brief 
	/// \return 
	Utility::GsString FieldName();
	/// \brief 设置正规化字段位置
	/// \param nPos 
	void NormalFieldPos(int nPos);
	/// \brief 返回正规化字段位置
	/// \return 
	int NormalFieldPos();
	/// \brief 设置正规化字段名
	/// \param strFieldName 
	void NormalFieldName(const char* strFieldName);
	/// \brief 返回正规化字段名
	/// \return 
	Utility::GsString NormalFieldName();

	/// \brief 设置分级值
	/// \param dValue 
	void BreakValue(double dValue);
	/// \brief 返回分级值
	/// \param nIndex 
	/// \return 
	double BreakValue(int nIndex);
	/// \brief 设置分级数量
	/// \param nCount 
	void BreakCount(int nCount);
	/// \brief 返回分级数量
	/// \return 
	int BreakCount();

	/// \brief 删除指定级别的符号,参数的最小值为0
	/// \param index 
	void RemoveSymbolAt(int index);

	/// \brief 根据指定值删除符号
	/// \param pSymbol 
	void RemoveSymbol(GsSymbol* pSymbol);
	/// \brief 删除所有的符号
	void RemoveAllSymbol();

	/// \brief 克隆
	/// \return 
	virtual GsFeatureRendererPtr Clone();

	/// \brief 初始化LegendGroup信息
	/// \param pLayer 
	virtual void InitLegendGroupInfo(GsLayer* pLayer);

};
/// \brief GsGraduatedRendererPtr
GS_SMARTER_PTR(GsGraduatedRenderer);




	/// \brief 点值法
class GS_API GsDotDensityRenderer:public GsFeatureRenderer
{
public:
	/// \brief 缺省构造
	GsDotDensityRenderer();
	virtual ~GsDotDensityRenderer();

	/// \brief 设置字段位置
	/// \param nIndex 
	void FieldIndex(int nIndex);
	/// \brief 返回字段位置
	/// \return 
	int FieldIndex();
	
	/// \brief 设置点的尺寸
	/// \param dDotSize 
	void DotSize(double dDotSize);
	/// \brief 返回点尺寸
	/// \return 
	double DotSize();

	/// \brief 设置点值
	/// \param dDotValue 
	void DotValue(double dDotValue);
	/// \brief 返回点值
	/// \return 
	double DotValue();

	/// \brief 设置点符号
	/// \param pPointSymbol 
	void PointSymbol(GsPointSymbol* pPointSymbol);
	/// \brief 获取点符号
	/// \return 
	GsPointSymbol* PointSymbol();

	/// \brief 设置背景面符号
	/// \param pFillSymbol 
	void BackGroundSymbol(GsFillSymbol* pFillSymbol);
	/// \brief 获取背景面符号
	/// \return 
	GsFillSymbol* BackGroundSymbol();

	/// \brief 设置是否绘制背景
	/// \param bVal 
	void IsDrawBackGround(bool bVal);
	/// \brief 获取是否绘制背景
	/// \return 
	bool IsDrawBackGround();
protected:
	/// \brief 渲染器开始绘制游标时发生
	/// \param pFeaFirst 
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	/// \param pFea 
	/// \param pDisplay 
	/// \return 
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	/// \param pFeaCursor 
	/// \param pDisplay 
	/// \return 
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);

	/// \brief 用以计算字段值
	/// \param pFea 
	/// \param pos 
	/// \param dValue 
	/// \return 
	bool FieldValue(GsFeature* pFea, int pos, double &dValue);
	/// \brief 计算随机数
	/// \param minNum 
	/// \param maxNum 
	/// \return 
	double RandomNumber(double minNum,double maxNum);

	/// \brief 克隆
	/// \return 
	virtual GsFeatureRendererPtr Clone();

	/// \brief 初始化LegendGroup信息
	/// \param pLayer 
	virtual void InitLegendGroupInfo(GsLayer* pLayer);

private:
	/// \brief 字段索引
	int m_nFieldIndex;
	/// \brief 点的大小
	double m_dDotSize ;
	/// \brief 点代表的值
	double m_dDotValue ; 
	/// \brief 字段的名称	
	Utility::GsString m_FieldName ; 

	bool m_bIsDirty ;
	bool m_bIsDrawBackGound ; 
	 
	GsGeometryPtr m_ptrGeoKnife;
	 

	GsFillSymbolPtr m_ptrFillSymbol;  //面符号  
	GsSymbolPtr m_ptrSymbol; // 指向当前的点符号     
	GsPointSymbolPtr m_ptrPointSymbol;//用来存储绘图使用的点符号		 


};
/// \brief GsDotDensityRendererPtr
GS_SMARTER_PTR(GsDotDensityRenderer);


/// \brief 动态投影的方法
enum GsProjectionStyle
{
	/// \brief 不论什么情况下不做动态投影
	eDoNotProjection,

	/// \brief 自动动态投影
	/// \details 仅在当前图层和地图参考不一致的时候进行动态投影
	eDoProjectionAuto,

	/// \brief 强制动态投影
	/// \details 不论当前图层和地图空间参考是否一致都进行投影
	eDoProjectionForce,
};

/// \brief 地物类图层
class GS_API GsFeatureLayer:public GsLayer
{ 
	GsFeatureClassPtr m_ptrFeaClass;
	GsFeatureRendererPtr m_ptrRenderer;
	GsFeatureRendererPtr m_ptrSelectionRenderer;
	GsSelectionSetPtr m_ptrSelectionSet;
	GsQueryFilterPtr m_ptrDisplayFilter;
	
	/// \brief 动态投影的方法
	GsProjectionStyle m_eProjectionStyle;
	
	/// \brief 进行强制投影变换是源投影
	GsSpatialReferencePtr m_ptrSource;
	

	/// \brief 事件，当外部调用Cancel方法时发生
	/// \param pCancel 
	/// \param name 
	void OnCancel(GsTrackCancel* pCancel,const char* name);
protected:
	/// \brief 绘制方法入口
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \return 
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);

	/// \brief 增加标注过滤条件
	/// \param pFilter 
	/// \param strWhereClause 
	/// \param strOrderField 
	void AddLabelFilter(GsQueryFilter *pFilter, const Utility::GsString& strWhereClause, const Utility::GsString& strOrderField);
	/// \brief 执行绘制
	/// \param pFeatureRender 
	/// \param pFilter 
	/// \param pDisplay 
	/// \param pDT 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \return 
	virtual bool DoDraw(GsFeatureRenderer* pFeatureRender,
		GsQueryFilter* pFilter, 
		GsDisplay* pDisplay,
		GsCoordinateTransformation* pDT,
		GsTrackCancel* pCancel,GsDrawPhase eDrawPhase = eDrawNormal);

	/// \brief 检索用于绘制的空间数据
	/// \param pFilter 
	/// \param eDrawPhase 
	/// \return 
	virtual GsFeatureCursorPtr SearchData(GsQueryFilter* pFilter, GsDrawPhase eDrawPhase);
public:
	/// \brief 从一个地物类构造
	/// \param vFeaClass 
	GsFeatureLayer(GsFeatureClass* vFeaClass);
	/// \brief 缺省构造
	GsFeatureLayer();
	virtual ~GsFeatureLayer();

	/// \brief 图层的地理范围
	/// \param pTargetSR 
	/// \return 
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0);
	

	/// \brief 获取图层的空间参考
	/// \return 
	virtual GsSpatialReference* SpatialReference();
	
	/// \brief 获取地物类对象指针
	/// \return 
	virtual GsFeatureClass* FeatureClass();
	/// \brief 设置地物类
	/// \param vFeaClass 
	virtual void FeatureClass(GsFeatureClass* vFeaClass);

	/// \brief 获取Renderer对象
	/// \return 
	virtual GsFeatureRenderer* Renderer();
	/// \brief 设置Renderer对象
	/// \param pRender 
	virtual void Renderer(GsFeatureRenderer* pRender);

	/// \brief 选择地物
	/// \param pFilter 查询条件
	/// \return 返回内部的选择集
	virtual GsSelectionSet* Select(GsQueryFilter* pFilter =  0);

	/// \brief 获取选择集
	/// \return 返回内部的选择集指针
	virtual GsSelectionSet* SelectionSet();

	/// \brief 清空选择集
	virtual void ClearSelection();

	
	/// \brief 图层是否存在选择集
	/// \return 
	virtual bool HasSelection();

	/// \brief 获取投影变换类型
	/// \return 
	virtual GsProjectionStyle ProjectionStyle();
	/// \brief 设置投影变换类型
	/// \param eStyle 
	virtual void ProjectionStyle(GsProjectionStyle eStyle);
	
	 /// \brief 获取强制投影时源空间参考
	/// \return 
	virtual GsSpatialReference* SourceSpatialReference();
	/// \brief 设置强制投影时源空间参考
	/// \param soruce 
	virtual void SpatialReference(GsSpatialReference* soruce);
	
	/// \brief 是否有效
	/// \return 
	virtual bool IsValid();

	/// \brief 开图时的过滤条件
	/// \param pFilter 
	virtual void DisplayFilter(GsQueryFilter* pFilter);
	/// \brief 
	/// \return 
	virtual GsQueryFilter *DisplayFilter();


	/// \brief 克隆图层
	/// \return 
	virtual GsLayerPtr Clone();
	/// \brief 选择集Renderer获取
	/// \return 
	virtual GsFeatureRenderer* SelectionRenderer();
	/// \brief 选择集Renderer设置
	/// \param pRender 
	virtual void SelectionRenderer(GsFeatureRenderer* pRender);
};
/// \brief GsFeatureLayerPtr
GS_SMARTER_PTR(GsFeatureLayer);

/// \brief 栅格图层的显示样式
enum GsRasterLayerShowStyle
{
	/// \brief 显示数据
	eShowRaster = 0x1,

	/// \brief 显示边界
	eShowBoundary = 0x2,

	/// \brief 显示轮廓
	eShowFootPrint = 0x4,
};

class GS_API GsRasterLayer:public GsLayer
{
	GsRasterClassPtr m_ptrRasterClass; 
	GsRasterResampleAlg m_eResampleAlg;//获取数据时候的插值算法
	GsRasterLayerShowStyle m_eRasterLayerShowStyle;//三个图层的显示样式
	GsRasterRendererPtr m_ptrRasterRenderer;
	/// \brief 镶嵌数据集的外边框（边界）
	GsSymbolPtr m_ptrBoundarySym;
	/// \brief 镶嵌数据集的内边框（轮廓）
	GsSymbolPtr m_ptrFootPrintSym;

	/// \brief 绘制边界框和轮廓框
	/// \param pDisplay 显示对象
	/// \param pCancel 绘制取消对象
	/// \return 返回是否绘制成功
	bool DrawBoundarys(GsDisplay* pDisplay, GsTrackCancel* pCancel);
protected:

	/// \brief 绘制方法入口
	/// \param pDisplay 显示对象
	/// \param pCancel 绘制取消对象
	/// \param eDrawPhase 绘制的阶段
	/// \return 返回是否绘制成功
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);
public:
	/// \brief 设置栅格数据集
	/// \param pRasterClass 栅格数据集
	GsRasterLayer(GsRasterClass* pRasterClass);

	/// \brief 根据RasterClass创建缺省的RasterRenderer
	/// \param pRasterClass 栅格数据集
	/// \return 
	static GsRasterRendererPtr CreateRasterRenderer(GsRasterClass *pRasterClass);

	/// \brief 获取插值算法
	/// \return 
	GsRasterResampleAlg  ResampleAlg();
	/// \brief 设置插值算法
	/// \param alg 
	void ResampleAlg(GsRasterResampleAlg  alg);

	
	/// \brief 图层的地理范围
	/// \param pTargetSR 以该空间参考返回范围
	/// \return 返回范围
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0);
	/// \brief 获取栅格类对象指针
	/// \return 返回栅格类指针
	GsRasterClass* RasterClass();
	/// \brief 设置栅格类
	/// \param pRasterClass 
	void RasterClass(GsRasterClass* pRasterClass);
	
	/// \brief 图层是否存在选择集
	/// \return 返回是否存在选择集
	virtual bool HasSelection();
	/// \brief 是否有效
	/// \return 返回是否有效
	virtual bool IsValid();

	/// \brief 图层的空间参考
	/// \return 返回空间参考
	virtual GsSpatialReference* SpatialReference();

	/// \brief 获取Renderer对象
	/// \return 返回栅格数据渲染器
	GsRasterRenderer *Renderer();

	/// \brief 设置Renderer对象
	/// \param pRenderer 栅格数据渲染器
	void Renderer(GsRasterRenderer *pRenderer);

	/// \brief 获取显示的样式
	/// \return 返回当前的样式
	GsRasterLayerShowStyle RasterLayerShowStyle();

	/// \brief 设置显示的样式
	/// \param style 样式
	void RasterLayerShowStyle(GsRasterLayerShowStyle style);
	
	/// \brief 设置镶嵌数据集的外边框（边界）
	/// \param pSym 外边框线符号
	void BoundarySymbol(GsSymbol* pSym);
	/// \brief 获取镶嵌数据集的外边框（边界）
	/// \return 返回外边框线符号
	GsSymbol* BoundarySymbol();

	/// \brief 设置镶嵌数据集的内边框（轮廓）
	/// \param pSym 轮廓线符号
	void FootPrintSymbol(GsSymbol* pSym);
	/// \brief 获取镶嵌数据集的内边框（轮廓）
	/// \return 返回轮廓线符号
	GsSymbol* FootPrintSymbol();

	/// \brief 克隆
	/// \return 返回克隆后的对象。
	virtual GsLayerPtr Clone();

};
/// \brief GsRasterLayerPtr
GS_SMARTER_PTR(GsRasterLayer);


/// \brief 瓦片类图层
class GS_API GsTileLayer:public GsLayer
{
protected:
	GsTileClassPtr m_ptrTileClass;
	/// \brief 是否进行同步绘制
	bool		m_bSynchronization;
	Utility::GsBackgroundTaskPtr m_ptrTask;
	Utility::GsBackgroundPtr m_ptrBackground;
protected:
	//进行同步绘制
	/// \brief 
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \param level 
	/// \param nMinRow 
	/// \param nMinCol 
	/// \param nMaxRow 
	/// \param nMaxCol 
	/// \return 
	bool SynchronizationDrawTile(GsDisplay* pDisplay, GsTrackCancel* pCancel, GsDrawPhase eDrawPhase, int level,int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	//进行异步绘制
	/// \brief 
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \param level 
	/// \param nMinRow 
	/// \param nMinCol 
	/// \param nMaxRow 
	/// \param nMaxCol 
	/// \return 
	bool AsynchronizationDrawTile(GsDisplay* pDisplay, GsTrackCancel* pCancel, GsDrawPhase eDrawPhase, int level, int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);

	/// \brief 绘制方法入口
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \return 
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);
public:
	/// \brief 
	/// \param pTileClass 
	GsTileLayer(GsTileClass* pTileClass);
	~GsTileLayer();

	/// \brief 是否进行同步绘制
	/// \return 
	bool Synchronization();
	/// \brief 是否进行同步绘制
	/// \param bSync 
	void Synchronization(bool bSync);

	/// \brief 图层的地理范围
	/// \param pTargetSR 以该空间参考返回范围
	/// \return 
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0);
	/// \brief 获取瓦片类对象指针
	/// \return 
	GsTileClass* TileClass();
	/// \brief 设置瓦片类
	/// \param vTileClass 
	void TileClass(GsTileClass* vTileClass);
	
	/// \brief 图层是否存在选择集
	/// \return 
	virtual bool HasSelection();
	/// \brief 是否有效
	/// \return 
	virtual bool IsValid();

	/// \brief 图层的空间参考
	/// \return 
	virtual GsSpatialReference* SpatialReference();

	/// \brief 克隆图层
	/// \return 
	virtual GsLayerPtr Clone();

};
/// \brief GsTileLayerPtr
GS_SMARTER_PTR(GsTileLayer);

/// \brief 鼠标按钮
enum GsButton
{
	/// \brief 没有按下任何键
	eNoneButton = 0,
	/// \brief 鼠标左键
	eLeftButton = 1,
	/// \brief 鼠标右键
	eRightButton = 2,
	/// \brief 鼠标中键
	eMiddleButton = 4,
};

/// \brief 键盘按钮
enum GsKey
{
	eKeyEscape = 0x01000000,                // misc keys
	eKeyTab = 0x01000001,
	eKeyBacktab = 0x01000002,
	eKeyBackspace = 0x01000003,
	eKeyReturn = 0x01000004,
	eKeyEnter = 0x01000005,
	eKeyInsert = 0x01000006,
	eKeyDelete = 0x01000007,
	eKeyPause = 0x01000008,
	eKeyPrint = 0x01000009,               // print screen
	eKeySysReq = 0x0100000a,
	eKeyClear = 0x0100000b,
	eKeyHome = 0x01000010,                // cursor movement
	eKeyEnd = 0x01000011,
	eKeyLeft = 0x01000012,
	eKeyUp = 0x01000013,
	eKeyRight = 0x01000014,
	eKeyDown = 0x01000015,
	eKeyPageUp = 0x01000016,
	eKeyPageDown = 0x01000017,
	eKeyShift = 0x01000020,                // modifiers
	eKeyControl = 0x01000021,
	eKeyMeta = 0x01000022,
	eKeyAlt = 0x01000023,
	eKeyCapsLock = 0x01000024,
	eKeyNumLock = 0x01000025,
	eKeyScrollLock = 0x01000026,
	eKeyF1 = 0x01000030,                // function keys
	eKeyF2 = 0x01000031,
	eKeyF3 = 0x01000032,
	eKeyF4 = 0x01000033,
	eKeyF5 = 0x01000034,
	eKeyF6 = 0x01000035,
	eKeyF7 = 0x01000036,
	eKeyF8 = 0x01000037,
	eKeyF9 = 0x01000038,
	eKeyF10 = 0x01000039,
	eKeyF11 = 0x0100003a,
	eKeyF12 = 0x0100003b,
	eKeyF13 = 0x0100003c,
	eKeyF14 = 0x0100003d,
	eKeyF15 = 0x0100003e,
	eKeyF16 = 0x0100003f,
	eKeyF17 = 0x01000040,
	eKeyF18 = 0x01000041,
	eKeyF19 = 0x01000042,
	eKeyF20 = 0x01000043,
	eKeyF21 = 0x01000044,
	eKeyF22 = 0x01000045,
	eKeyF23 = 0x01000046,
	eKeyF24 = 0x01000047,
	eKeyF25 = 0x01000048,                // F25 .. F35 only on X11
	eKeyF26 = 0x01000049,
	eKeyF27 = 0x0100004a,
	eKeyF28 = 0x0100004b,
	eKeyF29 = 0x0100004c,
	eKeyF30 = 0x0100004d,
	eKeyF31 = 0x0100004e,
	eKeyF32 = 0x0100004f,
	eKeyF33 = 0x01000050,
	eKeyF34 = 0x01000051,
	eKeyF35 = 0x01000052,
	eKeySuper_L = 0x01000053,                 // extra keys
	eKeySuper_R = 0x01000054,
	eKeyMenu = 0x01000055,
	eKeyHyper_L = 0x01000056,
	eKeyHyper_R = 0x01000057,
	eKeyHelp = 0x01000058,
	eKeyDirection_L = 0x01000059,
	eKeyDirection_R = 0x01000060,
	eKeySpace = 0x20,                // 7 bit printable ASCII
	eKeyAny = eKeySpace,
	eKeyExclam = 0x21,
	eKeyQuoteDbl = 0x22,
	eKeyNumberSign = 0x23,
	eKeyDollar = 0x24,
	eKeyPercent = 0x25,
	eKeyAmpersand = 0x26,
	eKeyApostrophe = 0x27,
	eKeyParenLeft = 0x28,
	eKeyParenRight = 0x29,
	eKeyAsterisk = 0x2a,
	eKeyPlus = 0x2b,
	eKeyComma = 0x2c,
	eKeyMinus = 0x2d,
	eKeyPeriod = 0x2e,
	eKeySlash = 0x2f,
	eKey0 = 0x30,
	eKey1 = 0x31,
	eKey2 = 0x32,
	eKey3 = 0x33,
	eKey4 = 0x34,
	eKey5 = 0x35,
	eKey6 = 0x36,
	eKey7 = 0x37,
	eKey8 = 0x38,
	eKey9 = 0x39,
	eKeyColon = 0x3a,
	eKeySemicolon = 0x3b,
	eKeyLess = 0x3c,
	eKeyEqual = 0x3d,
	eKeyGreater = 0x3e,
	eKeyQuestion = 0x3f,
	eKeyAt = 0x40,
	eKeyA = 0x41,
	eKeyB = 0x42,
	eKeyC = 0x43,
	eKeyD = 0x44,
	eKeyE = 0x45,
	eKeyF = 0x46,
	eKeyG = 0x47,
	eKeyH = 0x48,
	eKeyI = 0x49,
	eKeyJ = 0x4a,
	eKeyK = 0x4b,
	eKeyL = 0x4c,
	eKeyM = 0x4d,
	eKeyN = 0x4e,
	eKeyO = 0x4f,
	eKeyP = 0x50,
	eKeyQ = 0x51,
	eKeyR = 0x52,
	eKeyS = 0x53,
	eKeyT = 0x54,
	eKeyU = 0x55,
	eKeyV = 0x56,
	eKeyW = 0x57,
	eKeyX = 0x58,
	eKeyY = 0x59,
	eKeyZ = 0x5a,
};
/// \brief 屏幕绘制
class GS_API GsSymbolTracker:public Utility::GsRefObject 
{ 

public:
	/// \brief Tracker绘制的反馈
	enum GsTrackerFeedBack
	{
		/// \brief 通知Tracker什么也不做，保持Tracker当前的状态。
		eDoNothing,
		/// \brief 通知Tracker重新启动
		eRestartTracker,
		/// \brief 结束Tracker，Tracker将被销毁
		eFinishTracker,
	};

	/// \brief 
	/// \param pView 
	GsSymbolTracker(GsActiveView* pView);
	/// \brief 
	/// \param pMap 
	GsSymbolTracker(GsMap* pMap);
	virtual ~GsSymbolTracker();

	/// \brief 设置绘制用的符号
	/// \param sym 
	void Symbol(GsSymbol* sym);
	/// \brief 
	/// \return 
	GsSymbol* Symbol();

	/// \brief 重置
	virtual void Reset();
	
	/// \brief 将Tracker从Map绘制消息分离，此行为会导致Tracker不可使用，随后用于销毁
	virtual void Detach();

	/// \brief Geometry绘制完成的事件
	/// \details 参数1 
	Utility::GsDelegate<GsTrackerFeedBack(GsGeometry*)> OnGeometryTracked;

	/// \brief 接收鼠标双击消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseDoubleClick(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	/// \brief 接收鼠标按下消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseDown(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标弹起消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseUp(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标移动消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseMove(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标滚轮消息
	/// \param eButton 
	/// \param nDelta 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseWheel(GsButton eButton,int nDelta,int nKeyboard,const Utility::GsPT& pt);
	 
	/// \brief 获取Tracker所绑定的视图对象
	/// \return 
	GsActiveView* View(); 
	/// \brief 获取Tracker所绑定的地图对象
	/// \return 
	GsMap* Map();

	
protected:
	GsActiveViewPtr m_ptrView;
	GsDisplayTransformationPtr m_ptrDT;
	GsSymbolPtr m_ptrSymbol;
	Utility::GsLock m_Lock;
	
	/// \brief 将屏幕坐标点转换为地理坐标点
	/// \param pt 
	/// \return 
	GsRawPoint ToMaPoint(const Utility::GsPT& pt);
	/// \brief tracker绘制函数，子类通过覆盖此函数绘制内容。
	/// \param pDisp 
	virtual void OnTrackerDraw(GsDisplay* pDisp);
	/// \brief Geometry绘制完成时发生
	/// \param geo 
	/// \return 
	virtual GsTrackerFeedBack FireOnGeometryTracked(GsGeometry* geo);
	/// \brief Tracker绘制对象之前发生
	/// \param pDisp 
	/// \param geo 
	/// \param sym 
	/// \return 
	virtual int BeforeTrackerDraw(GsDisplay* pDisp,GsGeometry* geo,GsSymbol* sym);
	/// \brief Tracker绘制对象之后发生
	/// \param pDisp 
	/// \param geo 
	/// \param sym 
	/// \return 
	virtual int AfterTrackerDraw(GsDisplay* pDisp, GsGeometry* geo, GsSymbol* sym);

};
/// \brief GsSymbolTrackerPtr
GS_SMARTER_PTR(GsSymbolTracker);


/// \brief 屏幕绘制矩形的Tracker
class GS_API GsNewEnvelopeTracker:public GsSymbolTracker
{
	GsEnvelopePtr m_ptrEnvelope;
	/// \brief tracker绘制函数，子类通过覆盖此函数绘制内容。
	/// \param pDisp 
	virtual void OnTrackerDraw(GsDisplay* pDisp);
	volatile bool m_bStart,m_bMouseMove;
	GsRawPoint m_First,m_Second;
protected:
	/// \brief 成功绘制一个矩形，如果返回false则后续事件和刷新不会执行
	/// \param first 
	/// \param second 
	/// \return 
	virtual bool OnEnvelopeTracked(const GsRawPoint& first, const GsRawPoint& second);

	/// \brief 正在绘制矩形
	/// \param first 
	/// \param second 
	/// \return 
	virtual bool OnEnvelopeTracking(const GsRawPoint& first, const GsRawPoint& second);
public:
	/// \brief 
	/// \param pMap 
	GsNewEnvelopeTracker(GsActiveView* pMap);
	virtual ~GsNewEnvelopeTracker();

	/// \brief 重置
	virtual void Reset();
	/// \brief 接收鼠标按下消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseDown(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标弹起消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseUp(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标移动消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseMove(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
};
/// \brief GsNewEnvelopeTrackerPtr
GS_SMARTER_PTR(GsNewEnvelopeTracker);

/// \brief 屏幕绘制矩形的Tracker
class GS_API GsNewPolylineTracker :public GsSymbolTracker
{ 
	GsPolylinePtr m_ptrPolyline;
	GsRawPoint	m_Point[3];
	GsCircleArcPtr m_ptrArc;
	GsLinePtr	m_ptrLine;
	int			m_PointCount, m_MaxPoint;
	bool		m_bDblClickFinish;
	/// \brief tracker绘制函数，子类通过覆盖此函数绘制内容。
	/// \param pDisp 
	virtual void OnTrackerDraw(GsDisplay* pDisp);
	/// \brief 
	/// \param polyline 
	/// \return 
	GsPolylinePtr MakeGeometry(GsPolyline* polyline);
public:
	/// \brief 
	/// \param Map 
	GsNewPolylineTracker(GsActiveView* Map);
	virtual ~GsNewPolylineTracker();
	
	/// \brief 是否使用双击鼠标结束Tracker，false则用右键结束
	/// \return 
	bool DoubleClickToFinish();
	/// \brief 
	/// \param value 
	void DoubleClickToFinish(bool value);
	
	/// \brief 结束Tracker,如果无法成功构成Geometry则返回false
	/// \return 
	bool FinishTracker();


	/// \brief 是否绘制Arc
	/// \return 
	bool Arc();
	/// \brief 
	/// \param arc 
	void Arc(bool arc);
	/// \brief 重置
	virtual void Reset();
	 
	/// \brief 接收鼠标弹起消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseUp(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	/// \brief 接收鼠标移动消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseMove(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	/// \brief 接收鼠标双击消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseDoubleClick(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);

};
/// \brief GsNewPolylineTrackerPtr
GS_SMARTER_PTR(GsNewPolylineTracker);

/// \brief 绘制点的Tracker
class GS_API GsNewPointTracker :public GsSymbolTracker
{
	/// \brief tracker绘制函数，子类通过覆盖此函数绘制内容。
	/// \param pDisp 
	virtual void OnTrackerDraw(GsDisplay* pDisp);
public:
	/// \brief 
	/// \param pView 
	GsNewPointTracker(GsActiveView* pView);
	~GsNewPointTracker();
	/// \brief 接收鼠标弹起消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseUp(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	

};
/// \brief GsNewPointTracker Ptr
GS_SMARTER_PTR(GsNewPointTracker);

/// \brief 缩放Tracker
class GS_API GsZoomTracker :public GsNewEnvelopeTracker
{
public:
	enum GsZoomType
	{
		/// \brief 放大
		eZoomIn,
		/// \brief 缩小
		eZoomOut,
		/// \brief 仿CAD模式从左向右拉框放大，从右到左拉框缩小
		eZoomInOutLikeCAD,
	};
public:
	/// \brief 范围变化
	/// \details 参数1 
	Utility::GsDelegate<void(const GsBox&)> OnExtentChanged;
public:
	/// \brief 
	/// \param pView 
	/// \param eType 
	GsZoomTracker(GsActiveView* pView, GsZoomType eType);
	~GsZoomTracker();
protected:
	/// \brief 成功绘制一个矩形，如果返回false则后续事件和刷新不会执行
	/// \param first 
	/// \param second 
	/// \return 
	virtual bool OnEnvelopeTracked(const GsRawPoint& first, const GsRawPoint& second);
private:
	GsZoomType m_eType;
	/// \brief 
	/// \param extent 
	void ZoomTo(const GsBox& extent);
};
/// \brief GsZoomTracker 
GS_SMARTER_PTR(GsZoomTracker);

/// \brief 经典漫游Tracker
class GS_API GsZoomPanClassicTracker :public GsSymbolTracker
{
	bool m_bMoved;
	unsigned long long m_TickWheel;
public:
	/// \brief 
	/// \param view 
	GsZoomPanClassicTracker(GsActiveView* view);

	/// \brief 接收鼠标按下消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseDown(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	/// \brief 接收鼠标弹起消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseUp(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	/// \brief 接收鼠标移动消息
	/// \param eButton 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseMove(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	/// \brief 接收鼠标滚轮消息
	/// \param eButton 
	/// \param nDelta 
	/// \param nKeyboard 
	/// \param pt 
	virtual void OnMouseWheel(GsButton eButton, int nDelta, int nKeyboard, const Utility::GsPT& pt);
public:
	/// \brief 范围变化
	/// \details 参数1 
	Utility::GsDelegate<void(const GsBox&)> OnExtentChanged;
};
/// \brief GsZoomPanClassicTrackerPtr
GS_SMARTER_PTR(GsZoomPanClassicTracker);


/// \brief 基于内存的影像画布
class GS_API GsAggMemoryImageCanvas:public GsImageCanvas
{
protected:
	void* m_pHandle;
protected:
	GsAggMemoryImageCanvas();

public:
	using GsCanvas::RenderingOrigin;
	using GsCanvas::Clip;
	using GsCanvas::DrawLine;
	using GsCanvas::DrawImage;
	using GsCanvas::DrawString;
	using GsCanvas::CreateImage;

	/// \brief 根据宽和高构建RGBA32位色的画布
	/// \param w 
	/// \param h 
	/// \param dpi 
	GsAggMemoryImageCanvas(int w, int h, float dpi=96);

	/// \brief 从编码的栅格数据构造
	/// \param img 
	/// \param nLen 
	/// \param dpi 
	GsAggMemoryImageCanvas(const unsigned char* img,int nLen, float dpi = 96);
	/// \brief 从编码的栅格文件构造
	/// \param filename 
	/// \param dpi 
	GsAggMemoryImageCanvas(const char* filename, float dpi = 96);

	virtual ~GsAggMemoryImageCanvas();
	 
	/// \brief 设置绘制起算的原点
	/// \param pt 
	virtual void RenderingOrigin(const Utility::GsPT& pt);

	/// \brief 创建一个裁切范围
	/// \param path 
	/// \return 
	virtual GsRegionPtr CreateRegion(GsGraphicsPath*  path);
	/// \brief 创建一个裁切范围
	/// \param rect 
	/// \return 
	virtual GsRegionPtr CreateRegion(const Utility::GsRect& rect);
	/// \brief 设置path作为的裁切范围
	/// \param region 
    virtual void Clip(GsRegion *  region);
    /// \brief 清除裁切范围
    virtual void ClearClip();

	/// \brief 获取绘制的位图
	/// \return 
	virtual Utility::GsImage* Image();
	
	/// \brief 创建一个和当前画布兼容的Image画布
	/// \param width 画布的高度
	/// \param height 画布的宽度
	/// \return 
	virtual GsImageCanvasPtr CreateCompatibleImageCanvas(int width,int height);

	/// \brief 创建画笔对象
	/// \param color 画笔的颜色
	/// \param fWidth 画笔的宽度，像素单位
    /// \returns 返回创建的画笔对象指针
	virtual GsPenPtr CreatePen(const Utility::GsColor& color,float fWidth = 1.0f);

	/// \brief 从画刷创建画笔对象
	/// \param pBrush 画刷
	/// \param fWidth 画笔的宽度，像素单位
    /// \returns 返回创建的画笔对象指针
	virtual GsPenPtr CreatePen(GsBrush* pBrush,float fWidth = 1.0f);

	/// \brief 绘制多个点连续的线 
	/// \param pCoord 坐标数组指针，以X，Y坐标连续存储
	/// \param nPointCount 坐标点的数量
	/// \param pPen 绘制的画笔
	/// \returns 返回绘制是否成功
	virtual bool DrawLine(float* pCoord,int nPointCount,GsPen* pPen);
	 

	/// \brief 绘制Pie轮廓
	/// \param rect Pie所在椭圆的外接矩形范围
	/// \param start_angle 饼的开始角度
	/// \param sweepAngle 饼的旋转角度
	/// \param pPen 绘制的画笔
	/// \returns 返回绘制是否成功
	virtual bool DrawPie(const Utility::GsRectF  &rect,float start_angle,float sweepAngle,GsPen* pPen);

	/// \brief 填充Pie
	/// \param rect Pie所在椭圆的外接矩形范围
	/// \param start_angle 饼的开始角度
	/// \param sweepAngle 饼的旋转角度
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillPie(const Utility::GsRectF  &rect,float start_angle,float sweepAngle,GsBrush* pBrush);

	/// \brief 
	/// \param rect 
	/// \param pPen 
	/// \return 
	virtual bool DrawRectangle(const Utility::GsRectF& rect, GsPen* pPen);
	/// \brief 
	/// \param rect 
	/// \param pBrush 
	/// \return 
	virtual bool FillRectangle(const Utility::GsRectF& rect, GsBrush* pBrush);

	/// \brief 
	/// \param rect 
	/// \param pPen 
	/// \return 
	virtual bool DrawEllipse(const Utility::GsRectF& rect, GsPen* pPen);
	/// \brief 
	/// \param rect 
	/// \param pBrush 
	/// \return 
	virtual bool FillEllipse(const Utility::GsRectF& rect, GsBrush* pBrush);

	/// \brief 绘制图片的特定部分到特定范围 
	/// \param pImg 要绘制的图片
	/// \param source 图片要绘制的范围 
	/// \param target 要绘制到的目标范围
	/// \returns 返回绘制是否成功
	/// \param effect 
	virtual bool DrawImage(Utility::GsImage* pImg,const Utility::GsRect& source,const Utility::GsRectF& target,GsImageEffect* effect);

	
	/// \brief 从内存块直接创建图像对象
	/// \param strData 图像的内存块
	/// \param nLen 内存块的长度
	/// \return 返回图像对象
	virtual Utility::GsImagePtr CreateImage(const unsigned char* strData,int nLen);
	
	/// \brief 创建路径对象 
    /// \returns 返回创建的路径对象指针
	virtual GsGraphicsPathPtr CreatePath();

	/// \brief 绘制路径 
	/// \param pPath 要绘制的路径
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawPath(GsGraphicsPath* pPath,GsPen* pPen) ;

	
	/// \brief 填充路径 
	/// \param pPath 要填充的路径
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillPath(GsGraphicsPath* pPath,GsBrush* pBrush);

	/// \brief 绘制圆弧
	/// \param rect 要绘制圆弧的外接矩形
	/// \param dblStartAngle 开始角度
	/// \param dblSweepAngle 圆弧旋转的角度（单位度）
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawArc(const Utility::GsRectF& rect, float dblStartAngle, float dblSweepAngle, GsPen* pPen);

	/// \brief 用特定颜色清空整个画布  
	/// \param color 要清空的颜色  
	/// \returns 返回绘制是否成功 
	virtual bool Clear(const Utility::GsColor& color);
	 
	/// \brief 提交未提交的绘制数据   
	/// \returns 返回提交是否成功 
	virtual  bool Flush();

	/// \brief 绘制字符串
	/// \returns 返回提交是否成功 
	/// \param strText 
	/// \param nLen 
	/// \param pBrush 
	/// \param eLayout 
	/// \param pFormat 
	virtual bool DrawString(const char* strText,int nLen,GsBrush* pBrush,const Utility::GsRectF& eLayout,GsStringFormat* pFormat);
	
	/// \brief 计算字符串绘制大小
	/// \returns 返回计算是否成功 
	/// \param strText 
	/// \param nLen 
	/// \param eLayout 
	/// \param pFormat 
	virtual bool MeasureString(const char* strText,int nLen, Utility::GsRectF &eLayout,GsStringFormat* pFormat);

	/// \brief 
	/// \return 
	virtual bool Available();

	/// \brief 设置绘制效果
	/// \param effect 
	virtual void ImageEffect(GsImageEffect* effect);

	/// \brief 绘制效果
	/// \return 
	virtual GsImageEffectPtr ImageEffect();
};
/// \brief GsAggMemoryImageCanvasPtr
GS_SMARTER_PTR(GsAggMemoryImageCanvas);
typedef GsAggMemoryImageCanvasPtr GsMemoryImageCanvasPtr;
typedef GsAggMemoryImageCanvas GsMemoryImageCanvas;

/// \brief 基于文件的影像画布
/// \details 基于文件的影像画布可以实现超过内存存储限制的画布，画布通过和文件直接IO实现超大画布的绘制能力。性能上到低于基于内存的画布
class GS_API GsFileImageCanvas:public GsAggMemoryImageCanvas
{
public:
	/// \brief 根据文件名和宽高构建RGBA32位色的画布
	/// \param strFile PAM文件路径。
	/// \param w PAM图像的宽度
	/// \param h PAM图像的高度
	/// \param nMaxMemoryCache 缓存图形的行数据在内存中最多花费多少内存
	/// \param fDPI 分辨率
	GsFileImageCanvas(const char* strFile,int w,int h,int nMaxMemoryCache=0x100000,float fDPI=96.0f);
	virtual ~GsFileImageCanvas();
};
/// \brief GsFileImageCanvasPtr
GS_SMARTER_PTR(GsFileImageCanvas);

/// \brief 样式表
class GS_API GsStyleTable : public Utility::GsRefObject
{
protected:
	GsStyleTable();
public:
	virtual ~GsStyleTable();
	/// \brief 获取式样的内容
	/// \param contentname 
	/// \param buff 
	/// \return 
	virtual bool Content(const char* contentname,Utility::GsByteBuffer* buff) = 0;


	/// \brief 设置式样的内容
	/// \param contentname 
	/// \param blob 
	/// \param len 
	/// \return 
	virtual bool Content(const char* contentname,const unsigned char* blob,int len) = 0;

	/// \brief 指定范围内的字体产生为Protobuffer格式的栅格。
	/// \param fontFamily 字体名称
	/// \param style 字体风格(Regular、Bold等)
	/// \param size 字符大小(默认24)
	/// \param nStartCode 字符开始编号
	/// \param nEndCode 字符结束编号
	/// \param buff 返回的内存块
	/// \returns 返回执行是否成功 
	virtual bool GenerateRasterGlyph(const char* fontFamily,const char* style,float size,int nStartCode,int nEndCode,Utility::GsByteBuffer* buff) = 0;

	/// \brief 获得样式表名字
	/// \returns 返回样式表名字
	Utility::GsString Name();

	/// \brief 获得样式表版本
	/// \returns 返回样式表版本
	Utility::GsString Version();

	/// \brief 保存样式表为本地json文件
	/// \param strPath 
	virtual void SaveJson(const char *strPath);
	/// \brief 保存样式表为本地xml文件
	/// \param strPath 
	virtual void SaveXml(const char *strPath);
	/// \brief 保存样式表为本地地图定义文件
	/// \param strPath 
	virtual void SaveMapDefine(const char *strPath);

protected:
	Utility::GsString m_sName;
	Utility::GsString m_sVersion;
};
/// \brief GsStyleTablePtr
GS_SMARTER_PTR(GsStyleTable);

/// \brief 样式表类厂
/// \details 通过载入各种格式的文件创建样式表对象实例
class GS_API GsStyleTableFactory : public Utility::GsRefObject
{
public:
	GsStyleTableFactory(){}
	virtual ~GsStyleTableFactory(){}
	/// \brief 从Zip包二进制文件打开
	/// \param blob 
	/// \param nLen 
	/// \return 
	GsStyleTablePtr OpenFromZip(const unsigned char* blob,int nLen);
	/// \brief 从Zip包二进制文件打开
	/// \param strFile 
	/// \return 
	GsStyleTablePtr OpenFromZip(const char* strFile);
	/// \brief 从文件夹打开
	/// \param strFolder 
	/// \return 
	GsStyleTablePtr OpenFromFolder(const char* strFolder);

	/// \brief 从json文件构造样式表实例
	/// \param strJson 
	/// \param bIsFile 
	/// \return 
	GsStyleTablePtr OpenFromJson(const char *strJson,bool bIsFile = false);
	/// \brief 从xml构造样式表实例
	/// \param strXML 
	/// \param bIsFile 
	/// \return 
	GsStyleTablePtr OpenFromXml(const char *strXML,bool bIsFile = false);
	/// \brief 从地图定义文件构造样式表实例
	/// \param strFilePath 
	/// \param pPyramid 
	/// \return 
	GsStyleTablePtr OpenFromMapDefine(const char *strFilePath, GsPyramid* pPyramid = 0);
	/// \brief 构建一个空的样式表实例
	/// \return 
	GsStyleTablePtr CreateEmptyStyleTable();
};
/// \brief GsStyleTableFactoryPtr
GS_SMARTER_PTR(GsStyleTableFactory);

/// \brief 绘制矢量瓦片数据Renderer的抽象基类
class GS_API GsVectorTileRenderer : public GsRenderer
{
protected:
	double m_DPI;
	/// \brief 过滤绘制图层
	Utility::GsVector<Utility::GsString> m_FilterLayerNames;
	/// \brief 过滤绘制样式
	Utility::GsVector<Utility::GsString> m_FilterStyleNames;
protected:
	/// \brief 
	/// \param pImageCanvas 
	/// \param pGsPyramid 
	GsVectorTileRenderer(GsImageCanvas *pImageCanvas, GsPyramid *pGsPyramid);
	/// \brief 
	/// \param nWidth 
	/// \param nHeight 
	/// \param pGsPyramid 
	GsVectorTileRenderer(int nWidth, int nHeight, GsPyramid *pGsPyramid);
	
	/// \brief 创建坐标转换对象
	/// \param l 
	/// \param r 
	/// \param c 
	/// \return 
	virtual GsDisplayTransformationPtr CreateDisplay(int l,int r,int c);

public:
	virtual ~GsVectorTileRenderer();
	
	/// \brief Render绘制的DPI
	/// \return 
	float DPI();
	/// \brief Render绘制的DPI
	/// \param dpi 
	void DPI(float dpi);

	/// \brief 清空画布
	/// \param c 
	void ClearCanvas(const Utility::GsColor &c = Utility::GsColor(255, 255, 255, 0));

	/// \brief 返回画布指针
	/// \return 
	GsImageCanvas *ImageCanvas();

	/// \brief 绘制瓦片类型矢量数据
	/// \param pCanvas 
	/// \param pDT 
	/// \param tileExtent 
	/// \param rect 
	/// \param pData 
	/// \param nLen 
	/// \param l 
	/// \param r 
	/// \param c 
	/// \return 
	virtual bool DrawVectorTile(GsCanvas *pCanvas,GsDisplayTransformation* pDT,
					const GsBox& tileExtent,const Utility::GsRect& rect,const unsigned char* pData,int nLen,
					int l,int r,int c) = 0;

	/// \brief 绘制瓦片类型矢量数据
	/// \param pTile 
	/// \return 
	virtual bool DrawVectorTile(GsTile *pTile);

	/// \brief 绘制瓦片类型矢量数据
	/// \param pData 瓦片内存块
	/// \param nLen 内存块长度
	/// \param l 层号
	/// \param r 行号
	/// \param c 列号
	/// \return 
	virtual bool DrawVectorTile(const unsigned char* pData,int nLen,int l,int r,int c);
	
	/// \brief 得到过滤绘制图层
	/// \brief 显示时只绘制容器GsVector记录的图层，当GsVector未记录时，表示全绘制不进行过滤
	/// \return 
	Utility::GsVector<Utility::GsString>* FilterDrawLayerNames();

	/// \brief 得到过滤绘制的style
	/// \brief 显示时只绘制容器GsVector记录的style图层，当GsVector未记录时，表示全绘制不进行过滤
	/// \return 
	Utility::GsVector<Utility::GsString>* FilterDrawStyleNames();
protected:
	/// \brief 画布对象
	GsImageCanvasPtr m_ptrImageCanvas;
	/// \brief 金字塔对象
	GsPyramidPtr m_ptrPyramid;
	/// \brief 坐标转换对象
	GsDisplayTransformationPtr m_ptrDT;
	/// \brief 瓦片GZip内存块
	Utility::GsGrowByteBuffer		m_ZipBuffer;
};
/// \brief GsVectorTileRendererPtr
GS_SMARTER_PTR(GsVectorTileRenderer);


/// \brief 基于样式表绘制矢量数据的Renderer
/// \details 样式表在本类中默认为json格式，但可扩展为其他多种格式。根据样式表创建符号，并用符号绘制传入的矢量数据，最终在内存中创建栅格图片
class GS_API GsStyledVectorTileRenderer: public GsVectorTileRenderer
{
public:
	enum GsDrawBehavior
	{
		eDrawVectorData,
		eDrawLabelData,
		eDrawVectorAndLabelData,
	};
public:
	using GsVectorTileRenderer::DrawVectorTile;
	/// \brief 通过画布和金字塔构造Renderer
	/// \param pImageCanvas 
	/// \param pGsPyramid 
	/// \param pStyleTable 
	GsStyledVectorTileRenderer(GsImageCanvas *pImageCanvas, GsPyramid *pGsPyramid,GsStyleTable *pStyleTable = NULL);

	/// \brief 通过画布长，宽和金字塔构造Renderer
	/// \param nWidth 
	/// \param nHeight 
	/// \param pGsPyramid 
	/// \param pStyleTable 
	GsStyledVectorTileRenderer(int nWidth, int nHeight, GsPyramid *pGsPyramid,GsStyleTable *pStyleTable = NULL);
	virtual ~GsStyledVectorTileRenderer();

	/// \brief 设置样式表实例
	/// \param pStyleTable 
	void StyleTable(GsStyleTable *pStyleTable);
	/// \brief 获取样式表实例
	/// \return 
	GsStyleTable* StyleTable();
	 
	/// \brief 绘制瓦片类型矢量数据
	/// \param pCanvas 
	/// \param pDT 
	/// \param tileExtent 
	/// \param rect 
	/// \param pData 
	/// \param nLen 
	/// \param l 
	/// \param r 
	/// \param c 
	/// \return 
	virtual bool DrawVectorTile(GsCanvas *pCanvas,GsDisplayTransformation* pDT,const GsBox& tileExtent,const Utility::GsRect& rect,const unsigned char* pData,int nLen,
					int l,int r,int c);

	/// \brief 生成标注
	virtual void GenerateLabels();

	/// \brief 本地渲染设置标注参数容器
	/// \param pLabelContainer 
	void LabelContainer(GsLabelContainer* pLabelContainer);

	/// \brief 屏幕DT
	/// \param pDT 
	void ScreenDisplayTransformation(GsDisplayTransformation *pDT);

	/// \brief 绘制行为
	/// \param eDrawBehavior 
	void DrawBehavior(GsDrawBehavior eDrawBehavior);
	/// \brief 绘制方式
	/// \return 
	GsDrawBehavior DrawBehavior();

protected:
	/// \brief 转换标注样式
	void ConvertLabelProperty();
	/// \brief 根据几何维度获取自动标注对象（0：点  1：线  2：面）
	/// \param pLayerStyle 
	/// \param nDim 
	/// \return 
	GsLabelProperty* GetLabelProperty(LayerDrawStyle* pLayerStyle, int nDim);

	/// \brief 创建默认标注属性
	/// \param nDim 
	/// \return 
	GsLabelPropertyPtr CreateDefaultLabelProperty(int nDim);

	/// \brief 绘制瓦片记录
	/// \param pFeature 
	/// \param pLayerStyle 
	/// \param pLabelProp 
	void DrawTileFeature(GsMBFeature* pFeature, LayerDrawStyle* pLayerStyle, GsLabelProperty* pLabelProp);
	 
	/// \brief 判断是否是标注图层
	/// \param pLayerStyle 
	/// \return 
	bool IsLabelLayer(LayerDrawStyle *pLayerStyle);

	/// \brief 添加到碎片缓存
	/// \param strLayer 
	/// \param strLabel 
	/// \param nOID 
	/// \param pGeo 
	void AddPieceCache(const Utility::GsString& strLayer, const Utility::GsString& strLabel, long long nOID, GsGeometry *pGeo);

	/// \brief 合并碎片
	/// \param vecPieceCache 
	/// \param dTol 
	void UnionTilePiece(Utility::GsVector<void*>& vecPieceCache, double dTol);
protected:
	/// \brief 样式文件对象
	GsStyleTablePtr m_ptrStyleTable;
	/// \brief自动计算标注对象缓存
	Utility::GsStlMap<Utility::GsString, GsLabelPropertyPtr> m_mapLabelProp;
	/// \brief 地理到屏幕的坐标转换对象
	GsDisplayTransformationPtr m_ptrScreenDT;
	/// \brief 标注容器
	GsLabelContainerPtr m_pLabelContainer;
	/// \brief 绘制行为
	GsDrawBehavior m_eBehavior;
	/// \brief 几何缓存
	Utility::GsStlMap< Utility::GsString, Utility::GsVector<void*> > m_mapGeoCache;
	/// \brief 瓦片地理范围
	GsBox m_TileExtent;
};
/// \brief GsVectorStyleRenderer
GS_SMARTER_PTR(GsStyledVectorTileRenderer);


/// \brief GsSimpleVectorTileRenderer
/// \details 无样式配置的简单矢量瓦片渲染器，创建随机颜色样式的符号矢量数据
class GS_API GsSimpleVectorTileRenderer : public GsVectorTileRenderer
{
public:
	/// \brief 通过画布和金字塔构造Renderer
	/// \param pImageCanvas 
	/// \param pGsPyramid 
	GsSimpleVectorTileRenderer(GsImageCanvas* pImageCanvas, GsPyramid* pGsPyramid);

	/// \brief 通过画布长，宽和金字塔构造Renderer
	/// \param nWidth 
	/// \param nHeight 
	/// \param pGsPyramid 
	GsSimpleVectorTileRenderer(int nWidth, int nHeight, GsPyramid* pGsPyramid);
	virtual ~GsSimpleVectorTileRenderer();
	
	/// \brief 绘制瓦片类型矢量数据
	/// \param pCanvas 
	/// \param pDT 
	/// \param tileExtent 
	/// \param rect 
	/// \param pData 
	/// \param nLen 
	/// \param l 
	/// \param r 
	/// \param c 
	/// \return 
	virtual bool DrawVectorTile(GsCanvas *pCanvas,GsDisplayTransformation* pDT,const GsBox& tileExtent,const Utility::GsRect& rect,const unsigned char* pData,int nLen,
					int l,int r,int c);
private: 
	/// \brief 根据名称和几何类型获取符号
	/// \param szLyrName 
	/// \param eType 
	/// \return 
	GsSymbol* GetSymbol(const char* szLyrName, GsGeometryType eType);
private:
	/// \brief 符号缓存
	Utility::GsStlMap<Utility::GsString, GsSymbolPtr> m_mapSimpleSymbols;
};
/// \brief GsSimpleVectorTileRendererPtr
GS_SMARTER_PTR(GsSimpleVectorTileRenderer);


/// \brief GsVectorTileLayer
/// \details 矢量瓦片图层
class GS_API GsVectorTileLayer : public GsTileLayer
{
protected:
	/// \brief 绘制方法入口
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \return 
	virtual bool InnerDraw( GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase );
public:
	/// \brief 
	/// \param pTileClass 
	/// \param nMaxTileCache 
	GsVectorTileLayer(GsTileClass* pTileClass, int nMaxTileCache=100);
	virtual ~GsVectorTileLayer();

	/// \brief 获取Renderer对象
	/// \return 
	GsVectorTileRenderer* Renderer();

	/// \brief 设置Renderer对象
	/// \param pRender 
	void Renderer(GsVectorTileRenderer* pRender);

	/// \brief 清空
	void ClearCache();

private:
	/// \brief 渲染瓦片成图片
	/// \param pTile 
	/// \param pDT 
	/// \param extent 
	/// \param sx 
	/// \param sy 
	/// \return 
	Utility::GsImagePtr RenderTileImage(GsTile* pTile,GsDisplayTransformation* pDT,const GsBox& extent, int sx,int sy);

private:
	/// \brief 类型定义<GsImage, 瓦片id>
	typedef Utility::GsPair<Utility::GsImagePtr, unsigned long long> ImagePair;
	/// \brief 最大图片缓存
	int m_nMaxTileCache;
	/// \brief 矢量样式渲染对象
	GsVectorTileRendererPtr m_ptrRender;
	
	/// \brief 瓦片缓存
	Utility::GsList<ImagePair> m_lsTileImage;
	/// \brief 瓦片缓存索引(瓦片id, GsImage)
	Utility::GsStlMap<unsigned long long, Utility::GsList<ImagePair>::iterator> m_mapTileIndex;
};
/// \brief GsVectorTileLayerPtr
GS_SMARTER_PTR(GsVectorTileLayer);


/// \brief GsPyramidLayer
/// \details 金字塔网格图层
class GS_API GsPyramidLayer : public GsLayer
{
public:
	/// \brief 
	/// \param pPyramid 
	GsPyramidLayer(GsPyramid* pPyramid = 0);
	virtual ~GsPyramidLayer();

	/// \brief 内部绘制入口
	/// \details 子类通过覆盖此函数实现绘制。
	/// \param pDisplay 
	/// \param pCancel 
	/// \param eDrawPhase 
	/// \return 
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);

	/// \brief 图层的地理范围
	/// \param pTargetSR 以该空间参考返回范围
	/// \return 
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0);

	/// \brief 图层是否存在选择集
	/// \return 
	virtual bool HasSelection();

	/// \brief 是否有效
	/// \return 
	virtual bool IsValid();

	/// \brief 设置金字塔对象
	/// \param pPyramid 
	void Pyramid(GsPyramid* pPyramid);
	/// \brief 设置金字塔对象
	/// \return 
	GsPyramid* Pyramid();

	/// \brief 设置网格线颜色
	/// \param color 
	void GridColor(const Utility::GsColor& color);
	/// \brief 获取网格线颜色
	/// \return 
	Utility::GsColor GridColor();

	/// \brief 
	/// \return 
	virtual Utility::GsSmarterPtr<GsLayer> Clone() { return 0; }

private:
	/// \brief 金字塔对象
	GsPyramidPtr m_ptrPyramid;
	/// \brief 网格线颜色
	Utility::GsColor m_LineColor;
};
/// \brief GsPyramidLayerPtr
GS_SMARTER_PTR(GsPyramidLayer);

/// \brief GsFontFamily
/// \details 字体对象
class GS_API GsFontFamily:public Utility::GsRefObject
{
protected:
	GsFontFamily(){}
public:
	virtual ~GsFontFamily(){};

	/// \brief 从字体名称和式样构造
	/// \param fontname 
	/// \param style 
	/// \return 
	static Utility::GsSmarterPtr<GsFontFamily> CreateFontFamily(const char* fontname,GsFontStyle style);
	/// \brief 从字体文件构造
	/// \param fontfile 字体文件,*.ttf,*.ttc,*.font等
	/// \return 
	static Utility::GsSmarterPtr<GsFontFamily> CreateFontFamily(const char* fontfile);
	/// \brief 从内存块构造
	/// \param blob 
	/// \param nlen 
	/// \return 
	static Utility::GsSmarterPtr<GsFontFamily> CreateFontFamily(const unsigned char* blob,int nlen);
	
	/// \brief 将枚举的值字符串类型的式样
	/// \param style 
	/// \return 
	static Utility::GsString ConvertToString(GsFontStyle style);

	/// \brief 规范化字体的名称，将字体名称和式样的混合区分出名称和式样。
	/// \param fontNameAndStyle 
	/// \param style 
	/// \return 
	static Utility::GsString RegularFontName(const char* fontNameAndStyle,GsFontStyle& style);
	/// \brief 规范化字体的名称，将字体名称和式样的混合区分出名称和式样。
	/// \param fontNameAndStyle 
	/// \return 
	static GsTextSymbolPtr RegularFontName(const char* fontNameAndStyle);
	
	/// \brief 将字符串的式样转换为枚举值
	/// \param style 
	/// \return 
	static GsFontStyle ConvertToStyle(const Utility::GsString& style);
	/// \brief 将字符串的式样转换为枚举值
	/// \param style 
	/// \return 
	static GsFontStyle ConvertToStyle(const char* style);


	/// \brief 式样和字体自身的式样匹配程度
	/// \param style 
	/// \return 
	virtual int MatchStyle(GsFontStyle style) = 0;

	/// \brief 获取内部指针
	virtual void* Handle() = 0;
	
	/// \brief 获取字体的名称
	/// \return 
	virtual Utility::GsString FontName() = 0;
	
	/// \brief 获取字体的式样
	/// \return 
	virtual GsFontStyle Style() = 0;

	/// \brief 获取字体文件的路径
	/// \details 从内存中创建的字体将没有路径
	/// \return 
	virtual Utility::GsString FileName() = 0;

	/// \brief 重新开始遍历字体所有字符
	/// \details 获取字体内所有字符
	/// \return 
	virtual void Reset() = 0;

	/// \brief 遍历字体库中所有字符
	/// \params GsString & str 字符
	/// \details 返回utf8编码的字符
	/// \return  无字符返回false
	virtual bool Next(Utility::GsWString & str) = 0;
};
GS_SMARTER_PTR(GsFontFamily);

/// \brief 字体集合 
class GS_API GsFontCollection 
{
public:
	GsFontCollection();
	~GsFontCollection(void);
	/// \brief 枚举系统中有多少的字体
	/// \return 
	int FamilyCount();
	
	/// \brief 获取所有的字体
	/// \return 
	UTILITY_NAME::GsVector<GsFontFamilyPtr> Families();
	
	/// \brief 根据索引获取字体
	/// \param nIndex 
	/// \return 
	GsFontFamilyPtr Familiy(int nIndex);
};

//表达式相关解析所需参数
class GS_API GsExpressionContext2 : public Utility::GsRefObject
{
public:
	GsExpressionContext2();
	~GsExpressionContext2();
	/// \brief 设置表达式计算的要素
	void Feature(GsFeature* pFea);
	/// \brief 获取要素
	Kernel::GsFeature* Feature();
	/// \brief 设置符号，可用于动态改变符号参数
	void Symbol(GsSymbol* pSymbol);
	/// \brief 获取符号
	Kernel::GsSymbol* Symbol();
	/// \brief 设置当前图层，可参与表达式计算
	void Layer(GsLayer* pLayer);
	/// \brief 获取当前图层
	GsLayer* Layer();
	/// \brief 设置Display，可参与表达式计算
	void Display(GsDisplay* pDisplayer);
	/// \brief 获取Display
	GsDisplay* Display();
	/// \brief 获取自定义参数
	Utility::GsStlMap<Utility::GsString, Utility::GsStlMap<Utility::GsString, Utility::GsAny> >& Param();
	void Param(Utility::GsString& type,Utility::GsString& key, Utility::GsAny& value);
	Utility::GsStlMap<Utility::GsString, Utility::GsAny>& TypeParam(Utility::GsString& type);
protected:
	GsFeaturePtr m_pFea;
	GsSymbolPtr m_pSymbol;
	GsMapPtr m_pMap;
	GsLayerPtr m_pLayer;
	GsDisplayPtr m_pDisplay;
	//此处可增加一些参数，如地图display里面的相关的参数，地图比例、画布范围、中心店、地图名称、空间参考等
	//geometry 相关参数，如内点、中心点、宽、高、节点、端点、闭合点、面积、长度等
	//layer 相关参数，
	//地图相关参数
	//全局设置相关参数，可自定义设置
	Utility::GsStlMap<Utility::GsString, Utility::GsStlMap<Utility::GsString, Utility::GsAny> > m_mapParams;

private:
};
GS_SMARTER_PTR(GsExpressionContext2);
//DECLARE_CLASS_CREATE(GsExpressionContext2)
enum ExpressionType 
{
	UnKonwn,
	LuaExpression,
	PythonExpression
};
class GS_API GsExpressionExecute :public Utility::GsRefObject
{
public:
	GsExpressionExecute()
	{}
	~GsExpressionExecute()
	{}
	/// \brief 表达式类型
	virtual ExpressionType Type();
	//virtual Utility::GsAny evaluate(GsExpressionContext2* pExpContext, Utility::GsString&  strExp)
	//{
	//	if (!pExpContext || strExp.empty())
	//		return Utility::GsAny();
	//	return onExecute(pExpContext,strExp);
	//}
	/// \brief 表达式计算
	/// \param pExpContext 表达式上下文
	/// \param strExpList 表达式字符创列表
	virtual Utility::GsString Evaluate(GsExpressionContext2* pExpContext, Utility::GsVector<Utility::GsString>&  strExpList);
	virtual Utility::GsString Evaluate();
	/// \brief 表达式计算
	/// \param pExpContext 结算接口变量名称
	/// \param pExpContext 结算接口变量类型
	/// \return 返回表达式计算的结果值指针
	virtual void* EvaluateValue(const Utility::GsString& strKey, const Utility::GsString& strtype );
protected:

	//virtual Utility::GsAny onExecute(GsExpressionContext2* pExpContext, Utility::GsString&  strExp)
	//{
	//	return Utility::GsAny();
	//}
	virtual Utility::GsString onExecute(GsExpressionContext2* pExpContext, Utility::GsVector<Utility::GsString>&  strExpList);
};
GS_SMARTER_PTR(GsExpressionExecute);
//DECLARE_CLASS_CREATE(GsExpressionExecute)


class GS_API GsExpressionScript :public Utility::GsRefObject
{
public:
	/// \brief 初始化
	/// \param 表达式字符串
	GsExpressionScript(const Utility::GsString&  strExp);
	/// \brief 初始化
	/// \param 表达式字符串列表
	GsExpressionScript(const Utility::GsVector<Utility::GsString>&  strExpList);
	~GsExpressionScript();
	/// \brief 设置表达式字符串列表
	/// \param 表达式字符串列表
	void ExpressionString(const Utility::GsVector<Utility::GsString>&  strExpList);
	/// \brief 获取表达式字符串列表
	/// \return 返回表达式字符串列表
	Utility::GsVector<Utility::GsString>&  ExpressionString();
	
	/// \brief 设置表达式字符串列表
	/// \param 表达式字符串列表
	void Execute(GsExpressionExecute* pExe);
	/// \brief 获取表达式执行对象指针
	/// \return 
	GsExpressionExecute* Execute();
	/// \brief 设置表达式上下文
	/// \param 表达式上下文
	void Prepare(GsExpressionContext2* pExpContext);
	/// \brief 获取表达式上下文
	/// \return 
	GsExpressionContext2* ExpressionContext();
	/// \brief 计算表达式值
	/// \return 返回结果字符串
	//此处gsany类型返回值，待确定，是个问题，lua没有返回具体类型
	Utility::GsString Evaluate();
	/// \brief 返回表达式值计算的值
	/// \param 全局对象名称
	/// \param 全局对象类型
	/// \return 返回结果对象指针
	virtual void* EvaluateValue(const Utility::GsString& strKey, const Utility::GsString& strtype);
	/// \brief 返回表达式值计算的默认全局变量relvalue值
	/// \param 全局对象类型
	/// \return 返回结果对象指针
	virtual void* EvaluateValue(const Utility::GsString& strtype);
protected:
	//Utility::GsString m_strExp;
	Utility::GsVector<Utility::GsString>  m_strExpList;
	//其他参数
	GsExpressionContext2Ptr m_pExpContext;
	GsExpressionExecutePtr m_pExecute;

};
GS_SMARTER_PTR(GsExpressionScript);

/// \brief  脚本字段动态绑定
class GS_API GsScriptParameterDynamicBinder :public GsParameterDynamicBinder
{
public:
	/// \brief 初始化
	/// \param const char* strExpression 表达式
	GsScriptParameterDynamicBinder(const char*strExpression);
	/// \brief 初始化
	/// \param const char* strExpression 表达式
	GsScriptParameterDynamicBinder(GsExpressionScript* pExpScript);
	/// \brief 设置脚本表达式
	/// \param  表达式
	void ExpressionScript(GsExpressionScript* pExpScript);
	/// \brief 获取表达式
	/// \return  返回表达式
	GsExpressionScript* ExpressionScript();
	/// \brief 通过 GsParameterDynamicBinder 继承
	virtual void Binding(GsFeature * pFea, GsSymbol * pSym);

	/// \brief 克隆
	virtual Utility::GsSmarterPtr<GsParameterDynamicBinder> Clone();
protected:
	GsExpressionScriptPtr m_pExpScript;
};
GS_SMARTER_PTR(GsScriptParameterDynamicBinder);
//一下为测试代码，用于测试全局函数、静态函数的调用，可将一些常用的函数进行归类封装
//便于脚本使用
class GS_API GeometryFunction:public Utility::GsRefObject
{
public:
	GeometryFunction();
	~GeometryFunction();
	GsBox Bound(GsGeometry* pGeo);
};
GS_SMARTER_PTR(GeometryFunction);

class GS_API GeometryFunctionStaticTest
{
public:
	static GsBox Bound(GsGeometry* pGeo);
};
GS_API GsBox GeometryFunctionTest(GsGeometry* pGeo);
KERNEL_ENDNS