#pragma once  
#include "utility.h"
#include <kernel.h>
#include "webgeodataset.h"
#include "measureanalyzer.h"
#include "plotrendermanager.h"
#include <vectorhelp.h>
GLOBE_NS 

/// \brief 场景中输入消息类型
enum GsMessageType
{
	/// \brief 无类型
	eNoneType = 0,
	/// \brief 鼠标按下
	eButtonDown = 1 << 0,
	/// \brief 鼠标弹起
	eButtonUp = 1 << 1,
	/// \brief 鼠标双击
	eDoubleClick = 1 << 2,
	/// \brief 鼠标拖动
	eDrag = 1 << 3,
	/// \brief 鼠标移动
	eMove = 1 << 4,
	/// \brief 按键按下
	eKeyDown = 1 << 5,
	/// \brief 按键弹起
	eKeyUp = 1 << 6,
	/// \brief 滚轮
	eButtonWheel
};

/// \brief 场景中鼠标状态
struct GsMouseState
{
	KERNEL_NAME::GsButton Button;
	GsMessageType Type;
};

enum GsEngineRenderQuality
{
	/// \brief 低
	eLOW,
	/// \brief 中
	eMEDIUM,
	/// \brief 高
	eHIGH
};

/// \brief 鼠标键盘消息接收者
class GS_API GsSceneMessageHandle :public Utility::GsRefObject
{
public:
	GsSceneMessageHandle() {}
	virtual ~GsSceneMessageHandle() {}

	/// \brief 处理鼠标消息
	virtual void HandleMouseMessage(const GsMouseState& MouseState, int x, int y, int delta = 0) = 0;
	/// \brief 处理键盘消息
	/// \param  type 1为按下 0为弹起
	virtual void HandleKeyboardMessage(KERNEL_NAME::GsKey key, int type) {}
	/// \brief 重置状态
	virtual void ResetState() {}

	virtual void OnFocus() {};
	virtual void OnFocusOut() {};
};
/// \brief GsSceneMessageHandlePtr
GS_SMARTER_PTR(GsSceneMessageHandle);

/// \brief 漫游器
class GS_API GsManipulator : public GsSceneMessageHandle
{
public:
	GsManipulator() {}
	virtual ~GsManipulator() {}

public:
	/// \brief 漫游
	/// \param  ptGeoGraphy 地理坐标,经纬度加高程
	virtual void Pan(const GsRawPoint3D& ptGeo) = 0;

	/// \brief 漫游
	/// \param ptGeoCamera 相机地理坐标
	/// \param heading 相机方位角
	/// \param pitch 相机俯仰角
	/// \param ptGeoLookat 相机看向点地理坐标
	virtual void Pan(const GsRawPoint3D& ptGeoCamera, double heading, double pitch, const GsRawPoint3D& ptGeoLookat) = 0;
	virtual void SetCamera(const GsRawPoint3D& ptGeoCamera, double heading, double pitch, const GsRawPoint3D& ptGeoLookat) = 0;
	virtual void SetCamera(const GsRawPoint3D& ptGeoCameraPosition , const GsRawPoint3D& ptGeoCameraDir, const GsRawPoint3D& ptGeoCameraUp) = 0;
	/// \brief 阻止手动漫游操作
	virtual void BlockManualPan(bool bBlock) = 0;

	/// \brief 阻止手动缩放操作
	virtual void BlockManualZoom(bool bBlock) = 0;

	/// \brief 阻止手动旋转操作
	virtual void BlockManualRotate(bool bBlock) = 0;
	
	/// \brief 相机飞行到指定瓦片
	virtual void FlyTo(const KERNEL_NAME::GsBox& box) = 0;

	/// \brief 相机飞行到指定空间点
	virtual void FlyTo(const KERNEL_NAME::GsRawPoint3D& point) = 0;

	/// \brief 相机飞行到指定空间点
	virtual void FlyTo(const KERNEL_NAME::GsRawPoint3D& point, double heading, double pitch) = 0;

	virtual void FlyTo(const KERNEL_NAME::GsRawPoint3D& point, const KERNEL_NAME::GsRawPoint3D& dir, const KERNEL_NAME::GsRawPoint3D& up) = 0;

	/// \brief 获得相机当前经纬度位置
	virtual KERNEL_NAME::GsRawPoint3D CameraPosition() = 0;

	/// \brief 获取相机看向点经纬度坐标
	virtual KERNEL_NAME::GsRawPoint3D LookAtPosition() = 0;

	/// \brief 获取相机方位角
	virtual double Heading() = 0;
	
	/// \brief 获取相机俯仰角
	virtual double Pitch() = 0;

	virtual void AddCustomFlyPoint() = 0;
	virtual void AddCustomFlyPoint(KERNEL_NAME::GsRawPoint3D ptPosition, KERNEL_NAME::GsRawPoint3D ptDirection, KERNEL_NAME::GsRawPoint3D ptUp, int nTime) = 0;

	virtual KERNEL_NAME::GsRawPoint3D CameraDirection() = 0;
	virtual KERNEL_NAME::GsRawPoint3D CameraUp() = 0;

	virtual void CustomFly() = 0;

	virtual void RotateFly(const KERNEL_NAME::GsRawPoint3D& point) = 0;
	virtual void StopRotateFly() = 0;
	virtual void ReadyRoamFly() = 0;
	virtual void StopFly() = 0;
	virtual void StopRoamFly() = 0;
	virtual void RoamFly() = 0;
	
	virtual void Update() = 0;
	virtual void ClearFly() = 0;

	virtual void PauseFly() = 0;
	virtual void ContinueFly() = 0;

	virtual void RotateFlyTime(float time) = 0;

	virtual void ObjectTransparent(double dValue) = 0;

	virtual void Serialize(const UTILITY_NAME::GsString& fileName = "") = 0;

	virtual void UnSerialize(const UTILITY_NAME::GsString& fileName = "") = 0;

	virtual void CloudVisibleDistance(double distance) = 0;

	virtual float CloudVisibleDistance() = 0;

	virtual void CloudModeEnable(bool bEnable) = 0;

	virtual double CloudHeight() = 0;

	virtual void CloudHeight(double distance) = 0;

	virtual bool Snapshot(const UTILITY_NAME::GsString& shotpic, int nW, int nH, const UTILITY_NAME::GsString& saveXmlfile) = 0;

	virtual void CameraPosBySnapshot(const UTILITY_NAME::GsString& xmlfile) = 0;

	virtual void SetLeftBtnDoubleClickCenterView(bool bVal) = 0;

	virtual void GlobalView() = 0;
	virtual void NorthView() = 0;
	virtual void OrthoView() = 0;
	virtual void LockOrthoView(bool bVal) = 0;
	virtual void LockView(bool bVal) = 0;
};
/// \brief GsManipulator
GS_SMARTER_PTR(GsManipulator);

/// \brief 场景对象拾取器
class GsSceneObjectPicker : public GsSceneMessageHandle
{
public:
	struct PropertyPair
	{
		UTILITY_NAME::GsAny Field;
		UTILITY_NAME::GsAny Value;
	};
public:
	virtual ~GsSceneObjectPicker() {}

	UTILITY_NAME::GsDelegate<void(const KERNEL_NAME::GsRawPoint3D, GsModelDataNodePtr)> PickResultEventHandler;
	
	/// \brief 开启和关闭拾取模型功能
	virtual void Enable(bool bEnable) = 0;

	/// \brief 模型拾取功能状态
	virtual bool Enable() = 0;

	//对于过滤器的添加与删除
	virtual bool AddFilter(Gs3DLayerPtr layer) = 0;

	virtual bool RemoveFilter(Gs3DLayerPtr layer) = 0;

	/// \brief 模型高亮后追加描述信息标签
	/// \param nScreenOffsideX 标签默认位置在屏幕坐标x方向上的偏移值
	/// \param nScreenOffsideY 标签默认位置在屏幕坐标y方向上的偏移值
	//virtual void AttachLabel(UTILITY_NAME::GsImagePtr ptrLabel, int nScreenOffsideX, int nScreenOffsideY) = 0;
	/// \brief外部给node和图片来贴图
	virtual void AttachLabel(UTILITY_NAME::GsImagePtr ptrLabel, GsModelDataNodePtr ptrModelNode) = 0;
	virtual void AttachLabel(UTILITY_NAME::GsImagePtr ptrLabel, GsModelDataNodePtr ptrModelNode, int nScreenOffsideX, int nScreenOffsideY) = 0;

	/// \brief 取消所有高亮
	virtual void CancelHighlight() = 0;
};
GS_SMARTER_PTR(GsSceneObjectPicker);

/// \brief 模型拾取器
class GsModelPicker : public GsSceneMessageHandle
{
public:
	/// \brief 高亮参数类型
	struct GsHighlightParam
	{
		GsHighlightParam()
		{
			strTopField = "";
			strBottomField = "";
			bLevelFilter = false;
		}
		KERNEL_NAME::GsFillSymbolPtr ptrFillSymbol;	// 高亮显示符号
		UTILITY_NAME::GsString strTopField;			// 顶高属性字段
		UTILITY_NAME::GsString strBottomField;		// 底高属性字段
		bool bLevelFilter;							// 是否需要高度过滤
	};

public:
	virtual ~GsModelPicker() {}

	UTILITY_NAME::GsDelegate<void(GsFeaturePtr)> PickResultEventHandler;

	/// \brief 开启和关闭拾取模型功能
	virtual void Enable(bool bEnable) = 0;

	/// \brief 模型拾取功能状态
	virtual bool Enable() = 0;

	/// \brief 增加矢量数据参数
	virtual void AddFeatureClassInfo(KERNEL_NAME::GsFeatureClass* pFeatureClass, GsHighlightParam& param) = 0;
	/// \brief 删除指定矢量数据参数
	virtual void RemoveFeatureInfo(KERNEL_NAME::GsFeatureClass* pFeatureClass) = 0;

	/// \brief 清除所有矢量参数
	virtual void ClearFeatureClassInfo() = 0;

	/// \brief 高亮单个矢量
	virtual void HitTest(KERNEL_NAME::GsFeature *pFeature) = 0;
	/// \brief 取消所有模型高亮
	virtual void CancelHighlight() = 0;

	/// \brief 模型高亮后追加描述信息标签
	virtual void AttachLabel(KERNEL_NAME::GsFeature *pFeature, UTILITY_NAME::GsImagePtr ptrLabel) = 0;

	/// \brief 模型高亮后追加描述信息标签
	/// \param nScreenOffsideX 标签默认位置在屏幕坐标x方向上的偏移值
	/// \param nScreenOffsideY 标签默认位置在屏幕坐标y方向上的偏移值
	virtual void AttachLabel(KERNEL_NAME::GsFeature *pFeature, UTILITY_NAME::GsImagePtr ptrLabel, int nScreenOffsideX, int nScreenOffsideY) = 0;
};
GS_SMARTER_PTR(GsModelPicker);

enum enumFeaturePickerType {
	ePointPicker,
	ePolygonPicker,
	ePropertyPicker,
	eCancelPicker
};
/// \brief 矢量拾取器
class GsFeaturePicker : public GsSceneMessageHandle
{
public:
	virtual ~GsFeaturePicker() {}

	UTILITY_NAME::GsDelegate<void(const std::map<KERNEL_NAME::GsFeatureClassPtr, std::vector<KERNEL_NAME::GsFeaturePtr> >&)> PickResultEventHandler;
	/// \brief 开启和关闭拾取模型功能
	virtual void Enable(bool bEnable) = 0;

	/// \brief 模型拾取功能状态
	virtual bool Enable() = 0;

	// \brief 设置拾取矢量类型功能
	virtual void Type(enumFeaturePickerType eType) = 0;
	// \brief 设置拾取矢量类型功能
	virtual enumFeaturePickerType Type() = 0;

	/// \brief 增加矢量数据参数
	virtual void AddFeatureClassInfo(KERNEL_NAME::GsFeatureClass* pFeatureClass) = 0;
	/// \brief 删除指定矢量数据参数
	virtual void RemoveFeatureInfo(KERNEL_NAME::GsFeatureClass* pFeatureClass) = 0;

	/// \brief 高亮单个矢量
	virtual void HitTest(KERNEL_NAME::GsFeature *pFeature) = 0;
	/// \brief 取消所有矢量高亮
	virtual void CancelHighlight() = 0;
};
GS_SMARTER_PTR(GsFeaturePicker);

class Gs3DLayer;
/// \brief 参数结构类型（key-value结构）
struct GsParameter
{
	GeoStar::Utility::GsString Key;
	GeoStar::Utility::GsString Value;
};

/// \brief 参数数组结构类型
/// \detail 抽象类不可实现
class GS_API GsParameters :public Utility::GsRefObject
{
public:
	virtual ~GsParameters();
	/// \brief 新增参数对象
	virtual void AddParameter(const GsParameter& para) = 0;

	/// \brief 获取参数个数
	virtual int ParameterCount() = 0;

	/// \brief 移除指定参数
	virtual void RemoveParameter(int i ) = 0;

	/// \brief 获取指定参数
	virtual GsParameter Parameter(int i) = 0;

	/// \brief 返回所有的参数值
	virtual char** Values() = 0;

	/// \brief 返回所有的参数名和参数值
	/// \detail 返回结构（参数名1，参数值1，参数名2，参数值2...）
	virtual char** KeyValues() = 0;
};
/// \brief GsParametersPtr
GS_SMARTER_PTR(GsParameters);

/// \brief 设备上下文
/// \detail 抽象类不可实现
class GS_API Gs3DDeviceContext :public Utility::GsRefObject
{
public:
	virtual ~Gs3DDeviceContext();

	/// \brief 创建上下文对象
	virtual int CreateContext() = 0;

	/// \breif 销毁上下文对象
	virtual int DestroyContext() = 0;

	/// \brief 调整窗口大小
	virtual int ResizeWindow() = 0;

	/// \brief 
	virtual int SwapWindow() = 0;

	/// \brief 
	virtual int BackstageRender() = 0;
};
/// \brief Gs3DDeviceContextPtr
GS_SMARTER_PTR(Gs3DDeviceContext);

/// \brief 引擎状态标记
enum GsEngineStatusFlag
{
	eObliqueWorkingStatus,
	eBaseWorkingStatus,
};

/// \brief 三维引擎类型
class GS_API Gs3DEngine :public Utility::GsRefObject
{
public:
	virtual ~Gs3DEngine(); 

	/// \brief 引擎渲染性能设置
	virtual void RenderQuality(GsEngineRenderQuality eQuality) {}

	/// \brief 引擎状态
	virtual void EngineStatus(GsEngineStatusFlag eFlag, int nValue);
	virtual int EngineStatus(GsEngineStatusFlag eFlag);
};
/// \brief Gs3DEnginePtr
GS_SMARTER_PTR(Gs3DEngine);

/// \brief 三维场景的类型
enum GsSceneType
{
	/// \brief 未初始化，未知场景
	eUnInitializeScene,
	/// \brief 球面场景
	eSphereScene,
	/// \brief 平面3D场景
	eStereoScene,
};

/// \brief 帧率限流阀，控制渲染暂停或者降低帧率
/// \details 节流阀通过时间、DirtyCount等手段判断渲染过程是否需要全帧率进行，在没有必要的情况下，限流阀将逐步降低帧率以节省系统资源。
/// \details 节流阀亦可以用于暂停挂起渲染过程，当渲染引擎处于后台无须进行渲染时可以通过限流阀暂停渲染过程
class GS_API GsFrameThrottle:public UTILITY_NAME::GsRefObject
{
protected:
	GsFrameThrottle();
public:
	virtual ~GsFrameThrottle();
	/// \brief 数据发生变化或需要渲染，调用此方法，可通知节流阀保持帧率
	virtual void Dirty() = 0;
	/// \brief 判断是否处有数据变化
	virtual bool IsDirty(bool bClearDirty = true) = 0;
	/// \brief 清除数据变化计数
	virtual void ClearDirty() = 0;
	/// \brief 判断是否是帧时间，由渲染引擎使用
	virtual bool IsFrameTime(bool bClearDirty = true) = 0;
	/// \brief 是否挂起，挂起将导致渲染引擎暂停渲染
	virtual bool IsSuspend() = 0;
	/// \brief 是否挂起，挂起将导致渲染引擎暂停渲染
	virtual void IsSuspend(bool b) = 0;
};
/// \brief GsFrameThrottlePtr
GS_SMARTER_PTR(GsFrameThrottle);

/// \brief 错误消息
enum GsSceneGraphErrorCode
{
	/// \brief 无错误
	eNoneError,
	/// \brief 检测硬件失败
	eDetectHardwareFaild,
};
/// \brief 三维错误信息
struct GS_API GsSceneGraphError
{
	/// \brief 错误编码
	GsSceneGraphErrorCode ErrorCode;
	
	/// \brief 错误描述
	UTILITY_NAME::GsString ErrorMessage;
	
	GsSceneGraphError();
	GsSceneGraphError(const GsSceneGraphError& o);

	/// \brief bool重载操作符，是否成功
	operator bool();

	/// \brief 字符串重载，获取错误消息
	operator const char* ();
};
/// \brief 场景中的屏幕控件的事件
class GS_API GsSceneScreenControlEvent
{
public:
	virtual ~GsSceneScreenControlEvent();
	
	/// \brief 按钮控件点击了按钮时发生
	virtual void OnClick();
};

/// \brief 场景中的屏幕控件
class GS_API GsSceneScreenControl:public UTILITY_NAME::GsRefObject
{
	
protected:
	GsSceneScreenControlEvent* m_pEvent; 
	GsSceneScreenControl();
public:
	
	virtual ~GsSceneScreenControl();
	
	/// \brief 绑定事件通知
	virtual void EventNotify(GsSceneScreenControlEvent* pEventHandle);

	/// \brief 事件通知
	virtual GsSceneScreenControlEvent*  EventNotify();

	// \brief 背景图片
	virtual void BackgroundImage(UTILITY_NAME::GsImage *pImage);

	// \brief 设置是否可见
	virtual void Visible(bool bVisible);
};
/// \brief GsSceneScreenControlPtr
GS_SMARTER_PTR(GsSceneScreenControl);


/// \brief 三维场景对象
/// \detail 抽象类不可实现
class GS_API GsSceneGraph : public UTILITY_NAME::GsRefObject
{
protected:
	Gs3DDeviceContextPtr m_ptrContext;
	Gs3DEnginePtr		m_ptrEngine;
	GsParametersPtr		m_ptrParameters;
	GsFrameThrottlePtr	m_ptrFrameThrottle;
	UTILITY_NAME::GsConfig m_SceneGraphConfig;

	UTILITY_NAME::GsVector<UTILITY_NAME::GsSmarterPtr<Gs3DLayer> > m_vecLayers;
	virtual bool OnInitialize(GsSceneType  eType = eSphereScene) = 0;
	virtual bool OnHardwareDetection() = 0;
	void ReportError(GsSceneGraphErrorCode error, const char* errorMsg);
	void ReportSucceed();

	GsMeasureAnalyzerPtr m_ptrMeasureAnalyzer;
	GsPlotRenderManagerPtr m_ptrPlotRender;
	GsModelPickerPtr m_ptrModelPicker;
	GsLayerContainerPtr m_ptrLayerContainer;
	GsSceneObjectPickerPtr m_ptrSceneObjectPicker;
	GsFeaturePickerPtr m_ptrFeaturePicker;

	GsSceneGraphError m_LastError;

public:
	GsSceneGraph();
	virtual ~GsSceneGraph();
	
	/// \brief 根据配置在场景中载入一个场景屏幕控件
	GsSceneScreenControlPtr LoadScreenControl(const UTILITY_NAME::GsConfig& config);
	/// \brief 在场景中创建一个场景屏幕控件
	GsSceneScreenControlPtr CreateScreenControl(const char *strName);

	/// \brief 最后的错误
	GsSceneGraphError LastError();

	/// \brief 帧率节流阀
	GsFrameThrottle* FrameThrottle();
	/// \brief 帧率节流阀
	void  FrameThrottle(GsFrameThrottle* f);


	/// \brief 获取场景类型
	GsSceneType SceneType();

	/// \brief 返回三维引擎实例
	Gs3DEngine * Engine();

	/// \brief 获取配置节点
	Utility::GsConfig&	Config();
	/// \brief 设置配置节点
	void Config(const Utility::GsConfig& config);

	/// \brief 获取参数信息
	GsParameters* Parameters();

	/// \brief 初始化场景
	/// \details 初始化场景只能调用一次，多次调用无效
	virtual bool Initialize(GsSceneType  eType = eSphereScene);
	
	/// \brief 执行渲染
	virtual void OnRender();


	/// \brief 关闭场景
	virtual void Close();

	/// \brief 返回窗体对象
	virtual void* WindowHandle() = 0;
	
	/// \brief 获取窗体的大小
	virtual UTILITY_NAME::GsSize WindowSize();

	/// \brief 调整窗体Size
	virtual void ResizeWindow(int w, int h);

	/// \brief 鼠标按下事件
	virtual void OnMouseDown(GsButton button, int x, int y);

	/// \brief 鼠标弹起事件
	virtual void OnMouseUp(GsButton button, int x, int y);

	/// \brief 鼠标双击事件
	virtual void OnMouseDoubleClick(GsButton button, int x, int y);

	/// \brief 鼠标滚轮滚动事件
	virtual void OnMouseWheel(int delta, int x, int y);

	/// \brief 鼠标移动事件
	virtual void OnMouseMove(int x,int y);

	/// \brief 按键按下事件
	virtual void OnKeyDown(GsKey key);

	/// \brief 按键弹起事件
	virtual void OnKeyUp(GsKey key);

	/// \breif 失去焦点事件
	virtual void OnFocusOut();

	/// \breif 插件获取焦点事件
	virtual void OnFocus();

	/// \breif 添加场景消息处理器
	virtual void AddSceneMessageHandle(GsSceneMessageHandle* ptrHandle);

	/// \breif 移除场景消息处理器
	virtual void RemoveSceneMessageHandle(GsSceneMessageHandle* ptrHandle);

	/// \brief 查找消息处理句柄
	virtual bool FindSceneMessageHandle(GsSceneMessageHandle* ptrHandle);

public:
	/// \brief 鼠标拾取，返回鼠标拾取点的地理坐标
	bool PickUp(int nX, int nY, KERNEL_NAME::GsRawPoint3D& ptGeography);

	/// \brief 根据经纬度获取地面的高程信息
	double GetAltitude(double x, double y);

	/// \brief 设置瓦片网格显示状态
	void ShowTileBound(bool bVisible);
	 
	/// \brief 获得漫游器对象
	GsManipulator * Manipulator();
	
	/// \brief 设置太阳位置
	void SunPosition(int hour, int minute);

	/// \brief 设置时间，主要用于白天夜晚对路灯光照的控制
	void TimeChanged(float dTime);
	
	/// \brief 切换相机
	void PlayerType(int type);
	int PlayerType();

	/// \brief 地表透明
	void GroundTransparent(float value);
	/// \brief 地表透明
	float GroundTransparent();

	/// \brief 开启特效
	bool OpenSceneEffect(const char* strType, const UTILITY_NAME::GsStlMap<UTILITY_NAME::GsString, UTILITY_NAME::GsString>& mapParams = UTILITY_NAME::GsStlMap<UTILITY_NAME::GsString, UTILITY_NAME::GsString>());

	bool CloseSceneEffect(const char* strType);

	///\brief 量算分析类
	GsMeasureAnalyzer* MeasureAnalyzer();

	/// \brief 标绘管理类
	GsPlotRenderManager* PlotRenderManager();

	/// \brief 图层管理类
	GsLayerContainer* LayerContainer();

	/// \brief 地形访问器
	GsTerrainAccessor* TerrainAccessor();

	/// \brief 模型拾取器
	GsModelPicker* ModelPicker();

	/// \brief 拾取器
	GsSceneObjectPicker* SceneObjectPicker();

	/// \brief 矢量拾取器
	GsFeaturePicker* FeaturePicker();

	// 场景渲染参数
public:
	// 设置全局光模式
	void GlobalLight(bool bGlobeLight);
	// 是否使用全局光
	bool GlobalLight();

	/// \brief 场景初始化完成回调对象
	UTILITY_NAME::GsDelegate<void(void)> OnSceneInitCompleted;

public:
	UTILITY_NAME::GsDelegate<void(const char*)> FuntionProcessEndCallBack;

}; 
/// \brief GsSceneGraphPtr
GS_SMARTER_PTR(GsSceneGraph);

/// \brief 三维场景类型
/// \detail 基于OpenGL实现的场景
class GS_API GsGLSceneGraph :public GsSceneGraph
{  
protected:

	virtual bool OnInitialize(GsSceneType  eType = eSphereScene);
	virtual bool OnHardwareDetection();
public:
	GsGLSceneGraph();
	virtual ~GsGLSceneGraph();
};
/// \brief GsGLSceneGraphPtr
GS_SMARTER_PTR(GsGLSceneGraph);

#ifdef _WIN32
/// \brief 三维场景类型
/// \detail Windows下基于DirectX11实现的场景
class GS_API GsD3D11SceneGraph :public GsSceneGraph
{
protected:

	virtual bool OnInitialize(GsSceneType  eType = eSphereScene);
	virtual bool OnHardwareDetection();
public:
	GsD3D11SceneGraph();
	virtual ~GsD3D11SceneGraph();

};
/// \brief GsD3D11SceneGraphPtr
GS_SMARTER_PTR(GsD3D11SceneGraph);
#endif


GLOBE_ENDNS