#pragma once
#include "symbol.h"
#include "geometry.h"
#include <qrcode.h>
#include  <mathhelp.h>

KERNEL_NS    
/// \brief 制图线端套类型
enum GsLineCapStyle
{
	eLineCapButt = 512,
	eLineCapRound = 0,
	eLineCapSquare = 256
};

/// \brief 制图线接合类型
enum GsLineJoinStyle
{
	eLineJoinMiter = 8192,
	eLineJoinRound = 0,
	eLineJoinBevel = 4096
};
/// \brief 制图线接合类型
enum GsMirrorType
{
	eMirrorHorizontal = 0,
	eMirrorVertically = 1
};
/// \brief 点符号
class GS_API GsPointSymbol:public GsSymbol, public UTILITY_NAME::GsSerialize
{
protected:
	/// \brief 大小
	double m_dblSize;

	/// \brief 颜色
	Utility::GsColor m_Color;
	/// \brief 旋转角
	double m_dblAngle;

	/// \brief xy的偏移
	GsRawPoint m_Offset;

protected:
	
	/// \brief 当绘制的时候发生
	/// \details 子类通过覆盖此方法实现实际的绘制
	/// \param pBuffer 
	virtual void OnDraw(GsGeometryBlob* pBuffer);

	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	/// \param pScreenPoint 
	/// \param nLen 
	virtual void OnPointDraw(const float* pScreenPoint,int nLen);
	/// \brief 
	virtual void OnPointDraw();
	
	/// \brief 重新计算符号的Size
	void RecalculateSize();

	/// \brief 缺省构造
	GsPointSymbol();
public:
	virtual ~GsPointSymbol();
	/// \brief 符号类型
	/// \return 
	virtual GsSymbolType Type();
	/// \brief 符号大小
	/// \return 
	virtual double Size();
	/// \brief 设置符号大小
	/// \param dblSize 
	virtual void Size(double dblSize);

	/// \brief 符号大小
	/// \return 
	virtual double DesignSize();

	/// \brief 颜色
	/// \return 
	virtual Utility::GsColor Color();
	/// \brief 设置颜色
	/// \param c 
	virtual void Color(const Utility::GsColor& c);

	/// \brief 获取旋转角
	/// \return 
	virtual double Angle();
	/// \brief 设置旋转角
	/// \param angle 
	virtual void Angle(double angle);

	/// \brief x偏移
	/// \return 
	double OffsetX();
	/// \brief y偏移
	/// \return 
	double OffsetY();
	/// \brief x偏移  注意:此处目前内部按像素处理
	/// \param val 
	void OffsetX(double val);
	/// \brief y偏移
	/// \param val 
	void OffsetY(double val);
	/// \brief 偏移
	/// \return 
	GsRawPoint Offset();
	/// \brief 偏移
	/// \param val 
	void Offset(const GsRawPoint& val);
	/// \brief 偏移
	/// \param x 
	/// \param y 
	void Offset(double x,double y);

	/// \brief 点符号的矩形范围
	/// \return 
	virtual GsBox Envelope();

	/// \brief 点符号的镜像
	/// \details 镜像中心,即为实际镜像点相对绘制中心的位置
	/// \param ox 为镜像中心x
	/// \param oy 为镜像中心y
	/// \param type 
	/// \return 
	virtual GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);

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

	DECLARE_CLASS_NAME(GsPointSymbol);

	/// \brief 绘制几何对象
	/// \param pGeo 
	/// \return 
	virtual bool Draw(GsGeometry* pGeo);

};
/// \brief GsPointSymbolPtr
GS_SMARTER_PTR(GsPointSymbol);

/// \brief 简单点符号
class GS_API GsSimplePointSymbol:public GsPointSymbol
{
	GsSolidBrushPtr m_ptrBrush;
protected:

	/// \brief 
	virtual void OnPointDraw();
	
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
public:
	GsSimplePointSymbol();
	/// \brief 从颜色和size构造
	/// \param c 
	/// \param dblSize 
	GsSimplePointSymbol(const Utility::GsColor& c,double dblSize = 1);
	virtual ~GsSimplePointSymbol();
	 
};
GS_SMARTER_PTR(GsSimplePointSymbol);
DECLARE_CLASS_CREATE(GsSimplePointSymbol)

 
/// \brief 面类型的点符号抽象基类
class GS_API GsSurfacePointSymbol:public GsPointSymbol
{
protected:
	GsBrushStyle		m_FillType;
	Utility::GsColor	m_nFillColor;
	float 				m_fLineWidth;
	GsSurfacePointSymbol();
public:
	virtual ~GsSurfacePointSymbol();
	/// \brief 填充的画笔类
	/// \return 
	GsBrushStyle FillType();
	/// \brief 填充的画笔类
	/// \param eType 
	void FillType(GsBrushStyle eType);
	/// \brief 填充的画笔类
	/// \return 
	Utility::GsColor FillColor();
	/// \brief 填充的画笔类
	/// \param c 
	void FillColor(Utility::GsColor c);
	 
	/// \brief 线的宽度
	/// \return 
	float LineWidth();
	/// \brief 
	/// \param fWidth 
	void LineWidth(float fWidth);

};
GS_SMARTER_PTR(GsSurfacePointSymbol);


/// \brief 类椭圆点符号基类
template<class T>
class GsEllipsePointSymbolT:public T
{
protected:
	double m_dblLongAxis, m_dblShortAxis;
	GsEllipsePointSymbolT()
	{
		m_dblLongAxis = 1;
		m_dblShortAxis = 1; 
	}
public:
	virtual ~GsEllipsePointSymbolT(){}
	
	/// \brief 获取椭圆属性
	/// \param longAxis 
	/// \param shortAxis 
	/// \param angle 
	void EllipseParameter(double* longAxis,double* shortAxis,double* angle)
	{
		if(longAxis)
			*longAxis = m_dblLongAxis;
		if(shortAxis)
			*shortAxis = m_dblShortAxis;
		if(angle)
			*angle = this->m_dblAngle;
	}
	/// \brief 设置椭圆属性
	/// \param dblLongAxis 
	/// \param dblShortAxis 
	/// \param dblAngle 
	void EllipseParameter(double dblLongAxis, double dblShortAxis,double dblAngle = 0.0)
	{
		m_dblLongAxis  = dblLongAxis;
		m_dblShortAxis = dblShortAxis;
		this->m_dblAngle = dblAngle;
		//this->m_dblSize = 2* Utility::GsMath::Max(m_dblShortAxis,m_dblLongAxis);
		GsBox pBox = this->Envelope();
		this->m_dblSize = (pBox.Width() > pBox.Height() ? pBox.Width() : pBox.Height());
	}
	/// \brief 获取长轴长度
	/// \return 
	double LongAxis()
	{
		return m_dblLongAxis;
	}
	/// \brief 获取短轴长度
	/// \return 
	double ShortAxis()
	{
		return m_dblShortAxis;
	}
	/// \brief 设置长轴长度
	/// \param val 
	void LongAxis(double val)
	{
		m_dblLongAxis = fabs(val);
		GsBox pBox = this->Envelope();
		this->m_dblSize = (pBox.Width() > pBox.Height() ? pBox.Width() : pBox.Height());
		//this->m_dblSize = 2 * Utility::GsMath::Max(m_dblShortAxis,m_dblLongAxis);
	}
	/// \brief 设置短轴长度
	/// \param val 
	void ShortAxis(double val)
	{
		m_dblShortAxis = fabs(val);
		//this->m_dblSize = 2 * Utility::GsMath::Max(m_dblShortAxis,m_dblLongAxis);
		GsBox pBox = this->Envelope();
		this->m_dblSize = (pBox.Width() > pBox.Height() ? pBox.Width() : pBox.Height());
	}
	/// \brief 获取符号大小
	/// \return 
	virtual double Size()
	{ 
		//this->m_dblSize = 2 * Utility::GsMath::Max(m_dblShortAxis,m_dblLongAxis); 
		GsBox pBox = this->Envelope();
		this->m_dblSize = (pBox.Width() > pBox.Height() ? pBox.Width() : pBox.Height());
		return this->m_dblSize;
	}
	/// \brief 设置符号大小
	/// \param dblSize 
	virtual void Size(double dblSize)
	{
		if(dblSize <=0 || Utility::GsMath::IsEqual(dblSize,this->m_dblSize))
			return;
		double dblScale = dblSize / this->m_dblSize;
		m_dblLongAxis*=dblScale;
		m_dblShortAxis*=dblScale;

		T::Size(dblSize);
	}

	/// \brief 点符号的矩形范围
	/// \return 
	virtual GsBox Envelope()
	{
		GsBox env(-m_dblLongAxis,-m_dblShortAxis,m_dblLongAxis,m_dblShortAxis);
		//旋转
		if(fabs(this->m_dblAngle) > DBL_EPSILON)
		{
			env.Set(0,0,0,0);
			//包围盒GsBox的4个角点坐标,逆时针顺序
			double f[8] = { -m_dblLongAxis,-m_dblShortAxis,
				m_dblLongAxis,-m_dblShortAxis,
				m_dblLongAxis,m_dblShortAxis,
				-m_dblLongAxis,m_dblShortAxis, };
			GsMatrix mat;
			mat.Translate(this->m_Offset.X, this->m_Offset.Y);
			mat.Rotate(Utility::GsMath::ToRadian(this->m_dblAngle));
			mat.TransformPointsT(f, 4);
			//Union从左向右延伸的两个Box,保证同向
			env.Union(GsBox(f[0], f[1], f[2], f[3]));
			env.Union(GsBox(f[6], f[7], f[4], f[5]));
		}
		else
			env.Offset(this->m_Offset.X, this->m_Offset.Y);
		return env;
	}
}; 

/// \brief 椭圆的点符号。
class GS_API GsEllipsePointSymbol:public GsEllipsePointSymbolT<GsSurfacePointSymbol>
{
	GsSolidBrushPtr m_ptrBrush;
	GsPenPtr m_ptrPen;
protected:	
	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
	
public:
	GsEllipsePointSymbol();
	/// \brief 
	/// \param dblLongAxis 
	/// \param dblShortAxis 
	/// \param dblAngle 
	GsEllipsePointSymbol(double dblLongAxis, double dblShortAxis, double dblAngle = 0.0);
	~GsEllipsePointSymbol();
};
/// \brief GsEllipsePointSymbolPtr
GS_SMARTER_PTR(GsEllipsePointSymbol);
DECLARE_CLASS_CREATE(GsEllipsePointSymbol)

/// \brief pie符号
class GS_API GsPiePointSymbol:public GsEllipsePointSymbolT<GsSurfacePointSymbol>
{
	GsPenPtr m_ptrPen;
	GsSolidBrushPtr	m_ptrBrush; 
	double               m_StartAngle;       //弦形起始角
	double               m_EndAngle;         //弦形终止角
protected:
	/// \brief 
	virtual void OnPointDraw();

	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
public:
	GsPiePointSymbol();
	virtual ~GsPiePointSymbol();
	   
	/// \brief 设置Pie开始角度
	/// \param angle 
	void StartAngle(double angle);
	/// \brief 获取Pie开始角度
	/// \return 
	double StartAngle();
	/// \brief 设置Pie结束角度
	/// \param angle 
	void EndAngle(double angle);
	/// \brief 获取Pie结束角度
	/// \return 
	double EndAngle(); 
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);
};
/// \brief GsPiePointSymbolPtr
GS_SMARTER_PTR(GsPiePointSymbol);
DECLARE_CLASS_CREATE(GsPiePointSymbol)


/// \brief 线的点符号。
class GS_API GsLinePointSymbol:public GsPointSymbol
{
	GsPenPtr m_ptrPen;
	double m_dblWidth;
	GsRawPoint m_StartPoint, m_EndPoint;
	float m_Line[4];
	GsLineCapStyle     m_CapStyle;     //符号端套类型
	GsLineJoinStyle    m_JoinStyle;     //线段接头类型
	double               m_dblMiterLimit;	  //线端斜面接合限值属性
protected:	
	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();

public:
	/// \brief 默认构造函数
	GsLinePointSymbol();
	/// \brief 从颜色和线宽构造
	/// \param color 
	/// \param dblWidth 
	GsLinePointSymbol(const Utility::GsColor& color,double dblWidth);
	virtual ~GsLinePointSymbol();

	/// \brief 设置LinePoint的起点坐标
	/// \param x 
	/// \param y 
	void StartPoint(double x, double y);
	/// \brief 获取LinePoint的起点
	/// \return 
	GsRawPoint StartPoint();

	/// \brief 设置LinePoint的终点坐标
	/// \param x 
	/// \param y 
	void EndPoint(double x, double y);
	/// \brief 获取LinePoint的终点
	/// \return 
	GsRawPoint EndPoint();

	/// \brief 设置线宽度
	/// \param dblWidth 
	void Width(double dblWidth);
	/// \brief 获取线宽度
	/// \return 
	double Width();

	/// \brief 符号大小
	/// \return 
	virtual double Size();
	/// \brief 设置符号大小
	/// \param dblSize 
	virtual void Size(double dblSize);

	/// \brief 点符号的矩形范围
	/// \return 
	virtual GsBox Envelope();
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
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);

};
/// \brief GsLinePointSymbolPtr
GS_SMARTER_PTR(GsLinePointSymbol);
DECLARE_CLASS_CREATE(GsLinePointSymbol)


/// \brief 支持多个点构成曲线、曲线面的点符号模板基类
template<class T>
class GS_API GsCurvePointSymbolT:public T
{
protected:
	UTILITY_NAME::GsVector<GsRawPoint> m_vecPoints;
public:
	
	/// \brief 获取节点类型数组
	/// \param vecPoints 
	void CurvePoints(UTILITY_NAME::GsVector<GsRawPoint> &vecPoints)
	{
		if(vecPoints.empty())
			vecPoints = m_vecPoints;
		else
			m_vecPoints = vecPoints;

	}
	/// \brief 获取的节点类型数组
	/// \return 
	UTILITY_NAME::GsVector<GsRawPoint>  CurvePoints()
	{
		return m_vecPoints;
	}
	
	/// \brief 设置点
	/// \param pPoint 
	/// \param nCount 
	void CurvePoints(GsRawPoint* pPoint,int nCount)
	{
		m_vecPoints.clear();
		if(!pPoint  || nCount <=0)
			return;
		m_vecPoints.insert(m_vecPoints.begin(),pPoint,pPoint+ nCount);
		GsPointSymbol::RecalculateSize();
	}

	/// \brief 设置符号大小
	/// \param dblSize 
	virtual void Size(double dblSize)
	{
		if(dblSize <=0 || Utility::GsMath::IsEqual(dblSize,this->m_dblSize))
			return;
		double dblScale = dblSize / this->m_dblSize;

		for(int i = 0;i<m_vecPoints.size();i++)
		{ 
			//计算resize后polygon上的点
			m_vecPoints[i].X = m_vecPoints[i].X * dblScale;
			m_vecPoints[i].Y = m_vecPoints[i].Y * dblScale; 
		}
		this->m_Offset.X *= dblScale;
		this->m_Offset.Y *= dblScale;
		this->m_dblSize = dblSize;
	}
	/// \brief 获取符号大小
	/// \return 
	virtual double Size()
	{
		return this->m_dblSize;
	}

	/// \brief 符号的矩形范围
	/// \return 
	virtual GsBox Envelope()
	{
		GsBox env;
		if (m_vecPoints.empty())
			return env;

		GsMatrix mat;
		mat.Rotate(this->m_dblAngle * Utility::GsMath::Pi() / 180);
		float f[2];
		Utility::GsVector<GsRawPoint>::iterator it = m_vecPoints.begin();
		for(; it != m_vecPoints.end(); ++it)
		{
			f[0] = it->X;
			f[1] = it->Y;
			//角度大于0才做矩阵乘法，否则效率太低了
			if(fabs(this->m_dblAngle) > DBL_EPSILON)
				mat.TransformPointsT(f,1);

			env.Union(GsBox(f[0],f[1],f[0],f[1]));
		}
		GsMatrix mat1;
		mat1.Translate(this->m_Offset.X, this->m_Offset.Y);
		mat1.Rotate(this->m_dblAngle * Utility::GsMath::Pi() / 180);
		env.Offset(mat1.OffsetX(), mat1.OffsetY());
		return env;
	}

	/// \brief 
	/// \param ox 
	/// \param oy 
	/// \param type 
	/// \param vec 
	void PointsMirror(double ox, double oy, GsMirrorType type, UTILITY_NAME::GsVector<GsRawPoint>& vec)
	{
		double c = 1, s = 0;
		if (this->m_dblAngle!=0)
		{
			double angle = this->m_dblAngle / 180 * Utility::GsMath::Pi();
			c = cos(angle), s = sin(angle);
		}

		UTILITY_NAME::GsVector<GsRawPoint>::iterator it = m_vecPoints.begin();
		double x, y, px, py;
		switch (type)
		{
		case eMirrorHorizontal:
			for (; it != m_vecPoints.end(); ++it)
			{
				x = it->X;
				y = it->Y;
				px = c*x - s*y + this->m_Offset.X;
				py = s*x + c*y + this->m_Offset.Y;
				px = 2 * ox - px;
				GsRawPoint p(px, py);
				vec.push_back(p);
			}
			break;
		case eMirrorVertically:
			for (; it != m_vecPoints.end(); ++it)
			{
				x = it->X;
				y = it->Y;
				px = c*x - s*y + this->m_Offset.X;
				py = s*x + c*y + this->m_Offset.Y;
				py = 2 * oy - py;
				GsRawPoint p(px, py);
				vec.push_back(p);
			}
			break;
		default:
			break;
		}
	}
};
/// \brief 曲线点符号
class GS_API GsCurvelinePointSymbol : public GsCurvePointSymbolT<GsPointSymbol>
{
	GsPenPtr             m_ptrPen;
	GsGraphicsPathPtr    m_ptrGraphicsPath;
	double               m_dblWidth;

protected:
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
	/// \brief 
	virtual void OnPointDraw();
public:
	GsCurvelinePointSymbol();
	/// \brief 
	/// \param vec 
	GsCurvelinePointSymbol(UTILITY_NAME::GsVector<GsRawPoint>& vec);
	/// \brief 
	/// \param vec 
	/// \param c 
	GsCurvelinePointSymbol(UTILITY_NAME::GsVector<GsRawPoint>& vec,const Utility::GsColor& c);
	virtual ~GsCurvelinePointSymbol();
	 
	/// \brief 获取线宽度
	/// \return 
	double Width();
	/// \brief 设置线宽度
	/// \param dblWidth 
	void Width(double dblWidth);
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);
};
GS_SMARTER_PTR(GsCurvelinePointSymbol);
DECLARE_CLASS_CREATE(GsCurvelinePointSymbol);

/// \brief 面点符号
class GS_API GsPolygonPointSymbol:public GsCurvePointSymbolT<GsSurfacePointSymbol>
{
	GsGraphicsPathPtr m_ptrPath; 
	GsSolidBrushPtr m_ptrBrush;
	GsPenPtr m_ptrPen;

protected:
	/// \brief 
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
public:
	GsPolygonPointSymbol();

	/// \brief 从颜色和size构造
	/// \param vec 
	/// \param c 
	GsPolygonPointSymbol(UTILITY_NAME::GsVector<GsRawPoint>& vec,const Utility::GsColor& c);
	/// \brief 
	/// \param pts 
	/// \param nCount 
	/// \param c 
	GsPolygonPointSymbol(GsRawPoint* pts,int nCount,const Utility::GsColor& c);
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);
	virtual ~GsPolygonPointSymbol();
};
GS_SMARTER_PTR(GsPolygonPointSymbol);
DECLARE_CLASS_CREATE(GsPolygonPointSymbol);

/// \brief 圆弧点符号
class GS_API GsArcPointSymbol:public GsEllipsePointSymbolT<GsPointSymbol>
{
	double		m_dblStartAngle;
	double		m_dblEndAngle;
	float		m_fLineWidth;
	GsPenPtr	m_ptrPen;
protected:	
	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();

public:
	GsArcPointSymbol();
	/// \brief 
	/// \param dblStartAngle 
	/// \param dblEndAngle 
	GsArcPointSymbol(double dblStartAngle, double dblEndAngle);
	~GsArcPointSymbol();
	/// \brief 截取圆中arc的起始角度
	/// \return 
	double StartAngle();

	/// \brief 截取圆中arc的终止角度
	/// \return 
	double EndAngle();

	/// \brief 设置截取圆中arc的起始角度
	/// \param dblStartAngle 
	void StartAngle(double dblStartAngle);
	
	/// \brief 设置截取圆中arc的终止角度
	/// \param dblEndAngle 
	void EndAngle(double dblEndAngle);

	/// \brief 符号的线宽
	/// \return 
	float LineWidth();

	/// \brief 设置符号的线宽
	/// \param linewidth 
	void LineWidth(float linewidth);
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);

};
/// \brief GsArcPointSymbolPtr
GS_SMARTER_PTR(GsArcPointSymbol);
DECLARE_CLASS_CREATE(GsArcPointSymbol);

/// \brief 星形的类型
enum GsAsteriskType
{
	/// \brief 普通型
	eAsteristkOrdination,
	/// \brief 交叉型
	eAsteristkCross,
	/// \brief 内接型
	eAsteristkInternal,
	/// \brief 辐射型
	eAsteristkRadiation,
}; 
/// \brief 星形点符号
class GS_API GsAsteriskPointSymbol:public GsEllipsePointSymbolT<GsSurfacePointSymbol>
{
	/// \brief 边线
	GsPenPtr m_ptrPen;
	/// \brief 填充
	GsSolidBrushPtr	m_ptrBrush; 

	/// \brief 类型
	GsAsteriskType      m_Asterisk;
	/// \brief 角数量
	int                  m_nCorners;

	/// \brief 比例
	double               m_rate;
	/// \brief 开始外交
	double               m_InterStartAngle; 
	/// \brief 开始内角
	double               m_InnerStartAngle; 
	 
	/// \brief 星形路径
	GsGraphicsPathPtr	 m_ptrPath;
protected:
	/// \brief 绘制点
	virtual void OnPointDraw();

	/// \brief 符号开始绘制
	virtual void OnStartDrawing();
	/// \brief 符号结束绘制
	virtual void OnEndDrawing();

public:
	GsAsteriskPointSymbol();
	~GsAsteriskPointSymbol(); 

	/// \brief 获取比例
	/// \return 
	double Rate ();
    /// \brief 设置比例
	/// \param pRation 
	void Rate (double pRation );
	/// \brief 获取星型的类型
	/// \return 
	GsAsteriskType AsterType ();
    /// \brief 设置星型的类型
	/// \param eType 
	void AsterType (GsAsteriskType eType);
    /// \brief 获取星型角的数量
	/// \return 
	int Corners ();
	/// \brief 设置星型角的数量
	/// \param nVal 
	void Corners (int nVal);
    
	/// \brief 获取外角的开始角度
	/// \return 
	double InterStartAngle ();
	/// \brief 设置外角的开始角度
	/// \param dAngle 
	void InterStartAngle (double dAngle);
	
	/// \brief 获取内角的开始角度
	/// \return 
	double InnerStartAngle ();
	/// \brief 设置内角的开始角度
	/// \param dAngle 
	void InnerStartAngle (double dAngle);  
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);
};
/// \brief GsAsteriskPointSymbolPtr
GS_SMARTER_PTR(GsAsteriskPointSymbol);
DECLARE_CLASS_CREATE(GsAsteriskPointSymbol)
/// \brief 弦点符号
class GS_API GsChordPointSymbol:public GsEllipsePointSymbolT<GsSurfacePointSymbol>
{
	double		m_dblStartAngle;
	double		m_dblEndAngle; 
	GsPenPtr	m_ptrPen;
	GsSolidBrushPtr m_ptrBrush;
	GsGraphicsPathPtr m_ptrPath;

protected:	
	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();

public:
	GsChordPointSymbol();
	/// \brief 
	/// \param dblStartAngle 
	/// \param dblEndAngle 
	GsChordPointSymbol(double dblStartAngle, double dblEndAngle);
	~GsChordPointSymbol();
	 
   /// \brief 截取圆中arc的起始角度
	/// \return 
	double StartAngle();

    /// \brief 设置开始角度
	/// \param pAngle 
	void StartAngle (double pAngle );
    /// \brief 获取结束角度
	/// \return 
	double EndAngle ();
    /// \brief 设置结束角度
	/// \param pAngle 
	void EndAngle (double pAngle );

	/// \brief 设置符号大小,跟据设置的大小，调整长短轴
	/// \param dblSize 
	virtual void Size(double dblSize);
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);
};
/// \brief GsChordPointSymbolPtr
GS_SMARTER_PTR(GsChordPointSymbol);
DECLARE_CLASS_CREATE(GsChordPointSymbol);

/// \brief 由贝塞尔曲线构成的面点符号
class GS_API GsCurvegonPointSymbol:public GsCurvePointSymbolT<GsSurfacePointSymbol>
{ 
	GsPenPtr             m_ptrPen;
	GsGraphicsPathPtr    m_ptrGraphicsPath;
	GsSolidBrushPtr      m_ptrBrush;
public:
	GsCurvegonPointSymbol();
	/// \brief 
	/// \param vec 
	GsCurvegonPointSymbol(UTILITY_NAME::GsVector<GsRawPoint>& vec);
	/// \brief 
	/// \param vec 
	/// \param c 
	GsCurvegonPointSymbol(UTILITY_NAME::GsVector<GsRawPoint>& vec,const Utility::GsColor& c);
	~GsCurvegonPointSymbol();
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);
protected:
	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
};
/// \brief GsCurvegonPointSymbolPtr
GS_SMARTER_PTR(GsCurvegonPointSymbol);
DECLARE_CLASS_CREATE(GsCurvegonPointSymbol)

/// \brief 锁定类型
enum GsPictureKeepOrigin
{
    ePictureNoKeep,
	ePictureKeepWidth,
	ePictureKeepHeight,
	ePictureKeepAll= 255,
};

/// \brief 图片点符号
class GS_API GsPicturePointSymbol:public GsPointSymbol
{
	/// \brief 是否使用透明色
	bool m_bTrans;
	/// \brief 要透明的颜色
	Utility::GsColor m_TransColor;
	/// \brief 是否使用背景色
	bool m_bUseBackColor;
	/// \brief 背景色
	Utility::GsColor m_BackColor;
	/// \brief 宽度
	double m_dblWidth;
	/// \brief 高度
	double m_dblHeight;
	/// \brief 矩形框
	Utility::GsRectF m_Rect;
	/// \brief 锁定类型
	GsPictureKeepOrigin m_OriginalState;
	/// \brief 图片对象
	Utility::GsImagePtr m_ptrImage,m_ptrImageDrawing;
	/// \brief 图片的真实数据
	Utility::GsGrowByteBuffer m_ImageData;
	/// \brief 画刷
	GsSolidBrushPtr m_ptrBrush;

	/// \brief x方向上的间隔
	double m_IntervalX;
	/// \brief y方向上的间隔
	double m_IntervalY;
	Utility::GsSVGImage::svgDrawParams m_svgDrawParams;
protected:

	/// \brief 
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();

	/// \brief 点符号的矩形范围
	/// \return 
	virtual GsBox Envelope();

	/// \brief 处理透明色
	void ProcessTransparentColor();
public:
	/// \brief 无参构造函数
	GsPicturePointSymbol();
	/// \brief 路径导入图片构造函数
	/// \param strFileName 
	GsPicturePointSymbol(const char* strFileName);
	
	/// \brief 
	/// \param pBlob 
	/// \param nLen 
	GsPicturePointSymbol(const unsigned char* pBlob, int nLen);

	/// \brief 获取是否使用透明色
	/// \return 
	bool Transparent ();
    /// \brief 设置是否使用透明色
	/// \param bTrans 
	void Transparent (bool bTrans);
    /// \brief 获取要透明的颜色
	/// \return 
	Utility::GsColor TransparentColor ();
    /// \brief 设置要透明的颜色
	/// \param color 
	void TransparentColor (const Utility::GsColor& color);
	
	/// \brief 获取是否使用背景色
	/// \return 
	bool UseBackColor ();
	/// \brief 设置是否使用背景色
	/// \param bUse 
	void UseBackColor (bool bUse);
	/// \brief 获取背景色
	/// \return 
	Utility::GsColor BackColor ();
	/// \brief 设置背景色
	/// \param color 
	void BackColor (const Utility::GsColor& color);
	
	/// \brief 获取图片对象
	/// \return 
	Utility::GsImage* Picture ();
	/// \brief 获取图片的数据
	/// \return 
	Utility::GsGrowByteBuffer* PictureData ();
	/// \brief 设置图片对象
	/// \param pImage 
	void Picture(Utility::GsImage* pImage);
	/// \brief 获取图片宽度(单位毫米)
	/// \return 
	double Width ();
	/// \brief 设置图片宽度(单位毫米)
	/// \param dblWidth 
	void Width (double dblWidth);
	
	/// \brief 获取图片高度(单位毫米)
	/// \return 
	double Height();
	/// \brief 设置图片高度(单位毫米)
	/// \param dblHeight 
	void Height(double dblHeight);

	/// \brief 
	/// \param params 
	void SvgDrawParams(Utility::GsSVGImage::svgDrawParams& params);
	/// \brief 
	/// \return 
	Utility::GsSVGImage::svgDrawParams& SvgDrawParams();
	/// \brief 获取图片锁定状态
	/// \return 
	GsPictureKeepOrigin OriginalState ();
	/// \brief 设置图片锁定状态
	/// \param eState 
	void OriginalState (GsPictureKeepOrigin  eState);
	
	/// \brief 从文件载入图片
	/// \param strFileName 
	/// \return 
	bool LoadPicture (const char* strFileName);
    /// \brief 从内存块载入图片。
	/// \param pBlob 
	/// \param nLen 
	/// \return 
	bool LoadPicture(const unsigned char* pBlob,int nLen);

	/// \brief x方向上间隔
	/// \param dVal 
	virtual void XSeparation(double dVal);
	/// \brief x方向上间隔
	/// \return 
	virtual double XSeparation();
	/// \brief y方向上间隔
	/// \param dVal 
	virtual void YSeparation(double dVal);
	/// \brief y方向上间隔
	/// \return 
	virtual double YSeparation();
	/// \brief 获取符号大小
	/// \param dblSize 
	virtual double Size();
	/// \brief 设置符号大小
	/// \param dblSize 
	virtual void Size(double dblSize);
};
/// \brief GsPicturePointSymbolPtr
GS_SMARTER_PTR(GsPicturePointSymbol);
DECLARE_CLASS_CREATE(GsPicturePointSymbol);

/// \brief 折线点符号
class GS_API GsPolylinePointSymbol:public GsCurvePointSymbolT<GsPointSymbol>
{
	GsGraphicsPathPtr m_ptrPath; 
	GsPenPtr m_ptrPen;
	double m_dblWidth;

protected:
	/// \brief 
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
public:
	GsPolylinePointSymbol();

	/// \brief 从颜色和size构造
	/// \param vec 
	/// \param c 
	GsPolylinePointSymbol(UTILITY_NAME::GsVector<GsRawPoint>& vec,const Utility::GsColor& c);
	/// \brief 
	/// \param pts 
	/// \param nCount 
	/// \param c 
	GsPolylinePointSymbol(GsRawPoint* pts,int nCount,const Utility::GsColor& c);

	virtual ~GsPolylinePointSymbol();
	/// \brief 获取折线点的宽度
	/// \return 
	double Width ();

	/// \brief 设置折线点的宽度
	/// \param dblWidth 
	void Width (double dblWidth);
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);
};
/// \brief GsPolylinePointSymbolPtr
GS_SMARTER_PTR(GsPolylinePointSymbol);
DECLARE_CLASS_CREATE(GsPolylinePointSymbol);


/// \brief 矩形点符号
class GS_API GsRectanglePointSymbol:public GsEllipsePointSymbolT<GsSurfacePointSymbol>
{
private: 
	GsSolidBrushPtr m_ptrBrush;
	GsPenPtr m_ptrPen;
	Utility::GsRectF m_SymRect;
public:
	GsRectanglePointSymbol();
	/// \brief 
	/// \param width 
	/// \param height 
	/// \param angle 
	GsRectanglePointSymbol(double width, double height, double angle = 0.0); 
protected:	
	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();


};
/// \brief GsRectanglePointSymbolPtr
GS_SMARTER_PTR(GsRectanglePointSymbol);
DECLARE_CLASS_CREATE(GsRectanglePointSymbol);

/// \brief 文本点符号
class GS_API GsTextPointSymbol:public GsEllipsePointSymbolT<GsSurfacePointSymbol>
{
private: 
	GsItalic  m_pItalic;          //倾斜类型
	bool m_bBold;                 //加粗标识
	bool m_Stroke;                //空心标识
	Utility::GsString  m_strFont; //字体
	Utility::GsString  m_strText; //字符内容
	Utility::GsPTF m_Loc;                  //绘制范围
	GsSolidBrushPtr m_ptrBrush;   //画刷
	GsPenPtr m_ptrPen;
	GsPenPtr m_ptrHaloPen;			//光晕画笔
	GsStringFormatPtr m_ptrStrf;   //字符的stringformat
	GsGraphicsPathPtr m_ptrPath;  //绘制轮廓用字体path
	GsMatrix			m_Matrix;
public:
	GsTextPointSymbol();
	/// \brief 
	/// \param width 
	/// \param height 
	/// \param angle 
	GsTextPointSymbol(double width, double height, double angle = 0.0); 

	/// \brief 
	/// \param pItalic 
	/// \param bBold 
	/// \param bStroke 
    void TextFlag (GsItalic* pItalic,bool *bBold,bool* bStroke);
	/// \brief 
	/// \param pItalic 
	/// \param bBold 
	/// \param bStroke 
	void TextFlag (GsItalic pItalic,bool bBold,bool bStroke);

	/// \brief 获取字体
	/// \return 
	Utility::GsString  Font ();
	/// \brief 设置字体
	/// \param strFont 
	void Font (const char* strFont);
	
	/// \brief 获取字符内容
	/// \return 
	Utility::GsString Text ();
	/// \brief 设置字符内容
	/// \param strText 
	void Text(const char* strText);
	 
	/// \brief 设置加粗标识
	/// \param bBold 
	void Bold(bool bBold);
	/// \brief 获取加粗标识
	/// \return 
	bool Bold();

	/// \brief 设置空心标识
	/// \param mStroke 
	void Stroke(bool mStroke);
	/// \brief 获取空心标识
	/// \return 
	bool Stroke();
	 
	/// \brief 设置倾斜类型
	/// \param pItalic 
	void Italic(GsItalic pItalic);
	/// \brief 获取倾斜类型
	/// \return 
	GsItalic Italic();
protected:	
	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();

};
/// \brief GsTextPointSymbolPtr
GS_SMARTER_PTR(GsTextPointSymbol); 
DECLARE_CLASS_CREATE(GsTextPointSymbol) 



/// \brief 二维码点符号
class GS_API GsQRCodePointSymbol:public GsPointSymbol
{
	Utility::GsGrowByteBuffer	m_Buffer;
	Utility::GsGrowByteBuffer	m_CenterImage;
	Utility::GsImagePtr			m_ptrImage;
	Utility::GsQRCode			m_QRCode;
	GsImageCanvasPtr			m_ptrQRImage;
	int							m_nPageIndex;

	Utility::GsQRCodeDataType	m_eCodeDataType;
	double						m_dblBorderSize;
	double						m_dblRatio;
	Utility::GsColor			m_BKColor;
protected:	
	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();
public:
	GsQRCodePointSymbol();
	/// \brief 
	/// \param pData 
	/// \param nLen 
	GsQRCodePointSymbol(unsigned char* pData,int nLen);
	
	/// \brief 获取二维码边框留白的大小
	/// \return 
	double BorderSize ();
	/// \brief 设置二维码边框留白的大小
	/// \param size 
	void BorderSize (double size);

	/// \brief 获取二维码编码对象
	/// \return 
	Utility::GsQRCode* QRCodePtr();
	 
	/// \brief 多个二维码编码对象时编码某个页面
	/// \return 
	int PageIndex();
	/// \brief 多个二维码编码对象时编码某个页面
	/// \param nIndex 
	void PageIndex(int nIndex);

	/// \brief 置于二维码中心的标示图片
	/// \return 
	Utility::GsImagePtr LogoPicture();
	/// \brief 
	/// \param pImg 
	void LogoPicture(Utility::GsImage* pImg);
	
	/// \brief 二维码中心图片占用的比率
	/// \details 介于0.1~0.3之间，过大会遮挡过多二维码导致无法识别，过小中心图片看不清
	/// \return 
	double LogoPictureRatio();

	/// \brief 二维码中心图片占用的比率
	/// \param dblRatio 
	void LogoPictureRatio(double dblRatio);
	
	/// \brief 背景颜色
	/// \return 
	Utility::GsColor BackColor();
	/// \brief 背景颜色
	/// \param color 
	void BackColor(const Utility::GsColor& color);


	/// \brief 置于二维码中心的图片数据
	/// \return 
	Utility::GsGrowByteBuffer* LogoPictureData();
	
	/// \brief 二维码显示的原始数据
	/// \return 
	Utility::GsByteBuffer* QRData();
	/// \brief 设置任意二进制的数据
	/// \param pData 
	/// \param nLen 
	void QRData(const unsigned char* pData,int nLen);
	
	/// \brief 设置字符串的数据
	/// \param str 
	void QRData(const char* str);
	
	/// \brief 获取数据的类型
	/// \return 
	Utility::GsQRCodeDataType  DataType();


};
/// \brief GsQRCodePointSymbol
GS_SMARTER_PTR(GsQRCodePointSymbol); 
DECLARE_CLASS_CREATE(GsQRCodePointSymbol) 



/// \brief 复合点符号
class GS_API GsMultiPointSymbol:public GsMultiSymbolT<GsPointSymbol>
{
	bool m_IsDirectionPoint;
public:
	GsMultiPointSymbol();
	/// \brief 符号大小
	/// \return 
	virtual double Size();
	/// \brief 设置符号大小
	/// \param dblSize 
	virtual void Size(double dblSize);

	/// \brief 颜色
	/// \return 
	virtual Utility::GsColor Color();
	/// \brief 设置颜色
	/// \param c 
	virtual void Color(const Utility::GsColor& c);

	/// \brief 获取旋转角
	/// \return 
	virtual double Angle();
	/// \brief 设置旋转角
	virtual	void Angle(double angle);

	/// \brief x偏移
	/// \param val 
	void OffsetX(double val);
	/// \brief y偏移
	/// \param val 
	void OffsetY(double val);
	/// \brief 偏移
	/// \param val 
	void Offset(const GsRawPoint& val);

	/// \brief 点符号的矩形范围
	/// \return 
	virtual GsBox Envelope();

	//IPointSymbolProp
	/// \brief 
	/// \param isDirP 
	void IsDirectionPoint(bool isDirP);
	/// \brief 
	/// \return 
	bool IsDirectionPoint();

	/// \brief Multi符号外框的大小
	/// \return 
	double MultiSize();


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

	/// \brief 绘制画布坐标系下的几何对象
	/// \param pGeo 
	/// \param pBuffer 
	/// \return 
	virtual bool DrawGraphics(GsGraphicsGeometry* pGeo, GsGeometryBlob* pBuffer);
	/// \brief 点符号的镜像
	/// \param ox 镜像中心x
	/// \param oy 镜像中心y
	/// \param type 
	/// \return 
	GsSymbolPtr Mirror(double ox, double oy, GsMirrorType type);

};
/// \brief GsMultiPointSymbolPtr
GS_SMARTER_PTR(GsMultiPointSymbol);
DECLARE_CLASS_CREATE(GsMultiPointSymbol)

enum ScriptType
{
	Lua = 0,
	Python = 1
};
/// \brief 脚本化的点符号。
class GS_API GsScriptPointSymbol :public GsPointSymbol
{
	Utility::GsString m_strStartDrawingScript;
	Utility::GsString m_strEndDrawingScript;
	Utility::GsString m_strDrawScript;
	GsRefObject*	m_pScriptEngine;
	GsPointPtr		m_ptrPoint;
protected:
	/// \brief 当绘制点的时候发生
	/// \details 子类通过覆盖此函数实现点的绘制。基类已经实现了地理坐标到屏幕坐标的转换
	virtual void OnPointDraw();
	/// \brief 
	virtual void OnStartDrawing();
	/// \brief 
	virtual void OnEndDrawing();

public:
	
	/// \brief 缺省构造
	GsScriptPointSymbol();
	//\brief 构造
	GsScriptPointSymbol(ScriptType type);

	virtual ~GsScriptPointSymbol();
	
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
	void Init(ScriptType type);

};

/// \brief GsScriptPointSymbolPtr
GS_SMARTER_PTR(GsScriptPointSymbol);
DECLARE_CLASS_CREATE(GsScriptPointSymbol)

KERNEL_ENDNS