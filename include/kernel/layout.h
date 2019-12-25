#pragma once
#include "../utility/preconfig.h"
#include "layoutelement.h"

KERNEL_NS 



/// \brief 编辑回馈框架对象类型
enum GsFeedbackItemType
{
	/// \brief 普通可以编辑修改的回馈手柄
	eEditableHandle,

	/// \brief 用户修改旋转属性的回馈手柄
	eEditableRotateHandle,

	/// \brief 描绘编辑边界的边框线
	eFrameLine,

	/// \brief 用于延长显示的边框线
	eExtendFrameLine,

	/// \brief 可以编辑修改的功能性回馈手柄
	eEditableFunctionHandle,
};
/// \brief 编辑回馈框架对象的功能
enum GsFeedbackFunction
{
	/// \brief 无特定功能，仅用于渲染
	eNoneFunction,

	/// \brief 仿射变换左上移动功能
	eLeftTopMove,

	/// \brief 仿射变换左下移动功能
	eLeftBottomMove,

	/// \brief 仿射变换左中移动功能
	eLeftCenterMove,

	/// \brief 仿射变换中上移动功能
	eCenterTopMove,

	/// \brief 仿射变换中下移动功能
	eCenterBottomMove,

	/// \brief 仿射变换右上移动功能
	eRightTopMove,

	/// \brief 仿射变换右上移动功能
	eRightBottomMove,

	/// \brief 仿射变换右中移动功能
	eRightCenterMove,

	/// \brief 旋转对象的功能
	eRotateItem = 100,

	/// \brief 元素自定义的节点, 由各个element自行处理,
	eElementCustomization,
};
/// \brief 编辑回馈对象
struct  GsFeedbackItem
{
	
	/// \brief 编辑回馈对象
	/// \param t 编辑回馈框架对象类型
	/// \param geo 绘制的几何数据
	/// \param f 对象功能
	/// \param tol 命中容差
	GsFeedbackItem(GsFeedbackItemType t, GsGeometry* geo, GsFeedbackFunction f, double tol)
	{
		Type = t;
		Geometry = geo;
		Function = f;
		HittestTolerance = tol;
	}
	/// \brief 回馈对象的类型
	GsFeedbackItemType		Type;
	/// \brief 绘制的几何数据
	GsGeometryPtr			Geometry;
	
	/// \brief 对象功能
	GsFeedbackFunction		Function;

	/// \brief 命中容差
	double					HittestTolerance;

};
/// \brief 元素枚举器
class GS_API GsEnumElement :public Utility::GsRefObject
{

protected:
	/// \brief 元素枚举器
	GsEnumElement() {}
public:
	virtual ~GsEnumElement() {}

	/// \brief 重置枚举
	virtual void Reset() = 0;
	/// \brief 获取下一个元素
	/// \return 获取的下一个元素
	virtual GsElementPtr Next() = 0;
};
/// \brief GsEnumElementPtr
GS_SMARTER_PTR(GsEnumElement);

/// \brief 过滤特定类型元素的枚举器
template<class T>
class GsTypeFilterEnumElement :public GsEnumElement
{
	GsEnumElementPtr m_ptrBase;
public:
	/// \brief 过滤特定类型元素的枚举器
	/// \param pBase 元素枚举器
	GsTypeFilterEnumElement(GsEnumElement* pBase) : m_ptrBase(pBase) { }
	/// \brief 重置枚举
	virtual void Reset()
	{
		m_ptrBase->Reset();
	}
	/// \brief 获取下一个元素
	/// \return 返回下一个元素
	virtual GsElementPtr Next()
	{
		GsElementPtr ptrEle = m_ptrBase->Next();
		if (!ptrEle)
			return 0;
		
		T* pFilter = dynamic_cast<T*>(ptrEle.p);
		while (!pFilter)
		{
			ptrEle = m_ptrBase->Next();
			if (!ptrEle)
				return 0;

			pFilter = dynamic_cast<T*>(ptrEle.p);
		}

		return ptrEle;
	}
};
/// \brief 元素编辑回馈框架
class GS_API GsElementEditFeedback :public Utility::GsRefObject
{
	UTILITY_NAME::GsStlMap<GsFeedbackItemType, GsSymbolPtr> m_ItemSymbols;
protected:
	GsEnumElementPtr m_ptrEnumEle;
	//当前操作矩阵,基于开始的box
	GsMatrixD m_Matrix;
	GsBox m_BeginBox;

	UTILITY_NAME::GsVector<GsFeedbackItem> m_FeedBackItems;
	GsElementEditFeedback();
	/// \brief 开始绘制
	virtual void BeginDraw();
	/// \brief 完成绘制
	void FinishDraw();
public:
	virtual ~GsElementEditFeedback();

	/// \brief 根据变换的矩阵，调整每一项的Geometry.
	/// \param matrix 变换的矩阵
	/// \return 返回调整后的大小
	virtual GsBox UpdateMatrixFeedBackItems(const GsMatrixD & matrix);
	/// \brief 绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	virtual void Draw(GsDisplay* pDisp, GsTrackCancel* pCancel);

	/// \brief 获取特定对象类型的渲染符号	
	/// \param eType 编辑回馈框架对象类型
	/// \return 渲染符号
	GsSymbol* ItemSymbol(GsFeedbackItemType eType);

	/// \brief 设置特定对象类型的渲染符号
	/// \param eType 编辑回馈框架对象类型
	/// \param sym 渲染的符号
	void ItemSymbol(GsFeedbackItemType eType, GsSymbol* sym);
};
/// \brief GsElementEditFeedbackPtr
GS_SMARTER_PTR(GsElementEditFeedback);

/// \brief 进行仿射变换编辑的回馈框架
class GS_API GsAffineElementEditFeedback :public GsElementEditFeedback
{

	GsEnvelopePtr m_ptrTmpEnv;
	volatile bool m_bStart, m_bMouseMove;
	GsRawPoint m_First, m_Second;
	/// \brief 屏幕
	GsActiveViewPtr m_ptrView;
	/// \brief 当前选中的节点
	GsFeedbackItem * m_HitFeedBackItem;
	/// \brief 中间贴移动变换的兼容性位图
	GsImageCanvasPtr m_ptrFeedBackCanvas;
	/// \brief 选中的element是否随外界边框一起变化
	bool m_bElementbeAffine;
	/// \brief 
	/// \param point 
	/// \param tol 
	/// \return 
	bool HitFeedBackItem(const GsRawPoint & point, double tol= 0);
	/// \brief 计算八点拖拽缩放矩阵参数
	/// \param box 
	/// \param fun 
	/// \param p1 
	/// \param p2 
	/// \param m 
	/// \return 
	bool CalcScale(const GsBox& box, GsFeedbackFunction fun, const GsRawPoint &p1, const GsRawPoint& p2,  GsMatrixD& m);
	/// \brief 
	/// \param pt 
	void FireFaceBackEdit(const GeoStar::Utility::GsPT & pt);

	/// \brief 
	/// \param pEnumEle 
	/// \param pDT 
	/// \return 
	GeoStar::Utility::GsImage* FeedBackMoveImage(GsEnumElement* pEnumEle, GsDisplayTransformation* pDT);
public:
	GsAffineElementEditFeedback();
	/// \brief 进行仿射变换编辑的回馈框架
	/// \param ptrView 视图
	/// \param ElementbeAffine 选中的element是否随外界边框一起变化
	GsAffineElementEditFeedback(GsActiveView* ptrView,bool ElementbeAffine = true);
	~GsAffineElementEditFeedback();
	/// \brief 绑定编辑的元素
	/// \param pEle 元素枚举器
	void BindElement(GsEnumElement* pEle);
	/// \brief 获取元素枚举器
	/// \return 元素枚举器
	GsEnumElement* EnumElement();
	/// \brief 鼠标移动到选中的element上的事件,通知上层鼠标移动到了哪里 
	/// \details 参数1 
	Utility::GsDelegate<void(GsFeedbackItem*) >OnAffineElementFeedback;

	/// \brief 重置
	virtual void Reset();
	/// \brief 分离
	virtual void Detach();
	/// \brief 接收鼠标按下消息
	/// \param eButton 鼠标按键类型
	/// \param nKeyboard 键盘按键对应的ASCII码
	/// \param pt 鼠标点击位置
	virtual void OnMouseDown(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	/// \brief 接收鼠标弹起消息
	/// \param eButton 鼠标按键类型
	/// \param nKeyboard 键盘按键对应的ASCII码
	/// \param pt 鼠标点击位置
	virtual void OnMouseUp(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	/// \brief 接收鼠标移动消息
	/// \param eButton 鼠标按键类型
	/// \param nKeyboard 键盘按键对应的ASCII码
	/// \param pt 鼠标点击位置
	virtual void OnMouseMove(GsButton eButton, int nKeyboard, const Utility::GsPT& pt);
	/// \brief 
	/// \param pDisplay 显示的目标设备
	virtual void OnFeedbackDraw(GsDisplay* pDisplay);
};
/// \brief GsAffineElementEditFeedbackPtr
GS_SMARTER_PTR(GsAffineElementEditFeedback);


/// \brief 元素容器
class GS_API GsElementContainer :public Utility::GsRefObject
{
	Utility::GsList<GsElementPtr> m_vecElements;
public:
	GsElementContainer();
	virtual ~GsElementContainer();

	/// \brief 元素数量
	/// \return 元素数量
	int Count() const;

	/// \brief 元素数量
	void Clear();

	/// \brief 增加元素
	/// \param pEle 制图元素
	void Add(GsElement* pEle);

	/// \brief 获取相应索引位置的制图元素
	/// \param nIndex 索引
	/// \return 返回制图元素
	GsElement* At(int nIndex);

	/// \brief 插入制图元素
	/// \param pEle 制图元素
	/// \param i 索引
	/// \return 是否插入成功
	bool Insert(GsElement* pEle, int i);

	/// \brief 移除元素
	/// \param pEle 制图元素
	/// \return 移除的元素
	GsElementPtr Remove(GsElement* pEle);

	/// \brief 移除元素
	/// \param i 索引
	/// \return 移除的元素
	GsElementPtr Remove(int i);

	/// \brief 获取元素在容器中的索引，-1表示元素不在容器中
	/// \param ele 制图元素
	/// \return 返回制图元素对应的索引
	int IndexOf(GsElement* ele);

	/// \brief 下移元素
	/// \param ele 制图元素
	/// \return 移动后的索引
	int MoveDown(GsElement* ele);

	/// \brief 上移元素
	/// \param ele 制图元素
	/// \return 移动后的索引
	int MoveUp(GsElement* ele);

	/// \brief 移动元素到最顶层
	/// \param ele 制图元素
	/// \return 移动后的索引
	int MoveTop(GsElement* ele);

	/// \brief 移动元素到最底层
	/// \param ele 制图元素
	/// \return 移动后的索引，也就是0
	int MoveBottom(GsElement* ele);

	/// \brief 枚举所有的元素,每次都会新创建一个EnumElement
	/// \return 
	GsEnumElementPtr EnumElement();

	/// \brief 交换容器内的两个元素的位置，如果两个元素都存在，则交换返回true
	/// \param pEle1 制图元素1
	/// \param pEle2 制图元素2
	/// \return 返回是否交换成功
	bool Swap(GsElement* pEle1, GsElement* pEle2);

	/// \brief将容器内的pEle1替换为pEle2，如果不存在则返回false。
	/// \param pEleOld 制图元素old
	/// \param pEleNew 制图元素new
	/// \return 返回是否替换成功
	bool Replace(GsElement * pEleOld, GsElement * pEleNew);

	/// \brief 枚举特定类型的的元素。
	template<class T>
	/// \brief 
	/// \return 
	GsEnumElementPtr TypeFilterElement()
	{
		return new GsTypeFilterEnumElement<T>(EnumElement());
	}
};
/// \brief GsElementContainerPtr
GS_SMARTER_PTR(GsElementContainer);


/// \brief 复合元素
class GS_API GsMultiElement:public GsElement, public UTILITY_NAME::GsSerialize
{
	GsElementContainerPtr m_ptrContainer;
public:
	GsMultiElement();
	~GsMultiElement();
	
	/// \brief 获取所有元素
	/// \return 所有元素的容器
	GsElementContainer* Elements();
	/// \brief 设置仿射变换的矩阵
	/// \param mx 矩阵
	virtual void Transform(const GsMatrixD& mx);
	/// \brief 对制图元素进行克隆
	/// \return 返回复合元素的克隆后的对象指针
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
	virtual UTILITY_NAME::GsString ClassName();

	/// \brief 几何对象
	/// \return 返回获取到的制图中的集合对象
	virtual GsGeometry* Geometry();


protected:

	/// \brief 绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);
};
/// \brief GsMultiElementPtr
GS_SMARTER_PTR(GsMultiElement);
DECLARE_CLASS_CREATE(GsMultiElement);



/// \brief 纸张类型
/// \details https://en.wikipedia.org/wiki/Paper_size#Loose_sizes
enum GsPageType
{
	/// \brief North American paper sizes 216 × 279mm
	ePageLetter = 1,
	/// \brief North American paper sizes 216 × 356mm
	ePageLegal = 2,
	/// \brief North American paper sizes 279 × 432mm
	ePageTabloid = 3,
	/// \brief ANSI C 432 × 559mm
	ePageC = 4,
	/// \brief ANSI D 559 × 864mm
	ePageD = 5,
	/// \brief ANSI E 864 × 1118mm
	ePageE = 6,
	/// \brief ISO paper sizes, A series 148 × 210mm
	ePageA5 = 7,
	/// \brief ISO paper sizes, A series 210 × 297mm
	ePageA4 = 8,
	/// \brief ISO paper sizes, A series 297 × 420mm
	ePageA3 = 9,
	/// \brief ISO paper sizes, A series 420 × 594mm
	ePageA2 = 10,
	/// \brief ISO paper sizes, A series 594 × 841mm
	ePageA1 = 11,
	/// \brief ISO paper sizes, A series 841 × 1189mm
	ePageA0 = 12,


	/// \brief ISO paper sizes, A series 105 × 148mm
	ePageA6,
	/// \brief ISO paper sizes, A series 74 × 105mm
	ePageA7,
	/// \brief ISO paper sizes, A series 52 × 74mm
	ePageA8,
	/// \brief ISO paper sizes, A series 37 × 52mm
	ePageA9,
	/// \brief ISO paper sizes, A series 26 × 37mm
	ePageA10,

	/// \brief ISO paper sizes, B series 1000 × 1414mm
	ePageB0,
	/// \brief ISO paper sizes, B series 707 × 1000mm
	ePageB1,
	/// \brief ISO paper sizes, B series 500 × 707	mm
	ePageB2,
	/// \brief ISO paper sizes, B series 353 × 500mm
	ePageB3,
	/// \brief ISO paper sizes, B series 250 × 353	mm
	ePageB4,
	/// \brief ISO paper sizes, B series 176 × 250	mm
	ePageB5,
	/// \brief ISO paper sizes, B series 125 × 176	mm
	ePageB6,
	/// \brief ISO paper sizes, B series 88 × 125	mm
	ePageB7,
	/// \brief ISO paper sizes, B series 62 × 88	mm
	ePageB8,
	/// \brief ISO paper sizes, B series 44 × 62mm
	ePageB9,
	/// \brief ISO paper sizes, B series 31 × 44	mm
	ePageB10, 

	/// \brief ISO paper sizes, C series 917 × 1297mm
	ePageC0,
	/// \brief ISO paper sizes, C series 648 × 917mm
	ePageC1,
	/// \brief ISO paper sizes, C series 458 × 648mm
	ePageC2,
	/// \brief ISO paper sizes, C series 324 × 458	mm
	ePageC3,
	/// \brief ISO paper sizes, C series 229 × 324mm
	ePageC4,
	/// \brief ISO paper sizes, C series 162 × 229	mm
	ePageC5,
	/// \brief ISO paper sizes, C series 114 × 162	mm
	ePageC6,
	/// \brief ISO paper sizes, C series 81 × 114mm
	ePageC7,
	/// \brief ISO paper sizes, C series 57 × 81mm
	ePageC8,
	/// \brief ISO paper sizes, C series 40 × 57mm
	ePageC9,
	/// \brief ISO paper sizes, C series 28 × 40mm
	ePageC10,

	ePageCustom=1000,
};

/// \brief 记录纸张的横向，纵向
enum GsPageDirection
{
	/// \brief 横向
	ePageHorizontal,

	/// \brief 纵向
	ePageVertical,
};

/// \brief 页面元素
class GS_API GsPage :public GsElement
{
	GsPageDirection m_papeDirection;
	GsPageType m_eType;
	Utility::GsSizeF m_PageSize;
	GsFillSymbolPtr m_PageSymbol;
	GsFillSymbolPtr m_ShadowSymbol;
	UTILITY_NAME::GsRect	m_PageRect;//纸张在显示设备中的大小。
	
	/// \brief 根据大小创建页面元素
	/// \param s 纸张大小
	void CreatePage(const Utility::GsSizeF& s);

public:
	/// \brief 页面元素
	/// \param eType 纸张类型
	GsPage(GsPageType eType = ePageA4);
	~GsPage();
	
	/// \brief 根据纸张类型获取纸张大小
	/// \details https://en.wikipedia.org/wiki/Paper_size#Loose_sizes
	/// \param e 纸张类型
	/// \return 返回纸张类型对应的纸张大小
	static Utility::GsSizeF PageSize(GsPageType e);

	/// \brief 获取纸张大小
	/// \return 返回纸张大小
	Utility::GsSizeF PageSize();
	/// \brief 设置自定义的纸张大小，如果设置此参数，必须要设置纸张类型为定制类型
	/// \param s 自定义的纸张大小，
	void PageSize(const Utility::GsSizeF& s);
	/// \brief 获取纸张类型
	/// \return 纸张类型
	GsPageType PageType();
	/// \brief 设置纸张类型
	/// \param type 纸张类型
	void PageType(GsPageType type);

	/// \brief 获取纸张方向
	/// \return 纸张方向
	GsPageDirection PageDirection();
	/// \brief 设置纸张方向
	/// \param direct 纸张方向
	void PageDirection(GsPageDirection direct);

	/// \brief 获取纸张在设备中的大小
	/// \return 纸张在设备中的大小
	UTILITY_NAME::GsRect PageRect();
	
protected:
	/// \brief 绘制
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param drawType 绘制的阶段
	virtual void InnerDraw(GsDisplay* pDisp, GsTrackCancel* pCancel, GsDrawPhase drawType);

};
/// \brief GsPagePtr
GS_SMARTER_PTR(GsPage);


/// \brief 选择元素的类型
enum GsSelectElementType
{
	/// \brief 选择结果形成新选择集
	eNewSelection,
	/// \brief 选择结果并入原选择集
	eUnionSelection,
	/// \brief 选择结果和原选择集亦或
	eXorSelection,
};

enum GsSelectElementLocatType
{
	/// \brief 选择所有
	eAllLocatSelection,
	/// \brief 选择最上层
	eTopLocatSelection,
	/// \brief 选择最底层
	eBottomLocatSelection,
	
};


/// \brief 制图对象
class GS_API GsPageLayout:public GsActiveView,Utility::GsWorkThread
{ 
	GsPagePtr m_ptrPage; 
	GsAffineElementEditFeedbackPtr m_ptrEditFeedback;
	GsMultiElementPtr m_ptrAssistElement;
	GsMultiElementPtr m_ptrMainElement;
	GsMultiElementPtr m_ptrSelectionSet;
	GsMultiElementPtr m_ptrLocatSelectionSet;
	bool m_bValid;
	double m_dReferenceScale;
	/// \brief 执行线程，实现此纯虚函数
	/// \return 返回执行是否成功
	virtual bool Execute();
public:
	GsPageLayout();
	/// \brief 制图对象
	/// \param pDisplay 显示的目标设备
	GsPageLayout(GsScreenDisplay* pDisplay);
	~GsPageLayout();

	/// \brief 元素容器
	/// \return 返回元素对象集合
	GsElementContainer* ElementContainer();

	/// \brief 辅助元素容器
	/// \details 辅助元素如标尺、格网等辅助制图用途的元素
	/// \details 辅助元素绘制与所有制图元素之上
	/// \return 返回辅助元素对象集合
	GsElementContainer* AssistElementContainer();

	/// \brief 存放选中元素的容器
	/// \return 返回选中元素对象集合
	GsElementContainer* SelectionSet();

	/// \brief 清空选择
	void ClearSelection();

	/// \brief 点选择
	/// \param pt 点
	/// \param eType 选择元素的类型
	/// \param tol 容差
	/// \param eSelectLocatType 选择方式的类型
	/// \return 返回选择的对象集合
	GsElementContainer* SelectElement(const GsRawPoint& pt, GsSelectElementType eType,double tol, GsSelectElementLocatType eSelectLocatType = eAllLocatSelection);
	/// \brief 矩形选择
	/// \param box 
	/// \param eType 选择元素的类型
	/// \param eSelectLocatType 选择方式的类型
	/// \return 返回选择的对象集合
	GsElementContainer* SelectElement(const GsBox& box, GsSelectElementType eType, GsSelectElementLocatType eSelectLocatType = eAllLocatSelection);
	/// \brief 任意几何对象选择
	/// \param geo 几何数据
	/// \param eType 选择元素的类型
	/// \param eSelectLocatType 选择方式的类型
	/// \return 返回选择的对象集合
	GsElementContainer* SelectElement(GsGeometry* geo, GsSelectElementType eType, GsSelectElementLocatType eSelectLocatType = eAllLocatSelection);
	
	/// \brief 编辑回馈对象
	/// \return 编辑回馈对象
	GsElementEditFeedback *EditFeedback();


	/// \brief 获取纸张对象
	/// \return 纸张对象
	GsPage* Page();

	/// \brief 取消绘制
	void Cancel();
	/// \brief 刷新
	virtual void Update();

	/// \brief 输出
	/// \param pDisp 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \return 出图是否成功
	virtual bool Output(GsDisplay* pDisp, GsTrackCancel* pCancel);

	/// \brief 是否在绘制
	/// \return 是否在绘制
	bool IsDrawing();


	/// \brief 绘制地图
	/// \details 如果地图数据未失效，则直接绘制缓冲的位图，反之则重新绘制
	/// \param eReason 绘制的阶段
	virtual void Paint(GsDrawPhase eReason = eDrawNormal);

	/// \brief 使地图失效
	virtual void Invalidate();

	/// \brief 判断是否已经失效
	/// \return 是否已经失效
	virtual bool IsValid();

	 
	/// \brief 全图范围
	/// \details 所有图层的范围合并的范围
	/// \return 全图的范围
	virtual GsBox FullExtent();

	/// \brief 设置当前显示范围
	/// \details 会取消当前地图绘制，同时使得地图失效，但不会立刻刷新地图，需要额外调用Paint或者Update刷新地图
	/// \param extent 显示的范围
	virtual void ViewExtent(const GsBox& extent);

	/// \brief 获取当前显示范围
	/// \details 相当于调用方法Display()->DisplayTransformation()->MapExtent();
	/// \return 显示的范围
	virtual GsBox ViewExtent();

	/// \brief 获取参考比例尺
	/// \param dScale 参考比例尺 
	void ReferenceScale(double dScale);
	/// \brief 设置参考比例尺 
	/// \return 参考比例尺 
	double ReferenceScale();

protected:
	/// \brief 根据选择的位置得到选择集
	/// \param geo 几何数据
	/// \param eSelectLocatType 选择元素的类型
	/// \return 选择的元素集合
	GsElementContainer* SelectLocatElement(GsGeometry* geo, GsSelectElementLocatType eSelectLocatType = eAllLocatSelection);
};
/// \brief GsPageLayoutPtr
GS_SMARTER_PTR(GsPageLayout);

/// \brief 制图元素解析类
class GS_API GsLayoutParser
{
	Utility::GsString m_strFile;
	GsPageLayoutPtr m_ptrMap;
public:
	GsLayoutParser();
	~GsLayoutParser();

	/// \brief 解析制图模板为制图元素
	/// \param strFilePath 文件路径
	/// \param pLayout 解析后的制图元素
	/// \return 解析是否成功
	bool Read(const char* strFilePath, GsPageLayout* pLayout);

	/// \brief 保存到文件
	/// \param pLayout 需要保存的制图对象
	/// \param strFilePath 保存的文件路径
	/// \return 返回是否保存成功
	bool Save(GsPageLayout* pLayout, const char* strFilePath);
};
/// \brief Element对象需要在map中绘制 使用此封装对象
class GS_API GsGraphicElementLayer : public GsLayer
{
	GsMultiElementPtr m_ptrElementS;
public:
	GsGraphicElementLayer();
	~GsGraphicElementLayer();
	/// \brief 增加元素
	/// \param ele 制图元素
	void Add(GsElement* ele);
	/// \brief 获取元素
	/// \param i 索引
	/// \return 相应位置的元素
	GsElement* At(int i);
	/// \brief 元素数量
	/// \return 元素数量
	int Count();
	/// \brief 移除元素
	/// \param ele 制图元素
	void Remove(GsElement * ele);
	/// \brief 移除元素
	/// \param i 索引
	void Remove(int i);
	/// \brief 移除所有元素
	void Clear();
	/// \brief 移动元素
	/// \param ele 制图元素
	/// \param i 索引
	void MoveTo(GsElement* ele, int i);
	/// \brief 对Layer进行克隆
	/// \return 返回克隆后的对象
	virtual Utility::GsSmarterPtr<GsLayer> Clone();
	/// \brief 元素集合
	/// \return 返回元素的集合
	GsMultiElement* Elements();
	/// \brief 获取目标空间参考对应的范围
	/// \param pTargetSR 目标空间参考
	/// \return 返回范围
	virtual GsBox Extent(GsSpatialReference * pTargetSR = 0) override;
	/// \brief 选择集
	/// \return 是否包含选择集
	virtual bool HasSelection() override;


	/// \brief 特定过滤条件下，将图层中的geometry和symbol 转换为element，然后添加到自身容器中。
	/// \param pfeaLayer 图层
	/// \param pQueryFilter 属性过滤条件
	/// \return 成功大于等于0 ,失败小于0
	virtual int AddFeatureLayer(GsFeatureLayer * pfeaLayer, GsQueryFilter* pQueryFilter = NULL);
protected:	
	/// \brief 内部绘制入口
	/// \details 子类通过覆盖此函数实现绘制。
	/// \param pDisplay 显示的目标设备
	/// \param pCancel 绘制取消对象，如需绘制的时候中断，需要修改此参数
	/// \param eDrawPhase 绘制的阶段
	/// \return 返回是否绘制成功
	virtual bool InnerDraw(GsDisplay* pDisplay, GsTrackCancel* pCancel, GsDrawPhase eDrawPhase);

	/// \brief 转换简单渲染符号的Feature为element
	/// \param pSimpleRender 简单地物渲染器
	/// \param ptrCur 地物游标
	/// \return 成功大于等于0 ,失败小于0
	int ConvertSimpleRender(GsSimpleFeatureRenderer* pSimpleRender, GsFeatureCursor* ptrCur);
	/// \brief 转换唯一值渲染符号的Feature为element
	/// \param pUniqueRender 质底填充渲染器
	/// \param ptrCur 地物游标
	/// \return 成功大于等于0 ,失败小于0
	int ConvertUniqueValueRenderer(GsUniqueValueRenderer* pUniqueRender, GsFeatureCursor* ptrCur);
	/// \brief 转换分级符号渲染的Feature为element
	/// \param pGraduRender 分级渲染器
	/// \param ptrCur 地物游标
	/// \return 成功大于等于0 ,失败小于0
	int ConvertGraduatedRenderer(GsGraduatedRenderer* pGraduRender, GsFeatureCursor* ptrCur);
};
/// \brief GsGraphicElementLayerPtr
GS_SMARTER_PTR(GsGraphicElementLayer);

KERNEL_ENDNS
