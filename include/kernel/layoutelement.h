#pragma once
#include "../utility/preconfig.h" 
#include <object.h>
#include "spatialreference.h"
#include "geometry.h"
#include "map.h"
#include <matrix.h>
#include "serialize.h"
KERNEL_NS

/// \brief 元素测试命中的结果
enum GsElementHittestResult
{
	/// \brief 没有命中
	eElementHitNone,

	/// \brief 完整命中全部
	eElementHitWhole = 1,
};
/// \brief 制图对象
class GS_API GsElement :public Utility::GsRefObject
{

protected:
	GsAffineCoordinateTransformationPtr m_ptrTransform;
	GsMatrixD				m_Matrix;//制图的变换矩阵
	bool					m_Visible;
	bool					m_Selected;
	bool					m_CanHit;
	GsGeometryPtr			m_ptrGeometry;
	double					m_dblReferenceScale; // 参考比例尺
	UTILITY_NAME::GsRect	m_PageRect;//纸张在显示设备中的大小。
	UTILITY_NAME::GsString	m_Name;//名字接口
	UTILITY_NAME::GsString	m_ClassName;//实例名字
	GsElement();
	/// \brief 绘制的接口，子类实现子类的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType) = 0;
	/// \brief 任意几何对象中测试
	/// \param geo 测试的几何对象
	/// \return 返回测试的结果
	virtual GsElementHittestResult OnHittest(GsGeometry* geo);

	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsElement* pEle);

	/// \brief 计算并修改传入的矩阵，转换前后box的左下角点不变。
	/// \param box 旧的外接矩形范围
	/// \param point 转换之后，新的外接框矩形的最大点(XMax, YMax),其中转换过程中原有的(XMin,YMin)不变。
	/// \param mat 输出参数：计算出转换的矩阵，并且返回
	void CalcParamsMatrix(const GsBox& box, const GsRawPoint&point, GsMatrixD & mat);

	/// \brief 通过传入旧的box和新的box，计算并修改传入的矩阵
	/// \param oldBox 旧的外接矩形范围
	/// \param newBox 新的外接矩形范围
	/// \param mat 输出参数：计算出转换的矩阵，并且返回
	void CalcParamsMatrix(const GsBox& oldBox, const GsBox& newBox, GsMatrixD & mat);
	
	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	bool XmlSerialize(UTILITY_NAME::GsSerializeStream * pSerStream);
	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	bool XmlDeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream);
public:
	virtual ~GsElement();

	/// \brief 获取仿射变换的矩阵
	/// \return 返回放射变换的矩阵
	virtual GsMatrixD Transform();
	/// \brief 设置仿射变换的矩阵
	/// \param mx 设置传入的矩阵
	virtual void Transform(const GsMatrixD& mx);

	/// \brief 单点命中测试
	/// \param pt 测试的点数据
	/// \param tol 容差
	/// \return 返回测试的结果
	virtual GsElementHittestResult Hittest(const GsRawPoint& pt, double tol);
	/// \brief 矩形命中测试
	/// \param box 测试的矩形数据
	/// \return 返回测试的结果
	virtual GsElementHittestResult Hittest(const GsBox& box);
	/// \brief 任意几何对象中测试
	/// \param geo 测试的几何数据
	/// \return 返回测试的结果
	virtual GsElementHittestResult Hittest(GsGeometry* geo);


	/// \brief 是否可见
	/// \return 返回是否可见的属性
	bool Visible();
	/// \brief 设置是否可见
	/// \param b 设置可见状态
	void Visible(bool b);

	/// \brief 是否选中的状态
	/// \return 返回是否选中的属性
	bool Selected();
	/// \brief 是否选中
	/// \param bSelect设置选中状态
	void Selected(bool bSelect);

	/// \brief 能否被命中
	/// \return 返回能否被命中的状态
	bool CanHit();
	/// \brief 能否被命中
	/// \param bCanHit 设置能否被命中的属性
	void CanHit(bool bCanHit);

	/// \brief 几何对象
	/// \return 返回获取到的制图中的集合对象
	virtual GsGeometry* Geometry();
	/// \brief 几何对象
	/// \param geo 设置几何对象
	void Geometry(GsGeometry* geo);

	/// \brief 获取参考比例尺
	/// \return 返回获取的参考比例尺
	double ReferenceScale();
	/// \brief 设置参考比例尺
	/// \param dblReferenceScale 设置的参考比例尺
	void ReferenceScale(double dblReferenceScale);

	/// \brief 设置纸张在设备中大小
	/// \param rect 设置纸张的大小
	void PageRect(UTILITY_NAME::GsRect rect);
	/// \brief 获取纸张在设备中的大小
	/// \return 返回获取纸张在设备中的大小
	UTILITY_NAME::GsRect PageRect();

	/// \brief 设置名字
	/// \param name 设置的名字
	void Name(const char* name);
	/// \brief 获取名字
	/// \return 获取制图的名字
	const char * Name();

	/// \brief 获取经过几何变换后用于绘制的几何对象
	/// \return 返回经过集合变换后的几何对象，用于绘制
	virtual GsGeometryPtr DisplayGeometry();

	/// \brief 绘制的接口
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象
	/// \param drawType 绘制的阶段
	virtual void Draw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);

	/// \brief 获取位置 外接矩形的左下角位置(xmin,ymin)
	/// \return 获取制图的外接矩形的左下角位置
	virtual GsRawPoint Position();
	/// \brief 设置位置 外接矩形的左下角位置(xmin,ymin)
	/// \param position 设置制图的位置，以左下角位置为准
	virtual void Position(const GsRawPoint & position);

	/// \brief 获取制图的大小
	/// \return 返回制图的大小
	virtual Utility::GsSizeF Size();
	/// \brief 设置大小，设置后，(xmin, ymin)点不变
	/// \param sizef 设置制图的大小，
	virtual void Size(const Utility::GsSizeF & sizef);

	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	//virtual GeoStar::Utility::GsString ClassName();
};
/// \brief GsElementPtr
GS_SMARTER_PTR(GsElement);

/// \brief 地图元素
class GS_API GsMapElement :public GsElement, public UTILITY_NAME::GsSerialize
{
	GsPaintDevicePtr m_ptrPaintDevice;
	GsMapPtr m_ptrMap;
	bool		m_bClipPage;//控制是否裁切纸张。
	
	bool		m_bShowBorder;
	bool		m_isDirty;//控制是否需要清理缓存的变量
	GsSymbolPtr m_ptrBorderSymbol;
	double		m_dblBorderOffset;

	double m_dblFixScale;
	bool m_bFixScale;
	bool m_bRealScale;//是否更改制图比例尺，只有在用户设置了真实比例尺之后，才会变成true
	/// \brief 纸张设备上面绘制的地图，真实的比例尺，可以称之为制图比例尺,也是纸张打印后比例。
	double m_dblRealScale;
	bool m_bMapExtent;//记录用户是否设置了真实mapExtent的范围。
	GsBox m_mapExtent;//记录真实mapExtent的范围。

	double m_dblLastMapScale;//记录上次的MapScale。 临时变量，仅仅为了和本次作比较
	double m_dblLastPageScale;//记录上次的PageScale。临时变量，仅仅为了和本次作比较
	double m_dblLastScale;//上次的Scale记录。
	
	GsDisplayTransformationPtr m_ptrDT;//page和map对应的坐标转换对象
	UTILITY_NAME::GsSimpleBitmapPtr m_ptrBitmap;//临时位图
	GsBox  m_Box;
	UTILITY_NAME::GsRect m_Rect;

	/// \brief 初始化page和map对应的坐标转换对象
	/// \param pDisplay 屏幕显示对象，画布相关
	void InitDisplayTransformationForPageWithMap(GsDisplay* pDisplay);


	/// \brief 绘制MapElement中的map对象
	/// \param rect 绘制的设备范围。
	/// \param disp 绘制的设备
	/// \param pCancel 取消对象
	void DrawMap(const Utility::GsRect& rect, GsDisplay* disp, GsTrackCancel* pCancel);

	/// \brief 转换map坐标和纸张坐标的内部函数。
	/// \param isTransMapToPage 如果为真，map转换为page，如果为假，page转换为map
	/// \param point 输入点的坐标
	/// \param outPoint 返回转换后的坐标
	void TransMapPagePoint(bool isTransMapToPage, const GsRawPoint & point, GsRawPoint & outPoint);

	/// \brief 将画布上缓存图片保存到m_ptrBitmap
	/// \param pScreenDisplay 屏幕显示对象，画布相关
	void SaveCacheBitmap(GsScreenDisplay* pScreenDisplay);
public:
	GsMapElement();
	/// \brief 地图元素制图
	/// \param pMap 地图元素制图绑定的地图
	GsMapElement(GsMap* pMap);
	~GsMapElement();
	/// \brief 获取绑定的Map
	/// \return 返回获取绑定的Map
	GsMap* Map();

	/// \brief 图廓符号
	/// \return 返回图廓符号
	GsSymbol* BorderSymbol();

	/// \brief 设置图廓符号
	/// \param sym 图廓符号
	void BorderSymbol(GsSymbol* sym);

	/// \brief 是否显示图廓
	/// \return 返回是否显示图廓
	bool ShowBorder();
	/// \brief 是否显示图廓
	/// \param bShow 是否显示图廓
	void ShowBorder(bool bShow);

	/// \brief 图廓显示位置的偏移
	/// \return 返回图廓显示位置的偏移
	double BorderOffset();
	/// \brief 图廓显示位置的偏移，默认位置是map制图画布的外接矩形。如果是正，则向内偏移；如果是负，则向外偏移
	/// \param offset 设置图廓显示位置的偏移 
	void BorderOffset(double offset);

	/// \brief 是否裁切纸张
	/// \return 返回是否裁切纸张
	bool ClipPage();
	/// \brief 是否裁切纸张
	/// \param bClip 设置是否裁切纸张
	void ClipPage(bool bClip);

	/// \brief 获取是否锁定比例尺
	/// \return 返回是否锁定比例尺
	bool IsFixedScale();
	/// \brief 设置是否锁定比例尺
	/// \param bFixedScale 设置是否锁定比例尺
	void IsFixedScale(bool bFixedScale);

	/// \brief 获取锁定的比例尺, 此比例尺为PageLauout得DT得来
	/// \return 返回锁定的比例尺
	double FixedScale();
	/// \brief 设置锁定比例尺, 此比例尺为PageLauout得DT得来, 如果想要制图页面一致不改变比例尺不得设置,
	/// \brief 如果需要动态锁定比例尺(Map范围变化后锁定变化后的比例尺,则通过mapelemet中map范围和mapelement的大小重新计算一个用来锁定)
	/// \brief 默认锁定值会从layout的dt中拿一个范围
	/// \param dblFixedScale 设置锁定的比例尺
	void FixedScale(double dblFixedScale);

	/// \brief 获取绘制的比例
	/// \return 返回绘制的比例
	double DrawScale();

	/// \brief 纸张设备上面绘制的地图，真实的比例尺，可以称之为制图比例尺,也是纸张打印后比例。
	/// \return 返回制图元素的的比例尺
	double RealScale();
	/// \brief 纸张设备上面绘制的地图，真实的比例尺，可以称之为制图比例尺,也是纸张打印后比例。
	/// \param dblRealScale 设置的制图元素的的比例尺
	void RealScale(double dblRealScale);

	/// \brief 纸张设备上面绘制的地图，获取真实的MapExtent
	/// \return 返回制图元素外接框对应的map范围
	GsBox MapExtent();
	/// \brief 纸张设备上面绘制的地图，设置真实的MapExtent
	/// \param extent 设置制图元素外接框对应的map范围
	void MapExtent(const GsBox& extent);

	/// \brief 纸张坐标转换为地图坐标。
	/// \param point 传入点的纸张坐标
	/// \return 返回对应的地图坐标
	GsRawPoint ToMapPoint(const GsRawPoint& point);

	/// \brief 地图坐标转换为纸张坐标。
	/// \param point 传入点的地图坐标
	/// \return 返回对应的纸张坐标
	GsRawPoint FromMapPoint(const GsRawPoint& point);

	/// \brief 如果上层修改了map其他属性，导致需要强制重新绘制，就需要清除缓存，需要设置Dirty为True。
	/// \param bDirty 当为True，就需要重新绘制，当为False，什么也不干。
	void Dirty(bool bDirty);

	/// \brief 获取当前Dirty状态
	/// \return 返回当前Dirty状态
	bool Dirty();

	/// \brief 获取Cache的bitmap,
	UTILITY_NAME::GsSimpleBitmapPtr CacheBitMap();

	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 将MapElement进行序列化
	/// \param pSerStream 
	/// \return 返回序列化是否成功
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 获取制图类型的名字
	/// \return 返回制图类型的名字
	virtual UTILITY_NAME::GsString ClassName();
protected:
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsMapElement* pEle);

	
};
/// \brief GsMapElementPtr
GS_SMARTER_PTR(GsMapElement);
DECLARE_CLASS_CREATE(GsMapElement);


/// \brief 基于特定形状的元素
class GS_API GsShapeElement :public GsElement ,public UTILITY_NAME::GsSerialize
{
protected:
	GsSymbolPtr			m_ptrSymbol;
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsShapeElement* pEle);
	
public:
	GsShapeElement();
	/// \brief 基于特定形状的元素
	/// \param geo 几何，用来描述特定形状
	/// \param sym 符号，用来绘制特定形状的样式
	GsShapeElement(GsGeometry* geo, GsSymbol* sym);
	/// \brief 基于特定形状的元素
	/// \param geo 几何，用来描述特定形状
	GsShapeElement(GsGeometry* geo);
	~GsShapeElement();
	/// \brief 获取符号
	/// \return 返回制图中绘制的符号
	virtual GsSymbol * Symbol();
	/// \brief 设置符号
	/// \param pSym 设置的符号
	virtual void Symbol(GsSymbol* pSym);
	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();
	

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 获取制图类型的名字
	/// \return 返回制图类型的名字
	virtual UTILITY_NAME::GsString ClassName() ;

};
/// \brief GsShapeElementPtr
GS_SMARTER_PTR(GsShapeElement);
DECLARE_CLASS_CREATE(GsShapeElement);

/// \brief 几何元素
class GS_API GsGeometryElement :public GsShapeElement
{

protected:
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsGeometryElement* pEle);
	
public:
	GsGeometryElement();
	/// \brief 几何元素制图
	/// \param geo 几何形状
	/// \param sym 绘制几何所用的符号
	GsGeometryElement(GsGeometry* geo, GsSymbol* sym);
	/// \brief 几何元素制图
	/// \param geo 几何形状
	GsGeometryElement(GsGeometry* geo);
	~GsGeometryElement();
	using GsElement::Transform;

	/// \brief 设置仿射变换的矩阵
	/// \param mx 仿射变换的矩阵
	virtual void Transform(const GsMatrixD& mx);

	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;
};
/// \brief GsGeometyElementPtr
GS_SMARTER_PTR(GsGeometryElement);
DECLARE_CLASS_CREATE(GsGeometryElement);


/// \brief 图块
class GsBlockElement :public GsGeometryElement
{
protected:
	/// \brief 图块Geometry
	GsGeometryPtr m_prtBlockGeometry;
	/// \brief 图块Element
	GsGeometryElementPtr m_ptrBlockElement;

	GsSymbolPtr m_ptrFillSym;


public:
	GsBlockElement();
	GsBlockElement(const GsBox& box, GsSymbol* pFillSym);
	~GsBlockElement() {}

	virtual void Transform(const GsMatrixD& mx);

	virtual GsElementPtr Clone();

	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream);
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream);
protected:
	void InitDrawData();
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);

};
GS_SMARTER_PTR(GsBlockElement);
DECLARE_CLASS_CREATE(GsBlockElement);

/// \brief 矩形元素
class GS_API GsEnvelopeElement :public GsGeometryElement
{
protected:
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsEnvelopeElement* pEle);
public:
	GsEnvelopeElement();
	/// \brief 矩形元素制图
	/// \param box 矩形
	GsEnvelopeElement(const GsBox & box);
	/// \brief 矩形元素制图
	/// \param pEnv 矩形几何对象
	GsEnvelopeElement(GsEnvelope* pEnv);
	~GsEnvelopeElement();
	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();
};
GS_SMARTER_PTR(GsEnvelopeElement);
DECLARE_CLASS_CREATE(GsEnvelopeElement);
/// \brief 指北针类型
enum GsNorthArrowType
{
	/// \brief 指北针，上方没有N标识
	eNorthArrowAllNoText,
	/// \brief 左边是白色的指北针，上方有N标识
	eNorthArrowLeft,
	/// \brief 右边是白色的指北针，上方有N标识
	eNorthArrowRight,
	/// \brief 全部黑色的指北针，上方有N标识
	eNorthArrowAll,
	/// \brief 四个方向的指北针，上方有N标识
	eNorthArrowFour,
	/// \brief 基于点符号得指北针,//geostar.ttf code:21-27
	eNorthArrowByPointSymbol,
};
/// \brief 指北针
class GS_API GsNorthArrow :public GsGeometryElement
{
	//➢➣➤
	/// \brief 旋转角度
	double m_dblAngle;
	/// \brief 记录外接框
	GsBox m_Box;

	/// \brief 记录原有的box，转换样式的时候使用
	GsBox m_BoxOrigin;

	/// \brief 绘制过程中记录左边三角形
	GsRingPtr m_ptrRingLeft;
	/// \brief 绘制过程中记录右边三角形
	GsRingPtr m_ptrRingRight;
	
	/// \brief 绘制四个方向指北针的时候 记录GsRing 
	GsRingPtr m_ptrRingFourLeft;
	/// \brief 绘制四个方向指北针的时候 记录GsRing 
	GsRingPtr m_ptrRingFourRight;
	/// \brief 绘制过程中记录文字外接框的矩阵
	GsRingPtr m_ptrRingText;

	/// \brief 绘制指北针的类型
	GsNorthArrowType m_NorthArrowType;
	/// \brief 绘制指北针文字的符号。
	GsTextSymbolPtr m_ptrTextSymbol;
	
	/// \brief 绘制指北针填充的颜色。
	Utility::GsColor m_Color;
	/// \brief 文字和指北针之间的间距。
	double m_Gap;

	/// \brief绘制指北针
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	void DrawNorthArrow(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief绘制四个箭头样式的指北针
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	void DrawNorthArrowFour(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);

	/// \brief 绘制指北针上方的"N"文字。
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	/// \param box 绘制指北针之前的外接框。
	/// \param coff 文字放大系数。以高除以高来计算。
	/// \return 返回绘制后的"N"文字的范围
	GsBox DrawTextN(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType, GsBox box, double coff = 1.0);

	/// \brief 初始化m_ptrRingLeft,m_ptrRingRight,m_ptrRingText;
	void InitNorthArraw();
protected:
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsNorthArrow* pEle);
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	
public:
	GsNorthArrow();
	/// \brief 指北针制图元素
	/// \param x 绘制的起始点xmin
	/// \param y 绘制的起始点ymin
	/// \param w 指北针的宽
	/// \param h 指北针的高
	/// \param type 指北针的样式
	GsNorthArrow(double x, double y, double w, double h, GsNorthArrowType type = eNorthArrowRight);
	~GsNorthArrow();

	/// \brief 获取指北针的样式
	/// \return 返回指北针的样式
	GsNorthArrowType NorthArrowType();
	/// \brief 设置指北针的样式
	/// \param type 指北针的样式
	void NorthArrowType(GsNorthArrowType type);

	/// \brief 获取指北针的颜色
	/// \return 返回指北针的颜色
	virtual Utility::GsColor Color();
	/// \brief 设置指北针颜色
	/// \param c 颜色
	virtual void Color(const Utility::GsColor& c);

	/// \brief 设置旋转角度,单位是度
	/// \return 返回旋转的角度
	virtual double Angle();
	/// \brief 旋转角度,单位是度
	/// \param Angle 角度
	virtual void Angle(double Angle);

	/// \brief 获取文字"N"的大小
	/// \return 返回文字N的大小
	virtual double TextSize();
	/// \brief 设置文字"N"的大小
	/// \param size 文字大小
	virtual void TextSize(double size);
	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

};
GS_SMARTER_PTR(GsNorthArrow);
DECLARE_CLASS_CREATE(GsNorthArrow);

/// \brief 图片
class GS_API GsPictureElement :public GsGeometryElement
{
	Utility::GsImagePtr        m_ptrImage;
	double m_dHeight;
	double m_dWidth;
	GsRawPoint m_ptCenter;
	/// \brief 图廓符号
	GsSymbolPtr m_ptrBorderSymbol; 

	/// \brief 初始化图片制图元素的属性
	/// \param x 制图元素的起始点xmin
	/// \param y 制图元素的起始点ymin
	/// \param pImg 制图元素绑定的图片
	void Init(double x, double y, Utility::GsImage *pImg);
public:
	GsPictureElement();
	/// \brief 从图片对象构造
	/// \param x 制图元素的起始点xmin
	/// \param y 制图元素的起始点ymin
	/// \param pImg 制图元素绑定的图片
	GsPictureElement(double x, double y,GeoStar::Utility::GsImage * pImg);
	/// \brief 从图片内存块构造
	/// \param x 制图元素的起始点xmin
	/// \param y 制图元素的起始点ymin
	/// \param pBlob 图片内存的起始位置
	/// \param nLen 图片内存的长度
	GsPictureElement(double x, double y, const unsigned char *pBlob, int nLen);
	/// \brief 从图片文件构造
	/// \param x 制图元素的起始点xmin
	/// \param y 制图元素的起始点ymin
	/// \param pImageFile 绑定的文件路径
	GsPictureElement(double x, double y, const char* pImageFile);
	~GsPictureElement();

	/// \brief 获取图片的高度
	/// \return 返回图片的高度
	double Height();
	/// \brief 设置图片的高度
	/// \param dHeight 图片的高度
	void Height(double dHeight);

	/// \brief 获取图片的宽度
	/// \return 图片的宽度
	double Width();
	/// \brief 设置的宽度
	/// \param dWidth 宽度
	void Width(double dWidth);

	/// \brief 获取图片的中心点位置
	/// \return 返回图片的中心点位置
	GsRawPoint CenterPoint();
	/// \brief 设置图片的中心点位置
	/// \param pt 图片的中心点
	void CenterPoint(const GsRawPoint& pt);

	/// \brief 设置图廓符号
	/// \param pSym 绘制图片轮廓的符号
	void BorderSymbol(GsSymbol* pSym);
	/// \brief 获取图廓符号
	/// \return 返回图廓符号
	GsSymbol* BorderSymbol();

	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

protected:
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsPictureElement* pEle);
};
GS_SMARTER_PTR(GsPictureElement);
DECLARE_CLASS_CREATE(GsPictureElement);


/// \brief 接幅表
/// \brief 三行三列 九宫格
class GS_API GsJoinMapTableElement :public GsGeometryElement
{
	/// \brief 接幅表中间面填充符号,默认斜线填充
	GsFillSymbolPtr m_ptrFillSymbol;
	/// \brief 接幅表文字绘制符号
	GsTextSymbolPtr m_ptrTextSymbol;
	/// \brief 接幅表边线绘制符号
	GsLineSymbolPtr m_ptrLineSymbol;
	/// \brief 存储需要绘制的文字
	UTILITY_NAME::GsVector< UTILITY_NAME::GsVector<UTILITY_NAME::GsString> > m_Rows;

	/// \brief 记录外接框的大小。
	GsBox m_box;

	/// \brief 初始化绘制的线等信息
	/// \param pointInter[][4] 输出参数：接图表制图的交叉点(4行4列)
	/// \param pointCenter[][3] 输出参数：接图表9宫格的9个中心点(3行3列)
	void InitJoinMapTable(GsRawPoint pointInter[][4], GsRawPoint pointCenter[][3]);

	/// \brief 绘制线段
	/// \param pDisp 显示的目标设备
	/// \param point1 起始点
	/// \param point2 终点
	/// \param pSymbol 绘制线段的符号
	void DrawLine(GsDisplay* pDisp, const GsRawPoint& point1, const GsRawPoint& point2, GsSymbol* pSymbol = NULL );

public:
	GsJoinMapTableElement();
	/// \brief 接幅表构造函数
	/// \param x 制图元素的起始点xmin
	/// \param y 制图元素的起始点ymin
	GsJoinMapTableElement(double x, double y);
	/// \brief 接幅表析构函数
	~GsJoinMapTableElement();
	/// \brief 将接幅表看成三行三列的数据，设置某一位置的值,row和col的取值为0,1,2
	/// \param row 行
	/// \param col 列
	/// \param text 数据
	void Value(int row, int col, const char* text);
	/// \brief 获取某一位置的值，row和col的取值为0,1,2
	/// \param row 行
	/// \param col 列
	/// \return 返回相应位置的数据
	UTILITY_NAME::GsString Value(int row, int col);
	/// \brief 接幅表中间面填充符号
	/// \return 返回填充的符号
	GsFillSymbol* FillSymbol();
	/// \brief 接幅表中间面填充符号,默认斜线填充
	/// \param pFillSymbol 设置填充的符号
	void FillSymbol(GsFillSymbol *pFillSymbol);
	/// \brief 接幅表边线绘制符号
	/// \return 返回边线符号
	GsLineSymbol* FrameLineSymbol();
	/// \brief 接幅表边线绘制符号
	/// \param pLineSymbol 边线符号
	void FrameLineSymbol(GsLineSymbol *pLineSymbol);
	/// \brief 接幅表文字绘制符号
	/// \return 返回文字符号
	GsTextSymbol* TextSymbol();
	/// \brief 接幅表文字绘制符号
	/// \param pTextSymbol 文字符号
	void TextSymbol(GsTextSymbol *pTextSymbol);
	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

protected:
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsJoinMapTableElement* pEle);
};
GS_SMARTER_PTR(GsJoinMapTableElement);
DECLARE_CLASS_CREATE(GsJoinMapTableElement);


/// \brief 坡度尺的类型
enum GsSlopeRulerType
{	
	eSlopeRulerTypeNone = 0,
	/// \brief 一种是绘相邻六条等高线时，从第五度开始绘制
	eSlopeRulerTypeFive ,

	/// \brief 另一种从第十度开始绘制，对应的描述信息的位置都会随着改变
	eSlopeRulerTypeTen,
};

/// \brief 坡度尺
class GS_API GsSlopeRulerElement :public GsGeometryElement
{
	/// \brief 尺子的横向分隔值
	double   m_dfIntervalGap;
	/// \brief 标题和尺之间的间隔距离
	double   m_dfTitleGap;
	/// \brief 标注和尺子之间的间隔距离
	double   m_dfLabelRulerGap;
	/// \brief 等高距
	double   m_dfContourDist;
	/// \brief 是否显示正切标注
	bool     m_bShowTanlabel;
	/// \brief 坡度尺的类型
	GsSlopeRulerType m_enumType;
	/// \brief 说明信息字体高度
	double   m_dRulerInfoHeight;
	/// \brief 标题文字高度
	double   m_dTitleNameHeight;
	/// \brief 标注文字高度
	double   m_dLabelTextHeight;

	/// \brief 绘制线的符号Symbol
	GsLineSymbolPtr m_ptrLineSym;

	/// \brief 绘制的起点
	GsRawPoint m_ptStar;

	/// \brief 外边框
	GsGeometryPtr m_ptrFrameGeometry;


	// 下面的参数为该类的临时成员变量
protected:
	/// \brief 绘制坡度尺的线的临时成员变量
	GsLinePtr   m_ptrLine;	
	/// \brief 绘制线的起点
	GsRawPoint m_ptFrom;
	/// \brief 绘制线的终点
	GsRawPoint m_ptTo;
	/// \brief 所有需要绘制的线的集合
	UTILITY_NAME::GsVector<GsGeometryPtr> m_vecDrawLineGeos;
	/// \brief 所有需要绘制的坡度符号的位置的集合 (如1° 30°）
	UTILITY_NAME::GsVector<GsGeometryPtr> m_vecSlopeGeos;
	/// \brief 所有坡度注释符号的位置（如 “量相邻两条等高线时用”文字位置）
	UTILITY_NAME::GsVector<GsGeometryPtr> m_vecSlopenoteGeos;
	/// \brief 所有需要绘制正切值标注的位置的集合
	UTILITY_NAME::GsVector<GsGeometryPtr> m_vecTanlabelGeos;
	/// \brief 标题的位置
	GsGeometryPtr m_ptrTitleGeo;	
	/// \brief 所有需要绘制文字的Element集合
	UTILITY_NAME::GsVector<GsElementPtr> m_vecTestElements;
	/// \brief 临时计算出的标题与底线之间的高度
	double m_dRulerHeigh;

public:
	GsSlopeRulerElement();
	/// \brief 坡度尺制图
	/// \param x 绘制的起始点xmin
	/// \param y 制图元素的起始点ymin
	GsSlopeRulerElement(double x, double y);
	~GsSlopeRulerElement();

	/// \brief 获取尺子的横向分隔值
	/// \return 获取横向分隔值
	double IntervalGap();
	/// \brief 设置尺子的横向分隔值
	/// \param dIntervalGap 横向分隔值
	void IntervalGap(double dIntervalGap);

	/// \brief 
	/// \return 
	double TitleGap();
	/// \brief 
	/// \param dTitleGap 
	void TitleGap(double dTitleGap);

	/// \brief 获取标注和尺子之间的间隔距离
	/// \return 返回标注和尺子之间的间隔距离
	double LabelRulerGap();
	/// \brief 设置标注和尺子之间的间隔距离
	/// \param dLabelRulerGap 设置的间隔
	void LabelRulerGap(double dLabelRulerGap);

	/// \brief 获取等高距
	/// \return 返回等高距
	double ContourDist();
	/// \brief 设置等高距
	/// \param dContourDist 等高距
	void ContourDist(double dContourDist);

	/// \brief 获取是否显示正切标注
	/// \return 返回是否显示正切标注
	bool ShowTanlabel();
	/// \brief 设置是否显示正切标注
	/// \param bShowTanlabel 设置是否显示正切标注
	void ShowTanlabel(bool bShowTanlabel);

	/// \brief 获取坡度尺的类型
	/// \return 返回坡度尺的类型
	GsSlopeRulerType SlopeRulerType();
	/// \brief 设置坡度尺的类型
	/// \param eType 坡度尺的类型
	void SlopeRulerType(GsSlopeRulerType eType);

	/// \brief 获取说明信息字体高度
	/// \return 返回说明信息字体高度
	double RulerInfoHeight();
	/// \brief 设置说明信息字体高度
	/// \param dRulerInfoHeight 说明信息字体高度
	void RulerInfoHeight(double dRulerInfoHeight);

	/// \brief 获取标题文字高度
	/// \return 返回标题文字高度
	double TitleNameHeight();
	/// \brief 设置标题文字高度
	/// \param dTitleNameHeight 标题文字高度 
	void  TitleNameHeight(double dTitleNameHeight);

	/// \brief 获取标注文字高度
	/// \return 返回标注文字高度
	double LabelTextHeight();
	/// \brief 设置标注文字高度
	/// \param dLabelTextHeight 标注文字高度
	void LabelTextHeight(double dLabelTextHeight);

	/// \brief 获取绘制线的符号
	/// \return 返回绘制线的符号
	GsLineSymbol* LineSymbol();
	/// \brief 设置绘制线的符号
	/// \param pLineSym 绘制线的符号
	void LineSymbol(GsLineSymbol* pLineSym);


	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;
protected:
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsSlopeRulerElement* pEle);

private:
	/// \brief 初始化需要绘制的数据
	void InitDrawData();
	/// \brief 初始化时计算绘相邻两条等高线时的位置信息
	void CaculateTowContourLines();
	/// \brief 初始化时计算绘相邻六条等高线时的位置信息
	void CaculateSixContourLines();
	/// \brief 根据设置的参数计算外框
	void CaculateFrameBox();
	/// \brief 拖动改变边框重新计算内部数据的尺寸长宽 
	void InitSlopeRulerFormatGap();

};
GS_SMARTER_PTR(GsSlopeRulerElement);
DECLARE_CLASS_CREATE(GsSlopeRulerElement);


/// \brief数据表格
class GS_API GsTableElement :public GsGeometryElement
{
public:
	GsTableElement();
};
GS_SMARTER_PTR(GsTableElement);


/// \brief TextElement中文字填充类型
enum GsTextTensile
{
	//TextElement中的文字如何填充传入的矩形框
	/// \brief 完全拉伸，宽高不变
	eFullTensile,
	/// \brief 以宽高的最小值作为文字大小
	eMinTensile,
	/// \brief 以宽作为文字大小
	eWidthTensile,
	/// \brief 以高作为文字大小
	eHeightTensile
};


/// \brief 锚点的位置
enum GsTextAnchors
{
	//用户传入的锚点位置为坐标点
	//如旋转，开始绘制等都以锚点为参考
	//*    *    *
	//*    *    *
	//*    *    *

	/// \brief 第一行左边点
	eTextTopLeft,
	/// \brief 第一行中间点
	eTextTopCenter,
	/// \brief 第一行右边点
	eTextTopRight,
	/// \brief 第二行左边点
	eTextCenterLeft,
	/// \brief 第二行中间点
	eTextCenterCenter,
	/// \brief 第二行右边点
	eTextCenterRight,
	/// \brief 第三行左边点
	eTextBottomLeft,
	/// \brief 第三行中间点
	eTextBottomCenter,
	/// \brief 第三行右边点
	eTextBottomRight
};

/// \brief 文本元素
class GS_API GsTextElement : public GsGeometryElement
{
	/// \brief 锚点位置
	GsTextAnchors m_TextAnchors;
	/// \brief 锚点坐标
	GsRawPoint m_TextAnchorsPoint;

	/// \brief 记录文本框在不旋转的时候的形状
	GsRingPtr m_TextRing;
	/// \brief 记录文本框旋转后的形状
	GsRingPtr m_TextAngleRing;

	/// \brief 记录文本框中的文本值
	Utility::GsString m_sText;
	/// \brief 记录外接轮廓的宽
	double m_Width;
	/// \brief 记录外接轮廓的高
	double m_Height;
	/// \brief 记录左上角点的坐标，绘制开始的位置
	GsPointPtr m_Point;
	/// \brief 记录文本框旋转角度
	double m_Angle;
public:
	GsTextElement();
	/// \brief 根据字符串来设置外接矩形的宽高，然后根据锚点来设置外接矩形的坐标值
	/// \param pX 文本制图绘制的起始点xmin
	/// \param pY 文本制图绘制的起始点ymin
	/// \param pStr 文本
	/// \param pTextAnchors 锚点类型
	GsTextElement(double pX, double pY, const char* pStr = "", GsTextAnchors pTextAnchors = eTextBottomLeft);
	/// \brief 根据文本符号来设置外接矩形的宽高，然后根据锚点来设置外接矩形的坐标值
	/// \param pX 文本制图绘制的起始点xmin
	/// \param pY 文本制图绘制的起始点ymin
	/// \param pText 文本符号
	/// \param pTextAnchors 锚点类型
	GsTextElement(double pX, double pY, GsTextSymbol* pText, GsTextAnchors pTextAnchors = eTextBottomLeft);
	~GsTextElement();

	/// \brief 获取文本符号
	/// \return 返回文本符号
	GsTextSymbolPtr TextSymbol();
	/// \brief 设置文本符号
	/// \param pTextSym 文本符号
	void TextSymbol(GsTextSymbol* pTextSym);

	/// \brief 获取锚点所在坐标
	/// \return 返回锚点坐标
	GsRawPoint TextAnchorsPoint();
	/// \brief 设置锚点坐标
	/// \param p 锚点坐标
	void TextAnchorsPoint(const GsRawPoint& p);
	/// \brief 设置锚点坐标
	/// \param p 锚点的坐标
	/// \param pTextAnchors 锚点的类型
	void TextAnchorsPoint(const GsRawPoint& p, GsTextAnchors pTextAnchors);

	/// \brief 获取锚点类型
	/// \return 返回锚点类型
	GsTextAnchors TextAnchors();
	/// \brief 设置锚点类型
	/// \param pTextAnchors 锚点类型
	void TextAnchors(GsTextAnchors pTextAnchors);

	/// \brief 获取文本框的宽
	/// \return 返回文本框的宽
	double Width();
	/// \brief 设置文本框的宽
	/// \param pWidth 文本框的宽度
	void Width(double pWidth);

	/// \brief 获取文本框的高
	/// \return 返回文本框的高度
	double Height();
	/// \brief 设置文本框的高
	/// \param pHeight 文本框的高度
	void Height(double pHeight);

	/// \brief 获取文本框旋转角度，单位为度
	/// \return 返回文本旋转的角度
	double Angle();
	/// \brief 设置文本框旋转角度，单位为度
	/// \param pAngle 角度
	void Angle(double pAngle);

	/// \brief 获取文本框的字符串
	/// \return 返回文本框的字符串
	Utility::GsString Text();
	/// \brief 设置文本框的字符串
	/// \param str 字符串
	void Text(const char* str);

	/// \brief 获取外接矩形框的轮廓
	/// \return 返回外接矩形框的轮廓
	GsBox Envelope();
	/// \brief 根据传入的字符串计算新的外接矩形
	/// \param strText 传入的字符串
	/// \return 返回计算后的外界矩形
	GsBox Envelope(const char* strText);

	/// \brief 设置文本制图的外接矩形框
	/// \param pBoxWidth 外接矩形框的宽度
	/// \param pBoxHeight 外接矩形框的高度
	/// \param pTextTensile	文本制图中的文字填充类型
	void Envelope(double pBoxWidth, double pBoxHeight, GsTextTensile pTextTensile);

	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

protected:
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsTextElement* pEle);

private:
	/// \brief 计算字符串的外接矩形
	/// \param pCanvas 画布
	/// \param pDisplayTrans 坐标转换对象
	/// \param pTextSym 文字符号
	/// \return 返回计算的结果
	Utility::GsSizeF MeasureString(GsCanvas* pCanvas, GsDisplayTransformation* pDisplayTrans, GsTextSymbol* pTextSym);

	/// \brief 根据传入的矩形和旋转角度，计算新的矩形坐标，同时得到左上角点的坐标
	/// \param pRing 未做任何旋转的矩形
	/// \param dAngle 旋转角度
	/// \return 返回记录旋转后的面
	GsRingPtr EnvelopeAngle(GsRing* pRing, double dAngle);

	/// \brief 根据传入的宽高，锚点位置，返回矩形的坐标
	/// \param dWidth 宽
	/// \param dHeight 高
	/// \param pRawPoint 锚点坐标
	/// \param pTextAnchors 锚点类型
	/// \return 返回计算的矩形
	GsBox EnvelopeTransform(double dWidth, double dHeight, const GsRawPoint& pRawPoint, GsTextAnchors pTextAnchors);

	/// \brief 设置文本符号，来设置外接矩形的宽高
	/// \param pTextSym 文本符号
	/// \return 是否设置成功
	bool SetTextSymbol(GsTextSymbol* pTextSym);
};
GS_SMARTER_PTR(GsTextElement);
DECLARE_CLASS_CREATE(GsTextElement);


/// \brief 格网,方里网格网显示风格
enum GsGridLineShowType
{
	/// \brief 显示格网线
	eShowLines,
	/// \brief 显示格网线交点十字
	eShowTicks,
	/// \brief 不显示内部格网线
	eShowNone,
};

/// \brief 格网,方里网四边显示相关信息(主刻度，分刻度，标注),控制四个方向是否显示
enum GsGridOrientation
{
	/// \brief 上部显示
	eGridTop = 1,
	/// \brief 下部显示
	eGridBottom = 2,
	/// \brief 左部显示
	eGridLeft = 4,
	/// \brief 右部显示
	eGridRight = 8,
};

/// \brief 格网,方里网文字显示方向 不论是水平还是垂直都是自西向东,自南向北排列字
enum GsGridLabelOrientation
{
	/// \brief 水平显示
	eHorizontal,
	/// \brief 垂直显示
	eVerticalLabel,
};
/// \brief 格网,方里网四边显示文字的样式
enum GsGridLabelStringFormat
{
	/// \brief 六十进制显示度分秒 100°12′12″ N 或100°12′12″ E
	eSexagesimal,
	/// \brief 十进制 显示 100.7889,尾部字体分割大小显示
	eDecimalDivisional,
	/// \brief 自定义,暂未实现
	eCustomDefine,
};

/// \brief 格网,分刻度位置
enum GsGridScalePosition
{
	/// \brief 显示在格网线内部
	eInside,
	/// \brief 显示在格网线外部
	eOutside,
};
/// \brief 格网,方里网
class GS_API GsGridElement :public GsGeometryElement
{
	/// \brief 记录外接框的大小。
	GsBox m_box;
	/// \brief 记录格网显示的最大范围，默认是经度-180到180 维度-90到90，如果是0则无限制
	GsBox m_boxRange;
	/// \brief 十字交叉的外接圆的半径。
	double m_dfCrossTickSize;
	/// \brief 格网显示风格
	GsGridLineShowType m_LineShowType;
	/// \brief 控制四个方向是否显示标注
	GsGridOrientation m_GridLabelAxes;
	/// \brief 文字显示方向
	GsGridLabelOrientation  m_LabelOrientation;
	/// \brief 	四边显示文字的样式
	GsGridLabelStringFormat m_LabelFormat;
	/// \brief 是否根据Map范围变化调整格网绘制原点,默认位false,如果为true,地图范围变化将根据地图范围动态改变原点
	bool m_FixedOrigin;
	/// \brief x方向间距间距经度纬度
	double m_XIntervalSize;
	/// \brief Y方向间距 间距经度纬度
	double m_YIntervalSize;
	/// \brief x方向间距  实际绘制间距
	double m_XIntervalDrawSize;
	/// \brief Y方向间距 实际绘制间距
	double m_YIntervalDrawSize;
	/// \brief X轴原点的经纬度
	double m_XOrigin;
	/// \brief Y轴原点的经纬度
	double m_YOrigin;
	/// \brief 绑定的Map对象
	GsMapPtr m_ptrMap;
	/// \brief 格网线的符号
	GsLineSymbolPtr m_ptrLineSymbol;
	/// \brief 外边框符号
	GsLineSymbolPtr m_ptrBorderSymbol;

	/// \brief 主刻度的长度
	double m_dfMainScaleLength;
	/// \brief 四边是否绘制主刻度
	GsGridOrientation m_OrientMainScaleLine;
	/// \brief 主刻度的位置，格网外还是格网内
	GsGridScalePosition m_PosMainScale;
	
	/// \brief 分刻度将主刻度切分的数量
	int m_nDivisionScaleCount;
	/// \brief 分刻度的长度
	double m_dfDivisionScaleLength;
	/// \brief 四边是否绘制分刻度
	GsGridOrientation m_OrientDivisionScaleLine;
	/// \brief 分刻度的位置，格网外还是格网内
	GsGridScalePosition m_PosDivisionScale;

	/// \brief 标注偏移
	double m_dfTextOffset;
	/// \brief 文字标注符号
	GsTextSymbolPtr m_ptrTextSymbol;
	/// \brief label分段显示符号
	GsTextSymbolPtr m_ptrDecimalDivisionalTextSymbol;

	/// \brief x,y原点(经纬度)对应的实际坐标的原点
	GsRawPoint m_pointOrigin;

protected:
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);

	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsGridElement* pEle);
public:
	GsGridElement();
	/// \brief 按照Map范围构造
	/// \param ptrMap 绑定一个GsMap
	/// \param box 格网的box(设置建议和map制图的范围一致)
	GsGridElement(GsMap* ptrMap, GsBox box);
	/// \brief 构造格网制图
	/// \param dblXOrigin x轴起始点(经纬度)
	/// \param dblYOrigin y轴起始点(经纬度)
	/// \param XIntervalSize x轴起间距(经纬度)
	/// \param YIntervalSize y轴起间距(经纬度)
	/// \param ptrMap 绑定一个GsMap
	/// \param box 格网的box(设置建议和map制图的范围一致)
	GsGridElement(double dblXOrigin, double dblYOrigin, double XIntervalSize, double YIntervalSize, GsMap* ptrMap, GsBox box);

	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();
	/// \brief 格网线的符号
	/// \return 返回格网的线符号
	GsLineSymbol* LineSymbol();
	/// \brief 外边框符号
	/// \return 返回外边框符号
	GsLineSymbol* BorderSymbol();
	/// \brief 文字标注符号
	/// \return 返回文字标注符号
	GsTextSymbol* TextSymbol();
	/// \brief label分段显示文字标注符号，也就是小数部分的符号
	/// \return 返回label分段显示文字标注符号
	GsTextSymbol* DecimalDivisionalTextSymbol();

	/// \brief 设置格网线的符号
	/// \param pLineSymbol 线符号
	void LineSymbol(GsLineSymbol* pLineSymbol);
	/// \brief 设置外边框符号
	/// \param pLineSymbol 线符号
	void BorderSymbol(GsLineSymbol* pLineSymbol);
	/// \brief 设置文字标注符号
	/// \param pTextSymBol 文字符号
	void TextSymbol(GsTextSymbol* pTextSymBol);
	/// \brief label分段显示的文字标注符号
	/// \param pTextSymbol 文字符号
	void DecimalDivisionalTextSymbol(GsTextSymbol* pTextSymbol);
	///// \brief label分段显示符号位置
	//int TextBreakPoint();

	/// \brief 设置格网显示风格
	/// \param eGridLineType 格网显示风格
	void GridLineShowType(GsGridLineShowType eGridLineType);
	/// \brief 获取格网显示风格
	/// \return 返回格网显示风格
	GsGridLineShowType GridLineShowType();
	/// \brief 设置四个方向是否显示标注
	/// \param eGridLabelAxes 
	void GridLabelAxes(GsGridOrientation eGridLabelAxes);
	/// \brief 获取四个方向是否显示标注
	/// \return 
	GsGridOrientation GridLabelAxes();
	/// \brief 设置文字显示方向
	/// \param eGridLabelAxes 方向
	void GridLabelOrientation(GsGridLabelOrientation eGridLabelAxes);
	/// \brief 获取文字显示方向
	/// \return 返回文字显示方向
	GsGridLabelOrientation GridLabelOrientation();
	/// \brief 设置文字的样式
	/// \param eGridLabelAxes 样式
	void GridLabelStringFormat(GsGridLabelStringFormat eGridLabelAxes);
	/// \brief 获取文字的样式
	/// \return 返回文字的样式 
	GsGridLabelStringFormat GridLabelStringFormat();

	/// \brief 设置是否根据Map范围变化调整格网绘制原点,默认位false,如果为true,地图范围变化将根据地图范围动态改变原点
	/// \param bFixedOrigin 设置是否需要改变原点
	void FixedOrigin(bool bFixedOrigin);
	/// \brief 获取是否根据Map范围变化调整格网绘制原点,默认位false,如果为true,地图范围变化将根据地图范围动态改变原点
	/// \return 返回是否需要改变原点
	bool FixedOrigin();

	/// \brief 设置绘制主刻度的位置
	/// \param ePos 主刻度的位置
	void MainScalePosition(GsGridScalePosition ePos);
	/// \brief 获取绘制主刻度的位置
	/// \return 返回绘制主刻度的位置
	GsGridScalePosition MainScalePosition();
	/// \brief 设置主刻度是否显示在四边
	/// \param eOri 方向
	void MainScaleOrientation(GsGridOrientation eOri);
	/// \brief 获取主刻度是否显示在四边
	/// \return 获取是否显示在四边的方向
	GsGridOrientation MainScaleOrientation();
	/// \brief 获取主刻度的长度
	/// \return 返回主刻度的长度
	double MainScaleLength();
	/// \brief 设置主刻度的长度
	/// \param len 主刻度的长度
	void MainScaleLength(double len);

	/// \brief 设置分刻度的位置，格网外还是格网内
	/// \param ePos 位置
	void DivisionScalePosition(GsGridScalePosition ePos);
	/// \brief 设置分刻度的位置，格网外还是格网内
	/// \return 返回位置
	GsGridScalePosition DivisionScalePosition();
	/// \brief 设置四边是否绘制分刻度
	/// \param eOri 方向
	void DivisionScaleOrientation(GsGridOrientation eOri);
	/// \brief 获取四边是否绘制分刻度
	/// \return 返回方向
	GsGridOrientation DivisionScaleOrientation();
	/// \brief 获取分刻度的长度
	/// \return 返回长度
	double DivisionScaleLength();
	/// \brief 设置分刻度的长度
	/// \param len 分刻度的长度
	void DivisionScaleLength(double len);
	/// \brief 获取分刻度将主刻度切分的数量
	/// \return 返回分刻度将主刻度切分的数量
	int DivisionScaleCount();
	/// \brief 设置分刻度将主刻度切分的数量
	/// \param count 分刻度将主刻度切分的数量
	void DivisionScaleCount(int count);

	/// \brief 获取x间距
	/// \return 返回x间距
	double XIntervalSize();
	/// \brief 设置x间距
	/// \param size x间距
	void XIntervalSize(double size);
	/// \brief 以度分秒的方式设置x间距
	/// \param degree 度
	/// \param minute 分
	/// \param second 秒
	void XIntervalSize(double degree, double minute, double second);
	/// \brief x原点
	/// \return 返回x原点
	double XOrigin();
	/// \brief 设置x原点
	/// \param origin x原点
	void XOrigin(double origin);

	/// \brief 获取Y间距
	/// \return 返回Y间距
	double YIntervalSize();
	/// \brief 设置Y间距
	/// \param size Y间距
	void YIntervalSize(double size);
	/// \brief 设置Y间距
	/// \param degree 度
	/// \param minute 分
	/// \param second 秒
	void YIntervalSize(double degree, double minute, double second);
	/// \brief 获取Y原点
	/// \return 返回Y原点
	double YOrigin();
	/// \brief 设置Y原点
	/// \param origin Y原点
	void YOrigin(double origin);
	/// \brief 记录格网显示的最大范围，默认是经度-180到180 维度-90到90，如果是0,0,0,0则无限制
	/// \return 返回格网显示的最大范围
	GsBox Range();
	/// \brief 记录格网显示的最大范围，默认是经度-180到180 维度-90到90，如果是0,0,0,0则无限制
	/// \param box 设置格网显示的最大范围
	void Range(GsBox box);

	/// \brief 获取格网中绑定的Map
	/// \return 返回绑定的map
	GsMap* Map();
	/// \brief 设置格网中绑定的Map
	/// \param map 需要绑定的map
	void Map(GsMap* map);

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

private:

	/// \brief 初始化Map相关
	/// \param map 绑定的地图
	void InitMap(GsMap* map);

	/// \brief 绘制边框线。
	/// \param pDisp 显示的目标设备
	/// \param box 绘制的边框线。
	void DrawFrameLine(GsDisplay* pDisp, const GsBox& box);

	/// \brief 绘制十字交叉
	/// \param pDisp 显示的目标设备
	/// \param point 中心点.
	/// \param size 中心点到外接框的边线的距离。
	/// \param pSym 绘制的符号
	void DrawCrossTicks(GsDisplay* pDisp, const GsRawPoint& point, double size, GsSymbol * pSym);

	/// \brief 绘制所有的十字形
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制过程中可以通过此参数取消绘制。
	/// \param boxRange 确保绘制的十字架在boxRange范围内。
	/// \param point 绘制的基准点。
	void DrawAllCrossTicks(GsDisplay * pDisp, GsTrackCancel * pCancel, const GsBox& boxRange, const GsRawPoint& point);

	/// \brief 初始化外接框对应的经纬度。
	/// \param rect 对应的设备范围
	/// \return 返回经纬度最大范围(-180, -90, 180, 90),对应图纸上面的坐标范围
	GsBox InitGridElement(const Utility::GsRect& rect);

	/// \brief 绘制格网中的刻度
	/// \param pDisp 显示的目标设备
	/// \param pointRef 基准点
	/// \param boxRange 最大范围
	void DrawGridAndScaleBar(GsDisplay* pDisp, const GsRawPoint& pointRef, const GsBox& boxRange);
	/// \brief 获取基准点
	/// \param box 格网的矩形
	/// \param outRefPoint 输出基准点纸张坐标
	/// \param outRefLanLongPoint 输出基准点的经纬度坐标
	void InitReferencePoint(const GsBox &box, GsRawPoint & outRefPoint, GsRawPoint & outRefLanLongPoint);

	/// \brief 经纬度转换，从double类型表示的经纬度，转换为标注显示的经纬度。
	/// \param db 需要转换的经纬度
	/// \param isNorthSourth 是否是南北方向。
	/// \param outStr1 返回的整数部分，如果eDecimalDivisional情况下。否则返回字符串
	/// \param outStr2 返回的小数部分，如果eDecimalDivisional情况下。否则返回""
	void TextLabelFromDouble(double db, bool isNorthSourth, Utility::GsString& outStr1, Utility::GsString& outStr2);

	/// \brief 绘制文字标注。
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	/// \param pointRef 基准点
	/// \param pointRefLanLong 基准点对应的经纬点。
	/// \param boxRange 格网的边框线的范围。
	void DrawGridTextLabel(GsDisplay* pDisp, GsTrackCancel * pCancel, GsDrawPhase drawType, const GsRawPoint& pointRef, const GsRawPoint& pointRefLanLong, const GsBox& boxRange);
};
GS_SMARTER_PTR(GsGridElement);
DECLARE_CLASS_CREATE(GsGridElement);

/// \brief 比例尺Division的位置
enum GsScaleBarDivisionsPosition
{
	/// \brief 刻度显示在横线符号的上部
	eScaleBarDivisionsUp,
	/// \brief 刻度显示在横线符号的中间。
	eScaleBarDivisionsMiddle,
	/// \brief 刻度显示在横线符号的下部。
	eScaleBarDivisionsDown,
};
enum GsScaleBarType
{
	/// \brief 比例尺底部线符号是单条线。
	eScaleBarSingleLine,
	/// \brief 比例尺底部线符号是双条线，黑白相间填充。
	eScaleBarDoubleLine,
};

/// \brief 比例尺
class GS_API GsScaleBarElement :public GsGeometryElement
{
	/// \brief 记录矩形的大小
	GsBox m_Box;
	/// \brief 比例尺文字符号
	GsTextSymbolPtr m_ptrTextSymbol;
	/// \brief 比例尺单位符号
	GsTextSymbolPtr m_ptrTextSymbolUnit;

	/// \brief 比例尺单位显示的文本
	Utility::GsString m_sUnit;
	/// \brief 比例尺单位类型
	GsUnits m_eUnit;

	/// \brief 单位左边的间隙
	double m_Gap;
	/// \brief 比例尺单位元素
	GsTextElementPtr m_TextElementUnit;
	/// \brief 底部线符号
	GsSymbolPtr m_BottomLineSymbol;
	/// \brief 上面的线符号
	GsSymbolPtr m_ScaleLineSymbol;

	/// \brief 竖直线的长度， Big 是比较长的竖直线。
	double m_dfBigBarHeight;
	/// \brief 竖直线的长度， Small 是比较短的竖直线。 
	double m_dfSmallBarHeight;

	/// \brief 级别数量
	int m_nLevel;
	/// \brief 单个级别被切分的数量
	int m_nDivisions;

	/// \brief 单个级别的实际绘制宽度
	double m_dfDivisionsValue;

	/// \brief 左端点的刻度。默认值为0,也可以设置小于0的刻度
	double m_dfMinScale;
	/// \brief 右端点的刻度。因为比例尺都是根据map计算出的。所以这个参数作为临时变量
	double m_dfMaxScale;

	/// \brief 记录比例尺的样式
	GsScaleBarDivisionsPosition m_ScaleBarDivisionsPosition;

	/// \brief 记录比例尺的样式，单条线还是双条线的样式。
	GsScaleBarType m_ScaleBarType;

	/// \brief 记录比例尺绑定的Map。
	GsMapPtr m_ptrMap;
	/// \brief 记录比例尺绑定的MapElement。
	GsMapElementPtr m_ptrMapElement;

public:
	GsScaleBarElement();

	/// \brief 通过MapElement构造比例尺制图，使用的比例尺也就是MapElement::RealScale()
	/// \param x 绘制的起始点xmin
	/// \param y 制图元素的起始点ymin
	/// \param pMapEle 绑定的地图元素制图
	GsScaleBarElement(double x, double y, GsMapElement* pMapEle = NULL);

	~GsScaleBarElement();

	/// \brief 获取比例尺线符号
	/// \return 返回比例尺线符号
	GsSymbolPtr ScaleLineSymbol();
	/// \brief 获取比例尺线符号
	/// \param symbol 比例尺线符号
	void ScaleLineSymbol(GsSymbol* symbol);

	/// \brief 获取底部线符号
	/// \return 返回底部线符号
	GsSymbolPtr BottomLineSymbol();
	/// \brief 获取底部线符号
	/// \param symbol 底部线符号
	void BottomLineSymbol(GsSymbol* symbol);

	/// \brief 获取级别数量
	/// \return 返回级别数量
	int Level();
	/// \brief 设置级别数量
	/// \param nLevel 级别数量
	void Level(int nLevel);

	/// \brief 获取单个级别被切分的数量
	/// \return 返回单个级别被切分的数量
	int Division();
	/// \brief 设置单个级别被切分的数量
	/// \param division 单个级别被切分的数量
	void Division(int division);

	/// \brief 设置比例尺的单位显示的文本
	/// \param unit 比例尺的单位文本
	void Unit(const char* unit);
	/// \brief 获取比例尺的单位文本
	/// \return 返回比例尺的单位文本
	Utility::GsString Unit();

	/// \brief 设置比例尺的单位 
	/// \param eUnit 比例尺的单位
	void UnitType(GsUnits eUnit);
	/// \brief 获取比例尺的单位
	/// \return 返回比例尺的单位
	GsUnits UnitType();

	/// \brief 设置比例尺绘制的长度(底部水平线的长度)
	/// \param len 比例尺绘制的长度
	void ScaleLength(double len);
	/// \brief 获取比例尺绘制的长度(底部水平线的长度)
	/// \return 返回比例尺绘制的长度
	double ScaleLength();

	/// \brief 设置比例尺中最小刻度
	/// \param minScale 最小刻度
	void MinScale(double minScale);
	/// \brief 获取比例尺中最小刻度
	/// \return 返回最小刻度
	double MinScale();

	/// \brief 获取单位左边的间隙
	/// \return 返回间隙
	double Gap();
	/// \brief 设置单位左边的间隙
	/// \param gap 间隙
	void Gap(double gap);

	/// \brief 获取绑定的MapElement
	/// \return 返回绑定的地图元素制图
	GsMapElementPtr MapElement();
	/// \brief 设置绑定的MapElement
	/// \param map 绑定的MapElement
	void MapElement(GsMapElement* map);

	/// \brief 设置显示的刻度文字符号
	/// \param ptrTextSym 刻度文字符号
	void TextSymbol(GsTextSymbol* ptrTextSym);	
	/// \brief 获取显示的刻度文字符号
	/// \return 返回刻度文字符号
	GsTextSymbolPtr TextSymbol();

	/// \brief 设置单位的文字符号
	/// \param ptrTextSym 单位的文字符号
	void TextSymbolUnit(GsTextSymbol* ptrTextSym);
	/// \brief 获取单位的文字符号
	/// \return 返回单位的文字符号
	GsTextSymbolPtr TextSymbolUnit();

	/// \brief 设置比例尺bar的位置类型
	/// \param type 比例尺bar的位置类型
	void ScaleBarDivisionsPosition(GsScaleBarDivisionsPosition type);
	/// \brief 获取比例尺bar的位置
	/// \return 返回比例尺bar的位置类型
	GsScaleBarDivisionsPosition ScaleBarDivisionsPosition();

	/// \brief 设置比例尺的类型
	/// \param type 比例尺的类型
	void ScaleBarType(GsScaleBarType type);
	/// \brief 获取比例尺的类型
	/// \return 返回比例尺的类型
	GsScaleBarType ScaleBarType();

	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

protected:
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsScaleBarElement* pEle);

private:
	
	/// \brief 绘制黑白的方块。
	/// \param pDisp 显示的目标设备
	/// \param box 绘制的黑白方块的大小。
	/// \param color 绘制的黑白方块的填充颜色。
	void DrawDoubleLineFillColor(GsDisplay* pDisp, const GsBox& box, Utility::GsColor color);

	/// \brief 绘制线段
	/// \param pDisp 显示的目标设备
	/// \param point1 起始点
	/// \param point2 终点
	/// \param pSymbol 绘制线段的符号
	void DrawLine(GsDisplay* pDisp, const GsRawPoint& point1, const GsRawPoint& point2, GsSymbol* pSymbol = NULL);
	/// \brief 初始化比例尺制图属性
	/// \param x 绘制的起始点xmin
	/// \param y 制图元素的起始点ymin
	void InitScaleElementBox(double x, double y);
	/// \brief 初始化比例尺制图的比例
	void InitScale();
};
GS_SMARTER_PTR(GsScaleBarElement);
DECLARE_CLASS_CREATE(GsScaleBarElement);

/// \brief 三北方向
class GS_API GsThreeNorthElement :public GsGeometryElement
{
	/// \brief 记录矩形的大小
	GsBox m_Box;

	double m_dfLineLength;//三个北线的长度
	double m_dfAsteriskSize;//五角星大小
	double m_dfArrowSize;//箭头大小
	double m_dfGraphAngle;//倾斜度数,单位度
	double m_dfMagnetAngle;//磁偏角
	double m_dfMeridianAngle;//子午线收敛角
	double m_dfArcFirstSpace;//第一个拱形(下面那个拱形，一个箭头)的半径。以pointBottomCenter为圆心
	double m_dfArcSecondSpace;//第二个拱形(上面那个拱形，二个箭头)的半径。以pointBottomCenter为圆心
	/// \brief 拱形虚线符号
	GsCartographicLineSymbolPtr m_pArcDottedLine;
	/// \brief 三个子午线的线符号。
	GsLineSymbolPtr m_pLineSym;
	/// \brief 三个子午线的标注符号。
	GsTextSymbolPtr m_pTextNameSym;
	/// \brief 三个子午线的角度标注符号。
	GsTextSymbolPtr m_pTextAngleSym;

public:
	GsThreeNorthElement();
	/// \brief 三北方向制图
	/// \param x 绘制的起始点xmin
	/// \param y 制图元素的起始点ymin
	GsThreeNorthElement(double x, double y);
	~GsThreeNorthElement();

	/// \brief 设置三个子午线的线符号。
	/// \param pSym 线符号
	void LineSymbol(GsSymbol * pSym);
	/// \brief 获取三个子午线的线符号。
	/// \return 返回线符号
	GsSymbolPtr LineSymbol();

	/// \brief 设置三个子午线的线段长度，单位mm
	/// \param dfLength 设置线段的长度
	void LineLength(double dfLength);
	/// \brief 获取三个子午线的线段长度，单位mm
	/// \return 返回线段的长度
	double LineLength();

	/// \brief 设置磁偏角。(标注显示的角度值)
	/// \param dfAngle 磁偏角
	void MagnetAngle(double dfAngle);
	/// \brief 获取磁偏角
	/// \return 返回磁偏角
	double MagnetAngle();
	
	/// \brief 设置子午线收敛角。(标注显示的角度值)
	/// \param dfAngle 子午线收敛角
	void MeridianAngle(double dfAngle);
	/// \brief 获取子午线收敛角
	/// \return 返回子午线收敛角
	double MeridianAngle();
	
	/// \brief 绘制三北方向时的夹角。(因为三北方向线在绘制时的夹角是示意图，并不是实际的角度值),设置磁子午线和真子午线绘图的夹角，同时设置坐标纵线和真子午线绘图的夹角，两个夹角相等。
	/// \param dfAngle 实际夹角
	void GraphAngle(double dfAngle);
	/// \brief 获取三北方向时的夹角,获取磁子午线和真子午线绘图的夹角。
	/// \return 返回实际夹角
	double GraphAngle();

	/// \brief 设置五角星外接圆的半径。
	/// \param dfSize 五角星的大小
	void AsteriskSize(double dfSize);
	/// \brief 获取五角星外接圆的半径。
	/// \return 返回五角星的大小
	double AsteriskSize();

	/// \brief 设置箭头的长度
	/// \param dfSize 箭头的长度
	void ArrowSize(double dfSize);
	/// \brief 获取箭头的长度
	/// \return 返回箭头的长度
	double ArrowSize();

	/// \brief 设置拱形虚线符号。
	/// \param pSym 虚线的符号
	void ArcDottedLine(GsCartographicLineSymbol * pSym);
	/// \brief 获取拱形虚线符号。
	/// \return 返回虚线符号。
	GsCartographicLineSymbolPtr ArcDottedLine();

	/// \brief 设置名称标注的符号。
	/// \param pSym 文本符号
	void NameLabelSymbol(GsTextSymbol * pSym);
	/// \brief 获取名称标注的符号。
	/// \return 返回标注的符号。
	GsTextSymbolPtr NameLabelSymbol();

	/// \brief 设置角度标注的符号。
	/// \param pSym 角度标注的符号。
	void AngleLabelSymbol(GsTextSymbol * pSym);
	/// \brief 获取角度标注的符号。
	/// \return 返回角度标注的符号。
	GsTextSymbolPtr AngleLabelSymbol();

	/// \brief 设置大小
	/// \param sizef 三北方向制图的大小
	virtual void Size(const Utility::GsSizeF & sizef);
	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

protected:
	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsThreeNorthElement* pEle);

private:
	/// \brief 绘制线段
	/// \param pDisp 显示的目标设备
	/// \param point1 起始点
	/// \param point2 终点
	/// \param pSymbol 绘制线段的符号
	void DrawLine(GsDisplay* pDisp, const GsRawPoint& point1, const GsRawPoint& point2, GsSymbol* pSymbol = NULL);

	/// \brief 绘制拱形虚线
	/// \param pointFrom 起始点
	/// \param pointMiddle 中间点
	/// \param pointEnd 结束点
	/// \param pDisp 显示的目标设备
	void DrawArcDottedLine(GsDisplay* pDisp, const GsRawPoint& pointFrom, const GsRawPoint& pointMiddle, const GsRawPoint& pointEnd);

	/// \brief 绘制箭头
	/// \param point 基准点
	/// \param dfAngle 偏转角
	/// \param length 箭头的长度
	/// \param pDisp 显示的目标设备
	void DrawArrow(GsDisplay* pDisp, const GsRawPoint& point, double dfAngle, double length);

	/// \brief 绘制五角星
	/// \param point 五角星的中心点
	/// \param length 五角星的中心点到顶点的最远距离
	/// \param pDisp 显示的目标设备
	void DrawAsterisk(GsDisplay* pDisp, const GsRawPoint& point, double length);

	/// \brief 初始化m_box
	/// \param x 起始点xmin
	/// \param y 制图元素的起始点ymin
	void InitBox(double x, double y);

	/// \brief 根据m_box来初始化几个Point
	/// \param pointLeftTop;//磁子午线左上点。
	/// \param pointRightTop;//坐标纵线右上点。
	/// \param pointBottomCenter; //三北线底部交叉点，真子午线最低点。
	/// \param pointTopCenter; //真子午线最高点,五角星所在的位置。
	void InitBasicPoint(GsRawPoint& pointLeftTop, GsRawPoint& pointRightTop, GsRawPoint& pointBottomCenter, GsRawPoint& pointTopCenter);
	

	/// \brief 根据box的变化初始化一些基本属性。
	/// \param box 旧的box大小
	/// \param oldBox 新的box大小
	void InitBasicProperty(const GsBox& box, const GsBox& oldBox);

	/// \brief 属性按照一定的倍数缩放
	/// \param scale 比例
	void ScaleProperty(double scale);

};
GS_SMARTER_PTR(GsThreeNorthElement);
DECLARE_CLASS_CREATE(GsThreeNorthElement);


/// \brief GsLegend为整个图例的对象,内包含所有绑定地图的图例信息和对象
/// \details GsLegendFormat为GsLegend样式信息描述
class GS_API GsLegendsFormat :public Utility::GsRefObject
{
private:
	/// \brief legendgroup直接的垂直距离
	double m_dGroupGap;
	/// \brief 标题和图例之间的垂直距离
	double m_dHeadingGap;
	/// \brief 图例的水平距离，用于不止1列的图例
	double m_dHorizontalItemGap;
	/// \brief 图例画的符号与文字之间的水平距离
	double m_dHorizontalPatchGap;
	/// \brief 层名称与图示图形之间的垂直距离
	double m_dLayerNameGap;
	/// \brief 标题是否是显示
	bool m_bShowTitle;
	/// \brief 图层名字是否显示
	bool m_bShowLayerName;
	/// \brief 是否显示allOtherValues名字
	bool m_bShowAllOtherValues;
	/// \brief 字段名字是否显示
	bool m_bShowFieldName;

	/// \brief 标签和描述之间的水平距离。labels and descriptions.
	double m_dTextGap;
	/// \brief 标题和第一个GsLegendGroup之间的垂直距离。
	double m_dTitleGap;
	/// \brief 标题的位置
	GsRectanglePosition m_eRectanglePosition;
	/// \brief 标题文本所使用的文字符号
	GsTextSymbolPtr m_ptrTitleSymbol;
	/// \brief 图例中每个Item所使用的文字符号
	GsTextSymbolPtr m_ptrItemTextSymbol;
	/// \brief 图例中layerName所使用的文字符号
	GsTextSymbolPtr m_ptrLayerNameTextSymbol;
	/// \brief GsLegendGroup之间的垂直距离
	double m_dVerticalItemGap;
	/// \brief 图块之间的垂直距离。LegendClass之间的距离
	double m_dVerticalPatchGap;
	/// \brief 图块的高度
	double m_dDefaultPatchHeight;
	/// \brief 图块的宽度
	double m_dDefaultPatchWidth;	
	/// \brief 单列图例的宽度
	double m_dRowWidth;
	/// \brief 图层名高度
	double m_dDefaultLayerHeight;
	/// \brief 图层名宽度
	double m_dDefoultLayerWidth;
	/// \brief 标题宽度和高度
	double m_dDefoultHeadingWidth;
	double m_dDefoultHeadingHeight;

public:
	GsLegendsFormat();
	~GsLegendsFormat();
	/// \brief legendgroup之间的距离
	/// \return 
	double GroupGap();
	/// \brief 
	/// \param dblGap 
	void  GroupGap(double dblGap);
	/// \brief 标题和图例之间的垂直距离
	/// \return 
	double HeadingGap();
	/// \brief 
	/// \param dblGap 
	void  HeadingGap(double dblGap);
	/// \brief 图例的水平距离，用于不止1列的图例
	/// \return 
	double HorizontalItemGap();
	/// \brief 
	/// \param dblGap 
	void  HorizontalItemGap(double dblGap);
	/// \brief 图例画的符号与文字之间的水平距离
	/// \return 
	double HorizontalPatchGap();
	/// \brief 
	/// \param dblGap 
	void  HorizontalPatchGap(double dblGap);

	/// \brief 层名称与图示图形之间的垂直距离
	/// \return 
	double LayerNameGap();
	/// \brief 
	/// \param dblGap 
	void  LayerNameGap(double dblGap);
	/// \brief 标题是否是显示
	/// \return 
	bool ShowTitle();
	/// \brief 
	/// \param bShowTitle 
	void  ShowTitle(bool bShowTitle);
	/// \brief 图层名字是否显示
	/// \return 
	bool ShowLayerName();
	/// \brief 
	/// \param bShowLayerName 
	void ShowLayerName(bool bShowLayerName);
	/// \brief 是否显示allOtherValues名字
	/// \return 
	bool ShowAllOtherValues();
	/// \brief 
	/// \param bShowAllOtherValues 
	void ShowAllOtherValues(bool bShowAllOtherValues);
	/// \brief 字段名字是否显示
	/// \return 
	bool ShowFieldName();
	/// \brief 
	/// \param bShowFieldName 
	void ShowFieldName(bool bShowFieldName);
	/// \brief 标签和描述之间的水平距离。labels and descriptions.
	/// \return 
	double TextGap();
	/// \brief 
	/// \param dblGap 
	void  TextGap(double dblGap);

	/// \brief 标题和第一个GsLegendGroup之间的垂直距离。
	/// \return 
	double TitleGap();
	/// \brief 
	/// \param dblGap 
	void  TitleGap(double dblGap);
	/// \brief 标题的位置
	/// \return 
	GsRectanglePosition TitlePosition();
	/// \brief 
	/// \param eType 
	void TitlePosition(GsRectanglePosition eType);
	/// \brief 标题文本所使用的文字符号
	/// \return 
	GsTextSymbolPtr TitleSymbol();
	/// \brief 
	/// \param pSym 
	void TitleSymbol(GsTextSymbol* pSym);

	/// \brief 每个Item所使用的文字符号
	/// \return 
	GsTextSymbolPtr ItemTextSymbol();
	/// \brief 
	/// \param pSym 
	void ItemTextSymbol(GsTextSymbol* pSym);

	/// \brief LayerName和其他小标题所使用的文字符号
	/// \return 
	GsTextSymbolPtr LayerNameTextSymbol();
	/// \brief 
	/// \param pSym 
	void LayerNameTextSymbol(GsTextSymbol* pSym);

	/// \brief GsLegendGroup之间的垂直距离
	/// \return 
	double VerticalItemGap();
	/// \brief 
	/// \param dblGap 
	void  VerticalItemGap(double dblGap);
	/// \brief 图块之间的垂直距离。LegendClass之间的距离
	/// \return 
	double VerticalPatchGap();
	/// \brief 
	/// \param dblGap 
	void  VerticalPatchGap(double dblGap);

	/// \brief 图块的高度
	/// \return 
	double DefaultPatchHeight();
	/// \brief 
	/// \param dHeight 
	void DefaultPatchHeight(double dHeight);
	/// \brief 图块的宽度
	/// \return 
	double DefaultPatchWidth();
	/// \brief 
	/// \param dWidth 
	void DefaultPatchWidth(double dWidth);
	/// \brief 图层高度
	void DefaultLayerHeight(double dHeight);
	double DefaultLayerHeight();
	/// \brief 图层宽度
	void DefaultLayerWidth(double dWidth);
	double DefaultLayerWidth();
	/// \brief 标题宽度和高度
	void DefaultHeadingWidth(double dWidth);
	double DefaultHeadingWidth();
	void DefaultHeadingHeight(double dHeight);
	double DefaultHeadingHeight();
	/// \brief 单列图例的宽度
	/// \return 
	double RowWidth();
	/// \brief 
	/// \param dRowWidth 
	void RowWidth(double dRowWidth);
	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsLegendsFormat> Clone();
};
GS_SMARTER_PTR(GsLegendsFormat);

/// \brief 图例
/// \brief GsLegend为整个图例的对象,内包含所有绑定地图的图例信息和对象
class GS_API GsLegendsElement :public GsGeometryElement  
{
	Utility::GsVector<GsLegendGroupPtr > m_lstLegendGroup;
	/// \brief 当新的层添加到映射时是否应添加新项
	bool m_bAutoAdd;
	/// \brief 图例项是否应保持与图层相同的顺序
	bool m_bAutoReorder;
	/// \brief 表明如果items should be shown只有当相关层是可见的。
	bool m_bAutoVisibility;
	/// \brief 保留以备将来使用。
	bool m_bFlowRight;
	/// \brief 样式信息描述
	GsLegendsFormatPtr m_ptrLegendsFormat;
	/// \brief 题图map
	GsMapPtr m_ptrMap;
	/// \brief 图例标题
	Utility::GsString m_strTitle;
	/// \brief 图例标题高度
	double m_dTitleHeight;
	/// \brief 图例标题宽度
	double m_dTitleWidth;
	/// \brief 画图例的起始点位置
	GsRawPoint m_ptRawPoint;
	/// \brief 外框图廓
	GsGeometryPtr m_ptrBorderGeometry; 
	/// \brief 图廓符号
	GsSymbolPtr m_ptrBorderSymbol; 	

	/// \brief 边距暂不对外开接口
	/// \brief 上边距
	double m_dUpDistance;
	/// \brief 下边距
	double m_dDownDistance;
	/// \brief 左边距
	double m_dLeftDistance;
	/// \brief 右边距
	double m_dRightDistance;

	/// \brief 图例所有的element
	Utility::GsVector<GsElementPtr> m_vecElements;

	//临时对象，序列化读取记录的的LegendGroup一些信息，在InnerDraw后进行更新
	Utility::GsStlMap<Utility::GsString, GsLegendGroupPtr> m_stlMapLegendGroups;
	//只在序列化第一次调用InnerDraw有用，值为true，其他时候都为false
	bool m_bFirstDeSerialize;

public:
 	GsLegendsElement();
	/// \brief 
	/// \param x 绘制的起始点xmin
	/// \param y 制图元素的起始点ymin
	/// \param pMap 
	GsLegendsElement(double x,double y,GsMap* pMap);
	~GsLegendsElement();

	/// \brief 获取GsLegendGroup的集合
	/// \return 
	Utility::GsVector<GsLegendGroupPtr >* ListLegendGroup();

	/// \brief 获取GsLegendFormat为GsLegend样式描述
	/// \return 
	GsLegendsFormat* Format();
	/// \brief 
	/// \param pFormat 
	void Format(GsLegendsFormat* pFormat);

	/// \brief 获取Map
	/// \return 
	GsMap* Map();
	/// \brief 
	/// \param pMap 
	void Map(GsMap *pMap);

	/// \brief 图例的标题
	/// \return 
	Utility::GsString Title();
	/// \brief 
	/// \param strTitle 
	void Title(const char * strTitle);

	/// \brief 设置标题高度
	/// \param dHeight 
	void TitleHeight(double dHeight);
	/// \brief 得到标题高度
	/// \return 
	double TitleHeight();

	/// \brief 
	/// \param pDisplay 显示的目标设备
	/// \param pTrackCancel 
	/// \param pBounds 
	void Draw(GsDisplay*pDisplay, GsTrackCancel *pTrackCancel, GsEnvelope*pBounds);

	/// \brief 刷新
	void Refresh();

	/// \brief 制图的绘制，实现这个制图的内容的绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay * pDisp, GsTrackCancel * pCancel, GsDrawPhase drawType) override;

	/// \brief 设置图廓符号
	/// \param pSym 
	void BorderSymbol(GsSymbol* pSym);
	/// \brief 获取图廓符号
	/// \return 
	GsSymbol* BorderSymbol();

	/// \brief 当新的层添加是否应添加新项,同时图例与图层顺序相同
	/// \return 
	bool AutoAdd();
	/// \brief 
	/// \param pAutoAdd 
	void AutoAdd(bool pAutoAdd);

	/// \brief 对自身制图元素进行克隆，返回一个新的制图对象。
	/// \return 返回克隆后的制图对象。
	virtual Utility::GsSmarterPtr<GsElement> Clone();

	/// \brief 转换为组合元素的集合
	/// \return 
	GsElementPtr ConvertToGraphics();

	/// \brief 序列化，将自身属性序列化为xml
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;



protected:

	/// \brief 图例项是否应保持与图层相同的顺序
	/// \return 
	bool AutoReorder();
	/// \brief 
	/// \param pAutoReorder 
	void AutoReorder(bool pAutoReorder);

	/// \brief 表明如果items should be shown只有当相关层是可见的。
	/// \return 
	bool AutoVisibility();
	/// \brief 
	/// \param pAutoVisibility 
	void AutoVisibility(bool pAutoVisibility);
	
	/// \brief 保留以备将来使用。
	/// \return 
	bool FlowRight();
	/// \brief 
	/// \param pFlowRight 
	void FlowRight(bool pFlowRight);

	/// \brief 图例的显示范围
	/// \param pDisplay 显示的目标设备
	/// \param pTrackCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param pBounds 
	void QueryBounds(GsDisplay*pDisplay, GsTrackCancel *pTrackCancel, GsEnvelope*pBounds);


	/// \brief 根据m_pLegendGroup初始化绘制信息
	void InitElements();
	/// \brief 计算移动缩放后的各个尺寸及间距
	void InitLegendsFormatGap();
	/// \brief 初始化布局
	void InitLayout();
	/// \brief 对单个GsLegendGroup布局，ptPoint为布局起点
	/// \param pPoint 
	/// \param pLegendGroup 
	/// \param pBoxFrame 
	void InitLegendGroupLayout(GsRawPoint* pPoint, GsLegendGroup* pLegendGroup, GsBox* pBoxFrame, double dHeightStart, double dHeighEnd);
	/// \brief 拷贝自身属性到pEle
	/// \param pEle 目标制图对象：克隆属性到目标制图对象
	virtual void Assign(GsLegendsElement* pEle);
	/// \brief 根据layer增加m_lstLegendGroup,增加处理GsMultiLayer的情况
	/// \param pLayer 
	void AddLegendGroupByLayer(GsLayer* pLayer);

	/// \brief 序列化和反序列化m_lstLegendGroup
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确序列化
	bool SerializeLegendGroup(UTILITY_NAME::GsSerializeStream * pSerStream);
	
	/// \brief 反序列化，将xml中数据解析到自身属性
	/// \param pSerStream 序列化流。
	/// \return 返回是否正确反序列化
	bool DeSerializeLegendGroup(UTILITY_NAME::GsSerializeStream * pSerStream);
	
	/// \brief 
	void MatchAssignLegendGroups();
};
GS_SMARTER_PTR(GsLegendsElement);
DECLARE_CLASS_CREATE(GsLegendsElement);

/// \brief 制图页面的漫游Tracker
class GS_API GsZoomPanLayoutTracker : public GsZoomPanClassicTracker
{
public:
	/// \brief 制图页面的漫游Tracker
	/// \param view 制图元素视图
	GsZoomPanLayoutTracker(GsActiveView* view);
	~GsZoomPanLayoutTracker();
};

/// \brief 制图中地图的漫游Tracker
class GS_API GsZoomPanLayoutMapelementTracker :public GsSymbolTracker
{
	bool m_bMoved;
	unsigned long long m_TickWheel;
	GsMapElementPtr m_ptrMapEle;
	GsRawPoint m_First, m_Second;
	UTILITY_NAME::GsPT m_ptFirst, m_ptSecond;
	bool m_bStarPan;
	UTILITY_NAME::GsSimpleBitmapPtr m_ptrImageFull;//记录整个制图的图片
	UTILITY_NAME::GsSimpleBitmapPtr m_ptrImageMapOnly;//记录仅仅包含地图制图的图片，用来平移。
	UTILITY_NAME::GsSimpleBitmapPtr m_ptrImageBackColor;//纯色图片，颜色是制图的背景色

	/// \brief 绘制mapElement的偏移
	/// \param pDisp 绘制的设备
	void DrawMapElement(GsDisplay* pDisp);

public:
	/// \brief 制图中地图的漫游Tracker
	/// \param view 
	/// \param pEle 需要漫游的地图制图
	GsZoomPanLayoutMapelementTracker(GsActiveView* view,GsMapElement* pEle);

	/// \brief 接收鼠标按下消息
	/// \param eButton 鼠标按键类型
	/// \param nKeyboard 键盘按键对应的ASCII码
	/// \param pt 鼠标点击位置
	virtual void OnMouseDown(GsButton eButton, int nKeyboard, const UTILITY_NAME::GsPT& pt);
	/// \brief 接收鼠标弹起消息
	/// \param eButton 鼠标按键类型
	/// \param nKeyboard 键盘按键对应的ASCII码
	/// \param pt 鼠标点击位置
	virtual void OnMouseUp(GsButton eButton, int nKeyboard, const UTILITY_NAME::GsPT& pt);
	/// \brief 接收鼠标移动消息
	/// \param eButton 鼠标按键类型
	/// \param nKeyboard 键盘按键对应的ASCII码
	/// \param pt 鼠标点击位置
	virtual void OnMouseMove(GsButton eButton, int nKeyboard, const UTILITY_NAME::GsPT& pt);
	/// \brief 接收鼠标滚轮消息
	/// \param eButton 鼠标按键类型
	/// \param nDelta 滚轮系数
	/// \param nKeyboard 键盘按键对应的ASCII码
	/// \param pt 鼠标点击位置
	virtual void OnMouseWheel(GsButton eButton, int nDelta, int nKeyboard, const UTILITY_NAME::GsPT& pt);
	
public:
	/// \brief 范围变化
	/// \details 参数1 
	UTILITY_NAME::GsDelegate<void(const GsBox&)> OnExtentChanged;

protected:
	/// \brief tracker绘制函数，子类通过覆盖此函数绘制内容。
	/// \param pDisp 显示的目标设备
	virtual void OnTrackerDraw(GsDisplay* pDisp);
};
/// \brief GsZoomPanLayoutMapelementTrackerPtr
GS_SMARTER_PTR(GsZoomPanLayoutMapelementTracker);



KERNEL_ENDNS
