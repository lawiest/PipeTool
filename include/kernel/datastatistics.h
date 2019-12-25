#pragma once
#include "geodatabase.h"
using namespace GeoStar::Utility;
using namespace GeoStar::Utility::Data;
using namespace GeoStar::Kernel;

KERNEL_NS
/// \brief 统计结果数据结构
struct GS_API GsStatisticsResults
{
	/// \brief 值的总计
	long long Count;
	/// \brief 最小值
	double Minimum;
	/// \brief 最大值
	double Maximum;
	/// \brief 求和值
	double Sum;
	/// \brief 平均值
	double Mean;
	/// \brief 方和
	double QuadraticSum;
	/// \brief 标准差
	double StandardDeviation;
	/// \brief 极差  
	double Range;
	/// \brief 中程数 
	double MidRange;

	
	/// \brief 众数
	double	MaxModeNumber;
	/// \brief中位数
	double	Median;

	/// \brief 四分位数Q1
	double QuartileQ1;
	/// \brief 四分位数Q2
	double QuartileQ2;
	/// \brief 四分位数Q3
	double QuartileQ3;

};

enum  GsDataStatisticsType
{
	/// \brief 一般统计,最值,平均值,标准差, 统计时间复杂度位N,空间复杂度1
	eSimple,
	/// \brief 高级统计,众数,中位数,四分位数 统计时间复杂度位nlogN
	eAdvanced,
};

/// \brief 数据统计基本接口类
/// \details 此类只统计信息,排序能力可通过指定 各GsFeatureCursor,GsRowCursor的Where字句支持
/// \details 即 GsDataStatistics类对象接受GsFeatureCursor,GsRowCursor如果Cursor是排序遍历的,
/// \details 则统计将是按照排序实现的.
class GS_API GsDataStatistics : public Utility::GsRefObject
{
protected:
	GsDataStatisticsType m_Type;
	long long m_SampleRate;
	bool m_IsGroup;
	GsString m_strField;
	GsStatisticsResults m_Result;
protected:
	/// \brief 构造函数不可直接创建
	GsDataStatistics();


public:
	~GsDataStatistics();

	/// \brief 执行并返回当前统计结果
	/// \return 返回统计结果
	virtual GsStatisticsResults Statistics() = 0;

	/// \brief 设置统计字段名称
	/// \param const char* strField 地段字符串值
	/// \param strField 
	void Field(const char* strField);
	/// \brief 获取统计字段
	/// \return 返回统计字段值
	GsString Field();

	/// \brief 设置统计字段
	/// \param const char* strField 地段字符串值
	/// \param dsType 
	void DataStatisticsType(GsDataStatisticsType dsType);
	/// \brief 获取统计字段
	/// \return 返回统计字段值
	GsDataStatisticsType DataStatisticsType();

	/// \brief 获取需统计的条数, 
	/// \return 返回统计的条数
	long long SampleRate();

	/// \brief 设置统计的条数, 
	/// \param llSampleRate 条数
	void SampleRate(long long llSampleRate);

	/// \brief 获取是否分组
	/// \return 
	bool Group();

	/// \brief 设置是否记录分组,开启后可以获取数据的分组所有字段
	/// \param bGroup 
	void Group(bool bGroup);

	/// \brief 分组字段集合
	/// \return 
	virtual GsVector<GsAny>* UniqueValues();
	/// \brief 分组字段集合计数
	/// \param anyValue 
	/// \return 
	virtual int UniqueValuesCount(GsAny &anyValue);
	/// \brief 进度,实现此委托返回false 可中断
	/// \details 参数1 描述
	/// \details 参数2 已统计的数量
	/// \details 返回值  返回true，会继续执行,返回false会中断
	Utility::GsDelegate<bool(const char*, long long)> OnStatisticsProgress;
protected:
	GeoStar::Utility::GsVector<GsAny>	m_ValueGroup;
	GsStlMap<unsigned long long, int>    m_IndexMap;
	void* m_MaxMinHeap;
	/// \brief 
	/// \param type 
	/// \return 
	bool FieldIsVaild(Data::GsFieldType type);
	/// \brief 
	/// \param dblValue 
	void OnCalcOne(double dblValue);
	/// \brief 
	/// \param anyVale 
	void OnGroup(GsAny & anyVale);
	/// \brief 
	void ResultGenerator();
};
GS_SMARTER_PTR(GsDataStatistics);
/// \brief 地物类数据统计
/// \details 地物类数据统计实现类
class GS_API GsFeatureDataStatistics : public GsDataStatistics
{
	GsFeatureCursorPtr m_ptrCursor;
public:
	/// \brief 
	/// \param pFcs 
	/// \param pFilter 
	GsFeatureDataStatistics(GsFeatureClass* pFcs, GsQueryFilter* pFilter);
	/// \brief 
	/// \param pCursor 
	GsFeatureDataStatistics(GsFeatureCursor* pCursor);
	~GsFeatureDataStatistics();

	/// \brief 
	/// \return 
	virtual GsStatisticsResults Statistics();
};
GS_SMARTER_PTR(GsFeatureDataStatistics);
/// \brief FeatureDataIO数据统计
/// \details 任意数据类的统计实现类
class GS_API GsFeatureDataIOStatistics :public GsDataStatistics
{
	GsFeatureDataIO* m_pFeaIO;
	int m_nIndex;
public:
	/// \brief 
	/// \param pDataIO 
	/// \param nIndex 
	GsFeatureDataIOStatistics(GsFeatureDataIO * pDataIO,int nIndex);
	~GsFeatureDataIOStatistics();

	/// \brief 
	/// \return 
	virtual GsStatisticsResults Statistics();
};
GS_SMARTER_PTR(GsFeatureDataIOStatistics);

/// \brief GsRowClass数据统计
/// \details 二维表的统计实现类
class GS_API GsRowDataStatistics : public GsDataStatistics
{
	GsRowCursorPtr m_ptrRowCursor;
	GsRowClassPtr m_PtrRowCls;
public:
	/// \brief 
	/// \param pFcs 
	/// \param pFilter 
	GsRowDataStatistics(GsRowClass * pFcs, GsQueryFilter* pFilter);
	~GsRowDataStatistics();

	/// \brief 
	/// \return 
	virtual GsStatisticsResults Statistics();
};
GS_SMARTER_PTR(GsRowDataStatistics);


KERNEL_ENDNS