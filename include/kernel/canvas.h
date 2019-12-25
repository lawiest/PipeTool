#pragma once
#include "matrix.h"
#include "geometry.h"
#include <image.h>
#include <configuration.h>

KERNEL_NS

/// \brief 画笔的类型
enum GsPenStyle
{ 
	/// \brief 实线
	/// \image html eSolidLine.png "SolidLine"
	eSolidLine,
    /// \brief 虚线
	/// \image html eDashLine.png "SolidLine"
	eDashLine,
    /// \brief 点线
	/// \image html eDotLine.png "SolidLine"
	eDotLine,
	/// \brief 点划线
    /// \image html eDashDotLine.png "SolidLine"
	eDashDotLine,
    /// \brief 点点划线
	/// \image html eDashDotDotLine.png "SolidLine"
	eDashDotDotLine,
    /// \brief 自定义线
	/// \image html eCustomDashLine.png "SolidLine"
	eCustomDashLine,
};

/// \brief 画笔端头类型
enum GsPenCapStyle
{
	/// \brief 平头
	/// \image html eFlatCap.png "FlatCap"
	eFlatCap,
    /// \brief 方头
	/// \image html eSquareCap.png "SquareCap"
	eSquareCap,
	/// \brief 圆头
    /// \image html eRoundCap.png "RoundCap"
	eRoundCap
};

/// \brief 画笔线段衔接类型
enum GsPenJoinStyle 
{  
    /// \brief 尖
    /// \image html eMiterJoin.png "MiterJoin"
	eMiterJoin,
    /// \brief 楔形
	/// \image html eBevelJoin.png "BevelJoin"
	eBevelJoin,
    /// \brief 圆头
    /// \image html eRoundJoin.png "RoundJoin"
	eRoundJoin,
};

/// \brief 画笔绘制的类型
enum GsBrushStyle 
{  
	eHorizontalBrush,
	eVerticalBrush,
	eFdiagonalBrush,
	eBdiagonalBrush,
	eCrossBrush,
	eDiagCrossBrush,
	eEmptyBrush,
	eSolidBrush,
} ; 
/// \brief 字体的式样
enum GsFontStyle
{
	eFontStyleRegular = 0,
	eFontStyleBlack = 0x01,
	eFontStyleBold = 0x02,
	eFontStyleItalic = 0x04,
	eFontStyleBoldItalic = eFontStyleBold | eFontStyleItalic,
	eFontStyleBlackItalic = eFontStyleBlack | eFontStyleItalic,
	eFontStyleUnderline = 0x08,
    eFontStyleStrikeout = 0x10,
};

/// \brief 字体的倾斜
enum GsItalic
{
	/// \brief 不倾斜
	eNormalItalic,
    /// \brief 右倾斜
	eRightItalic,
    /// \brief 左倾斜
	eLeftItalic
};
/// \brief 字符对齐类型
enum GsStringAlignment
{
	eStringAlignmentNear = 0,
    eStringAlignmentCenter = 1,
    eStringAlignmentFar = 2
};

/// \brief 字符串格式化对象
class GS_API GsStringFormat:public Utility::GsRefObject
{
protected:
	Utility::GsString m_strFont;
	float m_fSize;
	GsFontStyle m_FontStyle;
	/// \brief 字符串行对齐
	GsStringAlignment m_eLineAlignment;
	/// \brief 字符串行对齐
	GsStringAlignment m_eAlignment;
	/// \brief 字体间距
	float m_fHExtra;
public:
	GsStringFormat();
	virtual ~GsStringFormat();
	
	/// \brief 设置字体名称
	/// \param strFont 
	virtual void Font(const char* strFont);
	/// \brief 获取字体名称
	/// \return 
	virtual Utility::GsString Font();

	/// \brief 设置字体大小,单位磅
	/// \param fSize 
	virtual void FontSize(float fSize);
	/// \brief 设置字体大小,单位磅
	/// \return 
	virtual float FontSize();

	/// \brief 字体式样
	/// \return 
	virtual GsFontStyle FontStyle();
	/// \brief 字体式样
	/// \param eStyle 
	virtual void FontStyle(GsFontStyle eStyle);

	/// \brief 列对齐
	/// \return 
	virtual GsStringAlignment Alignment();
	/// \brief 列对齐
	/// \param e 
	virtual void Alignment (GsStringAlignment e);

	/// \brief 行对齐
	/// \return 
	virtual GsStringAlignment LineAlignment();
	/// \brief 行对齐
	/// \param e 
	virtual void LineAlignment (GsStringAlignment e);
	/// \brief 字间距
	/// \param extra 
	virtual void HorizonExtra(float extra);
	/// \brief 
	/// \return 
	virtual float HorizonExtra();
};
/// \brief GsStringFormatPtr
GS_SMARTER_PTR(GsStringFormat);  


/// \brief 路径对象
/// \details 复杂线、面绘制数据对象，从GsCanvas::CreatePath()创建
class GS_API GsGraphicsPath:public  Utility::GsRefObject
{
protected:
	GsGraphicsPath();
	GsMatrix m_Mx;
public:
	virtual ~GsGraphicsPath();
	/// \brief 开始一个子绘制段
	/// \return 
	virtual bool StartFigure() = 0;
	/// \brief 封闭一个子绘制段
	/// \return 
	virtual bool CloseFigure()= 0;
	/// \brief 恢复路径对象为初始状态
	/// \return 
	virtual bool Reset()= 0;
	/// \brief 增加一根线段
	/// \param x1 
	/// \param y1 
	/// \param x2 
	/// \param y2 
	/// \return 
	virtual bool AddLine(int x1,int y1,int x2,int y2);
	/// \brief 增加一根线段
	/// \param x1 
	/// \param y1 
	/// \param x2 
	/// \param y2 
	/// \return 
	virtual bool AddLine(float x1,float y1,float x2,float y2);
	/// \brief 增加一段连续的线段
	/// \param pCoord 
	/// \param nPointCount 
	/// \return 
	virtual bool AddLines(float* pCoord,int nPointCount);
	/// \brief 增加一段连续的线段
	/// \param pCoord 
	/// \param nPointCount 
	/// \return 
	virtual bool AddLines(int* pCoord,int nPointCount);

	/// \brief 增加一段圆弧
	/// \param rect 圆弧所在椭圆的的矩形范围
	/// \param fStartAngle 圆弧开始的角度（单位度）
	/// \param fSweepAngle 圆弧旋转的角度（单位度）
	/// \return 
	virtual bool AddArc(const Utility::GsRect& rect,float fStartAngle,float fSweepAngle);
	/// \brief 
	/// \param rect 
	/// \param fStartAngle 
	/// \param fSweepAngle 
	/// \return 
	virtual bool AddArc(const Utility::GsRectF& rect,float fStartAngle,float fSweepAngle);
	
	/// \brief 增加三次贝塞尔曲线
	/// \param pCoord 
	/// \param nPointCount 
	/// \return 
	virtual bool AddBezier(float* pCoord,int nPointCount);
	/// \brief 增加三次贝塞尔曲线
	/// \param pCoord 
	/// \param nPointCount 
	/// \return 
	virtual bool AddBezier(int* pCoord,int nPointCount);

	/// \brief 增加二次贝塞尔曲线
	/// \param pCoord 
	/// \param nPointCount 
	/// \return 
	virtual bool AddQuadraticBezier (float* pCoord,int nPointCount);
	/// \brief 增加二次贝塞尔曲线
	/// \param pCoord 
	/// \param nPointCount 
	/// \return 
	virtual bool AddQuadraticBezier (int* pCoord,int nPointCount);
	
	/// \brief 向path中添加一个字符串
	/// \param str 
	/// \param nLen 
	/// \param pStrFormat 
	/// \param layoutRect 
	/// \return 
	virtual bool AddString(const char* str,int nLen,GsStringFormat* pStrFormat,const Utility::GsRectF &layoutRect);

	/// \brief 获取仿射变换矩阵
	/// \return 
	virtual GsMatrix Transform();
	/// \brief 设置仿射变换矩阵
	/// \param rhs 
	virtual void Transform(const GsMatrix& rhs);
	
	/// \brief 重置仿射变换矩阵为单位矩阵
	virtual void ResetTransform();

	/// \brief 范围
	/// \return 
	virtual Utility::GsRectF Envelope();


};
/// \brief GsGraphicsPathPtr
GS_SMARTER_PTR(GsGraphicsPath);

/// \brief 区域对象
/// \details 标示一个范围，可用于裁切
class GS_API GsRegion:public  Utility::GsRefObject
{
protected:
	GsRegion(){}

public:
	virtual ~GsRegion(){}

	/// \brief 区域的外接矩形范围
	/// \return 
	virtual Utility::GsRect Bounds() = 0;
};
/// \brief GsRegionPtr
GS_SMARTER_PTR(GsRegion);

/// \brief 画刷对象基类
class GS_API GsBrush:public  Utility::GsRefObject
{
};
/// \brief GsBrushPtr
GS_SMARTER_PTR(GsBrush);

/// \brief 颜色填充画刷对象
class GS_API GsSolidBrush:public  GsBrush
{
protected:
	/// \brief 画刷的颜色
	Utility::GsColor m_Color;
	 
	GsBrushStyle m_Style;
public:

	/// \brief 从颜色构造画刷
	/// \param c 
	GsSolidBrush(const Utility::GsColor& c);
	virtual ~GsSolidBrush();
	/// \brief 画刷的颜色
	/// \return 
	virtual Utility::GsColor Color();
	/// \brief 设置画刷的颜色
	/// \param c 
	virtual void Color(const Utility::GsColor& c);
	
	/// \brief 画笔的式样
	/// \return 
	GsBrushStyle  Style();
	/// \brief 画笔的式样
	/// \param eStyle 
	void Style(GsBrushStyle eStyle);
};
/// \brief GsSolidBrushPtr
GS_SMARTER_PTR(GsSolidBrush);

/// \brief 根据刷子样式获得最小范围(8*8)的像素块，用来填充
class GS_API GsBrushStylePixels
{
public:
	/// \brief 
	/// \param eStyle 
	/// \param c 
	GsBrushStylePixels(GsBrushStyle eStyle,const Utility::GsColor &c);
	virtual ~GsBrushStylePixels();

public:
	/// \brief 
	/// \param pBuffer 
	virtual void CopyPattern(unsigned char* pBuffer);

protected:
	Utility::GsColor m_Color;
	GsBrushStyle m_eStyle;

	/// \brief 
	/// \param c 
	/// \param pStream 
	void WriteColor(const Utility::GsColor &c, unsigned char* pStream);
};
/// \brief GsBrushStylePixels
GS_SMARTER_PTR(GsBrushStylePixels);

/// \brief 使用图片填充的画刷
class GS_API GsTextureBrush:public  GsBrush
{
protected:
	Utility::GsImagePtr m_ptrImage;
	GsMatrix m_Matrix;
public:
	/// \brief 从图片构造画刷
	/// \param pImage 
	GsTextureBrush(Utility::GsImage* pImage);

	/// \brief 获取画刷的图像
	/// \return 
	virtual  Utility::GsImage* Image();
	/// \brief 设置画刷的图像
	/// \param pImg 
	virtual  void Image(Utility::GsImage* pImg);

	/// \brief 获取变换矩阵
	/// \return 
	virtual GsMatrix Transform();
	/// \brief 设置变换矩阵
	/// \param mx 
	virtual void Transform(const GsMatrix& mx);
	
};
/// \brief GsTextureBrushPtr
GS_SMARTER_PTR(GsTextureBrush);


/// \brief 使用线型渐变填充的画刷
class GS_API GsLinearGradientBrush:public  GsBrush
{
protected:
	/// \brief 画刷的开始结束颜色
	Utility::GsColor m_StartColor;
	Utility::GsColor m_EndColor;
	/// \brief 画刷的开始结束位置
	Utility::GsPTF m_StartPoint;
	Utility::GsPTF m_EndPoint;

public:
	/// \brief 默认构造画刷
	GsLinearGradientBrush();
	/// \brief 从颜色和区域构造画刷
	/// \param StartColor 
	/// \param EndColor 
	GsLinearGradientBrush(const Utility::GsColor& StartColor, const Utility::GsColor& EndColor);

	virtual ~GsLinearGradientBrush();
	/// \brief 画刷的颜色
	/// \return 
	virtual Utility::GsColor StartColor();
	/// \brief 设置画刷的颜色
	/// \param c 
	virtual void StartColor(const Utility::GsColor& c);
	/// \brief 画刷的颜色
	/// \return 
	virtual Utility::GsColor EndColor();
	/// \brief 设置画刷的颜色
	/// \param c 
	virtual void EndColor(const Utility::GsColor& c);
	/// \brief 渐变的开始位置
	/// \return 
	virtual Utility::GsPTF StartPoint();
	/// \brief 设置渐变的开始位置
	/// \param c 
	virtual void StartPoint(const Utility::GsPTF& c);
	/// \brief 渐变的结束位置
	/// \return 
	virtual Utility::GsPTF EndPoint();
	/// \brief 设置渐变的结束位置
	/// \param c 
	virtual void EndPoint(const Utility::GsPTF& c);
};
/// \brief GsLinearGradientBrushPtr
GS_SMARTER_PTR(GsLinearGradientBrush);

/// \brief 使用辐射渐变填充的画刷
class GS_API GsRadialGradientBrush:public  GsBrush
{
protected:
	/// \brief 画刷的开始结束颜色
	Utility::GsColor m_StartColor;
	Utility::GsColor m_EndColor;
	/// \brief 辐射中心
	Utility::GsPTF m_CenterPoint;
	/// \brief 辐射半径
	float m_Radius;

public:
	/// \brief 默认构造画刷
	GsRadialGradientBrush();
	/// \brief 从颜色和范围构造画刷
	/// \param StartColor 
	/// \param EndColor 
	GsRadialGradientBrush(const Utility::GsColor& StartColor, const Utility::GsColor& EndColor);

	virtual ~GsRadialGradientBrush();
	/// \brief 画刷的颜色
	/// \return 
	virtual Utility::GsColor StartColor();
	/// \brief 设置画刷的颜色
	/// \param c 
	virtual void StartColor(const Utility::GsColor& c);
	/// \brief 画刷的颜色
	/// \return 
	virtual Utility::GsColor EndColor();
	/// \brief 设置画刷的颜色
	/// \param c 
	virtual void EndColor(const Utility::GsColor& c);
	
	/// \brief 辐射中心
	/// \return 
	virtual Utility::GsPTF CenterPoint();
	/// \brief 设置辐射中心
	/// \param p 
	virtual void CenterPoint(const Utility::GsPTF& p);
	/// \brief 辐射半径
	/// \return 
	virtual float Radius();
	/// \brief 设置辐射半径
	/// \param f 
	virtual void Radius(const float f);
};
/// \brief GsRadialGradientBrushPtr
GS_SMARTER_PTR(GsRadialGradientBrush);


/// \brief 画笔对象
class GS_API GsPen:public  Utility::GsRefObject
{ 
protected:
	/// \brief 画笔的颜色
	Utility::GsColor  m_Color;
	/// \brief 画笔的宽度
	float	m_fWidth;
	/// \brief 画笔的类型
	GsPenStyle m_ePenStyle;
	/// \brief 画笔的模板
	UTILITY_NAME::GsVector<float> m_vecDashPattern;
	/// \brief 画笔偏移长度
	float m_fDashOffset;
	/// \brief 线衔接尖头限制
	float m_fMiterLimit;
	/// \brief 线开始和结束头类型
	GsPenCapStyle m_eStartCap,m_eEndCap;
	/// \brief 线衔接类型
	GsPenJoinStyle m_eLineJoin;
	/// \brief 画笔使用的画刷。
	GsBrushPtr m_ptrBrush;
public:
	/// \brief 从颜色和宽度构造画笔
	/// \param color 
	/// \param fWidth 
	GsPen(const Utility::GsColor& color,float fWidth =1.0f);
	
	/// \brief 从画刷构建画笔
	/// \param pBrush 
	/// \param fWidth 
	GsPen(GsBrush* pBrush,float fWidth =1.0f);

	/// \brief 获取画刷
	/// \return 
	virtual GsBrush* Brush();
	/// \brief 设置画刷
	/// \param pBrush 
	virtual void Brush(GsBrush* pBrush);

	virtual ~GsPen();
	/// \brief 颜色
	/// \return 
	virtual Utility::GsColor Color() const;
	/// \brief 设置颜色
	/// \param  
	virtual void Color(const Utility::GsColor &);
	
	/// \brief 宽度
	/// \return 
	virtual float Width() const;
	/// \brief 设置宽度
	/// \param w 
	virtual void Width(float w);

	/// \brief 画笔式样
	/// \return 
	virtual GsPenStyle Style() const;
	/// \brief 设置画笔式样
	/// \param eStyle 
	virtual void Style(GsPenStyle eStyle);
	
	/// \brief 点线、点划线偏移量
	/// \param offset 
	virtual void DashOffset(float offset);
	/// \brief 获取点线、点划线偏移量
	/// \return 
	virtual float DashOffset()const;

	/// \brief 设置自定义点划线的模板
	/// \param pattern 
	virtual void DashPattern(const UTILITY_NAME::GsVector<float>& pattern);
	/// \brief 自定义点划线的模板
	/// \return 
	virtual UTILITY_NAME::GsVector<float> DashPattern() const;
	
	/// \brief 线衔接尖头限制
	/// \return 
	virtual float MiterLimit() const;
	/// \brief 设置线衔接尖头限制
	/// \param f 
	virtual void MiterLimit(float f);

	/// \brief 线起点的头类型
	/// \return 
	virtual GsPenCapStyle StartCap() const;
	/// \brief 设置线起点的头类型
	/// \param style 
	virtual void StartCap(GsPenCapStyle style);

	/// \brief 线终点的头类型
	/// \return 
	virtual GsPenCapStyle EndCap() const;
	/// \brief 设置线终点的头类型
	/// \param style 
	virtual void EndCap(GsPenCapStyle style);

	/// \brief 线衔接类型
	/// \return 
	virtual GsPenJoinStyle LineJoin() const;
	/// \brief 设置线衔接类型
	/// \param style 
	virtual void LineJoin(GsPenJoinStyle style);
};
/// \brief GsPenPtr
GS_SMARTER_PTR(GsPen);

/// \brief 图像效果。
class GS_API GsImageEffect:public Utility::GsRefObject
{
	float m_fTransparency;
public:
	GsImageEffect();
	virtual ~GsImageEffect();

	/// \brief 图像透明度[0-1]，0表示不透明，1表示完全透明
	/// \return 
	float Transparency();

	/// \brief 图像透明度[0-1]，0表示不透明，1表示完全透明
	/// \param fTransparency 
	void Transparency(float fTransparency);

	/// \brief 不透明度[0-1],0表示完全透明，1表示完全不透明，与透明度相反，等于1-Transparency();
	/// \return 
	float Opacity();

};
/// \brief GsImageEffectPtr
GS_SMARTER_PTR(GsImageEffect);


class GsImageCanvas;
/// \brief 画布的抽象基类
/// \details 通过继承此基类实现不同平台和不同绘制技术的画布
class GS_API GsCanvas:public Utility::GsRefObject
{
protected:
	/// \brief 缺省的矩阵
	GsMatrix m_Matrix; 

	/// \brief 绘制起算的原点
	Utility::GsPT m_RenderingOrigin;

	/// \brief 画布的可视范围
	Utility::GsRectF     m_VisibleBound;
	/// \brief 裁切范围
	GsRegionPtr m_ptrClipRegion;
	
	/// \brief 画布设备类型
	int m_DeviceType;

	GsCanvas();
public:
	virtual ~GsCanvas();

	/// \brief 画布设备类型
	/// \return 
	int DeviceType();

	/// \brief 画布设备类型
	/// \param eType 
	void DeviceType(int eType);

	/// \brief 获取绘制起算的原点
	/// \return 
	virtual Utility::GsPT RenderingOrigin();
	/// \brief 设置绘制起算的原点
	/// \param pt 
	virtual void RenderingOrigin(const Utility::GsPT& pt);

	/// \brief 获取仿射变换矩阵
	/// \return 
	virtual GsMatrix Transform();
	/// \brief 设置仿射变换矩阵
	/// \param rhs 
	virtual void Transform(const GsMatrix& rhs);
	
	/// \brief 重置仿射变换矩阵为单位矩阵
	virtual void ResetTransform();

	/// \brief 画布裁切的最大矩形范围或者画布的范围
	/// \details 画布如果设置了裁切范围则返回裁切的最大矩形，否则返回画布的范围
	/// \return 
	virtual Utility::GsRect ClipBounds();

	/// \brief 清除裁切范围
	virtual void ClearClip();

	/// \brief 设置矩形的裁切范围
	/// \param rhs 
	virtual void Clip(const Utility::GsRect& rhs);

	/// \brief 设置path作为的裁切范围
	/// \param path 
	virtual void Clip(GsGraphicsPath*  path);

	/// \brief 设置path作为的裁切范围
	/// \param region 
	virtual void Clip(GsRegion *  region);

	/// \brief 获取裁切范围
	/// \return 
	virtual GsRegion* Clip();

	/// \brief 创建一个裁切范围
	/// \param path 
	/// \return 
	virtual GsRegionPtr CreateRegion(GsGraphicsPath*  path)=0;
	/// \brief 创建一个裁切范围
	/// \param rect 
	/// \return 
	virtual GsRegionPtr CreateRegion(const Utility::GsRect& rect)=0;

	/// \brief 一个点是否在画布可见
	/// \param x 
	/// \param y 
	/// \return 
	virtual bool IsVisible(int x,int y);
	/// \brief 一个点是否在画布可见
	/// \param x 
	/// \param y 
	/// \return 
	virtual bool IsVisible(float x,float y);

	/// \brief 一个点是否在画布可见
	/// \param pt 
	/// \return 
	virtual bool IsVisible(Utility::GsPT& pt);
	/// \brief 一个点是否在画布可见
	/// \param pt 
	/// \return 
	virtual bool IsVisible(Utility::GsPTF& pt);

	/// \brief 一个矩形是否在画布中可见
	/// \param rect 
	/// \return 
	virtual bool IsVisible(const Utility::GsRectF& rect);
	/// \brief 一个矩形是否在画布中可见
	/// \param rect 
	/// \return 
	virtual bool IsVisible(const Utility::GsRect& rect);

	/// \brief 一个线段是否在画布中可见
	/// \param x1 
	/// \param y1 
	/// \param x2 
	/// \param y2 
	/// \return 
	virtual bool IsVisible(float x1,float y1,float x2,float y2);
	/// \brief 一个线段是否在画布中可见
	/// \param x1 
	/// \param y1 
	/// \param x2 
	/// \param y2 
	/// \return 
	virtual bool IsVisible(int x1,int y1,int x2,int y2);
	/// \brief 一个点或者一段线是否在画布中可见
	/// \param pt 
	/// \param nPointCount 
	/// \return 
	virtual bool IsVisible(float* pt,int nPointCount);
	/// \brief 一段线是否在画布中可见
	/// \param pt 
	/// \param nPointCount 
	/// \return 
	virtual bool IsVisible(int* pt,int nPointCount);

	/// \brief 获取画布的宽
	/// \return 
	virtual int Width();
	/// \brief 获取画布的高
	/// \return 
	virtual int Height();

	/// \brief 是否可用
	/// \return 
	virtual bool Available();
	/// \brief 设置绘制效果
	/// \param effect 
	virtual void ImageEffect(GsImageEffect* effect);
	/// \brief 绘制效果
	/// \return 
	virtual GsImageEffectPtr ImageEffect();
public:

	/// \brief 绘制一根线段
	/// \param x1 线段的起点x坐标
	/// \param y1 线段的起点y坐标
    /// \param x2 线段的终点x坐标
	/// \param y2 线段的终点y坐标
	/// \param pPen 画笔对象
    /// \return 返回绘制是否成功
	virtual bool DrawLine(float x1,float y1,float x2,float y2,GsPen* pPen);
	
	/// \brief 从文件创建存放于内存中的图像对象
	/// \param strFile 要打开的文件名
	/// \return 返回图像对象
	virtual Utility::GsImagePtr CreateImage(const char* strFile);

	/// \brief 从内存块直接创建图像对象
	/// \param strData 图像的内存块
	/// \param nLen  内存块的长度
	/// \return 返回图像对象
	virtual Utility::GsImagePtr CreateImage(const unsigned char* strData,int nLen) = 0;

	
	/// \brief 创建一个和当前画布兼容的Image画布
	/// \param width 画布的高度
	/// \param height 画布的宽度
	/// \return 
	virtual Utility::GsSmarterPtr<GsImageCanvas> CreateCompatibleImageCanvas(int width,int height) = 0;

public:
	/// \brief 创建画笔对象
	/// \param color 画笔的颜色
	/// \param fWidth 画笔的宽度，像素单位
    /// \returns 返回创建的画笔对象指针
	virtual GsPenPtr CreatePen(const Utility::GsColor& color,float fWidth = 1.0f);
	
	/// \brief 从画刷创建画笔对象
	/// \param pBrush 画刷
	/// \param fWidth 画笔的宽度，像素单位
    /// \returns 返回创建的画笔对象指针
	virtual GsPenPtr CreatePen(GsBrush* pBrush,float fWidth = 1.0f);
	
	/// \brief 创建颜色画刷
	/// \param color 画刷的颜色 
    /// \returns 返回创建的画刷对象指针
	virtual GsSolidBrushPtr CreateSolidBrush(const Utility::GsColor& color) ;
	
	/// \brief 创建纹理画刷
	/// \param pImg 画刷使用的纹理
    /// \returns 返回创建的画刷对象指针
	virtual GsTextureBrushPtr CreateTextureBrush(Utility::GsImage* pImg) ;

	/// \brief 创建颜色线性渐变画刷
	/// \param StartColor 变化开始的颜色
	/// \param EndColor 变化结束的颜色
    /// \returns 返回创建的画刷对象指针
	virtual GsLinearGradientBrushPtr CreateLinearGradientBrush(const Utility::GsColor& StartColor, const Utility::GsColor& EndColor);
	
	/// \brief 创建颜色辐射渐变画刷
	/// \param StartColor 变化开始的颜色
	/// \param EndColor 变化结束的颜色
    /// \returns 返回创建的画刷对象指针
	virtual GsRadialGradientBrushPtr CreateRadialGradientBrush(const Utility::GsColor& StartColor, const Utility::GsColor& EndColor);

	/// \brief 创建路径对象 
    /// \returns 返回创建的路径对象指针
	virtual GsGraphicsPathPtr CreatePath() = 0;
	

	/// \brief 创建字符串格式化话对象
    /// \returns 返回字符串格式化对象
	virtual GsStringFormatPtr CreateStringFormat();
public: 
	/// \brief 绘制多个点连续的线 
	/// \param pCoord 坐标数组指针，以X，Y坐标连续存储
	/// \param nPointCount 坐标点的数量
	/// \param pPen 绘制的画笔
	/// \returns 返回绘制是否成功
	virtual bool DrawLine(float* pCoord,int nPointCount,GsPen* pPen) = 0;
	 
	/// \brief 绘制一段圆弧
	/// \param rect 圆弧所在椭圆的的矩形范围
	/// \param fStartAngle 圆弧开始的角度（单位度）
	/// \param fSweepAngle 圆弧旋转的角度（单位度）
	/// \param pPen 绘制的画笔
	/// \brief 
	/// \return 
	virtual bool DrawArc(const Utility::GsRectF& rect,float fStartAngle,float fSweepAngle,GsPen* pPen);
	 
	/// \brief 绘制一段圆弧
	/// \param rect 圆弧所在椭圆的的矩形范围
	/// \param fStartAngle 圆弧开始的角度（单位度）
	/// \param fSweepAngle 圆弧旋转的角度（单位度）
	/// \param pPen 绘制的画笔
	/// \brief 
	/// \return 
	virtual bool DrawArc(const Utility::GsRect& rect,float fStartAngle,float fSweepAngle,GsPen* pPen);

	/// \brief 绘制椭圆 
	/// \param rect 椭圆的外接矩形范围
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawEllipse(const Utility::GsRectF& rect,GsPen* pPen);
	/// \brief 绘制椭圆 
	/// \param rect 椭圆的外接矩形范围
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawEllipse(const Utility::GsRect& rect,GsPen* pPen);

	 
	/// \brief 填充椭圆 
	/// \param rect 椭圆的外接矩形范围
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillEllipse(const Utility::GsRectF& rect,GsBrush* pBrush);
	 
	/// \brief 填充椭圆 
	/// \param rect 椭圆的外接矩形范围
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillEllipse(const Utility::GsRect& rect,GsBrush* pBrush);

	/// \brief 绘制矩形 
	/// \param rect 矩形范围
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawRectangle(const Utility::GsRect& rect,GsPen* pPen);

	/// \brief 绘制矩形 
	/// \param rect 矩形范围
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawRectangle(const Utility::GsRectF& rect,GsPen* pPen);

	/// \brief 填充矩形 
	/// \param rect 矩形范围
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillRectangle(const Utility::GsRect& rect,GsBrush* pBrush);

	/// \brief 填充矩形 
	/// \param rect 矩形范围
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillRectangle(const Utility::GsRectF& rect,GsBrush* pBrush);

	/// \brief 绘制Pie轮廓
	/// \param rect Pie所在椭圆的外接矩形范围
	/// \param start_angle 饼的开始角度
	/// \param sweepAngle 饼的旋转角度
	/// \param pPen 绘制的画笔
	/// \returns 返回绘制是否成功
	virtual bool DrawPie(const Utility::GsRectF  &rect,float start_angle,float sweepAngle,GsPen* pPen);

	/// \brief 填充Pie
	/// \param rect Pie所在椭圆的外接矩形范围
	/// \param start_angle 饼的开始角度
	/// \param sweepAngle 饼的旋转角度
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillPie(const Utility::GsRectF  &rect,float start_angle,float sweepAngle,GsBrush* pBrush);

	/// \brief 绘制路径 
	/// \param pPath 要绘制的路径
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawPath(GsGraphicsPath* pPath,GsPen* pPen) = 0;
	 
	/// \brief 填充路径 
	/// \param pPath 要填充的路径
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillPath(GsGraphicsPath* pPath,GsBrush* pBrush) = 0;

	/// \brief 绘制一个位图到指定坐标
	/// \param pImg 要绘制的图片
	/// \param pt 图片左上角对应绘制的坐标y坐标 
	/// \param effect 图像处理的效果
	/// \return 返回绘制是否成功
	virtual bool DrawImage(Utility::GsImage* pImg, const Utility::GsPT& pt = Utility::GsPT(), GsImageEffect* effect = NULL);
	 

	/// \brief 绘制图片的特定部分到特定范围 
	/// \param pImg 要绘制的图片
	/// \param source 图片要绘制的范围 
	/// \param target 要绘制到的目标范围
	/// \returns 返回绘制是否成功
	virtual bool DrawImage(Utility::GsImage* pImg,const Utility::GsRect& source,const Utility::GsRectF& target);
	
	/// \brief 绘制图片的特定部分到特定范围 
	/// \param pImg 要绘制的图片
	/// \param source 图片要绘制的范围 
	/// \param target 要绘制到的目标范围
	/// \returns 返回绘制是否成功
	/// \param effect 
	virtual bool DrawImage(Utility::GsImage* pImg, const Utility::GsRect& source, const Utility::GsRectF& target, GsImageEffect* effect);

	/// \brief 用特定颜色清空整个画布  
	/// \param color 要清空的颜色  
	/// \returns 返回绘制是否成功 
	virtual bool Clear(const Utility::GsColor& color) = 0;
	 
	/// \brief 提交未提交的绘制数据   
	/// \returns 返回提交是否成功 
	virtual  bool Flush() = 0;


	/// \brief 绘制字符串
	/// \returns 返回提交是否成功 
	/// \param strText 
	/// \param nLen 
	/// \param pBrush 
	/// \param eLayout 
	/// \param pFormat 
	virtual bool DrawString(const char* strText,int nLen,GsBrush* pBrush,const Utility::GsRectF& eLayout,GsStringFormat* pFormat) = 0;

	/// \brief 绘制字符串
	/// \returns 返回提交是否成功 
	/// \param strText 
	/// \param nLen 
	/// \param pBrush 
	/// \param loc 
	/// \param pFormat 
	virtual bool DrawString(const char* strText,int nLen,GsBrush* pBrush, const Utility::GsPTF& loc,GsStringFormat* pFormat);

	/// \brief 测试字符串绘制的大小
	/// \returns 返回测试是否成功
	/// \param strText 
	/// \param nLen 
	/// \param eLayout 
	/// \param pFormat 
	virtual bool MeasureString(const char* strText,int nLen,Utility::GsRectF& eLayout,GsStringFormat* pFormat);

}; 
/// \brief GsCanvasPtr  
GS_SMARTER_PTR(GsCanvas);

/// \brief 在位图上会绘制的画布  
class GS_API GsImageCanvas:public GsCanvas
{
public:
	/// \brief 获取绘制的位图
	/// \return 
	virtual Utility::GsImage* Image() = 0; 
};
/// \brief GsImageCanvasPtr  
GS_SMARTER_PTR(GsImageCanvas);

/// \brief 基于Cairo渲染引擎的画布
class GS_API GsCairoMemoryImageCanvas :public GsImageCanvas
{
protected:
	Utility::GsImagePtr m_ptrImage;
	void* m_Backend;
	/// \brief 
	/// \param backend 
	GsCairoMemoryImageCanvas(void* backend);
public:

	using GsCanvas::RenderingOrigin;
	using GsCanvas::Clip;
	using GsCanvas::DrawLine;
	using GsCanvas::DrawImage;
	using GsCanvas::DrawString;
	using GsCanvas::CreateImage;
	using GsCanvas::Transform;

	/// \brief 
	/// \param w 
	/// \param h 
	/// \param dpi 
	GsCairoMemoryImageCanvas(int w, int h, float dpi=96.0f);
	/// \brief 
	/// \param w 
	/// \param h 
	/// \param config 
	/// \param dpi 
	GsCairoMemoryImageCanvas(int w, int h,const Utility::GsConfig& config,float dpi = 96.0f);

	virtual ~GsCairoMemoryImageCanvas(); 
	  
	/// \brief 配置对象
	/// \return 
	Utility::GsConfig& Config();
	/// \brief 
	/// \param config 
	void Config(const Utility::GsConfig& config);

	/// \brief 创建纹理画刷
	/// \param pImg 画刷使用的纹理
	/// \returns 返回创建的画刷对象指针
	virtual GsTextureBrushPtr CreateTextureBrush(Utility::GsImage* pImg);

	/// \brief 创建颜色线性渐变画刷
	/// \param StartColor 变化开始的颜色
	/// \param EndColor 变化结束的颜色
	/// \returns 返回创建的画刷对象指针
	virtual GsLinearGradientBrushPtr CreateLinearGradientBrush(const Utility::GsColor& StartColor, const Utility::GsColor& EndColor);

	/// \brief 创建颜色辐射渐变画刷
	/// \param StartColor 变化开始的颜色
	/// \param EndColor 变化结束的颜色
	/// \returns 返回创建的画刷对象指针
	virtual GsRadialGradientBrushPtr CreateRadialGradientBrush(const Utility::GsColor& StartColor, const Utility::GsColor& EndColor);



	/// \brief 获取绘制的位图
	/// \return 
	virtual Utility::GsImage* Image();
	/// \brief 设置仿射变换矩阵
	/// \param rhs 
	virtual void Transform(const GsMatrix& rhs);


	/// \brief 重置仿射变换矩阵为单位矩阵
	virtual void ResetTransform();

	/// \brief 设置绘制起算的原点
	/// \param pt 
	virtual void RenderingOrigin(const Utility::GsPT& pt);

	/// \brief 创建一个裁切范围
	/// \param path 
	/// \return 
	virtual GsRegionPtr CreateRegion(GsGraphicsPath*  path);
	/// \brief 创建一个裁切范围
	/// \param rect 
	/// \return 
	virtual GsRegionPtr CreateRegion(const Utility::GsRect& rect);
	/// \brief 设置path作为的裁切范围
	/// \param region 
	virtual void Clip(GsRegion *  region);
	/// \brief 清除裁切范围
	virtual void ClearClip();

	
	/// \brief 创建一个和当前画布兼容的Image画布
	/// \param width 画布的高度
	/// \param height 画布的宽度
	/// \return 
	virtual GsImageCanvasPtr CreateCompatibleImageCanvas(int width, int height);

	
	/// \brief 绘制多个点连续的线 
	/// \param pCoord 坐标数组指针，以X，Y坐标连续存储
	/// \param nPointCount 坐标点的数量
	/// \param pPen 绘制的画笔
	/// \returns 返回绘制是否成功
	virtual bool DrawLine(float* pCoord, int nPointCount, GsPen* pPen);


	/// \brief 绘制Pie轮廓
	/// \param rect Pie所在椭圆的外接矩形范围
	/// \param start_angle 饼的开始角度
	/// \param sweepAngle 饼的旋转角度
	/// \param pPen 绘制的画笔
	/// \returns 返回绘制是否成功
	virtual bool DrawPie(const Utility::GsRectF  &rect, float start_angle, float sweepAngle, GsPen* pPen);

	/// \brief 填充Pie
	/// \param rect Pie所在椭圆的外接矩形范围
	/// \param start_angle 饼的开始角度
	/// \param sweepAngle 饼的旋转角度
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillPie(const Utility::GsRectF  &rect, float start_angle, float sweepAngle, GsBrush* pBrush);

	/// \brief 
	/// \param rect 
	/// \param pPen 
	/// \return 
	virtual bool DrawRectangle(const Utility::GsRectF& rect, GsPen* pPen);
	/// \brief 
	/// \param rect 
	/// \param pBrush 
	/// \return 
	virtual bool FillRectangle(const Utility::GsRectF& rect, GsBrush* pBrush);

	/// \brief 
	/// \param rect 
	/// \param pPen 
	/// \return 
	virtual bool DrawEllipse(const Utility::GsRectF& rect, GsPen* pPen);
	/// \brief 
	/// \param rect 
	/// \param pBrush 
	/// \return 
	virtual bool FillEllipse(const Utility::GsRectF& rect, GsBrush* pBrush);

	/// \brief 绘制图片的特定部分到特定范围 
	/// \param pImg 要绘制的图片
	/// \param source 图片要绘制的范围 
	/// \param target 要绘制到的目标范围
	/// \returns 返回绘制是否成功
	/// \param effect 
	virtual bool DrawImage(Utility::GsImage* pImg, const Utility::GsRect& source, const Utility::GsRectF& target, GsImageEffect* effect);


	/// \brief 从内存块直接创建图像对象
	/// \param strData 图像的内存块
	/// \param nLen 内存块的长度
	/// \return 返回图像对象
	virtual Utility::GsImagePtr CreateImage(const unsigned char* strData, int nLen);

	/// \brief 创建路径对象 
	/// \returns 返回创建的路径对象指针
	virtual GsGraphicsPathPtr CreatePath();

	/// \brief 绘制路径 
	/// \param pPath 要绘制的路径
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawPath(GsGraphicsPath* pPath, GsPen* pPen);


	/// \brief 填充路径 
	/// \param pPath 要填充的路径
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillPath(GsGraphicsPath* pPath, GsBrush* pBrush);

	/// \brief 绘制圆弧
	/// \param rect 要绘制圆弧的外接矩形
	/// \param dblStartAngle 开始角度
	/// \param fSweepAngle 圆弧旋转的角度（单位度）
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawArc(const Utility::GsRectF& rect, float dblStartAngle, float fSweepAngle, GsPen* pPen);

	/// \brief 用特定颜色清空整个画布  
	/// \param color 要清空的颜色  
	/// \returns 返回绘制是否成功 
	virtual bool Clear(const Utility::GsColor& color);

	/// \brief 提交未提交的绘制数据   
	/// \returns 返回提交是否成功 
	virtual  bool Flush();

	/// \brief 绘制字符串
	/// \returns 返回提交是否成功 
	/// \param strText 
	/// \param nLen 
	/// \param pBrush 
	/// \param eLayout 
	/// \param pFormat 
	virtual bool DrawString(const char* strText, int nLen, GsBrush* pBrush, const Utility::GsRectF& eLayout, GsStringFormat* pFormat);
	/// \brief 
	/// \param strText 
	/// \param nLen 
	/// \param eLayout 
	/// \param pFormat 
	/// \return 
	virtual bool MeasureString(const char* strText, int nLen, Utility::GsRectF &eLayout, GsStringFormat* pFormat);
};
/// \brief GsCairoMemoryImageCanvasPtr  
GS_SMARTER_PTR(GsCairoMemoryImageCanvas);


/// \brief 基于Cairo引擎的内存画布  
class GS_API GsCairoSVGImageCanvas:public GsCairoMemoryImageCanvas
{
	Utility::GsStringStream	m_SS;
	Utility::GsString	m_FileName;
public:
	/// \brief 
	/// \param svgFile 
	/// \param w 
	/// \param h 
	/// \param dpi 
	GsCairoSVGImageCanvas(const char* svgFile,int w, int h, float dpi = 96);
	/// \brief 
	/// \param w 
	/// \param h 
	/// \param dpi 
	GsCairoSVGImageCanvas(int w, int h, float dpi = 96);
	virtual ~GsCairoSVGImageCanvas();
	/// \brief 获取绘制的位图
	/// \return 
	virtual Utility::GsImage* Image();

	/// \brief 获取SVG的字符串
	/// \details 如果是文件svg则返回文件名称
	/// \return 
	Utility::GsString SVG();
};
/// \brief GsCairoSVGImageCanvasPtr  
GS_SMARTER_PTR(GsCairoSVGImageCanvas);



KERNEL_ENDNS