#pragma once
#include "../utility/preconfig.h" 
#include "geometry.h"
#include "geodatabase.h"

KERNEL_NS   

/// \brief 属性合并方法
enum GsJoinAttributeType
{
    /// \brief 合并所有属性
	eJoinAll,
	/// \brief 不合并OID
	eJoinNoOID,
	/// \brief 仅仅合并OID
	eJoinOnlyOID,
}; 
/// \brief 分析数据封装
class GS_API GsAnalysisData  :public GsFeatureBuffer
{ 
};

/// \brief 分析数据读写，通过继承此类以实现
class GS_API GsAnalysisDataIO:public GsFeatureDataIO
{
public:
	virtual ~GsAnalysisDataIO() {  }

	virtual void ResultFieleds(const GsFields& fields) {}

	virtual GsFeatureClass* FeatureClass() { return nullptr; }
};

/// \brief 封装GsAnalysisDataIO指针，便于控制生命周期
class GS_API GsAnalysisDataIOAgent:public Utility::GsRefObject
{
protected:
	GsAnalysisDataIO* m_Ptr;
	/// \brief 
	/// \param ptr 
	GsAnalysisDataIOAgent(GsAnalysisDataIO* ptr);
public:
	~GsAnalysisDataIOAgent();

	/// \brief 获取GsAnalysisDataIO指针
	/// \return 
	GsAnalysisDataIO* Ptr();

};
/// \brief GsAnalysisDataIOAgentPtr
GS_SMARTER_PTR(GsAnalysisDataIOAgent);


/// \brief 空间分析辅助类
class GS_API GsSpatialAnalysisUtility
{
public:
	/// \brief 从地物类创建空间分析数据IO
	/// \param pFeaClass 
	/// \param pQF 
	/// \return 
	static GsAnalysisDataIOAgentPtr CreateAnalysisDataReader(GsFeatureClass* pFeaClass,GsQueryFilter* pQF = NULL);
	/// \brief 
	/// \param pFeaClass 
	/// \return 
	static GsAnalysisDataIOAgentPtr CreateAnalysisDataWriter(GsFeatureClass* pFeaClass);
	/// \brief 
	/// \param pFeaClassIO 
	/// \return 
	static GsAnalysisDataIOAgentPtr CreateAnalysisDataIO(GsAnalysisDataIO * pFeaClassIO);
};


/// \brief 叠置分析结果输出类型
enum GsOverlapResultType
{
	/// \brief 数据输出结果为输入数据的最小维度
	eAsInput,
	/// \brief 输出结果为线
	eAsLine,
	/// \brief 输出结果为点
	eAsPoint,
};
/// \brief 大数据叠置分析
class GS_API GsOverlayAnalysis :public Utility::GsRefObject
{
	/// \brief 叠置分析容差
	double m_Tolerance;
	/// \brief 叠置分析容差相对于叠置分析的比率
	double m_InvalidToleranceScale;

	geostar::safe_ga m_ga;

	void BuildFields(GsAnalysisDataIO** vInputArray, int nInputCount, GsJoinAttributeType eJoinType, GsAnalysisDataIO* pOut);

public:
	/// \brief 大数据叠置分析
	/// \param tol 容差
	GsOverlayAnalysis(double tol);
	
	/// \brief 获取空间分析中最大内存使用，单位字节
	/// \return 字节数
	static long long MaxAnalysisMemorySize();

	/// \brief 设置空间分析中最大内存使用，单位字节
	/// \param max 字节数
	static void MaxAnalysisMemorySize(long long max);


	/// \brief 叠置分析容差相对于叠置分析的比率
	/// \return 比率
	double InvalidToleranceScale();
	/// \brief 叠置分析容差相对于叠置分析的比率
	/// \param scale 比率
	void InvalidToleranceScale(double scale);

	virtual ~GsOverlayAnalysis();
	
	/// \brief 合并N个地物类
	/// \param vInputArray 输入数据数组的首地址
	/// \param nInputCount 输入数据个数
	/// \param eJoinType 属性合并方法
	/// \param pOut 输出地物数据
	/// \return 返回是否分析成功
	bool Union(GsAnalysisDataIO**  vInputArray,int nInputCount,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut);
    /// \brief 合并2个地物类
	/// \param vInputA 输入的地物数据A
	/// \param vInputB 输入的地物数据B
	/// \param eJoinType 属性合并方法
	/// \param pOut 输出数据
	/// \return 返回是否分析成功
	bool Union(GsAnalysisDataIO* vInputA,GsAnalysisDataIO* vInputB,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut);
    
	/// \brief 擦除
	/// \param pInput 输入数据
	/// \param pErase 
	/// \param pOut 输出数据
	/// \param result 叠置分析结果输出类型
	/// \return 返回是否分析成功
	bool Erase(GsAnalysisDataIO* pInput,GsAnalysisDataIO* pErase,GsAnalysisDataIO* pOut, GsOverlapResultType result = eAsInput);
	/// \brief 相交
	/// \param vInputArray 输入数据数组的首地址
	/// \param nInputCount 输入数据个数
	/// \param eJoinType 属性合并方法
	/// \param pOut 输出数据
	/// \param result 叠置分析结果输出类型
	/// \return 返回是否分析成功
	bool Intersect(GsAnalysisDataIO**  vInputArray,int nInputCount,
		GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut , GsOverlapResultType result= eAsInput);
	/// \brief 相交
	/// \param vInputA 输入的地物数据A
	/// \param vInputB 输入的地物数据B
	/// \param eJoinType 属性合并方法
	/// \param pOut 输出数据
	/// \param result 叠置分析结果输出类型
	/// \return 返回是否分析成功
	bool Intersect(GsAnalysisDataIO* vInputA,GsAnalysisDataIO* vInputB,
		GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut, GsOverlapResultType result = eAsInput);
	
	/// \brief 标记
	/// \param pInput 输入数据
	/// \param pIdentity 
	/// \param eJoinType 属性合并方法
	/// \param pOut 输出数据
	/// \return 返回是否分析成功
	bool Identity(GsAnalysisDataIO* pInput,GsAnalysisDataIO* pIdentity,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut );
	
	/// \brief 更新
	/// \param pInput 输入数据
	/// \param pUpdate 
	/// \param pOut 输出数据
	/// \return 返回是否分析成功
	bool Update(GsAnalysisDataIO* pInput,GsAnalysisDataIO* pUpdate,GsAnalysisDataIO* pOut );

	/// \brief 对称差
	/// \param vInputA 输入的地物数据A
	/// \param vInputB 输入的地物数据B
	/// \param eJoinType 属性合并方法
	/// \param pOut 输出数据
	/// \return 返回是否分析成功
	bool SymmetricalDifference(GsAnalysisDataIO* vInputA,GsAnalysisDataIO* vInputB,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut );
};
/// \brief GsOverlayAnalysisPtr
GS_SMARTER_PTR(GsOverlayAnalysis);


/// \brief 缓冲区融合类型
enum GsBufferDissolveType
{
	/// \brief 每个地物均生成独立缓冲区，完全不融合
	eNoneDissolve,
	/// \brief 根据几何位置融合，几何上重叠的融合
	eDissolveByGeo,
	/// \brief 根据属性字段融合，将属性值相同的结果进行融合
	eDissolveByAttribute,

};
/// \brief 缓冲区类型
enum GsBufferType
{
	/// \brief 完全缓冲区
	/// \details 对于线输入要素，将在线两侧生成缓冲区
	/// 对于面输入要素，将在面周围生成缓冲区，并且这些缓冲区将包含并叠加输入要素的区域
	/// 对于点输入要素，将在点周围生成缓冲区
	eFullBuffer,
	/// \brief 外缓冲区
	/// \details 对于面输入要素，仅在输入面的外部生成缓冲区（输入面内部的区域将在输出缓冲区中被擦除）,此选项对于线输入要素无效
	eOutsideBuffer,
	/// \brief 內缓冲区
	/// \details 对于面输入要素，仅在输入面的内部生成缓冲区（输入面内部的区域与输出缓冲区求交）,此选项对于线输入要素无效
	eInsideBuffer,
};

/// \brief 缓冲区分析
class GS_API GsBufferAnalysis :public Utility::GsRefObject
{
	GsBufferCapType m_eCapType;
	GsBufferType	m_eBufferType;
	GsBufferDissolveType m_eDisType;
	int m_nDissolveField;
	double m_Tolerance;

public:
	/// \brief 
	/// \param tol 容差
	GsBufferAnalysis(double tol);
	~GsBufferAnalysis();
	/// \brief 线输入要素末端的缓冲区形状，缺省为内插圆
	/// \return 
	GsBufferCapType CapType();
	/// \brief 线输入要素末端的缓冲区形状，缺省为内插圆
	/// \param eType 
	void CapType(GsBufferCapType eType);
	
	/// \brief 缓冲区类型
	/// \return 
	GsBufferType BufferType();
	/// \brief 缓冲区类型
	/// \param eType 
	void BufferType(GsBufferType eType);

	/// \brief 执行哪种融合操作以移除输出缓冲区重叠,缺省为不融合
	/// \return 
	GsBufferDissolveType DissolveType();
	/// \brief 执行哪种融合操作以移除输出缓冲区重叠,缺省为不融合
	/// \param eType 
	void DissolveType(GsBufferDissolveType eType);
	/// \brief 融合字段的索引
	/// \return 
	int DissolveField();
	/// \brief 融合字段的索引
	/// \param nFieldIndex 
	void DissolveField(int nFieldIndex);

	/// \brief 生成缓冲区
	/// \param dblRadius 缓冲区的半径
	/// \param pInput 输入数据
	/// \param pOut 输出数据
	/// \return 
	bool Buffer(double dblRadius,GsAnalysisDataIO* pInput,GsAnalysisDataIO* pOut );

	/// \brief 根据属性值生成缓冲区
	/// \param nRadiusFieldIndex 获取缓冲区半径的字段索引
	/// \param pInput 输入数据
	/// \param pOut 输出数据
	/// \return 
	bool Buffer(int nRadiusFieldIndex,GsAnalysisDataIO* pInput,GsAnalysisDataIO* pOut );

	/// \brief 生成多重缓冲区
	/// \param vecRadius 输入半径的数组
	/// \param pInput 输入数据
	/// \param pOut 输出数据
	/// \return 
	bool Buffer(UTILITY_NAME::GsVector<double>& vecRadius,GsAnalysisDataIO* pInput,GsAnalysisDataIO* pOut );
};
/// \brief GsBufferAnalysisPtr
GS_SMARTER_PTR(GsBufferAnalysis);

/// \brief 提取分析
class GS_API GsExtractionAnalysis :public Utility::GsRefObject
{
private:
	GeoStar::Utility::GsConfig m_Config;
public:
	GsExtractionAnalysis();
	/// \brief 根据配置文件构造提取分析对象
	/// \param cfg 输入配置的根节点
	/// \param EnableOutOfRange 设置是否保留范围外的点
	/// \param DefaultValue 设置默认值
	GsExtractionAnalysis(const GeoStar::Utility::GsConfig& cfg);
	/// \brief 提取值至点
	/// \param pRaster 
	/// \param pInput 输入数据
	/// \param pOut 输出数据
	/// \return 
	bool ExtractValuesToPoints(GsRasterClass* pRaster, GsAnalysisDataIO* pInput, GsAnalysisDataIO* pOut);
};
/// \brief GsExtractionAnalysisPtr
GS_SMARTER_PTR(GsExtractionAnalysis);




/// \brief 拓扑规则类型
enum GsTopologyRuleType
{
	/// \brief 点必须被其他要素的边界覆盖
	/// \brief 输入:topo\点拓扑检查\必须被其他要素的边界覆盖\点要素.fcs
	/// \brief 输入:topo\点拓扑检查\必须被其他要素的边界覆盖\面要素.fcs
	/// \image html eTRT_PointCoveredByAreaBoundary.png "eTRT_PointCoveredByAreaBoundary"
	/// \brief 输出:验证失败，存在3个未被边界覆盖的点要素
	eTRT_PointCoveredByAreaBoundary = 0x1001,
	/// \brief 点必须被其他要素的端点覆盖
	/// \brief 输入:topo\点拓扑检查\点必须被其他要素的端点覆盖\点要素.fcs
	/// \brief 输入:topo\点拓扑检查\点必须被其他要素的端点覆盖\线要素.fcs
	/// \image html eTRT_PointCoveredByLineEndpoint.png "eTRT_PointCoveredByLineEndpoint"
	/// \brief 输出:验证失败，存在3个未被线端点覆盖的点要素
	eTRT_PointCoveredByLineEndpoint = 0x1002,
	/// \brief 点必须被线覆盖
	/// \brief 输入:topo\点拓扑检查\点必须被线覆盖\点要素.fcs
	/// \brief 输入:topo\点拓扑检查\点必须被线覆盖\线要素.fcs
	/// \image html eTRT_PointCoveredByLine.png "eTRT_PointCoveredByLine"
	/// \brief 输出:验证失败，存在1个未被线覆盖的点要素
	eTRT_PointCoveredByLine = 0x1003,
	/// \brief 点必须完全位于面内部
	/// \brief 输入:topo\点拓扑检查\点必须完全位于面内部\点要素.fcs
	/// \brief 输入:topo\点拓扑检查\点必须完全位于面内部\面要素.fcs
	/// \image html eTRT_PointProperlyInsideArea.png "eTRT_PointProperlyInsideArea"
	/// \brief 输出:验证失败，存在3个不位于面内部的点要素
	eTRT_PointProperlyInsideArea = 0x1004,
	/// \brief 点必须被其他要素类覆盖
	/// \brief 输入:topo\点拓扑检查\点必须被其他要素类覆盖\点要素1.fcs
	/// \brief 输入:topo\点拓扑检查\点必须被其他要素类覆盖\点要素2.fcs
	/// \image html eTRT_PointCoveredByPoint.png "eTRT_PointCoveredByPoint"
	/// \brief 输出:验证失败，存在3个未被线覆盖的点要素
	eTRT_PointCoveredByPoint = 0x1005,
	/// \brief 点必须不能相交
	/// \brief 输入:topo\点拓扑检查\点必须不能相交.fcs
	/// \image html eTRT_PointNoCovered.png "eTRT_PointNoCovered"
	/// \brief 输出:验证失败，存在1个相交的点要素
	eTRT_PointNoCovered = 0x1006,
	/// \brief 点不与其他要素点重合
	/// \brief 输入:topo\点拓扑检查\点不与其他要素点重合\点要素1.fcs
	/// \brief 输入:topo\点拓扑检查\点不与其他要素点重合\点要素2.fcs
	/// \image html eTRT_PointNoCoveredByPoint.png "eTRT_PointNoCoveredByPoint"
	/// \brief 输出:验证失败，存在7个重合的点要素
	eTRT_PointNoCoveredByPoint = 0x1007,



	/// \brief 线不能重叠,单个图层或IO各要素之间不覆盖
	/// \brief 输入:topo\线拓扑检查\线重叠.fcs
	/// \image html eTRT_LineNoOverlap.png "eTRT_LineNoOverlap"
	/// \brief 输出:验证失败，存在1处重叠的线要素
	eTRT_LineNoOverlap = 0x2001,
	/// \brief 线不能相交,单个图层或IO各要素之间不相交
	/// \brief 输入:topo\线拓扑检查\多线相交.fcs
	/// \image html eTRT_LineNoIntersection.png "eTRT_LineNoIntersection"
	/// \brief 输出:验证失败，存在1处重叠，1处相交
	eTRT_LineNoIntersection = 0x2002,
	/// \brief 线必须被其他要素类的要素覆盖,
	/// \brief 输入:topo\线拓扑检查\线必须被其他要素覆盖\线被线覆盖1.fcs
	/// \brief 输入:topo\线拓扑检查\线必须被其他要素覆盖\线被线覆盖2.fcs
	/// \image html eTRT_LineCoveredByLineClass.png "eTRT_LineCoveredByLineClass"
	/// \brief 输出:验证失败，存在2处未被覆盖的线要素
	eTRT_LineCoveredByLineClass = 0x2003,
	/// \brief 线不能与其他要素重叠
	/// \brief 输入:topo\线拓扑检查\线与其他要素重叠\线要素1.fcs
	/// \brief 输入:topo\线拓扑检查\线与其他要素重叠\线要素2.fcs
	/// \image html eTRT_LineNoOverlapLine.png "eTRT_LineNoOverlapLine"
	/// \brief 输出:验证失败，存在1处重叠的线要素
	eTRT_LineNoOverlapLine = 0x2004,
	/// \brief 线必须被其他要素的边界覆盖
	/// \brief 输入:topo\线拓扑检查\线必须被其他要素覆盖\线被面覆盖线.fcs
	/// \brief 输入:topo\线拓扑检查\线必须被其他要素覆盖\线被面覆盖面.fcs
	/// \image html eTRT_LineCoveredByAreaBoundary.png "eTRT_LineCoveredByAreaBoundary"
	/// \brief 输出:验证失败，存在1处未被边界覆盖的线要素
	eTRT_LineCoveredByAreaBoundary = 0x2005,
	/// \brief 线不能有悬挂点,单个图层或IO
	/// \brief 输入:topo\线拓扑检查\线有悬挂点.fcs
	/// \image html eTRT_LineNoDangles.png "eTRT_LineNoDangles"
	/// \brief 输出:验证失败，存在3个悬挂点
	eTRT_LineNoDangles = 0x2006,
	/// \brief 线不能有伪节点,单个图层或IO
	/// \brief 输入:topo\线拓扑检查\线有伪结点.fcs
	/// \image html eTRT_LineNoPseudos.png "eTRT_LineNoPseudos"
	/// \brief 输出:验证失败，存在1处伪结点
	eTRT_LineNoPseudos = 0x2007,
	/// \brief 线不能自重叠,单个图层或IO
	/// \brief 输入:topo\线拓扑检查\线自重叠.fcs
	/// \image html eTRT_LineNoSelfOverlap.png "eTRT_LineNoSelfOverlap"
	/// \brief 输出:验证失败，存在1处自重叠的线段
	eTRT_LineNoSelfOverlap = 0x2008,
	/// \brief 线不能自相交,单个图层或IO
	/// \brief 输入:topo\线拓扑检查\线自相交.fcs
	/// \image html eTRT_LineNoSelfIntersect.png "eTRT_LineNoSelfIntersect"
	/// \brief 输出:验证失败，存在1处交点
	eTRT_LineNoSelfIntersect = 0x2009,
	/// \brief 线必须为单一部分,单个图层或IO
	/// \brief 输入:topo\线拓扑检查\单一部分检测.fcs
	/// \image html eTRT_LineNoMultipart.png "eTRT_LineNoMultipart"
	/// \brief 输出:验证成功
	eTRT_LineNoMultipart = 0x2010,
	/// \brief 线不能相交或者内部相连,单个图层或者IO比较
	/// \brief 输入:topo\线拓扑检查\线是否相交或内部相连.fcs
	/// \image html eTRT_LineNoIntersectOrInteriorTouch.png "eTRT_LineNoIntersectOrInteriorTouch"
	/// \brief 输出:验证失败，存在1处重叠，1处相交
	eTRT_LineNoIntersectOrInteriorTouch = 0x2011,
	/// \brief 线端点必须被其他要素覆盖
	/// \brief 输入:topo\线拓扑检查\端点必须被其他要素覆盖\线的端点必须被点要素覆盖之线要素.fcs
	/// \brief 输入:topo\线拓扑检查\端点必须被其他要素覆盖\线的端点必须被点要素覆盖之点要素.fcs
	/// \image html eTRT_LineEndpointCoveredByPoint.png "eTRT_LineEndpointCoveredByPoint"
	/// \brief 输出:验证失败，存在3处未被覆盖的端点
	eTRT_LineEndpointCoveredByPoint = 0x2012,
	/// \brief 线线相交交点处必须存在节点
	/// \brief 输入:topo\线拓扑检查\线线相交处必须存在节点.fcs
	/// \image html eTRT_PointMustOnLineLineIntersection.png "eTRT_PointMustOnLineLineIntersection"
	/// \brief 输出:验证失败，存在3个不位于端点的交点
	eTRT_PointMustOnLineLineIntersection = 0x2013,	
	/// \brief 线必须完全位于面内部
	/// \brief 输入:topo\点拓扑检查\线必须位于内部\线必须位于内部之线.fcs
	/// \brief 输入:topo\点拓扑检查\线必须位于内部\线必须位于内部之面.fcs
	/// \image html eTRT_LineProperlyInsideArea.png "eTRT_LineProperlyInsideArea"
	/// \brief 输出:验证失败，存在1个不位于内部的线
	eTRT_LineProperlyInsideArea = 0x2014,
	/// \brief 线不能与其他要素线相交
	/// \brief 输入:topo\点拓扑检查\线与其他要素类相交检查\线与其他要素相交1.fcs
	/// \brief 输入:topo\点拓扑检查\线与其他要素类相交检查\线与其他要素相交2.fcs
	/// \image html eTRT_LineNoSelfIntersectLine.png "eTRT_LineNoSelfIntersectLine"
	/// \brief 输出:验证失败，存在3个相交点，2条重叠线
	eTRT_LineNoIntersectLine = 0x2015,
	/// \brief 线节点距离必须大于聚合阀值
	/// \brief 输入:topo\线拓扑检查\线节点距离必须大于聚合阀值\线节点距离必须大于聚合阀值.fcs
	/// \image html eTRT_LineAggregateThreshold.png "eTRT_LineAggregateThreshold"
	/// \brief 输出:验证失败，存在2个不符合条件的点
	eTRT_LineAggregateThreshold = 0x2016,

	/// \brief 线不能相交或者内部相连,两个图层或者IO比较
	//eTRT_LineNoIntersectOrInteriorTouchWith = 0x2014,

	/// \brief 面不能有空隙
	/// \brief 输入:topo\面拓扑检查\面不能有空隙.fcs
	/// \image html eTRT_AreaNoGaps.png "eTRT_AreaNoGaps"
	/// \brief 输出:验证失败，存在1处空隙
	eTRT_AreaNoGaps = 0x3001,
	/// \brief 面不能重叠
	/// \brief 输入:topo\面拓扑检查\面不能重叠.fcs
	/// \image html eTRT_AreaNoOverlap.png "eTRT_AreaNoOverlap"
	/// \brief 输出:验证失败，存在1处重叠
	eTRT_AreaNoOverlap = 0x3002,
	/// \brief 面不与其他要素重叠
	/// \brief 输入:topo\面拓扑检查\面不能与其他要素重叠\面要素1.fcs
	/// \brief 输入:topo\面拓扑检查\面不能与其他要素重叠\面要素2.fcs
	/// \image html eTRT_AreaNoOverlapArea.png "eTRT_AreaNoOverlapArea"
	/// \brief 输出:验证失败，存在1处重叠
	eTRT_AreaNoOverlapArea = 0x3003,
	/// \brief 面必须被其他要素类的要素覆盖
	/// \brief 输入:topo\面拓扑检查\面必须被其他要素的要素覆盖\面要素1.fcs
	/// \brief 输入:topo\面拓扑检查\面必须被其他要素的要素覆盖\面要素2.fcs
	/// \image html eTRT_AreaCoveredByAreaClass.png "eTRT_AreaCoveredByAreaClass"
	/// \brief 输出:验证失败，存在1处未被覆盖的面
	eTRT_AreaCoveredByAreaClass = 0x3004,
	/// \brief 面必须互相覆盖
	/// \brief 输入:topo\面拓扑检查\必须相互覆盖\面要素1.fcs
	/// \brief 输入:topo\面拓扑检查\必须相互覆盖\面要素2.fcs
	/// \image html eTRT_AreaCoverEachOther.png "eTRT_AreaCoverEachOther"
	/// \brief 输出:验证失败，存在2处未被覆盖的面
	eTRT_AreaCoverEachOther = 0x3005,
	/// \brief 面必须被其他要素覆盖
	/// \brief 输入:topo\面拓扑检查\面必须被其他要素覆盖\面必须被面覆盖1.fcs
	/// \brief 输入:topo\面拓扑检查\面必须被其他要素覆盖\面必须被面覆盖2.fcs
	/// \image html eTRT_AreaCoveredByArea.png "eTRT_AreaCoveredByArea"
	/// \brief 输出:验证失败，存在2处未被覆盖的面
	eTRT_AreaCoveredByArea = 0x3006,
	/// \brief 面边界必须被其他要素覆盖
	/// \brief 输入:topo\面拓扑检查\面边界必须被其他要素覆盖\面边界必须被覆盖.fcs
	/// \brief 输入:topo\面拓扑检查\面边界必须被其他要素覆盖\面边界必须被覆盖之线要素.fcs
	/// \image html eTRT_AreaBoundaryCoveredByLine.png "eTRT_AreaBoundaryCoveredByLine"
	/// \brief 输出:验证失败，存在2处未被覆盖的边界线
	eTRT_AreaBoundaryCoveredByLine = 0x3007,
	/// \brief 面边界必须被其他要素边界覆盖
	/// \brief 输入:topo\面拓扑检查\面边界必须被其他要素边界覆盖\面要素1.fcs
	/// \brief 输入:topo\面拓扑检查\面边界必须被其他要素边界覆盖\面要素2.fcs
	/// \image html eTRT_AreaBoundaryCoveredByAreaBoundary.png "eTRT_AreaBoundaryCoveredByAreaBoundary"
	/// \brief 输出:验证失败，存在2处未被覆盖的边界线
	eTRT_AreaBoundaryCoveredByAreaBoundary = 0x3008,
	/// \brief 面包含点
	/// \brief 输入:topo\面拓扑检查\面包含点之面要素.fcs
	/// \brief 输入:topo\面拓扑检查\面包含点值点要素.fcs
	/// \image html eTRT_AreaContainPoint.png "eTRT_AreaContainPoint"
	/// \brief 输出:验证失败，存在1个未包含点的面
	eTRT_AreaContainPoint = 0x3009,
	/// \brief 面只能包含一个点
	/// \brief 输入:topo\面拓扑检查\面只能包含一个点\面包含一个点之面要素.fcs
	/// \brief 输入:topo\面拓扑检查\面只能包含一个点\面包含一个点之点要素.fcs
	/// \image html eTRT_AreaContainOnlyOnePoint.png "eTRT_AreaContainOnlyOnePoint"
	/// \brief 输出:验证失败，存在2个不符合条件的面
	eTRT_AreaContainOnlyOnePoint = 0x3010,
	/// \brief 面节点距离必须大于聚合阀值
	/// \brief 输入:topo\面拓扑检查\面节点距离必须大于聚合阀值\面要素1.fcs
	/// \image html eTRT_AreaAggregateThreshold.png "eTRT_AreaAggregateThreshold"
	/// \brief 输出:验证失败，存在3个不符合条件的点
	eTRT_AreaAggregateThreshold = 0x3011,	

};

/// \brief 拓扑规则验证的结果
enum GsTopologyRuleValidateResult
{
	/// \brief 未实现，不支持
	eValidateNoImplemention = -2,

	/// \brief 验证失败
	eValidateFaild =-1,

	/// \brief 验证成功
	eValidateSucceed = 0,

	/// \brief 用户取消
	eValidateUserCanced = 1,
};

/// \brief 几何类型校验器
/// \details 校验传入的几何类型是否满足此类型要求
struct GS_API  GsGeometryTypeValidator
{
	/// \brief 开始索引
	int StartOrder;
	/// \brief 结束索引
	int EndOrder;

	/// \brief 几何类型
	GsGeometryType Type;

	GsGeometryTypeValidator();
	/// \brief 
	/// \param startOrder 
	GsGeometryTypeValidator(int startOrder);
	/// \brief 
	/// \param startOrder 
	/// \param nEndOrder 
	GsGeometryTypeValidator(int startOrder, int nEndOrder);
	/// \brief 
	/// \param startOrder 
	/// \param eType 
	GsGeometryTypeValidator(int startOrder, GsGeometryType eType);
	/// \brief 
	/// \param startOrder 
	/// \param nEndOrder 
	/// \param eType 
	GsGeometryTypeValidator(int startOrder, int nEndOrder,GsGeometryType eType);
	/// \brief 
	/// \param rhs 
	GsGeometryTypeValidator(const GsGeometryTypeValidator& rhs);
	/// \brief 执行校验
	/// \param order 
	/// \param eType 
	/// \return 
	bool Validate(int order, GsGeometryType eType);
};
/// \brief 拓扑规则验证器
class GS_API GsTopologyRuleValidator:public Utility::GsRefObject
{
protected:
	/// \brief 发送进度
	/// \param reason 
	/// \param step 
	/// \param totalstep 
	/// \param progress 
	/// \return 
	bool FireOnValidateProgress(const char* reason, int step, int totalstep, float progress);
	/// \brief 
	/// \param eRule 
	/// \param config 
	GsTopologyRuleValidator(GsTopologyRuleType eRule,const Utility::GsConfig& config);

protected:
	Utility::GsString   m_LastError;
	GsTopologyRuleType  m_eRuleType;
	double				m_Tolerance;
	Utility::GsConfig   m_Config;

	/// \brief 校验添加进入用于拓扑检查的地物类的几何类型是否符合特定的顺序
	Utility::GsVector<GsGeometryTypeValidator> m_TypeValidator;
	
	/// \brief 输入数据
	Utility::GsVector<GsAnalysisDataIO* > m_InputData;

	GsAnalysisDataIO* m_OutputData;
public:
	virtual ~GsTopologyRuleValidator();

	/// \brief 添加一个用于拓扑检查的要素类数据，要素类型需要符合DataType返回的类型
	/// \param data 
	/// \return 
	bool AddData(GsAnalysisDataIO* data);


	/// \brief 设置用于拓扑检查的输出IO
	/// \param data 
	/// \return 
	bool OutputData(GsAnalysisDataIO* data);
	/// \brief 获取可以添加的第N个要素类的类型
	/// \details 要素类的类型会返回eGeometryTypePoint,eGeometryTypePolyline,eGeometryTypePolygon,eGeometryTypeUnknown
	/// \details 四种类型，分别代表点、线、面和任意类型
	/// \param n 
	/// \return 
	GsGeometryType DataType(int n);

	/// \brief 获取最多需要多少要要素类
	/// \return 
	int MaxDataCount();

	/// \brief 获取最少少需要多少要素类
	/// \return 
	int MinDataCount();


	/// \brief 通用配置
	/// \return 
	Utility::GsConfig&   Config();
	/// \brief 通用配置
	/// \param config 
	void Config(const Utility::GsConfig& config);

	/// \brief 拓扑规则的类型
	/// \return 
	GsTopologyRuleType RuleType();

	/// \brief 最近一次错误描述
	/// \return 
	const char*  LastError();

	/// \brief 容差
	/// \return 
	double Tolerance();

	/// \brief 容差
	/// \param tol 容差
	void Tolerance(double tol);

	/// \brief 验证拓扑规则
	/// \return 
	virtual GsTopologyRuleValidateResult ValidateRule() = 0;
public:

	/// \brief 验证拓扑规则时的进度
	/// \details 参数意义
	/// \details 参数1 GsTopologyRuleValidator对象指针
	/// \details 参数2 执行步骤的名称
	/// \details 参数3 执行步骤
	/// \details 参数4 总的步骤数量
	/// \details 参数5 单个步骤的进度，范围[0~1]
	/// \details 返回值  返回true，会继续执行验证，返回false会中断执行
	Utility::GsDelegate<bool(GsTopologyRuleValidator*,const char*,int,int,float)> OnValidateProgress;
};
/// \brief GsTopologyRuleValidatorPtr
GS_SMARTER_PTR(GsTopologyRuleValidator);

/// \brief 拓扑检查预处理，将一批地物类预处理
class GS_API GsTopologyCheckPreprocesser :public Utility::GsRefObject
{ 
protected:
	double m_dblTol;
	/// \brief 
	/// \param tol 容差
	GsTopologyCheckPreprocesser(double tol);
	/// \brief 
	/// \param progress 
	/// \return 
	bool FireOnProgress(double progress);
public:
	virtual ~GsTopologyCheckPreprocesser();
	
	/// \brief 添加用于检查的地物类
	/// \param fea 
	virtual void Add(GsFeatureClass* fea) = 0;

	/// \brief 添加用于检查的数据
	/// \param io 
	virtual void Add(GsAnalysisDataIO* io) = 0;

	/// \brief 执行预处理
	/// \return 
	virtual bool Preprocess() = 0;

	/// \brief 预处理结果数量
	/// \return 
	virtual int ResultCount()  = 0;

	/// \brief 预处理结果
	/// \param n 
	/// \return 
	virtual GsAnalysisDataIOAgentPtr Result(int n) = 0;

	/// \brief 预处理结果清除, 如果拓扑检查没完成,请不要清除
	/// \return 
	virtual bool Clear() = 0;
public:
	/// \brief 处理进度
	/// \details 参数意义
	/// \details 参数1 执行进度，范围[0~1]
	/// \details 返回值  返回true，会继续执行处理，返回false会中断执行
	Utility::GsDelegate<bool( float)> OnProgress;
};
/// \brief GsTopologyCheckPreprocesserPtr
GS_SMARTER_PTR(GsTopologyCheckPreprocesser);

/// \brief 拓扑检查分析
class GS_API GsTopologyCheckAnalysis :public Utility::GsRefObject
{ 
	Utility::GsConfig m_Config;
public:
	GsTopologyCheckAnalysis(); 
	/// \brief 
	/// \param cfg 
	GsTopologyCheckAnalysis(const Utility::GsConfig& cfg); 

	/// \brief 创建一种拓扑检查规则
	/// \param eRule 
	/// \param tol 容差
	/// \return 
	GsTopologyRuleValidatorPtr CreateTopologyRule(GsTopologyRuleType eRule,double tol);

	/// \brief 创建预处理对象
	/// \param tol 容差
	/// \return 
	GsTopologyCheckPreprocesserPtr CreatePreprocesser(double tol);
};
/// \brief GsTopologyCheckAnalysisPtr
GS_SMARTER_PTR(GsTopologyCheckAnalysis);

/// \brief 抽稀简化的方法
/// \brief 暂时只有线、面抽稀方式
enum GsGeneralityProcessType
{
	/// \brief
	eGPT_None,
	/// \brief 抽稀点简化
	eGPT_PointGenerality,
	/// \brief 抽稀线简化
	eGPT_LineGenerality,
	/// \brief 抽稀面简化
	eGPT_PolygonGenerality,
};

/// \brief 抽稀分析
class GS_API GsGeneralityProcess : public Utility::GsRefObject
{
protected:
	/// \brief 抽稀简化的方法
	GsGeneralityProcessType m_eProcessType;
	/// \brief
	double m_Tolerance;
	/// \brief 输入数据
	Utility::GsVector<GsAnalysisDataIO* > m_InputData;
	/// \brief 输出数据
	GsAnalysisDataIO* m_OutputData;

public:
	/// \brief 
	/// \param nType 
	/// \param tol 容差
	GsGeneralityProcess(GsGeneralityProcessType nType, double tol);
	~GsGeneralityProcess();

	/// \brief 添加一个用于抽稀分析的要素类数据IO，暂时只支持一个图层的数据处理
	/// \param data 
	/// \return 
	bool AddData(GsAnalysisDataIO* data);
	/// \brief 设置用于接收抽稀结果的输出IO
	/// \param data 
	/// \return 
	bool OutputData(GsAnalysisDataIO* data);
	/// \brief 设置偏差、容差
	/// \param dTolerance 
	void Tolerance(double dTolerance);
	/// \brief 得到偏差、容差
	/// \return 
	double Tolerance();
	/// \brief 抽稀处理
	/// \return 成功返回ture,失败返回false
	bool Preprocess();
};
/// \brief GsGeneralityProcessPtr
GS_SMARTER_PTR(GsGeneralityProcess);


/// \brief 加密的方法
/// \brief 暂时只有简单和等值两种加密方式
enum GsIncreaseProcessType
{
	/// \brief
	eIPT_None,
	/// \brief 简单加密，相连两点按给定步长加密，不足不加点
	eIPT_SimpleIncrease,
	/// \brief 等值加密,相邻点按距离等分
	eIPT_EqualIncrease,
	
};

/// \brief 加密分析
class GS_API GsIncreaseProcess : public Utility::GsRefObject
{
	/// 这里的加密分析是指增加图形点密度的意思
protected:	
	/// \brief 加密方式
	GsIncreaseProcessType m_eProcessType;
	/// \brief 偏差、容差
	double m_Tolerance;
	/// \brief 输入数据
	Utility::GsVector<GsAnalysisDataIO* > m_InputData;
	/// \brief 输出数据
	GsAnalysisDataIO* m_OutputData;
public:
	/// \brief 
	/// \param nType 
	/// \param tol 容差
	GsIncreaseProcess(GsIncreaseProcessType nType, double tol);
	~GsIncreaseProcess();

	/// \brief 添加一个用于加密分析的要素类数据IO，暂时只支持一个图层的数据处理
	/// \param data 
	/// \return 
	bool AddData(GsAnalysisDataIO* data);
	/// \brief 设置用于接收加密结果的输出IO
	/// \param data 
	/// \return 
	bool OutputData(GsAnalysisDataIO* data);
	/// \brief 设置偏差、容差
	/// \param dTolerance 
	void Tolerance(double dTolerance);
	/// \brief 得到偏差、容差
	/// \return 
	double Tolerance();
	/// \brief 加密处理
	/// \return 成功返回ture,失败返回false
	bool Preprocess();
};
/// \brief GsIncreaseProcessPtr
GS_SMARTER_PTR(GsIncreaseProcess);



KERNEL_ENDNS