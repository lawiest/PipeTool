﻿#pragma once
//////////////////////////////////////////////////////////////////////////                                          
//!  \file label.h
//!  \brief GeoStar Kernel GIS内核
//!  \details 自动标注模块
//!  \author xiaochao
//!  \attention 
//!   Copyright (c) Wuda Geoinformatics Co.,Ltd. <br> 
//!   All Rights Reserved.
//!   版权所有(c) 武大吉奥信息技术有限公司 保留所有权利
//!  \version 1.1
//////////////////////////////////////////////////////////////////////////
#include "../utility/preconfig.h" 
#include<object.h>
#include<geodatabase.h>
#include<geometry.h>
#include<symbol.h>
#include "pointsymbol.h"

KERNEL_NS  

/// \brief 点标注九宫格位置
///        ４２５
///        １★０
///        ６３７
enum GsPointLabelPlace
{
	/// \brief 标注位于符号右边
	///
	///         ★Label
	///        
	eRight,
	/// \brief 标注位于符号左边
	///
	///       Label★
	///        
	eLeft,
	/// \brief 标注位于符号顶部
	///        Label
	///         ★
	///
	eTop,
	/// \brief 标注位于符号底部
	///
	///         ★
	///        Label
	eBottom,

	/// \brief 标注位于符号左上
	///    Label
	///         ★
	///        
	eTopLeft,
	/// \brief 标注位于符号右上
	///           Label
	///         ★
	///        
	eTopRight,
	/// \brief 标注位于符号左下
	///           
	///         ★
	///    Label   
	eBottomLeft,
	/// \brief 标注位于符号右下
	///           
	///         ★
	///           Label   
	eBottomRight,
};

/// \brief 点标注位置优先级别
enum GsPlaceOrderPriority
{
	/// \brief 放弃
	eAbandonPriority,
	/// \brief 高优先级
	eHighPriority,
	/// \brief 中等优先级
	eMiddlePriority,
	/// \brief 低先级
	eLowPriority,
};

/// \brief 线标注类型
enum GsLineLabelType
{
	/// \brief 无
	eUnKnown,
	/// \brief 水平标注
	eHorizon,
	/// \brief 垂直于线标注
	eVerticalLine,
	/// \brief 沿线标注
	eAlongLine,
	/// \brief 沿线标注，文字水平
	eAlongLineWithHorizon,
};

/// \brief 线标注起始点位置
enum GsLineLabelStartPos
{
	/// \brief 缺省位置 中点起算
	eDefaultPos,
	/// \brief 线起点位置
	eStartPos,
	/// \brief 线尾点位置
	eEndPos,
};

/// \brief 线与标注位置关系
enum GsLineLabelPos
{
	/// \brief 自动位置
	eAutoPlace,
	/// \brief 线上
	eTopLine,
	/// \brief 线下
	eBottomLine,
	/// \brief 线中
	eCenterLine,
};

/// \brief 标注背景框形状
enum GsLabelBackgroundFrame
{
	/// 无
	eNone,
	/// \brief 矩形
	eRectangle,
	/// \brief 圆角矩形
	eRoundRectangle,
	/// \brief 椭圆
	eEllipse,
};

/// \brief 标注对象
class GS_API GsLabel:public Utility::GsRefObject
{
protected:
	/// \brief 标注文字符号
	GsTextSymbolPtr m_ptrSymbol;
	/// \brief 标注点符号
	GsPointSymbolPtr m_ptrPointSymbol;
	/// \brief 标注ID
	int m_nID;
	/// \brief 标注所属几何标识
	long long m_nOwnID;
	/// \brief 标注属性标识
	long long m_nOrder;
	/// \brief 标注优先级
	int m_nPriority;
	/// \brief 标注文本
	Utility::GsString m_strText;
	GsGeometryBlob m_GeometryBlob;
	GsRawPoint m_Point;
	/// \brief 几何值
	double m_dGeoValue;
	/// \brief 标注背景框
	GsLabelBackgroundFrame m_eBgFrame;
	/// \brief 标注背景符号
	GsFillSymbolPtr m_ptrBgSymbol;

	GsLabel();
public:
	
	virtual  ~GsLabel();
	/// \brief 是否和另外一个label堆叠
	/// \param rhs 
	/// \return 
	virtual bool IsIntersects(GsLabel* rhs) const = 0;

	/// \brief 绘制标注
	/// \param pDT 
	/// \param pCanvas 
	virtual void Draw(GsDisplayTransformation* pDT,GsCanvas* pCanvas)  = 0;
	
	/// \brief 标准绘制的Geometry
	/// \return 
	GsGeometryBlob* Geometry();
	
	/// \brief 标注的点
	/// \param x 
	/// \param y 
	void LabelPoint(double x,double y);

	/// \brief 标注的点
	/// \return 
	GsRawPoint LabelPoint();

	/// \brief 重置标注为初始状态
	virtual void Reset();

	/// \brief 标注唯一标识
	/// \return 
	int ID() const;
	/// \brief 标注唯一标识
	/// \param n 
	void ID(int n);

	/// \brief 获取标注的优先级
	/// \return 
	int Priority()const;
	/// \brief 设置标注的优先级
	/// \param n 
	void Priority(int n);

	/// \brief 标注属性标识
	/// \return 
	long long Order()const;
	/// \brief 标注属性标识
	/// \param n 
	void Order(long long n);

	/// \brief 标注所属几何标识
	/// \return 
	long long OwnID()const;
	/// \brief 标注所属几何标识
	/// \param id 
	void OwnID(long long id);

	/// \brief 标注绘制的符号
	/// \return 
	GsTextSymbol* Symbol();
	/// \brief 标注绘制的符号
	/// \param sym 
	void Symbol(GsTextSymbol* sym);

	/// \brief 标注点符号
	/// \return 
	GsPointSymbol* PointSymbol();
	/// \brief 标注点符号
	/// \param sym 
	void PointSymbol(GsPointSymbol* sym);

	/// \brief 背景框形状
	/// \param eFrame 
	void BackgroundFrame(GsLabelBackgroundFrame eFrame);
	/// \brief 背景框形状
	/// \return 
	GsLabelBackgroundFrame BackgroundFrame();

	/// \brief 背景框符号
	/// \param pSymbol 
	void BackgroundSymbol(GsFillSymbol *pSymbol);
	/// \brief 背景框符号
	/// \return 
	GsFillSymbol* BackgroundSymbol();

	/// \brief 标注的文本
	/// \return 
	const char* Text()const;
	/// \brief 标注的文本
	/// \param str 
	void Text(const char* str);

	/// \brief 几何值（长、面积）
	/// \return 
	double GeometryValue();
	/// \brief 几何值（长、面积）
	/// \param dVal 
	void GeometryValue(double dVal);
};
/// \brief GsLabelPtr
GS_SMARTER_PTR(GsLabel);
class GsTrackCancel;
/// \brief 自动标注避让容器抽象基类
class GS_API GsLabelContainer:public Utility::GsRefObject
{
protected:
	/// \brief 已经安排位置的标注
	Utility::GsList<GsLabelPtr> m_lstPlaced;
	/// \brief 未能安排位置的标注
	Utility::GsList<GsLabelPtr> m_lstUnPlaced;

	/// \brief 标注对象池
	Utility::GsQueue<GsLabelPtr> m_LabelPool;
	
	/// \brief 最大存储的标注
	int m_nMax;

	/// \brief 标注容器是否可用
	bool m_bEnabled;

	/// \brief 是否自动标注
	bool m_bAutoLabel;

	/// \brief 是否去除重复标注
	bool m_bRemoveRepeatLabel;

	/// \brief 障碍物管理对象
	void *m_pObstacleManager;

	int m_nBaseId;
public:
	GsLabelContainer();
	virtual ~GsLabelContainer();

	/// \brief 准备避让
	virtual void Begin();

	/// \brief 增加一个标注到容器
	/// \param label 
	/// \return 
	virtual bool Add(GsLabel* label);

	/// \brief 结束避让
	virtual void End();

	/// \brief 绘制标注
	/// \param pDT 
	/// \param pCanvas 
	/// \param cancel 
	virtual void DrawLabel(GsDisplayTransformation* pDT,GsCanvas* pCanvas, GsTrackCancel* cancel = NULL);

	/// \brief 最大存储的标注
	/// \return 
	int MaxLabel();
	/// \brief 最大存储的标注
	/// \param n 
	void MaxLabel(int n);

	/// \brief 创建或者复用一个Label对象。
	/// \return 
	GsLabelPtr CreateLabel();

	/// \brief 是否去除重复标注
	/// \param bRemove 
	void RemoveRepeatLabel(bool bRemove);
	/// \brief 是否去除重复标注
	/// \return 
	bool RemoveRepeatLabel();

	/// \brief 障碍物管理类
	void* ObstacleMgr();

	/// \brief 检查冲突回调函数
	/// \details 参数1 
	Utility::GsDelegate<bool(GsLabel*)> CheckConflictCallBack;

public:
	/// \brief 标注容器是否可用
	/// \return 
	bool Enabled();
	/// \brief 标注容器是否可用
	/// \param b 
	void Enabled(bool b);

	/// \brief 标注是否自动避让
	/// \return 
	bool AutoLabel();
	/// \brief 标注是否自动避让
	/// \param b 
	void AutoLabel(bool b);

protected:
	/// \brief 回收标注
	/// \param lst 
	void Recovery(Utility::GsList<GsLabelPtr>& lst);
	/// \brief 
	/// \param label 
	void Recovery(GsLabel* label);

	/// \brief 准备避让
	virtual void OnBegin();

	/// \brief 增加一个标注到容器
	/// \param label 
	/// \return 
	virtual bool OnAdd(GsLabel* label);

	/// \brief 结束必避让
	virtual void OnEnd();
};
/// \brief GsLabelContainerPtr
GS_SMARTER_PTR(GsLabelContainer);


class GS_API GsSimpleLabelContainer:public GsLabelContainer
{
protected:
	/// \brief 准备避让
	virtual void OnBegin();

	/// \brief 增加一个标注到容器
	/// \param label 
	/// \return 
	virtual bool OnAdd(GsLabel* label);

	/// \brief 结束必避让
	virtual void OnEnd();

public:
	GsSimpleLabelContainer();
	virtual ~GsSimpleLabelContainer();
};
/// \brief GsSimpleLabelContainerPtr
GS_SMARTER_PTR(GsSimpleLabelContainer);

/// \brief 进阶版标注容器，采用更为复杂的避让规则
class GS_API GsAdvancedLabelContainer:public GsSimpleLabelContainer
{
protected:
	/// \brief 准备避让
	virtual void OnBegin();

	/// \brief 增加一个标注到容器
	/// \param label 
	/// \return 
	virtual bool OnAdd(GsLabel* label);

	/// \brief 结束必避让
	virtual void OnEnd();
public:
	GsAdvancedLabelContainer();
	virtual ~GsAdvancedLabelContainer();

};
/// \brief GsAdvancedLabelContainerPtr
GS_SMARTER_PTR(GsAdvancedLabelContainer);

/// \brief 自动标注计算基类
class GS_API GsLabelProperty:public Utility::GsRefObject
{
protected:
	/// \brief 标注符号的Clone，用于计算标注范围
	GsTextSymbolPtr m_ptrSymbolClone;

	/// \brief 公用的SE计算对象
	geostar::safe_ga m_ga;

	/// \brief 缓存一个Label的位置
	Utility::GsVector<Utility::GsRectF> m_vecLabelRects;

	/// \brief 当前DT
	GsDisplayTransformationPtr m_ptrDT;
	/// \brief 计算标注内容
	GsCanvasPtr			m_ptrTextCanvas;

	/// \brief 标注容器
	GsLabelContainerPtr m_ptrContainer;
	/// \brief 记录容器原始状态
	bool m_bOldRepeatLabelState;

	//合并标注参数
	/// \brief 待合并的几何对象
	Utility::GsVector<GsGeometryPtr> m_vecUnionGeo;
	/// \brief 合并标注文本
	Utility::GsString m_strUnionLabel;
	/// \brief 合并标注当前字段值
	Utility::GsString m_strUnionFieldVal;
	/// \brief 合并几何符号
	GsSymbolPtr m_ptrUnionSymbol;

	double m_dbSimpleTol;
	double m_dbUnionTol;
	double m_fBgSpace;

	/// \brief 使用新的简化算法对象
	GsTopologyPreservingGeometrySimplifierPtr m_ptrSimplifier;
protected:
	/// \brief 标注绘制的符号
	GsTextSymbolPtr m_ptrSymbol;

	/// \brief 标注优先级
	int m_nLabelPriority;
	/// \brief 标注的字段名
	Utility::GsString m_strFieldName;
	/// \brief 标注字段索引
	int m_nFieldIndex;

	/// \brief 是否允许重复标注
	bool m_bRemoveRepeatLabel;

	/// \brief 标注间距（单位mm）
	float m_fLabelDistance;
	double m_dGeoLabelDistance;

	/// \brief 背景框类型
	GsLabelBackgroundFrame m_eBgFrame;
	/// \brief 背景框符号
	GsFillSymbolPtr m_ptrBgSymbol;

	GsCalloutBackgroundPtr m_ptrBackground;

	/// \brief 标注最小要素大小(mm)
	float m_fLimitSize;
	float m_fGeoLimitSize;

	/// \brief 合并标注字段
	Utility::GsString m_strUnionField;
	/// \brief 合并标注字段索引
	int m_nUnionFieldIndex;
	/// \brief 表达式解析
	void* m_ExpressionParser;
	/// \brief 是否是简单表达式
	bool m_IsSimpleExpression;
protected:
	GsLabelProperty();

public:
	
	virtual ~GsLabelProperty();
	
	/// \brief 准备开始标注计算
	/// \param pDT 
	/// \param pContainer 
	virtual void Begin(GsDisplayTransformation* pDT, GsLabelContainer* pContainer);
	/// \brief 计算标注
	/// \param pFea 
	/// \param pSym 
	/// \return 
	virtual bool CalculateLabel(GsFeature* pFea, GsSymbol* pSym);
	/// \brief 计算标注
	/// \param pGeo 几何对象
	/// \param strLabel	标注文本
	/// \param pSym	几何符号
	/// \param strUnionValue 合并标注字段值（如果为NULL则跟标注文本一致）
	/// \return 
	virtual bool CalculateLabel(GsGeometry *pGeo, const char* strLabel, GsSymbol* pSym, const char* strUnionValue=0);
	/// \brief 结束标注计算
	virtual void End();

	/// \brief 克隆
	/// \return 
	virtual Utility::GsSmarterPtr<GsLabelProperty> Clone();
	
public:
	/// \brief 标注优先级
	/// \param nPriority 
	void LabelPriority(int nPriority);
	/// \brief 标注优先级
	/// \return 
	int LabelPriority();

	/// \brief 要标注的字段名称（支持多字段标注的表达式）
	/// \return 
	Utility::GsString LabelField();
	/// \brief 要标注的字段名称（支持多字段标注的表达式）
	/// \param strField 
	void LabelField(const char* strField);
	
	/// \brief 标注绘制的符号
	/// \return 
	GsTextSymbol* Symbol();
	/// \brief 标注绘制的符号
	/// \param sym 
	void Symbol(GsTextSymbol* sym);

	/// \brief 是否去除重复标注
	/// \param bRemove 
	void RemoveRepeatLabel(bool bRemove);
	/// \brief 是否去除重复标注
	/// \return 
	bool RemoveRepeatLabel();

	/// \brief 标注间距（单位mm）
	/// \param fDist 
	void LabelDistance(float fDist);
	/// \brief 标注间距（单位mm）
	/// \return 
	float LabelDistance();

	/// \brief 背景框形状
	/// \param eFrame 
	void BackgroundFrame(GsLabelBackgroundFrame eFrame);
	/// \brief 背景框形状
	/// \return 
	GsLabelBackgroundFrame BackgroundFrame();

	/// \brief 背景框符号
	/// \param pSymbol 
	void BackgroundSymbol(GsFillSymbol *pSymbol);
	/// \brief 背景框符号
	/// \return 
	GsFillSymbol* BackgroundSymbol();

	/// \brief 背景框
	/// \param ptrBackground 
	void CalloutBackground(GsCalloutBackground* ptrBackground);
	/// \brief 背景框
	/// \return 
	GsCalloutBackground* CalloutBackground();
	/// \brief 要素大小限制（小于尺寸的几何不生成标注）
	/// \param fSize 
	void LimitSize(float fSize);
	/// \brief 要素大小限制（小于尺寸的几何不生成标注）
	/// \return 
	float LimitSize();

	/// \brief 合并标注字段
	/// \param szUnionField 
	void UnionLabelField(const char* szUnionField);
	/// \brief 合并标注字段
	/// \return 
	Utility::GsString UnionLabelField();

protected:
	/// \brief 计算标注
	/// \param pGeo 几何对象
	/// \param strLabel	标注文本
	/// \param pSym	几何符号
	/// \return 
	virtual bool OnCalculateLabel(GsGeometry *pGeo, const char* strLabel, GsSymbol* pSym) = 0;

	/// \brief 过滤标注位置
	/// \param pLabel 
	/// \return 
	virtual bool FilterLabelPosition(GsLabel *pLabel);

	/// \brief 计算标注点的位置
	/// \param pGeo 
	/// \param nFlag 
	/// \return 
	virtual GsRawPoint LabelPoint(GsGeometry* pGeo, int nFlag = geostar::prop_geo_label);

	/// \brief 计算背景框距文字边界距离
	/// \param dWidth 
	/// \param dHeight 
	/// \return 
	virtual Utility::GsPTF CalBackgroundSpace(float dWidth, float dHeight);

	/// \brief 获取字段值
	/// \param pFea 
	/// \param strFieldName 
	/// \param nColumn 
	/// \return 
	Utility::GsString FieldText(GsFeature* pFea, const Utility::GsString& strFieldName, int nColumn);

	/// \brief 创建一个标注对象
	/// \return 
	GsLabelPtr CreateLabel();

	/// \brief 计算合并几何标注
	void CalUnionGeoLabel();

	/// \brief 计算几何值（长度、面积）
	/// \param pGeo 
	/// \return 
	double CalGeometryValue(GsGeometry *pGeo);

	/// \brief 裁切几何
	/// \param pSrcGeo 
	/// \return 
	GsGeometryPtr FilterGeometry(GsGeometry *pSrcGeo);

	/// \brief 合并几何
	/// \param vecGeo 
	/// \param tol 
	/// \return 
	GsGeometryPtr UnionGeometry(const Utility::GsVector<GsGeometryPtr>& vecGeo, double tol);

	/// \brief 转化几何数组对象
	/// \param vecGeo 
	/// \return 
	geostar::gobjptr ConvertObjectArray(const Utility::GsVector<GsGeometryPtr>& vecGeo);

	/// \brief 克隆自身属性和父类的属性。
	/// \param pLabel 
	void Assign(GsLabelProperty * pLabel);
};

/// \brief GsLabelPropertyPtr
GS_SMARTER_PTR(GsLabelProperty);


/// \brief 点自动标注计算类
class GS_API GsPointLabelProperty:public GsLabelProperty
{
public:
	/// \brief 换行符参数
	struct GsLineBreakParam
	{
		GsLineBreakParam()
			: m_nMinWords(0), m_nMaxRows(0)
			, m_strLineBreak("")
			, m_bWordGroup(false)
			, m_ptrWordAnalyzer(new Utility::GsSimpleWordAnalyzer())
		{
		}

		bool IsValid()
		{
			if ((m_nMaxRows <= 0 || m_nMinWords < 0) && m_strLineBreak.empty() && !m_bWordGroup)
				return false;
			return true;
		}
		/// \brief 每行允许的最小字数
		int m_nMinWords;
		/// \brief 允许的最大行数
		int m_nMaxRows;
		/// \brief 换行符
		Utility::GsString m_strLineBreak;
		/// \brief 是否分词组
		bool m_bWordGroup;
		/// \brief 分词器
		Utility::GsWordAnalyzerPtr m_ptrWordAnalyzer;
	};
protected:
	/// \brief 九宫格优先级
	Utility::GsVector<Utility::GsPair<GsPointLabelPlace,GsPlaceOrderPriority> > m_PlaceOrder;

	/// \brief 点与标注间距（单位mm）
	float m_fPointSpaceByLabel;
	/// \brief 是否换行
	bool m_bLineBreak;
	/// \brief 换行符参数
	GsLineBreakParam m_LineBreakParam;
	/// \brief 点标注与符号同时绘制
	bool m_bDrawLabelAndPoint;

	/// \brief 标注避让的最小比例尺范围（1：x）
	double m_dAvoidMinScale;
	/// \brief 标注避让的最大比例尺范围（1：x）
	double m_dAvoidMaxScale;

	/// \brief 避让数据列表
	UTILITY_NAME::GsVector<void*> m_vecAvoidData;
	UTILITY_NAME::GsStlMap<Utility::GsString, GsFeatureClassPtr> m_mapAvoidFeaClass;
	void* m_pObstacle;
public:
	using GsLabelProperty::CalculateLabel;
	GsPointLabelProperty();
	virtual ~GsPointLabelProperty();

	/// \brief 准备开始标注计算
	/// \param pDT 
	/// \param pContainer 
	virtual void Begin(GsDisplayTransformation* pDT,GsLabelContainer* pContainer);
	
	/// \brief 结束标注计算
	virtual void End();

	/// \brief 克隆
	/// \return 
	virtual GsLabelPropertyPtr Clone();

	/// \brief 存储避让数据
	/// \brief param strAvoidDataName避让数据名称
	/// \brief param pFeatureClass 数据集对象
	void StoreAvoidDataSource(const char* strAvoidDataName, GsFeatureClass* pFeatureClass);

public:
	/// \brief 获取标注位置的优先级
	/// \param e 
	/// \return 
	GsPlaceOrderPriority PlaceOrder(GsPointLabelPlace e);
	/// \brief 设置标注位置的优先级
	/// \param e 
	/// \param order 
	void PlaceOrder(GsPointLabelPlace e,GsPlaceOrderPriority order);

	/// \brief 点与标注间距
	/// \param fSpace 
	void PointSpaceByLabel(float fSpace);
	/// \brief 点与标注间距
	/// \return 
	float PointSpaceByLabel();

	/// \brief 是否换行
	/// \param bEnable 
	void LineBreak(bool bEnable);
	/// \brief 是否换行
	/// \return 
	bool LineBreak();

	/// \brief 换行符参数
	/// \return 
	GsLineBreakParam& LineBreakParam();

	/// \brief 同时绘制点符号和标注
	/// \param bEnable 
	void DrawPointAndLabel(bool bEnable);
	/// \brief 同时绘制点符号和标注
	/// \return 
	bool DrawPointAndLabel();
	
	/// \brief 标注避让的最小比例尺范围（1：x）
	/// \param dScale 
	void AvoidMinScale(double dScale);
	/// \brief 标注避让的最小比例尺范围（1：x）
	double AvoidMinScale();

	/// \brief 标注避让的最大比例尺范围（1：x）
	/// \param dScale 
	void AvoidMaxScale(double dScale);
	/// \brief 标注避让的最大比例尺范围（1：x）
	double AvoidMaxScale();

	/// \brief 增加避让数据
	/// \param strName 
	/// \param strWhere 
	/// \param dSize 
	void AddAvoidData(const char* strName, const char* strWhere="", double dSize = 0.0);
	/// \brief 删除避让数据
	/// \param strName 
	void RemoveAvoidData(const char* strName);
	/// \brief 获取避让数据名称
	UTILITY_NAME::GsVector< Utility::GsString > AvoidDataName();
	/// \brief 清空避让数据
	void ClearAvoidData();

protected:
	/// \brief 计算标注
	/// \param pGeo 几何对象
	/// \param strLabel	标注文本
	/// \param pSym	几何符号
	/// \param strUnionValue 合并标注字段值（如果为NULL则跟标注文本一致）
	/// \return 
	virtual bool OnCalculateLabel(GsGeometry *pGeo, const char* strLabel, GsSymbol* pSym);
	/// \brief 过滤标注位置
	/// \param pLabel 
	/// \return 
	virtual bool FilterLabelPosition(GsLabel *pLabel);
	/// \brief 保存障碍物数据
	void StoreAvoidData();
	/// \brief 计算标注候选位置
	/// \param pGeo 
	/// \param pLabel 
	/// \return 
	bool CalLabelPosition(GsGeometry *pGeo, GsLabel* pLabel);
	/// \brief 标注位置是否冲突
	/// \param pLabel 
	/// \return 
	bool IsLabelPositionConflict(GsLabel *pLabel);

	/// \brief 
	/// \param e 
	/// \param w 
	/// \param h 
	/// \param sw 
	/// \param sh 
	/// \param distXY 
	/// \return 
	Utility::GsPTF Offset(GsPointLabelPlace  e,float w,float h,float sw,float sh, Utility::GsPTF distXY);
	/// \brief 
	/// \param e 
	/// \param w 
	/// \param h 
	/// \param sw 
	/// \param sh 
	/// \param dDist 
	/// \return 
	float OffsetX(GsPointLabelPlace e,float w,float h,float sw,float sh, double dDist);
	/// \brief 
	/// \param e 
	/// \param w 
	/// \param h 
	/// \param sw 
	/// \param sh 
	/// \param dDist 
	/// \return 
	float OffsetY(GsPointLabelPlace e,float w,float h,float sw,float sh, double dDist);

	/// \brief 格式化标注文本
	/// \param strLabel 
	/// \return 
	Utility::GsString FormatLabelText(const char* strLabel);
	/// \brief 按照换行符打断字符串
	/// \param str 
	/// \param nStart 
	/// \param nEnd 
	/// \param vecLines 
	void BreakString(const Utility::GsWString& str, int nStart, int nEnd, UTILITY_NAME::GsVector<Utility::GsWString>& vecLines);
	/// \brief 通过行列数格式化字符串
	/// \param vecSubStr 
	/// \param vecLines 
	void LimitRowAndCol(const UTILITY_NAME::GsVector<UTILITY_NAME::GsVector<Utility::GsWString>>& vecSubStr, UTILITY_NAME::GsVector<Utility::GsWString>& vecLines);
	
	/// \brief 克隆自身属性和父类的属性。
	/// \param pLabel 
	void Assign(GsLabelProperty* pLabel);
};
/// \brief GsPointLabelPropertyPtr
GS_SMARTER_PTR(GsPointLabelProperty);


struct LabelInfo;
/// \brief 线自动标注计算类
class GS_API GsLineLabelProperty:public GsLabelProperty
{
protected:
	/// \brief 线标注类型
	GsLineLabelType m_eLineLabelType;
	/// \brief 标注与线位置关系
	GsLineLabelPos m_ePosType;
	/// \brief 线标注起点位置
	GsLineLabelStartPos m_eStartPos;
	/// \brief 是否标注多次
	bool m_bMultiLabel;
	/// \brief 线偏移量（单位mm）
	float m_fOffset;
	/// \brief 地理坐标线偏移量
	double m_dGeoLineOffset;
	/// \brief 同一条地物线标注多次, 标注次数, 不是单个地物分段标注多次
	int m_MultiSubPosCount;
	/// \brief 同一条地物线标注多次, 标注起始段索引
	int m_MultiSubPosIndex;
public:
	using GsLabelProperty::CalculateLabel;
	GsLineLabelProperty();
	virtual ~GsLineLabelProperty();

	/// \brief 
	/// \param pDT 
	/// \param pContainer 
	void Begin(GsDisplayTransformation* pDT,GsLabelContainer* pContainer);
	/// \brief 结束标注计算
	virtual void End();
	/// \brief 克隆
	/// \return 
	virtual GsLabelPropertyPtr Clone();

public:
	/// \brief 线标注类型
	/// \param eType 
	void LineLabelType(GsLineLabelType eType);
	/// \brief 线标注类型
	/// \return 
	GsLineLabelType LineLabelType();

	/// \brief 标注与线位置关系
	/// \param ePos 
	void LabelPos(GsLineLabelPos ePos);
	/// \brief 标注与线位置关系
	/// \return 
	GsLineLabelPos LabelPos();

	/// \brief 线标注起始点位置
	/// \param ePos 
	void StartPos(GsLineLabelStartPos ePos);
	/// \brief 线标注起始点位置
	/// \return 
	GsLineLabelStartPos StartPos();

	/// \brief 是否标注多次
	/// \param bValue 
	void MultiLabel(bool bValue);
	/// \brief 是否标注多次
	/// \return 
	bool MultiLabel();

	/// \brief 偏移量（单位mm）
	/// \param fOffset 
	void Offset(float fOffset);
	/// \brief 偏移量（单位mm）
	/// \return 
	float Offset();

	/// \brief 同一条地物线标注多次,标注次数,不是单个地物分段标注多次
	/// \param nSubsCount 
	void MultiSubPosCount(int nSubsCount);
	/// \brief 同一条地物线标注多次,标注次数,不是单个地物分段标注多次
	/// \return 
	int MultiSubPosCount();

	/// \brief 同一条地物线标注多次,标注的段数
	/// \param nSubIndex 
	void MultiSubPosIndex(int nSubIndex);
	/// \brief 同一条地物线标注多次,标注的段数
	/// \return 
	int MultiSubPosIndex();
protected:
	/// \brief 计算标注
	/// \param pGeo 几何对象
	/// \param strLabel	标注文本
	/// \param pSym	几何符号
	/// \return 
	virtual bool OnCalculateLabel(GsGeometry *pGeo, const char* strLabel, GsSymbol* pSym);

	/// \brief 转换标注对象
	/// \param labelInfo 
	/// \param pLabel 
	/// \return 
	bool CalLabelPosition(LabelInfo& labelInfo, GsLabel* pLabel);

	/// \brief 计算标注点
	/// \param pGeo 
	/// \param dWordLen 
	/// \param nWordNum 
	/// \param vecLabels 
	void LabelPoints(GsGeometry* pGeo, double dWordLen, int nWordNum, Utility::GsVector<LabelInfo>& vecLabels);

	/// \brief 计算标注点
	/// \param pPath 
	/// \param dWordLen 
	/// \param nWordNum 
	/// \param vecLabels 
	void LabelPointsForPath(GsPath* pPath, double dWordLen,int nWordNum, Utility::GsVector<LabelInfo>& vecLabels);

	/// \brief 重新排列标注点序
	/// \param label 
	/// \param dTextHeight 
	/// \param dOffset 
	void ReorderLabel(LabelInfo& label, double dTextHeight, double dOffset);

	/// \brief 沿线标注类型重新排列点序
	/// \param vecPoint 
	/// \param dTextHeight 
	/// \param dOffset 
	void ReorderForAlongLine(Utility::GsVector<GsRawPoint>& vecPoint, double dTextHeight, double dOffset);
	
	/// \brief 沿线标注文字水平重新排列点序
	/// \param vecPoint 
	/// \param dTextHeight 
	/// \param dOffset 
	void ReorderForAlongLineHorizonText(Utility::GsVector<GsRawPoint>& vecPoint, double dTextHeight, double dOffset);
	
	/// \brief 水平标注排列点序
	/// \param vecPoint 
	/// \param dTextHeight 
	/// \param dOffset 
	void ReorderForHorizon(Utility::GsVector<GsRawPoint>& vecPoint, double dTextHeight, double dOffset);
	
	/// \brief 垂直于线标注排列点序
	/// \param vecPoint 
	/// \param dTextHeight 
	/// \param dOffset 
	void ReorderForVerticalLine(Utility::GsVector<GsRawPoint>& vecPoint, double dTextHeight, double dOffset);

	/// \brief 克隆自身属性和父类的属性。
	/// \param pLabel 
	void Assign(GsLabelProperty* pLabel);
};
/// \brief GsLineLabelPropertyPtr
GS_SMARTER_PTR(GsLineLabelProperty);

/// \brief 面标注类型
enum GsSurfaceLabelType
{
	eNormal,	// 常规
	eSkeletonLine,	// 沿骨架线标注
};

/// \brief 面自动标注计算类
class GS_API GsSurfaceLabelProperty:public GsLineLabelProperty
{
protected:
	GsSurfaceLabelType m_eSurfaceLabelType;
public: 
	using GsLabelProperty::CalculateLabel;
	GsSurfaceLabelProperty();
	virtual ~GsSurfaceLabelProperty();

	/// \brief 克隆
	/// \return 
	virtual GsLabelPropertyPtr Clone();

	/// \brief 标注类型
	/// \param eType 
	void SurfaceLabelType(GsSurfaceLabelType eType);
	/// \brief 标注类型
	/// \return 
	GsSurfaceLabelType SurfaceLabelType();
protected:
	/// \brief 计算标注
	/// \param pGeo 几何对象
	/// \param strLabel	标注文本
	/// \param pSym	几何符号
	/// \return 
	virtual bool OnCalculateLabel(GsGeometry *pGeo, const char* strLabel, GsSymbol* pSym);

	/// \brief 计算标注点的位置
	/// \param pobj 
	/// \param nFlag 
	/// \return 
	virtual GsRawPoint LabelPoint(geostar::geo_object* pobj, int nFlag = geostar::prop_geo_label);

	/// \brief 转换标注对象
	/// \param pGeo 
	/// \param pLabel 
	/// \return 
	bool CalLabelPosition(GsGeometry *pGeo, GsLabel *pLabel);
	/// \brief 
	/// \param pGeo 
	/// \param pLabel 
	/// \return 
	bool CalLabelPosForNormal(GsGeometry *pGeo, GsLabel *pLabel);
	/// \brief 
	/// \param pGeo 
	/// \param pLabel 
	/// \return 
	bool CalLabelPosForSkeletonLine(GsGeometry *pGeo, GsLabel *pLabel);

	/// \brief 将Path转化为屏幕坐标系范围
	/// \param pPath 
	/// \return 
	GsPathPtr TransPathToScreen(GsPath *pPath);

	/// \brief 计算标注方向
	/// \param pPath 
	/// \return 
	GsRawPoint CalLabelDirection(GsPath* pPath);

	/// \brief 计算最小斜外接矩形
	/// \param pobj 
	/// \return 
	GsPathPtr CalMinimumEnvelop(geostar::geo_object* pobj);
};
/// \brief GsSurfaceLabelPropertyPtr
GS_SMARTER_PTR(GsSurfaceLabelProperty);


KERNEL_ENDNS