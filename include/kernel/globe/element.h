#pragma once
#include "utility.h"
#include "kernel.h"
#include <texturesource.h>

class UWaterMesh;
class UBboard;
class UDecal;

GLOBE_NS

/// \brief 三维场景要素基类
class GS_API Gs3DElement : public UTILITY_NAME::GsRefObject
{
	bool m_bOwner;
	bool m_bValid;
protected:
	bool m_bVisible;
	bool m_b3DElement;
	
public:
	Gs3DElement(bool bOwner=true);
	virtual ~Gs3DElement();

	/// \brief 场景要素是否由引擎管理
	virtual void Owner(bool bOwner) final;
	virtual bool Owner() const { return m_bOwner; }

	/// \brief 深度测试开关
	virtual void DepthTest(bool b) { }

	/// \brief 设置可见性
	virtual void Visible(bool b){ m_bVisible = b; }
	/// \brief 获取可见性
	virtual bool Visible() const { return m_bVisible; }

	/// \brief 是否是3D场景要素
	virtual void Element3D(bool b3DElement) { }
	virtual bool Element3D() const { return m_b3DElement; }

	/// \brief 释放显示的对象
	virtual void Destory();
};
GS_SMARTER_PTR(Gs3DElement);

class GS_API GsGeoElement : public Gs3DElement
{
protected:
	
	void* m_pElement;

	GsGeoElement(bool bOwner=true);
public:
	virtual ~GsGeoElement();

	/// \brief 设置可见性
	virtual void Visible(bool b);
	/// \brief 获取可见性
	virtual bool Visible();

	/// \brief 释放显示的对象
	virtual void Destory();

	/// \brief 几何对象
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	bool Valid();
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo) { return false; }

	// 创建2D几何要素
	virtual bool Create2DElement(KERNEL_NAME::GsGeometry* pGeo, KERNEL_NAME::GsSymbol* pSymbol);
};
GS_SMARTER_PTR(GsGeoElement);

/// \brief 点要素
class GS_API GsPointElement : public GsGeoElement
{
public:
	GsPointElement(KERNEL_NAME::GsGeometry* pGeo, KERNEL_NAME::GsPointSymbol *pSymbol);
	virtual ~GsPointElement();

	/// \brief 深度测试开关
	virtual void DepthTest(bool b);

	/// \brief 设置可见性
	virtual void Visible(bool b);
	/// \brief 获取可见性
	virtual bool Visible();

	/// \brief 释放显示的对象
	virtual void Destory();

	/// \brief 设置几何对象
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	/// \brief 显示符号
	bool Symbol(KERNEL_NAME::GsPointSymbol *pSymbol);
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo);

	// 生成图片
	UTILITY_NAME::GsImagePtr GenerateImage(KERNEL_NAME::GsPointSymbol *pPtSymbol);
};
GS_SMARTER_PTR(GsPointElement);

/// \brief 线要素
class GS_API GsLineElement : public GsGeoElement
{
public:
	GsLineElement(KERNEL_NAME::GsGeometry* pGeo, KERNEL_NAME::GsLineSymbol *pSymbol);
	virtual ~GsLineElement();

	/// \brief 深度测试开关
	virtual void DepthTest(bool b);

	/// \brief 设置可见性
	virtual void Visible(bool b);
	/// \brief 获取可见性
	virtual bool Visible();

	/// \brief 释放显示的对象
	virtual void Destory();

	/// \brief 设置几何对象
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	/// \brief 显示符号
	bool Symbol(KERNEL_NAME::GsLineSymbol *pSymbol);
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo);
};
GS_SMARTER_PTR(GsLineElement);

/// \brief 面要素
class GS_API GsFillElement : public GsGeoElement
{
public:
	GsFillElement(KERNEL_NAME::GsGeometry* pGeo, KERNEL_NAME::GsFillSymbol *pSymbol);
	virtual ~GsFillElement();

	/// \brief 深度测试开关
	virtual void DepthTest(bool b);

	/// \brief 设置可见性
	virtual void Visible(bool b);
	/// \brief 获取可见性
	virtual bool Visible();

	/// \brief 释放显示的对象
	virtual void Destory();

	/// \brief 设置几何对象
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	/// \brief 显示符号
	bool Symbol(KERNEL_NAME::GsFillSymbol *pSymbol);
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo);
};
GS_SMARTER_PTR(GsFillElement);


/// \brief 水面要素
/// \details 水面需要指定的材质，所以作为独立的Element存在
class GS_API GsWaterElement : public GsGeoElement
{
	UWaterMesh* m_ptrWaterMesh;
public:
	/// \brief 根据几何创建水面
	/// \param pGeo 携带高程值的几何数据
	GsWaterElement(KERNEL_NAME::GsGeometry* pGeo, bool bOwner = true);

	/// \brief 根据几何创建水面
	/// \param pGeo 不携带高程值的二维几何数据
	/// \param pElevation 高程值点序，长度和pGeo的点个数一致
	GsWaterElement(KERNEL_NAME::GsGeometry* pGeo, double *pElevation, bool bOwner = true);

	~GsWaterElement();

	/// \brief 深度测试开关
	virtual void DepthTest(bool b);

	/// \brief 释放显示的对象
	virtual void Destory();

	/// \brief 设置可见性
	virtual void Visible(bool b);

	/// \brief 获取可见性
	virtual bool Visible();

	/// \brief 几何对象
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	/// \brief 设置高程偏移值
	void ElevationOffside(double dblOffside);
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo);
};
GS_SMARTER_PTR(GsWaterElement);

/// \brief 广告牌要素
/// \details 标注显示广告牌，支持显示输入文字和输入图片
class GS_API GsBillboardElement : public Gs3DElement
{
public:
	GsBillboardElement(bool bOwner = true);
	virtual ~GsBillboardElement();

	/// \breif 设置深度测试
	virtual void DepthTest(bool bDepth);

	/// \brief 释放显示的对象
	virtual void Destory();

	/// \brief 设置可见性
	virtual void Visible(bool b);
	/// \brief 获取可见性
	virtual bool Visible();

	/// \brief 地理坐标
	void Position(const KERNEL_NAME::GsRawPoint3D& pt);
	/// \brief 地理坐标
	KERNEL_NAME::GsRawPoint3D Position();

	/// \brief 设置文字符号
	void TextSymbol(KERNEL_NAME::GsTextSymbol* pTextSymbol, KERNEL_NAME::GsFillSymbol* pBkSymbol=0);

	/// \brief 设置显示图片
	void Image(UTILITY_NAME::GsImage* pImage);

	/// \brief 最小可视距离
	void MinVisibleDistance(float fDis);
	/// \brief 最大可视距离
	void MaxVisibleDistance(float fDis);

	/// \brief 设置图标锚点位置(0，0 表示正中间，左下角-1，-1，右上角1，1，默认左下角)
	void AnchorPosition(float x, float y);

	/// \brief 获取屏幕像素范围
	UTILITY_NAME::GsRect ScreenRect();
protected:
	std::shared_ptr<UBboard> m_pUBboard;
};
GS_SMARTER_PTR(GsBillboardElement);

/// \brief 贴花基类,该类无法实例化，请使用其子类
/// \details 用于将纹理贴到任意地方
class GS_API GsDecalElement : public Gs3DElement
{
protected:
	GsDecalElement();
public:
	virtual ~GsDecalElement();

	/// \brief 释放显示的对象
	virtual void Destory();

	/// \brief 设置可见性
	virtual void Visible(bool bVisible);
	/// \brief 获取可见性
	virtual bool Visible();

	/// \brief 更新
	virtual void Update();

	/// \brief 地理坐标
	virtual void Position(const KERNEL_NAME::GsRawPoint3D& position);
	/// \brief 地理坐标
	virtual KERNEL_NAME::GsRawPoint3D Position();

	/// \brief 设置显示图片
	void Image(UTILITY_NAME::GsImage* pImage);

	/// \brief 设置纹理源
	/// \details 通过该参数可以实现很多特殊效果比如gif、视频播放等，可按需扩展
	void TextureSource(GsTextureSource* ptrTextureSource);
	/// \brief 获取纹理源
	GsTextureSource* TextureSource();

	/// \brief 设置最小可视距离
	virtual void MinVisibleDistance(float minDistance);
	/// \brief 获取最小可视距离
	virtual float MinVisibleDistance() const;

	/// \brief 设置最大可视距离
	virtual void MaxVisibleDistance(float maxDistance);
	/// \brief 获取最大可视距离
	virtual float MaxVisibleDistance() const;

	/// \brief 设置最大消失距离
	virtual void MaxFadeDistance(float maxFadeDistance);
	/// \brief 获取最大消失距离
	virtual float MaxFadeDistance() const;

	/// \brief 设置最小消失距离
	virtual void MinFadeDistance(float minFadeDistance);
	/// \brief 获取最小消失距离
	virtual float MinFadeDistance() const;

	/// \brief 设置偏航角(Z轴逆时针旋转)
	/// \details 以正北方向球切平面坐标系
	void Yaw(float angle);
	/// \brief 获取偏航角
	float Yaw() const;

	/// \brief 设置俯仰角(X轴逆时针旋转)
	/// \details 以正北方向球切平面坐标系
	void Pitch(float angle);
	/// \brief 获取俯仰角
	float Pitch() const;

protected:
	UDecal* m_ptrDecal;
	GsTextureSourcePtr m_ptrTextureSrc;
	unsigned long long m_preHash;
};
GS_SMARTER_PTR(GsDecalElement);

/// \brief 正交投影贴花
/// \details 用于将纹理贴到任意地方,原理为一个指定长、宽、高的长方体朝着指定方向投影(默认为地球上任意一点朝着地心方向)
/// \details 长和宽决定了投影的尺寸(一般情况下和纹理保持同样的比例)，高决定投影是否有效。只有该长方体底部面与待投影面相交时，才会被投影
class GS_API GsDecalOrthoElement : public GsDecalElement
{
public:

	/// \brief 构造函数
	/// \param position 投影中心点
	/// \param lenght 长方体长
	/// \param width 长方体宽
	/// \param height 长方体高
	GsDecalOrthoElement(const KERNEL_NAME::GsRawPoint3D& position, float lenght, float width, float height);
	virtual ~GsDecalOrthoElement();

	/// \brief 设置投影框长
	void Lenght(float lenght);
	/// \brief 获取投影框长
	float Lenght() const;

	/// \brief 设置投影框宽
	void Width(float width);
	/// \brief 获取投影框宽
	float Width() const;

	/// \brief 设置投影框高
	void Height(float height);
	/// \brief 获取投影框高
	float Height() const;
};

GS_SMARTER_PTR(GsDecalOrthoElement);

/// \brief 透视投影贴花
/// \details 用于将纹理贴到任意地方,原理为一个指定fov角、长宽比、投影高的视锥体朝着指定方向投影(默认为地球上任意一点朝着地心方向)
/// \details aspect决定了投影的长宽比(一般情况下和纹理保持同样的比例)
/// \details fov角决定了投影的大小，角度越大投影越大。建议在0-90度之间
/// \details 高决定投影是否有效。只有该长方体底部面与待投影面相交时，才会被投影
class GS_API GsDecalProjectionElement : public GsDecalElement
{
public:

	/// \brief 构造函数
	/// \param position 投影中心点
	/// \param fov 视锥体fov角
	/// \param aspect 视锥体长宽比
	/// \param height 投影高
	GsDecalProjectionElement(const KERNEL_NAME::GsRawPoint3D& position, float fov, float aspect, float height);
	virtual ~GsDecalProjectionElement();

	/// \brief 设置长宽比
	void Aspect(float aspect);
	/// \brief 获取长宽比
	float Aspect() const;
	/// \brief 设置Fov角
	void Fov(float fov);
	/// \brief 获取Fov角
	float Fov() const;
	/// \brief 设置投影高度
	void Height(float height);
	/// \brief 获取投影高度
	float Height() const;
};

GS_SMARTER_PTR(GsDecalOrthoElement);

GLOBE_ENDNS