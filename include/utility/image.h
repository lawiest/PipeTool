#pragma once
#include "preconfig.h" 
#include "object.h"
#include "memorymanager.h" 
#include "vectorhelp.h"
#include <fstream>
#include "structreflect.h"
#include "configuration.h"
UTILITY_NS 

/// \brief 颜色对象
struct  GS_API GsColor
{
	/// \brief 缺省构造
	GsColor();
	/// \brief 根据32位整数构造
	/// \param c 
	GsColor(unsigned int c);
	/// \brief 根据32位整数构造
	/// \param c 
	GsColor(int c);

	/// \brief 根据R，G，B，A通道构造
	/// \param r 红色通道[0,255]
	/// \param g 绿色通道[0,255]
	/// \param b 蓝色通道[0,255]
	/// \param a 透明通道[0,255]
	GsColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

	/// \brief 拷贝构造
	/// \param rhs 
	GsColor(const GsColor& rhs);
	/// \brief 改变透明度构造已有颜色
	/// \param rhs 
	/// \param a 
	GsColor(const GsColor& rhs, unsigned char a);

	/// \brief 交换RGB中R和B的通道
	void FlipRGB();

	/// \brief 从CSS颜色描述构造
	/// \param csscolor 
	/// \return 
	static GsColor FromCSS(const char* csscolor);

	/// \brief 从Win32的RGB颜色构造
	/// \param rgb 
	/// \return 
	static GsColor FromCOLORREF(unsigned int rgb);

	/// \brief 根据R，G，B，A通道构造
	/// \param r 红色通道[0,255]
	/// \param g 绿色通道[0,255]
	/// \param b 蓝色通道[0,255]
	/// \param a 透明通道[0,255]
	/// \return 
	static GsColor FromARGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

	/// \brief 从浮点R，G，B，A通道构造
	/// \param r 红色通道[0,1]
	/// \param g 绿色通道[0,1]
	/// \param b 蓝色通道[0,1]
	/// \param a 透明通道[0,1]
	/// \return 
	static GsColor FromARGBF(float r, float g, float b, float a = 1.0f);

	/// \brief 改变透明度构造已有颜色
	/// \param rhs 
	/// \param a 
	/// \return 
	static GsColor FromColor(const GsColor& rhs, unsigned char a);
	/// \brief 改变透明度构造已有颜色
	/// \param rhs 
	/// \param a 
	/// \return 
	static GsColor FromColorF(const GsColor& rhs, float a);

	/// \brief 从颜色名称构造 
	/// \param strName 
	/// \return 
	static GsColor FromName(const char* strName);

	/// \brief 颜色的名称，如果存在的话
	/// \return 
	GsString Name() const;

	/// \brief 是否是已知的颜色
	/// \return 
	bool IsKnownColor()const;


	/// \brief 生成一个随机的颜色
	/// \return 
	static GsColor Random();

	/// \brief 从HSV颜色构造
	/// \param h Hue  色调
	/// \param s Saturation 饱和度
	/// \param v Value 亮度
	/// \param a 透明度
	/// \return 
	static GsColor FromHSV(float h, float s, float v, unsigned char a = 255);

	/// \brief 用Win32 RGB颜色设置颜色值
	/// \param rgb 
	/// \param a 
	void SetCOLORREF(unsigned int rgb, unsigned char a = 255);
	/// \brief 转换为win32 RGB颜色值
	/// \return 
	unsigned int ToCOLORREF() const;

	/// \brief 以html的形式返回颜色值#RRGGBB
	/// \return 
	GsString ToHtml() const;
	/// \brief 以html的形式返回颜色值rgba(r,g,b,af);
	/// \return 
	GsString ToHtmlRGBA() const;

	/// \brief 转换为32位无符号整数
	/// \return 
	unsigned int ToUInt() const;

	/// \brief 转换HSV的颜色
	/// \param h 
	/// \param s 
	/// \param v 
	/// \return 
	bool ToHSV(float *h, float *s, float *v);

	/// \brief 转换为32位符号整数
	/// \return 
	int ToInt() const;


	/// \brief 根据R，G，B，A通道设置颜色值
	/// \param r 
	/// \param g 
	/// \param b 
	/// \param a 
	void SetARGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	/// \brief 根据R，G，B，A通道设置颜色值
	/// \param r 
	/// \param g 
	/// \param b 
	/// \param a 
	void SetARGBF(float r, float g, float b, float a = 1.0f);
	/// \brief 根据ARGB值设置
	/// \param argb 
	void SetARGB(unsigned int argb);
	/// \brief 从HSV颜色设置
	/// \param h Hue  色调
	/// \param s Saturation 饱和度
	/// \param v Value 亮度
	/// \param a 透明度
	void SetHSV(float h, float s, float v, unsigned char a = 255);

	/// \brief 浮点数R通道值
	/// \return 返回R通道值[0,1]
	float RedF()const;
	/// \brief 浮点数G通道值
	/// \return 返回G通道值[0,1]
	float GreenF()const;
	/// \brief 浮点数A通道值
	/// \return 返回A通道值[0,1]
	float AlphaF()const;
	/// \brief 浮点数B通道值
	/// \return 返回B通道值[0,1]
	float BlueF()const;

	/// \brief 等号操作符
	GsColor &operator=(unsigned int &argb);
	/// \brief 等号操作符
	GsColor &operator=(int &argb);
	/// \brief 等号操作符
	GsColor &operator=(const GsColor &rhs);
	/// \brief 颜色是否相等
	bool operator==(const GsColor &c) const;
	/// \brief 颜色是否不等
	bool operator!=(const GsColor &c) const;

	/// \brief 无符号整数重载操作符
	operator unsigned int() const;
	/// \brief 整数重载操作符
	operator int()const;

	/// \brief 颜色数据结构
	union
	{
		/// \brief ARGB颜色值
		unsigned int Argb;
		struct
		{
			unsigned char B, G, R, A;
		};
	};

	/// \brief 预制颜色值。
	enum
	{
		AliceBlue = 0xFFF0F8FF,
		AntiqueWhite = 0xFFFAEBD7,
		Aqua = 0xFF00FFFF,
		Aquamarine = 0xFF7FFFD4,
		Azure = 0xFFF0FFFF,
		Beige = 0xFFF5F5DC,
		Bisque = 0xFFFFE4C4,
		Black = 0xFF000000,
		BlanchedAlmond = 0xFFFFEBCD,
		Blue = 0xFF0000FF,
		BlueViolet = 0xFF8A2BE2,
		Brown = 0xFFA52A2A,
		BurlyWood = 0xFFDEB887,
		CadetBlue = 0xFF5F9EA0,
		Chartreuse = 0xFF7FFF00,
		Chocolate = 0xFFD2691E,
		Coral = 0xFFFF7F50,
		CornflowerBlue = 0xFF6495ED,
		Cornsilk = 0xFFFFF8DC,
		Crimson = 0xFFDC143C,
		Cyan = 0xFF00FFFF,
		DarkBlue = 0xFF00008B,
		DarkCyan = 0xFF008B8B,
		DarkGoldenrod = 0xFFB8860B,
		DarkGray = 0xFFA9A9A9,
		DarkGreen = 0xFF006400,
		DarkKhaki = 0xFFBDB76B,
		DarkMagenta = 0xFF8B008B,
		DarkOliveGreen = 0xFF556B2F,
		DarkOrange = 0xFFFF8C00,
		DarkOrchid = 0xFF9932CC,
		DarkRed = 0xFF8B0000,
		DarkSalmon = 0xFFE9967A,
		DarkSeaGreen = 0xFF8FBC8B,
		DarkSlateBlue = 0xFF483D8B,
		DarkSlateGray = 0xFF2F4F4F,
		DarkTurquoise = 0xFF00CED1,
		DarkViolet = 0xFF9400D3,
		DeepPink = 0xFFFF1493,
		DeepSkyBlue = 0xFF00BFFF,
		DimGray = 0xFF696969,
		DodgerBlue = 0xFF1E90FF,
		Feldspar = 0xFFD19275, //Html
		Firebrick = 0xFFB22222,
		FloralWhite = 0xFFFFFAF0,
		ForestGreen = 0xFF228B22,
		Fuchsia = 0xFFFF00FF,
		Gainsboro = 0xFFDCDCDC,
		GhostWhite = 0xFFF8F8FF,
		Gold = 0xFFFFD700,
		Goldenrod = 0xFFDAA520,
		Gray = 0xFF808080,
		Green = 0xFF008000,
		GreenYellow = 0xFFADFF2F,
		Honeydew = 0xFFF0FFF0,
		HotPink = 0xFFFF69B4,
		IndianRed = 0xFFCD5C5C,
		Indigo = 0xFF4B0082,
		Ivory = 0xFFFFFFF0,
		Khaki = 0xFFF0E68C,
		Lavender = 0xFFE6E6FA,
		LavenderBlush = 0xFFFFF0F5,
		LawnGreen = 0xFF7CFC00,
		LemonChiffon = 0xFFFFFACD,
		LightBlue = 0xFFADD8E6,
		LightCoral = 0xFFF08080,
		LightCyan = 0xFFE0FFFF,
		LightGoldenrodYellow = 0xFFFAFAD2,
		LightGray = 0xFFD3D3D3,
		LightGrey = 0xFFD3D3D3,//html
		LightGreen = 0xFF90EE90,
		LightPink = 0xFFFFB6C1,
		LightSalmon = 0xFFFFA07A,
		LightSeaGreen = 0xFF20B2AA,
		LightSkyBlue = 0xFF87CEFA,
		LightSlateBlue = 0xFF8470FF, //html
		LightSlateGray = 0xFF778899,
		LightSteelBlue = 0xFFB0C4DE,
		LightYellow = 0xFFFFFFE0,
		Lime = 0xFF00FF00,
		LimeGreen = 0xFF32CD32,
		Linen = 0xFFFAF0E6,
		Magenta = 0xFFFF00FF,
		Maroon = 0xFF800000,
		MediumAquamarine = 0xFF66CDAA,
		MediumBlue = 0xFF0000CD,
		MediumOrchid = 0xFFBA55D3,
		MediumPurple = 0xFF9370DB,
		MediumSeaGreen = 0xFF3CB371,
		MediumSlateBlue = 0xFF7B68EE,
		MediumSpringGreen = 0xFF00FA9A,
		MediumTurquoise = 0xFF48D1CC,
		MediumVioletRed = 0xFFC71585,
		MidnightBlue = 0xFF191970,
		MintCream = 0xFFF5FFFA,
		MistyRose = 0xFFFFE4E1,
		Moccasin = 0xFFFFE4B5,
		NavajoWhite = 0xFFFFDEAD,
		Navy = 0xFF000080,
		OldLace = 0xFFFDF5E6,
		Olive = 0xFF808000,
		OliveDrab = 0xFF6B8E23,
		Orange = 0xFFFFA500,
		OrangeRed = 0xFFFF4500,
		Orchid = 0xFFDA70D6,
		PaleGoldenrod = 0xFFEEE8AA,
		PaleGreen = 0xFF98FB98,
		PaleTurquoise = 0xFFAFEEEE,
		PaleVioletRed = 0xFFDB7093,
		PapayaWhip = 0xFFFFEFD5,
		PeachPuff = 0xFFFFDAB9,
		Peru = 0xFFCD853F,
		Pink = 0xFFFFC0CB,
		Plum = 0xFFDDA0DD,
		PowderBlue = 0xFFB0E0E6,
		Purple = 0xFF800080,
		Red = 0xFFFF0000,
		RosyBrown = 0xFFBC8F8F,
		RoyalBlue = 0xFF4169E1,
		SaddleBrown = 0xFF8B4513,
		Salmon = 0xFFFA8072,
		SandyBrown = 0xFFF4A460,
		SeaGreen = 0xFF2E8B57,
		SeaShell = 0xFFFFF5EE,
		Sienna = 0xFFA0522D,
		Silver = 0xFFC0C0C0,
		SkyBlue = 0xFF87CEEB,
		SlateBlue = 0xFF6A5ACD,
		SlateGray = 0xFF708090,
		Snow = 0xFFFFFAFA,
		SpringGreen = 0xFF00FF7F,
		SteelBlue = 0xFF4682B4,
		Tan = 0xFFD2B48C,
		Teal = 0xFF008080,
		Thistle = 0xFFD8BFD8,
		Tomato = 0xFFFF6347,
		Transparent = 0x00FFFFFF,
		Turquoise = 0xFF40E0D0,
		Violet = 0xFFEE82EE,
		VioletRed = 0xFFD02090,//html
		Wheat = 0xFFF5DEB3,
		White = 0xFFFFFFFF,
		WhiteSmoke = 0xFFF5F5F5,
		Yellow = 0xFFFFFF00,
		YellowGreen = 0xFF9ACD32,
	};
};

/// \brief 创建一个int类型的点结构体
struct GS_API GsPT
{
	int X,Y;
	GsPT();
	/// \brief 
	/// \param rhs 
	GsPT(const GsPT& rhs);
	/// \brief 
	/// \param x 
	/// \param y 
	GsPT(int x,int y);
	
	/// \brief 点Offset点
	GsPT operator +(const GsPT & pt) const;
	
	/// \brief offset自身
	GsPT& operator +=(const GsPT & pt);

	/// \brief 点Offset点
	GsPT operator -(const GsPT & pt) const;
	
	/// \brief offset自身
	GsPT& operator -=(const GsPT & pt); 
};
GS_DECLARE_REFLECT(GsPT);


/// \brief 创建一个float类型的点结构体
struct GS_API GsPTF
{
	float X,Y;

	/// \brief 缺省构造函数
	GsPTF();
	/// \brief 重载构造函数
	/// \param rhs 
	GsPTF(const GsPT& rhs);
	/// \brief 重载构造函数
	/// \param rhs 
	GsPTF(const GsPTF& rhs);
	/// \brief 重载构造函数
	/// \param x 
	/// \param y 
	GsPTF(int x,int y);
	/// \brief 重载构造函数
	/// \param x 
	/// \param y 
	GsPTF(float x,float y);

	/// \brief 点Offset点
	GsPTF operator +(const GsPTF & pt) const;
	
	/// \brief offset自身
	GsPTF& operator +=(const GsPTF & pt);
	
	/// \brief 点Offset点
	GsPTF operator -(const GsPTF & pt) const;
	
	/// \brief offset自身
	GsPTF& operator -=(const GsPTF & pt);
};

/// \brief 设置int型宽度和高度
struct GS_API GsSize
{
	int Width,Height;
	/// \brief 缺省构造函数
	GsSize();
	/// \brief 重载构造函数
	/// \param s 
	GsSize(const GsSize& s);
	/// \brief 从点构造
	/// \param p 
	GsSize(const GsPT& p);
	/// \brief 重载构造函数
	/// \param w 
	/// \param h 
	GsSize(int w,int h);
	
	/// \brief 是否相等
	bool operator == (const GsSize& s)const;
	/// \brief 赋值
	GsSize &operator = (const GsSize& s);
	/// \brief 是否不等
	bool operator != (const GsSize& s)const;

};
 
/// \brief 设置float型宽度和高度 
struct GS_API GsSizeF
{
	float Width,Height;
	/// \brief 缺省构造函数
	GsSizeF();
	/// \brief 重载构造函数
	/// \param s 
	GsSizeF(const GsSize& s);
	/// \brief 重载构造函数
	/// \param s 
	GsSizeF(const GsSizeF& s);
	/// \brief 重载构造函数
	/// \param w 
	/// \param h 
	GsSizeF(float w, float h);

	/// \brief 是否相等
	bool operator == (const GsSizeF& s)const;
	/// \brief 赋值
	GsSizeF &operator = (const GsSizeF& s);
	/// \brief 赋值
	GsSizeF &operator = (const GsSize& s);

	/// \brief 是否不等
	bool operator != (const GsSizeF& s)const;
};

/// \brief 设置Double型宽度和高度
struct GS_API GsSizeD
{
	double Width, Height;
	/// \brief 缺省构造函数
	GsSizeD();
	/// \brief 重载构造函数
	/// \param s 
	GsSizeD(const GsSize& s);
	/// \brief 重载构造函数
	/// \param s 
	GsSizeD(const GsSizeF& s);
	/// \brief 重载构造函数
	/// \param s 
	GsSizeD(const GsSizeD& s);

	/// \brief 重载构造函数
	/// \param w 
	/// \param h 
	GsSizeD(double w, double h);

	/// \brief 是否相等
	bool operator == (const GsSizeD& s)const;
	/// \brief 是否不等
	bool operator != (const GsSizeD& s)const;
	/// \brief 赋值
	GsSizeD &operator = (const GsSizeD& s);
	/// \brief 赋值
	GsSizeD &operator = (const GsSize& s);
	/// \brief 赋值
	GsSizeD &operator = (const GsSizeF& s);

};


/// \brief 创建一个int类型的矩形
struct GS_API GsRect
{
	int Left,Right,Top,Bottom;
	/// \brief 缺省构造函数
	GsRect();
	/// \brief 重载构造函数
	/// \param pt 
	/// \param s 
	GsRect(const GsPT& pt,const GsSize& s);
	/// \brief 重载构造函数
	/// \param rhs 
	GsRect(const GsRect& rhs);
	/// \brief 重载构造函数
	/// \param x 
	/// \param y 
	/// \param w 
	/// \param h 
	GsRect(int x,int y,int w,int h);
	/// \brief 设置宽度
	/// \return 
	int Width()const;
	/// \brief 设置高度
	/// \return 
	int Height()const;
	/// \brief 偏移一个位置
	/// \param pt 
	/// \return 
	GsRect& Offset(const GsPT& pt);

	/// \brief 中心点
	/// \return 
	GsPT Center()const;

	/// \brief 是否相交
	/// \param rhs 
	/// \return 
	bool IsIntersects(const GsRect& rhs)const;

	/// \brief 计算两个相交的部分
	/// \param rhs 
	/// \return 
	GsRect Intersects(const GsRect& rhs) const;

	/// \brief 是否和线相离
	/// \param x1 
	/// \param y1 
	/// \param x2 
	/// \param y2 
	/// \return 
	bool IsDisjoin(int x1,int y1,int x2,int y2)const;

	/// \brief 是否相离
	/// \param rhs 
	/// \return 
	bool IsDisjoin(const GsRect& rhs)const;

	/// \brief 是否包含
	/// \param x 
	/// \param y 
	/// \return 
	bool IsContain(int x,int y)const;

	/// \brief 是否包含
	/// \param pt 
	/// \return 
	bool IsContain(const GsPT& pt)const;

	/// \brief 是否包含
	/// \param rhs 
	/// \return 
	bool IsContain(const GsRect& rhs)const;

	/// \brief 定位点
	/// \return 
	GsPT Location()const;
	
	/// \brief 大小
	/// \return 
	GsSize Size() const;

	/// \brief 左上角
	/// \return 
	GsPT LeftTop()const;
	
	/// \brief 右上角
	/// \return 
	GsPT RightTop()const;
	
	/// \brief 左下角
	/// \return 
	GsPT LeftBottom()const;
	
	/// \brief 右下角
	/// \return 
	GsPT RightBottom()const;

	/// \brief 矩形偏移
	GsRect operator + (const GsPT& pt)const;

	/// \brief 矩形偏移
	GsRect operator - (const GsPT& pt)const;

	/// \brief 矩形偏移返回新的偏移后的矩形
	/// \param pt 
	/// \return 
	GsRect OffsetTo(const GsPT& pt)const;

	/// \brief 矩形合并
	GsRect operator + (const GsRect& rect)const;
	/// \brief 合并到自身
	GsRect& operator += (const GsRect& rect);
	
	/// \brief 矩形合并
	/// \param rect 
	/// \return 
	GsRect& Union(const GsRect& rect);

};

/// \brief 创建一个float类型的矩形
struct GS_API GsRectF
{
	float Left,Right,Top,Bottom;

	/// \brief 缺省构造函数
	GsRectF();
	/// \brief 构造函数重载
	/// \param pt 
	/// \param s 
	GsRectF(const GsPTF& pt,const GsSizeF& s);
	/// \brief 构造函数重载
	/// \param pt 
	/// \param s 
	GsRectF(const GsPT& pt,const GsSize& s);
	/// \brief 构造函数重载
	/// \param rhs 
	GsRectF(const GsRect& rhs);
	/// \brief 构造函数重载
	/// \param rhs 
	GsRectF(const GsRectF& rhs);
	/// \brief 构造函数重载
	/// \param x 
	/// \param y 
	/// \param w 
	/// \param h 
	GsRectF(int x,int y,int w,int h);
	/// \brief 构造函数重载
	/// \param x 
	/// \param y 
	/// \param w 
	/// \param h 
	GsRectF(float x,float y,float w,float h);
	/// \brief 设置宽度
	/// \return 
	float Width()const;
	/// \brief 设置高度
	/// \return 
	float Height()const;

	/// \brief 
	/// \param pt 
	/// \return 
	GsRectF& Offset(const GsPTF& pt);

	/// \brief 中心点
	/// \return 
	GsPTF Center()const;

	/// \brief 是否相交
	/// \param rhs 
	/// \return 
	bool IsIntersects(const GsRectF& rhs)const;
	/// \brief 计算两个相交的部分
	/// \param rhs 
	/// \return 
	GsRectF Intersects(const GsRectF& rhs) const;

	/// \brief 是否和线相离
	/// \param x1 
	/// \param y1 
	/// \param x2 
	/// \param y2 
	/// \return 
	bool IsDisjoin(float x1,float y1,float x2,float y2)const;

	/// \brief 是否相离
	/// \param rhs 
	/// \return 
	bool IsDisjoin(const GsRectF& rhs)const;

	/// \brief 是否包含
	/// \param x 
	/// \param y 
	/// \return 
	bool IsContain(float x,float y)const;

	/// \brief 是否包含
	/// \param pt 
	/// \return 
	bool IsContain(const GsPTF& pt)const;

	/// \brief 是否包含
	/// \param rhs 
	/// \return 
	bool IsContain(const GsRectF& rhs)const;

	/// \brief 定位点
	/// \return 
	GsPTF Location() const;
	
	/// \brief 大小
	/// \return 
	GsSizeF Size()const;

	/// \brief 左上角
	/// \return 
	GsPTF LeftTop()const;
	
	/// \brief 右上角
	/// \return 
	GsPTF RightTop()const;
	
	/// \brief 左下角
	/// \return 
	GsPTF LeftBottom()const;
	
	/// \brief 右下角
	/// \return 
	GsPTF RightBottom()const;

	/// \brief 矩形合并
	GsRectF operator + (const GsRectF& rect)const;
	/// \brief 合并到自身
	GsRectF& operator += (const GsRectF& rect);
	
	/// \brief 矩形合并
	/// \param rect 
	/// \return 
	GsRectF& Union(const GsRectF& rect);


	/// \brief 矩形偏移
	GsRectF operator + (const GsPTF& pt)const;

	/// \brief 矩形偏移
	GsRectF operator - (const GsPTF& pt)const;

	/// \brief 矩形偏移返回新的偏移后的矩形
	/// \param pt 
	/// \return 
	GsRectF OffsetTo(const GsPTF& pt)const;


	/// \brief 矩形偏移
	GsRectF operator + (const GsPT& pt)const;

	/// \brief 矩形偏移
	GsRectF operator - (const GsPT& pt)const;

	/// \brief 矩形偏移返回新的偏移后的矩形
	/// \param pt 
	/// \return 
	GsRectF OffsetTo(const GsPT& pt)const;


};

/// \brief RGBA4通道颜色类型，默认为读取为char *
enum GsRGBAType
{
	eBGRA32,//BGRA是指将内存块转换为char *，依次读取分别为BGRA。而不是int，下同。
	eABGR32,

	eRGBA32,
	eARGB32,
};

/// \brief 图像编码类型
enum GsImageEncodeType
{
	eUnknownImage,
	ePNG,
	eJPG,
	eBMP,
	eDNG,
	eGIF
};

/// \brief 图像对象
class GS_API GsImage:public GsRefObject
{
protected:
	GsRGBAType m_eRGBAType;
	GsImage();
public:
	/// \brief 析构函数
	virtual ~GsImage();

	
	/// \brief 拷贝
	/// \param pImage 
	/// \return 
	virtual bool CopyFrom(GsImage* pImage);

	/// \brief 拷贝外部数据到自身
	/// \param buff 
	/// \param nLen 
	/// \param eType 
	/// \return 
	virtual bool FillImageData(const unsigned char* buff, int nLen, GsRGBAType eType);

	/// \brief 拷贝自身的数据到外部影像
	/// \param buff 
	/// \param nLen 
	/// \param eType 
	/// \return 
	virtual int CopyImageData(unsigned char* buff, int nLen, GsRGBAType eType);

	/// \brief 将自身数据剪裁到目标图像中
	/// \param target 要存储数据的图像
	/// \param extent 要剪裁的数据范围
	/// \param offset 存储到目标数据的偏移位置
	/// \return 
	virtual bool CropTo(GsImage* target, const GsRect& extent, const GsPT& offset);


	/// \brief 将自身数据剪裁到目标内存块中
	/// \param target 要存储数据的目标内存
	/// \param nStride 目标数据行字节长度
	/// \param extent 要剪裁的数据范围
	/// \return 
	virtual bool CropTo(unsigned char* target, int nStride, const GsRect& extent);

	/// \brief 将自身数据剪裁到目标内存块中
	/// \param target 要存储数据的目标内存
	/// \param nStride 目标数据行字节长度
	/// \param extent 要剪裁的数据范围
	/// \return 
	virtual bool CropTo(GsByteBuffer* target, int nStride, const GsRect& extent);

	/// \brief 获取图片颜色格式
	/// \return 
	virtual GsRGBAType RGBAType();


	/// \brief 影像的宽和高
	virtual GsSize Size();

	/// \brief 获得宽度
	/// \return 
	virtual unsigned int Width() = 0;
	/// \brief 获得高度
	/// \return 
	virtual unsigned int Height() = 0;
	
	/// \brief 获取图像的字节数组，并非所有图像都能够成功
	/// \return 
	virtual const unsigned char* Bit() = 0;

	/// \brief 图像一行的字节长度
	/// \return 
	virtual unsigned int Stride();

	/// \brief 获取某行的首指针
	/// \param r 
	/// \return 
	virtual const unsigned char* Row(int r);

	/// \brief 保存图像为PNG格式文件
	/// \param strFile 
	/// \return 
	virtual bool SavePNG(const char* strFile);
	
	/// \brief 保存图像为PNG格式的内存块
	/// \param pBuffer 
	/// \return 
	virtual bool SavePNG(GsByteBuffer* pBuffer);

	/// \brief 保存图像为JPEG格式文件
	/// \param strFile 
	/// \param nQuality 
	/// \return 
	virtual bool SaveJPEG(const char* strFile,int nQuality=75);
	
	/// \brief 保存图像为JPEG格式的内存块
	/// \param pBuffer 
	/// \param nQuality 
	/// \return 
	virtual bool SaveJPEG(GsByteBuffer* pBuffer,int nQuality=75);
	 

	/// \brief 从文件载入生成图像
	/// \param strFile 
	/// \return 
	static GsSmarterPtr<GsImage> LoadFrom(const char* strFile);

	/// \brief 从内存块载入生成图像对象
	/// \param pBlob 
	/// \param nLen 
	/// \return 
	static GsSmarterPtr<GsImage> LoadFrom(const unsigned char *pBlob,int nLen);

	/// \brief 判断一个影像编码内存块的编码类型
	/// \param buff 
	/// \param nLen 
	/// \return 
	static GsImageEncodeType EncodeType(const unsigned char* buff, int nLen);

	/// \brief 判断一个影像文件的编码类型
	/// \param file 
	/// \return 
	static GsImageEncodeType EncodeType(const char* file);
};
/// \brief GsImagePtr
GS_SMARTER_PTR(GsImage);


/// \brief 影像格式解码器
class GS_API GsImageDecoder:public GsRefObject
{
protected:
	GsImageDecoder();
public:
	virtual ~GsImageDecoder();

	/// \brief 影像解码像素大小
	/// \return 
	virtual GsSize Size() = 0;

	/// \brief 开始解码
	/// \return 
	virtual bool BeginEncode() = 0;

	/// \brief 解码图像返回图像对象
	/// \return 
	virtual GsImagePtr Encode();

	/// \brief 解码图像，将数据如写入传入的空图像对象。
	/// \details 传入的空图像大小需要和解码器一致。
	/// \param img 
	/// \return 
	virtual bool Encode(GsImage* img) = 0;
};
/// \brief GsImageDecoderPtr
GS_SMARTER_PTR(GsImageDecoder);


/// \brief GIF格式解码
class GS_API GsGIFImageDecoder:public GsImageDecoder
{
private:
	int m_nDuration;
	GsSize m_Size;
	int m_nFrameCount;
	GsGrowByteBuffer m_srcBuffer;
	GsGrowByteBuffer m_dscBuffer;
	/// \brief 
	/// \param data 
	/// \param whdr 
	static int OnFrame(void* data, void* whdr);
	/// \brief 
	/// \param whdr 
	void Frame(void* whdr);
public:
	/// \brief 
	/// \param file 
	GsGIFImageDecoder(const char* file);
	/// \brief 
	/// \param blob 
	/// \param nlen 
	GsGIFImageDecoder(const unsigned char *blob ,int nlen);
	/// \brief 影像解码像素大小
	/// \return 
	virtual GsSize Size();

	/// \brief 开始解码
	/// \return 
	virtual bool BeginEncode() ;

	/// \brief 解码图像，将数据如写入传入的空图像对象。
	/// \details 传入的空图像大小需要和解码器一致。
	/// \param img 
	/// \return 
	virtual bool Encode(GsImage* img);

	/// \brief 图像的帧数量
	/// \return 
	virtual int FrameCount();

	/// \brief 开始读取一帧图像
	/// \param nFrameIndex 
	/// \return 
	virtual bool BeginFrame(int nFrameIndex);

	/// \brief 获取GIF播放时，帧间时间间隔
	/// \return 
	virtual int Duration();
};

/// \brief GsGIFImageDecoderPtr
GS_SMARTER_PTR(GsGIFImageDecoder);

/// \brief 影像格式编码器
class GS_API GsImageEncoder :public GsRefObject
{
protected:
	GsImageEncoder();
public:
	virtual ~GsImageEncoder();
	/// \brief 开始编码
	/// \return 
	virtual bool BeginEncode() = 0;

	/// \brief 写入影像或者一帧
	/// \param img 
	/// \return 
	virtual bool Write(GsImage* img) = 0;

	/// \brief 结束编码
	/// \return 
	virtual bool FinishEncode() = 0;
};
/// \brief GsImageEncoderPtr
GS_SMARTER_PTR(GsImageEncoder);

/// \brief GIF图像编码
class GS_API GsGIFImageEncoder :public GsImageEncoder
{
	void* m_ptrEncoder;
	GsSize m_Size;
	int m_nDuration;
	GsString m_strPath;
public:
	/// \brief 
	/// \param buff 
	GsGIFImageEncoder(GsByteBuffer* buff);
	/// \brief 
	/// \param file 
	/// \param size 
	/// \param nDuration 
	GsGIFImageEncoder(const char* file, GsSize& size, int nDuration);

	/// \brief 开始编码
	/// \return 
	virtual bool BeginEncode();

	/// \brief 开始一帧
	/// \return 
	virtual bool BeginFrame();

	/// \brief 写入影像或者一帧
	/// \param img 
	/// \return 
	virtual bool Write(GsImage* img);

	/// \brief 结束编码
	/// \return 
	virtual bool FinishEncode();
};
/// \brief GsGIFImageEncoder
GS_SMARTER_PTR(GsGIFImageEncoder);

/// \brief 针对渲染设备缓存后的Image
class GS_API GsCachedImage:public GsImage
{
protected:
	GsImagePtr m_ptrPrimitiveImage;
	GsStlMap<int, GsImagePtr> m_Cache;
public:
	/// \brief 
	/// \param primitiveImage 
	GsCachedImage(GsImage* primitiveImage);
	~GsCachedImage();

	/// \brief 获取缓存的图像
	/// \param nCache 
	/// \return 
	GsImage* CachedImage(int nCache);

	/// \brief 设置缓存的图像
	/// \param nCache 
	/// \param img 
	void CachedImage(int nCache, GsImage* img);


	/// \brief 获取图片颜色格式
	/// \return 
	virtual GsRGBAType RGBAType();



	/// \brief 获得宽度
	/// \return 
	virtual unsigned int Width() ;
	/// \brief 获得高度
	/// \return 
	virtual unsigned int Height();

	/// \brief 获取图像的字节数组，并非所有图像都能够成功
	/// \return 
	virtual const unsigned char* Bit();
};
/// \brief GsCachedImagePtr
GS_SMARTER_PTR(GsCachedImage);

/// \brief 图像处理类
class GS_API GsImageProcess
{ 
public:
	virtual ~GsImageProcess(){}
	/// \brief 返回位图影像的某行某列点像素地址
	/// \param r 
	/// \param c 
	/// \param pixel 
	/// \return 
	virtual int Process(int r, int c, unsigned  int* pixel) = 0;
};


/// \brief 内存中存储的简单位图对象
class GS_API GsSimpleBitmap:public GsImage
{
protected:
	GsGrowByteBuffer m_Buffer;
	int m_nWidth;
	int m_nHeight;
	int m_nBpp;
public :
	/// \brief 重载构造函数
	/// \param nWidth 
	/// \param nHeight 
	/// \param nBpp 
	GsSimpleBitmap(unsigned int nWidth,unsigned int nHeight,int nBpp = 32); 
	
	/// \brief 解码文件格式的图像
	/// \param strFile 
	GsSimpleBitmap(const char* strFile); 
	/// \brief 解码内存中的图像
	/// \param blob 
	/// \param nLen 
	GsSimpleBitmap(const unsigned char* blob,int nLen);  
	/// \brief 析构函数
	virtual ~GsSimpleBitmap();
	/// \brief 拷贝
	/// \param pImage 
	/// \return 
	virtual bool CopyFrom( GsImage* pImage );
	/// \brief 获得宽度
	/// \return 
	virtual unsigned int Width();
	/// \brief 获得高度
	/// \return 
	virtual unsigned int Height() ;
	/// \brief 获取图像的字节数组，并非所有图像都能够成功
	/// \return 
	virtual const unsigned char* Bit() ;
	
	/// \brief 图像一行的字节长度
	/// \return 
	virtual unsigned int Stride();
	
	/// \brief 遍历影像中各个像素
	/// \param pImageProcess 
	/// \param bParallel 
	virtual void ForEachPixel(GsImageProcess* pImageProcess, bool bParallel = false);
};
/// \brief GsSimpleBitmapPtr
GS_SMARTER_PTR(GsSimpleBitmap);


/// \brief 基于NetPbm的PAM格式文件影像
/// \details http://netpbm.sourceforge.net/
class GS_API GsPAMBitmap:public GsImage
{
	int m_nWidth;
	int m_nHeight;
	int m_nBpp;
	GsVector<unsigned char> m_RowData;
	std::fstream m_fStream;
	mutable std::fstream::pos_type m_nPixelBegin; 
public:
	/// \brief 
	/// \param strFile 
	GsPAMBitmap(const char* strFile);
	/// \brief 
	/// \param strFile 
	/// \param w 
	/// \param h 
	GsPAMBitmap(const char* strFile,int w,int h);

	/// \brief 获得宽度
	/// \return 
	virtual unsigned int Width();
	/// \brief 获得高度
	/// \return 
	virtual unsigned int Height() ;
	/// \brief 获取图像的字节数组，并非所有图像都能够成功
	/// \return 
	virtual const unsigned char* Bit() ;
	
	/// \brief 图像一行的字节长度
	/// \return 
	virtual unsigned int Stride();

	/// \brief 获取某行的首指针
	/// \param r 
	/// \return 
	virtual const unsigned char* Row(int r);

	/// \brief 获取某行的首指针
	/// \param r 
	/// \param vec 
	/// \return 
	virtual const unsigned char* Row(int r,GsVector<unsigned char> *vec);

	/// \brief 写入某行的数据
	/// \param r 
	/// \param pRowData 
	/// \param nLen 
	virtual void Row(int r,const unsigned char* pRowData,int nLen);
};
GS_SMARTER_PTR(GsPAMBitmap);


/// \brief 解析SVG为位图
class GS_API GsSVGImage:public GsImage
{
public:
	/// \brief 绘制相关参数，画笔颜色、画刷颜色、画笔宽度
	struct svgDrawParams
	{
		svgDrawParams()
			: m_fill(GsColor(255,0,0,128)), m_stroke(GsColor(255, 0, 0, 255)), m_strokeWidth(1.0)
		{

		}
		svgDrawParams(const GsColor &fill, const GsColor &stroke, double strokeWidth)
			:m_fill(fill), m_stroke(stroke), m_strokeWidth(strokeWidth)
		{

		}
		GsColor m_fill;
		GsColor m_stroke;
		double m_strokeWidth;
	};

private:
	float m_DPI;
	float m_Scale;
	void* m_pSVG;
	GsString m_SVG;
	GsImagePtr m_ptrImage;
	svgDrawParams m_svgParams;
	/// \brief 
	void CreateImage();
	/// \brief 
	void DestroyHandle();
	/// \brief 
	void CreateHandle();

protected:
//	void replaceElemParams(const GsColor &fill, const GsColor &stroke, double strokeWidth);
public:
	/// \brief 根据SVG文件或者字符串构造位图
	/// \param svg 
	/// \param bFileName 
	GsSVGImage(const char* svg,bool bFileName);
	GsSVGImage();
	
	~GsSVGImage();
	
	/// \brief 获得宽度
	/// \return 
	virtual unsigned int Width();
	/// \brief 获得高度
	/// \return 
	virtual unsigned int Height();
	
	/// \brief 获取图像的字节数组，并非所有图像都能够成功
	/// \return 
	virtual const unsigned char* Bit();

	/// \brief 获取SVG的xml字符串
	/// \return 
	GsString SVG();

	/// \brief 设置SVG字符串或者SVG文件
	/// \param svg 
	/// \param bFileName 
	void SVG(const char* svg,bool bFileName);

	/// \brief 是否是有效的SVG
	/// \return 
	bool IsValid();

	/// \brief SVG图像的宽和高
	/// \return 
	GsSize SVGSize();

	/// \brief 获取SVG绘制时的缩放比率
	/// \return 
	float SVGScale();

	/// \brief 设置SVG绘制时的缩放比率
	/// \param scale 
	void SVGScale(float scale);

	/// \brief 获取图像显示分辨率
	/// \return 
	float DPI();
	
	/// \brief 设置图像显示分辨率
	/// \param dpi 
	void DPI(float dpi);
	
	/// \brief 
	/// \param params 
	void SvgDrawParams(const svgDrawParams& params);
	/// \brief 
	/// \return 
	svgDrawParams& SvgDrawParams();
};
/// \brief GsSVGImagePtr
GS_SMARTER_PTR(GsSVGImage);

/// \brief 色带
class GS_API GsColorRamp :public Utility::GsRefObject
{
protected:
	/// \brief 色带名称
	GsString m_strName;
public:

	/// \brief 获取名称
	GsString Name();
	/// \brief 设置名称
	void Name(const char* strName);

	/// \brief 获取颜色
	/// \param value 色带渐变区间,取值0-1,其中0对应开始颜色,1对应结束颜色
	/// \return GsColor颜色对象
	virtual GsColor Color(double value) = 0;

	/// \brief 根据起止区间(0-1)和颜色数生成颜色
	/// \param nCount颜色数量
	/// \param start,end起止区间,取值0-1,其中0对应开始颜色,1对应结束颜色
	virtual void GenerateColors(int nCount, double start = 0, double end = 1) = 0;
	
	/// \brief 从配置反序列化为色带
	virtual bool Deserialize(const GsConfig& data) = 0;

	/// \brief 序列化色带到配置
	virtual bool Serialize(GsConfig& data) = 0;

	/// \brief 颜色代理,通过代理获取生成颜色的索引和颜色
	/// \details 参数1 颜色索引
	/// \details 参数2 颜色
	/// \details 返回值 颜色是否生成成功
	Utility::GsDelegate<bool(int, const GsColor&)> OnGenerateColors;
};
/// \brief GsColorRampPtr
GS_SMARTER_PTR(GsColorRamp);

/// \brief 渐变色
class GS_API GsGradsColor :public GsColorRamp
{
protected:
	/// \brief 渐变色的起止颜色
	GsColor m_from, m_to;
	/// \brief 更新渐变色
	virtual void UpdateColors() {}
public:
	/// \brief 获取开始颜色
	GsColor From();
	/// \brief 设置开始颜色
	void From(const GsColor & color);

	/// \brief 获取结束颜色
	GsColor To();
	/// \brief 设置结束颜色
	void To(const GsColor & color);

	/// \brief 获取渐变色
	/// \param value 渐变区间,取值0-1,其中0对应开始颜色,1对应结束颜色
	/// \return GsColor颜色对象
	GsColor Color(double value);
	/// \brief 根据渐变区间(0-1)和颜色数生成颜色
	/// \param nCount颜色数量
	/// \param start,end渐变区间,取值0-1,其中0对应开始颜色,1对应结束颜色
	void GenerateColors(int nCount, double start = 0, double end = 1);

	/// \brief 从配置反序列化为色带
	virtual bool Deserialize(const GsConfig& data);
	/// \brief 序列化色带到配置
	virtual bool Serialize(GsConfig& data);

};
/// \brief GsGradsColorPtr
GS_SMARTER_PTR(GsGradsColor);

/// \brief 方程式渐变色
enum GsFormulaGradesColorStyle
{
	eHSVFormula = 0,
	eHFormula = 1,
	eSFormula = 2,
	eVFormula = 3
};
/// \brief 方程式渐变色
class GS_API GsFormulaGradsColor :public GsGradsColor
{
	GsFormulaGradesColorStyle m_eStyle;
public:
	/// \brief 从起止颜色构造
	/// \param from 开始颜色
	/// \param to 结束颜色
	GsFormulaGradsColor(const GsColor& from, const GsColor& to);

	/// \brief 获取变换类型 
	GsFormulaGradesColorStyle Style();
	/// \brief 设置变换类型
	void Style(GsFormulaGradesColorStyle style);

	/// \brief 获取渐变色
	/// \param value 渐变区间,取值0-1,其中0对应开始颜色,1对应结束颜色
	/// \return GsColor颜色对象
	GsColor Color(double value);
	/// \brief 根据渐变区间(0-1)和颜色数生成颜色
	/// \param nCount颜色数量
	/// \param start,end渐变区间,取值0-1,其中0对应开始颜色,1对应结束颜色
	void GenerateColors(int nCount, double start = 0, double end = 1);
};
/// \brief GsFormulaGradsColorPtr
GS_SMARTER_PTR(GsFormulaGradsColor);

/// \brief 固定颜色数量的渐变色
/// \brief 通过一定数量的颜色进行堆叠，达到渐变的效果
class GS_API GsFixedGradsColor :public GsGradsColor
{
	GsVector<GsColor> m_Color;
	/// \brief 更新颜色
	void UpdateColors();
public:
	/// \brief 通过起止颜色，颜色数量，以及变换类型构造
	/// \brief 在起止颜色范围内,通过变换类型,随机生成由count个颜色构成的色带
	GsFixedGradsColor(const GsColor& from, const GsColor& to,
		int count = 10, GsFormulaGradesColorStyle style= eHSVFormula);
	/// \brief 通过一定数量的颜色数组构造
	GsFixedGradsColor(GsColor* colors, int count);

	/// \brief 获取渐变色数组
	GsVector<GsColor>& Colors();

	/// \brief 获取渐变色
	/// \param value 渐变区间,取值0-1,其中0对应开始颜色,1对应结束颜色
	/// \return GsColor颜色对象
	GsColor Color(double value);

	/// \brief 根据渐变区间(0-1)和颜色数生成颜色
	/// \param nCount颜色数量
	/// \param start,end渐变区间,取值0-1,其中0对应开始颜色,1对应结束颜色
	void GenerateColors(int nCount, double start = 0, double end = 1);

	/// \brief 从配置反序列化为色带
	bool Deserialize(const GsConfig& data);
	/// \brief 序列化色带到配置
	bool Serialize(GsConfig& data);
};
/// \brief GsFixedGradsColorPtr
GS_SMARTER_PTR(GsFixedGradsColor);
UTILITY_ENDNS