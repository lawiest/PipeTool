#include "../utility/image.h"
#include "geodatabase.h"
KERNEL_NS

/// \brief 滤波器类型
enum GS_API GsFilterType
{
	/// \brief 均值滤波
	eMeanFilter,
	/// \brief 中值滤波
	eMedianFilter,
	/// \brief 最大值滤波
	eMaxFilter,
	/// \brief 最小值滤波
	eMinFilter,
	/// \brief 双边滤波
	eBilateralFilter,
	/// \brief 引导滤波
	eGuidedFilter,
	/// \brief Sobel滤波
	eSobelFilter,

};

enum GS_API GsColorSelectionMode
{
	/// \brief 选择内插颜色
	eColorSelectionInterpolate,
	/// \brief 选择邻近颜色
	eColorSelectionNearestEntry,
	/// \brief 选择精确相等的颜色
	eColorSelectionExactEntry
};

/// \brief 山体阴影参数结构体
struct GS_API GsHillshadeData
{
	/// \brief 太阳高度角
	double AltRadians;
	/// \brief 太阳方位角
	double AzRadians;
	/// \brief 南北方向分辨率
	double Nsres;
	/// \brief 南北方向分辨率
	double Ewres;
	/// \brief 设置高程的缩放系数(夸大系数)
	double Factor;
	/// \brief 水平像素单位和高程单位的换算系数
	double Scale;
	/// \brief 标准差，对比度拉伸用，预留算法还没有实现 
	double dblStandardDeviation;
};

/// \ brief 栅格处理基类
class GS_API GsRasterProcess : public Utility::GsRefObject
{
public:
	/// \ brief 析构函数
	~GsRasterProcess();
	/// \ brief 栅格处理，将源栅格pSrcRaster经过处理得到新的栅格pDstRaster
	virtual bool Process(GsRaster* pSrcRaster, GsRaster* pDstRaster) = 0;
};

/// \brief  GsRasterProcessPtr
GS_SMARTER_PTR(GsRasterProcess);

/// \brief 一般的3*3窗口的栅格处理(八邻域分析)
class GS_API GsGeneric3x3Process :public GsRasterProcess
{
	/// \ brief 山体阴影参数结构体
	GsHillshadeData m_Data;
	/// \ brief 滤波类型
	GsFilterType m_Type;
	/// \ brief 是否求山体阴影
	bool m_IsHillShade;

public:
	/// \ brief 从滤波类型构造
	GsGeneric3x3Process(GsFilterType type);
	/// \ brief 从山体阴影参数结构体构造
	GsGeneric3x3Process(const GsHillshadeData& pData);

	/// \ brief 析构函数
	~GsGeneric3x3Process();

	/// \ brief 栅格处理函数，覆盖基类函数
	/// \ brief 将源栅格pSrcRaster经过处理得到新的栅格pDstRaster
	bool Process(GsRaster* pSrcRaster, GsRaster* pDstRaster);

protected:
	/// \ brief 处理栅格
	template<class T>
	bool OnProcess(GsRaster* pSrcRaster, GsRaster* pDstRaster);
};
/// \brief  GsGeneric3x3ProcessPtr
GS_SMARTER_PTR(GsGeneric3x3Process);

/// \brief DEM伪彩色处理
class GS_API GsDEMColorReliefProcess :public GsRasterProcess
{
protected:
	/// \brief 颜色选择模式
	GsColorSelectionMode m_Mode;
	/// \brief 颜色数组
	Utility::GsVector<Utility::GsColor> m_vecColor;
	
public:
	/// \brief 构造函数，还未实现,从色带和颜色Count构造
	GsDEMColorReliefProcess(Utility::GsGradsColor* c, int count,GsColorSelectionMode mode= eColorSelectionInterpolate);

	/// \brief 析构函数
	~GsDEMColorReliefProcess();

	/// \brief 设置颜色选择模式
	void ColorSelectionMode(GsColorSelectionMode mode);
	/// \brief 获取颜色选择模式
	GsColorSelectionMode ColorSelectionMode();

	/// \ brief 栅格处理函数，覆盖基类函数
	/// \ brief 将源栅格pSrcRaster经过处理得到新的栅格pDstRaster
	bool Process(GsRaster* pSrcRaster, GsRaster* pDstRaster);

protected:

	/// \brief 颜色值
	bool EnumColors(int i, const Utility::GsColor& c);
	/// \brief 栅格伪彩色处理
	template<class T1,class T2>
	bool OnProcess(GsRaster* pSrcRaster, GsRaster* pDstRaster);
};
/// \brief  GsDEMColorReliefProcessPtr
GS_SMARTER_PTR(GsDEMColorReliefProcess);

KERNEL_ENDNS