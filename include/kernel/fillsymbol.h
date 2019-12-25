#pragma once
#include "symbol.h"
#include "linesymbol.h"

KERNEL_NS    
/// \brief 简单面符号
class GS_API GsSimpleFillSymbol:public GsFillSymbol
{
	
	GsSolidBrushPtr m_ptrBrush;
	GsBrushStyle m_Style;
protected:

	/// \brief 
	/// \param pPath 
	/// \param pBlob 
	virtual void OnDraw(GsGraphicsPath* pPath,GsGeometryBlob * pBlob);

	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
public:
	GsSimpleFillSymbol();
	/// \brief 
	/// \param c 
	GsSimpleFillSymbol(const Utility::GsColor& c);
	virtual ~GsSimpleFillSymbol();
	
	
	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();

	/// \brief 画笔的式样
	/// \return 
	GsBrushStyle  Style();
	/// \brief 画笔的式样
	/// \param eStyle 
	void Style(GsBrushStyle eStyle);
};
GS_SMARTER_PTR(GsSimpleFillSymbol);

DECLARE_CLASS_CREATE(GsSimpleFillSymbol);


/// \brief 点符号填充式样
enum GsPointFillStyle
{
	
    /// \brief 格网填充
	ePFS_Grid = 0,
    /// \brief 品形填充
	ePFS_Triangle = 1,
    /// \brief 随机填充
	ePFS_Random = 2,
    /// \brief Label点填充
	ePFS_LabelPoint = 3
};


/// \brief 点填充符号
class GS_API GsPointFillSymbol:public GsFillSymbol
{
	GsPointSymbolPtr m_ptrPointSymbol;
	GsPointFillStyle m_eStyle;
	double m_dblGridAngle;
	GsRawPoint m_Offset;
	double m_dblXSeparation,m_dblYSeparation;
	Utility::GsImagePtr  m_ptrImage;
	GsTextureBrushPtr m_ptrTexture;
	double m_dblPointAngle;

protected:
	/// \brief 
	/// \param pPath 
	/// \param pBlob 
	virtual void OnDraw(GsGraphicsPath* pPath,GsGeometryBlob * pBlob);
	/// \brief 
	/// \param pPath 
	/// \param pGeoPath 
	virtual void DrawRandomPoint(GsGraphicsPath* pPath,geostar::gobjptr &pGeoPath);
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
	/// \brief 
	/// \param pPath 
	/// \param pGeoPath 
	virtual void DrawCentralPoint(GsGraphicsPath* pPath,geostar::gobjptr &pGeoPath);
protected:
	
	/// \brief 点符号生成位图
	/// \return 
	bool CreateBitmap();

public:
	GsPointFillSymbol();
	/// \brief 
	/// \param pPt 
	/// \param eStyle 
	GsPointFillSymbol(GsPointSymbol* pPt,GsPointFillStyle eStyle);
	
	/// \brief 获取点符号
	/// \return 
	GsPointSymbol* PointSymbol();
	/// \brief 设置点符号
	/// \param pt 
	void PointSymbol(GsPointSymbol* pt);
	/// \brief 获取点符号填充式样
	/// \return 
	GsPointFillStyle Style();
	/// \brief 设置点符号填充式样
	/// \param eStyle 
	void Style(GsPointFillStyle eStyle);

	/// \brief 获取格网填充时格网的角度
	/// \return 
	double GridAngle();
	/// \brief 获取格网角度
	/// \param angle 
	void GridAngle(double angle);

	/// \brief 偏移
	/// \return 
	GsRawPoint Offset();
	/// \brief 偏移
	/// \param offset 
	void Offset(const GsRawPoint& offset);

	/// \brief x方向上间隔
	/// \return 
	double XSeparation();
	/// \brief x方向上间隔
	/// \param val 
	void XSeparation(double val);

	/// \brief y方向上间隔
	/// \return 
	double YSeparation();
	/// \brief y方向上间隔
	/// \param val 
	void YSeparation(double val);

	/// \brief 获取图片
	/// \return 
	Utility::GsImage* Picture();

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();
};
GS_SMARTER_PTR(GsPointFillSymbol);
DECLARE_CLASS_CREATE(GsPointFillSymbol);

/// \brief 线填充符号
class GS_API GsLineFillSymbol:public GsFillSymbol
{
	double m_dblOffset;
	double m_dblAngle;
	GsLineSymbolPtr m_ptrFillLineSymbol;
	double m_dblSeparation;
	GsTextureBrushPtr m_ptrTexture;
	GsPenPtr m_ptrPen;
//	Utility::GsColor m_color;
public:
	GsLineFillSymbol();
	/// \brief 
	/// \param pLineSymbol 
	GsLineFillSymbol(GsLineSymbol* pLineSymbol);
	/// \brief 获取线填充的角度
	/// \return 
	double Angle();
	/// \brief 设置线填充的角度
	/// \param angle 
	void Angle(double angle);

	/// \brief 获取线符号
	/// \return 
	GsLineSymbol* LineSymbol();
	/// \brief 设置线符号
	/// \param pLine 
	void LineSymbol(GsLineSymbol* pLine);

	/// \brief 获取线填充的间隔
	/// \return 
	double Separation();
	/// \brief 设置线填充的间隔
	/// \param dblValue 
	void Separation(double dblValue);
	
	/// \brief 线的偏移
	/// \return 
	double Offset();
	/// \brief 线的偏移
	/// \param off 
	void Offset(double off);
protected:
	/// \brief 
	/// \param pPath 
	/// \param pBlob 
	virtual void OnDraw(GsGraphicsPath* pPath,GsGeometryBlob *pBlob);

	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
	/// \brief 
	/// \param ptrSym 
	/// \param dblWidth 
	/// \param dblHeight 
	void CreateBitmapBrush(GsSymbolPtr ptrSym,double dblWidth,double dblHeight);
	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();

};
GS_SMARTER_PTR(GsLineFillSymbol);
DECLARE_CLASS_CREATE(GsLineFillSymbol);


/// \brief 图片填充符号
class GS_API GsPictureFillSymbol:public GsFillSymbol
{
	GsRawPoint m_Offset;
	double m_dblXSeparation, m_dblYSeparation;
	double m_dblXScale, m_dblYScale;

	Utility::GsGrowByteBuffer  m_ImageData;
	Utility::GsImagePtr        m_ptrImage;
	GsTextureBrushPtr          m_ptrTextureBrush;
	/// \brief 背景色
	Utility::GsColor                    m_BackColor;
	/// \brief 透明色,显示时会将此颜色设为透明
	Utility::GsColor                    m_TransparentColor;
	double                     m_dblAngle;

public:
	GsPictureFillSymbol();
	/// \brief 
	/// \param pImg 
	GsPictureFillSymbol(Utility::GsImage* pImg);
	
	/// \brief 获取图片的旋转
	/// \return 
	double Angle();
	/// \brief 设置图片的旋转
	/// \param angle 
	void Angle(double angle);

	/// \brief 获取图片
	/// \return 
	Utility::GsImage* Picture();
	/// \brief 设置图片
	/// \param img 
	void Picture(Utility::GsImage* img);

	/// \brief 背景色
	/// \return 
	Utility::GsColor  BackColor();
	/// \brief 透明色
	/// \param color 
	void BackColor(const Utility::GsColor& color);

	/// \brief 透明色
	/// \return 
	Utility::GsColor TransparentColor();
	/// \brief 设置线填充的间隔
	/// \param color 
	void TransparentColor(const Utility::GsColor& color);

	/// \brief x方向上的缩放比率
	/// \return 
	double XScale();
	/// \brief x方向上的缩放比率
	/// \param scale 
	void XScale(double scale);

	/// \brief y方向上的缩放比率
	/// \return 
	double YScale();
	/// \brief y方向上的缩放比率
	/// \param scale 
	void YScale(double scale);

	/// \brief 从文件载入图片
	/// \param strFile 
	void LoadPicture(const char* strFile);
	/// \brief 从内存载入图片
	/// \param blob 
	/// \param nLen 
	void LoadPicture(const unsigned char* blob,int nLen);
	
	/// \brief 是否平铺
	/// \return 
	bool Tile();
	/// \brief 是否平铺
	/// \param bVal 
	void Tile(bool bVal);
	
	/// \brief 偏移
	/// \return 
	GsRawPoint Offset();
	/// \brief 偏移
	/// \param offset 
	void Offset(const GsRawPoint& offset);
	
	/// \brief x方向上间隔
	/// \return 
	double XSeparation();
	/// \brief x方向上间隔
	/// \param val 
	void XSeparation(double val);

	/// \brief y方向上间隔
	/// \return 
	double YSeparation();
	/// \brief y方向上间隔
	/// \param val 
	void YSeparation(double val);

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();

protected:
	/// \brief 
	void InitProperty();

	/// \brief 
	/// \param pPath 
	/// \param pBlob 
	virtual void OnDraw(GsGraphicsPath* pPath,GsGeometryBlob * pBlob);
	/// \brief 当开始绘制的时候发生
	virtual void OnStartDrawing();
	/// \brief 当结束绘制时发生
	virtual void OnEndDrawing();

};
GS_SMARTER_PTR(GsPictureFillSymbol);
DECLARE_CLASS_CREATE(GsPictureFillSymbol);


enum GsGradsFillStyle
{
    eGFS_LINEAR = 1,
    eGFS_RECTANGULAR = 2,
    eGFS_CIRCULAR = 3,
    eGFS_GFSBUFFERED = 4
};
enum GsColorGradient
{
	eAllGradient =1,
	eToneGradient=2,
	eSaturationGradient=3,
	ePurityGradient=4,
};
/// \brief 渐变填充符号
class GS_API GsGradsFillSymbol:public GsFillSymbol
{
private:	
	int m_Interval;
	double m_Percentage;

	double m_GradsAngle;
	GsGradsFillStyle m_Style;
	GsColorGradient m_ColorGradient;
	Utility::GsGradsColor *m_pGradsColor;

	Utility::GsColor m_StartColor;
	Utility::GsColor m_EndColor;

	GsLinearGradientBrushPtr m_ptrLinearGradientBrush;
	GsRadialGradientBrushPtr m_ptrRadialGradientBrush;

public:
	GsGradsFillSymbol();
	/// \brief 
	/// \param grads 
	/// \param eStyle 
	GsGradsFillSymbol(Utility::GsGradsColor* grads,GsGradsFillStyle eStyle);
	/// \brief 
	/// \param sc 
	/// \param ec 
	/// \param eStyle 
	GsGradsFillSymbol(Utility::GsColor& sc,Utility::GsColor& ec,GsGradsFillStyle eStyle);

	/// \brief 渐变色填充的角度
	/// \param angle 
	void GradsAngle(double angle);
	/// \brief 渐变色填充的角度
	/// \return 
	double GradsAngle();
	
	/// \brief 渐变色填充的式样
	/// \return 
	GsGradsFillStyle Style();
	/// \brief 渐变色填充的式样
	/// \param eStyle 
	void Style(GsGradsFillStyle eStyle);

	/// \brief 渐变色填充
	/// \return 
	GsColorGradient ColorGradientStyle();
	/// \brief 渐变色填充
	/// \param eStyle 
	void ColorGradientStyle(GsColorGradient eStyle);
	/// \brief 渐变色填充的比率
	/// \return 
	double Percentage();
	/// \brief 渐变色填充的比率
	/// \param val 
	void Percentage(double val);
	
	/// \brief 渐变色填充的间隔
	/// \return 
	int Interval();
	/// \brief 渐变色填充的间隔
	/// \param val 
	void Interval(int val);


	/// \brief 渐变色
	/// \return 
	Utility::GsColor StartColor();
	/// \brief 渐变色
	/// \param c 
	void StartColor(Utility::GsColor &c);
	/// \brief 渐变色
	/// \return 
	Utility::GsColor EndColor();
	/// \brief 渐变色
	/// \param c 
	void EndColor(Utility::GsColor &c);

	/// \brief 渐变色
	/// \return 
	Utility::GsGradsColor* GradsColor();
	/// \brief 渐变色
	/// \param grads 
	void GradsColor(Utility::GsGradsColor* grads);

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	bool IsValid();

protected: 
	/// \brief 
	/// \param env_in 
	/// \param startPoint 
	/// \param endPoint 
	void StartAndEndPoint(GsBox &env_in, GsRawPoint& startPoint, GsRawPoint& endPoint);
	/// \brief 
	/// \param pPath 
	void RectGradsFill(geostar::gobjptr& pPath);

	/// \brief 当绘制的时候发生
	/// \details 子类通过覆盖此方法实现实际的绘制
	/// \param pBlob 
	virtual void OnDraw(GsGeometryBlob * pBlob);
	/// \brief 
	/// \param pPath 
	/// \param pBlob 
	virtual void OnDraw(GsGraphicsPath* pPath, GsGeometryBlob *pBlob);


	/// \brief 当开始绘制的时候发生
	virtual void OnStartDrawing();
	/// \brief 当结束绘制时发生
	virtual void OnEndDrawing();
};
GS_SMARTER_PTR(GsGradsFillSymbol);
DECLARE_CLASS_CREATE(GsGradsFillSymbol);

/// \brief 建筑符号
class GS_API GsBuildingFillSymbol:public GsFillSymbol
{
public:
	/// \brief 立体房屋的高度获取方式
	enum GsExtrusionHeightMode
	{
		/// \brief 不设置
		NONE=0,
		/// \brief 常数
		CONSTANTNUM,
		/// \brief 字段
		FIELDKEY,
		/// \brief 脚本计算
		AUTOCAL
	};
private:
	int m_iHeight;
	Utility::GsString m_iHeightKey;
	GsExtrusionHeightMode m_iHeightMode;
	int m_iAngle;
	GsBrushStyle m_Style;
	GsSolidBrushPtr m_ptrBrush;
	GsSimpleFillSymbolPtr m_ptrWallFillSym;
	GsSimpleLineSymbolPtr m_ptrWallLineSym;
	GsSimpleFillSymbolPtr m_ptrTopFillSym;
public:
	GsBuildingFillSymbol();

	/// \brief 视角
	/// \return 
	int ViewAngle();
	/// \brief 视角
	/// \param iAngle 
	void ViewAngle(int iAngle);

	/// \brief 基础，必须要小于或者等于高度
	/// \return 
	int ExtrusionBase();

	/// \brief 获取高度的方式
	/// \return 
	GsExtrusionHeightMode ExtrusionHeightMode();
	/// \brief 高度(地理距离,单位米)
	/// \return 
	int ExtrusionHeight();
	/// \brief 高度(地理距离,单位米)
	/// \param iHeight 
	void ExtrusionHeight(int iHeight);
	/// \brief 高度字段
	/// \return 
	Utility::GsString ExtrusionHeightKey();
	/// \brief 高度字段
	/// \param HeightKey 
	void ExtrusionHeightKey(Utility::GsString HeightKey);

	virtual GsSymbolType Type();	

	/// \brief 画笔的式样
	/// \return 
	GsBrushStyle  Style();
	/// \brief 画笔的式样
	/// \param eStyle 
	void Style(GsBrushStyle eStyle);
	
	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	/// \return 
	virtual bool IsValid();

	/// \brief 绘制顶部
	/// \param pGeo 
	virtual void DrawTop(GsGeometry* pGeo);

protected:
	/// \brief 
	/// \param pPath 
	/// \param pBlob 
	virtual void OnDraw(GsGraphicsPath* pPath,GsGeometryBlob * pBlob);
	/// \brief 当开始绘制的时候发生
	virtual void OnStartDrawing();
	/// \brief 当结束绘制时发生
	virtual void OnEndDrawing();

protected:
	bool IsViewVisible(double x1, double y1, double x2, double y2, int iAngle, bool bClockWise);	
	/// \brief 
	/// \param vecCoord 
	/// \param ptrSym 
	void DrawPolygon(Utility::GsVector<double>& vecCoord, GsFillSymbol* ptrSym);
};
GS_SMARTER_PTR(GsBuildingFillSymbol);
DECLARE_CLASS_CREATE(GsBuildingFillSymbol);

KERNEL_ENDNS