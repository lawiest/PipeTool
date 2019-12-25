#pragma once
#include "../utility/preconfig.h" 
#include "geometry.h"
#include "spatialreference.h"
#include "canvas.h" 
#include <image.h>
#include <wordanalyzer.h>
#include "serialize.h"
KERNEL_NS   
/// \brief 符号的类型
enum GsSymbolType
{
	/// \brief 点符号
	ePointSymbol,
	/// \brief 线符号
	eLineSymbol,
	/// \brief 面符号
	eFillSymbol,
	/// \brief 文本符号
	eTextSymbol,

	/// \brief 复合符号，不区分点、线、面
	eCompoundSymbol,
};
  

/// \brief 显示坐标转换对象
/// \details 用于实现设备和地图之间的坐标以及长度单位的转换
class GS_API GsDisplayTransformation:public Utility::GsRefObject
{
	/// \brief 参考比例尺
	double					m_RefScale;
	
	/// \brief 地图范围
	GsBox					m_mapExtent;
	/// \brief 设备范围
	Utility::GsRect			m_deviceExtent;

	/// \brief 分辨率，每个像素代表多少地理长度
	double					m_dblResolution;
	/// \brief 地图比例尺。
	double					m_dblScale;

	/// \brief 设备分辨率，缺省为96
	float					m_fDPI;
	
	/// \brief 设备空间参考
	GsSpatialReferencePtr	m_ptrSR;

	
	/// \brief 计算单位相对于米的比例。
	/// \param eUnit 
	/// \return 
	double UnitScale(GsUnits eUnit);
public:	
	/// \brief 从设备范围和地图范围构造
	/// \param mapExtent 
	/// \param deviceExtent 
	GsDisplayTransformation(const GsBox& mapExtent,const Utility::GsRect& deviceExtent);
	virtual ~GsDisplayTransformation();
	/// \brief 当前空间参考
	/// \return 
	GsSpatialReference* SpatialReference();
	
	/// \brief 设置当前空间参考
	/// \param sr 
	void SpatialReference(GsSpatialReference* sr);

	/// \brief 地图范围
	/// \return 
	GsBox MapExtent() const;
	/// \brief 设置地图范围
	/// \param extent 
	void MapExtent(const GsBox& extent);
	
	/// \brief 设备分辨率
	/// \return 
	float DPI();
	/// \brief 设置设备分辨率
	/// \param dpi 
	void DPI(float dpi);
	
	/// \brief 地图分辨率
	/// \return 
	double Resolution();
	
	/// \brief 设置地图分辨率
	/// \param res 
	void Resolution(double res);

	/// \brief 设备范围
	/// \return 
	Utility::GsRect DeviceExtent()const ;
	/// \brief 设置范围
	/// \param extent 
	void DeviceExtent(const Utility::GsRect& extent);

	/// \brief 转换设备坐标到地图坐标
	/// \param x 
	/// \param y 
	/// \param mapx 
	/// \param mapy 
	void ToMap(float x,float y,double& mapx,double& mapy);
	/// \brief 转换设备坐标到地图坐标
	/// \param x 
	/// \param y 
	/// \param mapx 
	/// \param mapy 
	void ToMap(int x,int y,double& mapx,double& mapy);
	/// \brief 转换设备坐标到地图坐标
	/// \param pScreenCoord 
	/// \param nCount 
	/// \param nDim 
	/// \param pMapCoord 
	void ToMap(float* pScreenCoord,int nCount,int nDim,double* pMapCoord);
	/// \brief 转换设备坐标到地图坐标
	/// \param pScreenCoord 
	/// \param nCount 
	/// \param nDim 
	/// \param pMapCoord 
	void ToMap(int* pScreenCoord,int nCount,int nDim,double* pMapCoord);
	
	/// \brief 转换设备坐标到地图坐标
	/// \param rect 
	/// \return 
	GsBox ToMap(const Utility::GsRect& rect);
	/// \brief 转换设备坐标到地图坐标
	/// \param rect 
	/// \return 
	GsBox ToMap(const Utility::GsRectF& rect);
	/// \brief 转换设备坐标到地图坐标
	/// \param pt 
	/// \return 
	GsRawPoint ToMap(const Utility::GsPT& pt);
	/// \brief 转换设备坐标到地图坐标
	/// \param pt 
	/// \return 
	GsRawPoint ToMap(const Utility::GsPTF& pt);
	/// \brief 转换设备坐标到地图坐标
	/// \param x 
	/// \param y 
	/// \return 
	GsRawPoint ToMap(int x,int y);
	/// \brief 转换设备坐标到地图坐标
	/// \param x 
	/// \param y 
	/// \return 
	GsRawPoint ToMap(float x, float y);

	/// \brief 转换地图坐标到设备坐标
	/// \param pt 
	/// \return 
	Utility::GsPTF FromMap(const GsRawPoint& pt);
	/// \brief 转换地图坐标到设备坐标
	/// \param box 
	/// \return 
	Utility::GsRect FromMap(const GsBox& box);
	/// \brief 转换地图坐标到设备坐标
	/// \param box 
	/// \param rect 
	/// \return 
	Utility::GsRectF FromMap(const GsBox& box,Utility::GsRectF& rect );

	/// \brief 转换地图坐标到设备坐标
	/// \param x 
	/// \param y 
	/// \return 
	Utility::GsPTF FromMap(double x,double y);

	/// \brief 转换地图坐标到设备坐标
	/// \param x 
	/// \param y 
	/// \param screenX 
	/// \param screenY 
	void FromMap(double x,double y,float &screenX,float & screenY);
	/// \brief 转换地图坐标到设备坐标
	/// \param x 
	/// \param y 
	/// \param screenX 
	/// \param screenY 
	void FromMap(double x,double y,int &screenX,int & screenY);
	
	/// \brief 转换地图坐标到设备坐标
	/// \param pMapCoord 
	/// \param nCount 
	/// \param nDim 
	/// \param pScreenCoord 
	void FromMap(double* pMapCoord,int nCount,int nDim,float* pScreenCoord);
	/// \brief 转换地图坐标到设备坐标
	/// \param pMapCoord 
	/// \param nCount 
	/// \param nDim 
	/// \param pScreenCoord 
	void FromMap(double* pMapCoord,int nCount,int nDim,int* pScreenCoord);

	/// \brief 从纸面单位长度转换为像素单位长度
	/// \param u 
	/// \param dblLen 
	/// \return 
	double FromPageMeasure(GsUnits u,double dblLen);

	/// \brief 获取比例尺分母的值
	/// \return 
	double Scale();
	/// \brief 设置比例尺的值
	/// \param scale 
	void Scale(double scale);

	/// \brief 获取参考比例尺
	/// \return 
	double ReferenceScale();
	/// \brief 设置参考比例尺
	/// \param dblScale 
	void ReferenceScale(double dblScale);

	/// \brief 地图到屏幕的转换矩阵
	/// \details 屏幕到地图的转换矩阵可以通过矩阵Invert获得
	/// \return 
	GsMatrix Matrix();

public:
	/// \brief 转换毫米单位长度为像素单位长度
	/// \param mm 
	/// \return 
	float MMToPixel(double mm);
	/// \brief 毫米单位转换为字体的单位磅（point)
	/// \param mm 
	/// \return 
	float MMToPoint(double mm);
	/// \brief 磅（point)转换为毫米单位
	/// \param point 
	/// \return 
	float PointToMM(double point);

	/// \brief 像素到毫米
	/// \param nPixel 
	/// \return 
	double PixelToMM(double nPixel);

	/// \brief 毫米单位到地图长度
	/// \param dblMM 
	/// \return 
	double MMToMap(double dblMM);
	/// \brief 地图长度到毫米
	/// \param dblMM 
	/// \return 
	double MapToMM(double dblMM);
	/// \brief 像素长度到地图长度
	/// \param dblPixel 
	/// \return 
	double PixelToMap(double dblPixel);
	/// \brief 地图长度到像素长度
	/// \param dblMap 
	/// \return 
	double MapToPixel(double dblMap);

private:
	double m_MMToPixel;
	double m_MMToPoint;
	double m_MMToMap;
	double m_PixelToMap;
	
	/// \brief 
	void Pretreatment();

};
/// \brief GsDisplayTransformationPtr
GS_SMARTER_PTR(GsDisplayTransformation);


/// \brief 基于画布坐标系系的Geomety
class GS_API GsGraphicsGeometry:public Utility::GsRefObject
{
	Utility::GsGrowByteBuffer m_Temp;
	Utility::GsGrowByteBuffer m_Coordinate;
	Utility::GsGrowByteBuffer m_Interpret;
public:
	GsGraphicsGeometry();
	/// \brief 
	/// \param geo 
	/// \param dt 
	GsGraphicsGeometry(GsGeometry* geo,GsDisplayTransformation* dt);
	/// \brief 
	/// \param geo 
	/// \param dt 
	GsGraphicsGeometry(GsGeometryBlob* geo, GsDisplayTransformation* dt);
	virtual ~GsGraphicsGeometry();
	
	/// \brief 绑定并转换几何数据
	/// \param geo 
	/// \param dt 
	void Assign(GsGeometry* geo, GsDisplayTransformation* dt);
	/// \brief 绑定并转换几何数据
	/// \param geo 
	/// \param dt 
	void Assign(GsGeometryBlob* geo, GsDisplayTransformation* dt);

	/// \brief 几何分块的数量
	/// \return 
	int PartCount()const;

	/// \brief 特定块的坐标指针
	/// \param i 
	/// \return 
	float* PartPtr(int i) const;
	
	/// \brief 特定块的坐标长度
	/// \param i 
	/// \return 
	int PartLength(int i)const;

	/// \brief 总的坐标长度
	/// \return 
	int TotalLength()const;

	/// \brief 清空几何对象
	void Clear();

	/// \brief 添加一段几何坐标
	/// \param pCoord 
	/// \param nLen 
	/// \return 
	float* Append(const float* pCoord, int nLen);

	/// \brief 预留空间添加一段几何坐标
	/// \param nLen 
	/// \return 
	float* Append(int nLen);

};
/// \brief GsGraphicsGeometryPtr
GS_SMARTER_PTR(GsGraphicsGeometry);

/// \brief 符号对象基类
class GS_API GsSymbol:public Utility::GsRefObject
{
	/// \brief 
	/// \param pCoord 
	/// \param nLen 
	/// \param pPath 
	/// \param ndim 
	void AppendPath(double* pCoord,int nLen,GsGraphicsPath* pPath,int ndim = 2);

	/// \brief 
	/// \param n_cood 
	/// \param p_cood 
	/// \param cdim 
	/// \param path 
	void AppendPolyline( int n_cood,double *p_cood,int cdim,GsGraphicsPath*  path);
	/// \brief 
	/// \param pointArray 
	/// \param path 
	/// \param circle 
	void AppendCurve(Utility::GsVector<GsRawPoint>& pointArray,GsGraphicsPath*  path,bool circle=false);
	/// \brief 
	/// \param n_cood 
	/// \param p_cood 
	/// \param cdim 
	/// \param path 
	void AppendEnv( int n_cood,double *p_cood,int cdim,GsGraphicsPath*  path);

protected:
	/// \brief 绘制的画布
	GsCanvasPtr m_ptrCanvas;
	/// \brief 坐标转换
	GsDisplayTransformationPtr m_ptrDT;
	
	/// \brief 画布坐标系Geomety
	GsGraphicsGeometryPtr m_ptrGraphGeo;

	/// \brief 符号名称
	Utility::GsString m_strName;
	/// \brief 符号版本
	Utility::GsString m_strVersion;
	/// \brief 符号描述
	Utility::GsString m_strDesc;


	/// \brief 符号编码
	long long m_nCode; 
	/// \brief 图示编号，字符串的编码
	Utility::GsString m_strCode;

	/// \brief 转换显示用的屏幕坐标
	Utility::GsGrowByteBuffer m_ScreenBuff;  
	
protected:
	/// \brief 由空间分析的path构建成可绘制的path
	/// \param pBlob 
	/// \return 
	GsGraphicsPathPtr CreateGraphicsPath(GsGeometryBlob *pBlob);

	
	/// \brief 转换地理坐标为屏幕坐标
	/// \param pCoord 
	/// \param nLen 
	/// \param nDim 
	/// \return 
	virtual Utility::GsGrowByteBuffer* ToScreen(double* pCoord,int nLen,int nDim);
	/// \brief 
	/// \param pCoord 
	/// \param nLen 
	/// \param nDim 
	/// \return 
	virtual float* ToScreenPtr(double* pCoord,int nLen,int nDim);

	/// \brief 当开始绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据准备
	virtual void OnStartDrawing();
	/// \brief 当结束绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据回收过程
	virtual void OnEndDrawing();

	/// \brief 当绘制的时候发生
	/// \details 子类通过覆盖此方法实现实际的绘制
	/// \param pBuffer 
	virtual void OnDraw(GsGeometryBlob* pBuffer);

	/// \brief 绘制Canvas的path
	/// \param pPath 
	/// \param pBlob 
	virtual void OnDraw(GsGraphicsPath* pPath,GsGeometryBlob *pBlob) ;

	/// \brief 几何数据操作
	/// \details 子类通过覆盖此函数实现绘制前对几何数据的处理，例如计算平行线
	/// \param pPath 
	/// \return 
	virtual geostar::gobjptr GeometryOperator(geostar::gobjptr& pPath);
	/// \brief 缺省构造
	GsSymbol();
public:
	virtual ~GsSymbol();
	
	/// \brief 符号名称
	/// \return 
	virtual Utility::GsString Name();
	/// \brief 设置符号名称
	/// \param strName 
	virtual void Name(const char* strName);
	
	/// \brief 符号版本
	/// \return 
	virtual Utility::GsString Version();
	/// \brief 设置符号版本
	/// \param strVer 
	virtual void Version(const char* strVer);
	
	/// \brief 符号描述
	/// \return 
	virtual Utility::GsString Description();
	/// \brief 设置符号描述
	/// \param strDesc 
	virtual void Description(const char* strDesc);
	
	/// \brief 符号编码
	/// \return 
	virtual long long Code();
	/// \brief 设置符号编码
	/// \param nCode 
	virtual void Code(long long nCode);
	
	/// \brief 图式编号
	/// \return 
	virtual Utility::GsString SchemaCode();
	/// \brief 设置图式编号
	/// \param strCode 
	virtual void SchemaCode(const char* strCode);
	
	/// \brief 是否已经调用了StartDrawing方法
	/// \return 
	virtual bool HasStartDrawing();
	/// \brief 开始绘制
	/// \param pCanvas 
	/// \param pDT 
	/// \return 
	virtual bool StartDrawing(GsCanvas* pCanvas,GsDisplayTransformation *pDT) ;
	/// \brief 结束绘制
	/// \return 
	virtual bool EndDrawing() ;

	/// \brief 绘制几何对象
	/// \param pGeo 
	/// \return 
	virtual bool Draw(GsGeometry* pGeo);

	/// \brief 绘制几何内存块
	/// \param pBuffer 
	/// \return 
	virtual bool DrawBlob(GsGeometryBlob* pBuffer);

	/// \brief 绘制画布坐标系下的几何对象
	/// \param pGeo 
	/// \param pBuffer 
	/// \return 
	virtual bool DrawGraphics(GsGraphicsGeometry* pGeo, GsGeometryBlob* pBuffer);

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();

	/// \brief 符号的类型
	/// \return 
	virtual GsSymbolType Type() = 0;

	
	/// \brief 对符号进行克隆
	/// \return 
	virtual Utility::GsSmarterPtr<GsSymbol> Clone();
	/// \brief	用指定符号的边界填充现有多边形.
	/// \details Geometry参数输入有特定限制:
	/// \details PointSymbol,  Geometry 必须为GsPoint.
	/// \details FillSymbol,  Geometry 必须为  GsPolygon;
	/// \details LineSymbol,  Geometry 必须为 GsPolyline
	/// \param pCanvas 
	/// \param pDT 
	/// \param pGeometry 
	/// \param pboundary 
	/// \return 
	virtual bool QueryBoundary(GsCanvas* pCanvas, GsDisplayTransformation *pDT, GsGeometry * pGeometry, GsPolygon* pboundary);
	DECLARE_CLASS_NAME(GsSymbol);
};
/// \brief GsSymbolPtr
GS_SMARTER_PTR(GsSymbol);
 

/// \brief 线符号基类
class GS_API GsLineSymbol:public GsSymbol, public UTILITY_NAME::GsSerialize
{
protected:
	/// \brief 线的宽度
	double m_dblWidth;
	/// \brief 线的颜色
	Utility::GsColor m_Color;
protected:
	GsLineSymbol();
public:
	using GsSymbol::DrawGraphics;
	virtual ~GsLineSymbol();

	/// \brief 绘制Canvas的path
	/// \param pPath 
	/// \param pBlob 
	virtual void DrawGraphics(GsGraphicsPath* pPath, GsGeometryBlob *pBlob);

	/// \brief 符号的类型
	/// \return 
	virtual GsSymbolType Type();
	
	/// \brief 线符号的宽度,单位毫米
	/// \return 
	virtual double Width();
	/// \brief 设置线符号的宽度,单位毫米
	/// \param dblWidth 
	virtual void Width(double dblWidth);

	/// \brief 线符号颜色
	/// \return 
	virtual Utility::GsColor Color();
	/// \brief 设置线符号颜色
	/// \param c 
	virtual void Color(const Utility::GsColor& c);

	// 通过 GsSerialize 继承
	/// \brief 
	/// \param pSerStream 
	/// \return 
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 
	/// \param pSerStream 
	/// \return 
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 
	/// \return 
	virtual UTILITY_NAME::GsString ClassName();
	DECLARE_CLASS_NAME(GsLineSymbol);
};
GS_SMARTER_PTR(GsLineSymbol);


/// \brief 面符号基类
class GS_API GsFillSymbol:public GsSymbol, public UTILITY_NAME::GsSerialize
{
protected:
	/// \brief 填充颜色
	Utility::GsColor m_Color; 
	/// \brief 面的边线符号
	GsLineSymbolPtr m_ptrLineSymbol;
	/// \brief 面的边界线是否转化为线数据
	bool m_GenerateLine;
	 
protected: 
	/// \brief 当开始绘制的时候发生
	virtual void OnStartDrawing();
	/// \brief 当结束绘制时发生
	virtual void OnEndDrawing();
	 
public:
	GsFillSymbol();
	virtual ~GsFillSymbol();
	
	/// \brief 绘制Canvas的path
	/// \param pPath 
	/// \param pBlob 
	virtual void DrawGraphics(GsGraphicsPath* pPath, GsGeometryBlob *pBlob);
	/// \brief 绘制Canvas的path
	/// \param pPath 
	/// \param pBlob 
	/// \return 
	virtual bool DrawGraphics(GsGraphicsGeometry* pPath, GsGeometryBlob *pBlob);

	/// \brief 符号类型
	/// \return 
	virtual GsSymbolType Type();
	/// \brief 填充的颜色
	/// \return 
	virtual Utility::GsColor FillColor();
	/// \brief 设置填充的颜色
	/// \param c 
	virtual void FillColor(const Utility::GsColor& c);
	/// \brief 边线符号
	/// \return 
	virtual GsLineSymbol* Outline();
	/// \brief 设置边线符号
	/// \param pSym 
	virtual  void Outline(GsLineSymbol* pSym);

	/// \brief 设置面边界是否转为线符号
	/// \param bGenerateLine 
	virtual void GenerateLine(bool bGenerateLine);

	/// \brief 获取面边界是否转为线符号
	/// \return 
	virtual bool GenerateLine();

	// 通过 GsSerialize 继承
	/// \brief 
	/// \param pSerStream 
	/// \return 
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 
	/// \param pSerStream 
	/// \return 
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 
	/// \return 
	virtual UTILITY_NAME::GsString ClassName();
	DECLARE_CLASS_NAME(GsFillSymbol);
};
GS_SMARTER_PTR(GsFillSymbol);



/// \brief 文本风格（左倾、右倾、左耸、右耸）
enum GsTextStyle
{
	/// \brief 无倾斜
	/// \details  ━━
	/// \details ┃  ┃
	/// \details ┃  ┃
	/// \details  ━━
	/// \details 
	eTextStyleNormal,
	/// \brief 左倾
	/// \details  ━━
	/// \details  ╲   ╲
	/// \details    ╲   ╲
	/// \details       ━━
	eTextStyleLeftItalic,
	/// \brief 右倾
	/// \details        ━━
	/// \details      ╱  ╱
	/// \details    ╱  ╱
	/// \details   ━━
	eTextStyleRightItalic,
	/// \brief 左耸
	/// \details ┃╲    
	/// \details ┃  ╲  
	/// \details  ╲   ┃
	/// \details     ╲┃
	eTextStyleLeftShrug,
	/// \brief 右耸
	/// \details    ╱┃   
	/// \details  ╱  ┃  
	/// \details ┃  ╱
	/// \details ┃╱
	eTextStyleRightShrug 
};
/// \brief 背景绘制接口类, 继承此接口实现不同背景的绘制,此接口类只管绘制, 具体调用需要调用者组织
class GS_API GsCalloutBackground :public Utility::GsRefObject
{
protected:
	/// \brief 
	GsCalloutBackground() {}
public:
	/// \brief 绘制背景
	/// \details 根据设备和几何绘制背景,
	/// \param pGeo 绘制的几何
	/// \param pCanvas 绘制的Canvas
	/// \param pDT 绘制DT
	/// \return 是否绘制成功
	virtual bool Draw(GsGeometry* pGeo, GsCanvas* pCanvas, GsDisplayTransformation* pDT) = 0;

	/// \brief 
	/// \return 
	virtual GeoStar::Utility::GsSmarterPtr<GsCalloutBackground> Clone() = 0;
};
GS_SMARTER_PTR(GsCalloutBackground);
/// \brief 标注符号背景绘制枚举
enum GsTextBackgroundBoundingStyle
{
	/// \brief 绘制指定范围的最小外接矩形
	eMinimumBoundingBox,
	/// \brief 绘制指定范围的最小外接圆
	eMinimumBoundingCircle,
};
/// \brief TextSymbol背景绘制实现
class GS_API GsTextBackground :public GsCalloutBackground
{
	GsTextBackgroundBoundingStyle m_BoxStyle;
	bool m_isSetPoint;
	GsRawPoint m_pt;
	GsFillSymbolPtr m_ptrSymbol;

	/// \brief 传进来GsRing类型的面数据，获取添加点后的面数据。
	/// \param pGeo 需要处理的面数据
	/// \param point 需要添加的点数据。
	/// \return 返回处理后的数据。如果面包含点，则返回原数据.
	GsGeometryPtr GetGeometryAfterAddPoint(GsGeometry* pGeo, GsRawPoint point);
public:
	/// \brief 构造函数,默认使用外接矩形绘制方式
	/// \param enumBoundingStyle 
	GsTextBackground(GsTextBackgroundBoundingStyle enumBoundingStyle= eMinimumBoundingBox);
	~GsTextBackground();

	/// \brief 绘制背景
	/// \details 根据设备和几何绘制背景,
	/// \param pGeo 绘制的几何
	/// \param pCanvas 绘制的Canvas
	/// \param pDT 绘制DT
	/// \return 是否绘制成功
	virtual bool Draw(GsGeometry* pGeo, GsCanvas* pCanvas, GsDisplayTransformation* pDT);
	/// \brief 设置绘制的面符号
	/// \param pFillSym 
	void FillSymbol(GsFillSymbol* pFillSym);
	/// \brief 获取绘制的面符号
	/// \return 
	GsFillSymbol* FillSymbol();
	/// \brief 设置绘制的样式
	/// \param enumBoundingStyle 
	void BoundingStyle(GsTextBackgroundBoundingStyle enumBoundingStyle);
	/// \brief 获取绘制的样式
	/// \return 
	GsTextBackgroundBoundingStyle BoundingStyle();
	/// \brief 文字悬浮框符号指示点,
	/// \param point 
	void Point(const GsRawPoint& point);
	/// \brief 文字悬浮框符号指示点,
	/// \return 
	GsRawPoint Point();

	/// \brief 
	/// \return 
	virtual GeoStar::Utility::GsSmarterPtr<GsCalloutBackground> Clone();
};
GS_SMARTER_PTR(GsTextBackground);

struct TextDrawUnit;
/// \brief 文本符号
class GS_API GsTextSymbol : public GsSymbol, public UTILITY_NAME::GsSerialize
{  
	GsTextStyle				m_eTextStyle;					//倾斜类型
	bool					m_bBold;						//加粗标识
	bool					m_bHollow;						//空心标识
	bool					m_bUnderLine;					//下划线标识
	bool					m_bStrikeOut;					//删除线标识
	GsSolidBrushPtr			m_ptrBrush;						//注记填充画刷
	GsPenPtr				m_ptrHaloPen;					//注记光晕画笔
	GsPenPtr				m_ptrPen;						//注记描边画笔
	GsPenPtr				m_ptrWhitePen;					//绘制不偏移阴影效果时的白色画刷
	Utility::GsColor					m_textColor;					//注记颜色
	Utility::GsString		m_strFont;						//字体名称
	float					m_fSize;						//字体大小
	Utility::GsString		m_strText;						//注记内容
	GsStringFormatPtr		m_ptrTextFormat;				//注记样式
	GsStringAlignment		m_eHAlignment;					//水平对齐方式
	GsStringAlignment		m_eVAlignment;					//垂直对齐方式
	double					m_dblWidth;						//注记宽度
	double					m_dblHeight;					//注记高度
	double					m_dblStyleAngle;				//字体风格的角度参数，例左倾斜的角度
	double					m_dblAngle;						//旋转角度
	double					m_offsetX;						//X偏移
	double					m_offsetY;						//Y偏移
	double					m_dblHExtra;					//水平间距
	double					m_dblVExtra;					//垂直间距
	Utility::GsColor					m_backColor;					//背景色（为空时表示透明）
	GsSolidBrushPtr			m_ptrBackBrush;					//背景填充画刷
	Utility::GsColor					m_shadowColor;					//阴影色（为空时表示无阴影效果）
	GsSolidBrushPtr			m_ptrShadowBrush;				//阴影填充画刷
	double					m_shadowOffsetX;				//阴影X偏移
	double					m_shadowOffsetY;				//阴影Y偏移
	GsMatrix				m_WordStyleMatrix;				//单个字的式样变换矩阵实现倾斜和缩放。
	int						m_iLabelOffset;					//LineLabelPlacement Offset。
	Utility::GsSizeF		m_WordSize;
	Utility::GsSizeF		m_StringSize;
	UTILITY_NAME::GsVector<Utility::GsString> m_SplitWords;
	bool					m_SimpleDraw;
	Utility::GsWordAnalyzerPtr		m_ptrWordAnalyzer;
	Utility::GsColor					m_HaloColor;					//光晕颜色
	double					m_HaloSize;						//光晕的大小
	GsCalloutBackgroundPtr  m_ptrBackground;					//背景的绘制

	bool					m_bVerticalText;				//是否是纵向文字
	Utility::GsString		m_strVerticalText;				//纵向文字
private:
	/// \brief 绘制一个文本单元
	/// \param loc 
	/// \param angle 
	/// \param vecWords 
	void DrawText(const Utility::GsPTF& loc,double angle,const UTILITY_NAME::GsVector<Utility::GsString>& vecWords);
	
	/// \brief 将字符串进行整体的绘制
	/// \param loc 
	void DrawText(const Utility::GsPTF& loc);
	
	/// \brief 符号是否可以用简单绘制实现
	/// \return 
	bool CanSimpleDraw();

	/// \brief 
	/// \param vecDraw 
	/// \param mxBlock 
	void DrawUnderLine(const UTILITY_NAME::GsVector<TextDrawUnit>& vecDraw, const GsMatrix& mxBlock);

	void DoVerticalText();

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
	
	/// \brief 单独绘制背景
	void DrawCelloutBackground();
	/// \brief 一个文本单元位置计算
	/// \param vecDraw 
	/// \param loc 
	/// \param Angle 
	/// \param vecWords 
	/// \param w 
	/// \param h 
	void DrawUnitCalc(Utility::GsVector<TextDrawUnit>& vecDraw,const Utility::GsPTF& loc, double Angle, const Utility::GsVector<Utility::GsString>& vecWords,int &w,int &h);

public:
	/// \brief 默认构造函数
	GsTextSymbol();
	/// \brief 析构函数
	virtual ~GsTextSymbol();

	/// \brief 获取光晕的颜色
	/// \return 
	Utility::GsColor HaloColor();
	/// \brief 设置光晕的颜色
	/// \param halo 
	void HaloColor(const Utility::GsColor& halo);

	/// \brief 获取光晕的大小，单位毫米
	/// \return 
	double HaloSize();
	/// \brief 设置光晕的大小，单位毫米
	/// \param size 
	void HaloSize(double size);


	/// \brief 设置倾斜类型
	/// \param style 
	void TextStyle(GsTextStyle style);
	/// \brief 获取倾斜类型
	/// \return 
	GsTextStyle TextStyle();

	/// \brief 设置加粗标识
	/// \param bBold 
	void Bold(bool bBold);
	/// \brief 获取加粗标识
	/// \return 
	bool Bold();

	/// \brief 设置空心标识
	/// \param bStroke 
	void Hollow(bool bStroke);
	/// \brief 获取空心标识
	/// \return 
	bool Hollow();

	/// \brief 设置下划线标识
	/// \param bUnderLine 
	void UnderLine(bool bUnderLine);
	/// \brief 获取下划线标识
	/// \return 
	bool UnderLine();

	/// \brief 设置删除线标识
	/// \param bStrikeOut 
	void StrikeOut(bool bStrikeOut);
	/// \brief 获取删除线标识
	/// \return 
	bool StrikeOut();

	/// \brief 返回符号的颜色
	/// \return 
	Utility::GsColor Color();
	/// \brief 设置符号的颜色
	/// \param color 
	void Color(const Utility::GsColor& color);

	/// \brief 返回符号的字体
	/// \return 
	Utility::GsString Font();
	/// \brief 设置符号的字体
	/// \param strFont 
	void Font(const char* strFont);

	/// \brief 返回符号的大小
	/// \return 
	float Size();
	/// \brief 设置符号的大小 注记的宽度和高度也改变为符号的大小，也可通过其他方法直接改变注记的宽度和高度
	/// \param iSize 
	void Size(float iSize);

	/// \brief 返回符号的文本
	/// \return 
	Utility::GsString Text();
	/// \brief 设置符号的文本
	/// \param strText 
	void Text(const char* strText);

	/// \brief 获取水平对齐方式
	/// \return 
	GsStringAlignment HorizonAlign();
	/// \brief 设置水平对齐方式
	/// \param eAlignment 
	void HorizonAlign(GsStringAlignment eAlignment);

	/// \brief 获取垂直对齐方式
	/// \return 
	GsStringAlignment VerticalAlign();
	/// \brief 设置垂直对齐方式
	/// \param eAlignment 
	void VerticalAlign(GsStringAlignment eAlignment);

	/// \brief 获取注记宽度
	/// \return 
	double Width();
	/// \brief 设置注记高度
	/// \param width 
	void Width(double width);

	/// \brief 获取注记高度
	/// \return 
	double Height();
	/// \brief 设置注记高度
	/// \param height 
	void Height(double height);

	/// \brief 获取字体风格的倾斜角度
	/// \return 
	double StyleAngle();
	/// \brief 设置字体风格的倾斜角度
	/// \param angle 
	void StyleAngle(double angle);

	/// \brief 获取注记旋转角度
	/// \return 
	double Angle();
	/// \brief 设置注记旋转角度
	/// \param angle 
	void Angle(double angle);

	/// \brief 获取注记X偏移
	/// \return 
	double OffsetX();
	/// \brief 设置注记X偏移
	/// \param offset 
	void OffsetX(double offset);

	/// \brief 获取注记Y偏移
	/// \return 
	double OffsetY();
	/// \brief 设置注记Y偏移
	/// \param offset 
	void OffsetY(double offset);

	/// \brief 获取注记水平间距
	/// \return 
	double HorizonExtra();
	/// \brief 设置注记水平间距
	/// \param extra 
	void HorizonExtra(double extra);

	/// \brief 获取注记垂直间距
	/// \return 
	double VerticalExtra();
	/// \brief 设置垂直水平间距
	/// \param extra 
	void VerticalExtra(double extra);

	/// \brief 返回注记的背景色
	/// \return 
	Utility::GsColor BackgroundColor();
	/// \brief 设置注记的背景色
	/// \param color 
	void BackgroundColor(const Utility::GsColor& color);

	/// \brief 返回注记阴影的颜色
	/// \return 
	Utility::GsColor ShadowColor();
	/// \brief 设置注记阴影的颜色
	/// \param color 
	void ShadowColor(const Utility::GsColor& color);

	/// \brief 返回注记阴影的X偏移
	/// \return 
	double ShadowOffsetX();
	/// \brief 设置注记阴影的X偏移
	/// \param offset 
	void ShadowOffsetX(double offset);

	/// \brief 返回注记阴影的Y偏移
	/// \return 
	double ShadowOffsetY();
	/// \brief 设置注记阴影的Y偏移
	/// \param offset 
	void ShadowOffsetY(double offset);

	/// \brief 设置文字内容中的方框大小
	/// \param pSize 
	void StringSize(const Utility::GsSizeF& pSize);

	/// \brief 返回符号的类型
	/// \return 
	virtual GsSymbolType Type();
	
	/// \brief 是否有效
	/// \return 
	virtual bool IsValid();

	/// \brief 对符号进行克隆
	/// \return 
	virtual Utility::GsSmarterPtr<GsSymbol> Clone();

	/// \brief 返回分词器
	/// \return 
	Utility::GsWordAnalyzer* WordAnalyzer();
	/// \brief 设置分词器
	/// \param pAnalyzer 
	void WordAnalyzer(Utility::GsWordAnalyzer* pAnalyzer);

	// 通过 GsSerialize 继承
	/// \brief 
	/// \param pSerStream 
	/// \return 
	virtual bool Serialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 
	/// \param pSerStream 
	/// \return 
	virtual bool DeSerialize(UTILITY_NAME::GsSerializeStream * pSerStream) override;

	/// \brief 
	/// \return 
	virtual UTILITY_NAME::GsString ClassName();
	/// \brief 背景绘制类
	/// \param pBackground 
	void CalloutBackground(GsCalloutBackground* pBackground);
	/// \brief 背景绘制类
	/// \return 
	GsCalloutBackground* CalloutBackground();
	DECLARE_CLASS_NAME(GsTextSymbol);

	/// \brief 设置是否纵向绘制文字
	/// \param bVerticalText 
	void VerticalText(bool bVerticalText);
	/// \brief 是否是纵向绘制文字
	bool VerticalText();
};

/// \brief GsTextSymbolPtr
GS_SMARTER_PTR(GsTextSymbol);
DECLARE_CLASS_CREATE(GsTextSymbol);



template<typename T>
class GsMultiSymbolT:public T
{
protected:
	UTILITY_NAME::GsVector<Utility::GsSmarterPtr<T> > m_Symbols;
	GsMultiSymbolT(){}
	
	/// \brief 当开始绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据准备
	virtual void OnStartDrawing()
	{
		typename UTILITY_NAME::GsVector<Utility::GsSmarterPtr<T> >::iterator it = m_Symbols.begin();
		for(;it != m_Symbols.end(); ++it)
		{
			(*it)->StartDrawing(this->m_ptrCanvas,this->m_ptrDT);
		}
	}
	/// \brief 当结束绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据回收过程
	virtual void OnEndDrawing()
	{
		typename UTILITY_NAME::GsVector<Utility::GsSmarterPtr<T> >::iterator it = m_Symbols.begin();
		for(; it != m_Symbols.end(); ++it)
		{
			(*it)->EndDrawing();
		}
	}

	/// \brief 当绘制的时候发生
	/// \details 子类通过覆盖此方法实现实际的绘制
	/// \param pBuffer 
	virtual void OnDraw(GsGeometryBlob* pBuffer)
	{
		typename UTILITY_NAME::GsVector<Utility::GsSmarterPtr<T> >::iterator it = m_Symbols.begin();
		for(; it != m_Symbols.end(); ++it)
		{
			(*it)->DrawBlob(pBuffer);
		}
	}
	
public:
	virtual ~GsMultiSymbolT(){}
	/// \brief 绘制画布坐标系下的几何对象
	/// \param pGeo 
	/// \param pBuffer 
	/// \return 
	virtual bool DrawGraphics(GsGraphicsGeometry* pGeo, GsGeometryBlob* pBuffer)
	{
		typename UTILITY_NAME::GsVector<Utility::GsSmarterPtr<T> >::iterator it = m_Symbols.begin();
		for (; it != m_Symbols.end(); ++it)
		{
			if(!(*it)->DrawGraphics(pGeo,pBuffer) )
				(*it)->DrawBlob(pBuffer);
		}
		return true;
	}

	/// \brief 增加子符号
	/// \param pSymbol 
	virtual void Add(T* pSymbol)
	{
		m_Symbols.push_back(pSymbol);
	}

	/// \brief 清空所有的符号
	virtual void Clear()
	{
		m_Symbols.clear();
	}

	/// \brief 子符号的数量
	/// \return 
	virtual int Count()
	{
		return m_Symbols.size();
	}
	/// \brief 子符号的数量
	/// \param i 
	virtual void RemoveAt(int i)
	{
		if(i <0 || i >= m_Symbols.size())
			return;
		m_Symbols.erase(m_Symbols.begin() + (Utility::GsVector<GsSymbolPtr>::difference_type)i);
	}

	/// \brief 获取子符号
	/// \param i 
	/// \return 
	T* ElementAt(int i)
	{
		if(i <0 || i >= m_Symbols.size())
			return NULL;
		return m_Symbols[i].p;
	}
	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid()
	{
		if(m_Symbols.empty())
			return false;
		//所有的子符号，如果一个有效则整个有效
		typename UTILITY_NAME::GsVector<Utility::GsSmarterPtr<T> >::iterator it = m_Symbols.begin();
		for(; it != m_Symbols.end(); ++it)
		{
			if((*it)->IsValid())
				return true;
		}
		return false;
	}
	

};


/// \brief 复合线符号
class GS_API GsMultiLineSymbol:public GsMultiSymbolT<GsLineSymbol>
{
public:
	/// \brief 获取线符号的宽度,单位毫米
	/// \return 
	virtual double Width();
	/// \brief 设置线符号的宽度,单位毫米
	/// \param dblWidth 
	virtual void Width(double dblWidth);

	/// \brief 获取线符号颜色
	/// \return 
	virtual Utility::GsColor Color();
	/// \brief 设置线符号颜色
	/// \param c 
	virtual void Color(const Utility::GsColor& c);
};
/// \brief GsMultiLineSymbolPtr
GS_SMARTER_PTR(GsMultiLineSymbol);
DECLARE_CLASS_CREATE(GsMultiLineSymbol);


/// \brief 复合面符号
class GS_API GsMultiFillSymbol:public GsMultiSymbolT<GsFillSymbol>
{
public:
	/// \brief 获取填充的颜色
	/// \return 
	virtual Utility::GsColor FillColor();
	/// \brief 设置填充的颜色
	/// \param c 
	virtual void FillColor(const Utility::GsColor& c);
	/// \brief 获取边线符号
	/// \return 
	virtual GsLineSymbol* Outline();
	/// \brief 设置边线符号
	/// \param pSym 
	virtual  void Outline(GsLineSymbol* pSym);
	DECLARE_CLASS_NAME(GsMultiFillSymbol);
};
/// \brief GsMultiFillSymbolPtr
GS_SMARTER_PTR(GsMultiFillSymbol);
DECLARE_CLASS_CREATE(GsMultiFillSymbol);

/// \brief 复合符号、混合符号
class GS_API GsCompoundSymbol :public GsSymbol
{
	GsSymbolPtr  m_Symbols[3];
protected:
	/// \brief 当开始绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据准备
	virtual void OnStartDrawing();
	/// \brief 当结束绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据回收过程
	virtual void OnEndDrawing();

	/// \brief 当绘制的时候发生
	/// \details 子类通过覆盖此方法实现实际的绘制
	/// \param pBuffer 
	virtual void OnDraw(GsGeometryBlob* pBuffer);
public:
	GsCompoundSymbol();
	GsCompoundSymbol(GsSymbol* ptSym, GsSymbol* lineSym, GsSymbol* fillSym);
	
	/// \brief 根据维度获取符号,维度（0，1，2）
	GsSymbol* SymbolDimension(int n);

	/// \brief 根据维度设置符号,维度（0，1，2）
	void SymbolDimension(int n,GsSymbol* sym);

	/// \brief 点符号
	GsSymbol* PointSymbol();
	/// \brief 点符号
	void PointSymbol(GsSymbol* ptSym);

	/// \brief 线符号
	GsSymbol* LineSymbol();
	/// \brief 线符号
	void LineSymbol(GsSymbol* ptSym);

	/// \brief 面符号
	GsSymbol* FillSymbol();
	/// \brief 面符号
	void FillSymbol(GsSymbol* ptSym);


	/// \brief 返回符号的类型
	/// \return 
	virtual GsSymbolType Type();


};
/// \brief GsCompoundSymbolPtr
GS_SMARTER_PTR(GsCompoundSymbol);
DECLARE_CLASS_CREATE(GsCompoundSymbol);


/// \brief 符号库的格式
enum GsSymbolLibraryFormat
{
	/// \brief 地图定义文件的符号存储格式
	eGeoMapDefineFormat,
	/// \brief 跨平台符号的符号存储格式。
	eGenernalFormat,
};

/// \brief 符号库对象。
/// \details 用于实例化符号库的符号或者生成符号库文件。
class GS_API GsSymbolLibrary
{
	void *m_Doc;
	/// \brief 
	void LoadSymbol();
	Utility::GsString m_strFileName;
	Utility::GsString m_Name;
	Utility::GsString m_Description;
	UTILITY_NAME::GsVector<GsSymbolPtr> m_vecSymbols;
public:
	/// \brief 从符号库文件或者符号库xml字符串实例化对象
	/// \param strSymbolLib 
	/// \param bFileName 
	GsSymbolLibrary(const char* strSymbolLib,bool bFileName = true);
	
	/// \brief 构造一个空的符号库对象
	GsSymbolLibrary();

	virtual ~GsSymbolLibrary();
	
	/// \brief 符号库的路径
	/// \return 
	Utility::GsString Path();


	/// \brief 保存符号的集合
	/// \return 
	UTILITY_NAME::GsVector<GsSymbolPtr>* Symbols();

	/// \brief 根据符号的Code查找符号
	/// \details 如果存在多个相同的code则返回第一个符号。
	/// \param nCode 
	/// \return 
	GsSymbolPtr SymbolByCode(long long nCode);

	/// \brief 根据符号的Code查找符号
	/// \param nCode 需要查找的编号
	/// \param eType 需要查找的符号的类型
	/// \return 返回特定类型(eType)下找到的(nCode)编号的第一个符号
	GsSymbolPtr SymbolByCode(long long nCode, GsSymbolType eType);

	/// \brief 根据符号的名称查找符号
	/// \details 支持统配查找
	/// \param strName 
	/// \return 
	GsSymbolPtr SymbolByName(const char* strName);

	/// \brief 根据字符串的图式编号查找Code
	/// \details 支持统配查找
	/// \param SchemaCode 
	/// \return 
	GsSymbolPtr SymbolBySchemaCode(const char* SchemaCode);

	/// \brief 返回特定类型的符号。
	/// \param eType 
	/// \return 
	UTILITY_NAME::GsVector<GsSymbolPtr> Symbols(GsSymbolType eType);

	/// \brief 保存符号库到文件
	void Save();
	
	/// \brief 保存符号库到字符串
	/// \param eFormat 
	/// \return 
	Utility::GsString SaveToString(GsSymbolLibraryFormat eFormat=eGenernalFormat);
	
	/// \brief 保存符号库到新的文件。
	/// \param strSymbolLibFile 
	void Save(const char* strSymbolLibFile);

	/// \brief 符号库的名称
	/// \return 
	Utility::GsString Name();
	
	/// \brief 设置符号库的名称
	/// \param strName 
	void Name(const char* strName);

	/// \brief 符号库的名称
	/// \return 
	Utility::GsString Description();
	
	/// \brief 设置符号库的描述信息。
	/// \param strDesc 
	void Description(const char* strDesc);

	/// \brief 将符号序列化为字符串。
	/// \param pSym 
	/// \param eFormat 
	/// \return 
	static Utility::GsString ToString(GsSymbol* pSym,GsSymbolLibraryFormat eFormat = eGenernalFormat);
	
	/// \brief 计算符号哈希值
	/// \param pSym 
	/// \return 
	static long long HashCode(GsSymbol* pSym);

	/// \brief 从字符串解析生成符号对象
	/// \param str 
	/// \return 
	static GsSymbolPtr ParserSymbol(const char* str);

	/// \brief 为特定的符号解析并配置属性
	/// \param pSym 
	/// \param strXML 
	/// \return 
	static bool Assign(GsSymbol* pSym,const char* strXML);

	/// \brief 为特定的符号解析并配置属性
	/// \param pSym 
	/// \param pEle 
	/// \return 
	static bool Assign(GsSymbol* pSym,tinyxml2::XMLElement* pEle);

};

KERNEL_ENDNS