#pragma once
#include "utility.h"
#include "tracker.h"

GLOBE_NS

enum GsPlotType
{
	ePlotNull,
	ePlotPoint,
	ePlotLine,
	ePlotSurface,
	ePlotModel,
};
enum GsPlotModeType
{
	eSphereModelType = 1,
	eCubeModelType = 2,
};
/// \brief 标绘对象
class GS_API GsPlotObject : public UTILITY_NAME::GsRefObject
{
protected:
	GsPlotType m_ePlotType;	// 类型
	int m_nID; // 唯一id值

	UTILITY_NAME::GsString m_strName;		// 名称

	GsRawPoint3D m_ptCamera;	// 相机位置
	GsRawPoint3D m_ptLookAt;	// 看向点位置
	GsRawPoint3D m_dir, m_up;
	double m_dPitchAngle;		// 俯仰角
	double m_dHeadingAngle;		// 方位角

	// 轨迹对象
	GsTrackerElementPtr m_ptrTrackEle;
	// 描述信息
	UTILITY_NAME::GsString m_strDesc;

	// 点文字符号
	GsTextSymbolPtr m_ptrTextSymbol;
	// 点标绘图标属性
	UTILITY_NAME::GsConfig m_PointCfg;

	// 模型大小
	int m_fModelSize;
	// 模型类型
	GsPlotModeType m_eModelType;
public:
	GsPlotObject(GsPlotType eType);
	GsPlotObject(GsTrackerElement* pEle, GsPlotType eType);
	~GsPlotObject();

	/// \brief 设置轨迹对象
	void Element(GsTrackerElement* pTracker) { m_ptrTrackEle = pTracker; }
	/// \brief 获取轨迹对象
	GsTrackerElement* Element() { return m_ptrTrackEle; }

	/// \biref 标绘类型
	GsPlotType PlotType() { return m_ePlotType; }

	/// \brief 标绘唯一ID
	void ID(int nid) { m_nID = nid; }
	int ID() { return m_nID; }

	/// \brief 名称
	void Name(const char* strUTF8Name);
	UTILITY_NAME::GsString Name() { return m_strName; }

	/// \brief 相机位置
	void CameraPosition(const GsRawPoint3D& ptGeo) { m_ptCamera = ptGeo; }
	GsRawPoint3D CameraPosition() { return m_ptCamera; }

	/// \brief 看向点位置
	void LookAtPosition(const GsRawPoint3D& pt) { m_ptLookAt = pt; }
	GsRawPoint3D LookAtPosition() { return m_ptLookAt; }

	void Direction(const GsRawPoint3D& dir) { m_dir = dir; }
	GsRawPoint3D Direction() { return m_dir; }

	void Up(const GsRawPoint3D& up) { m_up = up; }
	GsRawPoint3D Up() { return m_up; }

	/// \brief 俯仰角
	void Pitch(double dPitch) { m_dPitchAngle = dPitch; }
	double Pitch() { return m_dPitchAngle; }

	/// \brief 方位角
	void Heading(double dHeading) { m_dHeadingAngle = dHeading; }
	double Heading() { return m_dHeadingAngle; }

	/// \brief 描述信息
	void Description(const char* str) { 
		if (str == 0) m_strDesc.empty();
		else m_strDesc = str; 
	}
	UTILITY_NAME::GsString Description() { return m_strDesc; }

	/// \brief 通过xml字符串创建标绘对象
	static UTILITY_NAME::GsSmarterPtr<GsPlotObject> LoadFrom(const UTILITY_NAME::GsString& strXml);
	/// \brief 转化成xml字符串
	UTILITY_NAME::GsString ToXml();

public:
	/// \brief 点标绘文字符号
	void TextSymbol(GsTextSymbol* pSym);
	GsTextSymbol* TextSymbol() { return m_ptrTextSymbol; }
	/// \brief 获取点标绘图标路径
	UTILITY_NAME::GsString PointImagePath();
	/// \brief 点标绘图标属性
	UTILITY_NAME::GsConfig& PointImageProperty() { return m_PointCfg; }

public:
	/// \brief 模型类型
	void ModelType(GsPlotModeType eType) { m_eModelType = eType; }
	GsPlotModeType ModelType() { return m_eModelType; }

	/// \brief 模型大小
	void ModelSize(float fVal) { m_fModelSize = fVal; }
	float ModelSize() { return m_fModelSize; }

protected:
	/// \brief 刷新点标绘
	void RefreshPointPlot();
};
GS_SMARTER_PTR(GsPlotObject);

class GS_API GsPlotRenderManager : public UTILITY_NAME::GsRefObject
{
public:
	GsPlotRenderManager();
	virtual ~GsPlotRenderManager();

	/// \brief 标绘类型
	void PlotType(GsPlotType eType);
	GsPlotType PlotType();

	/// \brief 获取当前工具对象
	GsTracker* CurrentTracker() {
		return m_pTracker;
	}

	/// \brief 清除标绘结果
	virtual void ClearResult();
public:
	/// \brief 工具完成事件
	UTILITY_NAME::GsDelegate<void(GsPlotObject*)> CompleteEventHandler;

	/// \breif 添加标绘对象
	void AddPlotObject(GsPlotObject *pPlot);

	/// \brief 删除标绘对象
	void DeletePlotObject(GsPlotObject *pPlot);
protected:
	/// \brief 根据标绘类型获取轨迹工具
	GsTracker* GetTracker(GsPlotType eType);

	/// \brief 工具完成响应函数
	void OnComplete(GsTrackerElement *pEle, GsTracker *pTool, unsigned int nErrorCode);

	void OnClearPlotObject();
private:
	// 轨迹工具 
	GsTrackerPtr m_ptrModelTracker;
	// 轨迹类型
	GsPlotType m_eType;
	// 当前轨迹工具
	GsTracker* m_pTracker;

	// 标绘对象缓存
	UTILITY_NAME::GsStlMap<int, GsPlotObjectPtr> m_mapPlotObj;

	int m_nIndex;
	UTILITY_NAME::GsStlMap<GsPlotType, int> m_mapPlotCount;
};
GS_SMARTER_PTR(GsPlotRenderManager);

/// \brief 体标绘工具
class GsModelPlotTool : public UTILITY_NAME::GsRefObject
{
protected:
	GsModelPlotTool()
		:m_eModelType(eSphereModelType)
	{
		m_fModelSize = 10;
	}
public:
	/// \brief 标绘模型类型
	void ModelType(GsPlotModeType eType) { m_eModelType = eType; }
	GsPlotModeType ModelType() { return m_eModelType; }

	/// \brief 模型大小
	void ModelSize(float fVal) { m_fModelSize = fVal; }
	float ModelSize() { return m_fModelSize; }

protected:
	int m_fModelSize;
	GsPlotModeType m_eModelType;
};
GS_SMARTER_PTR(GsModelPlotTool);
GLOBE_ENDNS
