#pragma once
#include "canvas.h" 
#include "pointsymbol.h"
KERNEL_NS    



/// \brief 简单线符号
class GS_API GsSimpleLineSymbol:public GsLineSymbol
{
	GsPenPtr m_ptrPen;
	GsPenStyle m_eLineStyle;

	/// \brief 符号端套类型
	GsLineCapStyle     m_CapStyle;    
	/// \brief 线段接头类型
	GsLineJoinStyle    m_JoinStyle;    
	/// \brief 线端斜面接合限值属性
	double    m_dblMiterLimit;	 
protected: 
	/// \brief 绘制Canvas的path
	/// \param pPath 
	/// \param pBlob 
	virtual void OnDraw(GsGraphicsPath* pPath,GsGeometryBlob * pBlob);

	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
public:
	GsSimpleLineSymbol();
	/// \brief 从颜色和线宽构造
	/// \param color 
	/// \param dblWidth 
	GsSimpleLineSymbol(const Utility::GsColor& color,double dblWidth = 0.1);
	virtual ~GsSimpleLineSymbol(); 
	/// \brief 获取端套类型
	GsLineCapStyle	CapStyle();
	/// \brief 设置端套类型
	/// \param Style 
	void CapStyle(GsLineCapStyle Style);

	/// \brief 获取接头类型
	/// \return 
	GsLineJoinStyle JoinStyle();
	/// \brief 设置接头类型
	/// \param Style 
	void JoinStyle(GsLineJoinStyle Style);

	/// \brief 获取制图线的线端斜面接合限值
	/// \return 
	double MiterLimit();
	/// \brief 设置制图线的线端斜面接合限值
	/// \param Limit 
	void MiterLimit(double Limit);

	/// \brief 获取线的类型
	/// \return 
	GsPenStyle LineStyle();
	/// \brief 设置线的类型
	/// \param eStyle 
	void LineStyle(GsPenStyle eStyle);
	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();
	/// \brief 绘制画布坐标系下的几何对象
	/// \param pGeo 
	/// \param pBuffer 
	/// \return 
	virtual bool DrawGraphics(GsGraphicsGeometry* pGeo, GsGeometryBlob* pBuffer);
};
GS_SMARTER_PTR(GsSimpleLineSymbol);
DECLARE_CLASS_CREATE(GsSimpleLineSymbol);

/// \brief 简单线符号
class GS_API GsLineDecorationStrategy :public Utility::GsRefObject
{
protected:
	/// \brief 是否按照点个数等比例设置点的位置
	bool m_PositionAsRatio; 
	/// \brief 点的位置
	Utility::GsVector<double> m_Positions;

public:
	virtual ~GsLineDecorationStrategy() {}

	/// \brief 设置是否按照点个数等比例设置点的位置
	/// \param pPositionAsRatio 
	virtual void PositionAsRatio(bool pPositionAsRatio);
	/// \brief 获取是否按照点个数等比例设置点的位置属性
	/// \return 
	virtual bool PositionAsRatio();

	/// \brief 获取点的个数
	/// \return 
	virtual int PositionCount();
	/// \brief 增加点
	/// \param elementPosition 
	virtual void AddPosition(double elementPosition);

	/// \brief 根据索引获取点的位置
	/// \param index 
	/// \return 
	virtual double GetPosition(int index) ;
	/// \brief 根据索引删除点的位置
	/// \param index 
	virtual void DeletePosition(int index);
	/// \brief 重置
	virtual void Reset();

};
/// \brief GsLineDecorationStrategyPtr
GS_SMARTER_PTR(GsLineDecorationStrategy);

/// \brief 简单线装饰元素
class GS_API GsSimpleLineDecorationStrategy :public GsLineDecorationStrategy
{
public:
	/// \brief 
	GsSimpleLineDecorationStrategy() {}

	/// \brief 根据装饰点及点个数构造
	/// \param pPointSymbol 
	/// \param pPositionCount 
	GsSimpleLineDecorationStrategy(GsPointSymbol *pPointSymbol, int pPositionCount);
	virtual ~GsSimpleLineDecorationStrategy();

	/// \brief 设置首节点翻转属性
	/// \param pFlipFirst 
	void FlipFirst(bool pFlipFirst);
	/// \brief 获取首节点翻转属性
	/// \return 
	bool FlipFirst();

	/// \brief 设置全部翻转属性
	/// \param pFlipAll 
	void FlipAll(bool pFlipAll);
	/// \brief 获取全部翻转属性
	/// \return 
	bool FlipAll();

	/// \brief 设置旋转属性
	/// \param pRotate 
	void Rotate(bool pRotate);
	/// \brief 获取旋转属性
	/// \return 
	bool Rotate();

	/// \brief 设置装饰点
	/// \param pPointSymbol 
	void PointSymbol(GsPointSymbol* pPointSymbol);
	/// \brief 获取装饰点
	/// \return 
	GsPointSymbol* PointSymbol();

	/// \brief 重置
	void Reset();

private:

	/// \brief 是否翻转首节点
	bool m_FlipFirst;  

	/// \brief 是否全部翻转
	bool m_FlipAll;     
	/// \brief 是否旋转
	bool m_Rotate;      
	/// \brief 点符号
	GsPointSymbolPtr m_ptrPointSymbol;  
};

/// \brief GsSimpleLineDecorationStrategyPtr
GS_SMARTER_PTR(GsSimpleLineDecorationStrategy);

/// \brief 线装饰
class GS_API GsLineDecoration:public Utility::GsRefObject
{
protected:

	/// \brief 根据点的个数等间隔内插点
	/// \param pBlob 
	/// \param PointCount 
	void LineToPoint(GsGeometryBlob *pBlob,int PointCount);   
	/// \brief 根据当前长度求线参数
	/// \param l 
	/// \param lengthes 
	/// \return 
	double LineParam(double l,const Utility::GsVector<double>& lengthes);

	/// \brief 内插点
	Utility::GsVector<GsRawPoint> m_Points;

	/// \brief 装饰策略
	Utility::GsVector<GsLineDecorationStrategyPtr> m_LineDecorationStratics;

public:

	GsLineDecoration();
	virtual ~GsLineDecoration();

	/// \brief 装饰策略种类
	/// \return 
	int StrategyCount();

	/// \brief 添加装饰策略
	/// \param lineDecorationStrategy 
	void AddStrategy(GsLineDecorationStrategy* lineDecorationStrategy);
	 

	/// \brief 根据索引删除装饰策略
	/// \param index 
	void DeleteStrategy(int index);

	/// \brief 获取装饰策略对象
	/// \param i 
	/// \return 
	GsLineDecorationStrategy* Strategy(int i);

	/// \brief 重置
	void Reset();

	/// \brief 装饰绘制
	/// \param Canvas 
	/// \param DT 
	/// \param pBlob 
	virtual void DrawDecoration(GsCanvas* Canvas, GsDisplayTransformation* DT, GsGeometryBlob *pBlob);

};
/// \brief GsLineDecorationPtr
GS_SMARTER_PTR(GsLineDecoration);

/// \brief 线模板元素
struct GS_API GsPattern
{
	GsPattern()
	{
		fMark	= 0;
		fGap	= 0;
	}
	/// \brief 
	/// \param mark 
	/// \param gap 
	GsPattern(int mark, int gap)
	{
		fMark	= mark;
		fGap	= gap;
	}
	/// \brief 
	int fMark;
	/// \brief 
	int fGap;
};

/// \brief 线模板
class GS_API GsSymbolTemplate:public Utility::GsVector<GsPattern>
{
	/// \brief 线头方向的偏移量
	float m_fOffset;
	float m_fInterval;
public:
	/// \brief 构造函数  
	GsSymbolTemplate(); 
	/// \brief 
	/// \param offset 
	/// \param interval 
	GsSymbolTemplate(float offset,float interval);
	/// \brief 
	/// \param rhs 
	GsSymbolTemplate(const GsSymbolTemplate& rhs);
	/// \brief 析构函数
	virtual ~GsSymbolTemplate();
	 
	/// \brief 获得线的偏移量
	/// \return 
	float Offset();
	/// \brief 设置线的偏移量
	/// \param offset 
	void Offset(float offset); 

	/// \brief 获得线的倍率
	/// \return 
	float Interval();
	/// \brief 设置线的倍率
	/// \param interval 
	void Interval(float interval); 

	/// \brief 加入一个线模板
	/// \param pattern 
	void Add(const GsPattern& pattern); 
	/// \brief 加入一个线模板
	/// \param mark 
	/// \param gap 
	void Add(float mark, float gap);
	/// \brief 重置线模板
	void Reset();
	 
	/// \brief 返回模板序列的首地址
	/// \return 
	float* MakePattern();
};

class GS_API GsTemplateLineSymbol: public GsLineSymbol
{
protected:
	GsSymbolTemplate m_template;
	double m_dblOffset;
	double m_dblMapOffset;
	void* m_Parser;
	GsLineDecorationPtr m_ptrLineDecoration;

	GsGeometryBlob m_BlobOff;
protected:  
	/// \brief 几何数据操作
	/// \details 子类通过覆盖此函数实现绘制前对几何数据的处理，例如计算平行线
	/// \param pPath 
	/// \return 
	virtual geostar::gobjptr GeometryOperator(geostar::gobjptr& pPath);

	/// \brief 如果模板线符号中的包含偏移，则计算新的GsGeometryBlob
	/// \param pOldBlob 
	/// \param pNewBlob 
	/// \return 
	bool ComputeNewGeometryForOffset(GsGeometryBlob* pOldBlob, GsGeometryBlob* pNewBlob);

	/// \brief 以Geomathd的path进行绘制
	/// \details 线、或者面的子类符号可以覆盖此方法进行绘制。此方法在GeometryOperator方法之后被调用
	/// \param pBlob 
	virtual void OnDraw(GsGeometryBlob * pBlob);
	
	/// \brief 
	/// \param pPoint 
	/// \param a 
	virtual void OnDrawSub(GsPoint* pPoint,double a){}
	
	/// \brief 
	virtual void OnStartDrawing();

	/// \brief 
	virtual void OnEndDrawing();

	GsTemplateLineSymbol(); 

public:  
	/// \brief 析构函数
	virtual ~GsTemplateLineSymbol(); 

	/// \brief 获取线符号模版属性
	/// \return 
	GsSymbolTemplate SymbolTemplate();
	
	/// \brief 获取线符号模版的指针
	/// \return 返回线符号模版的指针
	GsSymbolTemplate* SymbolTemplatePtr();

	/// \brief 设置线符号模版属性
	/// \param pTemplate 模版对象的指针
	void SymbolTemplate(const GsSymbolTemplate& pTemplate);

	/// \brief 设置线模板的偏移量
	/// \param offset 线模板的偏移量
	void Offset(double offset);

	/// \brief 获取线模板的偏移量
	/// \return 
	double Offset();

	/// \brief 设置线模板的装饰
	/// \param pLineDecoration 
	void LineDecoration(GsLineDecoration* pLineDecoration);

	/// \brief 获取线模板的装饰
	/// \return 
	GsLineDecoration* LineDecoration();

};
GS_SMARTER_PTR(GsTemplateLineSymbol);

class GS_API GsPointLineSymbol:public GsTemplateLineSymbol
{
	GsPointSymbolPtr m_ptrPointSymbol;
	double m_dblSymAngle;
protected:
	/// \brief 绘制点
	/// \param pPoint 
	/// \param a 
	virtual void OnDrawSub(GsPoint* pPoint,double a);

	/// \brief 判断是否可以绘制，SymbolTemplate和PointSymbol非空
	/// \return 
	virtual bool IsValid();

	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
public:
	/// \brief 默认构造函数
	GsPointLineSymbol();

	/// \brief 传入点符号构建
	/// \param pPointSymbol 
	GsPointLineSymbol(GsPointSymbol *pPointSymbol);

	/// \brief 传入点符号和模板构建
	/// \param pPointSymbol 
	/// \param symTemplate 
	GsPointLineSymbol(GsPointSymbol *pPointSymbol,GsSymbolTemplate symTemplate);

	/// \brief 析构函数
	virtual ~GsPointLineSymbol(); 

	/// \brief 获取点线符号中的点符号
	/// \return 
	GsPointSymbol* PointSymbol();

	/// \brief 
	/// \param pPointSymbol 
	void PointSymbol(GsPointSymbol* pPointSymbol);

	/// \brief 设置线符号颜色
	/// \param c 
	virtual void Color(const Utility::GsColor& c);

	/// \brief 线符号颜色
	/// \return 
	virtual Utility::GsColor Color();

	/// \brief 线符号的宽度,单位毫米
	/// \return 
	virtual double Width();
	/// \brief 设置线符号的宽度,单位毫米
	/// \param dblWidth 
	virtual void Width(double dblWidth);
};
GS_SMARTER_PTR(GsPointLineSymbol);
DECLARE_CLASS_CREATE(GsPointLineSymbol);

/// \brief 图框线图片方向
enum GsFramePicDirection
{
	ePicDirectionUp = 1,
	ePicDirectionDown = 2,
	ePicDirectionLeft = 3,
	ePicDirectionRight = 4
};

/// \brief 图框线符号
class GS_API GsFrameLineSymbol:public GsLineSymbol
{
	/// \brief 定义图框线的8个位置
	enum GsFrameElement
	{
		eLeftBottom,
		eRightBottom,
		eRightTop,
		eLeftTop,
		eBottom,
		eRight,
		eTop,
		eLeft,
	};
	/// \brief 记录8个元素位置的方向
	Utility::GsVector<GsFramePicDirection> m_ElementDirection;
	
	/// \brief 线的偏移
	double m_dblOffset;
	
	/// \brief 角落的图片和边上的图片内存块
	Utility::GsGrowByteBuffer m_CornerImage,m_SideImage;
	
	/// \brief 角落和边的的图片。
	Utility::GsImagePtr m_ptrCorner,m_ptrSide;
	
	/// \brief 透明色，背景色
	Utility::GsColor m_pTransparentColor,m_pBackColor;

	GsPenPtr m_ptrPen;
	GsTextureBrushPtr m_ptrBrush;
	/// \brief 是否使用线宽属性
	bool m_bUseWidth;
	/// \brief X、Y方向比例因子
	double m_XScale, m_YScale; 

	/// \brief 
	/// \param w 
	/// \param h 
	/// \param l 
	/// \param d 
	/// \param sx 
	/// \param sy 
	/// \return 
	GsMatrix ComputerMatrix(double w, double h,float* l,int d,double sx=1.0,double sy = 1.0);
private:
	/// \brief 
	/// \param pSide 
	/// \param nPointCount 
	/// \param nIndex 
	virtual void DrawSide(double* pSide,int nPointCount,int nIndex);
	/// \brief 
	/// \param pCorner 
	/// \param nIndex 
	virtual void DrawCorner(double* pCorner,int nIndex);

	/// \brief 
	/// \param coords 
	/// \param num 
	virtual void DrawSingle(double * coords,int num);
	/// \brief 
	/// \param env 
	virtual void DrawSingle(GsBox &env);
protected:	
	/// \brief 以Geomathd的path进行绘制
	/// \details 线、或者面的子类符号可以覆盖此方法进行绘制。此方法在GeometryOperator方法之后被调用
	/// \param pBlob 
	virtual void OnDraw(GsGeometryBlob * pBlob);
	/// \brief 几何数据操作
	/// \details 子类通过覆盖此函数实现绘制前对几何数据的处理，例如计算平行线
	/// \param pPath 
	/// \return 
	virtual geostar::gobjptr GeometryOperator(geostar::gobjptr& pPath);
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();

public:
	GsFrameLineSymbol();
	/// \brief 
	/// \param color 
	/// \param dblWidth 
	GsFrameLineSymbol(const Utility::GsColor& color,double dblWidth = 0.1);
	virtual ~GsFrameLineSymbol(); 

	/// \brief 设置四角的图片
	/// \param pImage 
	void CornerPicture(Utility::GsImagePtr pImage);
	/// \brief 获取四角的图片
	/// \return 
	Utility::GsImagePtr CornerPicture();
	/// \brief 设置四边的图片
	/// \param pImage 
	void SidePicture(Utility::GsImagePtr pImage);
	/// \brief 获取四边的图片
	/// \return 
	Utility::GsImagePtr SidePicture();

	/// \brief 线的偏移
	/// \return 
	double Offset();
	/// \brief 线的偏移
	/// \param off 
	void Offset(double off);

	/// \brief 设置透明色
	/// \param color 
	void TransparentColor (const Utility::GsColor& color);
	/// \brief 获取透明色
	/// \return 
	Utility::GsColor TransparentColor ();
	/// \brief 设置背景色
	/// \param color 
	void BackColor (const Utility::GsColor& color);
	/// \brief 获取背景色
	/// \return 
	Utility::GsColor BackColor ();

	/// \brief 设置X方向比例因子
	/// \param XScale 
	void XScale(double XScale);
	/// \brief 获取X方向比例因子
	/// \return 
	double XScale();
	/// \brief 设置Y方向比例因子
	/// \param YScale 
	void YScale(double YScale);
	/// \brief 获取Y方向比例因子
	/// \return 
	double YScale();

	/// \brief 设置是否使用线宽属性
	/// \param bUseWidth 
	void UseWidth (bool bUseWidth);
	/// \brief 获取是否使用线宽属性
	/// \return 
	bool UseWidth ();

	/// \brief 获取左上角图片方向
	/// \return 
	GsFramePicDirection LeftTopDirection();
	/// \brief 设置左上角图片方向
	/// \param LTDir 
	void LeftTopDirection(GsFramePicDirection LTDir);
	/// \brief 获取右上角图片方向
	/// \return 
	GsFramePicDirection RightTopDirection();
	/// \brief 设置右上角图片方向
	/// \param RTDir 
	void RightTopDirection(GsFramePicDirection RTDir);
	/// \brief 获取左下角图片方向
	/// \return 
	GsFramePicDirection LeftBottomDirection();
	/// \brief 设置左下角图片方向
	/// \param LBDir 
	void LeftBottomDirection(GsFramePicDirection LBDir);
	/// \brief 获取右下角图片方向
	/// \return 
	GsFramePicDirection RightBottomDirection();
	/// \brief 设置右下角图片方向
	/// \param RBDir 
	void RightBottomDirection(GsFramePicDirection RBDir);
	/// \brief 获取左边图片方向
	/// \return 
	GsFramePicDirection LeftSideDirection();
	/// \brief 设置左边图片方向
	/// \param LSideDir 
	void LeftSideDirection(GsFramePicDirection LSideDir);
	/// \brief 获取上边图片方向
	/// \return 
	GsFramePicDirection TopSideDirection();
	/// \brief 设置上边图片方向
	/// \param TSideDir 
	void TopSideDirection(GsFramePicDirection TSideDir);
	/// \brief 获取右边图片方向
	/// \return 
	GsFramePicDirection RightSideDirection();
	/// \brief 设置右边图片方向
	/// \param RSideDir 
	void RightSideDirection(GsFramePicDirection RSideDir);
	/// \brief 获取下边图片方向
	/// \return 
	GsFramePicDirection BottomSideDirection();
	/// \brief 设置下边图片方向
	/// \param BSideDir 
	void BottomSideDirection(GsFramePicDirection BSideDir);

	/// \brief 加载四角图片
	/// \param strFileName 
	/// \return 
	bool LoadCornerPicture(const char* strFileName);
	/// \brief 加载四边图片
	/// \param strFileName 
	/// \return 
	bool LoadSidePicture(const char* strFileName);
	  
};
GS_SMARTER_PTR(GsFrameLineSymbol);
DECLARE_CLASS_CREATE(GsFrameLineSymbol);

/// \brief 点符号方向
enum GsSymbolLocateDirectionType
{
	/// \brief 正北方向
	eDirectionNorth,
	/// \brief 左侧
	eDirectionLeft,
	/// \brief 右侧
    eDirectionRight,
	/// \brief 双侧
	eDirectionBidirectional,
	/// \brief 角平分线
	eDirectionBisector,
};

/// \brief 端点类型
enum GsSymbolLocateEndsType
{
	/// \brief 不绘端点
	eLocateNone,
	/// \brief 仅绘起点
	eLocateBegin,
	/// \brief 仅绘终点
	eLocateEnd,
	/// \brief 绘两端点
	eLocateBoth,
};

class GsAnalysisBlob;
/// \brief 定位点线符号
class GS_API GsLocatePointLineSymbol:public GsLineSymbol
{
	GsPointSymbolPtr                m_ptrPointSymbol;
	GsSymbolLocateDirectionType     m_eDirType;
	GsSymbolLocateEndsType          m_eEndsType;
	Utility::GsImagePtr             m_ptrImage;

	double                          m_dblXmin;
	double                          m_dblYmax;
	long							m_nStartPos;
	long							m_nEndPos;

public:
	/// \brief 默认构造
	GsLocatePointLineSymbol();
	/// \brief 通过点符号构造
	/// \param ptrPointSym 
	GsLocatePointLineSymbol(GsPointSymbolPtr ptrPointSym);

public:
	/// \brief 设置点符号
	/// \param ptrPointSym 
	void PointSymbol(GsPointSymbolPtr ptrPointSym);
	/// \brief 获得点符号
	/// \return 
	GsPointSymbol* PointSymbol();

	/// \brief 设置点符号方向
	/// \param eType 
	void LocateDirection(GsSymbolLocateDirectionType eType);
	/// \brief 获取点符号方向
	/// \return 
	GsSymbolLocateDirectionType LocateDirection();

	/// \brief 设置端点绘制方式
	/// \param eType 
	void LocateEnds(GsSymbolLocateEndsType eType);
	/// \brief 获取端点绘制方式
	/// \return 
	GsSymbolLocateEndsType LocateEnds();

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();

	/// \brief 线符号颜色
	/// \return 
	virtual Utility::GsColor Color();
	/// \brief 设置线符号颜色
	/// \param c 
	virtual void Color(const Utility::GsColor& c);

protected:
	/// \brief 以GeomathSE的path进行绘制
	/// \details 线、或者面的子类符号可以覆盖此方法进行绘制。此方法在GeometryOperator方法之后被调用
	/// \param pBlob 
	virtual void OnDraw(GsGeometryBlob * pBlob);

	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
protected:
	/// \brief 点符号生成位图
	/// \return 
	bool CreateSymbolBitmap();
	/// \brief 初始化成员
	void InitProp();
	/// \brief 根据GsSymbolLocateEndsType过滤顶点
	void FilterVertex();
	/// \brief 绘制图片
	/// \param fX 
	/// \param fY 
	void DrawBitmap(float fX, float fY);
	/// \brief 根据屏幕坐标计算贴图坐标
	/// \param pPath 
	/// \param pAnaBlob 
	/// \param eDirectionType 
	void CalcuBitmapPosition(GsGeometryBlob* pPath,GsAnalysisBlob* pAnaBlob, GsSymbolLocateDirectionType eDirectionType);
	/// \brief 计算点符号旋转角度
	/// \param pAnaBlob 
	/// \param nCurrentIndex 
	/// \param nPointCount 
	/// \param eDirectionType 
	/// \return 
	double RoundAngle(GsAnalysisBlob* pAnaBlob, int nCurrentIndex, int nPointCount, GsSymbolLocateDirectionType eDirectionType);
	/// \brief 根据向量计算角度
	/// \param gsPoint 
	/// \return 
	double Angle(GsRawPoint gsPoint);
};
GS_SMARTER_PTR(GsLocatePointLineSymbol);
DECLARE_CLASS_CREATE(GsLocatePointLineSymbol);

/// \brief 哈希线符号
class GS_API GsHashLineSymbol:public GsTemplateLineSymbol
{
protected:
	/// \brief 实际的绘制线
	GsLineSymbolPtr		m_ptrLineSymbol;
	/// \brief 设置子线和原线的夹角
	double			m_Angle ;
	/// \brief 子线符号的线宽
	double			m_dblSubLineWidth;

protected:
	/// \brief 开始绘制
	virtual void OnStartDrawing();
	/// \brief 结束绘制
	virtual void OnEndDrawing();

protected:	
	/// \brief 根据点位置和角度来做实际绘制
	/// \param pPoint 
	/// \param a 
	virtual void OnDrawSub(GsPoint* pPoint,double a);

public:
	/// \brief 返回线符号
	/// \return 
	GsLineSymbol* LineSymbol();
	/// \brief 设置线符号
	/// \param pLineSymbol 
	void LineSymbol( GsLineSymbol* pLineSymbol);
	/// \brief 获取子线和原线的夹角
	/// \return 
	double Angle();
	/// \brief 设置子线和原线的夹角
	/// \param Angle 
	void Angle(double Angle);

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();

	/// \brief 设置线符号颜色
	/// \param c 
	virtual void Color(const Utility::GsColor& c);

	/// \brief 线符号颜色
	/// \return 
	virtual Utility::GsColor Color();

};
GS_SMARTER_PTR(GsHashLineSymbol);
DECLARE_CLASS_CREATE(GsHashLineSymbol);
/// \brief 制图线符号
class GS_API GsCartographicLineSymbol:public GsTemplateLineSymbol

{
protected: 
	GsLineCapStyle		m_CapStyle;      //符号端套类型
	GsLineJoinStyle		m_JoinStyle;     //线段接头类型
	double				m_dblMiterLimit; //线端斜面接合限值属性
	GsPenPtr			m_ptrPen;		 //画笔
protected: 
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
	 
	/// \details 线、或者面的子类符号可以覆盖此方法进行绘制。此方法在GeometryOperator方法之后被调用
	/// \brief 
	/// \param pBlob 
	virtual void OnDraw(GsGeometryBlob * pBlob);
	
	/// \brief 绘制Canvas的path
	/// \param pPath 
	/// \param pBlob 
	virtual void OnDraw(GsGraphicsPath* pPath,GsGeometryBlob * pBlob);

public:
	GsCartographicLineSymbol();
	/// \brief 
	/// \param color 
	/// \param dblWidth 
	GsCartographicLineSymbol(const Utility::GsColor& color,double dblWidth =0.1);
	virtual ~GsCartographicLineSymbol(); 
	using GsSymbol::DrawGraphics;

	/// \brief 
	/// \param pGeo 
	/// \param pBuffer 
	/// \return 
	bool DrawGraphics(GsGraphicsGeometry* pGeo, GsGeometryBlob* pBuffer);

	/// \brief 获取端套类型
	GsLineCapStyle	CapStyle();
	/// \brief 设置端套类型
	/// \param Style 
	void CapStyle(GsLineCapStyle Style );

	/// \brief 获取接头类型
	/// \return 
	GsLineJoinStyle JoinStyle();
	/// \brief 设置接头类型
	/// \param Style 
	void JoinStyle(GsLineJoinStyle Style );

    /// \brief 获取制图线的线端斜面接合限值
	/// \return 
	double MiterLimit();
	/// \brief 设置制图线的线端斜面接合限值
	/// \param Limit 
	void MiterLimit(double Limit );

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();
};

GS_SMARTER_PTR(GsCartographicLineSymbol);
DECLARE_CLASS_CREATE(GsCartographicLineSymbol);


class GS_API GsLeadConnectedLineSymbol:public GsLineSymbol
{
protected:
	double m_dblInterval;	//单线之间的间隔
	GsLineSymbolPtr m_ptrLineSymbol; //绘制的线型符号

public:
	/// \brief 构造函数，无参构造函数使用简单线符号进行导线的绘制
	GsLeadConnectedLineSymbol();
	/// \brief 构造函数，使用给定的颜色和宽度构造简单线符号进行导线的绘制
	/// \param color 
	/// \param dblWidth 
	GsLeadConnectedLineSymbol(const Utility::GsColor& color,double dblWidth = 0.1);
	/// \brief 构造函数，使用给定的线符号进行导线的绘制
	/// \param ptrLineSymbol 
	GsLeadConnectedLineSymbol(GsLineSymbol* ptrLineSymbol);
	/// \brief 析构函数
	virtual ~GsLeadConnectedLineSymbol();
	/// \brief 获取单线之间的间隔
	/// \return 
	double Interval();
	/// \brief 设置单线之间的间隔
	/// \param interval 
	void Interval(double interval);
	/// \brief 获取线型符号
	/// \return 
	GsLineSymbolPtr LineSymbol();
	/// \brief 设置线型符号
	/// \param ptrLineSymbol 
	void LineSymbol(GsLineSymbol* ptrLineSymbol);

	/// \brief 重写父类方法。获取线符号的宽度,单位毫米
	/// \return 
	virtual double Width();
	/// \brief 重写父类方法。设置线符号的宽度,单位毫米
	/// \param dblWidth 
	virtual void Width(double dblWidth);

	/// \brief 重写父类方法。获取线符号颜色
	/// \return 
	virtual Utility::GsColor Color();
	/// \brief 重写父类方法。设置线符号颜色
	/// \param c 
	virtual void Color(const Utility::GsColor& c);

protected:
	
	/// \brief 当绘制的时候发生
	/// \details 子类通过覆盖此方法实现实际的绘制
	/// \param pBuffer 
	virtual void OnDraw(GsGeometryBlob* pBuffer);

	/// \brief 当开始绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据准备
	virtual void OnStartDrawing();
	/// \brief 当结束绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据回收过程
	virtual void OnEndDrawing();
private:
	/// \brief 
	/// \param pBlobIn 
	/// \param pBlobOut 
	void CalculatePath(GsGeometryBlob * pBlobIn ,GsGeometryBlob &pBlobOut);
	/// \brief 
	/// \param num 
	/// \param coods 
	/// \param pBlobOut 
	void ProcessLine(int num, double * coods, GsGeometryBlob & pBlobOut);

};

GS_SMARTER_PTR(GsLeadConnectedLineSymbol);
DECLARE_CLASS_CREATE(GsLeadConnectedLineSymbol);



/// \brief 脚本化的线符号
class GS_API GsScriptLineSymbol :public GsLineSymbol
{
	Utility::GsString m_strStartDrawingScript;
	Utility::GsString m_strEndDrawingScript;
	Utility::GsString m_strDrawScript;
	GsRefObject*	m_pScriptEngine; 
protected:
	/// \brief 当绘制的时候发生
	/// \details 子类通过覆盖此方法实现实际的绘制
	/// \param pBuffer 
	virtual void OnDraw(GsGeometryBlob* pBuffer);
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();

public:
	/// \brief 缺省构造
	GsScriptLineSymbol();
	GsScriptLineSymbol(ScriptType type);
	virtual ~GsScriptLineSymbol();

	/// \brief 获取开始绘制的脚本
	/// \return 
	Utility::GsString StartDrawingScript();
	/// \brief 设置开始绘制的脚本
	/// \param script 
	void StartDrawingScript(const char* script);

	/// \brief 获取结束绘制的脚本
	/// \return 
	Utility::GsString EndDrawingScript();
	/// \brief 设置结束绘制的脚本
	/// \param script 
	void EndDrawingScript(const char* script);

	/// \brief 获取绘制的脚本
	/// \return 
	Utility::GsString DrawScript();
	/// \brief 设置绘制的脚本
	/// \param script 
	void DrawScript(const char* script);
protected:
protected:
	void Init(ScriptType type);
};

/// \brief GsScriptLineSymbolPtr
GS_SMARTER_PTR(GsScriptLineSymbol);
DECLARE_CLASS_CREATE(GsScriptLineSymbol)

KERNEL_ENDNS
