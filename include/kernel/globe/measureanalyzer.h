#pragma once
#include "kernel.h"
#include "utility.h"
#include "tracker.h"


GLOBE_NS
/// \brief 量算方式
enum GsMeasureMode
{
	eMeasureNull = 0,
	//地表长度量算1
	eSurfaceLength,
	//空间长度量算2
	eSpaceLength,
	//地表面积量算3
	eSurfaceArea,
	//空间面积量算4
	eSpaceArea,
	//高度量算5
	eAltitude,
	//填挖方量算6
	eCutFillVolumn,
	//洪水淹没7
	eFlood,
	//剖面分析8
	eSectionAnalysis,
	//日照分析9
	eSunAnalysis,
	//单点可视10
	eOnePointAnalyse,
	//两点通视11
	eTwoPointAnalyse,
	//多点通视12
	eMultiPointAnalyse,
	//摄像头分析13
	eCameraAnalyse,
	//高程查询14
	eQueryAltitude,
	//坡度查询15
	eQuerySlope,
	//坡向分析16
	eSlopeAnalyse,
	// 雷达分析17
	eRadarAnalyse,
	//可视域分析18
	eViewShedAnalyse,
	// 天际线分析19
	eSkylineAnalysis,
	// 限高分析20
	eHeightLimitAnalysis
};


/// \brief 量算分析类
class GS_API GsMeasureAnalyzer : public UTILITY_NAME::GsRefObject
{
	//  测量方式
	GsMeasureMode m_eMode;
	// 符号队列
	UTILITY_NAME::GsVector<KERNEL_NAME::GsSymbolPtr> m_vtSymbolBox;
	
	// 测量工具缓存
	UTILITY_NAME::GsStlMap< GsMeasureMode, GsTrackerPtr > m_mapMeasureTool;

	GsTracker* m_pTracker;
public:
	GsMeasureAnalyzer(KERNEL_NAME::GsPyramid* pPym = 0);
	virtual ~GsMeasureAnalyzer();

	/// \brief 清除量算结果
	virtual void ClearResult();

	/// \brief 测量模式
	void MeasureMode(GsMeasureMode eMode);
	GsMeasureMode MeasureMode() { return m_eMode; }

	/// \brief 当前轨迹工具
	GsTracker* CurrentTracker() { return m_pTracker; }

private:
	/// \brief 获取符号
	KERNEL_NAME::GsSymbol* GetSymbol(GsMeasureMode eMode, bool bRefreshSymbol);

	// 获取测量工具
	GsTracker* GetTrackerTool(GsMeasureMode eMode);

	/// \brief 设置天际线参数
	void SetSkylineParam();

};
GS_SMARTER_PTR(GsMeasureAnalyzer);

/// \brief 两点通视分析工具
class GsTwoPointAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	/// \brief 两点通视分析结果事件
	UTILITY_NAME::GsDelegate<void(const KERNEL_NAME::GsRawPoint3D&, const KERNEL_NAME::GsRawPoint3D&, const KERNEL_NAME::GsRawPoint3D&)> TwoPointAnalyseEventHandler;
};
GS_SMARTER_PTR(GsTwoPointAnalysis);

/// \brief 洪水淹没分析工具
class GsFloodAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	/// \brief 洪水淹没分析结果事件（地形最小高程、地形最大高程,是否是地形高程范围）
	/// \breif 如果bool参数为false，double参数表示(洪水面积、洪水高度)
	UTILITY_NAME::GsDelegate<void(double, double, bool, bool bComplete)> FloodAnalyseEventHandler;

	/// \brief 开始操作
	/// \params dStepHeight 洪水每次增高高度
	virtual bool Start(double dStepHeight) = 0;

	// 停止
	virtual void Stop() = 0;

	// 设置淹没高度
	virtual void FloodElevation(double dH) = 0;
	// 获取淹没高度
	virtual double FloodElevation() = 0;
};

/// \brief 剖面分析工具
class GsSectionAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	/// \brief 剖面信息委托对象, 
	// 参数：1.折线中差分后的各线段的长度; 2.折线中差分后的各线段的末端点的高程;
	UTILITY_NAME::GsDelegate<void(std::vector<double>&, std::vector<double>&, std::vector<GsRawPoint3D>&)> SectionAnalysisEventHandler;
};
GS_SMARTER_PTR(GsSectionAnalysis);


/// \brief 填挖方分析工具
class GsCutFillAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	/// \brief 填挖方信息委托对象, 
	// 参数：1.填方; 2.挖方;2.最小高度;2.最大高度;2.填挖方基准高度;
	UTILITY_NAME::GsDelegate<void(double, double, double, double ,double)> OnCutFillEventFinish;
	virtual void CutFillByHeight(double dbHeight) = 0;
};
GS_SMARTER_PTR(GsCutFillAnalysis);

/// \brief 日照分析工具
class GsSunshineAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	// 获取日照累计结果
	virtual double GetSunshineAnalysisResult(int nStartHour, int nStartMinute, int nEndHour, int nEndMinute, int nFrequency, double dLength) = 0;
};
GS_SMARTER_PTR(GsSunshineAnalysis);

/// \brief 限高分析工具
class GsHeightLimitAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	// 显示包围盒
	virtual void ShowAnalysisResult(double dHeight) = 0;
};
GS_SMARTER_PTR(GsHeightLimitAnalysis);

GLOBE_ENDNS